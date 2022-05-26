/* Purpose: Defines the menu class
 * Author: Matthew Lidell
 * CS260 Project 3
 * Date: 11/7/21
 */
#pragma once
#include <cmath>
#include "table.h"


class Menu
/* UI For using the Table ADT
 * This class has 3 data attributes:
 * 	-table: pointer to the Table object the user is populating and interacting with
 * 	-retrieved: pointer to website data last retrieved from table
 * This class has 3 public member functions:
 * 	-Default Construtor
 * 	-Default Destructor
 * 	-run() - runs the main menu looping allowing the user to view and select menu options for populating and interacting with the table
 * This class has has 11 private member functions:
 * 	-printMenu() - prints the menu options
 * 	-getReply() - gets the user input
 * 	-doCommand() - performs command based on user input
 * 	-display() - displays all Websites in the table in alphabetical order
 * 	-insert() - get website data from user and add a new topic
 * 	-getWebsite() - gets website data from user
 * 	-retrieve() - retrieves website data with a specific keyword match and stores it in this->retrieved
 * 	-viewRetrieved - views previously retrieved website data
 * 	-remove() - removes a website with a specific keyword match from the tree
 * 	-removeTopic() - removes all websites of a specific topic from the tree
 * 	-checkHeight() - checks height of tree and efficiency
 */
{
	public:
		Menu();
		~Menu();
		void run();

	private:
		void printMenu();
		const char getReply();
		void doCommand(const char reply);
		void display();
		void insert();
		const Website getWebsite();
		void retrieve();
		void viewRetrieved();
		void remove();
		void removeTopic();
		void checkHeight();
		Table * table; // Pointer to table object
		Website * retrieved; // Stores retrieved website between retrievals
};
