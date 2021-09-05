//
// Created by Elayne Debi on 8/19/21.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP

#include "reverse_iter.hpp"
#include "memory"
#include <iostream>
#include "algo.hpp"
#include "stack.hpp"
#include "bt_node.hpp"

namespace ft {

    template<typename Alloc, typename V, typename T>
    class map_iterator {

    public:
        typedef T iterator_type;
        typedef typename std::bidirectional_iterator_tag iterator_category;
        typedef V value_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename ft::iterator_traits<iterator_type>::reference reference;
        typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
    private:
        ft::rbt_node<value_type> *_node;
        ft::rbt_node<value_type> *_null_node;
    public:
        map_iterator() : _node(NULL), _null_node(NULL) {};

        map_iterator(ft::rbt_node<value_type> *n, ft::rbt_node<value_type> *null_n) : _node(n), _null_node(null_n) {};

        map_iterator(const map_iterator &r) : _node(r._node), _null_node(r._null_node) {};

        map_iterator &operator=(const map_iterator &r) {
            if (*this == r)
                return (*this);
            _node = r._node;
            _null_node = r._null_node;
            return (*this);
        };

        template<class U>
        bool operator==(const map_iterator<Alloc, V, U> &rhs) const {
            if (_node == rhs._node)
                return (true);
            return (false);
        }

        map_iterator &operator++() {
            if (_node->right != _null_node) {
                _node = _node->right;
                while (_node->left != _null_node) {
                    _node = _node->left;
                }
                return (*this);
            }

            while (true) {
                //@todo  element after last. Check what needs to be sent here
                if (_node->parent == _null_node) {
                    {
                        _node = _null_node;
                        return (*this);
                    }
                }
                if (_node->parent->left == _node) {
                    _node = _node->parent;
                    return (*this);
                }
                _node = _node->parent;
            }
        }

        map_iterator operator++(int) {
            map_iterator tmp = *this;
            ++(*this);
            return (tmp);
        }

        map_iterator &operator--() {
            if (_node->left != _null_node) {
                _node = _node->left;
                while (_node->right != _null_node) {
                    _node = _node->right;
                }
                return (*this);
            }
            while (true) {
                //@todo  element after last. Check what needs to be sent here
                if (_node->parent == _null_node) {
                    _node = _null_node;
                    return (*this);
                }
                if (_node->parent->right == _node) {
                    _node = _node->parent;
                    return (*this);
                }
                _node = _node->parent;
            }
        }

        map_iterator operator--(int) {
            map_iterator tmp = *this;
            --(*this);
            return (tmp);
        }

        ~map_iterator() {};

        friend
        bool operator==(const map_iterator &x, const map_iterator &y) {
            return (x._node == y._node && x._null_node == y._null_node);
        };

        friend
        bool operator!=(const map_iterator &x, const map_iterator &y) {
            return (x._node != y._node || x._null_node != y._null_node);
        };

        reference operator*() const { return (_node->value); }

        pointer operator->() const { return (&(_node->value)); }

        rbt_node<value_type> *base() const { return (_node); }

        ft::rbt_node<value_type> *null() const { return (_null_node); }
    };

    template<typename Alloc, typename V, typename T, typename B>
    class map_const_iterator {
    private:
        typedef typename ft::map_iterator<Alloc, V, T> iterator;
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef typename Alloc::difference_type difference_type;
        typedef V value_type;
        typedef typename Alloc::const_pointer pointer;
        typedef typename Alloc::const_reference reference;
    private:
        const ft::rbt_node<value_type> *_node;
        const ft::rbt_node<value_type> *_null_node;
    public:
        map_const_iterator() : _node(NULL), _null_node(NULL) {}


        map_const_iterator(const ft::rbt_node<value_type> *node, const ft::rbt_node<value_type> *null_node) : _node(
                node),
                                                                                                              _null_node(
                                                                                                                      null_node) {}

