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
	inline size_t _sort3(
		const RandomAccessIterator first, 
		const RandomAccessIterator second, 
		const RandomAccessIterator third, 
		const Compare cmp)
	{
		size_t numSwap = 0;
		if (!cmp(*second, *first))
		{
			if (!cmp(*third, *second))
				return numSwap;

			sort::swap(*second, *third);
			numSwap = 1;

			if (cmp(*second, *first))
			{
				sort::swap(*first, *second);
				numSwap = 2;
			}

			return numSwap;
		}

		if (cmp(*third, *second))
		{
			sort::swap(*first, *third);
			numSwap = 1;
			return numSwap;
		}
		
		sort::swap(*first, *second);
		numSwap = 1;
		
		if (cmp(*third, *second))
		{
			sort::swap(*second, *third);
			numSwap = 2;
		}

		return numSwap;
	}

	template<typename RandomAccessIterator, typename Compare>
	inline size_t _sort4(
		const RandomAccessIterator first, 
		const RandomAccessIterator second, 
		const RandomAccessIterator third, 
		const RandomAccessIterator fourth, const Compare cmp)
	{
		size_t numSwap = sort::_sort3(first, second, third, cmp);
		if (cmp(*fourth, *third))
		{
			sort::swap(*third, *fourth);
			++numSwap;
			if (cmp(*third, *second))
			{
				sort::swap(*second, *third);
				++numSwap;
				if (cmp(*second, *first))
				{
					sort::swap(*first, *second);
					++numSwap;
				}
			}
		}
		return numSwap;
	}

	template<typename RandomAccessIterator, typename Compare>
	inline size_t _sort5(
		const RandomAccessIterator first, 
		const RandomAccessIterator second, 
		const RandomAccessIterator third,
		const RandomAccessIterator fourth, 
		const RandomAccessIterator fifth, 
		const Compare cmp)
	{
		size_t numSwap = sort::_sort4(first, second, third, fourth, cmp);
		if (cmp(*fifth, *fourth))
		{
			sort::swap(*fourth, *fifth);
			++numSwap;
			if (cmp(*fourth, *third))
			{
				sort::swap(*third, *fourth);
				++numSwap;
				if (cmp(*third, *second))
				{
					sort::swap(*second, *third);
					++numSwap;
					if (cmp(*second, *first))
					{
						sort::swap(*first, *second);
						++numSwap;
					}
				}
			}
		}

		return numSwap;
	}

	template<typename RandomAccessIterator, typename Compare>
	void _dualPivotQuickSort(RandomAccessIterator first, RandomAccessIterator last, const Compare cmp)
	{
	dualPivotQuickSortLoop:
		auto length = last - first;

		switch (length)
		{
		case 0:
		case 1:
			return;
		case 2:
			if (cmp(*(first + 1), *first))
			{
				sort::swap(*(first + 1), *first);
			}
			return;
		case 3:
			_sort3(first, first + 1, first + 2, cmp);
			return;
		case 4:
			_sort4(first, first + 1, first + 2, first + 3, cmp);
			return;
		case 5:
			_sort5(first, first + 1, first + 2, first + 3, first + 4, cmp);
			return;
		}

		if (length < 8)
		{
			sort::insertionSort(first, last, cmp);
			return;
		}

		RandomAccessIterator pivot1;
		RandomAccessIterator pivot2;
		size_t numSwap = 0;

		{
			const auto offset = length / 4;
			RandomAccessIterator p1 = first;
			RandomAccessIterator p2 = p1 + offset;
			RandomAccessIterator p3 = p2 + offset;
			RandomAccessIterator p4 = p3 + offset;
			RandomAccessIterator p5 = last - 1;
			numSwap = _sort5(p1, p2, p3, p4, p5, cmp);

			if (!cmp(*p2, *p3))
				pivot1 = p1;
			else
				pivot1 = p2;

			if (!cmp(*p3, *p4))
				pivot2 = p5;
			else
				pivot2 = p4;

			if (pivot1 != first)
			{
				sort::swap(*pivot1, *first);
				pivot1 = first;
			}
			if (pivot2 != last - 1)
			{
				sort::swap(*pivot2, *(last - 1));
				pivot2 = last - 1;
			}
		}

		RandomAccessIterator less = pivot1 + 1;
		RandomAccessIterator great = pivot2 - 1;

		for (RandomAccessIterator i = less; i <= great; ++i)
		{
			if (cmp(*i, *pivot1))
			{
				if (i != less)
				{
					sort::swap(*i, *less);
					++numSwap;
				}

				++less;
			}
			else if (!cmp(*i, *pivot2))
			{
				while (cmp(*pivot2, *great) && i < great)
				{
					--great;
				}

				if (i != great)
				{
					sort::swap(*i, *great);
					++numSwap;
				}

				--great;

				if (cmp(*i, *pivot1))
				{
					if (i != less)
					{
						sort::swap(*i, *less);
						++numSwap;
					}

					++less;
				}
			}
		}

		--less;
		++great;

		if (pivot1 != less)
		{
			sort::swap(*pivot1, *less);
			pivot1 = less;
		}
		
		if (pivot2 != great)
		{
			sort::swap(*pivot2, *great);
			pivot2 = great;
		}

		for (RandomAccessIterator i = less + 1; i < great; ++i)
		{
			// *i == *less
			if (!cmp(*less, *i))
			{
				++pivot1;
				if (i != pivot1)
				{
					sort::swap(*i, *pivot1);
					++numSwap;
				}
			}
		}

		for (RandomAccessIterator i = great + 1; i < last; ++i)
		{
			// *i == *great
			if (!cmp(*great, *i))
			{
				++pivot2;
				if (i != pivot2)
				{
					sort::swap(*i, *pivot2);
					++numSwap;
				}
			}
		}

		if (numSwap == 0)
		{
			sort::insertionSort(first, less, cmp);
			sort::insertionSort(pivot1 + 1, great, cmp);
			sort::insertionSort(pivot2 + 1, last, cmp);
			return;
		}

		const auto length1 = less - first;
		const auto length2 = great - (pivot1 + 1);
		const auto length3 = last - (pivot2 + 1);

		if (length1 > length2)
		{
			if (length3 > length1)
			{
				sort::_dualPivotQuickSort(first, less, cmp);
				sort::_dualPivotQuickSort(pivot1 + 1, great, cmp);
				first = pivot2 + 1;
			}
			else
			{
				sort::_dualPivotQuickSort(pivot1 + 1, great, cmp);
				sort::_dualPivotQuickSort(pivot2 + 1, last, cmp);
				last = less;
			}
		}
		else
		{
			if (length3 > length2)
			{
				sort::_dualPivotQuickSort(first, less, cmp);
				sort::_dualPivotQuickSort(pivot1 + 1, great, cmp);
				first = pivot2 + 1;
			}
			else
			{
				sort::_dualPivotQuickSort(first, less, cmp);
				sort::_dualPivotQuickSort(pivot2 + 1, last, cmp);
				first = pivot1 + 1;
				last = great;
			}
		}

		goto dualPivotQuickSortLoop;
	}

	template<typename RandomAccessIterator, typename Compare>
	void sort(const RandomAccessIterator first, const RandomAccessIterator last, const Compare cmp)
	{
		sort::_dualPivotQuickSort(first, last, cmp);
	}
}