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
	inline void _dualPivotQuickSort(RandomAccessIterator first, RandomAccessIterator last, const Compare& cmp)
	{
	dualPivotQuickSortLoopStart:

		auto count = last - first;
		if (count > 32)
		{
			RandomAccessIterator pivot1;
			RandomAccessIterator pivot2;

			if (count > 4096)
			{
				const auto offset = (count + 1) / 34;
				const RandomAccessIterator samples[35] = {
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
					first + (offset * 10),
					first + (offset * 11),
					first + (offset * 12),
					first + (offset * 13),
					first + (offset * 14),
					first + (offset * 15),
					first + (offset * 16),
					first + (offset * 17),
					first + (offset * 18),
					first + (offset * 19),
					first + (offset * 20),
					first + (offset * 21),
					first + (offset * 22),
					first + (offset * 23),
					first + (offset * 24),
					first + (offset * 25),
					first + (offset * 26),
					first + (offset * 27),
					first + (offset * 28),
					first + (offset * 29),
					first + (offset * 30),
					first + (offset * 31),
					first + (offset * 32),
					first + (offset * 33),
					last - 1 };

				for (size_t i = 1; i < 35; ++i)
				{
					for (size_t j = i; j > 0; --j)
					{
						if (!cmp(*(samples[j]), *(samples[j - 1])))
							break;

						sort::swap(*(samples[j]), *(samples[j - 1]));
					}
				}

				pivot1 = samples[11];
				pivot2 = samples[23];
			}
			else if (count > 40)
			{
				auto offset = (count + 1) / 13;
				RandomAccessIterator samples[14] = {
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
					first + (offset * 10),
					first + (offset * 11),
					first + (offset * 12),
					last - 1 };

				for (size_t i = 1; i < 14; ++i)
				{
					for (size_t j = i; j > 0; --j)
					{
						if (!cmp(*(samples[j]), *(samples[j - 1])))
							break;

						sort::swap(*(samples[j]), *(samples[j - 1]));
					}
				}

				pivot1 = samples[4];
				pivot2 = samples[9];
			}
			else
			{
				auto offset = (count + 1) / 4;
				pivot1 = first + offset;
				const RandomAccessIterator middel = pivot1 + offset;
				pivot2 = middel + offset;

				sort::_sort5(first, pivot1, middel, pivot2, last - 1, cmp);
			}

			sort::swap(*pivot1, *first);
			sort::swap(*pivot2, *(last - 1));

			pivot1 = first;
			pivot2 = last - 1;

			RandomAccessIterator less = pivot1 + 1;
			RandomAccessIterator great = pivot2 - 1;

			for (RandomAccessIterator i = less; i <= great; ++i)
			{
				if (cmp(*i, *pivot1))
				{
					sort::swap(*i, *less);
					++less;
				}
				else if (!cmp(*i, *pivot2))
				{
					while (cmp(*pivot2, *great) && i < great)
					{
						--great;
					}

					sort::swap(*i, *great);
					--great;

					if (cmp(*i, *pivot1))
					{
						sort::swap(*i, *less);
						++less;
					}
				}
			}

			--less;
			++great;

			sort::swap(*pivot1, *less);
			sort::swap(*pivot2, *great);

			pivot1 = less;
			pivot2 = great;

			for (RandomAccessIterator i = less + 1; i < great; ++i)
			{
				if (!cmp(*less, *i))
				{
					++pivot1;
					std::swap(*i, *pivot1);
				}
			}

			for (RandomAccessIterator i = great + 1; i < last; ++i)
			{
				if (!cmp(*great, *i))
				{
					++pivot2;
					std::swap(*i, *pivot2);
				}
			}

			const auto count1 = less - first;
			const auto count2 = great - (pivot1 + 1);
			const auto count3 = last - (pivot2 + 1);

			if (count1 > count2)
			{
				sort::_dualPivotQuickSort(pivot1 + 1, great, cmp);

				if (count3 > count1)
				{
					sort::_dualPivotQuickSort(first, less, cmp);
					first = pivot2 + 1;
				}
				else
				{
					sort::_dualPivotQuickSort(pivot2 + 1, last, cmp);
					last = less;
				}
			}
			else
			{
				sort::_dualPivotQuickSort(first, less, cmp);

				if (count3 > count2)
				{
					sort::_dualPivotQuickSort(pivot1 + 1, great, cmp);
					first = pivot2 + 1;
				}
				else
				{
					sort::_dualPivotQuickSort(pivot2 + 1, last, cmp);
					first = pivot1 + 1;
					last = great;
				}
			}

			goto dualPivotQuickSortLoopStart;
		}
		else if (count > 1)
		{
			sort::insertionSort(first, last, cmp);
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	inline void sort(const RandomAccessIterator& first, const RandomAccessIterator& last, const Compare& cmp)
	{
		sort::_dualPivotQuickSort(first, last, cmp);
	}
}