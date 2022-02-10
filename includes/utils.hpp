/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:37:03 by lbenedar          #+#    #+#             */
/*   Updated: 2022/02/07 18:12:46 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> {typedef T type;};

    template<class T, T v>
    struct integral_constant
    {
        typedef T value_type;

        static const value_type value = v;
    };

    typedef struct integral_constant<bool, true> true_type;
    typedef struct integral_constant<bool, false> false_type;

    template<class T>
    struct is_integral_base : public false_type {};
    
    template<class T>
    struct is_integral_base<const T> : public is_integral_base<T> {};
    template<class T>
    struct is_integral_base<volatile const T> : public is_integral_base<T> {};
    template<class T>
    struct is_integral_base<volatile T> : public is_integral_base<T> {};

    template<> struct is_integral_base<unsigned char> : public true_type {};
    template<> struct is_integral_base<unsigned short> : public true_type {};
    template<> struct is_integral_base<unsigned int> : public true_type {};
    template<> struct is_integral_base<unsigned long> : public true_type {};
    
    template<> struct is_integral_base<signed char> : public true_type {};
    template<> struct is_integral_base<short> : public true_type {};
    template<> struct is_integral_base<int> : public true_type {};
    template<> struct is_integral_base<long> : public true_type {};

    template<> struct is_integral_base<char> : public true_type {};
    template<> struct is_integral_base<bool> : public true_type {};

    template<class T>
    struct is_integral : public is_integral_base<T> {};

    template <class Key, class Compare, class Alloc>
    class set;

    template<class T>
    struct is_set : public false_type {};

    template <class Key, class Compare, class Alloc>
    struct is_set<ft::set<Key, Compare, Alloc> > : public true_type {};
    


    template <class Iter>
    struct iterator_traits
    {
        typedef typename Iter::difference_type       difference_type;
        typedef typename Iter::value_type            value_type;
        typedef typename Iter::pointer               pointer;
        typedef typename Iter::reference             reference;
        typedef typename Iter::iterator_category     iterator_category;
    };
    
    struct random_access_iterator_tag {};
    struct bidirectional_iterator_tag {};

    template<class T, class Compare>
    class value_compare
    {
    private:
        typedef T           value_type;
        typedef Compare     key_compare;
    public:
        typedef bool        result_type;
        typedef value_type  first_argument_type;
        typedef value_type  second_argument_type;
                     
        value_compare(key_compare c) : comp(c) {};
        value_compare(const value_compare& other) : comp(other.comp) {};
        bool    operator()(const value_type& x, const value_type& y) const {return comp(x.first, y.first);}
    protected:
        key_compare comp;
    };

};

#endif