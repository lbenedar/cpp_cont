/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:00:41 by lbenedar          #+#    #+#             */
/*   Updated: 2022/02/09 16:21:12 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"
#include "time.h"
#include <typeinfo>
#ifdef STD1
#include <map>
#include <stack>
#include <vector>
#include <set>
namespace ft = std;
#else
#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include "set.hpp"
#endif


int main()
{
#ifdef STD
    std::cout << "std" << std::endl;
#else
    std::cout << "ft" << std::endl;
#endif

    std::pair<int, int> a;
    std::cout << a.first << " " << a.second << std::endl;

    clock_t t1, t2;
    t1 = clock();

    ft::vector<int> n;

    for (int i = 0; i < 100; ++i)
        n.push_back(i);

    ft::vector<int> k(3, 7);

    std::cout << "2nd element of n is " << n.at(1) << ", 4th element of n is " << n.at(3) << std::endl;

    try
    {
        n.at(10);
        //std::cerr << "Error: 10th element doesn't exist" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Check on exception for \"at\" is passed" << std::endl;
    }

    std::cout << "k size - " << k.size() << ", k capacity - " << k.capacity() << std::endl;

    ft::vector<int> m(n);

    std::cout << "value of 2nd element in n is " << n.at(1) << ", value of 2nd element in m is " << m.at(1) << std::endl;
    std::cout << "address of 2nd element in n is " << &n.at(1) << ", address of 2nd element in m is " << &m.at(1) << std::endl;

    ft::vector<int> l(k.begin(), k.end());

    std::cout << "value of 2nd element in n is " << k.at(1) << ", value of 2nd element in m is " << l.at(1) << std::endl;
    std::cout << "address of 2nd element in n is " << &k.at(1) << ", address of 2nd element in m is " << &l.at(1) << std::endl;

    l = m;

    std::cout << "value of 2nd element in n is " << m.at(1) << ", value of 2nd element in m is " << l.at(1) << std::endl;
    std::cout << "address of 2nd element in n is " << &m.at(1) << ", address of 2nd element in m is " << &l.at(1) << std::endl;

    std::cout << std::endl;

    std::cout << "Test of vector functions" << std::endl;

    {
        std::cout << "size(): " << n.size() << ", max_size(): " << n.max_size() << std::endl;
        std::cout << "capacity(): " << n.capacity() << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "clear()" << std::endl;
        n.clear();
        std::cout << "size after clear(): " << n.size() << ", capacity after clear(): " << n.capacity() << std::endl;
        if (n.empty())
            std::cout << "n is empty" << std::endl;
        else
            std::cout << "n is not empty" << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Added 4 elements with push_back(). Should be in that order {2, 6, 1, 8}" << std::endl;
        n.push_back(2);
        n.push_back(6);
        n.push_back(1);
        n.push_back(8);
        if (n.empty())
            std::cout << "n is empty" << std::endl;
        else
            std::cout << "n is not empty" << std::endl;
        std::cout << "Check element with front(): " << n.front() << ", check element with back(): " << n.back() << std::endl;
        std::cout << "Check element with index 1 ([]): " << n[1] << ", check element with index 2 (at()): " << n.at(2) << std::endl;
        std::cout << "Check size: " << n.size() << ", check capacity: " << n.capacity() << std::endl;
        std::cout << std::endl;
    }

    {
        n.pop_back();
        n.pop_back();
        std::cout << "Remove 2 elements with pop_back(). Should be in that order {2, 6}" << std::endl;
        std::cout << "Check element with front(): " << n.front() << ", check element with back(): " << n.back() << std::endl;
        std::cout << "Check element with index 0 ([]): " << n[0] << ", check element with index 1 (at()): " << n.at(1) << std::endl;
        std::cout << "Check size: " << n.size() << ", check capacity: " << n.capacity() << std::endl;
        std::cout << std::endl;
    }

    ft::vector<int> test(3, 3);

    {
        std::cout << "Swap 2 vectors. Should be {3, 3, 3} in n and {2, 6} in test" << std::endl;
        test.swap(n);
        std::cout << "size of test is " << test.size() << ", size of n is " << n.size() << std::endl;
        std::cout << "capacity of test is " << test.capacity() << ", capacity of n is " << n.capacity() << std::endl;
        std::cout << "elements of test: " << std::endl;
        for (ft::vector<int>::iterator i = test.begin(); i < test.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check resize() with n greater than container capacity" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();
        n.resize(10, 4);
        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check resize() with n greater than container size" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();
        n.resize(14, 5);
        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check resize() with n smaller than container size" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();
        n.resize(6, 1);
        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check reserve() with n greater than container capacity" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();
        n.reserve(21);
        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check reserve() with n smaller than container capacity" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();
        n.reserve(5);
        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check assign(size_type, value_type&) with n smaller than container capacity" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();
        n.assign(5, 10);
        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check assign(size_type, value_type&) with n greater than container capacity" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();
        n.assign(48, 10);
        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check assign(iterator, iterator)" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();
        n.assign(k.begin(), k.end());
        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        ft::vector<int> h;
        n = h;
    }

    {
        std::cout << "Check insert(iterator, val)" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();

        n.insert(n.begin(), 2);
        n.insert(n.end(), 3);
        n.insert(n.end() - 1, 7);

        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check erase(iterator)" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();
        
        n.erase(n.begin());
        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check insert(iterator, size_type, val)" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();

        n.insert(n.begin(), 2, 5);        
        n.insert(n.end(), 3, 7);
        n.insert(n.end() - 1, 1, 9);
        n.insert(n.end() - 2, 0, 11);

        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check erase(iterator, iterator)" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();
        
        n.erase(n.begin(), n.end() - 5); // {3 7 7 9 7}
        n.erase(n.end() - 2, n.end() - 1); // {3 7 7 7}
        
        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check insert(iterator, iterator, iterator)" << std::endl;
        size_t t_size = n.size();
        size_t t_cap = n.capacity();

        n.insert(n.begin(), k.begin(), k.end()); // {7, 7, 7} -> {7 7 7 3 7 7 7}
        n.insert(n.end(), m.begin(), m.begin() + 5); // {0, 1, 2, 3, 4} -> {7 7 7 3 7 7 7 0 1 2 3 4}
        n.insert(n.begin() + 6, test.begin(), test.end()); // {2, 6} -> {7 7 7 3 7 7 2 6 7 0 1 2 3 4}

        std::cout << "size of n is " << n.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "capacity of n is " << n.capacity() << "(was " << t_cap << ")" << std::endl;
        std::cout << "elements of n: " << std::endl;
        for (ft::vector<int>::iterator i = n.begin(); i < n.end(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check reverse iterator" << std::endl;
        for (ft::vector<int>::reverse_iterator i = n.rbegin(); i < n.rend(); ++i)
            std::cout << *i << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check compare operators for iterator and const_iterator" << std::endl;
        if (n.begin() < n.end())
            std::cout << "n.begin() < n.end()" << std::endl;
        else
            std::cout << "n.begin() >= n.end()" << std::endl;
        if (n.begin() == n.end())
            std::cout << "n.begin() == n.end()" << std::endl;
        else
            std::cout << "n.begin() != n.end()" << std::endl;
        if (n.begin() != n.begin())
            std::cout << "n.begin() != n.begin()" << std::endl;
        else
            std::cout << "n.begin() == n.begin()" << std::endl;
        if (n.begin() + 1 <= n.begin())
            std::cout << "n.begin() + 1 <= n.begin()" << std::endl;
        else
            std::cout << "n.begin() + 1 > n.begin()" << std::endl;
        if (n.end() - 1 > n.end())
            std::cout << "n.end() - 1 > n.end()" << std::endl;
        else
            std::cout << "n.end() - 1 <= n.end()" << std::endl;
        if (n.end() >= n.begin())
            std::cout << "n.end() >= n.begin()" << std::endl;
        else
            std::cout << "n.end() < n.begin()" << std::endl;
        std::cout << std::endl;
    }
    
    {
        std::cout << "Check compare operators for vector" << std::endl;
        ft::vector<int> q(5, 3);
        ft::vector<int> w(3, 3);
        ft::vector<int> e(4, 3);
        ft::vector<int> r(6, 3);

        if (w < q)
            std::cout << "w < q" << std::endl;
        else
            std::cout << "w >= q" << std::endl;
        if (w == e)
            std::cout << "w == e" << std::endl;
        else
            std::cout << "w != e" << std::endl;
        if (e != e)
            std::cout << "e != e" << std::endl;
        else
            std::cout << "e == e" << std::endl;
        if (e <= q)
            std::cout << "e <= q" << std::endl;
        else
            std::cout << "e > q" << std::endl;
        if (r > e)
            std::cout << "r > e" << std::endl;
        else
            std::cout << "r <= e" << std::endl;
        if (r >= w)
            std::cout << "r >= w" << std::endl;
        else
            std::cout << "r < w" << std::endl;
        std::cout << std::endl;
    }

    {
        ft::stack<int, ft::vector<int> > k(n);
        
        std::cout << "Test of stack functions" << std::endl;

        std::cout << "result of top() function: " << k.top() << ", size of stack is " << k.size() << std::endl;

        for (int i = 0; i < 6; ++i)
            k.pop();

        std::cout << "result of top() function after 6 pop functions: " << k.top() << ", size of stack is " << k.size() << std::endl;
        
        for (int i = 0; i < 6; ++i)
            k.push(i);

        std::cout << "result of top() function after 6 push functions: " << k.top() << ", size of stack is " << k.size() << std::endl;
        std::cout << std::endl;

        if (k.empty())
            std::cout << "k is empty" << std::endl;
        else
            std::cout << "k is not empty" << std::endl;

        std::cout << "Remove all elements from stack with pop()" << std::endl;
        while (!k.empty())
            k.pop();

        if (k.empty())
            std::cout << "k is empty" << std::endl;
        else
            std::cout << "k is not empty" << std::endl;
        std::cout << std::endl;        


        std::cout << "Remove all elements from stack with pop()" << std::endl;
        
        ft::stack<int, ft::vector<int> > y(m);
        std::cout << "Check operator=() for stack" << std::endl;
        k = y;
        for (;!k.empty(); k.pop())
           std::cout <<  k.top() << std::endl;
        for (;!y.empty(); y.pop())
           std::cout <<  y.top() << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Test of map functions" << std::endl;

    ft::map<int, int> j;
     
    j.insert(ft::make_pair(5, 9));
    j.insert(ft::make_pair(7, 12));
    j.insert(ft::make_pair(8, 21));
    j.insert(ft::make_pair(11, 9));
    j.insert(ft::make_pair(13, 12));
    j.insert(ft::make_pair(15, 21));
    j.insert(ft::make_pair(17, 12));

    ft::map<int, int> ml(j);

    j.insert(ft::make_pair(22, 9));
    j.insert(ft::make_pair(27, 9));
    j.insert(ft::make_pair(3, 9));
    j.insert(ft::make_pair(1, 9));
    j.insert(--j.end(), ft::make_pair(29, 9));
    j.insert(j.find(8), ft::make_pair(9, 19));
    j.insert(ft::make_pair(6, 11));
    j.insert(ft::make_pair(25, 12));

    {
        std::cout << "size(): " << j.size() << ", max_size(): " << j.max_size() << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "clear()" << std::endl;
        std::cout << "size before clear(): " << j.size() << std::endl;
        j.clear();
        std::cout << "size after clear(): " << j.size() << std::endl;
        if (j.empty())
            std::cout << "n is empty" << std::endl;
        else
            std::cout << "n is not empty" << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Added 4 elements with insert(). Added in that order {2, 6, 1, 8}. Should be {1, 2, 6, 8}" << std::endl;
        j.insert(ft::make_pair(2, 2));
        j.insert(ft::make_pair(6, 6));
        j.insert(ft::make_pair(1, 1));
        j.insert(ft::make_pair(8, 8));
        if (j.empty())
            std::cout << "n is empty" << std::endl;
        else
            std::cout << "n is not empty" << std::endl;
        std::cout << "Check size: " << j.size() << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        
        std::cout << std::endl;
    }

    {
        j.erase(6);
        j.erase(2);
        std::cout << "Remove 2 elements (6 and 2) with erase(). Should be in that order {1, 8}" << std::endl;
        std::cout << "Check size: " << j.size() << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    ft::map<int, int> test_map(j);

    {
        std::cout << "Check copy construct with previous map. Should be {1, 8}" << std::endl;
        std::cout << "Check size: " << test_map.size() << std::endl;
        for (ft::map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Change/Add elements to test_map using []. Should be {1, 2, 5, 8, 9}" << std::endl;
        test_map[5] = 3;
        test_map[2] = 7;
        test_map[1] = 6;
        test_map[9] = 10;
        std::cout << "Check size: " << test_map.size() << std::endl;
        for (ft::map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Swap 2 maps. Should be {1, 2, 5, 8, 9} in j and {1, 8} in test_map"  << std::endl;
        ft::swap(test_map, j);
        std::cout << "Check size j and values of j: " << j.size() << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Check size of test_map: " << test_map.size() << std::endl;
        for (ft::map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;
        
    }

    {
        std::cout << "Check operator= for j with empty map"  << std::endl;
        ft::map<int, int> zero_j;
        j = zero_j;
        std::cout << "size of j is " << j.size() << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value:" << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check range construct with test_map"  << std::endl;
        ft::map<int, int> range_const(test_map.begin(), test_map.end());
        std::cout << "Check size of range_const: " << test_map.size() << std::endl;
        for (ft::map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check insert(val)" << std::endl;

        size_t t_size = j.size();

        ft::pair<ft::map<int, int>::iterator, bool> ret = j.insert(ft::make_pair(15, 2));

        std::cout << "size of j is " << j.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "returned value is: " << std::endl;
        std::cout << "Key: " << ret.first->first << " | Value: " << ret.first->second << " | Is_inserted" << ret.second << std::endl;
        std::cout << "elements of j: " << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check insert(it, val)" << std::endl;

        size_t t_size = j.size();

        j.insert(++j.begin(), ft::make_pair(3, 3));

        std::cout << "size of j is " << j.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of j: " << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

        {
        std::cout << "Check insert(it, it). Insert all test_map" << std::endl;

        size_t t_size = j.size();

        test_map.insert(ft::make_pair(6, 3));
        test_map.insert(ft::make_pair(9, 6));
        test_map.insert(ft::make_pair(10, 2));
        
        j.insert(test_map.begin(), test_map.end());

        std::cout << "size of j is " << j.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of j: " << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }

        std::cout << "elements of test_map: " << std::endl;
        for (ft::map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check erase(iterator). Delete first in j" << std::endl;
        size_t t_size = j.size();
        
        j.erase(j.begin());
        std::cout << "size of j is " << j.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of j: " << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check erase(iterator, iterator). Delete should stay only 2 last elements" << std::endl;
        size_t t_size = j.size();
        
        j.erase(j.begin(), --(--j.end())); 
        
        std::cout << "size of j is " << j.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of j: " << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

        {
        std::cout << "Check erase(key). Delete 11 and 10. Should stay only 1 element" << std::endl;
        size_t t_size = j.size();
        
        j.erase(11);
        j.erase(10);
        
        std::cout << "size of j is " << j.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of j: " << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value:" << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check clear()." << std::endl;
        size_t t_size = j.size();
        
        j.clear();
        
        std::cout << "size of j is " << j.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of j: " << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check key_comp() and value_comp()." << std::endl;
        
        const std::type_info& key_info = typeid(j.key_comp());
        const std::type_info& value_info = typeid(j.value_comp());

        std::cout << "Key_comp type is " << key_info.name() << std::endl;
        std::cout << "Value_comp type is " << value_info.name() << std::endl;
        
        std::cout << std::endl;
    }

    {
        std::cout << "Check value_compare. Use pair for 5 and 7 keys" << std::endl;

        if (j.value_comp()(ft::make_pair(5, 7), ft::make_pair(7, 5)))
            std::cout << "Pair with 5 is less than 7" << std::endl;
        else
            std::cout << "Error" << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Insert values to map j" << std::endl;
        j.insert(ft::make_pair(22, 9));
        j.insert(ft::make_pair(27, 9));
        j.insert(ft::make_pair(3, 9));
        j.insert(ft::make_pair(1, 9));
        j.insert(--j.end(), ft::make_pair(29, 9));
        j.insert(j.find(8), ft::make_pair(9, 19));
        j.insert(ft::make_pair(6, 11));
        j.insert(ft::make_pair(25, 12));
        j.insert(ft::make_pair(5, 9));
        j.insert(ft::make_pair(7, 12));
        j.insert(ft::make_pair(8, 21));
        j.insert(ft::make_pair(11, 9));
        j.insert(ft::make_pair(13, 12));
        j.insert(ft::make_pair(15, 21));
        j.insert(ft::make_pair(17, 12));
        std::cout << "size of j is " << std::endl;
        std::cout << "elements of j: " << std::endl;
        for (ft::map<int, int>::iterator it = j.begin(); it != j.end(); ++it)
        {
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check find() with value 7, 10 and 3" << std::endl;

        ft::map<int, int>::iterator it = j.find(7);
        if (it != j.end())
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        else
            std::cout << "Hasn't find 7" << std::endl;
        it = j.find(10);
        if (it != j.end())
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        else
            std::cout << "Hasn't find 10" << std::endl;
        it = j.find(3);
        if (it != j.end())
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        else
            std::cout << "Hasn't find 3" << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check count() with value 13, 28 and 8" << std::endl;
        size_t num = j.count(13);
        std::cout << "Count with 13: " << num << std::endl;
        num = j.count(28);
        std::cout << "Count with 28: " << num << std::endl;
        num = j.count(8);
        std::cout << "Count with 8: " << num << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check lower_bound() with value 7, 10, 30" << std::endl;
        ft::map<int, int>::iterator it = j.lower_bound(7);
        if (it != j.end())
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        else
            std::cout << "Hasn't find lower_bound 7" << std::endl;
        it = j.lower_bound(10);
        if (it != j.end())
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        else
            std::cout << "Hasn't find lower_bound 10" << std::endl;
        it = j.lower_bound(30);
        if (it != j.end())
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        else
            std::cout << "Hasn't find lower_bound 30" << std::endl;
    }

    {
        std::cout << "Check upper_bound() with value 7, 10, 30" << std::endl;
        ft::map<int, int>::iterator it = j.upper_bound(7);
        if (it != j.end())
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        else
            std::cout << "Hasn't find upper_bound 7" << std::endl;
        it = j.upper_bound(10);
        if (it != j.end())
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        else
            std::cout << "Hasn't find upper_bound 10" << std::endl;
        it = j.upper_bound(30);
        if (it != j.end())
            std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
        else
            std::cout << "Hasn't find upper_bound 30" << std::endl;
    }

    {
        std::cout << "Check equal_range() with value 7, 10, 30" << std::endl;
        ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> eq_it = j.equal_range(7);
        if (eq_it.first != j.end())
            std::cout << "Key: " << eq_it.first->first << " | Value: " << eq_it.first->second << std::endl;
        else
            std::cout << "Hasn't find lower_bound 7" << std::endl;
        if (eq_it.second != j.end())
            std::cout << "Key: " << eq_it.second->first << " | Value: " << eq_it.second->second << std::endl;
        else
            std::cout << "Hasn't find upper_bound 7" << std::endl;
        eq_it = j.equal_range(10);
        if (eq_it.first != j.end())
            std::cout << "Key: " << eq_it.first->first << " | Value: " << eq_it.first->second << std::endl;
        else
            std::cout << "Hasn't find lower_bound 10" << std::endl;
        if (eq_it.second != j.end())
            std::cout << "Key: " << eq_it.second->first << " | Value: " << eq_it.second->second << std::endl;
        else
            std::cout << "Hasn't find upper_bound 10" << std::endl;
        eq_it = j.equal_range(30);
        if (eq_it.first != j.end())
            std::cout << "Key: " << eq_it.first->first << " | Value: " << eq_it.first->second << std::endl;
        else
            std::cout << "Hasn't find lower_bound 30" << std::endl;
        if (eq_it.second != j.end())
            std::cout << "Key: " << eq_it.second->first << " | Value: " << eq_it.second->second << std::endl;
        else
            std::cout << "Hasn't find upper_bound 30" << std::endl;

        std::cout << std::endl;
    }

    {
        std::cout << "Check reverse iterator" << std::endl;

        for (ft::map<int,int>::reverse_iterator rit = j.rbegin(); rit != j.rend(); ++rit)
            std::cout << "Key: " << rit->first << " | Value: " << rit->second << std::endl;
        
        std::cout << std::endl;
    }

    {
        std::cout << "Equal operator" << std::endl;
        ft::map<int,int> test_j(j);
        if (j == test_j)
            std::cout << "j is equal to test_j" << std::endl;
        else
            std::cout << "j isnt equal to test_j" << std::endl;
    }

    {
        std::cout << "Less operator" << std::endl;
        ft::map<int,int> test_j(j);
        if (j < test_j)
            std::cout << "j is less than test_j" << std::endl;
        else
            std::cout << "j isnt less than test_j" << std::endl;
        std::cout << "remove last element from j" << std::endl;
        j.erase(--j.end());
        if (j < test_j)
            std::cout << "j is less than test_j" << std::endl;
        else
            std::cout << "j isnt less than test_j" << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Test of set functions" << std::endl;

    ft::set<int> st;
     
    st.insert(5);
    st.insert(7);
    st.insert(8);
    st.insert(11);
    st.insert(13);
    st.insert(15);
    st.insert(17);

    ft::set<int> mls(st);

    st.insert(22);
    st.insert(27);
    st.insert(3);
    st.insert(1);
    st.insert(--st.end(), 29);
    st.insert(st.find(8), 9);
    st.insert(6);
    st.insert(25);

    {
        std::cout << "size(): " << st.size() << ", max_size(): " << st.max_size() << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "clear()" << std::endl;
        std::cout << "size before clear(): " << st.size() << std::endl;
        st.clear();
        std::cout << "size after clear(): " << st.size() << std::endl;
        if (st.empty())
            std::cout << "n is empty" << std::endl;
        else
            std::cout << "n is not empty" << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Added 4 elements with insert(). Added in that order {2, 6, 1, 8}. Should be {1, 2, 6, 8}" << std::endl;
        st.insert(2);
        st.insert(6);
        st.insert(1);
        st.insert(8);
        if (st.empty())
            std::cout << "n is empty" << std::endl;
        else
            std::cout << "n is not empty" << std::endl;
        std::cout << "Check size: " << st.size() << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        
        std::cout << std::endl;
    }

    {
        st.erase(6);
        st.erase(2);
        std::cout << "Remove 2 elements (6 and 2) with erase(). Should be in that order {1, 8}" << std::endl;
        std::cout << "Check size: " << st.size() << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

    ft::set<int> test_set(st);

    {
        std::cout << "Check copy construct with previous set. Should be {1, 8}" << std::endl;
        std::cout << "Check size: " << test_set.size() << std::endl;
        for (ft::set<int>::iterator it = test_set.begin(); it != test_set.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Change/Add elements to test_set using []. Should be {1, 2, 5, 8, 9}" << std::endl;
        test_set.insert(5);
        test_set.insert(2);
        test_set.insert(1);
        test_set.insert(9);
        std::cout << "Check size: " << test_set.size() << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Swap 2 sets. Should be {1, 2, 5, 8, 9} in st and {1, 8} in test_set"  << std::endl;
        ft::swap(test_set, st);
        std::cout << "Check size st and values of st: " << st.size() << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Check size of test_set: " << test_set.size() << std::endl;
        for (ft::set<int>::iterator it = test_set.begin(); it != test_set.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
        
    }

    {
        std::cout << "Check operator= for st with empty set"  << std::endl;
        ft::set<int> zero_st;
        st = zero_st;
        std::cout << "size of st is " << st.size() << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check range construct with test_set"  << std::endl;
        ft::set<int> range_const(test_set.begin(), test_set.end());
        std::cout << "Check size of range_const: " << range_const.size() << std::endl;
        for (ft::set<int>::iterator it = range_const.begin(); it != range_const.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check insert(val)" << std::endl;

        size_t t_size = st.size();

        ft::pair<ft::set<int>::iterator, bool> ret = st.insert(15);

        std::cout << "size of st is " << st.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "returned value is: " << std::endl;
        std::cout << "Key: " << *(ret.first) << " | Is_inserted - " << ret.second << std::endl;
        std::cout << "elements of st: " << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check insert(it, val)" << std::endl;

        size_t t_size = st.size();

        st.insert(++st.begin(), 3);

        std::cout << "size of st is " << st.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of st: " << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

        {
        std::cout << "Check insert(it, it). Insert all test_set" << std::endl;

        size_t t_size = st.size();

        test_set.insert(6);
        test_set.insert(9);
        test_set.insert(10);
        
        st.insert(test_set.begin(), test_set.end());

        std::cout << "size of st is " << st.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of st: " << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }

        std::cout << "elements of test_set: " << std::endl;
        for (ft::set<int>::iterator it = test_set.begin(); it != test_set.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check erase(iterator). Delete first in st" << std::endl;
        size_t t_size = st.size();
        
        st.erase(st.begin());
        std::cout << "size of st is " << st.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of st: " << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check erase(iterator, iterator). Delete should stay only 2 last elements" << std::endl;
        size_t t_size = st.size();
        
        st.erase(st.begin(), --(--st.end())); 
        
        std::cout << "size of st is " << st.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of st: " << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

        {
        std::cout << "Check erase(key). Delete 11 and 10. Should stay only 1 element" << std::endl;
        size_t t_size = st.size();
        
        st.erase(11);
        st.erase(10);
        
        std::cout << "size of st is " << st.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of st: " << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check clear()." << std::endl;
        size_t t_size = st.size();
        
        st.clear();
        
        std::cout << "size of st is " << st.size() << "(was " << t_size << ")" << std::endl;
        std::cout << "elements of st: " << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check key_comp() and value_comp()." << std::endl;
        
        const std::type_info& key_info = typeid(st.key_comp());
        const std::type_info& value_info = typeid(st.value_comp());

        std::cout << "Key_comp type is " << key_info.name() << std::endl;
        std::cout << "Value_comp type is " << value_info.name() << std::endl;
        
        std::cout << std::endl;
    }

    {
        std::cout << "Insert values to set st" << std::endl;
        st.insert(22);
        st.insert(27);
        st.insert(3);
        st.insert(1);
        st.insert(--st.end(), 29);
        st.insert(st.find(8), 9);
        st.insert(6);
        st.insert(25);
        st.insert(5);
        st.insert(7);
        st.insert(8);
        st.insert(11);
        st.insert(13);
        st.insert(15);
        st.insert(17);
        std::cout << "size of st is " << std::endl;
        std::cout << "elements of st: " << std::endl;
        for (ft::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        {
            std::cout << "Key: " << *it << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Check find() with value 7, 10 and 3" << std::endl;

        ft::set<int>::iterator it = st.find(7);
        if (it != st.end())
            std::cout << "Key: " << *it << std::endl;
        else
            std::cout << "Hasn't find 7" << std::endl;
        it = st.find(10);
        if (it != st.end())
            std::cout << "Key: " << *it << std::endl;
        else
            std::cout << "Hasn't find 10" << std::endl;
        it = st.find(3);
        if (it != st.end())
            std::cout << "Key: " << *it << std::endl;
        else
            std::cout << "Hasn't find 3" << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check count() with value 13, 28 and 8" << std::endl;
        size_t num = st.count(13);
        std::cout << "Count with 13: " << num << std::endl;
        num = st.count(28);
        std::cout << "Count with 28: " << num << std::endl;
        num = st.count(8);
        std::cout << "Count with 8: " << num << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Check lower_bound() with value 7, 10, 30" << std::endl;
        ft::set<int>::iterator it = st.lower_bound(7);
        if (it != st.end())
            std::cout << "Key: " << *it << std::endl;
        else
            std::cout << "Hasn't find lower_bound 7" << std::endl;
        it = st.lower_bound(10);
        if (it != st.end())
            std::cout << "Key: " << *it << std::endl;
        else
            std::cout << "Hasn't find lower_bound 10" << std::endl;
        it = st.lower_bound(30);
        if (it != st.end())
            std::cout << "Key: " << *it << std::endl;
        else
            std::cout << "Hasn't find lower_bound 30" << std::endl;
    }

    {
        std::cout << "Check upper_bound() with value 7, 10, 30" << std::endl;
        ft::set<int>::iterator it = st.upper_bound(7);
        if (it != st.end())
            std::cout << "Key: " << *it << std::endl;
        else
            std::cout << "Hasn't find upper_bound 7" << std::endl;
        it = st.upper_bound(10);
        if (it != st.end())
            std::cout << "Key: " << *it << std::endl;
        else
            std::cout << "Hasn't find upper_bound 10" << std::endl;
        it = st.upper_bound(30);
        if (it != st.end())
            std::cout << "Key: " << *it << std::endl;
        else
            std::cout << "Hasn't find upper_bound 30" << std::endl;
    }

    {
        std::cout << "Check equal_range() with value 7, 10, 30" << std::endl;
        ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> eq_it = st.equal_range(7);
        if (eq_it.first != st.end())
            std::cout << "Key: " << *(eq_it.first) << std::endl;
        else
            std::cout << "Hasn't find lower_bound 7" << std::endl;
        if (eq_it.second != st.end())
            std::cout << "Key: " << *(eq_it.second) << std::endl;
        else
            std::cout << "Hasn't find upper_bound 7" << std::endl;
        eq_it = st.equal_range(10);
        if (eq_it.first != st.end())
            std::cout << "Key: " << *(eq_it.first) << std::endl;
        else
            std::cout << "Hasn't find lower_bound 10" << std::endl;
        if (eq_it.second != st.end())
            std::cout << "Key: " << *(eq_it.second) << std::endl;
        else
            std::cout << "Hasn't find upper_bound 10" << std::endl;
        eq_it = st.equal_range(30);
        if (eq_it.first != st.end())
            std::cout << "Key: " << *(eq_it.first) << std::endl;
        else
            std::cout << "Hasn't find lower_bound 30" << std::endl;
        if (eq_it.second != st.end())
            std::cout << "Key: " << *(eq_it.second) << std::endl;
        else
            std::cout << "Hasn't find upper_bound 30" << std::endl;

        std::cout << std::endl;
    }

    {
        std::cout << "Check reverse iterator" << std::endl;

        for (ft::set<int>::reverse_iterator rit = st.rbegin(); rit != st.rend(); ++rit)
            std::cout << "Key: " << *rit << std::endl;
        
        std::cout << std::endl;
    }

    {
        std::cout << "Equal operator" << std::endl;
        ft::set<int> test_st(st);
        if (st == test_st)
            std::cout << "st is equal to test_st" << std::endl;
        else
            std::cout << "st isnt equal to test_st" << std::endl;
    }

    {
        std::cout << "Less operator" << std::endl;
        ft::set<int> test_st(st);
        if (st < test_st)
            std::cout << "st is less than test_st" << std::endl;
        else
            std::cout << "st isnt less than test_st" << std::endl;
        std::cout << "remove last element from st" << std::endl;
        st.erase(--st.end());
        if (st < test_st)
            std::cout << "st is less than test_st" << std::endl;
        else
            std::cout << "st isnt less than test_st" << std::endl;
        std::cout << std::endl;
    }

    t2 = clock();
    std::cout << "Running time: " << (double)(t2 - t1) << std::endl;

    return (0);
}