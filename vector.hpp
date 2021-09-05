//
// Created by Elayne Debi on 7/21/21.
// https://github.com/thefullarcticfox/ft_containers/blob/master/adapted_traits.hpp

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include "reverse_iter.hpp"
#include "algo.hpp"

namespace ft {

	/* RandomAccessIterator for vector */

	template<typename T, typename Container>
	class vector_iterator {
	public:
		typedef T iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename ft::iterator_traits<iterator_type>::reference reference;
		typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
	private:
		iterator_type _i;
	public:
		vector_iterator() : _i(T()) {}

		explicit
		vector_iterator(const T &val) : _i(val) {}

		// Allow iterator to const_iterator conversion
		template<typename Iter>
		vector_iterator(const vector_iterator<Iter,
				typename ft::enable_if<
						(ft::is_same<Iter, typename Container::pointer>::value),
						Container>::type> &val)
				: _i(val.base()) {}

		reference operator*() const {
			return *_i;
		}

		pointer operator->() const {

			return (pointer) std::addressof(*_i);
		}

		vector_iterator &operator--() {

			--_i;
			return *this;
		}

		vector_iterator operator--(int) {
			vector_iterator _tmp(*this);
			--(*this);
			return _tmp;
		}

		vector_iterator &
		operator+=(difference_type _n) {

			_i += _n;
			return *this;
		}

		vector_iterator
		operator-(difference_type _n) const { return *this + (-_n); }


		reference
		operator[](difference_type _n) const {

			return _i[_n];
		}

		iterator_type
		base() const { return _i; }


		vector_iterator &operator=(const vector_iterator &x) {
			if (this == &x)
				return (*this);
			this->_i = x._i;
			return (*this);
		};

		friend bool operator==(const vector_iterator &x, const vector_iterator &y) {
			return (x._i == y._i);
		};


		friend bool operator!=(const vector_iterator &x, const vector_iterator &y) {
			return (x._i != y._i);
		};

		vector_iterator operator++(int) {
			vector_iterator _tmp(*this);
			++(*this);
			return _tmp;
		}

		vector_iterator &operator++() {
			++_i;
			return *this;
		}

		vector_iterator operator+(difference_type _n) const {
			vector_iterator _w(*this);
			_w += _n;
			return _w;
		}


		vector_iterator operator-(difference_type val) {
			return (vector_iterator(_i - val));
		};

		friend difference_type operator-(const vector_iterator &a, const vector_iterator &b) {
			return (a._i - b._i);
		}


		vector_iterator &operator-=(difference_type val) {
			_i -= val;
			return (*this);
		}

		reference operator*() {
			return (*_i);
		}

		friend bool operator>(const vector_iterator &lhs, const vector_iterator &rhs) {
			return (lhs._i > rhs._i);
		}

		friend bool operator<(const vector_iterator &lhs, const vector_iterator &rhs) {
			return (lhs._i < rhs._i);
		}

		friend bool operator>=(const vector_iterator &lhs, const vector_iterator &rhs) {
			return (lhs._i >= rhs._i);
		}

		friend bool operator<=(const vector_iterator &lhs, const vector_iterator &rhs) {
			return (lhs._i <= rhs._i);
		}

		friend vector_iterator operator+(difference_type n, const vector_iterator &x) {
			return (x + n);
		}

	};

	template<typename ItL, typename ItR, typename Container>
	typename vector_iterator<ItL, Container>::difference_type
	operator-(const vector_iterator<ItL, Container> &lhs,
			  const vector_iterator<ItR, Container> &rhs) { return lhs.base() - rhs.base(); }

	template<typename It, typename Container>
	typename vector_iterator<It, Container>::difference_type
	operator-(const vector_iterator<It, Container> &lhs,
			  const vector_iterator<It, Container> &rhs) { return lhs.base() - rhs.base(); }

	template<typename It, typename Container>
	vector_iterator<It, Container>
	operator+(typename vector_iterator<It, Container>::difference_type
			  n, const vector_iterator<It, Container> &i) {
		return vector_iterator<It, Container>(i.base() + n);
	}

	template<typename T, typename Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;

		typedef typename ft::vector_iterator<pointer, vector> iterator;
		typedef typename ft::vector_iterator<const_pointer, vector> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		allocator_type _alloc;
		pointer _arr;
		size_type _size;
		size_type _cap;

		void _choose_constructor(size_type n, const value_type val,
								const allocator_type &alloc,
								ft::is_int) {
			_size = n;
			_cap = n * 2;
			_alloc = alloc;
			_arr = _alloc.allocate(_cap);
			size_type i = 0;
			try {
				for (; i < n; ++i) {
					_alloc.construct(this->_arr + i, val);
				}
			}
			catch (std::exception &e) {
				for (; i > 0; --i) {
					_alloc.destroy(_arr + i);
				}
				_alloc.destroy(_arr);
				_alloc.deallocate(_arr, _cap);
				std::cout << "Error: vector: In object constructor " << e.what() << std::endl;
				throw;
			}
		}

