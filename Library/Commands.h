#pragma once
#include "Library.h"

class Commands {
private:
    const char* BOOKSFILENAME = "books.bin";
    const char* USERNAME = "admin";
    const char* PASSWORD = "Admin123!";
    const int MAXLENGHT = 1028;

public:
    bool login();
	void addBook(Library& library, bool isAdministrator);
	void deleteBook(Library& library, bool isAdministrator);
    void printAllBooks(const Library& library);
    void sortBooks(Library& library);
    void findBook(Library& library);
    void printBook(Book& book);
    void printBooks(Library& library);
    void printBookFile(Library& library);
    void startProgram();
};