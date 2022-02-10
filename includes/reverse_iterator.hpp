/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:28:48 by lbenedar          #+#    #+#             */
/*   Updated: 2022/02/06 16:50:01 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "utils.hpp"
#include <memory>

namespace ft
{

    template <class Iter>
    class reverse_iterator
    {
    public:
        typedef Iter                                                    iterator_type;
        typedef typename ft::iterator_traits<Iter>::iterator_category   iterator_category;
        typedef typename ft::iterator_traits<Iter>::value_type          value_type;
        typedef typename ft::iterator_traits<Iter>::difference_type     difference_type;
        typedef typename ft::iterator_traits<Iter>::pointer             pointer;
        typedef typename ft::iterator_traits<Iter>::reference           reference;

        reverse_iterator() : current(Iter()) {};
        explicit reverse_iterator(iterator_type x) : current(x) {};
        template<class U>
        reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {};

        ~reverse_iterator() {};

        template <class U>
        reverse_iterator &operator=(const reverse_iterator<U> &other);

        iterator_type base() const;

        reference operator*() const;
        pointer operator->() const;
        reference operator[](difference_type n) const;

        reverse_iterator &operator++();
        reverse_iterator &operator--();
        reverse_iterator operator++(int);
        reverse_iterator operator--(int);
        reverse_iterator operator+(difference_type n) const;
        reverse_iterator operator-(difference_type n) const;
        reverse_iterator &operator+=(difference_type n);
        reverse_iterator &operator-=(difference_type n);

    protected:
        iterator_type current;
    };

    template <class Iter1, class Iter2>
    bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <class Iter1, class Iter2>
    bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <class Iter1, class Iter2>
    bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <class Iter1, class Iter2>
    bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <class Iter1, class Iter2>
    bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }


    template <class Iter1, class Iter2>
    bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template<class Iter>
    reverse_iterator<Iter>  operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
    {
        return (reverse_iterator<Iter>(it.base() - n));
    }

    template<class Iter1, class Iter2>
    typename reverse_iterator<Iter1>::difference_type    operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
    {
        return (rhs.base() - lhs.base());
    }

    template<class Iterator>
    template <class U>
    reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator=(const reverse_iterator<U> &other)
    {
        current = other.base();
        return (*this);
    }

    template<class Iterator>
    typename reverse_iterator<Iterator>::iterator_type reverse_iterator<Iterator>::base() const
    {
        return (current);
    }

    template<class Iterator>
    typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator*() const
    {
        Iterator    tmp = current;
        
        return (*(--tmp));
    }

    template<class Iterator>
    typename reverse_iterator<Iterator>::pointer reverse_iterator<Iterator>::operator->() const
    {
        return (std::__addressof(operator*()));
    }
    
    template<class Iterator>
    typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator[](difference_type n) const
    {
        return (base()[-n - 1]);
    }

    template<class Iterator>
    reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator++()
    {
        --current;
        return (*this);
    }

    template<class Iterator>
    reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator--()
    {
        ++current;
        return (*this);
    }

    template<class Iterator>
    reverse_iterator<Iterator>  reverse_iterator<Iterator>::operator++(int)
    {
        reverse_iterator<Iterator>  temp = *this;

        --current;
        return (temp);
    }

    template<class Iterator>
    reverse_iterator<Iterator>  reverse_iterator<Iterator>::operator--(int)
    {
        reverse_iterator<Iterator>  temp = *this;

        ++current;
        return (temp);
    }

    template<class Iterator>
    reverse_iterator<Iterator>  reverse_iterator<Iterator>::operator+(difference_type n) const
    {
        return (reverse_iterator(base() - n));
    }
    
    template<class Iterator>
    reverse_iterator<Iterator>  reverse_iterator<Iterator>::operator-(difference_type n) const
    {
        return (reverse_iterator(base() + n));
    }

    template<class Iterator>
    reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator+=(difference_type n)
    {
        current -= n;
        return (*this);
    }

    template<class Iterator>
    reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator-=(difference_type n)
    {
        current += n;
        return (*this);
    }
}

#endif