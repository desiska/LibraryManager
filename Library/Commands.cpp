#include<iostream>
#include "Library.h"
#include "Commands.h"

bool Commands::login()
{
	char username[1028];
	char password[1028];

	std::cout << "Username: ";
	std::cin.ignore();
	std::cin.getline(username, MAXLENGHT);
	std::cout << "Password: ";
	std::cin.ignore();
	std::cin.getline(password, MAXLENGHT);

	if (strcmp(username, this->USERNAME) == 0 &&
		strcmp(password, this->PASSWORD) == 0) {
		return true;
	}

	std::cout << "Invalid username or password!\n";

	return false;
}

void Commands::addBook(Library& library, bool isAdministrator)
{
	if (isAdministrator) {
		char author[1028];
		std::cout << "Author: ";
		std::cin.ignore();
		std::cin.getline(author, MAXLENGHT);

		char title[1028];
		std::cout << "Title: ";
		std::cin.ignore();
		std::cin.getline(title, MAXLENGHT);

		char fileNameBook[1028];
		std::cout << "File name: ";
		std::cin.ignore();
		std::cin.getline(fileNameBook, MAXLENGHT);

		char description[1028];
		std::cout << "Description: ";
		std::cin.ignore();
		std::cin.getline(description, MAXLENGHT);

		bool isValidRating = true;
		double rating;
		do
		{
			std::cout << "Rating: ";
			std::cin >> rating;
			std::cin.ignore();

			if (rating < 0.0 || rating > 10.0) {
				isValidRating = false;
			}

		} while (!isValidRating);

		char isbn[1028];
		std::cout << "ISBN code: ";
		std::cin.ignore();
		std::cin.getline(isbn, MAXLENGHT);

		Book book = library.addBook(Book(
			author, title, fileNameBook, description, rating, isbn
		));
	}
	else {
		std::cout << "This function is access only for admin!\n";
	}
}

void Commands::deleteBook(Library& library, bool isAdministrator)
{
	if (isAdministrator) {
		char isbn[1028];
		std::cout << "ISBN: ";
		std::cin.ignore();
		std::cin.getline(isbn, MAXLENGHT);

		library.deleteBook(isbn);
	}
	else {
		std::cout << "This function is access only for admin!\n";
	}
}

void Commands::printAllBooks(const Library& library)
{
	library.printBooks();
}

void Commands::sortBooks(Library& library)
{
	std::cout << "Please choose criterian by sort: \n"
		<< "[1] Author\n"
		<< "[2] Title\n"
		<< "[3] Rating\n";
	char choosen;

	do
	{
		std::cout << "Enter your choose: ";
		std::cin.ignore();
		std::cin >> choosen;

		if (choosen < 1 || choosen > 3) {
			std::cout << "There is not such criterian! Try again!\n";
		}

	} while (choosen < 1 || choosen > 3);

	if (choosen == '1') {
		library.sortBooks("author");
	}
	else if (choosen == '2') {
		library.sortBooks("title");
	}
	else {
		library.sortBooks("rating");
	}
	
	library.printBooks();
}

void Commands::findBook(Library& library)
{
	std::cout << "Please choose criterian by searching: \n"
		<< "[1] Author\n"
		<< "[2] Title\n"
		<< "[3] ISBN code\n"
		<< "[4] Description\n";
	char choosen;

	do
	{
		std::cout << "Enter your choose: ";
		std::cin.ignore();
		std::cin >> choosen;

		if (choosen < 1 || choosen > 4) {
			std::cout << "There is not such criterian! Try again!\n";
		}

	} while (choosen < 1 || choosen > 4);

	char query[1028];
	std::cout << "Enter a text which will be searching: ";
	std::cin.ignore();
	std::cin.getline(query, 1028);

	if (choosen == '1') {
		printBook(*library.findBook(query, "author"));
	}
	else if (choosen == '2') {
		printBook(*library.findBook(query, "title"));
	}
	else if (choosen == '3') {
		printBook(*library.findBook(query, "isbn"));
	}
	else {
		printBook(*library.findBook(query, "description"));
	}
}

void Commands::printBook(Book& book)
{
	if (&book == nullptr) {
		std::cout << "It is not found a book with this criterian!\n";
	}
	else {
		std::cout << book;
	}
}

void Commands::printBooks(Library& library)
{
	library.printBooks();
}

void Commands::printBookFile(Library& library)
{
	char isbn[1028];
	std::cout << "Enter a ISBN code for seraching: ";
	std::cin.ignore();
	std::cin.getline(isbn, 1028);

	Book book = *library.findBook(isbn, "isbn");

	if (&book == nullptr) {
		std::cout << "Book is not found!\n";
	}
	else {
		std::cout << book << '\n';
	}

	std::ifstream in;
	in.open(book.getFileName());
	if(in) {
		while (!in.eof()) {
			char output[1028];
			in.getline(output, MAXLENGHT);
			std::cout << output << '\n';
		}
	}
	in.close();
}

void Commands::startProgram()
{
	Library library = Library(BOOKSFILENAME);
	bool isAdministrator = false;

	std::cout << "Hello! Welcome to the Electronic Library! I hope you have a good experience! :D:D:D\n";

	std::cout << "Commands:\n"
		<< "[1] Log in like administrator\n"
		<< "[2] Sorted list of books\n"
		<< "[3] Searching book by criterian\n"
		<< "[4] Print books\n"
		<< "[5] Print file book\n"
		<< "[6] Add book \n"
		<< "[7] Remove book\n"
		<< "[0] Exit\n\n";

	std::cout << "Enter a command: ";
	char choosen;
	std::cin >> choosen;

	while (choosen != '0') {
		if (choosen == '1') {
			isAdministrator = login();
		}
		else if (choosen == '2') {
			this->sortBooks(library);
		}
		else if (choosen == '3') {
			this->findBook(library);
		}
		else if (choosen == '4') {
			this->printBooks(library);
		}
		else if (choosen == '5') {
			this->printBookFile(library);
		}
		else if (choosen == '6') {
			this->addBook(library, isAdministrator);
		}
		else if (choosen == '7') {
			this->deleteBook(library, isAdministrator);
		}
		else {
			std::cout << "There is not this command!\n";
		}

		std::cout << "Commands:\n"
			<< "[1] Log in like administrator\n"
			<< "[2] Sorted list of books\n"
			<< "[3] Searching book by criterian\n"
			<< "[4] Print books\n"
			<< "[5] Print file book\n"
			<< "[6] Add book \n"
			<< "[7] Remove book\n"
			<< "[0] Exit\n\n";

		std::cout << "Enter a command: ";
		std::cin >> choosen;
	}
}
