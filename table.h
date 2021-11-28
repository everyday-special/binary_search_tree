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
/*
 */
{
	public:
		Table();
		~Table();
		int getHeight();
		bool insert(Website& newWebsite);
		bool remove(const char toRemove[]);
		bool removeTopic(const char topic[]);
		bool retrieve(const char keyword[], Website & retrieved);
		bool display();
		bool saveToFile(const char filename[]);
		bool loadFromFile(const char filename[]);

	private:
		node * root;
		int * size;
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
