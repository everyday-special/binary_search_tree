/* Matthew Lidell
 * CS 260
 * Project 4
 * 11/22/21
 * File: table.h
 * Purpose: Defines the BST table class
 */
#pragma once
#include <fstream>
#include "treenode.h"
#include "utils.h"

class Table
/* Class representing a Binary Search Tree for website data
 * This class has 2 private data members:
 * 	- node * root - pointer to root of the tree
 * 	- int * size - pointer to integer holding the size of the tree (how many nodes are stored)
 * This class has 10 public member functions:
 * 	-Constructor
 * 	-Destructor
 * 	-getHeight - gets height of the tree
 * 	-getSize - gets size of the tree
 * 	-insert - adds a new website to the tree
 * 	-remove - removes a website from the tree
 * 	-removeTopic - removes all websites with a specific topic from the tree
 * 	-retrieve - retrieves website data for a specific website
 * 	-display - prints the entire tree in alphabetical order
 * 	-saveToFile - saves the tree to a file
 * 	-loadFromFile - loads data from a file
 * This class has 14 private member functions:
 * 	-display - recursive backend for displaying all websites in alphabetical order
 * 	-getHeight - revursive backend for getting the height
 *	-destroy - recursively deletes all the nodes in the tree
 *	-insert - recursive backend for adding a new node to the tree
 *	-remove - recursive backend for removing a specific node from the tree
 *	-deleteNode - deletes a node from the tree and replaces it with the next order node
 *	-removeTopic - recursive backend for removing all nodes with a specific topic
 *	-rotate - determines what type of rotationg is needed to keep the tree balanced
 *	-singleLeft - performs a single left rotation on the subtree at root
 *	-singleRight - performs a single right rotation on the subtree at root
 *	-doubleLeft - performs a double left rotation on the subtree at root
 *	-doubleRight - performs a double right rotation on the subtree at root
 *	-retrieve - recursive backend for retrieving a specific website data
 *	-saveToFile - recursive backend for saving tree data to file
 */
{
	public:
		Table();
		~Table();
		int getHeight();
		int getSize();
		bool insert(Website& newWebsite);
		bool remove(const char toRemove[]);
		bool removeTopic(const char topic[]);
		bool retrieve(const char keyword[], Website & retrieved);
		bool display();
		bool saveToFile(const char filename[]);
		bool loadFromFile(const char filename[]);

	private:
		node * root; // Root of the tree
		int * size; // Size of the tree
		void display(node * root);
		int getHeight(node * root);
		void destroy(node *& root);
		node * insert(node *& root, Website& newWebsite);
		node * remove(node *& root, const char toRemove[]);
		node * deleteNode(node *& toDelete);
		node * removeTopic(node *& root, const char topic[]);
		node * rotate(node *& root);
		node * singleLeft(node *& root);
		node * singleRight(node *& root);
		node *  doubleLeft(node *& root);
		node * doubleRight(node *& root);
		bool  retrieve(node * root, const char keyword[], Website & retrieved);
		bool saveToFile(node * root, std::ofstream & outFile);
};
