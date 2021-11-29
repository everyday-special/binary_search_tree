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
 * Class has 6 private data members:
 * 	-topic - cstring containing the website topic
 * 	-keyword - cstring containing the website keyword
 * 	-address - cstring containing the website address
 * 	-summary - cstring containing the website summary
 * 	-review - cstring containing the website review
 * 	-rating - int from 1 to 5 representing the websites rating (out of 5)
 * Class has 12 public member and friend functions
 * 	-Default constructor
 * 	-Overloaded constructor
 * 	-Copy constructor
 * 	-Default destructor
 * 	-Overloaded assignment operator
 * 	-Overloaded insertion operator
 *	-getKeyword - accessor function for keyword data member
 *	-getTopic - accessor function for topic data member
 *	-getAddress - accessor function for address data member
 *	-getSummary - accessor function for summary data member
 *	-getReview - accessor function for review data member
 *	-getRating - accessor function for rating data member
 */
{
	public:
		Website();
		Website(const char newTopic[], const char newKeyword[], const char newAddress[], const char newSummary[], const char newReview[], const int newRating);
		Website(const Website& srcWebstire);
		~Website();
		void operator=(const Website& srcWebsite);
		void getKeyword(char result[]);
		void getTopic(char result[]);
		void getAddress(char result[]);
		void getSummary(char result[]);
		void getReview(char result[]);
		int getRating();
		bool isNotEmpty();
		
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
