/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 00:31:57 by lbenedar          #+#    #+#             */
/*   Updated: 2022/02/09 20:03:32 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include <memory>
#include "pair.hpp"
#include "rbtree.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
    class map
    {
    private:
        typedef rb_tree<pair<const Key, T> , ft::value_compare<pair<const Key, T>, Compare>, Alloc>    tree_type;
    public:
        typedef Key                                             key_type;
        typedef T                                               mapped_type;
        typedef pair<const Key, T>                              value_type;
        typedef Compare                                         key_compare;
        typedef Alloc                                           allocator_type;
        typedef typename Alloc::reference                       reference;
        typedef typename Alloc::const_reference                 const_reference;
        typedef typename Alloc::pointer                         pointer;
        typedef typename Alloc::const_pointer                   const_pointer;
        typedef typename tree_type::iterator                    iterator;
        typedef typename tree_type::const_iterator              const_iterator;
        typedef typename tree_type::reverse_iterator            reverse_iterator;
        typedef typename tree_type::const_reverse_iterator      const_reverse_iterator;
        typedef typename ft::value_compare<value_type, Compare> value_compare; 
        typedef std::ptrdiff_t                                  difference_type;
        typedef std::size_t                                     size_type;

        //empty
        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
        //range
        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
        //copy
        map(const map& x);
        
        ~map() {};
        
        map&    operator=(const map& x);

        iterator                begin();
        const_iterator          begin() const;
        iterator                end();
        const_iterator          end() const;
        reverse_iterator        rbegin();
        const_reverse_iterator  rbegin() const;
        reverse_iterator        rend();
        const_reverse_iterator  rend() const;
        
        bool        empty() const;
        size_type   size() const;
        size_type   max_size() const;

        mapped_type&    operator[](const key_type&);

        pair<iterator, bool>    insert(const value_type& val);
        iterator                insert(iterator position, const value_type& val);
        template <class InputIterator>
        void                    insert(InputIterator first, InputIterator last);
        
        void            erase(iterator position);
        size_type       erase(const key_type& k);
        void            erase(iterator first, iterator last);
        void            swap(map& x);
        void            clear();
        key_compare     key_comp() const;
        value_compare   value_comp() const;
        
        iterator        find(const key_type& k);
        const_iterator  find(const key_type& k) const;
        size_type       count(const key_type&) const;

        iterator                                lower_bound(const key_type&);
        const_iterator                          lower_bound(const key_type&) const;
        iterator                                upper_bound(const key_type&);
        const_iterator                          upper_bound(const key_type&) const;
        pair<iterator, iterator>                equal_range(const key_type &k);
        pair<const_iterator, const_iterator>    equal_range(const key_type &k) const;
        
        allocator_type get_allocator() const;

    private:
        tree_type     m_tree;
        key_compare   m_comp;
    };

    template <class Key, class T, class Compare, class Alloc>
    bool    operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);

    template <class Key, class T, class Compare, class Alloc>
    bool    operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);

    template <class Key, class T, class Compare, class Alloc>
    bool    operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);

    template <class Key, class T, class Compare, class Alloc>
    bool    operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);

    template <class Key, class T, class Compare, class Alloc>
    bool    operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);

    template <class Key, class T, class Compare, class Alloc>
    bool    operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);

    template <class Key, class T, class Compare, class Alloc>
    void    swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs);

    // map implementation

    template <class Key, class T, class Compare, class Alloc>
    map<Key, T, Compare, Alloc>::map(const key_compare& comp, const allocator_type& alloc): m_tree(value_compare(comp), alloc), m_comp(comp) 
    {

    }

    template <class Key, class T, class Compare, class Alloc>
    template <class InputIterator>
    map<Key, T, Compare, Alloc>::map(InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc):  m_tree(value_compare(comp), alloc), m_comp(comp)
    {
        insert(first, last);
    }

    template <class Key, class T, class Compare, class Alloc>
    map<Key, T, Compare, Alloc>::map(const map& x) : m_tree(value_compare(x.m_comp), x.get_allocator()), m_comp(x.m_comp)
    {
        *this = x; 
    }

    template <class Key, class T, class Compare, class Alloc>
    map<Key, T, Compare, Alloc>&    map<Key, T, Compare, Alloc>::operator=(const map& x)
    {
        if (this == &x)
            return (*this);
        clear();
        insert(x.begin(), x.end());
        return (*this);
    }
    
    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator        map<Key, T, Compare, Alloc>::begin()
    {
        return (m_tree.begin());
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator  map<Key, T, Compare, Alloc>::begin() const
    {
        return (m_tree.begin());
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator        map<Key, T, Compare, Alloc>::end()
    {
        return (m_tree.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator  map<Key, T, Compare, Alloc>::end() const
    {
        return (m_tree.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::reverse_iterator        map<Key, T, Compare, Alloc>::rbegin()
    {
        return (reverse_iterator(end()));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_reverse_iterator  map<Key, T, Compare, Alloc>::rbegin() const
    {
        return (const_reverse_iterator(end()));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::reverse_iterator        map<Key, T, Compare, Alloc>::rend()
    {
        return (reverse_iterator(begin()));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_reverse_iterator  map<Key, T, Compare, Alloc>::rend() const
    {
        return (const_reverse_iterator(begin()));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::mapped_type&    map<Key, T, Compare, Alloc>::operator[](const key_type& k)
    {
        return ((*((insert(ft::make_pair(k, mapped_type()))).first)).second);
    }

    template <class Key, class T, class Compare, class Alloc>
    pair<typename map<Key, T, Compare, Alloc>::iterator, bool>    map<Key, T, Compare, Alloc>::insert(const value_type& val)
    {
        pair<iterator, bool>    pair_result;
        typename tree_type::node_type   *new_node = m_tree.get_alloc_node().allocate(1);
        m_tree.get_alloc_node().construct(new_node, typename tree_type::node_type(val));
        m_tree.get_allocator().construct(&new_node->value, val);
        pair_result = m_tree.insert_node(new_node);
        if (!pair_result.second)
            m_tree.dealloc_node(new_node);
        return (pair_result);
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator    map<Key, T, Compare, Alloc>::insert(iterator position, const value_type& val)
    {
        pair<iterator, bool>    pair_result;
        typename tree_type::node_type   *new_node = m_tree.get_alloc_node().allocate(1);
        m_tree.get_alloc_node().construct(new_node, typename tree_type::node_type(val));
        m_tree.get_allocator().construct(&new_node->value, val);
        pair_result = m_tree.insert_node(position, new_node);
        if (!pair_result.second)
            m_tree.dealloc_node(new_node);
        return (pair_result.first);
    }

    template <class Key, class T, class Compare, class Alloc>
    template <class InputIterator>
    void    map<Key, T, Compare, Alloc>::insert(InputIterator first, InputIterator last)
    {
        for (InputIterator it = first; it != last; ++it)
            insert(*it);
    }

    template <class Key, class T, class Compare, class Alloc>
    void            map<Key, T, Compare, Alloc>::erase(iterator position)
    {
        m_tree.erase(position);
    }
    
    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::size_type       map<Key, T, Compare, Alloc>::erase(const key_type& k)
    {
        iterator pos = find(k);
        if (pos != end())
        {
            erase(pos);
            return (1);
        }
        return (0);
    }
    
    template <class Key, class T, class Compare, class Alloc>
    void            map<Key, T, Compare, Alloc>::erase(iterator first, iterator last)
    {
        for (iterator it = first; it != last;)
            erase(it++);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool        map<Key, T, Compare, Alloc>::empty() const
    {
        if (m_tree.size())
            return (false);
        return (true);
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::size_type   map<Key, T, Compare, Alloc>::size() const
    {
        return (m_tree.size());
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::size_type   map<Key, T, Compare, Alloc>::max_size() const
    {
        return (m_tree.get_alloc_node().max_size());
    }

    template <class Key, class T, class Compare, class Alloc>
    void    map<Key, T, Compare, Alloc>::swap(map& x)
    {
        m_tree.swap(x.m_tree);
    }

    template <class Key, class T, class Compare, class Alloc>
    void        map<Key, T, Compare, Alloc>::clear()
    {
        m_tree.clear();
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::key_compare     map<Key, T, Compare, Alloc>::key_comp() const
    {
        return (m_comp);
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::value_compare      map<Key, T, Compare, Alloc>::value_comp() const
    {
        return (value_compare(m_comp));
    }


    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator      map<Key, T, Compare, Alloc>::find(const key_type& k)
    {
        return (m_tree.find_node(ft::make_pair(k, mapped_type())));
    }
    
    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator  map<Key, T, Compare, Alloc>::find(const key_type& k) const
    {
        return (m_tree.find_node(ft::make_pair(k, mapped_type())));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::size_type       map<Key, T, Compare, Alloc>::count(const key_type &k) const
    {
        if (m_tree.find_node(ft::make_pair(k, mapped_type())) != end())
            return (1);
        return (0);
    }

        template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator  map<Key, T, Compare, Alloc>::lower_bound(const key_type& k)
    {
        return (m_tree.lower_bound(ft::make_pair(k, mapped_type())));
    }
        
    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator    map<Key, T, Compare, Alloc>::lower_bound(const key_type& k) const
    {
        return (m_tree.lower_bound(ft::make_pair(k, mapped_type())));
    }
        
    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator          map<Key, T, Compare, Alloc>::upper_bound(const key_type& k)
    {
        return (m_tree.upper_bound(ft::make_pair(k, mapped_type())));
    }
        
    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator    map<Key, T, Compare, Alloc>::upper_bound(const key_type& k) const
    {
        return (m_tree.upper_bound(ft::make_pair(k, mapped_type())));
    }
        
    template <class Key, class T, class Compare, class Alloc>
    pair<typename map<Key, T, Compare, Alloc>::iterator,
    typename map<Key, T, Compare, Alloc>::iterator>         map<Key, T, Compare, Alloc>::equal_range(const key_type &k)
    {
        return (m_tree.equal_range(ft::make_pair(k, mapped_type())));
    }
        
    template <class Key, class T, class Compare, class Alloc>
    pair<typename map<Key, T, Compare, Alloc>::const_iterator,
    typename map<Key, T, Compare, Alloc>::const_iterator>    map<Key, T, Compare, Alloc>::equal_range(const key_type &k) const
    {
        return (m_tree.equal_range(ft::make_pair(k, mapped_type())));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::allocator_type map<Key, T, Compare, Alloc>::get_allocator() const
    {
        return (m_tree.get_allocator());
    }
    
    // operators and swap implementation

    template <class Key, class T, class Compare, class Alloc>
    bool    operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        typename map<Key, T, Compare, Alloc>::const_iterator  t_last = lhs.end();
        for (typename map<Key, T, Compare, Alloc>::const_iterator i = lhs.begin(), j = rhs.begin(); i != t_last; ++i, ++j)
            if (*i != *j)
                return (false);
        return (true);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool    operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool    operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        typename map<Key, T, Compare, Alloc>::const_iterator   t_last_l = lhs.end();
        typename map<Key, T, Compare, Alloc>::const_iterator   t_last_r = rhs.end();
        typename map<Key, T, Compare, Alloc>::const_iterator   j = rhs.begin();
        for (typename map<Key, T, Compare, Alloc>::const_iterator i = lhs.begin(); i != t_last_l; ++i, ++j)
            if (j == t_last_r || *j < *i)
                return (false);
            else if (*i < *j)
                return (true);
        return (j != t_last_r);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool    operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        return (!(rhs < lhs));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool    operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        return (rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool    operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }

    template <class Key, class T, class Compare, class Alloc>
    void    swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs)
    {
        lhs.swap(rhs);
    }
}

#endif