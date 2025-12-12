#include "User.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

User::User(const string& name, const string& userId) 
    : name(name), userId(userId), maxBooksAllowed(3) {
    
    if (name.empty() || userId.empty()) {
        throw invalid_argument("Имя и ID пользователя не могут быть пустыми");
    }
}

string User::getName() const { return name; }
string User::getUserId() const { return userId; }
const vector<string>& User::getBorrowedBooks() const { return borrowedBooks; }
int User::getMaxBooksAllowed() const { return maxBooksAllowed; }

bool User::canBorrowMore() const {
    return borrowedBooks.size() < maxBooksAllowed;
}

void User::addBook(const string& isbn) {
    if (isbn.empty()) {
        throw invalid_argument("ISBN не может быть пустым");
    }
    
    if (!canBorrowMore()) {
        throw runtime_error("Пользователь достиг лимита книг");
    }
    
    if (find(borrowedBooks.begin(), borrowedBooks.end(), isbn) != borrowedBooks.end()) {
        throw runtime_error("Книга с ISBN " + isbn + " уже взята пользователем");
    }
    
    borrowedBooks.push_back(isbn);
}

void User::removeBook(const string& isbn) {
    if (isbn.empty()) {
        throw invalid_argument("ISBN не может быть пустым");
    }
    
    auto it = find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
    if (it == borrowedBooks.end()) {
        throw runtime_error("Книга с ISBN " + isbn + " не найдена у пользователя");
    }
    
    borrowedBooks.erase(it);
}

void User::displayProfile() const {
    cout << "Имя: " << name << "\n"
         << "ID пользователя: " << userId << "\n"
         << "Взято книг: " << borrowedBooks.size() << " из " << maxBooksAllowed << "\n";
    
    if (!borrowedBooks.empty()) {
        cout << "Взятые книги (ISBN):\n";
        for (const auto& isbn : borrowedBooks) {
            cout << "  - " << isbn << "\n";
        }
    }
    cout << "\n";
}

string User::toFileString() const {
    string result = "USER\nName: " + name + "\nUserID: " + userId + "\n";
    
    result += "BorrowedBooks: ";
    if (borrowedBooks.empty()) {
        result += " ";
    } else {
        for (size_t i = 0; i < borrowedBooks.size(); ++i) {
            result += borrowedBooks[i];
            if (i != borrowedBooks.size() - 1) {
                result += "|";
            }
        }
    }
    result += "\nMaxBooks: " + to_string(maxBooksAllowed) + "\n";
    
    return result;
}