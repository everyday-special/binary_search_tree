/* Matthew Lidell
 * 11/22/21
 * File: website.cpp
 * Purpose: Defines website class member and friend functions
 */
#include "website.h"

Website::Website()
/* Default constructor
 * Parameters: None
 * Return: None
 */
{
	topic = nullptr;
	keyword = nullptr;
	address = nullptr;
	summary = nullptr;
	review = nullptr;
	rating = nullptr;
}



Website::Website(const char newTopic[], const char newKeyword[], const char newAddress[], const char newSummary[], const char newReview[], const int newRating)
/* Overloaded constructor for website class
 * Parameters:
 * 	-const char newTopic[] - cstring representing the new website's topic
 * 	-const char newKeyword[] - cstring representing the new website's keyword
 * 	-const char newAddress[] - cstring representing the new website's address
 * 	-const char newSummary[] - cstring representing the new website's summary
 * 	-const char newReview[] - cstring representing the new website's review
 * 	-const int newRating - integer representing the new website's rating from 1 to 5
 * Return: None
 */
{
	int strLen; // Stores length of input strings

	strLen = strlen(newTopic);
	this->topic = new char[++strLen];
	strcpy(this->topic, newTopic);
	strLen = strlen(newKeyword);
	this->keyword = new char[++strLen];
	strcpy(this->keyword, newKeyword);
	strLen = strlen(newAddress);
	this->address = new char[++strLen];
	strcpy(this->address, newAddress);
	strLen = strlen(newSummary);
	this->summary = new char[++strLen];
	strcpy(this->summary, newSummary);
	strLen = strlen(newReview);
	this->review = new char[++strLen];
	strcpy(this->review, newReview);
	this->rating = new int(newRating);
}



Website::Website(const Website& srcWebsite)
/* Copy constructor for website class
 * Parameters:
 * 	-const Website srcWebsite - website object whose data is being copied into a new website object
 * Return: None
 */
{
        int strLen; // Stores length of input strings

	strLen = strlen(srcWebsite.topic);
        this->topic = new char[++strLen];
        strcpy(this->topic, srcWebsite.topic);
	strLen = strlen(srcWebsite.keyword);
        this->keyword = new char[++strLen];
        strcpy(this->keyword, srcWebsite.keyword);
        strLen = strlen(srcWebsite.address);
        this->address = new char[++strLen];
        strcpy(this->address, srcWebsite.address);
        strLen = strlen(srcWebsite.summary);
        this->summary = new char[++strLen];
        strcpy(this->summary, srcWebsite.summary);
        strLen = strlen(srcWebsite.review);
        this->review = new char[++strLen];
        strcpy(this->review, srcWebsite.review);
        this->rating = new int((*srcWebsite.rating));
}



Website::~Website()
/* Destructor for website class
 * Parameters: None
 * Return: None
 */
{
	delete [] topic;
	topic = nullptr;
	delete [] keyword;
	keyword = nullptr;
	delete [] address;
	address = nullptr;
	delete [] summary;
	summary = nullptr;
	delete [] review;
	review = nullptr;
	delete rating;
	rating = nullptr;
}



void Website::operator=(const Website& srcWebsite)
/* Overloaded assignment operator for website class
 * Parameters:
 *      -const Website& srcWebsite - website object whose data is being copied into a new website object
 * Return: None
 */
{
	int strLen; // Stores length of input strings

	delete [] topic;
	delete [] keyword;
	delete [] address;
	delete [] summary;
	delete [] review;
	delete rating;

        strLen = strlen(srcWebsite.topic);
        this->topic = new char[++strLen];
        strcpy(this->topic, srcWebsite.topic);
	strLen = strlen(srcWebsite.keyword);
        this->keyword = new char[++strLen];
        strcpy(this->keyword, srcWebsite.keyword);
        strLen = strlen(srcWebsite.address);
        this->address = new char[++strLen];
        strcpy(this->address, srcWebsite.address);
        strLen = strlen(srcWebsite.summary);
        this->summary = new char[++strLen];
        strcpy(this->summary, srcWebsite.summary);
        strLen = strlen(srcWebsite.review);
        this->review = new char[++strLen];
        strcpy(this->review, srcWebsite.review);
        this->rating = new int((*srcWebsite.rating));
}



void Website::getKeyword(char result[])
/* Accessor function for keyword data member
 * Parameters: char result[] - cstring that holds the value of keyword
 * Return: None
 */
{
	strcpy(result, this->keyword);
}



void Website::getTopic(char result[])
/* Accessor function for topic data member
 * Parameters: char result[] - cstring that holds the value of topic
 * Return: None
 */
{
	strcpy(result, this->topic);
}



void Website::getAddress(char result[])
/* Accessor function for address data member
 * Parameters: char result[] - cstring that holds the value of address
 * Return: None
 */
{
	strcpy(result, this->address);
}



void Website::getSummary(char result[])
/* Accessor function for summary data member
 * Parameters: char result[] - cstring that holds the value of summary
 * Return: None
 */
{
	strcpy(result, this->summary);
}



void Website::getReview(char result[])
/* Accessor function for review data member
 * Parameters: char result[] - cstring that holds the value of review
 * Return: None
 */
{
	strcpy(result, this->review);
}



int Website::getRating()
/* Accessor function for rating data member
 * Parameters: None
 * Return: int - value of rating data member
 */
{
	return *rating;
}



bool Website::isNotEmpty()
/* Checks to see if any website data is stored in website
 * Parameters: None
 * Return: bool - True if data is stored in website, false if not
 */
{
	if (keyword)
		return true;
	else
		return false;
}



std::ostream& operator<<(std::ostream& out, const Website& website)
/* Overloaded << operator for website class
 * Parameters:
 * 	-std::ostream& out - ostream object
 * 	-const Website& website - website object whose data is being printed
 * Return:
 * 	-std::ostream& - ostream object with data being printed
 */
{
	out << "Keyword: " << website.keyword;
	out << "\nTopic: " << website.topic;
	out << "\nAddress: " << website.address;
	out << "\nSummary: " << website.summary;
	out << "\nReview: " << website.review;
	out << "\nRating: " << *(website.rating) << "/5" << std::endl;
	return out;
}
