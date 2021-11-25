/* Matthew Lidell
 * CS 260
 * Project 4
 * 11/24/21
 * File: treenode.h
 * Purpose: Defines the node class
 */
#pragma once
#include "website.h"

class node
/*
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
		//int * data;
		Website * data;
		node * left;
		node * right;
		friend class Table;
};
