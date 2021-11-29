/* Purpose: Defines the menu member functions
 * Author: Matthew Lidell
 * CS260 Project 3
 * Date: 11/7/21
 * file: menu.cpp
 */
#include "menu.h"


Menu::Menu()
/* Purpose: Default constructor for menu. Initializes attributes and loads data from file.
 * Parameters: None
 * Return: None
 */
{
	table = new Table(); // Instantiate table object
	retrieved = new Website();
	if (table->loadFromFile(FILENAME))
		std::cout << "Loaded websites from '" << FILENAME << "'." << std::endl;
	else
		std::cout << "Error loading data from '" << FILENAME << "'. No data was loaded." << std::endl;
}



Menu::~Menu()
/* Purpose: Default destructor for menu. Saves data to file and then deletes allocated memory.
 * Parameters: None
 * Return: None
 */
{
	if (table->saveToFile(FILENAME))
		std::cout << "Website data saved to '" << FILENAME << "'." << std::endl;
	else
		std::cout << "Error sacing data to '" << FILENAME << "'. No data was saved." << std::endl;
	delete table;
	table = nullptr;
	delete retrieved;
	retrieved = nullptr;
}



void Menu::run()
/* Purpose: Runs the main menu loop
 * Parameters: None
 * Return: None
 */
{
	char reply; // Used to store user input

	do
	{
		printMenu();
		reply = getReply();
		doCommand(reply);
	}
	while (reply != 'q');
}



void Menu::printMenu()
/* Purpose: Prints the menu options
 * Parameters: None
 * Return None
 */
{
	std::cout << "\nMenu Options:" << std::endl;
	std::cout << "a) Display all websites in the table." << std::endl;
	std::cout << "b) Insert a new website into the table." << std::endl;
	std::cout << "c) Remove a specific website." << std::endl;
	std::cout << "d) Remove all websites of a specific topic." << std::endl;
	std::cout << "e) Retrieve the entry for a specific website" << std::endl;
	std::cout << "f) View last retrieved website." << std::endl;
	std::cout << "g) View the height of the table." << std::endl;
	std::cout << "q) Quit." << std::endl;
}



const char Menu::getReply()
/* Pupose: Gets character input representing menu selection from user
 * Parameters: None
 * Return: None
 */
{
	std::cout << "Please make a selection from the options shown above: " << std::endl;
	return getChar();
}



void Menu::doCommand(const char reply)
/* Purpose: Performs command based on the user input
 * Parameter: const char reply - char representing user menu selection
 * Return: None
 */
{
	std::cout << std::endl;
	switch (reply)
	{
		case 'a':
			display();
			break;
		case 'b':
			insert();
			break;
		case 'c':
			remove();
			break;
		case 'd':
			removeTopic();
			break;
		case 'e':
			retrieve();
			break;
		case 'f':
			viewRetrieved();
			break;
		case 'g':
                        checkHeight();
                        break;
		case 'q':
			std::cout << "Exiting menu..." << std::endl;
			break;
		default:
			std::cout << "'" << reply << "' is not a valid option. Please try again." << std::endl;
	}
}



const Website Menu::getWebsite()
/* Purpose: Gets website data from user, creates that website and returns it
 * Parameters: None
 * Return: const Website - website created from user input
 */
{
	char newKeyword[MAX_SIZE];
	char newTopic[MAX_SIZE];
	char newAddress[MAX_SIZE];
	char newSummary[MAX_SIZE];
	char newReview[MAX_SIZE];
	int newRating;

	std::cout << "Please enter a unique keyword for the website: ";
	getString(newKeyword);
	lower(newKeyword);
	std::cout << "Please enter the website's topic: ";
	getString(newTopic);
	std::cout << "Please enter the website's address: ";
	getString(newAddress);
	std::cout << "Please enter a summary of the website: ";
	getString(newSummary);
	std::cout << "Please enter your review of the website: ";
	getString(newReview);
	std::cout << "Please enter a rating of the website from 1 to 5: ";
	newRating = getInt();
	while (newRating < 1 || newRating > 5)
	{
		std::cout << "Please enter a rating from 1 to 5: ";
		newRating = getInt();
	}
	return Website(newTopic, newKeyword, newAddress, newSummary, newReview, newRating);
}



void Menu::insert()
/* Purpose: Inserts a new user created website
 * Parameters: None
 * Return: None
 */
{
	Website newWebsite = getWebsite();

	if (table->insert(newWebsite))
		std::cout << "\nWebsite added." << std::endl;
	else
		std::cout << "\nWebsite was already in the table." << std::endl;
}



void Menu::display()
/* Purpose: Displays all the data in the hash table
 * Parameters: None
 * Return: None
 */
{
	bool ret = table->display();
	if (!ret)
		std::cout << "\nTable is empty." << std::endl;
}



void Menu::retrieve()
/* Purpose: Retrieves a list of all websites matching a user specific topic. Stores these results in this->results
 * Parameters: None
 * Return: None
 */
{
	char query[MAX_SIZE];
	bool ret;

	std::cout << "\nPlease enter the keyword for which you wish to retrieve from the table: " << std::endl;
	getString(query);
	lower(query);
	ret = table->retrieve(query, *retrieved);
	if (ret)
		std::cout << "\nSuccessfully retrieved data for '" << query << "'. Select option 'f' in the menu to view the retrieved data." << std::endl;
	else
		std::cout << "\nNo websites were found with a keyword matching '" << query << "'. Please try again." << std::endl;
}



void Menu::viewRetrieved()
/* Purpose: Views the websites that were previously retrieved and stored in this->results
 * Parameters: None
 * Return: None
 */
{
	if (!(*retrieved).isNotEmpty())
		std::cout << "\nNo websites have been retrieved." << std::endl;
	else
	{
		std::cout << "\nLast retrieved website: " << std::endl;
		std::cout << *retrieved << std::endl;
	}
}



void Menu::remove()
/* Purpose: Removes all websites with a rating of 1 from the table. Prints the amount of websites that were removed.
 * Parameters: None
 * Return: None
 */
{
	char keyword[MAX_SIZE];

	std::cout << "Please enter the keyword for the website you wish to remove: ";
	getString(keyword);
	lower(keyword);
	if (table->remove(keyword))
		std::cout << "\n'" << keyword << "' was removed." << std::endl;
	else
		std::cout << "\nNo websites were removed." << std::endl;
}



void Menu::removeTopic()
{
	char topic[MAX_SIZE];

	std::cout << "Please enter the topic you wish to remove from the table: ";
	getString(topic);
	if (table->removeTopic(topic))
		std::cout << "\nAll websites with topic '" << topic << "' were removed from the table." << std::endl;
	else
		std::cout << "\nNo websites were removed." << std::endl;
}



void Menu::checkHeight()
/* Purpose: Prints the length of all the chains in the hash table to monitor hashing performance
 * Parameters: None
 * Return: None
 */
{
	int height = table->getHeight();
	int size = table->getSize();
	double result = log2(size);
	std::cout << "\nSize of the table: " << table->getSize() << std::endl;
	std::cout << "Height of the table: " << height << std::endl;
	std::cout << "Log2 of size plus 1: " << round(result) + 1 << std::endl;
}
