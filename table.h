/* Matthew Lidell
 * CS 260
 * Project 4
 * 11/22/21
 * File: table.h
 * Purpose: Defines the BST table class
 */
#pragma once
#include "website.h"
#include "utils.h"

struct node
{
	node(const int& val)//const Website& website)
	{
	//data = new Website(website);
		data = new int(val);
		left = nullptr;
		right = nullptr;
	}
	~node()
	{
		delete data;
		data = nullptr;
		left = nullptr;
		right = nullptr;
	}
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
	int * data;
	//Website * data;
	node * left;
	node * right;
};

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
		bool insert(node *& root, const int& val);
		bool remove(node *& root, const int& val);
		void deleteNode(node *& toDelete);
		/*void remove(node * root, const char keyword[]);
		void removeTopic(node * root, const char keyword[]);*/
		void rotate(node *& root);
		void singleLeft(node *& root);
		void singleRight(node *& root);
		void  doubleLeft(node *& root);
		void doubleRight(node *& root);
		//void retrieve(Node * root, const char keyword[], Website *& retrieved);
};
