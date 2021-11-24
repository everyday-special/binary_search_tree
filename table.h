/* Matthew Lidell
 * CS 260
 * Project 4
 * 11/22/21
 * File: table.h
 * Purpose: Defines the BST table class
 */
#pragma once
#include "treenode.h"
#include "utils.h"

class Table
/*
 */
{
	public:
		Table();
		~Table();
		int getHeight(node * root);
		bool insert(const int& val);
		bool remove(const int& val);
		/*bool insert(const Website& website);
		bool remove(const char keyword[]);
		bool removeTopic(const char topic[]);
		bool retrieve(const char keyword[], Website *& retrieved);*/
		void display();

	private:
		node * root;
		int * size;
		void display(node * root);
		void destroy(node *& root);
		node * insert(node *& root, const int& val);
		node * remove(node *& root, const int& val);
		node * deleteNode(node *& toDelete);
		/*node * remove(node * root, const char keyword[]);
		node * removeTopic(node * root, const char keyword[]);*/
		node * rotate(node *& root);
		node * singleLeft(node *& root);
		node * singleRight(node *& root);
		node *  doubleLeft(node *& root);
		node * doubleRight(node *& root);
		//void retrieve(Node * root, const char keyword[], Website *& retrieved);
};
