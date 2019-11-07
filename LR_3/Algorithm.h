#ifndef ALGORITHM_H
#define ALGORITHM_H

template<class _DataType>
VectorIterator<_DataType> MinElement(VectorIterator<_DataType> beg_iter, VectorIterator<_DataType> end_iter)
{
	VectorIterator<_DataType> iter_min = beg_iter;
	for (; beg_iter < end_iter; beg_iter++)
	{
		if (*iter_min > *beg_iter)
		{
			iter_min = beg_iter;
		}
	}
	return iter_min;
}

template<class _DataType>
VectorIterator<_DataType> MaxElement(VectorIterator<_DataType> beg_iter, VectorIterator<_DataType> end_iter)
{
	VectorIterator<_DataType> iter_max = beg_iter;
	for (; beg_iter < end_iter; beg_iter++)
	{
		if (*iter_max < *beg_iter)
		{
			iter_max = beg_iter;
		}
	}
	return iter_max;
}

template <class _DataType, class _Fn>
void Sort(VectorIterator<_DataType> beg_iter, VectorIterator<_DataType> end_iter, _Fn Function)
{
	while (beg_iter < --end_iter)
	{
		for (VectorIterator<_DataType> i = beg_iter; i < end_iter; ++i)
		{
			VectorIterator<_DataType> iplus = i + 1;
			if (Function(*iplus,*i))
			{
				std::iter_swap(i, iplus);
			}
		}
	}
}

template < class _Fn,class _SrcIterType, class _DstIterType>
_DstIterType CopyIf(_SrcIterType source_beg_iter, _SrcIterType source_end_iter,
	_DstIterType dest_beg_iter, _Fn Function)
{
	auto beg = source_beg_iter;
	const auto last = source_end_iter;
	auto dest = dest_beg_iter;
	for (; beg < last; ++beg)
	{
		if (Function(*beg))
		{
			*dest = *beg;
			++dest;
		}
	}
	return dest;
}

template <class _DataType, class _Fn>
_Fn ForEach(VectorIterator<_DataType> beg_iter, VectorIterator<_DataType> end_iter, _Fn Function)
{
	auto beg = beg_iter;
	const auto last = end_iter;
	for (; beg < last; ++beg)
	{
		Function(*beg);
	}
	return (Function);
}

template<class _DataType, class _Fn>
VectorIterator<_DataType> FindIf(VectorIterator<_DataType> beg_iter, VectorIterator<_DataType> end_iter, _Fn Function)
{
	auto beg = beg_iter;
	const auto last = end_iter;
	for (; beg < last; ++beg)
	{
		if (Function(*beg))
		{
			break;
		}
	}
	return (beg);
};

#endif ALGORITHM_H