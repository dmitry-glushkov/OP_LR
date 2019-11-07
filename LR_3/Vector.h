#ifndef VECTOR_H
#define VECTOR_H
//using namespace std;

template <class _DataType>
class oIterator
{
private:
	std::ostream & m_Out;
public:
	oIterator(std::ostream & p_Out):m_Out(p_Out)
	{

	}
	oIterator & operator=(const _DataType & obj_p)
	{
		m_Out << obj_p;
		return *this;
	}
	oIterator & operator++()
	{
		return *this;
	}
	oIterator & operator++(int)
	{
		return *this;
	}
	oIterator & operator*()
	{
		return *this;
	}
};

template <class _DataType>
class VectorIterator
{
private:

	_DataType * idx;

public:

	VectorIterator()
	{
		idx = nullptr;
	}

	VectorIterator(_DataType * idx_p)
	{
		idx = idx_p;
	}

	VectorIterator(const VectorIterator & iter_p)
	{
		idx = iter_p.idx;
	}

	VectorIterator(VectorIterator && iter_p) noexcept
	{
		idx = iter_p.idx;
		iter_p.idx = nullptr;
	}

	VectorIterator & operator ++ (int)  //префиксный ++idx
	{
		++idx;
		return *this;
	}

	VectorIterator & operator ++ ()  //постфиксный idx++
	{
		idx++;
		return *this;
	}

	VectorIterator & operator -- (int)  //префиксный --idx
	{
		--idx;
		return *this;
	}

	VectorIterator & operator -- ()  //постфиксный idx--
	{
		idx--;
		return *this;
	}

	_DataType & operator * ()
	{
		return *idx;
	}

	_DataType * operator -> ()
	{
		return idx;
	}

	VectorIterator & operator = (const VectorIterator & p)
	{
		if (this == &p)
		{
			return *this;
		}
		idx = p.idx;
		return *this;
	}

	VectorIterator operator + (int p)  //idx+int 
	{
		VectorIterator tmp(*this);
		tmp.idx = tmp.idx + p;
		return tmp;
	}

	VectorIterator operator - (int p)  //idx-int
	{
		VectorIterator tmp(*this);
		tmp.idx = tmp.idx - p;
		return tmp;
	}

	int operator - (const VectorIterator & rv)
	{
		int dif = idx - rv.idx;
		return dif;
	}

	bool operator == (VectorIterator const& a)
	{
		if (idx == a.idx) return true;
		else
			return false;
	}

	bool operator != (VectorIterator const& a)
	{
		if (idx != a.idx) return true;
		else
			return false;
	}

	bool operator < (VectorIterator const& a)
	{
		if (idx < a.idx) return true;
		else
			return false;
	}

	/*bool operator <= (VectorIterator const& a)
	{
		if (idx <= a.idx) return true;
		else
			return false;
	}*/

	bool operator > (VectorIterator const& a)
	{
		if (idx > a.idx) return true;
		else
			return false;
	}

	/*bool operator >= (VectorIterator const& a)
	{
		if (idx >= a.idx) return true;
		else
			return false;
	}*/

	VectorIterator & operator += (int p)
	{
		idx = idx + p;
		return *(this);
	}

	VectorIterator & operator -= (int p)
	{
		idx = idx - p;
		return *(this);
	}

	void Show()
	{
		std::cout << idx;
	}

	~VectorIterator()
	{

	}

};

template <class _DataType>
class Vector
{

private:

	_DataType * Arr;
	_DataType * beg;		//указатель на первый элемент
	_DataType * end;		//указатель за последний элемент
	_DataType * last;		//вместимость

public:

	typedef VectorIterator<_DataType> iterator;

	Vector()
	{
		beg = nullptr;
		end = nullptr;
		last = nullptr;
		Arr = nullptr;
	}

	Vector(int len)
	{
		Arr = new _DataType[len];
		beg = Arr;
		end = Arr + len;
		last = Arr + len;
	}

	Vector(int len, _DataType * tmp)
	{
		Arr = new _DataType[len];
		beg = Arr;
		last = Arr + len;
		end = Arr + len;
		for (_DataType *i = beg; i < end; i++)
		{
			Arr[i] = tmp[i];
		}
	}

	template <class _ItType>
	Vector(_ItType beg_p, _ItType end_p)
	{
		Arr = new _DataType[100];
		beg = Arr;
		end = Arr + (end_p - beg_p);
		last = Arr + (end_p - beg_p);
		_DataType * ptr = beg;
		for (; beg_p < end_p; beg_p++)
		{
			*ptr = *beg_p;
			++ptr;
		}

	};

	Vector(const std::initializer_list<_DataType> & List)
	{
		Arr = new _DataType[List.size()];
		beg = Arr;
		end = beg + List.size();
		last = beg + List.size();
		auto tmp_ptr = beg;
		for (auto ptr = List.begin(); ptr < List.end(); ptr++)
		{
			*tmp_ptr = *ptr;
			tmp_ptr++;
		}
	}

	Vector(const Vector & buf)
	{
		Arr = new _DataType[buf.last - buf.beg];
		beg = Arr;
		end = Arr + buf.end - buf.beg;
		last = Arr + buf.last - buf.beg;
		_DataType * ptr_p = buf.beg;
		_DataType * ptr = beg;
		for (; ptr_p < buf.end; ptr_p++)
		{
			*ptr = *ptr_p;
			ptr++;
		}
	}

	Vector(Vector &&buf) noexcept
	{
		Arr = buf.Arr;
		beg = buf.beg;
		end = buf.end;
		last = buf.last;
		buf.Arr = nullptr;
		buf.beg = nullptr;
		buf.end = nullptr;
		buf.last = nullptr;
	}

