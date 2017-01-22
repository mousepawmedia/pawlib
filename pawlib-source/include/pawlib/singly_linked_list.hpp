/** Singly Linked List [PawLIB]
  * Version: 0.1 (Experimental)
  *
  * A singly linked list class.
  *
  * Author(s): Michael Parkman
  */

/* LICENSE
 * Copyright (c) 2016 MousePaw Games.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef SINGLYLINKEDLIST_HPP_INCLUDED
#define SINGLYLINKEDLIST_HPP_INCLUDED

#include <stdlib.h>

#include "pawlib/iochannel.hpp"

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
