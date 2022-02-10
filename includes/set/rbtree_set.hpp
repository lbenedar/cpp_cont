/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_set.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:17:15 by lbenedar          #+#    #+#             */
/*   Updated: 2022/01/24 16:07:48 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_SET_HPP
# define RB_TREE_SET_HPP

#include "pair.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template <class T, class Compare, class Alloc>
    class rb_tree_set
    {
    public:
        typedef T                   value_type;
        typedef Compare             key_compare;
        typedef Alloc               allocator_type;
        typedef value_type&         reference;
        typedef value_type*         pointer;
        typedef const value_type&   const_reference;
        typedef std::size_t         size_type;

        struct  node_type{
            node_type();
            node_type(const T &val);
            node_type(const node_type&);
            node_type&  operator=(const node_type&);

            node_type           *parent;
            node_type           *child[2];
            bool                is_red;
            T                   value;
        };

        typedef typename allocator_type::template rebind<node_type>::other   allocator_node_type;

        class const_iterator;

        class iterator
        {
        public:
            typedef std::ptrdiff_t              difference_type;
            typedef T                           value_type;
            typedef T*                          pointer;
            typedef T&                          reference;
            typedef bidirectional_iterator_tag  iterator_category;

            iterator() : i_node(NULL) {};
            iterator(node_type *ptr) : i_node(ptr) {};
            iterator(const iterator& other) : i_node(other.i_node) {};
            iterator(const const_iterator& other) : i_node(const_cast<node_type*>(other.get_ptr())) {};

            ~iterator() {};

            iterator&   operator=(const iterator&);
            iterator&   operator=(const const_iterator&);

            node_type   *get_ptr() const;

            iterator&   operator++();
            iterator    operator++(int);
            iterator&   operator--();
            iterator    operator--(int);
            bool        operator==(const iterator& other) const;
            bool        operator!=(const iterator& other) const;
            bool        operator==(const const_iterator& other) const;
            bool        operator!=(const const_iterator& other) const;
            
            reference   operator*() const;
            pointer     operator->() const;

        private:
            node_type  *i_node;
        };

        class const_iterator
        {
        public:
            typedef std::ptrdiff_t              difference_type;
            typedef const T                     value_type;
            typedef const T*                    pointer;
            typedef const T&                    reference;
            typedef bidirectional_iterator_tag  iterator_category;

            const_iterator() : ci_node(NULL) {};
            const_iterator(const node_type *ptr) : ci_node(ptr) {};
            const_iterator(const const_iterator& other) : ci_node(other.ci_node) {};
            const_iterator(const iterator& other) : ci_node(other.get_ptr()) {};
            ~const_iterator() {};

            const_iterator&     operator=(const const_iterator&);
            const_iterator&     operator=(const iterator&);

            const node_type     *get_ptr() const;

            const_iterator&     operator++();
            const_iterator      operator++(int);
            const_iterator&     operator--();
            const_iterator      operator--(int);
            bool                operator==(const const_iterator& other) const;
            bool                operator!=(const const_iterator& other) const;
            bool                operator==(const iterator& other) const;
            bool                operator!=(const iterator& other) const;
            
            reference             operator*() const;
            pointer               operator->() const;

        private:
            const node_type  *ci_node;
        };

        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

        rb_tree_set(const key_compare& comp, const allocator_type& alloc);
        rb_tree_set(const rb_tree_set& other);
        ~rb_tree_set();

        rb_tree_set&    operator=(const rb_tree_set&);

        iterator        begin();
        const_iterator  begin() const;
        iterator        end();
        const_iterator  end() const;

        pair<iterator, bool>    insert_node(node_type *);
        pair<iterator, bool>    insert_node(iterator, node_type *);
        iterator                find_node(const value_type &k);
        const_iterator          find_node(const value_type &k) const;
        void                    erase(iterator);
        void                    copy_tree(node_type*& current, node_type* parent, node_type* curr_copy);
        void                    clear();
        void                    dealloc_node(node_type* node);
        void                    swap(rb_tree_set& x);

        iterator                                lower_bound(const value_type&);
        const_iterator                          lower_bound(const value_type&) const;
        iterator                                upper_bound(const value_type&);
        const_iterator                          upper_bound(const value_type&) const;
        pair<iterator, iterator>                equal_range(const value_type &k);
        pair<const_iterator, const_iterator>    equal_range(const value_type &k) const;

        size_type               size() const;
        key_compare             key_comp() const;
        allocator_type          get_allocator() const;
        allocator_node_type     get_alloc_node() const;

    private:
        enum    direction{
            RIGHT = 0,
            LEFT = 1
        };

        node_type*                      get_grandparent(node_type *);
        node_type*                      get_uncle(node_type *);
        pair<node_type*, node_type*>    bst_delete_node(node_type *);
        pair<node_type*, node_type*>    bst_delete_w_children(node_type *, size_type);
        void                            setup_for_case(node_type *, pair<node_type*, node_type*> &);
        void                            choose_erase_case(node_type *x, node_type *x_sibling);
        void                            erase_case_1(node_type *x, node_type* w);
        void                            erase_case_2(node_type *x, node_type* w);
        void                            erase_case_3(node_type *x, node_type* w);
        void                            erase_case_4(node_type *x, node_type* w);
        void                            rotate(node_type *node, direction dir);
        void                            balance_tree(node_type *);
        void                            rotate_tree(node_type *);
        void                            set_loop_children();
        void                            set_loop_children(node_type* node);
        void                            clear_tree(node_type* other);

        node_type           *loop_root;
        node_type           *root;
        allocator_node_type t_alloc_node;
        allocator_type      t_alloc_pair;
        key_compare         t_comp;
        size_type           t_size;

    };

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator&   rb_tree_set<T, Compare, Alloc>::iterator::operator=(const iterator &other)
    {
        if (this == &other)
            return (*this);
        i_node = other.i_node;
        return (*this);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator&   rb_tree_set<T, Compare, Alloc>::iterator::operator=(const const_iterator &other)
    {
        if (this == &other)
            return (*this);
        i_node = other.get_ptr();
        return (*this);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::node_type   *rb_tree_set<T, Compare, Alloc>::iterator::get_ptr() const
    {
        return (i_node);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator&   rb_tree_set<T, Compare, Alloc>::iterator::operator++()
    {
        if (!i_node->child[RIGHT])
        {
            while (i_node->parent && i_node->parent->child[RIGHT] == i_node)
                i_node = i_node->parent;
            if (i_node->parent)
                i_node = i_node->parent;
        }
        else
        {
            i_node = i_node->child[RIGHT];
            while (i_node->child[LEFT])
                i_node = i_node->child[LEFT];
        }
        return (*this);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator   rb_tree_set<T, Compare, Alloc>::iterator::operator++(int)
    {
        iterator    temp = *this;
        
        ++(*this);
        return (temp);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator&   rb_tree_set<T, Compare, Alloc>::iterator::operator--()
    {
        if (!i_node->child[LEFT])
        {
            while (i_node->parent && i_node->parent->child[LEFT] == i_node)
                i_node = i_node->parent;
            if (i_node->parent)
                i_node = i_node->parent;
        }
        else
        {
            i_node = i_node->child[LEFT];
            while (i_node->child[RIGHT])
                i_node = i_node->child[RIGHT];
        }
        return (*this);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator   rb_tree_set<T, Compare, Alloc>::iterator::operator--(int)
    {
        iterator    temp = *this;
        
        --(*this);
        return (temp);
    }

    template <class T, class Compare, class Alloc>
    bool        rb_tree_set<T, Compare, Alloc>::iterator::operator==(const iterator& other) const
    {
        if (i_node == other.i_node)
            return (true);
        return (false);
    }

    template <class T, class Compare, class Alloc>
    bool        rb_tree_set<T, Compare, Alloc>::iterator::operator!=(const iterator& other) const
    {
        return (!(*this == other));
    }

    template <class T, class Compare, class Alloc>
    bool        rb_tree_set<T, Compare, Alloc>::iterator::operator==(const const_iterator& other) const
    {
        if (i_node == other.get_ptr())
            return (true);
        return (false);
    }

    template <class T, class Compare, class Alloc>
    bool        rb_tree_set<T, Compare, Alloc>::iterator::operator!=(const const_iterator& other) const
    {
        return (!(*this == other));
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::reference   rb_tree_set<T, Compare, Alloc>::iterator::operator*() const
    {
        return (i_node->value);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::pointer   rb_tree_set<T, Compare, Alloc>::iterator::operator->() const
    {
        return (&(i_node->value));
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator&   rb_tree_set<T, Compare, Alloc>::const_iterator::operator=(const const_iterator &other)
    {
        if (this == &other)
            return (*this);
        ci_node = other.ci_node;
        return (*this);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator&   rb_tree_set<T, Compare, Alloc>::const_iterator::operator=(const iterator &other)
    {
        if (this == &other)
            return (*this);
        ci_node = other.get_ptr();
        return (*this);
    }

    template <class T, class Compare, class Alloc>
    const typename rb_tree_set<T, Compare, Alloc>::node_type   *rb_tree_set<T, Compare, Alloc>::const_iterator::get_ptr() const
    {
        return (ci_node);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator&   rb_tree_set<T, Compare, Alloc>::const_iterator::operator++()
    {
        if (!ci_node->child[RIGHT])
        {
            while (ci_node->parent && ci_node->parent->child[RIGHT] == ci_node)
                ci_node = ci_node->parent;
            if (ci_node->parent)
                ci_node = ci_node->parent;
        }
        else
        {
            ci_node = ci_node->child[RIGHT];
            while (ci_node->child[LEFT])
                ci_node = ci_node->child[LEFT];
        }
        return (*this);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator   rb_tree_set<T, Compare, Alloc>::const_iterator::operator++(int)
    {
        const_iterator    temp = *this;
        
        ++(*this);
        return (temp);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator&   rb_tree_set<T, Compare, Alloc>::const_iterator::operator--()
    {
        if (!ci_node->child[LEFT])
        {
            while (ci_node->parent && ci_node->parent->child[LEFT] == ci_node)
                ci_node = ci_node->parent;
            if (ci_node->parent)
                ci_node = ci_node->parent;
        }
        else
        {
            ci_node = ci_node->child[LEFT];
            while (ci_node->child[RIGHT])
                ci_node = ci_node->child[RIGHT];
        }
        return (*this);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator   rb_tree_set<T, Compare, Alloc>::const_iterator::operator--(int)
    {
        const_iterator    temp = *this;
        
        --(*this);
        return (temp);
    }

    template <class T, class Compare, class Alloc>
    bool        rb_tree_set<T, Compare, Alloc>::const_iterator::operator==(const const_iterator& other) const
    {
        if (ci_node == other.ci_node)
            return (true);
        return (false);
    }

    template <class T, class Compare, class Alloc>
    bool        rb_tree_set<T, Compare, Alloc>::const_iterator::operator!=(const const_iterator& other) const
    {
        return (!(*this == other));   
    }

    template <class T, class Compare, class Alloc>
    bool        rb_tree_set<T, Compare, Alloc>::const_iterator::operator==(const iterator& other) const
    {
        if (ci_node == other.get_ptr())
            return (true);
        return (false);
    }

    template <class T, class Compare, class Alloc>
    bool        rb_tree_set<T, Compare, Alloc>::const_iterator::operator!=(const iterator& other) const
    {
        return (!(*this == other));   
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator::reference   rb_tree_set<T, Compare, Alloc>::const_iterator::operator*() const
    {
        return (ci_node->value);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator::pointer   rb_tree_set<T, Compare, Alloc>::const_iterator::operator->() const
    {
        return (&(ci_node->value));
    }

    template <class T, class Compare, class Alloc>
    rb_tree_set<T, Compare, Alloc>::node_type::node_type() : value(value_type())
    {
        parent = NULL;
        child[LEFT] = NULL;
        child[RIGHT] = NULL;
        is_red = true;
    }

    template <class T, class Compare, class Alloc>
    rb_tree_set<T, Compare, Alloc>::node_type::node_type(const T &val) : value(val)

    {
        parent = NULL;
        child[LEFT] = NULL;
        child[RIGHT] = NULL;
        is_red = true;
    }

    template <class T, class Compare, class Alloc>
    rb_tree_set<T, Compare, Alloc>::node_type::node_type(const node_type& other) : value(other.value)
    {
        parent = NULL;
        child[LEFT] = NULL;
        child[RIGHT] = NULL;
        is_red = other.is_red;
    }

    template <class T, class Compare, class Alloc>
    rb_tree_set<T, Compare, Alloc>::rb_tree_set(const key_compare& comp, const allocator_type& alloc) : t_comp(comp)
    {
        t_alloc_pair = alloc;
        t_alloc_node = allocator_node_type();
        t_comp = comp;
        loop_root = t_alloc_node.allocate(1);
        t_alloc_node.construct(loop_root, node_type());
        t_size = 0;
        root = NULL;
    }

    template <class T, class Compare, class Alloc>
    rb_tree_set<T, Compare, Alloc>::rb_tree_set(const rb_tree_set& other) : t_comp(other.t_comp)
    {
        t_alloc_pair = other.t_alloc_pair;
        t_alloc_node = other.t_alloc_node;
        
        *this = other;
    }

    template <class T, class Compare, class Alloc>
    rb_tree_set<T, Compare, Alloc>& rb_tree_set<T, Compare, Alloc>::operator=(const rb_tree_set& other)
    {
        if (this == &other)
            return (*this);
        clear();
        loop_root = t_alloc_node.allocate(1);
        t_alloc_node.construct(loop_root, node_type());
        copy_tree(root, loop_root, other.root);
        t_size = other.t_size;
        loop_root->parent = NULL;
        set_loop_children();
        return (*this);
    }

    template <class T, class Compare, class Alloc>
    rb_tree_set<T, Compare, Alloc>::~rb_tree_set()
    {
        clear();
        dealloc_node(loop_root);
        loop_root = NULL;
        root = NULL;
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator   rb_tree_set<T, Compare, Alloc>::begin()
    {
        if (root)
            return (iterator(loop_root->child[RIGHT]));
        return (iterator(loop_root));
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator  rb_tree_set<T, Compare, Alloc>::begin() const
    {
        if (root)
            return (const_iterator(loop_root->child[RIGHT]));
        return (const_iterator(loop_root));    
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator   rb_tree_set<T, Compare, Alloc>::end()
    {
        return (iterator(loop_root));
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator  rb_tree_set<T, Compare, Alloc>::end() const
    {
        return (const_iterator(loop_root));
    }

    template <class T, class Compare, class Alloc>
    void rb_tree_set<T, Compare, Alloc>::clear()
    {
        if (root)
        {
            clear_tree(root);
            root = NULL;
            t_size = 0;
        }
    }

    template <class T, class Compare, class Alloc>
    void rb_tree_set<T, Compare, Alloc>::clear_tree(node_type *node)
    {
        if (node->child[LEFT])
            clear_tree(node->child[LEFT]);
        if (node->child[RIGHT])
            clear_tree(node->child[RIGHT]);
        dealloc_node(node);
    }

    template <class T, class Compare, class Alloc>
    void rb_tree_set<T, Compare, Alloc>::dealloc_node(node_type *node)
    {
        t_alloc_pair.destroy(&node->value);
        t_alloc_node.deallocate(node, 1);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::key_compare      rb_tree_set<T, Compare, Alloc>::key_comp() const
    {
        return (t_comp);
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::swap(rb_tree_set& x)
    {
        node_type   *temp_root = x.root;
        node_type   *temp_loop = x.loop_root;
        size_type   temp_size = x.t_size;
        
        x.root = root;
        x.loop_root = loop_root;
        x.t_size = t_size;

        root = temp_root;
        loop_root = temp_loop;
        t_size = temp_size;
    }

    template <class T, class Compare, class Alloc>
    void rb_tree_set<T, Compare, Alloc>::set_loop_children(node_type* node)
    {
        if (t_comp(node->value, loop_root->child[RIGHT]->value))
            loop_root->child[RIGHT] = node;
        else if (t_comp(loop_root->child[LEFT]->value, node->value))
            loop_root->child[LEFT] = node;
    }

    template <class T, class Compare, class Alloc>
    void rb_tree_set<T, Compare, Alloc>::set_loop_children()
    {
        if (!root)
        {
            loop_root->child[LEFT] = NULL;
            loop_root->child[RIGHT] = NULL;
            return ;
        }

        node_type* temp = root;
        while (temp->child[LEFT])
            temp = temp->child[LEFT];
        loop_root->child[RIGHT] = temp;
        temp = root;
        while (temp->child[RIGHT])
            temp = temp->child[RIGHT];
        loop_root->child[LEFT] = temp;
    }

    template <class T, class Compare, class Alloc>
    void rb_tree_set<T, Compare, Alloc>::copy_tree(node_type*& current, node_type* curr_parent, node_type* curr_copy)
    {
        if (!curr_copy)
            current = NULL;
        else
        {
            current = t_alloc_node.allocate(1);
            t_alloc_node.construct(current, *curr_copy);
            current->parent = curr_parent;
            copy_tree(current->child[LEFT], current, curr_copy->child[LEFT]);
            copy_tree(current->child[RIGHT], current, curr_copy->child[RIGHT]);
        }
    }


    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::node_type*   rb_tree_set<T, Compare, Alloc>::get_grandparent(node_type *node)
    {
        if (node && node->parent)
            return (node->parent->parent);
        else
            return (NULL);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::node_type*   rb_tree_set<T, Compare, Alloc>::get_uncle(node_type *node)
    {
        node_type   *temp = get_grandparent(node);
        if (!temp)
            return (NULL);
        if (node->parent == temp->child[LEFT])
            return (temp->child[RIGHT]);
        else
            return (temp->child[LEFT]);
    }

    template <class T, class Compare, class Alloc>
    pair<typename rb_tree_set<T, Compare, Alloc>::iterator, bool>    rb_tree_set<T, Compare, Alloc>::insert_node(node_type *node)
    {
        node_type   *t_node = root;
        if (!t_node)
        {
            node->is_red = 0;
            root = node;
            root->parent = loop_root;
            loop_root->parent = NULL;
            loop_root->child[LEFT] = root;
            loop_root->child[RIGHT] = root;
            ++t_size;
            return (ft::make_pair(iterator(root), true));
        }
        node_type   *t_parent = NULL;
        while (t_node)
        {
            if (t_node->value == node->value)
                return (ft::make_pair(iterator(t_node), false));
            t_parent = t_node;
            t_node = t_node->child[(int)t_comp(node->value, t_node->value)];
        }
        t_parent->child[(int)t_comp(node->value, t_parent->value)] = node;
        node->parent = t_parent;
        balance_tree(node);
        set_loop_children(node);
        ++t_size;
        return (ft::make_pair(iterator(node), true));
    }

    template <class T, class Compare, class Alloc>
    pair<typename rb_tree_set<T, Compare, Alloc>::iterator, bool>    rb_tree_set<T, Compare, Alloc>::insert_node(iterator pos, node_type *node)
    {
        if (pos != iterator(loop_root) && t_comp(*pos, node->value) && (!pos.get_ptr()->child[RIGHT]) &&
            ((++pos == iterator(loop_root)) || t_comp(node->value, *pos)))
        {
            --pos;
            pos.get_ptr()->child[RIGHT] = node;
            node->parent = pos.get_ptr();
            balance_tree(node);
            set_loop_children(node);
            ++t_size;
            return (ft::make_pair(iterator(node), true));
        }
        return (insert_node(node));
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::erase(iterator erase_it)
    {
        node_type*  erase_node = erase_it.get_ptr();
        pair<node_type*, node_type*> replace_parent = bst_delete_node(erase_node);

        if (erase_node != root || erase_node->child[LEFT] || erase_node->child[RIGHT])
            setup_for_case(erase_node, replace_parent);
        if (root == erase_node)
            root = replace_parent.first;
        dealloc_node(erase_node);
        set_loop_children();
        --t_size;
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::setup_for_case(node_type *erase_node, pair<node_type*, node_type*> &replace_parent)
    {
        node_type *x = NULL;
        node_type *x_sibling = NULL;

        if (replace_parent.second)
        {
            if (replace_parent.first == replace_parent.second)
            {
                x = replace_parent.second->child[RIGHT];
                x_sibling = replace_parent.second->child[LEFT];
            }
            else
            {
                x = replace_parent.second->child[LEFT];
                x_sibling = replace_parent.second->child[RIGHT];
            }
        }
        else if (!replace_parent.first)
            x_sibling = erase_node->parent->child[static_cast<size_type>(!!erase_node->parent->child[LEFT])];
        
        if (!erase_node->is_red && replace_parent.first && replace_parent.first->is_red)
            replace_parent.first->is_red = false;
        else if (!erase_node->is_red && (!replace_parent.first || !replace_parent.first->is_red))
            choose_erase_case(x, x_sibling);
        else if (erase_node->is_red && replace_parent.first && !replace_parent.first->is_red)
        {
            replace_parent.first->is_red = true;
            choose_erase_case(x, x_sibling);
        }
    }

    template <class T, class Compare, class Alloc>
    pair<typename rb_tree_set<T, Compare, Alloc>::node_type*, typename rb_tree_set<T, Compare, Alloc>::node_type*>
        rb_tree_set<T, Compare, Alloc>::bst_delete_node(node_type *node)
    {
        size_type   parent_dir = static_cast<size_type>(node->parent->child[LEFT] == node);
        node_type   *temp_x = NULL;

        if (!node->child[LEFT])
        {
            node->parent->child[parent_dir] = node->child[RIGHT];
            if (node->child[RIGHT])
                node->child[RIGHT]->parent = node->parent;
        }
        else if (!node->child[RIGHT])
        {
            node->parent->child[parent_dir] = node->child[LEFT];
            if (node->child[LEFT])
                node->child[LEFT]->parent = node->parent;
        }
        else
            return (bst_delete_w_children(node, parent_dir));
        return (ft::make_pair(node->parent->child[parent_dir], temp_x));
    }

    template <class T, class Compare, class Alloc>
    pair<typename rb_tree_set<T, Compare, Alloc>::node_type*, typename rb_tree_set<T, Compare, Alloc>::node_type*>
        rb_tree_set<T, Compare, Alloc>::bst_delete_w_children(node_type *node, size_type parent_dir)
    {
        node_type *temp_y = node->child[RIGHT];
        node_type *temp_x = NULL;

        while (temp_y->child[LEFT])
            temp_y = temp_y->child[LEFT];
        temp_x = temp_y->child[RIGHT];
        if (temp_y->parent != node)
        {
            temp_y->parent->child[LEFT] = temp_x;
            if (temp_x)
                temp_x->parent = temp_y->parent;
            temp_x = temp_y->parent;
        }
        else
        {
            temp_y->parent->child[RIGHT] = temp_x;
            temp_x = temp_y;
        }
        
        node->parent->child[parent_dir] = temp_y;
        temp_y->parent = node->parent;
        if (node->child[LEFT])
            node->child[LEFT]->parent = temp_y;
        if (node->child[RIGHT])
            node->child[RIGHT]->parent = temp_y;
        temp_y->child[LEFT] = node->child[LEFT];
        temp_y->child[RIGHT] = node->child[RIGHT];
        return (ft::make_pair(node->parent->child[parent_dir], temp_x));
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::choose_erase_case(node_type *x, node_type *x_sibling)
    {
        if (x && x->is_red)
            x->is_red = false;
        else if (x_sibling && x_sibling->is_red)
            erase_case_1(x, x_sibling);
        else
        {
            if (!x_sibling || ((!x_sibling->child[LEFT] || !x_sibling->child[LEFT]->is_red) && 
                (!x_sibling->child[RIGHT] || !x_sibling->child[RIGHT]->is_red)))
                erase_case_2(x, x_sibling);
            else if ((x_sibling->parent->child[LEFT] == x && x_sibling->child[RIGHT] && x_sibling->child[RIGHT]->is_red) ||
                       (x_sibling->parent->child[RIGHT] == x && x_sibling->child[LEFT] && x_sibling->child[LEFT]->is_red))
                erase_case_3(x, x_sibling);
            else
                erase_case_4(x, x_sibling);
        }
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::erase_case_1(node_type *x, node_type* w)
    {
        node_type *parent = w->parent;
        w->is_red = false;
        parent->is_red = true;
        if (parent->child[LEFT] == x)
        {
            rotate(parent, LEFT);
            w = parent->child[RIGHT];
        }
        else
        {
            rotate(parent, RIGHT);
            w = parent->child[LEFT];
        }
        choose_erase_case(x, w);
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::erase_case_2(node_type *x, node_type* w)
    {
        node_type *parent = w->parent;
        w->is_red = true;
        x = parent;
        if (x->is_red)
            x->is_red = false;
        else if (x->parent != loop_root)
            choose_erase_case(x, get_uncle(w));
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::erase_case_3(node_type *x, node_type* w)
    {
        node_type *parent = w->parent;

        w->is_red = parent->is_red;
        parent->is_red = false;
        if (parent->child[LEFT] == x)
        {
            w->child[RIGHT]->is_red = false;
            rotate(parent, LEFT);
        }
        else
        {
            w->child[LEFT]->is_red = false;
            rotate(parent, RIGHT);
        }
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::erase_case_4(node_type *x, node_type* w)
    {
        node_type *parent = w->parent;
        w->is_red = true;
        if (parent->child[LEFT] == x)
        {
            w->child[LEFT]->is_red = false;
            rotate(w, RIGHT);
            w = parent->child[RIGHT];
        }
        else
        {
            w->child[RIGHT]->is_red = false;
            rotate(w, LEFT);
            w = parent->child[LEFT];
        }
        erase_case_3(x, w);
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::rotate(node_type *node, direction dir)
    {
        node_type   *node_dir = node->child[!dir];
        node_type   *parent = node->parent;

        node->child[!dir] = node_dir->child[dir];
        if (node_dir->child[dir])
            node_dir->child[dir]->parent = node;
        node->parent = node_dir;
        node_dir->parent = parent;
        node_dir->child[dir] = node;
        
        if (node == root)
            root = node_dir;
        else
        {
            if (parent->child[LEFT] == node)
                parent->child[LEFT] = node_dir;
            else
                parent->child[RIGHT] = node_dir;
        }
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::rotate_tree(node_type *node)
    {
        node_type   *grandparent = get_grandparent(node);
        if (node == node->parent->child[RIGHT] && node->parent == grandparent->child[LEFT])
        {
            rotate(node->parent, LEFT);
            grandparent->child[LEFT] = node;
            node = node->child[LEFT];
        }
        else if (node == node->parent->child[LEFT] && node->parent == grandparent->child[RIGHT])
        {
            rotate(node->parent, RIGHT);
            grandparent->child[RIGHT] = node;
            node = node->child[RIGHT];
        }
        
        grandparent = get_grandparent(node);
        grandparent->is_red = true;
        node->parent->is_red = false;
        if (node->parent == grandparent->child[LEFT])
            rotate(grandparent, RIGHT);
        else
            rotate(grandparent, LEFT);
    }

    template <class T, class Compare, class Alloc>
    void    rb_tree_set<T, Compare, Alloc>::balance_tree(node_type *node)
    {
        if (node->parent->is_red)
        {
            node_type   *uncle = get_uncle(node);
            if (!uncle || !uncle->is_red)
                rotate_tree(node);
            else
            {
                node_type   *grandparent = get_grandparent(node);
                uncle->is_red = false;
                node->parent->is_red = false; 
                if (root != grandparent)
                {
                    grandparent->is_red = true;
                    balance_tree(grandparent);
                }
            }
        }
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator  rb_tree_set<T, Compare, Alloc>::find_node(const value_type &k)
    {
        node_type   *temp = root;
        while (temp)
        {
            if (temp->value == k)
                return (iterator(temp));
            temp = temp->child[(int)t_comp(k, temp->value)];
        }
        return (iterator(loop_root));
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator    rb_tree_set<T, Compare, Alloc>::find_node(const value_type &k) const
    {
        const node_type   *temp = root;
        while (temp)
        {
            if (temp->value == k)
                return (const_iterator(temp));
            temp = temp->child[(int)t_comp(k, temp->value)];
        }
        return (const_iterator(loop_root));
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator  rb_tree_set<T, Compare, Alloc>::lower_bound(const value_type& k)
    {
        node_type   *temp = root;
        node_type   *before_temp = NULL;
        while (temp)
        {
            if (temp->value == k)
                return (iterator(temp));
            before_temp = temp;
            temp = temp->child[(int)t_comp(k, temp->value)];
        }
        if (t_comp(k, before_temp->value))
            return (iterator(before_temp));
        return (++iterator(before_temp));
    }
        
    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator    rb_tree_set<T, Compare, Alloc>::lower_bound(const value_type& k) const
    {
        const node_type   *temp = root;
        const node_type   *before_temp = NULL;
        while (temp)
        {
            if (temp->value == k)
                return (const_iterator(temp));
            before_temp = temp;
            temp = temp->child[(int)t_comp(k, temp->value)];
        }
        if (t_comp(k, before_temp->value))
            return (const_iterator(before_temp));
        return (++const_iterator(before_temp));
    }
        
    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::iterator  rb_tree_set<T, Compare, Alloc>::upper_bound(const value_type& k)
    {
        node_type   *temp = root;
        node_type   *before_temp = NULL;
        while (temp)
        {
            if (temp->value == k)
                return (++iterator(temp));
            before_temp = temp;
            temp = temp->child[(int)t_comp(k, temp->value)];
        }
        if (t_comp(k, before_temp->value))
            return (iterator(before_temp));
        return (++iterator(before_temp));
    }
        
    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::const_iterator    rb_tree_set<T, Compare, Alloc>::upper_bound(const value_type& k) const
    {
        const node_type   *temp = root;
        const node_type   *before_temp = NULL;
        while (temp)
        {
            if (temp->value == k)
                return (++const_iterator(temp));
            before_temp = temp;
            temp = temp->child[(int)t_comp(k, temp->value)];
        }
        if (t_comp(k, before_temp->value))
            return (const_iterator(before_temp));
        return (++const_iterator(before_temp));
    }
        
    template <class T, class Compare, class Alloc>
    pair<typename rb_tree_set<T, Compare, Alloc>::iterator,
    typename rb_tree_set<T, Compare, Alloc>::iterator>         rb_tree_set<T, Compare, Alloc>::equal_range(const value_type &k)
    {
        return (ft::make_pair(lower_bound(k), upper_bound(k)));
    }
        
    template <class T, class Compare, class Alloc>
    pair<typename rb_tree_set<T, Compare, Alloc>::const_iterator,
    typename rb_tree_set<T, Compare, Alloc>::const_iterator>    rb_tree_set<T, Compare, Alloc>::equal_range(const value_type &k) const
    {
        return (ft::make_pair(lower_bound(k), upper_bound(k)));
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::size_type     rb_tree_set<T, Compare, Alloc>::size() const
    {
        return (t_size);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::allocator_type    rb_tree_set<T, Compare, Alloc>::get_allocator() const
    {
        return (t_alloc_pair);
    }

    template <class T, class Compare, class Alloc>
    typename rb_tree_set<T, Compare, Alloc>::allocator_node_type     rb_tree_set<T, Compare, Alloc>::get_alloc_node() const
    {
        return (t_alloc_node);
    }
}

#endif