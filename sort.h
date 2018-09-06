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

				swap(*j, *(j - 1));
			}
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	void _dualPivotQuickSort(RandomAccessIterator first, RandomAccessIterator last, const Compare cmp)
	{
		while (true)
		{
			auto length = last - first;
			if (length <= 1)
				return;

			if (length < 27)
			{
				insertionSort(first, last, cmp);
				return;
			}
			
			auto div = length / 3;
			RandomAccessIterator pivot1 = first + div;
			RandomAccessIterator pivot2 = last - div;

			if (cmp(*pivot1, *pivot2))
			{
				swap(*pivot1, *first);
				swap(*pivot2, *(last - 1));
			}
			else
			{
				swap(*pivot2, *first);
				swap(*pivot1, *(last - 1));
			}

			pivot1 = first;
			pivot2 = last - 1;

			RandomAccessIterator less = pivot1 + 1;
			RandomAccessIterator great = pivot2 - 1;
			RandomAccessIterator i = less;

			while(i - great <= 0)
			{
				if (cmp(*i, *pivot1))
				{
					swap(*i, *less);
					++less;
				}
				else if (!cmp(*i, *pivot2))
				{
					while (cmp(*pivot2, *great) && (i - great) < 0)
						--great;

					swap(*i, *great);
					--great;

					if (cmp(*i, *pivot1))
					{
						swap(*i, *less);
						++less;
					}
				}

				++i;
			}

			--less;
			++great;

			swap(*pivot1, *less);
			swap(*pivot2, *great);

			auto length1 = less - first;
			auto length2 = great - (less + 1);
			auto length3 = last - (great + 1);

			if (length1 > length2)
			{
				if (length3 > length1)
				{
					_dualPivotQuickSort(first, less, cmp);
					_dualPivotQuickSort(less + 1, great, cmp);
					first = great + 1;
				}
				else
				{
					_dualPivotQuickSort(less + 1, great, cmp);
					_dualPivotQuickSort(great + 1, last, cmp);
					last = less;
				}
			}
			else
			{
				if (length3 > length2)
				{
					_dualPivotQuickSort(first, less, cmp);
					_dualPivotQuickSort(less + 1, great, cmp);
					first = great + 1;
				}
				else
				{
					_dualPivotQuickSort(first, less, cmp);
					_dualPivotQuickSort(great + 1, last, cmp);
					first = less + 1;
					last = great;
				}
			}
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	void sort(const RandomAccessIterator first, const RandomAccessIterator last, const Compare cmp)
	{
		_dualPivotQuickSort(first, last, cmp);
	}
}