        map_const_iterator(const map_const_iterator &x) : _node(x._node), _null_node(x._null_node) {
        }

        map_const_iterator(const iterator &x) : _node(x.base()), _null_node(x.null()) {}

        map_const_iterator(iterator &x) : _node(x.base()), _null_node(x.null()) {}

        ~map_const_iterator() {};

        map_const_iterator &operator=(const map_const_iterator &x) {
            if (*this == x)
                return (*this);
            _node = x._node;
            _null_node = x._null_node;
            return (*this);
        };


        map_const_iterator &operator=(const iterator &x) {
            if (*this == x)
                return (*this);
            _node = x._node;
            _null_node = x._null_node;
            return (*this);
        };

        bool operator==(const map_const_iterator &rhs) {
            if (_node == rhs._node)
                return (true);
            return (false);
        }

        map_const_iterator &operator++() {
            if (_node->right != _null_node) {
                _node = _node->right;
                while (_node->left != _null_node) {
                    _node = _node->left;
                }
                return (*this);
            }

            while (true) {
                //@todo  element after last. Check what needs to be sent here
                if (_node->parent == _null_node) {
                    {
                        _node = _null_node;
                        return (*this);
                    }
                }
                if (_node->parent->left == _node) {
                    _node = _node->parent;
                    return (*this);
                }
                _node = _node->parent;
            }
        }

        map_const_iterator operator++(int) {
            map_const_iterator tmp = *this;
            ++(*this);
            return (tmp);
        }

        map_const_iterator &operator--() {
            if (_node->left != _null_node) {
                _node = _node->left;
                while (_node->right != _null_node) {
                    _node = _node->right;
                }
                return (*this);
            }
            while (true) {
                //@todo  element after last. Check what needs to be sent here
                if (_node->parent == _null_node) {
                    _node = _null_node;
                    return (*this);
                }
                if (_node->parent->right == _node) {
                    _node = _node->parent;
                    return (*this);
                }
                _node = _node->parent;
            }
        }

        map_const_iterator operator--(int) {
            map_const_iterator tmp = *this;
            --(*this);
            return (tmp);
        }

        friend
        bool operator==(const map_const_iterator &x, const map_const_iterator &y) {
            return (x._node == y._node && x._null_node == y._null_node);
        };

        friend
        bool operator!=(const map_const_iterator &x, const map_const_iterator &y) {
            return (x._node != y._node || x._null_node != y._null_node);
        };

        reference operator*() const { return (_node->value); }

        pointer operator->() const { return (&(_node->value)); }

        rbt_node<value_type> *base() const { return (_node); }

    };

    template<class Key, class T, class Compare = std::less <Key>, class Alloc = std::allocator <ft::pair<const Key, T> > >
    class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::difference_type difference_type;

        typedef ft::map_iterator<Alloc, value_type, pointer> iterator;
        typedef ft::map_const_iterator<Alloc, value_type, pointer, const_pointer> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef size_t size_type;

        class value_compare
                : public std::binary_function<value_type, value_type, bool> {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
            friend class map;

        protected:
            key_compare comp;

            value_compare(key_compare c) : comp(c) {}  // constructed with map's comparison object
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;

            /* comp(0, 1) return true */
            bool operator()(const value_type &x, const value_type &y) const {
                return comp(x.first, y.first);
            }
        };

        //@todo insert operations assume null leaf is node onject (not NULL); implement accordingly
    private:

        typedef typename Alloc::template rebind<ft::rbt_node<value_type> >::other node_allocator;
        typedef ft::rbt_node<value_type> rb_node;

        rb_node *_root;
        rb_node *_null_node;
        node_allocator _alloc;
        Alloc _val_alloc;
        size_type _size;
        value_compare _comp;

        rb_node *_allocate_node(value_type const &val) {
            rb_node *node = _alloc.allocate(1);
            _alloc.construct(node);
            _val_alloc.construct(&node->value, val);
            return (node);
        }

