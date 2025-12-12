#include "Book.h"
#include <stdexcept>

using namespace std;

Book::Book(const string& title, const string& author, 
           int year, const string& isbn)
    : title(title), author(author), year(year), isbn(isbn),
      isAvailable(true), borrowedBy("") {
    
    if (title.empty() || author.empty() || isbn.empty()) {
        throw invalid_argument("Название, автор и ISBN не могут быть пустыми");
    }
    
    if (!isValidYear(year)) {
        throw invalid_argument("Год издания должен быть между 1450 и текущим годом");
    }
}

bool Book::isValidYear(int year) const {
    return year >= 1450 && year <= 2025;
}

string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
string Book::getISBN() const { return isbn; }
bool Book::getIsAvailable() const { return isAvailable; }
string Book::getBorrowedBy() const { return borrowedBy; }

void Book::borrowBook(const string& userName) {
    if (!isAvailable) {
        throw runtime_error("Книга уже выдана пользователю: " + borrowedBy);
    }
    if (userName.empty()) {
        throw invalid_argument("Имя пользователя не может быть пустым");
    }
    
    isAvailable = false;
    borrowedBy = userName;
}

void Book::returnBook() {
    if (isAvailable) {
        throw runtime_error("Книга уже доступна для выдачи");
    }
    
    isAvailable = true;
    borrowedBy = "";
}

void Book::displayInfo() const {
    cout << "Название: " << title << "\n"
         << "Автор: " << author << "\n"
         << "Год издания: " << year << "\n"
         << "ISBN: " << isbn << "\n"
         << "Статус: " << (isAvailable ? "Доступна" : "Выдана пользователю: " + borrowedBy) 
         << "\n\n";
}

string Book::toFileString() const {
    return "BOOK\nTitle: " + title + "\nAuthor: " + author + 
           "\nYear: " + to_string(year) + "\nISBN: " + isbn + 
           "\nAvailable: " + (isAvailable ? "yes" : "no") + 
           "\nBorrowedBy: " + borrowedBy + "\n";
}