	_DataType & At(int idx)
	{
		const int size = end - beg;
		if (idx >= size)
		{
			//exception
			return -1;
		}
		else
		{
			return *(beg + idx);
		}
	};

	VectorIterator<_DataType> Begin()
	{
		return VectorIterator<_DataType>(beg);
	};

	VectorIterator<_DataType> End()
	{
		return VectorIterator<_DataType>(end);
	};

	Vector & operator = (Vector & rv)
	{
		int capacity = rv.last - rv.beg;
		Arr = new _DataType[capacity];
		beg = Arr;
		end = Arr + (rv.end - rv.beg);
		last = Arr + capacity;
		VectorIterator<_DataType> iter_beg = rv.Begin();
		VectorIterator<_DataType> iter_end = rv.End();
		VectorIterator<_DataType> iter_to_fill = beg;
		for (; iter_beg < iter_end; iter_beg++)
		{
			*iter_to_fill = *iter_beg;
			iter_to_fill++;
		}
		return *this;
	};

	Vector & PushBack(const _DataType & elem)
	{
		if (last == end)
		{
			int capacity = (last - beg) * 2;
			int size = (end - beg);
			_DataType * tmpArr = new _DataType[end - beg];
			_DataType * ptr_p = beg;
			_DataType * ptr = tmpArr;
			for (; ptr_p < end; ptr_p++)
			{
				*ptr = *ptr_p;
				ptr++;
			}
			delete[] Arr;
			Arr = new _DataType[capacity];
			beg = Arr;
			end = beg + size;
			last = beg + capacity;
			_DataType * tmp_ptr = tmpArr;
			for (_DataType * ptr = beg; ptr < end; ptr++)
			{
				*ptr = *tmp_ptr;
				tmp_ptr++;
			}
			*end = elem;
			end++;
			delete[] tmpArr;
		}
		else
		{
			*end = elem;
			end++;
		}
		return *this;
	};

	Vector & PopBack()
	{
		*end = 0;
		end--;
		return *this;
	}

	VectorIterator<_DataType> Insert(VectorIterator<_DataType> pos, const _DataType & elem)
	{
		VectorIterator<_DataType> beg_iter = beg;
		VectorIterator<_DataType> end_iter = end;
		Vector tmp_before_pos(beg_iter, pos);
		Vector tmp_after_pos(pos, end_iter);
		const int dif = pos - beg_iter;
		tmp_before_pos.PushBack(elem);
		beg_iter = tmp_after_pos.Begin();
		end_iter = tmp_after_pos.End();
		for (; beg_iter < end_iter; beg_iter++)
		{
			tmp_before_pos.PushBack(*beg_iter);
		}
		*this = tmp_before_pos;
		pos = beg + dif;
		return pos;
	};

	template <class _IterType>
	VectorIterator<_DataType> Insert(VectorIterator<_DataType> pos, _IterType & insert_beg, _IterType & insert_end)
	{

		/*VectorIterator<_DataType> beg_iter = beg;
		VectorIterator<_DataType> end_iter = end;
		Vector tmp_before_pos(beg_iter, pos);
		Vector tmp_after_pos(pos, end_iter);
		int dif = pos - beg_iter;
		for (; insert_beg < insert_end; insert_beg++)
		{
			tmp_before_pos.PushBack(*insert_beg);
		}
		beg_iter = tmp_after_pos.Begin();
		end_iter = tmp_after_pos.End();
		for (; beg_iter < end_iter; beg_iter++)
		{
			tmp_before_pos.PushBack(*beg_iter);
		}
		*this = tmp_before_pos;
		pos = beg + dif;
		return pos;*/
		const int dif = pos - beg;
		for (; insert_beg < insert_end; insert_beg++)
		{
			Insert(pos, *insert_beg);
			++pos;
		}
		return (beg + dif);
	};

	VectorIterator<_DataType> Erase(VectorIterator<_DataType> pos)
	{
		VectorIterator<_DataType> beg_iter = beg;
		Vector tmp_before_pos(beg_iter, pos);
		VectorIterator<_DataType> end_iter = end;
		VectorIterator<_DataType> tmp_end_iter = tmp_before_pos.End();
		int dif = pos - beg;
		tmp_before_pos.Insert(tmp_end_iter, pos + 1, end_iter);
		*this = tmp_before_pos;
		pos = beg + dif;
		return pos;
	};

	void Reserve(int num)
	{
		int capacity = num;
		const int size = end - beg;
		_DataType *tmpArr = new _DataType[size];
		for (int i = 0; i < size; i++)
		{
			*(tmpArr + i) = *(Arr + i);
		}
		delete[] Arr;
		Arr = new _DataType[capacity];
		for (int i = 0; i < size; i++)
		{
			*(Arr + i) = *(tmpArr + i);
		}
		delete[] tmpArr;
	}

	void Resize(int new_size)
	{
		if (new_size > (last - beg))
		{
			//Доделать!
		}
		else
		{
			end = beg + new_size;
		}
	}

	bool Empty()
	{
		if (end == beg) return true;
		else return false;
	}

	int Size()
	{
		return end - beg;
	}

	int Capacity()
	{
		return last - beg;
	}

	void Clear()
	{
		for (; end > beg; end--)
		{
			*end = 0;
		}
	}

	void Show()
	{
		for (int i = 0; i < end - beg; i++)
		{
			std::cout << *(Arr + i) << " | ";
		}
		std::cout << std::endl;
	}

	~Vector()
	{
//		delete[] Arr;
	}

};

#endif VECTOR_H