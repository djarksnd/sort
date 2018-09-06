#pragma once

namespace sort
{
	template<typename T>
	void swap(T& left, T& right)
	{
		T temp = left;
		left = right;
		right = temp;
	}

	template<typename RandomAccessIterator, typename Compare>
	void insertionSort(const RandomAccessIterator first, const RandomAccessIterator last, const Compare cmp)
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
	void _dualPivotQuickSort(RandomAccessIterator first, RandomAccessIterator last, const Compare cmp)
	{
		while (true)
		{
			const auto length = last - first;
			if (length <= 1)
				return;

			if (length < 27)
			{
				sort::insertionSort(first, last, cmp);
				return;
			}
			
			auto div = length / 3;
			RandomAccessIterator pivot1 = first + div;
			RandomAccessIterator pivot2 = last - div;

			if (cmp(*pivot1, *pivot2))
			{
				sort::swap(*pivot1, *first);
				sort::swap(*pivot2, *(last - 1));
			}
			else
			{
				sort::swap(*pivot2, *first);
				sort::swap(*pivot1, *(last - 1));
			}

			pivot1 = first;
			pivot2 = last - 1;

			RandomAccessIterator less = pivot1 + 1;
			RandomAccessIterator great = pivot2 - 1;

			for (RandomAccessIterator i = less; i - great <= 0; ++i)
			{
				if (cmp(*i, *pivot1))
				{
					sort::swap(*i, *less);
					++less;
				}
				else if (!cmp(*i, *pivot2))
				{
					while (cmp(*pivot2, *great) && (i - great) < 0)
						--great;

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

			auto length1 = less - first;
			auto length2 = great - (less + 1);
			auto length3 = last - (great + 1);

			if (length1 > length2)
			{
				if (length3 > length1)
				{
					sort::_dualPivotQuickSort(first, less, cmp);
					sort::_dualPivotQuickSort(less + 1, great, cmp);
					first = great + 1;
				}
				else
				{
					sort::_dualPivotQuickSort(less + 1, great, cmp);
					sort::_dualPivotQuickSort(great + 1, last, cmp);
					last = less;
				}
			}
			else
			{
				if (length3 > length2)
				{
					sort::_dualPivotQuickSort(first, less, cmp);
					sort::_dualPivotQuickSort(less + 1, great, cmp);
					first = great + 1;
				}
				else
				{
					sort::_dualPivotQuickSort(first, less, cmp);
					sort::_dualPivotQuickSort(great + 1, last, cmp);
					first = less + 1;
					last = great;
				}
			}
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	void sort(const RandomAccessIterator first, const RandomAccessIterator last, const Compare cmp)
	{
		sort::_dualPivotQuickSort(first, last, cmp);
	}
}