		template<class InputIterator>
		void _choose_constructor(InputIterator first, InputIterator last,
								const allocator_type &alloc,
								ft::not_int) {
			_alloc = alloc;
			_size = 0;
			_cap = 0;
			size_type i = 0;
			InputIterator start = first;
			try {
				for (; start != last; ++start) {
					push_back(*start);
					i++;
				}
			}
			catch (std::exception &e) {
				for (; i > 0; --i) {
					_alloc.destroy(_arr + i);
				}
				_alloc.destroy(_arr);
				_alloc.deallocate(_arr, _cap);
				std::cout << "Error: vector: in object constructor " << e.what() << std::endl;
				throw;
			}
		}

		template<class InputIterator>
		void _choose_assign(InputIterator first, InputIterator last, ft::not_int) {
			clear();
			if (first == last)
				return;
			for (InputIterator it = first; it != last; ++it) {
				push_back(*it);
			}
		}

		void _choose_assign(size_type i, const T &val, ft::is_int) {
			clear();
			size_type n = static_cast<size_type>(i);
			if (n > _cap)
				reserve(n * 2);

			for (size_type i = 0; i < (n); ++i) {
				_alloc.construct(_arr + i, val);
			}
			_size = n;
		}

		template<class InputIterator>
		void _choose_insert(iterator position, InputIterator first, InputIterator last, ft::not_int) {
			size_type i = 0;

			for (iterator it = begin(); it != position; ++it)
				i++;
			for (; first != last; ++first) {
				insert(begin() + i, *first);
				i++;
			}
		}

		void _choose_insert(iterator position, size_type n, const value_type val, ft::is_int) {
			difference_type i = position - begin();
			if (_cap <= _size + n)
				reserve(std::max(_cap * 2, _size + n));
			for (size_type k = i; k < _size; ++k)
				_alloc.construct(_arr + k + n, *(_arr + k));
			for (size_type k = i; k < i + n; ++k)
				_alloc.construct(_arr + k, val);
			_size += n;
		}

