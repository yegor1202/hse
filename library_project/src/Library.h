#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <vector>
#include <string>
#include <fstream>

class Library {
private:
    std::vector<Book> books;
    std::vector<User> users;
    std::string dataFile;
    
    void parseBookFromFile(std::ifstream& file);
    void parseUserFromFile(std::ifstream& file);

public:
    Library(const std::string& filename = "data/library_data.txt");
    
    void addBook(const Book& book);
    void addUser(const User& user);
    void borrowBook(const std::string& userName, const std::string& isbn);
    void returnBook(const std::string& isbn);
    
    Book* findBookByISBN(const std::string& isbn);
    User* findUserByName(const std::string& name);
    
    void displayAllBooks() const;
    void displayAllUsers() const;
    
    void saveToFile() const;
    void loadFromFile();
    
    const std::vector<Book>& getBooks() const { return books; }
    const std::vector<User>& getUsers() const { return users; }
};

#endif