        rb_node *_create_node(const value_type &val) {
            rb_node *node = _allocate_node(val);
            node->red = true;
            node->left = _null_node;
            node->right = _null_node;
            return (node);
        }

        void _init_map() {
            _null_node = _create_null_node();
            _root = _null_node;
        }

        rb_node *_create_null_node() {
            rb_node *res = _allocate_node(value_type());
            res->red = false;
            res->left = res;
            res->right = res;
            res->parent = res;
            return (res);
        }

        void _delete_node(rb_node *ptr) {
//            _val_alloc.destroy(&ptr->value);
            _alloc.destroy(ptr);
            _alloc.deallocate(ptr, 1);
        }

/* comp (1, 0) returns false  comp(1, 0) returns true */
        rb_node *_find_node_to_insert(const value_type &val, iterator hint) const {
            rb_node *node = _root;
            iterator tmp(hint);

            if (hint.base() != NULL && hint.base() != _null_node && _comp(*hint, val) && _comp(val, *(tmp++)))
                node = hint.base();
            while (node != _null_node) {
                if (_comp(node->value, val)) {
                    if (node->right == _null_node)
                        return (node);
                    node = node->right;
                } else {
                    if (!_comp(val, node->value)) // identical keys if comp(1, 2) == false && comp(2, 1) == false;
                        return (node);
                    if (node->left == _null_node) {
                        return (node);
                    }
                    node = node->left;
                }
            }
            return (NULL);
        }

        rb_node *_find_node_to_delete(const key_type &k) const {
            mapped_type b;
            key_type c = k;

            rb_node *node = _find_node_to_insert(ft::make_pair(c, b),
                                                 iterator(_null_node, _null_node));

            return (node);
        }

        rb_node *_grandparent(rb_node *n) {
            if (n != NULL && n->parent != NULL)
                return (n->parent->parent);
            else
                return (NULL);
        }

        rb_node *_uncle(rb_node *n) {
            rb_node *g = _grandparent(n);
            if (g == NULL)
                return (NULL); // No _grandparent means no _uncle
            if (n->parent == g->left)
                return g->right;
            else
                return g->left;
        }

        rb_node *_sibling(rb_node *n) {
            if (n == n->parent->left)
                return (n->parent->right);
            else
                return (n->parent->left);
        }

        void
        _replace_node(rb_node *n, rb_node *child) {
            child->parent = n->parent;
            if (n == n->parent->left)
                n->parent->left = child;
            else
                n->parent->right = child;
        }

        bool _is_leaf(rb_node *nb) {
            if (nb == _null_node)
                return (true);
            return (false);
        }

        void _delete_one_child(rb_node *nb) {
            rb_node *child = _is_leaf(nb->right) ? nb->left : nb->right;

            if (_null_node->right == nb) {
                iterator tmp(_null_node->right, _null_node);
                ++tmp;
                _null_node->right = tmp.base();
            }
            if (_null_node->left == nb) {
                iterator tmp(_null_node->left, _null_node);
                --tmp;
                _null_node->left = tmp.base();
            }
            _replace_node(nb, child);
            if (nb->red == false) {
                if (child->red == true)
                    child->red = false;
                else
                    _delete_case1(child);
            }
            if (nb == _root)
                _root = child;
            _delete_node(nb);
        }

        void _delete_case1(rb_node *nb) {
            if (nb->parent != _null_node) {
                _delete_case2(nb);
            }
        }

        void _delete_case2(rb_node *nb) {
            rb_node *sib = _sibling(nb);

            if (sib->red == true) {
                nb->parent->red = true;
                sib->red = false;
                if (nb == nb->parent->left)
                    _left_rotate(nb->parent);
                else
                    _right_rotate(nb->parent);
            }
            _delete_case3(nb);
        }

