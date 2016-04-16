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
