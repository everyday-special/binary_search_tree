/* Matthew Lidell
 * CS 260
 * Project 4
 * 11/24/21
 * File: treenode.cpp
 * Purpose: Defines the node class
 */

#include "treenode.h"

node::node(const Website& website)
{
        data = new Website(website);
	//data = new int(val);
	left = nullptr;
	right = nullptr;
}



node::~node()
{
	delete data;
	data = nullptr;
	left = nullptr;
	right = nullptr;
}
