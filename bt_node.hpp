//
// Created by Elayne Debi on 8/24/21.
//

#ifndef CONTAINERS_BT_NODE_HPP
#define CONTAINERS_BT_NODE_HPP

#include <cstddef>
# include <typeinfo>

namespace ft {

    template<class T1, class T2>
    struct pair {
    public:
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair() : first(T1()), second(T2()) {};

        ~pair() {};

        template<class C1, class C2>
        pair(const pair<C1, C2> &pr) : first(pr.first), second(pr.second) {};

        pair(const first_type &a, const second_type &b) : first(a), second(b) {};

        pair &operator=(const pair &pr) {
            if (*this == pr)
                return (*this);
            first = pr.first;
            second = pr.second;
            return (*this);
        }
    };

    template<class T1, class T2>
    pair<T1, T2> make_pair(const T1 x, const T2 y) {
        return (pair<T1, T2>(x, y));
    };

    template<class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs == rhs); }

    template<class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template<class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(rhs < lhs); };

    template<class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return rhs < lhs; };

    template<class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs < rhs); };

    template<typename value_type>
    struct rbt_node {
    public:
        value_type value;
        rbt_node *parent;
        rbt_node *left;
        rbt_node *right;
        bool red;

        rbt_node() : value(value_type()), parent(nullptr), left(nullptr), right(nullptr), red(true) {};

        rbt_node(const value_type &val, rbt_node *p = nullptr, rbt_node *l = nullptr, rbt_node *r = nullptr) :
                value(val), parent(p), left(l), right(r), red(true) {
        };

        rbt_node &operator=(const rbt_node &node)
        {
            if (*this == node)
                return (*this);
            parent = node.parent;
            left = node.left;
            right = node.right;
            red = node.red;
            return (*this);
        }

        rbt_node(const rbt_node &nd) : value(nd.value), parent(nd.parent), left(nd.left), right(nd.right),
                                       red(nd.red) {};

        ~rbt_node() {};

    };
};
#endif //CONTAINERS_BT_NODE_HPP
