/*
 *
 * MIT License
 *
 * Copyright (c) 2021 Rohit Philip Mathew
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef _LIST_HPP_ 
#define _LIST_HPP_

#include <initializer_list>
#include <cstdbool>
#include <type_traits>

namespace miniSTL
{

  /* For time being we are skipping allocator */
  template<class T>
    class list
    {

      struct node;
    public:

      /* should iterators be aggregates? */
      struct iterator
      {
        iterator () :
            iter_node (nullptr)
        {
        }
        iterator (node *val) :
            iter_node (val)
        {
        }
        friend class list<T> ;
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        /* postfix */
        iterator
        operator++ (int)
        {
          node *previous = iter_node;
          iter_node = iter_node->next;
          return iterator (previous);
        }

        /* prefix */
        iterator&
        operator++ ()
        {
          iter_node = iter_node->next;
          return *this;
        }

        /* postfix */
        iterator
        operator-- (int)
        {
          node *previous = iter_node;
          iter_node = iter_node->prev;
          return iterator (previous);
        }

        /* prefix */
        iterator&
        operator-- ()
        {
          iter_node = iter_node->prev;
          return *this;
        }

        bool
        operator!= (const iterator &iter)
        {
          return iter_node != iter.iter_node;
        }

        bool
        operator== (const iterator &iter)
        {
          return iter_node == iter.iter_node;
        }

        T&
        operator* ()
        {
          return iter_node->data;
        }

      private:
        node *iter_node;
      };

      typedef T value_type;
      typedef value_type *pointer;
      typedef const pointer const_pointer;
      typedef value_type &reference;
      typedef const reference const_reference;
      typedef const iterator const_iterator;
      typedef value_type *reverse_iterator;
      typedef const reverse_iterator const_reverse_iterator;
      typedef size_t size_type;

      /* I need to be truthful here. I copied this snippet from SO. 
       My understanding here is that during template instantiation,
       this would do a compile time check to see if the deducted
       type is an iterator. Since std::iterator require 5 different
       members including a tag denoting its type, I added them for
       my iterator as well. Things work now. I'll need to start with
       traits soon since this would just be the beginning :(
       */
      template<typename InputIterator>
        using RequireInputIterator = typename
        std::enable_if<std::is_convertible<typename
        std::iterator_traits<InputIterator>::iterator_category,
        std::input_iterator_tag>::value>::type;

      /// constructors ///

      /**
       * default constructor for a list
       *
       * @param  : none
       * @return : none
       */
      explicit
      list () :
          m_head (nullptr), m_tail (nullptr), m_size (0)
      {

      }

      /**
       * fill constructor for a list
       *
       * this version of fill constructor zero initializes
       * all n elements
       *
       * @param  : size_t - number of elements to add to list
       * @return : none
       */
      explicit
      list (size_type n) :
          m_head (nullptr), m_tail (nullptr), m_size (0)
      {
        /// allocate n nodes with value zero ///
        for (size_type i = 0; i < n; i++)
        {
          push_back (0);
        }
      }

      /**
       * fill constructor for a list
       * 
       * this version of fill constructor initializes 
       * all n elements with value val
       * 
       * @param  : size_t - number of elements to add to list
       *         : T&     - value to initialize each element with 
       * @return : none
       */
      list (size_type n, const value_type &val) :
          m_head (nullptr), m_tail (nullptr), m_size (0)
      {
        for (size_type i = 0; i < n; i++)
        {
          push_back (val);
        }
      }

      /**
       * range constructor for a list
       *
       * initializes the list with elements given in the 
       * range
       *
       * @param  : InputIterator - any iteratable type object denoting
       *           the start of the range
       *         : InputIterator - any iteratable type object denoting 
       *           the end of the range
       * @return : none
       */
      template<class InputIterator, typename = RequireInputIterator<
          InputIterator>>
        list (InputIterator first, InputIterator last) :
            m_head (nullptr), m_tail (nullptr), m_size (0)
        {
          assign (first, last);
        }

      /**
       * copy constructor for a list
       *
       * @param  : list& - list object from where we need to copy
       * @return : none
       */
      list (const list &x) :
          m_head (nullptr), m_tail (nullptr), m_size (0)
      {
        /// Do a deep copy ///
        for (auto &el : x)
        {
          push_back (el);
        }
      }

      /**
       * move constructor for a list
       *
       * @param  : list&& - the list object from where we need to move
       * @return : none
       */
      list (list &&x)
      {
        m_head = x.m_head;
        m_tail = x.m_tail;
        m_size = x.m_size;
        x.m_head = x.m_tail = nullptr;
      }

      /**
       * initializer list constructor for a list
       *
       * @param  : std::initializer_list<value_type> - initializer
       *           list from where we need to copy values to our list
       * @return : none
       */
      list (std::initializer_list<value_type> il) :
          m_head (nullptr), m_tail (nullptr), m_size (0)
      {
        assign (il.begin (), il.end ());
      }

      /// destructor ///

      /**
       * Destructor
       *
       * @param  : none
       * @return : none
       */
      ~list ()
      {
        erase (begin (), end ());
      }

      /// assignment operator ///

      /**
       * copy assignment operator for a list
       *
       * @param  : list& - list from where we need to copy
       *           assign values to our list
       * @return : reference to this list
       */
      list&
      operator= (const list &x)
      {
        if (this == &x)
        {
          return *this;
        }

        erase (begin (), end ());

        for (auto &el : x)
        {
          push_back (el);
        }
        return *this;
      }

      /**
       * move assignment operator for a list
       *
       * @param  : list&& - list from where we need to move
       *           assign to our list
       * @return : reference to this list
       */
      list&
      operator= (list &&x)
      {
        if (this == &x)
        {
          return *this;
        }

        erase (begin (), end ());
        m_head = x.m_head;
        m_tail = x.m_tail;
        m_size = x.m_size;
        x.m_head = x.m_tail = nullptr;
        return *this;
      }

      /**
       * initializer list assignment operator for a list
       *
       * @param  : std::initializer_list<value_type> - initializer
       *           list from where we need to copy assign our list
       * @return : reference to this list
       */
      list&
      operator= (std::initializer_list<value_type> il)
      {
        erase (begin (), end ());
        assign (il.begin (), il.end ());
        return *this;
      }

      /// Element access ///

      /**
       * get the element at the end of the list
       *
       * this function has no guarantee against
       * throwing. If no element exists at the 
       * tail, behaviour is undefined 
       *
       * @param  : none
       * @return : reference to last element
       */
      reference
      back ()
      {
        return (reference) m_tail->data;
      }

      /**
       * get the element at the end of the list
       *
       * this function has no guarantee against
       * throwing. If no element exists at the 
       * tail, behaviour is undefined 
       *
       * @param  : none
       * @return : const reference to last element
       */
      const_reference
      back () const
      {
        return (const_reference) m_tail->data;
      }

      /**
       * get the element at the head of the list
       *
       * this function has no guarantee against
       * throwing. If no element exists at the 
       * head, behaviour is undefined 
       *
       * @param  : none
       * @return : reference to first element
       */
      reference
      front ()
      {
        return (reference) m_head->data;
      }

      /**
       * get the element at the head of the list
       *
       * this function has no guarantee against
       * throwing. If no element exists at the 
       * head, behaviour is undefined 
       *
       * @param  : none
       * @return : const reference to first element
       */
      const_reference
      front () const
      {
        return (const_reference) m_head->data;
      }

      /**
       * assign a range of elements to the list
       *
       * this method would assign a range of elements 
       * of type T from an iteratable range.
       *
       * @param  : InputIterator - start of the range
       *         : InputIterator - end of the range
       * @return : none
       */
      template<class InputIterator, typename = RequireInputIterator<
          InputIterator>>
        void
        assign (InputIterator first, InputIterator last)
        {
          /** official c++ websites states that existing nodes 
           are destroyed and new nodes are allocated. Since
           assign is a single call, we are optimizing by re-
           using existing nodes and allocating only if there
           are more nodes than what already exists
           */
          iterator temp (m_head);
          while (temp.iter_node != nullptr && first != last)
          {
            *temp++ = *first++;
          }

          if (temp.iter_node != nullptr && first == last)
          {
            erase (temp, end ());
          }
          else if (temp.iter_node == nullptr && first != last)
          {
            while (first != last)
            {
              push_back (*first);
              first++;
            }
          }
        }

      /**
       * assign a range of elements to the list
       *
       * this method would assign n elements 
       * of type T. Any existing elements in the 
       * list would be destroyed after assign operation
       *
       * @param  : n - start of the range
       *         : const value_type& - end of the range
       * @return : none
       */
      void
      assign (size_type n, const value_type &val)
      {
        if (!n)
        {
          return;
        }

        iterator temp (m_head);
        while (temp.iter_node != nullptr && n)
        {
          *temp++ = val;
          n -= 1;
        }

        if (temp.iter_node != nullptr && (n == 0))
        {
          erase (temp, end ());
        }
        else if (temp.iter_node == nullptr && (n != 0))
        {
          while (n)
          {
            push_back (val);
            n -= 1;
          }
        }
      }

      /**
       * assign from an initializer list
       *
       * this method would assign elements from an
       * initializer list. Any existing elements in the 
       * list would be destroyed after assign operation
       *
       * @param  : std::initializer_list<value_type> initializer
       *           list from which we assign
       * @return : none
       */
      void
      assign (std::initializer_list<value_type> il)
      {
        if (!il.size ())
        {
          return;
        }

        iterator temp (m_head);
        auto il_iter = il.begin ();

        while (temp.iter_node != nullptr && il_iter != il.end ())
        {
          *temp++ = *il_iter++;
        }

        if (temp.iter_node != nullptr && il_iter == il.end ())
        {
          erase (temp, end ());
        }
        else if (temp.iter_node == nullptr && il_iter != il.end ())
        {
          while (il_iter != il.end ())
          {
            push_back (*il_iter);
            il_iter++;
          }
        }
      }

      /**
       * push elements to the front of a list
       *
       * element passed as param is copied to the 
       * front of the list
       *
       * @param  : value_type& - value to be pushed
       * @return : none
       */
      void
      push_front (const value_type &val)
      {
        node *cur_node = new node (val);
        push_front_helper (cur_node);
      }

      /**
       * push elements to the front of a list
       *
       * element passed as param is moved to the 
       * front of the list
       *
       * @param  : value_type&& - value to be pushed
       * @return : none
       */
      void
      push_front (value_type &&val)
      {
        node *cur_node = new node (std::move (val));
        push_front_helper (cur_node);
      }

      /**
       * pop elements from front of a list
       *
       * @param  : none
       * @return : none
       */
      void
      pop_front ()
      {
        if (empty ())
          return;

        node *cur_node = m_head;
        m_head = m_head->next;
        if (m_head != nullptr)
        {
          m_head->prev = nullptr;
        }
        delete cur_node;
        m_size--;
      }

      /**
       * push elements to the back of a list
       *
       * element passed as param is copied to the 
       * back of the list
       *
       * @param  : value_type& - value to be pushed
       * @return : none
       */
      void
      push_back (const value_type &val)
      {
        node *cur_node = new node (val);
        push_back_helper (cur_node);
      }

      /**
       * push elements to the back of a list
       *
       * element passed as param is moved to the 
       * back of the list
       *
       * @param  : value_type&& - value to be pushed
       * @return : none
       */
      void
      push_back (value_type &&val)
      {
        node *cur_node = new node (std::move (val));
        push_back_helper (cur_node);
      }

      /**
       * pop elements from back of a list
       *
       * @param  : none
       * @return : none
       */
      void
      pop_back ()
      {
        if (empty ())
          return;

        node *cur_node = m_tail;
        m_tail = m_tail->prev;
        if (m_tail != nullptr)
        {
          m_tail->next = nullptr;
        }
        delete cur_node;
        m_size--;
      }

      /**
       * insert a single element before the given iterator
       *
       * @param  : const_iterator - iterator before which 
       *           the new element needs to be inserted
       *         : value_type& - value to be inserted 
       * @return : iterator to the element inserted
       */
      iterator
      insert (const_iterator position, const value_type &val)
      {
        node *cur_node = position.iter_node, *prev_node = cur_node->prev;
        /* we are not handling a bad iterator being passed case */

        node *new_node = new node (val);
        if (prev_node)
        {
          new_node->prev = prev_node;
          prev_node->next = new_node;
        }
        else
        {
          /* we are modifying head */
          new_node->prev = nullptr;
          m_head = new_node;
        }

        new_node->next = cur_node;
        cur_node->prev = new_node;
        m_size++;
        return iterator (new_node);
      }

      /**
       * insert n element before the given iterator
       *
       * @param  : const_iterator - iterator before which 
       *           the new element needs to be inserted
       *         : size_type - number of elements to be 
       *           inserted into the list
       *         : value_type& - value to be inserted 
       * @return : iterator to the first element inserted
       */
      iterator
      insert (const_iterator position, size_type n, const value_type &val)
      {
        //TODO understand what the behavior would be for this scenario
        if (!n)
          return position;
        size_t p_size = n;
        node *cur_node = position.iter_node, *prev_node = cur_node->prev,
            *new_node = nullptr, *ret_node = nullptr;

        new_node = new node (val);
        if (prev_node)
        {
          new_node->prev = prev_node;
          prev_node->next = new_node;
        }
        else
        {
          /* we are modifying the head */
          m_head = new_node;
          new_node->prev = nullptr;
        }
        prev_node = ret_node = new_node;

        while (n - 1)
        {
          new_node = new node (val);
          new_node->prev = prev_node;
          prev_node->next = new_node;
          prev_node = new_node;
          n--;
        }
        prev_node->next = cur_node;
        cur_node->prev = prev_node;
        m_size += p_size;
        return iterator (ret_node);
      }

      /**
       * insert a range of element before the given iterator
       *
       * @param  : const_iterator - iterator before which 
       *           the new element needs to be inserted
       *         : InputIterator - start of the range
       *         : InputIterator - end of the range 
       * @return : iterator to the first element inserted
       */
      template<class InputIterator, typename = RequireInputIterator<
          InputIterator>>
        iterator
        insert (const_iterator position, InputIterator first,
                InputIterator last)
        {

          // TODO Understand what would be the behavior here?
          if (first == last)
            return position;
          node *cur_node = position.iter_node, *prev_node = cur_node->prev,
              *new_node = nullptr, *ret_node = nullptr;
          int p_size = std::distance (first, last);
          new_node = new node (*first++);
          if (prev_node)
          {
            new_node->prev = prev_node;
            prev_node->next = new_node;
          }
          else
          {
            /* we are modifying the head */
            m_head = new_node;
            new_node->prev = nullptr;
          }
          prev_node = ret_node = new_node;

          while (first != last)
          {
            new_node = new node (*first++);
            new_node->prev = prev_node;
            prev_node->next = new_node;
            prev_node = new_node;
          }
          prev_node->next = cur_node;
          cur_node->prev = prev_node;
          m_size += p_size;
          return iterator (ret_node);
        }

      /**
       * insert a single element before the given iterator
       *
       * @param  : const_iterator - iterator before which 
       *           the new element needs to be inserted
       *         : value_type&& - value to be moved to
       * @return : iterator to the element inserted
       */
      iterator
      insert (const_iterator position, value_type &&val)
      {

        node *cur_node = position.iter_node, *prev_node = cur_node->prev;
        /* we are not handling a bad iterator being passed case */

        node *new_node = new node (std::move (val));
        if (prev_node)
        {
          new_node->prev = prev_node;
          prev_node->next = new_node;

        }
        else
        {
          /* we are modifying head */
          new_node->prev = nullptr;
          m_head = new_node;
        }
        new_node->next = cur_node;
        cur_node->prev = new_node;
        m_size++;
        return iterator (new_node);
      }

      /**
       * insert a single element before the given iterator
       *
       * @param  : const_iterator - iterator before which 
       *           the new element needs to be inserted
       *         : std::initializer_list<value_type> il - 
       *           initializer list from which elements 
       *           needs to be inserted   
       * @return : iterator to the firstelement inserted
       */
      iterator
      insert (const_iterator position, std::initializer_list<value_type> il)
      {
        return insert (position, il.begin (), il.end ());
      }

      /**
       * delete a single element pointed by the given iterator
       *
       * @param  : const_iterator - iterator  which
       *           points to the element to be deleted
       * @return : iterator to the element that follows the element
       *           to be deleted
       */
      iterator
      erase (const_iterator position)
      {
        node *cur_node = position.iter_node, *prev_node = cur_node->prev,
            *next_node = cur_node->next, *ret_node = cur_node->next;

        if (prev_node)
        {
          prev_node->next = next_node;
        }
        else
        {
          /* We are erasing head */
          m_head = next_node;
        }
        if (next_node)
        {
          next_node->prev = prev_node;
        }
        else
        {
          /* We are erasing m_tail*/
          m_tail = prev_node;
        }
        delete cur_node;
        m_size--;
        return iterator (ret_node);
      }

      /**
       * delete a range of elements pointed by the given
       * iterators
       *
       * @param  : const_iterator - iterator  which
       *           points to first element in the list
       *           const_iterator - iterator which points
       *           to a location after the last element in
       *           the list
       * @return : iterator to the element that follows the
       *           last element to be deleted
       */
      iterator
      erase (const_iterator first, const_iterator last)
      {

        if (empty ())
        {
          return first;
        }
        size_type p_size = std::distance (first, last);
        node *first_node = first.iter_node, *last_node = last.iter_node,
            *prev_node = first_node->prev, *next_node = last_node, *temp_node =
                nullptr;

        /* clean from first to last [) */
        while (first_node != last_node)
        {
          temp_node = first_node->next;
          delete first_node;
          first_node = temp_node;
        }

        if (prev_node)
        {
          prev_node->next = next_node;
        }
        else
        {
          /* We are erasing head */
          m_head = next_node;
        }
        if (next_node)
        {
          next_node->prev = prev_node;
        }
        else
        {
          /* We are erasing m_tail*/
          m_tail = prev_node;
        }
        m_size = (m_size > p_size) ? m_size - p_size : 0;
        return last;
      }

      /**
       * swaps the contents of a list with the one passed
       *
       * @param  : list & - the list to swap from
       * @return : none
       */
      void
      swap (list &x)
      {
        std::swap (m_head, x.m_head);
        std::swap (m_tail, x.m_tail);
        std::swap (m_size, x.m_size);
      }

      /**
       * returns the size of the list
       *
       *
       * @param  : none
       * @return : size_type - denoting size of the list
       */
      size_type
      size () const noexcept
      {
        return m_size;
      }
      /**
       * re-sizes the list. if size is greater than current
       * size, new nodes are allocated, else existing nodes
       * are removed. list is default value initialized in this
       * case
       *
       * @param  : n - new size of the list
       * @return : none
       */
      void
      resize (size_type n)
      {
        if (n > m_size)
        {
          //proceed to remove nodes from end
        }
        else if (n < m_size)
        {
          //proceed to push_back
        }
      }

      void
      resize (size_type n, const value_type &val)
      {

      }

      void
      clear () noexcept
      {

      }

      iterator
      begin () noexcept
      {
        return iterator (m_head);
      }

      const_iterator
      begin () const noexcept
      {
        return (const_iterator) iterator (m_head);
      }

      const_iterator
      cbegin () const noexcept
      {
        return (const_iterator) iterator (m_head);
      }

      iterator
      end () noexcept
      {
        return iterator (nullptr);
      }

      const_iterator
      end () const noexcept
      {
        return (const_iterator) iterator (nullptr);
      }

      const_iterator
      cend () const noexcept
      {
        return (const_iterator) iterator (nullptr);
      }

      inline bool
      empty () const
      {
        return m_head == nullptr;
      }

    private:

      void
      push_front_helper (node *cur_node)
      {
        if (empty ())
        {
          m_head = m_tail = cur_node;
        }
        else
        {
          cur_node->next = m_head;
          m_head->prev = cur_node;
          m_head = cur_node;
        }
        m_size++;
      }

      void
      push_back_helper (node *cur_node)
      {
        if (empty ())
        {
          m_head = m_tail = cur_node;
        }
        else
        {
          m_tail->next = cur_node;
          cur_node->prev = m_tail;
          m_tail = cur_node;
        }
        m_size++;
      }

      /* list node type */
      struct node
      {
        T data;
        struct node *next;
        struct node *prev;
        node () :
            data (T ()), next (nullptr), prev (nullptr)
        {
        }
        node (const T &val) :
            data (T (val)), next (nullptr), prev (nullptr)
        {
        }
        node (T &&val) :
            data (T (std::move (val))), next (nullptr), prev (nullptr)
        {
        }
      };
      node *m_head, *m_tail;
      size_type m_size;
    };

}

#endif /* _LIST_HPP_*/
