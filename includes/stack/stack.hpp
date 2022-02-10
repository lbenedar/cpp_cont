/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:49:26 by lbenedar          #+#    #+#             */
/*   Updated: 2022/02/09 20:00:23 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
# define FT_STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> >
    class stack
    {
    public:

        typedef Container                           container_type;
        typedef typename Container::value_type      value_type;
        typedef typename Container::size_type       size_type;

        explicit    stack(const container_type& ctnr = container_type());
        stack(const stack& other);
        ~stack() {};
        stack   &operator=(const stack& other);
        
        bool                empty() const;
        size_type           size() const;
        value_type&         top();
        const   value_type& top() const;
        void                push(const value_type& val);
        void                pop();

        template <class U, class Cont>
        friend bool    operator== (const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
        template <class U, class Cont>
        friend bool    operator< (const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);

    protected:
        container_type  container;
    };

    template <class T, class Container>
        bool    operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
    template <class T, class Container>
        bool    operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
    template <class T, class Container>
        bool    operator< (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
    template <class T, class Container>
        bool    operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
    template <class T, class Container>
        bool    operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
    template <class T, class Container>
        bool    operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs);

    template <class T, class Container>
    stack<T, Container>::stack(const container_type& cntr)
    {
        container = cntr;
    }

    template <class T, class Container>
    stack<T, Container>::stack(const stack& other)
    {
        *this = other;
    }

    template <class T, class Container>
    stack<T, Container>   &stack<T, Container>::operator=(const stack& other)
    {
        if (this == &other)
            return (*this);
        container_type  cont = other.container;
        container = cont;
        return (*this);
    };

    template <class T, class Container>
    bool    stack<T, Container>::empty() const
    {
        return (container.empty());
    }

    template <class T, class Container>
    typename stack<T, Container>::size_type  stack<T, Container>::size() const
    {
        return (container.size());
    }

    template <class T, class Container>
    typename stack<T, Container>::value_type&         stack<T, Container>::top()
    {
        return (container.back());
    }

    template <class T, class Container>
    const   typename stack<T, Container>::value_type& stack<T, Container>::top() const
    {
        return (container.back());
    }

    template <class T, class Container>
    void    stack<T, Container>::push(const value_type& val)
    {
        container.push_back(val);
    }

    template <class T, class Container>
    void    stack<T, Container>::pop()
    {
        container.pop_back();
    }

    template <class T, class Container>
    bool    operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        if (lhs.container == rhs.container)
            return (true);
        return (false);
    }

    template <class T, class Container>
    bool    operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return (!(lhs == rhs));
    }

    template <class T, class Container>
    bool    operator< (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        if (lhs.container < rhs.container)
            return (true);
        return (false);
    }

    template <class T, class Container>
    bool    operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return (!(rhs < lhs));
    }

    template <class T, class Container>
    bool    operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Container>
    bool    operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return (!(lhs < rhs));
    }

}

#endif