//
// Created by Elayne Debi on 8/19/21.
//

#ifndef CONTAINERS_ALGO_HPP
#define CONTAINERS_ALGO_HPP
#include "traits.hpp"
namespace ft {

	template<class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1) {
			if (*first1 != *first2)   // or: if (!pred(*first1,*first2)), for version 2
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1,
			   InputIterator2 first2, BinaryPredicate pred) {
		while (first1 != last1) {
			if (!pred(*first1, *first2))   // or: if (!pred(*first1,*first2)), for version 2
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template<class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2,
								 Compare comp) {
		while (first1 != last1) {
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template<class InputIterator, class ForwardIterator>
			ForwardIterator uninitialized_copy(InputIterator first, InputIterator last,
											   ForwardIterator result) {
				typedef typename ForwardIterator::value_type T;
				ForwardIterator cp_res = result;
				try {
					for (; first != last; ++result, ++first)
						new(static_cast<void *>(&*result)) T(*first);
					return result;
				}
				catch (std::exception &e) {
					for (; cp_res != result; ++cp_res) {
						cp_res->~T();
					}
					throw;
				}
			}
}
#endif //CONTAINERS_ALGO_HPP
