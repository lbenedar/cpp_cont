/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:16:11 by lbenedar          #+#    #+#             */
/*   Updated: 2022/02/06 18:21:27 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1  first_type;
        typedef T2  second_type;

        pair();
        template<class U, class V>
        pair(const pair<U,V>&);
        pair(const first_type&, const second_type&);

        pair&   operator=(const pair&);

        first_type  first;
        second_type second;
    };

    template <class T1, class T2>
    pair<T1, T2>    make_pair(T1 x, T2 y);

    template <class T1, class T2>
    bool    operator==(const pair<T1, T2>&, const pair<T1, T2>&);
    template <class T1, class T2>
    bool    operator!=(const pair<T1, T2>&, const pair<T1, T2>&);
    template <class T1, class T2>
    bool    operator<(const pair<T1, T2>&, const pair<T1, T2>&);
    template <class T1, class T2>
    bool    operator<=(const pair<T1, T2>&, const pair<T1, T2>&);
    template <class T1, class T2>
    bool    operator>(const pair<T1, T2>&, const pair<T1, T2>&);
    template <class T1, class T2>
    bool    operator>=(const pair<T1, T2>&, const pair<T1, T2>&);

    template <class T1, class T2>
    pair<T1, T2>::pair() : first(first_type()), second(second_type())
    {

    }

    template <class T1, class T2>
    template<class U, class V>
    pair<T1, T2>::pair(const pair<U,V>& other) : first(other.first), second(other.second)
    {

    }

    template <class T1, class T2>
    pair<T1, T2>::pair(const first_type& a, const second_type& b) : first(a), second(b)
    {

    }

    template <class T1, class T2>
    pair<T1, T2>&   pair<T1, T2>::operator=(const pair& other)
    {
        if (this == &other)
            return (*this);
        first = other.first;
        second = other.second;
        return (*this);
    }

    template <class T1, class T2>
    pair<T1, T2>    make_pair(T1 x, T2 y)
    {
        return (pair<T1, T2>(x, y));
    }

    template <class T1, class T2>
    bool    operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (lhs.first == rhs.first);
    }

    template <class T1, class T2>
    bool    operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (!(lhs == rhs));
    }

    template <class T1, class T2>
    bool    operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }

    template <class T1, class T2>
    bool    operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (!(rhs < lhs));
    }

    template <class T1, class T2>
    bool    operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (rhs < lhs);
    }
    template <class T1, class T2>
    bool    operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (!(lhs < rhs));
    }
}

#endif