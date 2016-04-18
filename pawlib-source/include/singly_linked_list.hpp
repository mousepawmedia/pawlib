/** Singly Linked List [PawLIB]
  * Version: 1.0
  *
  * A singly linked list class.
  *
  * Last Updated: 8 March 2016
  * Author: Michael Parkman
  */

/* LICENSE
 * Copyright (C) 2016 MousePaw Games.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * CONTRIBUTING
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef SINGLYLINKEDLIST_HPP_INCLUDED
#define SINGLYLINKEDLIST_HPP_INCLUDED

#include <stdlib.h>
#include <iochannel.hpp>

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    //Node structure using Templates
    //contains 4 variables: Pointer to the name, pointer to the type, pointer to the variable, and pointer to the next node
    template<typename T>
    struct Node{
        public:
            // cppcheck-suppress noExplicitConstructor
            Node(T datas){
                data = datas;
                next = nullptr;
            }

            //some getters and setters
            T getData(){return data;}
            Node<T>* getNext(){return next;}
            void setNext(Node<T>* nxt){next = nxt;}

        //private variables
        private:
            T data;
            Node<T>* next;
    };
    //

    //Class declaration for a template based Linked List
    template<class Type>
    class SinglyLinkedList{
        public:
            //constructor
            SinglyLinkedList(){
                initialization();           //initializes all pointers to nullptr and sizes to 0
            }
            //deconstructor: frees up the memory of any remaining node in the list
            ~SinglyLinkedList(){
                Node<Type>* prev = nullptr;
                Node<Type>* curr = head;
                for(int i = 0; i < size; i++, curr = curr->getNext()){
                    if(prev != nullptr){
                        delete(prev);
                        prev = curr;
                    }else{
                        prev = curr;
                    }
                }
                delete(prev);
            }

            //adds a node to the list
            //gets passed in variable name, variable type, and the actual variable
            void  add(Type data){
                if(size == 0){
                    head = new Node<Type>(data);
                    size++;
                }else{
                    Node<Type>* newNode = new Node<Type>(data);
                    Node<Type>* temp = head;
                    for(int i = 0; i < size - 1; i++, temp = temp -> getNext());
                    temp -> setNext(newNode);
                    size++;
                }
            }

            //adds new node into list
            //sorts by name
            void addOrdered(Type data){
                Node<Type>* newNode = new Node<Type>(data);
                if(size == 0){
                    head = newNode;
                    size++;
                }else{
                    Node<Type>* curr = head;
                    Node<Type>* prev = nullptr;
                    for(int i = 0; i < size; i++){
                        if(newNode->getData() < curr->getData()){
                            break;
                        }else{
                            prev = curr;
                            curr = curr -> getNext();
                        }
                    }
                    if(prev == nullptr)
                    {
                        head = newNode;
                    }
                    else
                    {
                       prev -> setNext(newNode);
                    }
                    newNode->setNext(curr);
                    size++;
                }
            }

            //removes the node at the specified index
            //if the index is not in the list or there are no items in the list it returns nullptr
            //otherwise it returns the node that was removed
            Node<Type>* remove(int index){
                if(size == 0){
                    ioc << cat_error << vrb_quiet << "List is empty" << io_end;
                    return nullptr;
                }
                else if(index < 0 || index > size - 1)
                {
                    ioc << cat_error << vrb_quiet << "Index out of bounds" << io_end;
                    return nullptr;
                }
                else if(index == 0)
                {
                    Node<Type>* prev = head;
                    head = head -> getNext();
                    size--;
                    return prev;
                }
                else{
                    Node<Type>* prev = head;
                    Node<Type>* curr = head;
                    for(int i = 0; i < index; i++, prev = curr, curr = curr -> getNext());
                    prev->setNext(curr->getNext());
                    size--;
                    return curr;
                }
            }

            //removes all the nodes in the list
            void removeAll(){
                if(size != 0){
                    Node<Type>* curr = head;
                    Node<Type>* prev = head;
                    while(size > 1){
                        curr = curr->getNext();
                        head = curr;
                        delete(prev);
                        prev = curr;
                        size--;
                    }
                    delete curr;
                    initialization();
                }
            }

            //finds the Node at the specified index. If the index is not in the list or the list is empty it returns 0
            //otherwise it returns the node at the specified index
            Type get(int index){
                if(size == 0 || index > size){
                    return nullptr;
                }else{
                    Node<Type>* curr = head;
                    for(int i = 0; i < index; i++, curr = curr -> getNext());
                    return curr->getData();
                }
            }

            //prints out the list
            void print(){
                Node<Type>* curr = head;
                for(int i = 0; i < size; i++){
                    ioc << curr -> getData() << io_end;
                    curr = curr -> getNext();
                }
            }

            //returns size of the list
            int getSize(){
                return size;
            }

        //private variables
        private:
            int size;
            Node<Type>* head;

            //initializes head to nullptr and size to zero
            void initialization(){
                head = nullptr;
                size = 0;
            }

    };
}
#endif // SINGLYLINKEDLIST_HPP_INCLUDED
