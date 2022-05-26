/* Matthew Lidell
 * 11/24/21
 * File: treenode.h
 * Purpose: Defines the node class
 */
#pragma once
#include "website.h"

class node
/* Class representing a node in the binary search tree
 * This class has 1 friend class:
 * 	-Table
 * This class has 3 private data members:
 * 	-data - website data stored at this node
 * 	-left - pointer to left child node
 * 	-right - pointer to right child node
 * This class has 3 public member and friend functions:
 * 	-Overloaded constructor
 * 	-Destructor
 * 	-Overlaoded insertion operator
 */
{
	public:
		node(const Website& website);
		~node();

		friend std::ostream& operator<<(std::ostream& out, const node& node)
			/* Purpose: Overloaded insertion operator for printing Website data
			 * Parameters:
			 *      -std::ostream& out - ostream object
			 *      -const Node& node - node to be printed
			 * Return: std::ostream& out - ostream object with data inserted
			 */
			{
			        out << *(node.data);
	        		return out;
			}


	private:
		Website * data; // Website data stored at this node
		node * left; // Pointer to left child/subtree
		node * right; // Pointer to right child/subtree
		friend class Table;
};