        void _delete_case3(rb_node *nb) {
            rb_node *sib = _sibling(nb);

            if ((nb->parent->red == false) &&
                (sib->red == false) &&
                (sib->left->red == false) &&
                (sib->right->red == false)) {
                sib->red = true;
                _delete_case1(nb->parent);
            } else
                _delete_case4(nb);
        }

        void _delete_case4(rb_node *nb) {
            rb_node *s = _sibling(nb);

            if ((nb->parent->red == true) &&
                (s->red == false) &&
                (s->left->red == false) &&
                (s->right->red == false)) {
                s->red = true;
                nb->parent->red = false;
            } else
                _delete_case5(nb);
        }

        void _delete_case5(rb_node *nb) {
            rb_node *sib = _sibling(nb);

            if (sib->red == false) {
                if ((nb == nb->parent->left) &&
                    (sib->right->red == false) &&
                    (sib->left->red == true)) { /* this last test is trivial too due to cases 2-4. */
                    sib->red = true;
                    sib->left->red = false;
                    _right_rotate(sib);
                } else if ((nb == nb->parent->right) &&
                           (sib->left->red == false) &&
                           (sib->right->red == true)) {/* this last test is trivial too due to cases 2-4. */
                    sib->red = true;
                    sib->right->red = false;
                    _left_rotate(sib);
                }
            }
            _delete_case6(nb);
        }

        void _delete_case6(rb_node *nb) {
            rb_node *sib = _sibling(nb);

            sib->red = nb->parent->red;
            nb->parent->red = false;

            if (nb == nb->parent->left) {
                sib->right->red = false;
                _left_rotate(nb->parent);
            } else {
                sib->left->red = false;
                _right_rotate(nb->parent);
            }
        }

        void _insert_case1(rb_node *new_node) {
            if (new_node->parent == _null_node) {
                new_node->red = false;
                _root = new_node;
                return;
            } else
                _insert_case2(new_node);
        }

        void _insert_case2(rb_node *node) {
            if (node->parent->red == false)
                return;
            else
                _insert_case3(node);
        }

        void _insert_case3(rb_node *new_node) {
            rb_node *u = _uncle(new_node);
            rb_node *g;
            if (u != NULL && u != _null_node && u->red == true) {
                new_node->parent->red = false;
                u->red = false;
                g = _grandparent(new_node);
                g->red = true;
                _insert_case1(g);
            } else
                _insert_case4(new_node);
        }

        void _left_rotate(rb_node *node) {
            rb_node *pv = node->right;

            pv->parent = node->parent;

            if (node->parent != _null_node) {
                if (node->parent->left == node)
                    node->parent->left = pv;
                else
                    node->parent->right = pv;
            } else
                _root = pv;
            node->right = pv->left;
            if (pv->left != _null_node)
                pv->left->parent = node;
            node->parent = pv;
            pv->left = node;
//			if (pv->parent == _null_node)
//				_root = pv;
        }

        void _right_rotate(rb_node *node) {
            rb_node *pv = node->left;

            pv->parent = node->parent; /* при этом, возможно, pivot становится корнем дерева */

            if (node->parent != _null_node) {
                if (node->parent->left == node)
                    node->parent->left = pv;
                else
                    node->parent->right = pv;
            } else
                _root = pv;
            node->left = pv->right;
            if (pv->right != _null_node)
                pv->right->parent = node;
            node->parent = pv;
            pv->right = node;
        }

        void _insert_case4(rb_node *node) {
            rb_node *g = _grandparent(node);

            if (node == node->parent->right && node->parent == g->left) {
                _left_rotate(node->parent);
                node = node->left;
            } else if (node == node->parent->left && node->parent == g->right) {
                _right_rotate(node->parent);
                node = node->right;
            }
            _insert_case5(node);
        }

        void _insert_case5(rb_node *node) {
            rb_node *g = _grandparent(node);

            node->parent->red = false;
            g->red = true;
            if (node == node->parent->left && node->parent == g->left)
                _right_rotate(g);
            else
                _left_rotate(g);
        }