	public:
		/* empty constructor */
		vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _cap(0) {

		};


		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) {
			_choose_constructor(n, val, alloc, ft::is_int());
		}

		/* range constructor */
		template<class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) {
			_choose_constructor(first, last, alloc, ft::type_is_int<InputIterator>());
		};

		/* @todo copy constructor */
		vector(const vector &x) : _alloc(x._alloc), _size(x._size), _cap(x._cap) {
			size_type i = 0;
			_arr = _alloc.allocate(_cap);
			try {
				for (; i < _size; ++i) {
					_alloc.construct(_arr + i, *(x._arr + i));
				}
			}
			catch (std::exception &e) {
				for (; i > 0; --i) {
					_alloc.destroy(_arr + i);
				}
				_alloc.destroy(_arr);
				_alloc.deallocate(_arr, _cap);
				std::cout << "Error: vector: in object constructor: " << e.what() << std::endl;
				throw;
			}
		};

		~vector() {
			clear();
			if (_cap > 0)
				_alloc.deallocate(_arr, _cap);
		};

		/*
		 * @todo strong exception guarantee
		 * ? if count > size fills from copy constructor. Explore behaviour in tests.
		 * */
		void resize(size_type count, value_type value = value_type()) {
			if (count > _cap)
				reserve(count);
			if (count < _size) {
				erase(end() - (_size - count), end());
			} else {
				size_type i = _size;
				try {
					for (; i < count; ++i) {
						_alloc.construct(_arr + i, value);
					}
				}
				catch (std::exception &e) {
					for (; i >= _size; --i) {
						_alloc.destroy(_arr + i);
					}
					std::cout << "Error: resize()" << std::endl;
					throw;
				}
			}
			_size = count;
		}

		/* exception safety */
		void reserve(size_type new_cap) {
			if (new_cap > this->max_size())
				throw std::length_error("Vector::max_size exceeded");
			if (this->_cap >= new_cap)
				return;
			//@todo rewrite std::uninitialized_copy
			pointer new_arr = _alloc.allocate(new_cap);
			try {
				ft::uninitialized_copy(begin(), end(), vector_iterator<pointer, vector>(new_arr));
			}
			catch (std::exception &e) {
				_alloc.deallocate(new_arr, new_cap);
				throw;
			}
			for (size_type i = 0; i < _size; ++i) {
				_alloc.destroy(_arr + i);
			}
			if (_size != 0)
				_alloc.destroy(_arr);
			if (_cap != 0)
				_alloc.deallocate(_arr, _cap);
			this->_arr = new_arr;
			this->_cap = new_cap;
		};

		//@todo add copying
		// should use propagate_on_container_copy_assignment since C++ 11
		vector &operator=(const vector &x) {
			if (this == &x)
				return (*this);
			clear();
			if (x.size() > _cap)
				reserve(x.size() * 2);
			for (const_iterator it = x.begin(); it != x.end(); ++it) {
				push_back(*it);
			}
			return (*this);
		}

		reference operator[](size_type pos) {
			return (this->_arr[pos]);
		}

		const_reference operator[](size_type pos) const {
			return (this->_arr[pos]);
		}

		reference at(size_type pos) {
			if (pos >= this->_size)
				throw std::out_of_range("Out of range pos");
			return (this->_arr[pos]);
		}

		const_reference at(size_type pos) const {
			if (pos >= this->_size)
				throw std::out_of_range("Out of range pos");
			return (this->_arr[pos]);
		}

		iterator begin() {
			return (iterator(_arr));
		}

		const_iterator begin() const {
			return (const_iterator(_arr));
		}

		iterator end() {
			return (iterator(_arr + _size));
		}

		const_iterator end() const {
			return (const_iterator(_arr + _size));
		}

		reverse_iterator rbegin() {
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend() {
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const {
			return (const_reverse_iterator(begin()));
		}


		template<class InputIterator>
		void assign(InputIterator first, InputIterator last) {
			_choose_assign(first, last, ft::type_is_int<InputIterator>());
		}

		void
		assign(size_type n, const T &val) {
			_choose_assign(n, val, ft::is_int());
		}

		reference front() {
			return (_arr[0]);
		}

		const_reference front() const {
			return (_arr[0]);
		}

		reference back() {
			return (_arr[_size - 1]);
		};

		const_reference back() const {
			return (_arr[_size - 1]);
		};

		bool empty() const {
			return (_size == 0);
		}

		size_type size() const {
			return (_size);
		}

		size_type max_size() const {
			return (std::numeric_limits<size_type>::max() / sizeof(value_type));
		}

		size_t capacity() const {
			return (_cap);
		}

		void clear() {
			for (size_type i = 0; i < _size; ++i) {
				_alloc.destroy(_arr + i);
			}
			_size = 0;
		}

		iterator insert(iterator position, const value_type &val) {
			difference_type pos = position - begin();
			if (_size == _cap)
				reserve((_cap + 1) * 2);
			size_type i = _size;
			for (; i > static_cast<size_type>(pos); --i)
				_alloc.construct(_arr + i, *(_arr + i - 1));
			_alloc.construct(_arr + i, val);
			_size++;
			return (begin() + i);
		}

		void insert(iterator position, size_type n, const value_type &val) {
			_choose_insert(position, n, val, ft::is_int());
		}

		/*
		 * *  Move elements from current position to new position
		 */

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last) {
			_choose_insert(position, first, last, ft::type_is_int<InputIterator>());
		};


		/* basic exception safety  */
		iterator erase(iterator position) {
			if (position == (this->end() - 1)) {
				--_size;
				_alloc.destroy(_arr + _size);
				return (end());
			}
			iterator it = position;
			for (; it != end(); ++it) {
				*it = *(it + 1);
			}
			--_size;
			_alloc.destroy(_arr + _size);
			return (position);
		};

		/* Copy all new elements to new array */
		iterator erase(iterator first, iterator last) {
			iterator begin = this->begin();
			if (last - first <= 0)
				return (vector_iterator<pointer, vector>(_arr + (begin - last)));
			difference_type res = last - first;
			for (iterator it = first; it != end() - res; ++it) {
				*it = *(it + res);
			}
			for (size_type i = _size; i > _size - res; --i) {
				_alloc.destroy(_arr + i);
			}
			_size -= last - first;
			return (first);
		};

		void push_back(const value_type &val) {
			if (_cap == _size)
				reserve((_size + 1) * 2);
			_alloc.construct(_arr + _size, val);
			++_size;
		};

		void pop_back() {
			_alloc.destroy(_arr + _size - 1);
			--_size;
		}

		void swap(vector &x) {
			pointer arr = x._arr;
			size_type size = x._size;
			size_type cap = x._cap;

			x._cap = _cap;
			x._size = _size;
			x._arr = _arr;

			_arr = arr;
			_cap = cap;
			_size = size;
		}


		allocator_type get_allocator() const {
			return (_alloc);
		}

	};

	template<class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
		x.swap(y);
	};


	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return !(lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return !(rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return (rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return !(lhs < rhs);
	}
}
#endif //CONTAINERS_VECTOR_HPP
