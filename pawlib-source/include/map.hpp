/** Map [PawLIB]
  * Version: 1.0
  *
  * A map/dictionary with a low dynamic allocation demand.
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