        void _rebalance(rb_node *new_node) {
            _insert_case1(new_node);
        }

        pair<iterator, bool> _insert(const value_type &val, iterator hint = iterator()) {
            rb_node *res = _find_node_to_insert(val, hint);
            ft::pair<iterator, bool> ret;

            //if key found update val
            if (res != NULL && res != _null_node && res->value.first == val.first) {
//                res->value.second = val.second;
                ret.first = iterator(res, _null_node);
                ret.second = false;
                return (ret);
            }
            rb_node *new_node = _create_node(val);
            if (res == NULL) {
                _root = new_node;
                _root->parent = _null_node;
                _root->red = false;
                _null_node->right = _root;
                _null_node->left = _root;
            } else if (_comp(res->value, val)) {
                if (_null_node->left == res)
                    _null_node->left = new_node;
                res->right = new_node;
                new_node->parent = res;
            } else {
                if (_null_node->right == res)
                    _null_node->right = new_node;
                res->left = new_node;
                new_node->parent = res;
            }
            ++_size;
            _rebalance(new_node);
            ret.first = iterator(new_node, _null_node);
            ret.second = true;
            return (ret);
        }

        rbt_node<value_type> *_replace_with_new_node(rbt_node<value_type> *orig, const value_type &val) {
            rbt_node<value_type> *new_node = _create_node(val);

            new_node->red = orig->red;
            new_node->parent = orig->parent;
            if (orig->parent->left == orig)
                orig->parent->left = new_node;
            else
                orig->parent->right = new_node;
            new_node->right = orig->right;
            new_node->left = orig->left;
            if (new_node->left != _null_node)
                new_node->left->parent = new_node;
            if (new_node->right != _null_node)
                new_node->right->parent = new_node;
            if (_root == orig)
                _root = new_node;
            return (new_node);
        }

    public:
        map(const key_compare &com = key_compare(),
            const allocator_type &alloc = allocator_type()) : _alloc(alloc),
                                                              _size(0), _comp(com) {
            _init_map();
        };

