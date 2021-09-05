//
// Created by George Tevosov on 17.08.2021.
//

#ifndef CONT2_REVERSE_ITER_HPP
#define CONT2_REVERSE_ITER_HPP
#include "traits.hpp"

namespace ft {


	template<class Iterator>
	class reverse_iterator {
	private:
		Iterator _it;
	public:
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

		reverse_iterator() : _it() {}

		explicit
		reverse_iterator(iterator_type x) : _it(x) {}

		reverse_iterator(const reverse_iterator &x)
				: _it(x._it) {}

		template<typename Iter>
		reverse_iterator(const reverse_iterator<Iter> &x)
				: _it(x.base()) {}

		~reverse_iterator() {

		};

		iterator_type
		base() const { return _it; }

		reference
		operator*() const {
			Iterator tmp = _it;
			return *--tmp;
		}

		pointer
		operator->() const { return &(operator*()); }

		reverse_iterator &
		operator++() {
			--_it;
			return *this;
		}

		reverse_iterator
		operator++(int) {
			reverse_iterator tmp = *this;
			--_it;
			return tmp;
		}

		reverse_iterator &
		operator--() {
			++_it;
			return *this;
		}

		reverse_iterator
		operator--(int) {
			reverse_iterator tmp = *this;
			++_it;
			return tmp;
		}

		reverse_iterator
		operator+(difference_type n) const { return reverse_iterator(_it - n); }

		reverse_iterator &
		operator+=(difference_type n) {
			_it -= n;
			return *this;
		}

		reverse_iterator
		operator-(difference_type n) const { return reverse_iterator(_it + n); }

		reverse_iterator &
		operator-=(difference_type n) {
			_it += n;
			return *this;
		}

		reference
		operator[](difference_type n) const { return *(*this + n); }

	};

	template<typename It>
	bool
	operator==(const reverse_iterator<It> &x,
			   const reverse_iterator<It> &y) { return x.base() == y.base(); }

	template<typename It>
	bool
	operator<(const reverse_iterator<It> &x,
			  const reverse_iterator<It> &y) { return y.base() < x.base(); }

	template<typename It>
	bool
	operator!=(const reverse_iterator<It> &x,
			   const reverse_iterator<It> &y) { return !(x == y); }

	template<typename It>
	bool
	operator>(const reverse_iterator<It> &x,
			  const reverse_iterator<It> &y) { return y < x; }

	template<typename It>
	bool
	operator<=(const reverse_iterator<It> &x,
			   const reverse_iterator<It> &y) { return !(y < x); }

	template<typename It>
	bool
	operator>=(const reverse_iterator<It> &x,
			   const reverse_iterator<It> &y) { return !(x < y); }

	template<typename It>
	typename reverse_iterator<It>::difference_type
	operator-(const reverse_iterator<It> &x,
			  const reverse_iterator<It> &y) { return y.base() - x.base(); }

	template<typename It>
	reverse_iterator<It>
	operator+(typename reverse_iterator<It>::difference_type n,
			  const reverse_iterator<It> &x) { return reverse_iterator<It>(x.base() - n); }

// Comparison of reverse_iterator to const reverse_iterator.
	template<typename ItL, typename ItR>
	bool
	operator==(const reverse_iterator<ItL> &x,
			   const reverse_iterator<ItR> &y) { return x.base() == y.base(); }

	template<typename ItL, typename ItR>
	bool
	operator<(const reverse_iterator<ItL> &x,
			  const reverse_iterator<ItR> &y) { return y.base() < x.base(); }

	template<typename ItL, typename ItR>
	bool
	operator!=(const reverse_iterator<ItL> &x,
			   const reverse_iterator<ItR> &y) { return !(x == y); }

	template<typename ItL, typename ItR>
	bool
	operator>(const reverse_iterator<ItL> &x,
			  const reverse_iterator<ItR> &y) { return y < x; }

	template<typename ItL, typename ItR>
	bool
	operator<=(const reverse_iterator<ItL> &x,
			   const reverse_iterator<ItR> &y) { return !(y < x); }

	template<typename ItL, typename ItR>
	bool
	operator>=(const reverse_iterator<ItL> &x,
			   const reverse_iterator<ItR> &y) { return !(x < y); }

	template<typename ItL, typename ItR>
	typename reverse_iterator<ItL>::difference_type
	operator-(const reverse_iterator<ItL> &x,
			  const reverse_iterator<ItR> &y) { return y.base() - x.base(); }

};
#endif //CONT2_REVERSE_ITER_HPP
