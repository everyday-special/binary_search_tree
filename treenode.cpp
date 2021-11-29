/* Matthew Lidell
 * CS 260
 * Project 4
 * 11/24/21
 * File: treenode.cpp
 * Purpose: Defines the node class
 */

#include "treenode.h"

node::node(const Website& website)
/* Constructor for node
 * Parameters: Website website - website data being stored at this node. Passed by reference
 * Return: None
 */
{
        data = new Website(website);
	left = nullptr;
	right = nullptr;
}



node::~node()
/* Destructor for node
 * Parameters: None
 * Return: None
 */
{
	delete data;
	data = nullptr;
	left = nullptr;
	right = nullptr;
}