        template<class InputIterator>
        map(InputIterator
            first, InputIterator
            last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : _alloc(alloc),
                                                              _size(0), _comp(comp) {
            _init_map();
            for (InputIterator it = first; it != last; ++it) {
                insert(*it);
            }
        };

        map(const map &x) : _size(0), _comp(x._comp) {
            _init_map();
            _comp = x._comp;
            _size = 0;
            for (const_iterator it = x.begin(); it != x.end(); ++it) {
                insert(*it);
            }
            _size = x.size();
        };

        ~map() {
            clear();
            _delete_node(_null_node);
        };

        map &operator=(const map &x) {
            if (this == &x)
                return (*this);
            clear();
            insert(x.begin(), x.end());
            return (*this);
        };


        rb_node *find_min(rb_node *val) const {
            rb_node *res = val;
            while (res->left != _null_node)
                res = res->left;
            return (res);
        }

        rb_node *find_max(rb_node *val) const {
            rb_node *res = val;
            while (res->right != _null_node)
                res = res->right;
            return (res);
        }

        iterator begin() {
            rb_node *res = find_min(_root);
            return (iterator(res, _null_node));
        };

        const_iterator begin() const {
            return (const_iterator(find_min(_root), _null_node));
        };

        iterator end() {
            return (iterator(_null_node, _null_node));
        };

        const_iterator end() const {
            return (const_iterator(_null_node, _null_node));
        };

        reverse_iterator rbegin() {
            return (reverse_iterator(end()));
        };

        const_reverse_iterator rbegin() const {
            return (const_reverse_iterator(end()));
        };

        reverse_iterator rend() { return (reverse_iterator(begin())); };

        const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); };

        bool empty() const {
            return (_size == 0);
        };

        size_type size() const { return _size; };

        //@todo copy from vec
        size_type max_size() const { return _alloc.max_size(); };

        mapped_type &operator[](const key_type &k) {
            return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
        };

        pair<iterator, bool> insert(const value_type &val) {
            return (_insert(val));
        };

        iterator insert(iterator hint, const value_type &val) {
            return (_insert(val, hint).first);
        };

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last) {
            for (; first != last; ++first) {
                insert(*first);
            }
        };

        void erase(iterator position) {
            rbt_node<value_type> *node = position.base();
            if (node->left != _null_node && node->right != _null_node) {
                rbt_node<value_type> *node_max_left = node->left;
                //find max node in left sub-tree
                while (node_max_left->right != _null_node)
                    node_max_left = node_max_left->right;
                //replace current node value with max node from left sub-tree
                _replace_with_new_node(node, node_max_left->value);
                _delete_node(node);
                _delete_one_child(node_max_left);
            } else
                _delete_one_child(position.base());
            --_size;
        };

        size_type erase(const key_type &k) {
            iterator it = find(k);

            if (it == end())
                return (0);
            else
                erase(it);
            return (1);
        };

        //@todo FIX ROOT VAL

        void erase(iterator first, iterator last) {
            iterator tmp = first;

            while (first != last) {
                tmp = first++;
                erase(tmp);
            }
        };

        void swap(map &x) {
            rb_node *tmp_root = x._root;
            rb_node *tmp_null_node = x._null_node;
            size_type tmp_sz = x._size;

            x._root = _root;
            x._null_node = _null_node;
            x._size = _size;

            _root = tmp_root;
            _null_node = tmp_null_node;
            _size = tmp_sz;
        };

        void clear() {
            erase(begin(), end());
        };

        key_compare key_comp() const {
            return (_comp.comp);
        };

        value_compare value_comp() const {
            return (_comp);
        };

        iterator find(const key_type &k) {
            rb_node *node = _find_node_to_delete(k);

            if (node != _null_node && node->value.first == k)
                return (iterator(node, _null_node));
            else
                return (end());
        };

        const_iterator find(const key_type &k) const {
            rb_node *node = _find_node_to_delete(k);

            if (node != _null_node && node->value.first == k)
                return (const_iterator(node, _null_node));
            else
                return (end());
        };

        size_type count(const key_type &k) const {
            if (find(k) != end())
                return (1);
            return (0);
        };

        iterator lower_bound(const key_type &k) {
            iterator it = begin();
            for (; it != end(); ++it) {
                if (!_comp.comp((*it).first, k))
                    break;
            }
            return (it);
        };

        const_iterator lower_bound(const key_type &k) const {
            const_iterator it = begin();
            for (; it != end(); ++it) {
                if (!_comp.comp((*it).first, k))
                    break;
            }
            return (it);
        };

        iterator upper_bound(const key_type &k) {
            iterator it = begin();
            for (; it != end(); ++it) {
                if (_comp.comp(k, (*it).first))
                    break;
            }
            return (it);
        };

        const_iterator upper_bound(const key_type &k) const {
            const_iterator it = begin();
            for (; it != end(); ++it) {
                if (_comp.comp(k, (*it).first))
                    break;
            }
            return (it);
        };

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
            return (ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
        };

        pair<iterator, iterator> equal_range(const key_type &k) {

            return (ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
        };

        allocator_type get_allocator() const {
            return (_alloc);
        };
    };

    template<class Key, class T, class Compare, class Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs) {
        if (lhs.size() != rhs.size())
            return (false);
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs) {
        return (!(lhs == rhs));
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs) {
        return (!(rhs < lhs));
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs) {
        return (rhs < lhs);
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs) {
        return (!(lhs < rhs));
    }

    template<class Key, class T, class Compare, class Alloc>
    void swap(ft::map<Key, T, Compare, Alloc> &lhs,
              ft::map<Key, T, Compare, Alloc> &rhs) {
        lhs.swap(rhs);
    }
}
#endif //CONTAINERS_MAP_HPP
