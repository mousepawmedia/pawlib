/** AVL Tree [PawLIB]
  * Version: 0.1 (Experimental)
  *
  * A binary search tree with a low dynamic allocation demand.
  *
  * Author(s): Michael Parkman
  */

/* LICENSE
 * Copyright (c) 2016 MousePaw Media.
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
 * See https://www.mousepawmedia.com/developers for information
 * on how to contribute to our projects.
 */

#ifndef PAWLIB_AVLTREE_HPP
#define PAWLIB_AVLTREE_HPP

#include "pawlib/flex_queue.hpp"
#include "pawlib/iochannel.hpp"
#include "pawlib/singly_linked_list.hpp"

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template<class Type>
    class AVL_Tree
    {
        private:
            //Node for a binary search tree
            struct Node
            {
                //Has a left and a right child
                Node *left, *right;
                //the height of a node is defined as the max height (between the left and right child) + 1
                int height;
                //the data to be stored (should be comparable)
                Type data;
                //constructor
                Node()
                {
                    left = nullptr;
                    right = nullptr;
                    height = nullptr;
                }
            };

            //a pointer to the list of nodes not currently in the tree
            Node* notUsed;
            //the number of nodes to make next time the list runs out
            int nodesToMake;
            //returns a new node with the data of what is passed in
            Node* newNode(Type element)
            {
                //temporary node used for creation/removal of a node from the list of nodes not in use
                Node* temp;
                //if all of the nodes are currently in use
                if(notUsed == nullptr)
                {
                    //loop through the number of nodes to make
                    for(int i = 0; i < nodesToMake; i++)
                    {
                        //instantiate new nodes
                        temp = new Node();
                        //place them on the list of nodes not in use
                        temp->right = notUsed;
                        notUsed = temp;
                    }
                    //next time make twice as many nodes
                    nodesToMake *= 2;
                }
                //get the node on the front of the list
                temp = notUsed;
                //remove the node form the list
                notUsed = notUsed->right;
                temp->right = nullptr;
                //set the data of the node to the correct value
                temp->data = element;
                //return the new node
                return temp;
            }

            //adds the current node onto the list of nodes not in use
            void removeNode(Node* element)
            {
                //remove the left child
                element->left = nullptr;
                //add the node onto the front of the list
                element->right = notUsed;
                notUsed = element;
            }

            Node* root;

            //returns the height of the desired element
            int height(Node* element)
            {
                return element ? element->height  : -1;
            }

            //updates the height of the desired node
            void updateHeight(Node* element)
            {
                //set the nodes height to the max height between the left and right childs
                element->height = height(element->left) - height(element->right) > 0? height(element->left) + 1 : height(element->right) + 1;
            }

            //performs a left rotation on the current node
            Node* leftRotate(Node* element)
            {
                //the right child of the passed in node
                Node* rightChild = element->right;
                //set the passed in nodes right child equal to it's original right childs left child
                element->right = rightChild->left;
                //set the original right child's left child equal to the passed in node
                rightChild->left = element;
                //update the height of the passed in element
                updateHeight(element);
                //update the height of the new root of this subtree (the original right child)
                updateHeight(rightChild);
                //return the new root of this subtree
                return rightChild;
            }

            //performs a right rotation on the current node
            Node* rightRotate(Node* element)
            {
                //the left child of the passed in node
                Node* leftChild = element->left;
                //set the passed in nodes left child equal to it's original left child's right child
                element->left = leftChild->right;
                //set the original left child's right child equal to the passed in node
                leftChild->right = element;
                //update the height of the passed in node
                updateHeight(element);
                //update the height of the new root of this subtree (the original left child)
                updateHeight(leftChild);
                //return the new root of this subtree
                return leftChild;
            }

            //returns the current height difference between the two subtrees
            //returns a positive number if the left child's height is greater than the left
            //returns 0 if the heights are the same
            //returns a negative number if the right child's height is greater than the right
            int checkBalance(Node* element)
            {
                //returns the difference in the heights
                return height(element->left) - height(element->right);
            }

            //balances the subtree that is passed in
            Node* balance(Node* element)
            {
                //updates the height of the subtree
                updateHeight(element);
                //checks the balance of the subtree
                int difference = checkBalance(element);
                //if element is left heavy
                if(difference > 1)
                {
                    //if left child is right heavy
                    if(checkBalance(element->left) < 0)
                    {
                        //perform a left rotation on the left child
                        element->left = leftRotate(element->left);
                    }
                    //perform a right rotation on the current element
                    return rightRotate(element);
                }
                //if element is right heavy
                else if(difference < -1)
                {
                    //if right child is left heavy
                    if(checkBalance(element->right) > 0)
                    {
                        //perform a right rotation on the right child
                        element->right = rightRotate(element->right);
                    }
                    //perform a left rotation on the current element
                    return leftRotate(element);
                }
                //if there is no rotations performed, return the current root
                return element;
            }

            //inserts the passed in element into the tree
            Node* insert(Node* curr, Type element)
            {
                //if the current node is null
                if(curr == nullptr)
                {
                    //return a new node with the passed in data to be added to the tree
                    return newNode(element);
                }
                //if the element is less than the current node's data
                else if(element < curr->data)
                {
                    //set the current node's left child equal to the root that is returned from the balanced insertion into the left subtree
                    curr->left = insert(curr->left, element);
                }
                //if the element is greater than the current node's data
                else if(element > curr->data)
                {
                    //set the current node's right child equal to the root that is returned from the balanced insertion into the right subtree
                    curr->right = insert(curr->right, element);
                }
                //balance the current subtree and return the root
                return balance(curr);
            }

            Node* remove(Node* curr, Type element)
            {
                //if the passed in node is null, return null
                if(curr == nullptr)
                {
                    return curr;
                }
                //if the element is less than the current node
                else if(element < curr->data)
                {
                    //set the left child equal to the balanced subtree that is returned from the removal of the node from the left subtree
                    curr->left = remove(curr->left, element);
                }
                //if the element is greater than the current node
                else if(element > curr->data)
                {
                    //set the right child equal to the balanced subtree that is returned from the removal of the node form the right subtree
                    curr->right = remove(curr->right, element);
                }
                //if the current node is the element to remove
                else
                {
                    //If the current node is a leaf
                    if(curr -> left == nullptr && curr->right == nullptr)
                    {
                        //remove the node
                        removeNode(curr);
                        //return null
                        return nullptr;
                    }
                    //if current node has a right child but not a left
                    else if(curr->left == nullptr && curr->right != nullptr)
                    {
                        //get the right child
                        Node* temp = curr->right;
                        //remove the current node
                        removeNode(curr);
                        //return the balanced subtree with the right child as the root.
                        //this sets the right child as the left or right child of the current node's parent
                        return balance(temp);
                    }
                    //if the current node has a left child but not a right
                    else if(curr->left != nullptr && curr->right == nullptr)
                    {
                        //get the left child
                        Node* temp = curr->left;
                        //remove the current node
                        removeNode(curr);
                        //return the balanced subtree with the left child as the root
                        //this sets the left child as the left or right child of the current node's parent
                        return balance(temp);
                    }
                    //if the current node has both a left and right child
                    else
                    {
                        //The parent of the successor
                        Node* parent;
                        //get the current nodes successor
                        Node* successor = getSuccessor(curr, &parent);
                        //replace the current node with it's successor
                        successor->left = curr->left;
                        //the right child of the current node is not the current nodes successor
                        if(curr->right != successor)
                            //set the successor's right child to that of the current node's right child
                            successor->right = curr->right;

                        //if the left child of the parent is the successor
                        if(parent->left == successor)
                            //set the left child of the parent to be null
                            parent->left = nullptr;
                        //if the right child of the parent is the successor
                        else if(parent->right == successor)
                            //set the right child of the parent to be null
                            parent->right = nullptr;
                        //add the current node to the list of nodes not in use
                        removeNode(curr);
                        //return the balanced subtree with the successor as the root
                        return balance(successor);
                    }
                }
                //return the balanced subtree
                return balance(curr);
            }

            //get the successor of a node if that node does not have a right child
            Node* getSuccessor(Node* curr, Type element, Node** parent)
            {
                //if the passed in node is null, return null
                if(curr == nullptr)
                {
                    return nullptr;
                }
                //if the current node is the node for which we are finding the successor
                else if(element == curr->data)
                {
                    //return null
                    return nullptr;
                }
                //else if node we are finding the successor for is to the left of the current node
                else if(element < curr->data)
                {
                    //if we want to know the parent
                    if(parent != nullptr)
                        //update the parent
                        *parent = curr;
                    //Set temp equal to the whatever getSuccessor returns
                    Node* temp = getSuccessor(curr->left, element, parent);
                    //if temp returns null this means that the current node is the last parent that has a value greater than the value of the node we are finding the successor for
                    //So if temp returns null, we return this node, otherwise we return whatever was returned
                    return temp ? temp : curr;
                }
                else
                {
                    //if we want to know the parent
                    if(parent != nullptr)
                        //update the parent
                        *parent = curr;
                    //return the results of getSuccessor
                    return getSuccessor(curr->right, element, parent);
                }
            }

            //get the predecessor of a node if that node does not have a left child
            Node* getPredecessor(Node* curr, Type element, Node** parent)
            {
                //if the passed in node is null, return null
                if(curr == nullptr)
                {
                    return nullptr;
                }
                //if the current node is the node for which we are finding the successor
                else if(element == curr->data)
                {
                    //return null
                    return nullptr;
                }
                //else if node we are finding the successor for is to the right of the current node
                else if(element > curr->data)
                {
                    //if we want to know the parent
                    if(parent != nullptr)
                        //update the parent
                        *parent = curr;
                    //Set temp equal to the whatever getSuccessor returns
                    Node* temp = getSuccessor(curr->right, element, parent);
                    //if temp returns null this means that the current node is the last parent that has a value greater than the value of the node we are finding the successor for
                    //So if temp returns null, we return this node, otherwise we return whatever was returned
                    return temp ? temp : curr;
                }
                else
                {
                    //if we want to know the parent
                    if(parent != nullptr)
                        //update the parent
                        *parent = curr;
                    //return the results of getSuccessor
                    return getSuccessor(curr->right, element, parent);
                }
            }

            //pre-order print
            void printNode(Node* temp)
            {
                ioc << temp->data << io_end;
                if(temp->left != nullptr)
                {
                    printNode(temp->left);
                }

                if(temp->right != nullptr)
                {
                    printNode(temp->right);
                }
            }

        public :
            AVL_Tree()
            {
                root = nullptr;
                notUsed = nullptr;
                nodesToMake = 8;
            }

            //inserts the element into the tree
            void insert(Type element)
            {
                //call the helper function
                root = insert(root, element);
            }

            void remove(Type element)
            {
                //call the helper function
                root = remove(root, element);
            }

            //Searches the tree for the element
            //returns true and sets the passed in return value equal to the desired node's data if desired node is in the tree
            //returns false if the node does not exist
            bool retrieve(Type element, Type* returnVal)
            {
                //The searching node
                Node* temp = root;
                //while the searching node is not null
                while(temp != nullptr)
                {
                    //if the element matches the current node's data
                    if(element == temp->data)
                    {
                        //break out and return
                        break;
                    }
                    //if the element is less than the current node's data
                    else if(element < temp->data)
                    {
                        //continue searching down the left subtree
                        temp = temp->left;
                    }
                    //if the element is greater than the current node's data
                    else
                    {
                        //continue searching down the right subtree
                        temp = temp->right;
                    }
                }
                //if node exists
                if(temp)
                {
                    //set return value equal to the data
                    *returnVal = temp->data;
                    return true;
                }
                //otherwise return false
                return false;
            }

            //gets the predecessor of the passed in element
            //if parent is not null, will set that equal to the parent of the predecessor
            Node* getPredecessor(Node* element, Node** parent = nullptr)
            {
                //if the node does not have a right child
                if(element->left == nullptr)
                {
                    //then we have to find the successor a different way
                    return getPredecessor(root, element->data, parent);
                }
                //if the node has a right child
                else
                {
                    //set temp equal to the left child
                    Node* temp = element->left;
                    //if temp does not have a right child
                    if(temp->right == nullptr)
                    {
                        //if we want to know the parent
                        if(parent != nullptr)
                        {
                            //update the parent
                            *parent = element;
                        }
                        //this means that temp is the predecessor, so return temp
                        return temp;
                    }
                    //while temp has a right child
                    while(temp->right != nullptr)
                    {
                        //if we want to know the parent
                        if(parent != nullptr)
                            //update the parent
                            *parent = temp;
                        //update temp to it's right child
                        temp = temp->right;
                    }
                    //return temp which is the successor of the passed in node
                    return temp;
                }
            }

            //gets the successor of the passed in element
            //if parent is not null, will set that equal to the parent of the successor
            Node* getSuccessor(Node* element, Node** parent = nullptr)
            {
                //if the node does not have a right child
                if(element->right == nullptr)
                {
                    //then we have to find the successor a different way
                    return getSuccessor(root, element->data, parent);
                }
                //if the node has a right child
                else
                {
                    //set temp equal to the right child
                    Node* temp = element->right;
                    //if temp does not have a left child
                    if(temp->left == nullptr)
                    {
                        //if we want to know the parent
                        if(parent != nullptr)
                            //update the parent
                            *parent = element;
                        //this means that temp is the successor, so return temp
                        return temp;
                    }
                    //while temp has a left child
                    while(temp->left != nullptr)
                    {
                        //if we want to know the parent
                        if(parent != nullptr)
                            //update the parent
                            *parent = temp;
                        //update temp to it's left child
                        temp = temp->left;
                    }
                    //return temp which is the successor of the passed in node
                    return temp;
                }
            }

            //prints the tree with a pre-order traversal
            void print()
            {
                printNode(root);
            }

            //creates a new tree by copying the nodes over via level order traversal
            //do level order traversal so that there does not need to be any rotations to keep the tree balanced
            AVL_Tree<Type>* clone()
            {
                //Create a new tree
                AVL_Tree<Type>* daClone = new AVL_Tree<Type>();
                //if there is something in this tree, copy it into the new tree
                if(root != nullptr)
                {
                    //A FlexQueue to store the different nodes for the level order traversal
                    FlexQueue<Node*> q = new FlexQueue<Node*>();
                    //add the root node to the queue
                    q->add(root);
                    //to store the node we are currently looking at
                    // cppcheck-suppress variableScope
                    Node* temp;
                    //loop until there are no more nodes to be copied to the new tree
                    while(q->getSize() != 0)
                    {
                        //remove the first element in the queue
                        temp = q->poll();
                        //if the current node has a left child
                        if(temp->left != nullptr)
                        {
                            //add the child to the queue
                            q->add(temp->left);
                        }
                        //if the current node has a right child
                        if(temp->right != nullptr)
                        {
                            //add the child to the queue
                            q->add(temp->right);
                        }
                        //insert the current node into the tree
                        daClone->insert(temp);
                    }
                }
                //return the copy
                return daClone;
            }
    };
}

#endif // PAWLIB_AVLTREE_HPP
