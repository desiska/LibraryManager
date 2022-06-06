#include<iostream>
#include<cstring>
#include "Library.h"


void Library::copy(const Library& other)
{
	this->setBooks(other.getBooks(), other.getSize());
	this->setFileName(other.getFileName());
	this->setSize(other.getSize());
}

void Library::clean()
{
	delete[] this->books;
	this->books = nullptr;

	delete[] this->fileName;
	this->fileName = nullptr;
}

char* Library::toLower(char* arr)
{
	unsigned lenght = strlen(arr);
	char* result = new char[lenght + 1];

	for (unsigned i = 0; i < lenght; ++i) {
		if (arr[i] >= 'A' && arr[i] <= 'Z') {
			result[i] = arr[i] - 'A' + 'a';
		}
		else {
			result[i] = arr[i];
		}
	}
	result[lenght] = '\0';

	return result;
}


void Library::updateFile() const
{
	std::ofstream out;
	out.open(this->fileName);
	if (out) {
		out.write((char*)&this->size, sizeof(this->size));
		for (unsigned i = 0; i < this->size; ++i) {
			out << this->books[i];
		}
	}
	out.close();
}


Library::Library()
{
	this->fileName = nullptr;
	this->books = nullptr;
	this->size = 0;
}

Library::Library(const char* fileInfo)
{
    this->fileName = nullptr;
	this->setFileName(fileInfo);

    std::ifstream in;
	in.open(fileInfo, std::ios::binary);
	if (in) {
		unsigned booksCount;
		in.read((char*)&booksCount, sizeof(booksCount));

        this->setSize(booksCount);
        this->books = new Book [booksCount];

		for (unsigned i = 0; i < booksCount; ++i) {
			Book book;
			book.pullInfoFromFile(in);
            this->books[i] = book;
		}
	}
	in.close();
}

Library::Library(const Library& other)
{
	this->copy(other);
}

Library& Library::operator=(const Library& other)
{
	if (this != &other) {
		this->clean();
		this->copy(other);
	}

	return *this;
}

Library::~Library()
{
	this->clean();
}

Book* Library::getBooks() const
{
	return this->books;
}

void Library::setBooks(Book* books, unsigned size)
{
	this->books = new Book[size];

	for (unsigned i = 0; i < size; ++i) {
		this->books[i] = books[i];
	}
}

char* Library::getFileName() const
{
	return this->fileName;
}

void Library::setFileName(const char* fileName)
{
	if (this->fileName != nullptr) {
		delete[] this->fileName;
		this->fileName = nullptr;
	}

	if (fileName != nullptr) {
		this->fileName = new char[strlen(fileName) + 1];
		strcpy_s(this->fileName, strlen(fileName) + 1, fileName);
	}
}

unsigned Library::getSize() const
{
	return this->size;
}

void Library::setSize(unsigned size)
{
	this->size = size;
}

Book& Library::addBook(const Book& book)
{
	this->setSize(this->size + 1);

	Book* arr = new Book[this->size];

	for (unsigned i = 0; i < this->size - 1; ++i) {
		arr[i] = this->books[i];
	}
	arr[this->size - 1] = book;

	delete[] this->books;
	this->books = arr;

	this->updateFile();

	return this->books[this->size - 1];
}

Book* Library::findBook(char* query, const char* criterian)
{
	unsigned index = -1;
	bool isFind = false;
	char* toLowerQuery = toLower(query);

	for (unsigned i = 0; !isFind && i < this->size; ++i) {
		if (strcmp(criterian, "author") == 0) {
			char* toLowerAuthor = toLower(this->books[i].getAuthor());

			if (strcmp(toLowerQuery, toLowerAuthor) == 0) {
				isFind = true;
				index = i;
			}

			delete[] toLowerAuthor;
			toLowerAuthor = nullptr;
		}
		else if (strcmp(criterian, "title") == 0) {
			char* toLowerTitle = toLower(this->books[i].getTitle());

			if (strcmp(toLowerTitle, toLowerQuery) == 0) {
				isFind = true;
				index = i;
			}

			delete[] toLowerTitle;
			toLowerTitle = nullptr;
		}
		else if (strcmp(criterian, "isbn") == 0) {
			char* toLowerISBN = toLower(query);

			if (strcmp(toLowerQuery, toLowerISBN) == 0) {
				isFind = true;
				index = i;
			}

			delete[] toLowerISBN;
			toLowerISBN = nullptr;
		}
		else if (strcmp(criterian, "description") == 0) {
			char* toLowerDescription = toLower(this->books[i].getDescription());
			
			if (strstr(toLowerDescription, toLowerQuery) == 0) {
				isFind = true;
				index = i;
			}

			delete[] toLowerDescription;
			toLowerDescription = nullptr;
		}
		else {
			std::cout << "There is not another criterian to find a book!\n";
			i = this->size;
		}
	}
	
	delete[] toLowerQuery;
	toLowerQuery = nullptr;

	if (isFind) {
		return &this->books[index];
	}

	return nullptr;
}

void Library::deleteBook(char* isbn)
{
	bool isFind = false;
	int index = 0;

	for (unsigned i = 0; !isFind && i < this->size; ++i) {
		if (strcmp(this->books[i].getISBN(), isbn)) {
			isFind = true;
			index = i;
		}
	}

	if (isFind) {
		remove(this->books[index].getFileName());
		--this->size;

		Book* arr = new Book[this->size];

		for (unsigned i = 0; i < index; ++i) {
			arr[i] = this->books[i];
		}

		for (unsigned i = index; i < this->size; ++i) {
			arr[i] = this->books[i + 1];
		}

		delete[] this->books;
		this->books = arr;
	}
	else {
		std::cout << "Not found a book with this ISBN code!\n";
	}

}

void Library::sortBooks(const char* criterian)
{
	bool isCriterianValid = true;
	for (unsigned i = 0; isCriterianValid && i < this->size - 1; ++i) {
		for (unsigned j = i + 1; isCriterianValid && j < this->size; ++j) {
			bool hasSwap = false;

			if (strcmp(criterian, "author") == 0) {
				if (strcmp(this->books[i].getAuthor(), this->books[j].getAuthor()) > 0) {
					hasSwap = true;
				}
			}
			else if (strcmp(criterian, "title") == 0) {
				if (strcmp(this->books[i].getTitle(), this->books[j].getTitle()) > 0) {
					hasSwap = true;
				}
			}
			else if (strcmp(criterian, "rating") == 0) {
				if (this->books[i].getRating() > this->books[j].getRating()) {
					hasSwap = true;
				}
			}
			else {
				std::cout << "There is not another criterian!\n";
				isCriterianValid = false;
			}

			if (hasSwap) {
				Book temp = books[i];
				this->books[i] = this->books[j];
				this->books[j] = temp;
			}
		}
	}
}

void Library::printBooks() const
{
	for (unsigned i = 0; i < this->size; ++i) {
		std::cout << this->books[i];
	}
}
