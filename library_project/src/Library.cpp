#include "Library.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <sstream>

Library::Library(const std::string& filename) : dataFile(filename) {
    try {
        loadFromFile();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка загрузки файла: " << e.what() << std::endl;
        std::cout << "Создана пустая библиотека.\n";
    }
}

void Library::addBook(const Book& book) {
    if (findBookByISBN(book.getISBN()) != nullptr) {
        throw std::runtime_error("Книга с ISBN " + book.getISBN() + " уже существует");
    }
    books.push_back(book);
}

void Library::addUser(const User& user) {
    if (findUserByName(user.getName()) != nullptr) {
        throw std::runtime_error("Пользователь с именем " + user.getName() + " уже существует");
    }
    users.push_back(user);
}

void Library::borrowBook(const std::string& userName, const std::string& isbn) {
    Book* book = findBookByISBN(isbn);
    User* user = findUserByName(userName);
    
    if (book == nullptr) {
        throw std::runtime_error("Книга с ISBN " + isbn + " не найдена");
    }
    
    if (user == nullptr) {
        throw std::runtime_error("Пользователь " + userName + " не найден");
    }
    
    if (!user->canBorrowMore()) {
        throw std::runtime_error("Пользователь достиг лимита книг");
    }
    
    book->borrowBook(userName);
    user->addBook(isbn);
}

void Library::returnBook(const std::string& isbn) {
    Book* book = findBookByISBN(isbn);
    
    if (book == nullptr) {
        throw std::runtime_error("Книга с ISBN " + isbn + " не найдена");
    }
    
    if (book->getIsAvailable()) {
        throw std::runtime_error("Книга уже доступна для выдачи");
    }
    
    std::string userName = book->getBorrowedBy();
    User* user = findUserByName(userName);
    
    if (user != nullptr) {
        user->removeBook(isbn);
    }
    
    book->returnBook();
}

Book* Library::findBookByISBN(const std::string& isbn) {
    for (auto& book : books) {
        if (book.getISBN() == isbn) {
            return &book;
        }
    }
    return nullptr;
}

User* Library::findUserByName(const std::string& name) {
    for (auto& user : users) {
        if (user.getName() == name) {
            return &user;
        }
    }
    return nullptr;
}

void Library::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "В библиотеке нет книг.\n";
        return;
    }
    
    std::cout << "=== КАТАЛОГ КНИГ ===\n";
    for (const auto& book : books) {
        book.displayInfo();
    }
}

void Library::displayAllUsers() const {
    if (users.empty()) {
        std::cout << "В библиотеке нет пользователей.\n";
        return;
    }
    
    std::cout << "=== ПОЛЬЗОВАТЕЛИ ===\n";
    for (const auto& user : users) {
        user.displayProfile();
    }
}

void Library::parseBookFromFile(std::ifstream& file) {
    std::string line;
    std::string title, author, isbn, borrowedBy;
    int year = 0;
    bool available = true;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        if (line.find("Title: ") == 0) {
            title = line.substr(7);
        } else if (line.find("Author: ") == 0) {
            author = line.substr(8);
        } else if (line.find("Year: ") == 0) {
            year = std::stoi(line.substr(6));
        } else if (line.find("ISBN: ") == 0) {
            isbn = line.substr(6);
        } else if (line.find("Available: ") == 0) {
            std::string availStr = line.substr(11);
            available = (availStr == "yes");
        } else if (line.find("BorrowedBy: ") == 0) {
            borrowedBy = line.substr(12);
        } else if (line == "---USERS---" || line == "USER") {
            break;
        } else if (line == "BOOK") {
            continue;
        }
    }
    
    if (!title.empty() && !author.empty() && !isbn.empty()) {
        Book book(title, author, year, isbn);
        if (!available) {
            book.borrowBook(borrowedBy);
        }
        books.push_back(book);
    }
}

void Library::parseUserFromFile(std::ifstream& file) {
    std::string line;
    std::string name, userId;
    std::vector<std::string> borrowedBooks;
    int maxBooks = 3;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        if (line.find("Name: ") == 0) {
            name = line.substr(6);
        } else if (line.find("UserID: ") == 0) {
            userId = line.substr(8);
        } else if (line.find("BorrowedBooks: ") == 0) {
            std::string booksStr = line.substr(15);
            if (!booksStr.empty() && booksStr != " ") {
                std::stringstream ss(booksStr);
                std::string isbn;
                while (std::getline(ss, isbn, '|')) {
                    borrowedBooks.push_back(isbn);
                }
            }
        } else if (line.find("MaxBooks: ") == 0) {
            maxBooks = std::stoi(line.substr(10));
        } else if (line == "BOOK") {
            file.seekg(-static_cast<int>(line.length() + 1), std::ios::cur);
            break;
        } else if (line == "USER") {
            continue;
        }
    }
    
    if (!name.empty() && !userId.empty()) {
        User user(name, userId);
        for (const auto& isbn : borrowedBooks) {
            try {
                user.addBook(isbn);
            } catch (...) {
            }
        }
        users.push_back(user);
    }
}

void Library::loadFromFile() {
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        std::cout << "Файл данных не найден. Будет создан новый.\n";
        return;
    }
    
    std::string line;
    bool inUserSection = false;
    
    while (std::getline(file, line)) {
        if (line == "BOOK") {
            parseBookFromFile(file);
        } else if (line == "USER") {
            parseUserFromFile(file);
        } else if (line == "---USERS---") {
            inUserSection = true;
        }
    }
    
    file.close();
}

void Library::saveToFile() const {
    std::ofstream file(dataFile);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи");
    }
    
    for (const auto& book : books) {
        file << book.toFileString() << std::endl;
    }
    
    file << "---USERS---" << std::endl << std::endl;
    
    for (const auto& user : users) {
        file << user.toFileString() << std::endl;
    }
    
    file.close();
    std::cout << "Данные успешно сохранены в файл.\n";
}