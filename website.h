/* Matthew Lidell
 * CS 260
 * Project 4
 * 11/22/21
 * File: website.h
 * Purpose: Defines the website class
 */
#pragma once
#include <cstring>
#include <ostream>

class Website
/* Class representing an website information
 * Class has two friend classes:
 * 	-LinkedList
 * 	-Table
 * Class has 5 private data members:
 * 	-topic - cstring containing the website topic
 * 	-keyword - cstring containing the website keyword
 * 	-address - cstring containing the website address
 * 	-summary - cstring containing the website summary
 * 	-review - cstring containing the website review
 * 	-rating - int from 1 to 5 representing the websites rating (out of 5)
 * Class has 8 public member and friend functions
 * 	-Default constructor
 * 	-Overloaded constructor
 * 	-Copy constructor
 * 	-Default destructor
 * 	-Overloaded assignment operator
 * 	-setReview() - setter for review attribute
 * 	-setRating() - setter for rating attribute
 * 	-Overloaded insertion operator
 */
{
	public:
		Website();
		Website(const char newTopic[], const char newKeyword[], const char newAddress[], const char newSummary[], const char newReview[], const int newRating);
		Website(const Website& srcWebstire);
		~Website();
		void operator=(const Website& srcWebsite);
		void setReview(const char newReview[]);
		void setRating(const int& newRating);
		void getKeyword(char result[]);
		
		friend std::ostream& operator<<(std::ostream& out, const Website& website);

	private:
		char * topic; // Holds website topic
		char * keyword; // Holds website keyword
		char * address; // Holds website address
		char * summary; // Holds summary of website contents
		char * review; // Holds written review of website
		int * rating; // Holds numerical rating of 1 to 5
		friend class Tree;
		friend class node;
};
