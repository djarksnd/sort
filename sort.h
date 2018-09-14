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
	void _dualPivotQuickSort(RandomAccessIterator first, RandomAccessIterator last, const Compare& cmp)
	{
		while (first < last)
		{
			auto length = last - first;

			switch (length)
			{
			case 1:
				return;
			case 2:
				if (cmp(*(first + 1), *first))
					sort::swap(*(first + 1), *first);
				return;
			case 3:
				sort::_sort3(first, first + 1, first + 2, cmp);
				return;
			case 4:
				sort::_sort4(first, first + 1, first + 2, first + 3, cmp);
				return;
			case 5:
				sort::_sort5(first, first + 1, first + 2, first + 3, first + 4, cmp);
				return;
			}

			if (length <= 32)
			{
				sort::insertionSort(first, last, cmp);
				return;
			}
			else
			{
				auto offset = length / 4;
				RandomAccessIterator pivot1 = first + offset;
				RandomAccessIterator middel = pivot1 + offset;
				RandomAccessIterator pivot2 = middel + offset;

				sort::_sort5(first, pivot1, middel, pivot2, last - 1, cmp);

				if (cmp(*first, *pivot1))
					sort::swap(*pivot1, *first);

				if (cmp(*middel, *pivot2))
					sort::swap(*pivot2, *(last - 1));
				else
					sort::swap(*middel, *(last - 1));

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

				if (length > 256)
				{
					for (RandomAccessIterator i = less + 1; i < great; ++i)
					{
						if (!cmp(*less, *i))
						{
							++pivot1;
							sort::swap(*i, *pivot1);
						}
					}

					for (RandomAccessIterator i = great + 1; i < last; ++i)
					{
						if (!cmp(*great, *i))
						{
							++pivot2;
							sort::swap(*i, *pivot2);
						}
					}
				}

				const auto length1 = less - first;
				const auto length2 = great - (pivot1 + 1);
				const auto length3 = last - (pivot2 + 1);

				if (length1 > length2)
				{
					sort::_dualPivotQuickSort(pivot1 + 1, great, cmp);

					if (length3 > length1)
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

					if (length3 > length2)
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
			}
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	void sort(const RandomAccessIterator& first, const RandomAccessIterator& last, const Compare& cmp)
	{
		sort::_dualPivotQuickSort(first, last, cmp);
	}
}