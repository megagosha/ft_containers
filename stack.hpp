//
// Created by Elayne Debi on 8/24/21.
//

#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft {

	template<class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
	protected:
		container_type c;
	public:
		explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {
		}

		bool empty() const {
			return (c.empty());
		}

		size_type size() const {
			return (c.size());
		}

		value_type &top() {
			return (c.back());
		}

		const value_type &top() const {
			return (c.back());
		}

		void push(const value_type &val) {
			return (this->c.push_back(val));
		}

		void pop() {
			return (c.pop_back());
		}

		template<class T1, class _C1>
		friend
		bool
		operator==(const stack<T1, _C1> &x, const stack<T1, _C1> &y);

		template<class T1, class C1>
		friend
		bool
		operator<(const stack<T1, C1> &x, const stack<T1, C1> &y);

	};

	template<class T, class Container>
	bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
		return (lhs.c == rhs.c);
	}

	template<class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (!(lhs == rhs));
	}

	template<class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (lhs.c < rhs.c);
	}

	template<class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (!(rhs < lhs));
	}

	template<class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (rhs < lhs);

	}

	template<class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (!(lhs < rhs));

	}
};

#endif //CONTAINERS_STACK_HPP
