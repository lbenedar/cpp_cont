/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:48:01 by lbenedar          #+#    #+#             */
/*   Updated: 2022/02/09 16:28:58 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
#include <iterator>
#include "utils.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
    public:
    
        typedef T                                   value_type;
        typedef Alloc                               allocator_type;
        typedef std::size_t                         size_type;
        typedef std::ptrdiff_t                      difference_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef typename Alloc::pointer             pointer;
        typedef typename Alloc::const_pointer       const_pointer;

        class const_iterator;

        class iterator
        {
        public:
            typedef std::ptrdiff_t              difference_type;
            typedef T                           value_type;
            typedef T*                          pointer;
            typedef T&                          reference;
            typedef random_access_iterator_tag  iterator_category;
    
            iterator() : i_ptr(NULL) {};
            iterator(value_type *ptr) : i_ptr(ptr) {};
            iterator(const iterator &it) : i_ptr(it.i_ptr) {};
            iterator&   operator=(const iterator&);

            bool        operator==(const iterator& other) const;
            bool        operator!=(const iterator& other) const;

            reference   operator*() const;
            pointer     operator->() const;
            reference   operator[](difference_type n) const;
            
            iterator&   operator++();
            iterator    operator++(int);
            iterator&   operator--();
            iterator    operator--(int);
            
            iterator            operator+(difference_type) const;
            iterator            operator-(difference_type) const;
            difference_type     operator-(const iterator&);
            difference_type     operator-(const const_iterator&);
            
            bool        operator<(const iterator& other) const;
            bool        operator<=(const iterator& other) const;
            bool        operator>(const iterator& other) const;
            bool        operator>=(const iterator& other) const;
            
            iterator&   operator+=(difference_type);
            iterator&   operator-=(difference_type);

            bool        operator==(const const_iterator& other) const;
            bool        operator!=(const const_iterator& other) const;
            bool        operator<(const const_iterator& other) const;
            bool        operator<=(const const_iterator& other) const;
            bool        operator>(const const_iterator& other) const;
            bool        operator>=(const const_iterator& other) const;

            friend iterator operator+(difference_type n, const iterator& it)
            {
                return (it + n);
            }

        private:
            value_type  *i_ptr;
        };

        class const_iterator
        {
        public:
            typedef std::ptrdiff_t              difference_type;
            typedef const T                     value_type;
            typedef const T*                    pointer;
            typedef const T&                    reference;
            typedef random_access_iterator_tag  iterator_category;
    
            const_iterator() : ci_ptr(NULL) {};
            const_iterator(value_type *ptr) : ci_ptr(ptr) {};
            const_iterator(const const_iterator& cit): ci_ptr(cit.ci_ptr) {};
            const_iterator(const iterator& it): ci_ptr(it.operator->()) {};
            const_iterator&   operator=(const const_iterator&);

            bool        operator==(const const_iterator& other) const;
            bool        operator!=(const const_iterator& other) const;

            reference   operator*() const;
            pointer     operator->() const;
            reference   operator[](difference_type n) const;
            
            const_iterator&   operator++();
            const_iterator    operator++(int);
            const_iterator&   operator--();
            const_iterator    operator--(int);
            
            const_iterator      operator+(difference_type) const;
            const_iterator      operator-(difference_type) const;
            difference_type     operator-(const const_iterator&) const;
            difference_type     operator-(const iterator&) const;
            
            bool        operator<(const const_iterator& other) const;
            bool        operator<=(const const_iterator& other) const;
            bool        operator>(const const_iterator& other) const;
            bool        operator>=(const const_iterator& other) const;
            
            const_iterator&   operator+=(difference_type);
            const_iterator&   operator-=(difference_type);

            bool        operator==(const iterator& other) const;
            bool        operator!=(const iterator& other) const;
            bool        operator<(const iterator& other) const;
            bool        operator<=(const iterator& other) const;
            bool        operator>(const iterator& other) const;
            bool        operator>=(const iterator& other) const;

            friend const_iterator operator+(difference_type n, const const_iterator& cit)
            {
                return (cit + n);
            }

        private:
            value_type  *ci_ptr;
        };

        typedef ft::reverse_iterator<iterator>        reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;        

        //default constructor
        explicit    vector(const allocator_type& alloc = allocator_type()); 
        //fill constructor
        explicit    vector(size_type n, const value_type &val = value_type(),
                           const allocator_type &alloc = allocator_type());
        //range constructor
        template <class InputIterator>
                    vector(InputIterator first, InputIterator last, 
                           const allocator_type &alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0);
        //copy constructor
        vector(const vector& x);
        
        //destructor
        ~vector(); 
        
        vector& operator=(const vector& x);

        iterator                begin();
        const_iterator          begin() const;
        iterator                end();
        const_iterator          end() const;
        reverse_iterator        rbegin();
        const_reverse_iterator  rbegin() const;
        reverse_iterator        rend();
        const_reverse_iterator  rend() const;

        size_type   size() const;
        size_type   max_size() const;
        void        resize(size_type n, value_type val = value_type());
        // return size of allocated memory
        size_type   capacity() const;
        bool        empty() const;
        // request a change of capacity
        void        reserve(size_type n);
        
        reference       operator[](size_type n);
        const_reference operator[](size_type n) const;
        reference       at(size_type n);
        const_reference at(size_type n) const;
        reference       front();
        const_reference front() const;
        reference       back();
        const_reference back() const;

        template <class InputIterator>
            void    assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0);
        void        assign(size_type n, const value_type &val);
        void        push_back(const value_type &val);
        void        pop_back();
        iterator    insert(iterator position, const value_type val);
        void        insert(iterator position, size_type n, const value_type & val);
        template <class InputIterator>
            void    insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0);
        iterator    erase(iterator position);
        iterator    erase(iterator first, iterator last);
        void        swap(vector &x);
        void        clear();

        // return allocator
        allocator_type  get_allocator() const;

    private:
        pointer         first;
        pointer         last;
        size_t          alloc_size;
        size_t          alloc_cap;
        allocator_type  alloc_t;

        size_type   nextPowerOf2(size_type);
        void        clear_range(pointer begin, size_t n);
        size_type   realloc_copy(size_type new_size);
    };

    template <class T, class Alloc>
        bool    operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        bool    operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        bool    operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        bool    operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        bool    operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        bool    operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        void swap(vector<T,Alloc>& x, vector<T,Alloc>& y);

    // iterators implementation

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator&   vector<T, Alloc>::iterator::operator=(const iterator& other)
    {
        if (this == &other)
            return (*this);
        i_ptr = other.i_ptr;
        return (*this);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator==(const iterator& other) const
    {
        if (i_ptr == other.i_ptr)
            return (true);
        return (false);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator!=(const iterator& other) const
    {
        return (!(*this == other));   
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::reference   vector<T, Alloc>::iterator::operator*() const
    {
        return (*i_ptr);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator::pointer     vector<T, Alloc>::iterator::operator->() const
    {
        return (i_ptr);
    }
    
    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator::reference   vector<T, Alloc>::iterator::operator[](difference_type n) const
    {
        return (*(i_ptr + n));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator&   vector<T, Alloc>::iterator::operator++()
    {
        ++i_ptr;
        return (*this);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator   vector<T, Alloc>::iterator::operator++(int)
    {
        iterator    temp = *this;
        ++(*this);
        return (temp);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator&   vector<T, Alloc>::iterator::operator--()
    {
        --i_ptr;
        return (*this);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator   vector<T, Alloc>::iterator::operator--(int)
    {
        iterator    temp = *this;
        --(*this);
        return (temp);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator   vector<T, Alloc>::iterator::operator+(difference_type n) const
    {
        iterator    temp = *this;
        temp.i_ptr += n;
        return (temp);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator   vector<T, Alloc>::iterator::operator-(difference_type n) const
    {
        iterator    temp = *this;
        temp.i_ptr -= n;
        return (temp);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::difference_type   vector<T, Alloc>::iterator::operator-(const iterator& other)
    {
        return (static_cast<difference_type>(this->i_ptr - other.i_ptr));
    }

        template <class T, class Alloc>
    typename vector<T, Alloc>::difference_type   vector<T, Alloc>::iterator::operator-(const const_iterator& other)
    {
        return (static_cast<difference_type>(this->i_ptr - other.operator->()));
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator<(const iterator& other) const
    {
        if (i_ptr < other.i_ptr)
            return (true);
        return (false);
    }
    
    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator<=(const iterator& other) const
    {
        return (!(other < *this));
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator>(const iterator& other) const
    {
        return (other < *this);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator>=(const iterator& other) const
    {
        return (!(*this < other));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator&   vector<T, Alloc>::iterator::operator+=(difference_type n)
    {
        i_ptr += n;
        return (*this);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator&   vector<T, Alloc>::iterator::operator-=(difference_type n)
    {
        i_ptr -= n;
        return (*this);
    }

    template <class T, class Alloc>
    static typename vector<T, Alloc>::iterator    operator+(long n, const typename vector<T, Alloc>::iterator& it)
    {
        return (it + n);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator==(const const_iterator& other) const
    {
        if (i_ptr == other.operator->())
            return (true);
        return (false);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator!=(const const_iterator& other) const
    {
        return (!(*this == other));   
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator<(const const_iterator& other) const
    {
        if (i_ptr < other.operator->())
            return (true);
        return (false);
    }
    
    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator<=(const const_iterator& other) const
    {
        return (!(other < *this));
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator>(const const_iterator& other) const
    {
        return (other < *this);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::iterator::operator>=(const const_iterator& other) const
    {
        return (!(*this < other));
    }

    // const_iterators implementation
    
    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator&   vector<T, Alloc>::const_iterator::operator=(const const_iterator& other)
    {
        if (this == &other)
            return (*this);
        ci_ptr = other.ci_ptr;
        return (*this);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator==(const const_iterator& other) const
    {
        if (ci_ptr == other.ci_ptr)
            return (true);
        return (false);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator!=(const const_iterator& other) const
    {
        return (!(*this == other));  
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator::reference   vector<T, Alloc>::const_iterator::operator*() const
    {
        return (*ci_ptr);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator::pointer     vector<T, Alloc>::const_iterator::operator->() const
    {
        return (ci_ptr);
    }
    
    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator::reference   vector<T, Alloc>::const_iterator::operator[](difference_type n) const
    {
        return (*(ci_ptr + n));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator&   vector<T, Alloc>::const_iterator::operator++()
    {
        ++ci_ptr;
        return (*this);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator   vector<T, Alloc>::const_iterator::operator++(int)
    {
        const_iterator  temp = *this;
        ++(*this);
        return (temp); 
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator&   vector<T, Alloc>::const_iterator::operator--()
    {
        --ci_ptr;
        return (*this);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator   vector<T, Alloc>::const_iterator::operator--(int)
    {
        const_iterator  temp = *this;
        --(*this);
        return (temp); 
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator   vector<T, Alloc>::const_iterator::operator+(difference_type n) const
    {
        const_iterator  temp = *this;
        temp.ci_ptr += n;
        return (temp);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator   vector<T, Alloc>::const_iterator::operator-(difference_type n) const
    {
        const_iterator  temp = *this;
        temp.ci_ptr -= n;
        return (temp);
    }
    

    template <class T, class Alloc>
    typename vector<T, Alloc>::difference_type   vector<T, Alloc>::const_iterator::operator-(const const_iterator &other) const
    {
        return (static_cast<difference_type>(this->ci_ptr - other.ci_ptr));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::difference_type   vector<T, Alloc>::const_iterator::operator-(const iterator &other) const
    {
        return (static_cast<difference_type>(this->ci_ptr - other.operator->()));
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator<(const const_iterator& other) const
    {
        if (ci_ptr < other.ci_ptr)
            return (true);
        return (false);
    }
    
    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator<=(const const_iterator& other) const
    {
        return (!(other < *this));
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator>(const const_iterator& other) const
    {
        return (other < *this);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator>=(const const_iterator& other) const
    {
        return (!(*this < other));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator&   vector<T, Alloc>::const_iterator::operator+=(difference_type n)
    {
        ci_ptr += n;
        return (*this);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator&   vector<T, Alloc>::const_iterator::operator-=(difference_type n)
    {
        ci_ptr -= n;
        return (*this);
    }

    template <class T, class Alloc>
    static typename vector<T, Alloc>::const_iterator    operator+(typename vector<T, Alloc>::const_iterator::difference_type n, const typename vector<T, Alloc>::const_iterator& cit)
    {
        return (cit + n);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator==(const iterator& other) const
    {
        if (ci_ptr == other.operator->())
            return (true);
        return (false);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator!=(const iterator& other) const
    {
        return (!(*this == other));   
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator<(const iterator& other) const
    {
        if (ci_ptr < other.operator->())
            return (true);
        return (false);
    }
    
    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator<=(const iterator& other) const
    {
        return (!(other < *this));
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator>(const iterator& other) const
    {
        return (other < *this);
    }

    template <class T, class Alloc>
    bool        vector<T, Alloc>::const_iterator::operator>=(const iterator& other) const
    {
        return (!(*this < other));
    }

    template <class T, class Alloc>
    size_t  vector<T, Alloc>::nextPowerOf2(size_type n)
    {
        --n;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return (++n);
    }

    template <class T, class Alloc>
    void  vector<T, Alloc>::clear_range(pointer begin, size_t n)
    {
        for (size_t i = 0; i < n; ++i)
            alloc_t.destroy(begin + i);
    }

    template <class T, class Alloc>
    size_t  vector<T, Alloc>::realloc_copy(size_type new_size)
    {
        size_type   temp_cap = nextPowerOf2(new_size);
        pointer     temp = alloc_t.allocate(temp_cap + 1);
        size_type   j = 0;
        if (first)
        {
            for (; j < alloc_size; ++j)
                alloc_t.construct(temp + j, first[j]);
            clear_range(first, alloc_size);
            alloc_t.deallocate(first, alloc_cap + 1);
        }
        first = temp;
        last = temp + j;
        alloc_cap = temp_cap;
        return (j);
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const Alloc& alloc)
    {
        alloc_t = alloc;
        first = NULL;
        last = NULL;
        alloc_size = 0;
        alloc_cap = 0;
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(size_type n, const value_type &val, const allocator_type &alloc)
    {
        alloc_t = alloc;
        alloc_size = n;
        alloc_cap = nextPowerOf2(alloc_size);
        first = alloc_t.allocate(alloc_cap + 1);
        size_type i;
        for (i = 0; i < alloc_size; ++i)
            alloc_t.construct(first + i, val);
        last = first + i;
    }

    template <class T, class Alloc>
    template <class InputIterator>
    vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type &alloc,
                                typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type*)
    {
        alloc_size = 0;
        alloc_t = alloc;
        for (InputIterator i = first; i != last; ++i)
            ++alloc_size;
        alloc_cap = nextPowerOf2(alloc_size);
        this->first = alloc_t.allocate(alloc_cap + 1);
        size_type j = 0;
        for (InputIterator i = first; i != last; ++i)
            alloc_t.construct(this->first + j++, *i);
        this->last = this->first + j;
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const vector& x)
    {
        alloc_t = x.get_allocator();
        alloc_size = 0;
        alloc_cap = 0;
        *this = x;
    }

    template <class T, class Alloc>
    vector<T, Alloc>  &vector<T, Alloc>::operator=(const vector& x)
    {
        if (this == &x)
            return (*this);
        if (alloc_cap < x.size() && alloc_cap)
        {
            clear_range(first, alloc_size);
            alloc_t.deallocate(first, alloc_cap + 1);
            alloc_cap = x.capacity();
            first = alloc_t.allocate(alloc_cap + 1);
        } else if (!alloc_cap)
        {
            alloc_cap = x.capacity();
            first = alloc_t.allocate(alloc_cap + 1);
        }
        
        alloc_size = x.size();
        size_type j = 0;
        const_iterator    t_last = x.end();
        for (const_iterator i = x.begin(); i != t_last; ++i, ++j)
            alloc_t.construct(first + j, *i);
        last = first + j;
        return (*this);
    }

    template <class T, class Alloc>
    vector<T, Alloc>::~vector()
    {
        clear_range(first, alloc_size);
        alloc_t.deallocate(first, alloc_cap + 1);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator  vector<T, Alloc>::begin()
    {
        return (iterator(first));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator  vector<T, Alloc>::begin() const
    {
        return (const_iterator(first));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator  vector<T, Alloc>::end()
    {
        return (iterator(last));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator  vector<T, Alloc>::end() const
    {
        return (const_iterator(last));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::reverse_iterator  vector<T, Alloc>::rbegin()
    {
        return (reverse_iterator(end()));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_reverse_iterator  vector<T, Alloc>::rbegin() const
    {
        return (const_reverse_iterator(end()));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::reverse_iterator  vector<T, Alloc>::rend()
    {
        return (reverse_iterator(begin()));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_reverse_iterator  vector<T, Alloc>::rend() const
    {
        return (const_reverse_iterator(begin()));
    }

    template <class T, class Alloc>
    size_t   vector<T, Alloc>::size() const
    {
        return (alloc_size);
    }

    template <class T, class Alloc>
    size_t   vector<T, Alloc>::max_size() const
    {
        return (alloc_t.max_size());
    }

    template <class T, class Alloc>
    void        vector<T, Alloc>::resize(size_type n, value_type val)
    {
        if (n < alloc_size)
            clear_range(first + n, alloc_size - n);
        else if (n > alloc_cap)
            for (size_type j = realloc_copy(n); j < n; ++j)
                alloc_t.construct(first + j, val);
        else if (n > alloc_size)
            for (size_type j = alloc_size; j < n; ++j)
                alloc_t.construct(first + j, val);
        alloc_size = n;
        last = first + n;
    }

    template <class T, class Alloc>
    size_t        vector<T, Alloc>::capacity() const
    {
        return (alloc_cap);
    }

    template <class T, class Alloc>
    bool    vector<T, Alloc>::empty() const
    {
        return (!alloc_size);
    }

    template <class T, class Alloc>
    void    vector<T, Alloc>::reserve(size_type n)
    {
        if (n > max_size())
            throw(std::length_error("Your size argument is greater than max_size"));
        if (n > alloc_cap)
            realloc_copy(n);
    }


    template <class T, class Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type n)
    {
        return (*(first + n));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](size_type n) const
    {
        return (*(first + n));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n)
    {
        if (n >= alloc_size)
            throw(std::out_of_range("index out of range"));
        return (*(first + n));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type n) const
    {
        if (n >= alloc_size)
            throw(std::out_of_range("index out of range"));
        return (*(first + n));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::front()
    {
        return (*first);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const
    {
        return (*first);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::back()
    {
        return (*(last - 1));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const
    {
        return (*(last - 1));
    }

    template <class T, class Alloc>
    template <class InputIterator>
    void    vector<T, Alloc>::assign(InputIterator first, InputIterator last,
                                        typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type*)
    {
        size_type temp_size = 0;
        for (InputIterator i = first; i != last; ++i)
            ++temp_size;
        if (temp_size > alloc_cap)
        {
            clear_range(this->first, alloc_size);
            alloc_t.deallocate(this->first, alloc_cap + 1);
            alloc_cap = nextPowerOf2(temp_size);
            this->first = alloc_t.allocate(alloc_cap + 1);
        }
        alloc_size = temp_size;
        size_type j = 0;
        for (InputIterator i = first; i != last; ++i, ++j)
            alloc_t.construct(this->first + j, *i);
        this->last = this->first + j;
    }

    template <class T, class Alloc>
    void    vector<T, Alloc>::assign(size_type n, const value_type &val)
    {
        if (n > alloc_size)
        {
            clear_range(first, alloc_size);
            alloc_t.deallocate(first, alloc_cap + 1);
            alloc_cap = nextPowerOf2(n);
            first = alloc_t.allocate(alloc_cap + 1);
        }
        alloc_size = n;
        for (size_type i = 0; i < alloc_size; ++i)
            alloc_t.construct(first + i, val);
        last = first + alloc_size;
    }

    template <class T, class Alloc>
    void    vector<T, Alloc>::push_back(const value_type &val)
    {
        if (alloc_size + 1 > alloc_cap)
            realloc_copy(alloc_size + 1);
        alloc_t.construct(first + alloc_size, val);
        ++alloc_size;
        last = first + alloc_size;
    }

    template <class T, class Alloc>
    void    vector<T, Alloc>::pop_back()
    {
        if (!alloc_size)
            return ;
        --alloc_size;
        last = first + alloc_size;
        alloc_t.destroy(last);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator    vector<T, Alloc>::insert(iterator position, const value_type val)
    {
        size_type  pos_num = position - begin();
        if (alloc_size + 1 > alloc_cap)
            realloc_copy(alloc_size + 1);
        position = begin() + pos_num;
        for (iterator i = end(); i >= position; --i)
            alloc_t.construct(&(*(i + 1)), *i);
        alloc_t.construct(&(*position), val);
        ++alloc_size;
        last = first + alloc_size;
        return (position);
    }

    template <class T, class Alloc>
    void        vector<T, Alloc>::insert(iterator position, size_type n, const value_type & val)
    {
        size_type  pos_num = position - begin();
        if (alloc_size + n > alloc_cap)
            realloc_copy(alloc_size + n);
        position = begin() + pos_num;
        for (iterator i = end(); i >= position; --i)
            alloc_t.construct(&(*(i + n)), *i);
        for (size_type i = 0; i < n; ++i)
            alloc_t.construct(&(*(position + i)), val);
        alloc_size += n;
        last = first + alloc_size;
    }
    
    template <class T, class Alloc>
    template <class InputIterator>
    void        vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last,
                                            typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type*)
    {
        size_type n = 0;
        for (InputIterator i = first; i != last; ++i)
            ++n;
        size_type  pos_num = position - begin();
        if (alloc_size + n > alloc_cap)
            realloc_copy(alloc_size + n);
        position = begin() + pos_num;
        for (iterator i = end(); i >= position; --i)
            alloc_t.construct(&(*(i + n)), *i);
        size_type j = 0;
        for (InputIterator i = first; i != last; ++i, ++j)
            alloc_t.construct(&(*(position + j)), *i);
        alloc_size += n;
        this->last = this->first + alloc_size;
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator    vector<T, Alloc>::erase(iterator position)
    {
        if (!alloc_size)
            return (position);
        reference   val = *position;
        alloc_t.destroy(&val);
        iterator t_last = end();
        for (iterator i = (position + 1); i < t_last; ++i)
            alloc_t.construct(&(*(i - 1)), *i);
        --alloc_size;
        last = first + alloc_size;
        return (position);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator    vector<T, Alloc>::erase(iterator first, iterator last)
    {
        if (!alloc_size)
            return (first);
        size_type   n = 0;
        for (iterator i = first; i < last; ++i, ++n)
            alloc_t.destroy(&(*i));
        iterator t_last = end();
        for (iterator i = last; i < t_last; ++i)
            alloc_t.construct(&(*(i - n)), *i);
        alloc_size -= n;
        this->last = this->first + alloc_size;
        return (first);
    }

    template <class T, class Alloc>
    void    vector<T, Alloc>::swap(vector &x)
    {
        pointer t_first = x.first;
        pointer t_last = x.last;
        size_t  t_alloc_size = x.alloc_size;
        size_t  t_alloc_cap = x.alloc_cap;

        x.first = first;
        x.last = last;
        x.alloc_size = alloc_size;
        x.alloc_cap = alloc_cap;

        first = t_first;
        last = t_last;
        alloc_size = t_alloc_size;
        alloc_cap = t_alloc_cap;
    }

    template <class T, class Alloc>
    void    vector<T, Alloc>::clear()
    {
        vector<T, Alloc>().swap(*this);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::allocator_type  vector<T, Alloc>::get_allocator() const
    {
        return (alloc_t);
    }
    
    template <class T, class Alloc>
    bool    operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        typename vector<T, Alloc>::const_iterator  t_last = lhs.end();
        for (typename vector<T, Alloc>::const_iterator i = lhs.begin(), j = rhs.begin(); i != t_last; ++i, ++j)
            if (*i != *j)
                return (false);
        return (true);
    }

    template <class T, class Alloc>
    bool    operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    
    template <class T, class Alloc>
    bool    operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        typename vector<T,Alloc>::const_iterator   t_last_l = lhs.end();
        typename vector<T,Alloc>::const_iterator   t_last_r = rhs.end();
        typename vector<T,Alloc>::const_iterator   j = rhs.begin();
        for (typename vector<T,Alloc>::const_iterator i = lhs.begin(); i != t_last_l; ++i, ++j)
            if (j == t_last_r || *j < *i)
                return (false);
            else if (*i < *j)
                return (true);
        return (j != t_last_r);
    }

    template <class T, class Alloc>
    bool    operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(rhs < lhs));
    }

    template <class T, class Alloc>
    bool    operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Alloc>
    bool    operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }

    template <class T, class Alloc>
    void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
    {
        x.swap(y);
    }
}

#endif