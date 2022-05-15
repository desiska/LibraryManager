#pragma once

#include "Book.h"

class Library {
	private:
		Book* books;
		char* fileName;
		unsigned size;

		void copy(const Library& other);
		void clean();
		char* toLower(char* arr);
		void updateFile() const;

	public:
		Library();
		Library(const char* fileInfo);
		Library(const Library& other);
		Library& operator =(const Library& other);
		~Library();

		Book* getBooks() const;
		void setBooks(Book* books, unsigned size);
		char* getFileName() const;
		void setFileName(const char* fileName);
		unsigned getSize() const;
		void setSize(unsigned size);
		Book& addBook(const Book& book);
		Book* findBook(char* query, const char* criterian);
		void deleteBook(char* isbn);
		void sortBooks(const char* criterian);
		void printBooks() const;

};