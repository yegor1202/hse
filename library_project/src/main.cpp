#include "Library.h"
#include <iostream>
#include <limits>
#include <string>
#include <locale>

#ifdef _WIN32
    #define NOMINMAX
    #include <windows.h>
#endif

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMenu() {
    cout << "\n=== БИБЛИОТЕКА ===" << endl;
    cout << "1. Просмотреть все книги" << endl;
    cout << "2. Просмотреть всех пользователей" << endl;
    cout << "3. Добавить новую книгу" << endl;
    cout << "4. Зарегистрировать пользователя" << endl;
    cout << "5. Выдать книгу пользователю" << endl;
    cout << "6. Принять книгу от пользователя" << endl;
    cout << "7. Поиск книги по ISBN" << endl;
    cout << "8. Просмотреть профиль пользователя" << endl;
    cout << "9. Сохранить данные в файл" << endl;
    cout << "10. Выход" << endl;
    cout << "Ваш выбор: ";
}

int getChoice() {
    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 10) {
        cout << "Некорректный ввод. Введите число от 1 до 10: ";
        clearInput();
    }
    clearInput();
    return choice;
}

void addBookMenu(Library& library) {
    string title, author, isbn;
    int year;
    
    cout << "=== ДОБАВЛЕНИЕ НОВОЙ КНИГИ ===" << endl;
    cout << "Введите название: ";
    getline(cin, title);
    
    cout << "Введите автора: ";
    getline(cin, author);
    
    cout << "Введите год издания: ";
    while (!(cin >> year)) {
        cout << "Некорректный год. Попробуйте снова: ";
        clearInput();
    }
    clearInput();
    
    cout << "Введите ISBN: ";
    getline(cin, isbn);
    
    try {
        Book newBook(title, author, year, isbn);
        library.addBook(newBook);
        cout << "Книга успешно добавлена!" << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void addUserMenu(Library& library) {
    string name, userId;
    
    cout << "=== РЕГИСТРАЦИЯ ПОЛЬЗОВАТЕЛЯ ===" << endl;
    cout << "Введите фамилию пользователя: ";
    getline(cin, name);
    
    cout << "Введите ID пользователя (формат USR_001): ";
    getline(cin, userId);
    
    try {
        User newUser(name, userId);
        library.addUser(newUser);
        cout << "Пользователь успешно зарегистрирован!" << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void borrowBookMenu(Library& library) {
    string userName, isbn;
    
    cout << "=== ВЫДАЧА КНИГИ ===" << endl;
    cout << "Введите фамилию пользователя: ";
    getline(cin, userName);
    
    cout << "Введите ISBN книги: ";
    getline(cin, isbn);
    
    try {
        library.borrowBook(userName, isbn);
        cout << "Книга успешно выдана!" << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void returnBookMenu(Library& library) {
    string isbn;
    
    cout << "=== ВОЗВРАТ КНИГИ ===" << endl;
    cout << "Введите ISBN книги: ";
    getline(cin, isbn);
    
    try {
        library.returnBook(isbn);
        cout << "Книга успешно возвращена!" << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void searchBookMenu(Library& library) {
    string isbn;
    
    cout << "=== ПОИСК КНИГИ ПО ISBN ===" << endl;
    cout << "Введите ISBN: ";
    getline(cin, isbn);
    
    Book* book = library.findBookByISBN(isbn);
    if (book != nullptr) {
        book->displayInfo();
    } else {
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
    }
}

void viewUserProfileMenu(Library& library) {
    string name;
    
    cout << "=== ПРОСМОТР ПРОФИЛЯ ПОЛЬЗОВАТЕЛЯ ===" << endl;
    cout << "Введите фамилию пользователя: ";
    getline(cin, name);
    
    User* user = library.findUserByName(name);
    if (user != nullptr) {
        user->displayProfile();
    } else {
        cout << "Пользователь " << name << " не найден." << endl;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
#else
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
    
    Library library;
    
    cout << "Добро пожаловать в систему управления библиотекой!" << endl;
    
    bool running = true;
    while (running) {
        displayMenu();
        int choice = getChoice();
        
        try {
            switch (choice) {
                case 1:
                    library.displayAllBooks();
                    break;
                case 2:
                    library.displayAllUsers();
                    break;
                case 3:
                    addBookMenu(library);
                    break;
                case 4:
                    addUserMenu(library);
                    break;
                case 5:
                    borrowBookMenu(library);
                    break;
                case 6:
                    returnBookMenu(library);
                    break;
                case 7:
                    searchBookMenu(library);
                    break;
                case 8:
                    viewUserProfileMenu(library);
                    break;
                case 9:
                    library.saveToFile();
                    break;
                case 10:
                    cout << "Сохранение данных и выход..." << endl;
                    library.saveToFile();
                    running = false;
                    break;
            }
        } catch (const exception& e) {
            cout << "Произошла ошибка: " << e.what() << endl;
        }
        
        if (running && choice != 10) {
            cout << "\nНажмите Enter для продолжения...";
            cin.get();
        }
    }
    
    cout << "До свидания!" << endl;
    return 0;
}