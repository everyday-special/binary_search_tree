/* Purpose: Defines the menu class
 * Author: Matthew Lidell
 * CS260 Project 3
 * Date: 11/7/21
 * file: menu.h
 */
#pragma once
#include "table.h"


class Menu
/* UI For using the Table ADT
 * This class has 3 data attributes:
 * 	-table: pointer to the Table object the user is populating and interacting with
 * 	-results: array of Websites to hold data retrieved from table
 * 	-results_size: pointer to int containing the number of Websites retrieved and held in results
 * This class has 3 public member functions:
 * 	-Default Construtor
 * 	-Default Destructor
 * 	-run() - runs the main menu looping allowing the user to view and select menu options for populating and interacting with the table
 * This class has has 12 private member functions:
 * 	-printMenu() - prints the menu options
 * 	-getReply() - gets the user input
 * 	-doCommand() - performs command based on user input
 * 	-displayAll() - displays all Websites in the table
 * 	-displayTopic() - displays all websites of a user-specified topic
 * 	-insert() - get website data from user and add a new topic
 * 	-getWebsite() - gets website data from user
 * 	-retrieve() - retrieves all websites for a given topic and stores it in this->results
 * 	-viewRetrievedResults - views previously retrieved results
 * 	-edit() - edits a user specified website
 * 	-viewChainLengths() - views the length of the individual chains in the hash table to evaluate hash function performance
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
