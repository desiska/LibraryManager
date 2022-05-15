#pragma once
#include <fstream>

class Book {
    private:
        char* author;
        char* title;
        char* fileName;
        char* description;
        double rating;
        char* isbn;
        void copy(const Book& other);
        void clear();

    public:
        Book();
        Book(char* author, char* title, char* fileName, char* description, double rating, char* isbn);
        Book(const Book& other);
        Book& operator = (const Book& other);
        ~Book();

        char* getAuthor() const;
        void setAuthor(const char* author);
        char* getTitle() const;
        void setTitle(const char* title);
        char* getDescription() const;
        void setDescription(const char* description);
        double getRating() const;
        void setRating(double rating);
        char* getISBN() const;
        void setISBN(const char* isbn);
        char* getFileName() const;
        void setFileName(const char* fileName);
        void pullInfoFromFile(std::istream& in);

        friend std::ofstream& operator<<(std::ofstream& out, const Book& book);
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
};