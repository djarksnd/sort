#pragma once

namespace sort
{
	template<typename T>
	inline void swap(T& left, T& right)
	{
		const T temp = left;
		left = right;
		right = temp;
	}

	template<typename RandomAccessIterator, typename Compare>
	inline void insertionSort(const RandomAccessIterator& first, const RandomAccessIterator& last, const Compare& cmp)
	{
		for (RandomAccessIterator i = first + 1; i != last; ++i)
		{
			for (RandomAccessIterator j = i; j != first; --j)
			{
				if (!cmp(*j, *(j - 1)))
					break;

				sort::swap(*j, *(j - 1));
			}
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	inline void _sort3(
		const RandomAccessIterator& first,
		const RandomAccessIterator& second,
		const RandomAccessIterator& third,
		const Compare& cmp)
	{
		if (!cmp(*second, *first))
		{
			if (!cmp(*third, *second))
				return;

			sort::swap(*second, *third);

			if (cmp(*second, *first))
			{
				sort::swap(*first, *second);
			}

			return;
		}

		if (cmp(*third, *second))
		{
			sort::swap(*first, *third);
			return;
		}

		sort::swap(*first, *second);

		if (cmp(*third, *second))
		{
			sort::swap(*second, *third);
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	inline void _sort4(
		const RandomAccessIterator& first,
		const RandomAccessIterator& second,
		const RandomAccessIterator& third,
		const RandomAccessIterator& fourth, const Compare& cmp)
	{
		sort::_sort3(first, second, third, cmp);
		if (cmp(*fourth, *third))
		{
			sort::swap(*third, *fourth);
			if (cmp(*third, *second))
			{
				sort::swap(*second, *third);
				if (cmp(*second, *first))
				{
					sort::swap(*first, *second);
				}
			}
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	inline void _sort5(
		const RandomAccessIterator& first,
		const RandomAccessIterator& second,
		const RandomAccessIterator& third,
		const RandomAccessIterator& fourth,
		const RandomAccessIterator& fifth,
		const Compare& cmp)
	{
		sort::_sort4(first, second, third, fourth, cmp);
		if (cmp(*fifth, *fourth))
		{
			sort::swap(*fourth, *fifth);
			if (cmp(*fourth, *third))
			{
				sort::swap(*third, *fourth);
				if (cmp(*third, *second))
				{
					sort::swap(*second, *third);
					if (cmp(*second, *first))
					{
						sort::swap(*first, *second);
					}
				}
			}
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	inline RandomAccessIterator _guessPivot(const RandomAccessIterator& first, const RandomAccessIterator& last, const Compare& cmp)
	{
		const auto count = last - first;
		if (40 < count)
		{
			const auto offset = (count + 1) / 10;
			const RandomAccessIterator samples[11] = {
				first,
				first + offset,
				first + (offset * 2),
				first + (offset * 3),
				first + (offset * 4),
				first + (offset * 5),
				first + (offset * 6),
				first + (offset * 7),
				first + (offset * 8),
				first + (offset * 9),
				last - 1 };

			for (size_t i = 1; i < 11; ++i)
			{
				for (size_t j = i; j > 0; --j)
				{
					if (!cmp(*(samples[j]), *(samples[j - 1])))
						break;

					sort::swap(*(samples[j]), *(samples[j - 1]));
				}
			}

			return samples[5];
		}
		else
		{
			const RandomAccessIterator middle = first + ((last - first) >> 1);
			const auto step = (count + 1) >> 2;
			const auto lastMinusOne = last - 1;
			sort::_sort5(first, first + step, middle, lastMinusOne - step, lastMinusOne, cmp);

			return middle;
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	inline void _partition(RandomAccessIterator& first, RandomAccessIterator& last, const Compare& cmp, RandomAccessIterator& outSecond, RandomAccessIterator& outThird)
	{
		RandomAccessIterator pivot = sort::_guessPivot(first, last, cmp);
		sort::swap(*pivot, *(last - 1));
		pivot = last - 1;

		outSecond = first;

		for (RandomAccessIterator i = first; i < pivot; ++i)
		{
			if (cmp(*i, *pivot))
			{
				sort::swap(*i, *outSecond);
				++outSecond;
			}
		}

		sort::swap(*pivot, *outSecond);

		outThird = outSecond + 1;
		for (RandomAccessIterator i = outThird; i < last; ++i)
		{
			if (!cmp(*outSecond, *i))
			{
				std::swap(*i, *(outThird));
				++outThird;
			}
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	inline void _quickSort(RandomAccessIterator first, RandomAccessIterator last, const Compare& cmp)
	{
	quickSortLoopStart:
		auto count = last - first;

		if (count > 32)
		{
			RandomAccessIterator second;
			RandomAccessIterator third;
			sort::_partition(first, last, cmp, second, third);

			if (last - third > second - first)
			{
				sort::_quickSort(first, second, cmp);
				first = third;
			}
			else
			{
				sort::_quickSort(third, last, cmp);
				last = second;
			}

			goto quickSortLoopStart;
		}
		else if (count > 1)
		{
			insertionSort(first, last, cmp);
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	inline void sort(const RandomAccessIterator& first, const RandomAccessIterator& last, const Compare& cmp)
	{
		sort::_quickSort(first, last, cmp);
	}
}