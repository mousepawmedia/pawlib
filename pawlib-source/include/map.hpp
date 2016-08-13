/** Map [PawLIB]
  * Version: 1.0
  *
  * A map/dictionary with a low dynamic allocation demand.
  *
  * Last Updated: 8 March 2016
  * Author: Michael Parkman
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

#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <avl_tree.hpp>
#include <iosfwd>
#include <ostream>

using std::ostream;

namespace pawlib
{
    template<class TypeOfKey, class TypeToMap>
    class Map
    {
        private:
            struct MapNode
            {
                //the key used to sort the MapNode
                TypeOfKey key;
                //the data to store
                TypeToMap data;

                //empty constructor, needed for creation in AVL_Tree
                MapNode() { }

                //copy constructor
                MapNode(const MapNode&) = default;

                //constructor used for retrieve method
                explicit MapNode(TypeOfKey theKey)
                {
                    key = theKey;
                }

                //a MapNode contains a key and the data
                MapNode(TypeOfKey theKey, TypeToMap theData)
                {
                    key = theKey;
                    data = theData;
                }

                //overrides the comparable operators for comparison in the AVL_Tree
                bool operator < (const MapNode& otherNode) {return key < otherNode.key; }
                bool operator > (const MapNode& otherNode) { return key > otherNode.key; }
                bool operator == (const MapNode& otherNode) { return key == otherNode.key; }
                bool operator != (const MapNode& otherNode) { return key != otherNode.key; }
            };

            //override the output stream for printing possibilities in AVL_Tree
            friend ostream& operator << (ostream& os, const MapNode& node) { os << node.data; return os; }

            //a map has an AVL_Tree
            AVL_Tree<MapNode>* tree;

            AVL_Tree<MapNode>* clone()
            {
                return tree->clone();
            }

        public:
            //empty constructor initializes the tree
            Map()
            {
                tree = new AVL_Tree<MapNode>();
            }

            Map(const Map& mapToCopy)
            {
                tree = mapToCopy.clone();
            }

            //insert the couple into the tree
            void insert(TypeOfKey key, TypeToMap data)
            {
                MapNode node(key, data);
                tree->insert(node);
            }

            //remove the element, that has the given key, from the tree
            void remove(TypeOfKey key)
            {
                tree->remove(key);
            }

            //retrieves the element that has the given key
            //returns true if the element exists and sets the returnVal pointer equal to the elements data
            //returns false if not
            bool retrieve(TypeOfKey key, TypeToMap* returnVal)
            {
                //holds the return value form the trees search method
                MapNode data, temp(key);
                //exists will be true if the key exists in the tree
                bool exists = tree->retrieve(key, &data);
                //if the element exists
                if(exists)
                {
                    //set the return value equal to the elements data
                    *returnVal = data.data;
                    return true;
                }
                return false;
            }

            //calls the tree pre-order print function
            void print()
            {
                tree->print();
            }
    };
}

#endif // MAP_HPP_INCLUDED
