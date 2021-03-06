#include<iostream>
#include<cstring>
#include "Book.h"

void Book::copy(const Book& other)
{
	this->setAuthor(other.getAuthor());
	this->setTitle(other.getTitle());
	this->setFileName(other.getFileName());
	this->setDescription(other.getDescription());
	this->setRating(other.getRating());
	this->setISBN(other.getISBN());
}

void Book::clear()
{
	delete[] this->author;
	this->author = nullptr;

	delete[] this->title;
	this->title = nullptr;

	delete[] this->fileName;
	this->fileName = nullptr;

	delete[] this->description;
	this->description = nullptr;

	delete[] this->isbn;
	this->isbn = nullptr;
}

Book::Book()
{
	this->author = nullptr;
	this->title = nullptr;
	this->description = nullptr;
	this->rating = 0;
	this->fileName = nullptr;
	this->isbn = nullptr;
}

Book::Book(char* author, char* title, char* fileName, char* description, double rating, char* isbn)
{

	this->setAuthor(author);
	this->setTitle(title);
	this->setFileName(fileName);
	this->setDescription(description);
	this->setRating(rating);
	this->setISBN(isbn);
}


Book::Book(const Book& other)
{
	this->copy(other);
}

Book& Book::operator=(const Book& other)
{
	if (this != &other) {
		this->clear();
		this->copy(other);
	}
	return *this;
}

Book::~Book()
{
	this->clear();
}

char* Book::getAuthor() const
{
	return this->author;
}

void Book::setAuthor(const char* author)
{
	/*if (this->author != nullptr && strlen(this->author) > 0) {
		delete[] this->author;
		this->author = nullptr;
	}*/

	if(author != nullptr) {
		this->author = new char[strlen(author) + 1];
		strcpy_s(this->author, strlen(author) + 1, author);
	}
    else{
        this->author = nullptr;
    }
}

char* Book::getTitle() const
{
	return this->title;
}

void Book::setTitle(const char* title)
{
	/*if (this->title != nullptr) {
		delete[] this->title;
		this->title = nullptr;
	}*/

	if (title != nullptr) {
		this->title = new char[strlen(title) + 1];
		strcpy_s(this->title, strlen(title) + 1, title);
	}
    else {
        this->title = nullptr;
    }
}

char* Book::getDescription() const
{
	return this->description;
}

void Book::setDescription(const char* description)
{
	/*if (this->description != nullptr) {
		delete[] this->description;
		this->description = nullptr;
	}*/

	if (description != nullptr) {
		this->description = new char[strlen(description) + 1];
		strcpy_s(this->description, strlen(description) + 1, description);
	}
    else {
        this->description = nullptr;
    }
}

double Book::getRating() const
{
	return this->rating;
}

void Book::setRating(double rating)
{
	if (rating > 0.0 && rating < 10.0) {
		this->rating = rating;
	}
	else {
		std::cout << "Rating cannot be more than 10 and less than 0!\n";
	}
}

char* Book::getISBN() const
{
	return this->isbn;
}

void Book::setISBN(const char* isbn)
{
	/*if (this->isbn != nullptr) {
		delete[] this->isbn;
		this->isbn = nullptr;
	}*/

	if (isbn != nullptr) {
		this->isbn = new char[strlen(isbn) + 1];
        strcpy_s(this->isbn, strlen(isbn) + 1, isbn);
	}
    else {
        this->isbn = nullptr;
    }
}

char* Book::getFileName() const
{
	return this->fileName;
}

void Book::setFileName(const char* fileName)
{
	/*if (this->fileName != nullptr) {
		delete[] this->fileName;
		this->fileName = nullptr;
	}*/

	if (fileName != nullptr) {
		this->fileName = new char[strlen(fileName) + 1];
		strcpy_s(this->fileName, strlen(fileName) + 1, fileName);
	}
    else {
        this->fileName = nullptr;
    }
}

void Book::pullInfoFromFile(std::istream& in)
{
	unsigned int authorLength;
	in.read((char*)&authorLength, sizeof(authorLength));
	this->author = new char[authorLength + 1];
	in.read(this->author, authorLength);
    this->author[authorLength] = '\0';

	unsigned int titleLength;
	in.read((char*)&titleLength, sizeof(titleLength));
	this->title = new char[titleLength + 1];
	in.read(this->title, titleLength);
    this->title[titleLength] = '\0';

    unsigned int filenameLength;
    in.read((char*)&filenameLength, sizeof(filenameLength));
    this->fileName = new char[filenameLength + 1];
    in.read(this->fileName, filenameLength);
    this->fileName[filenameLength] = '\0';

	unsigned int descriptionLength;
	in.read((char*)&descriptionLength, sizeof(descriptionLength));
	this->description = new char[descriptionLength + 1];
	in.read(this->description, descriptionLength);
    this->description[descriptionLength] = '\0';

	in.read((char*)&this->rating, sizeof(this->rating));

	unsigned int ISBNLength;
	in.read((char*)&ISBNLength, sizeof(ISBNLength));
	this->isbn = new char[ISBNLength + 1];
	in.read(this->isbn, ISBNLength);
    this->isbn[ISBNLength] = '\0';
}

std::ofstream& operator<<(std::ofstream& out, const Book& book)
{
	unsigned int authorLength = std::strlen(book.author);
	out.write((char*)&authorLength, sizeof(authorLength));
	out.write((char*)book.author, authorLength);

	unsigned int titleLength = std::strlen(book.title);
	out.write((char*)&titleLength, sizeof(titleLength));
	out.write((char*)book.title, titleLength);

	unsigned int descriptionLength = std::strlen(book.description);
	out.write((char*)&descriptionLength, sizeof(descriptionLength));
	out.write((char*)book.description, descriptionLength);

	out.write((char*)&book.rating, sizeof(book.rating));

	unsigned int ISBNLength = std::strlen(book.isbn);
	out.write((const char*)&ISBNLength, sizeof(ISBNLength));
	out.write((const char*)book.isbn, ISBNLength);

	unsigned int fileNameLength = std::strlen(book.fileName);
	out.write((const char*)&fileNameLength, sizeof(fileNameLength));
	out.write((const char*)book.fileName, fileNameLength);

	return out;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
	os << "Author: " << book.getAuthor() << ", Title: " << book.getTitle() 
		<< ", File Name: " << book.getFileName() << ", Rating: " << book.getRating()
		<< ", ISBN: " << book.getISBN() << '\n';
	
	return os;
}