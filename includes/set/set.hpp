/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:52:37 by lbenedar          #+#    #+#             */
/*   Updated: 2022/02/07 18:42:37 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include <memory>
#include "rbtree_set.hpp"

namespace ft
{
    template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class set
    {
    private:
        typedef ft::rb_tree_set<Key, Compare, Allocator>        tree_type;
    public:
        typedef Key                                             key_type;
        typedef Key                                             value_type;
        typedef std::size_t                                     size_type;
        typedef std::ptrdiff_t                                  difference_type;
        typedef Compare                                         key_compare;
        typedef Compare                                         value_compare;
        typedef Allocator                                       allocator_type;
        typedef value_type&                                     reference;
        typedef const value_type&                               const_reference;
        typedef typename Allocator::pointer                     pointer;
        typedef typename Allocator::const_pointer               const_pointer;
        typedef typename tree_type::const_iterator              iterator;
        typedef typename tree_type::const_iterator              const_iterator;
        typedef typename tree_type::const_reverse_iterator      reverse_iterator;
        typedef typename tree_type::const_reverse_iterator      const_reverse_iterator;

        explicit    set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
        template <class InputIterator>
        set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
        set(const set& x);

        ~set() {};

        set&    operator=(const set& x);
        
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

        pair<iterator, bool>    insert(const value_type& val);
        iterator                insert(iterator position, const value_type& val);
        template <class InputIterator>
        void                    insert(InputIterator first, InputIterator last);
        void                    erase(iterator position);
        size_type               erase(const value_type& val);
        void                    erase(iterator first, iterator last);
        void                    swap(set &x);
        void                    clear();

        key_compare     key_comp() const;
        value_compare   value_comp() const;

        iterator                                find(const value_type& val);
        const_iterator                          find(const value_type& val) const;
        size_type                               count(const value_type& val) const;
        iterator                                lower_bound(const value_type& val);
        const_iterator                          lower_bound(const value_type& val) const;
        iterator                                upper_bound(const value_type& val);
        const_iterator                          upper_bound(const value_type& val) const;
        pair<iterator, iterator>                equal_range(const value_type& val);
        pair<const_iterator, const_iterator>    equal_range(const value_type& val) const;

        allocator_type  get_allocator() const;
                
    private:
        tree_type     s_tree;
    };

    template <class Key, class Compare, class Alloc>
    bool    operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs);
    template <class Key, class Compare, class Alloc>
    bool    operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs);
    template <class Key, class Compare, class Alloc>
    bool    operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs);
    template <class Key, class Compare, class Alloc>
    bool    operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs);
    template <class Key, class Compare, class Alloc>
    bool    operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs);
    template <class Key, class Compare, class Alloc>
    bool    operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs);
    template <class Key, class Compare, class Alloc>
    void    swap(set<Key, Compare, Alloc>& lhs, set<Key, Compare, Alloc>& rhs);


    template <class Key, class Compare, class Alloc>
    set<Key, Compare, Alloc>::set(const key_compare& comp, const allocator_type& alloc) : s_tree(comp, alloc)
    {
        
    }

    template <class Key, class Compare, class Alloc>
    template <class InputIterator>
    set<Key, Compare, Alloc>::set(InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc) : s_tree(comp, alloc)
    {
        insert(first, last);
    }

    template <class Key, class Compare, class Alloc> 
    set<Key, Compare, Alloc>::set(const set& x) : s_tree(x.key_comp(), x.get_allocator())
    {
        *this = x; 
    }

    template <class Key, class Compare, class Alloc>
    set<Key, Compare, Alloc>&    set<Key, Compare, Alloc>::operator=(const set& x)
    {
        if (this == &x)
            return (*this);
        clear();
        insert(x.begin(), x.end());
        return (*this);
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::iterator        set<Key, Compare, Alloc>::begin()
    {
        return (s_tree.begin());
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::const_iterator  set<Key, Compare, Alloc>::begin() const
    {
        return (s_tree.begin());
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::iterator        set<Key, Compare, Alloc>::end()
    {
        return (s_tree.end());
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::const_iterator  set<Key, Compare, Alloc>::end() const
    {
        return (s_tree.end());
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::reverse_iterator        set<Key, Compare, Alloc>::rbegin()
    {
        return (reverse_iterator(end()));
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::const_reverse_iterator  set<Key, Compare, Alloc>::rbegin() const
    {
        return (const_reverse_iterator(end()));
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::reverse_iterator        set<Key, Compare, Alloc>::rend()
    {
        return (reverse_iterator(begin()));
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::const_reverse_iterator  set<Key, Compare, Alloc>::rend() const
    {
        return (const_reverse_iterator(begin()));
    }

    template <class Key, class Compare, class Alloc>
    pair<typename set<Key, Compare, Alloc>::iterator, bool>    set<Key, Compare, Alloc>::insert(const value_type& val)
    {
        pair<iterator, bool>    pair_result;
        typename tree_type::node_type   *new_node = s_tree.get_alloc_node().allocate(1);
        s_tree.get_alloc_node().construct(new_node, typename tree_type::node_type(val));
        s_tree.get_allocator().construct(&new_node->value, val);
        pair_result = s_tree.insert_node(new_node);
        if (!pair_result.second)
            s_tree.dealloc_node(new_node);
        return (pair_result);
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::iterator    set<Key, Compare, Alloc>::insert(iterator position, const value_type& val)
    {
        pair<iterator, bool>    pair_result;
        typename tree_type::node_type   *new_node = s_tree.get_alloc_node().allocate(1);
        s_tree.get_alloc_node().construct(new_node, typename tree_type::node_type(val));
        s_tree.get_allocator().construct(&new_node->value, val);
        pair_result = s_tree.insert_node(position, new_node);
        if (!pair_result.second)
            s_tree.dealloc_node(new_node);
        return (pair_result.first);
    }

    template <class Key, class Compare, class Alloc>
    template <class InputIterator>
    void    set<Key, Compare, Alloc>::insert(InputIterator first, InputIterator last)
    {
        for (InputIterator it = first; it != last; ++it)
            insert(*it);
    }

    template <class Key, class Compare, class Alloc>
    void            set<Key, Compare, Alloc>::erase(iterator position)
    {
        s_tree.erase(position);
    }
    
    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::size_type       set<Key, Compare, Alloc>::erase(const key_type& k)
    {
        iterator pos = find(k);
        if (pos != end())
        {
            erase(pos);
            return (1);
        }
        return (0);
    }
    
    template <class Key, class Compare, class Alloc>
    void            set<Key, Compare, Alloc>::erase(iterator first, iterator last)
    {
        for (iterator it = first; it != last;)
            erase(it++);
    }

    template <class Key, class Compare, class Alloc>
    bool        set<Key, Compare, Alloc>::empty() const
    {
        if (s_tree.size())
            return (false);
        return (true);
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::size_type   set<Key, Compare, Alloc>::size() const
    {
        return (s_tree.size());
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::size_type   set<Key, Compare, Alloc>::max_size() const
    {
        return (s_tree.get_alloc_node().max_size());
    }

    template <class Key, class Compare, class Alloc>
    void    set<Key, Compare, Alloc>::swap(set& x)
    {
        s_tree.swap(x.s_tree);
    }

    template <class Key, class Compare, class Alloc>
    void    set<Key, Compare, Alloc>::clear()
    {
        s_tree.clear();
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::key_compare     set<Key, Compare, Alloc>::key_comp() const
    {
        return (s_tree.key_comp());
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::value_compare      set<Key, Compare, Alloc>::value_comp() const
    {
        return (s_tree.key_comp());
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::iterator      set<Key, Compare, Alloc>::find(const key_type& k)
    {
        return (s_tree.find_node(k));
    }
    
    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::const_iterator  set<Key, Compare, Alloc>::find(const key_type& k) const
    {
        return (s_tree.find_node(k));
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::size_type       set<Key, Compare, Alloc>::count(const key_type &k) const
    {
        if (s_tree.find_node(k) != end())
            return (1);
        return (0);
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::iterator  set<Key, Compare, Alloc>::lower_bound(const key_type& k)
    {
        return (s_tree.lower_bound(k));
    }
        
    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::const_iterator    set<Key, Compare, Alloc>::lower_bound(const key_type& k) const
    {
        return (s_tree.lower_bound(k));
    }
        
    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::iterator          set<Key, Compare, Alloc>::upper_bound(const key_type& k)
    {
        return (s_tree.upper_bound(k));
    }
        
    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::const_iterator    set<Key, Compare, Alloc>::upper_bound(const key_type& k) const
    {
        return (s_tree.upper_bound(k));
    }
    
    template <class Key, class Compare, class Alloc>
    pair<typename set<Key, Compare, Alloc>::iterator,
    typename set<Key, Compare, Alloc>::iterator>         set<Key, Compare, Alloc>::equal_range(const key_type &k)
    {
        return (s_tree.equal_range(k));
    }
        
    template <class Key, class Compare, class Alloc>
    pair<typename set<Key, Compare, Alloc>::const_iterator,
    typename set<Key, Compare, Alloc>::const_iterator>    set<Key, Compare, Alloc>::equal_range(const key_type &k) const
    {
        return (s_tree.equal_range(k));
    }

    template <class Key, class Compare, class Alloc>
    typename set<Key, Compare, Alloc>::allocator_type set<Key, Compare, Alloc>::get_allocator() const
    {
        return (s_tree.get_allocator());
    }

    // operators and swap implementation

    template <class Key, class Compare, class Alloc>
    bool    operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        typename set<Key, Compare, Alloc>::const_iterator  t_last = lhs.end();
        for (typename set<Key, Compare, Alloc>::const_iterator i = lhs.begin(), j = rhs.begin(); i != t_last; ++i, ++j)
            if (*i != *j)
                return (false);
        return (true);
    }

    template <class Key, class Compare, class Alloc>
    bool    operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }

    template <class Key, class Compare, class Alloc>
    bool    operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        typename set<Key, Compare, Alloc>::const_iterator   t_last_l = lhs.end();
        typename set<Key, Compare, Alloc>::const_iterator   t_last_r = rhs.end();
        typename set<Key, Compare, Alloc>::const_iterator   j = rhs.begin();
        for (typename set<Key, Compare, Alloc>::const_iterator i = lhs.begin(); i != t_last_l; ++i, ++j)
            if (j == t_last_r || *j < *i)
                return (false);
            else if (*i < *j)
                return (true);
        return (j != t_last_r);
    }

    template <class Key, class Compare, class Alloc>
    bool    operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        return (!(rhs < lhs));
    }

    template <class Key, class Compare, class Alloc>
    bool    operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        return (rhs < lhs);
    }

    template <class Key, class Compare, class Alloc>
    bool    operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }

    template <class Key, class Compare, class Alloc>
    void    swap(set<Key, Compare, Alloc>& lhs, set<Key, Compare, Alloc>& rhs)
    {
        lhs.swap(rhs);
    }

}

#endif