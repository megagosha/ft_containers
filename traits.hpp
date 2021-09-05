//
// Created by Elayne Debi on 8/19/21.
//

#ifndef CONTAINERS_TRAITS_HPP
#define CONTAINERS_TRAITS_HPP

#include <type_traits>
#include <iterator>

namespace ft {

    struct not_int {
    };
    struct is_int {
    };

    template<class T>
    struct type_is_int : public not_int {
    };

    template<>
    struct type_is_int<int> : public is_int {
    };

//    template<>
//    struct type_is_int<unsigned int> : public is_int {
//    };
//
//    template<>
//    struct type_is_int<unsigned long> : public is_int {
//    };
//    template<>
//    struct type_is_int<long> : public is_int {
//    };
//    template<>
//    struct type_is_int<float> : public is_int {
//    };

    template<bool B, class T = void>
    struct enable_if {
    };

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };


    template<class T, class U>
    struct is_same : std::false_type {
    };

    template<class T>
    struct is_same<T, T> : std::true_type {
    };

    /*Traits  */
    template<class Iterator>
    struct iterator_traits {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template<class T>
    struct iterator_traits<T *> {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template<class T>
    struct iterator_traits<const T *> {

        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    };
}
#endif //CONTAINERS_TRAITS_HPP
