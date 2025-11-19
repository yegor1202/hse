#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;

const int MAX_BOOKS_AMOUNT = 1000;
const int MAX_NAME_LEN = 50;
const int DATE_LEN = 11;
const int RATING_LEN = 3;
const int MAX_AUTHOR = 100;

struct Book
{
    char date_start[DATE_LEN];
    char date_end[DATE_LEN];
    char rating[RATING_LEN];
    char author[MAX_AUTHOR];
    char name[MAX_NAME_LEN];
};

Book books[MAX_BOOKS_AMOUNT];
int booksCount = 0;

bool isValidDate(const char* date) {
    if (strlen(date) != 10) return false;
    
    if (date[2] != '.' || date[5] != '.') return false;
    
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && !isdigit(date[i])) {
            return false;
        }
    }
    
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + 
               (date[8] - '0') * 10 + (date[9] - '0');
    
    if (month < 1 || month > 12) return false;
    
    int daysInMonth;
    switch (month) {
        case 2:
            if (year % 4 == 0) {
                daysInMonth = 29;
            } else {
                daysInMonth = 28;
            }
            break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
        default:
            daysInMonth = 31;
    }
    
    if (day < 1 || day > daysInMonth) return false;
    
    return true;
}

void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void inputDateWithValidation(const char* message, char* date) {
    do {
        cout << message;
        cin >> date;
        
        if (!isValidDate(date)) {
            cout << "Ошибка: неверный формат даты! Используйте формат дд.мм.гггг\n";
        } else {
            break;
        }
    } while (true);
}

void loadBooks(const char *filename)
{
    ifstream fin(filename);

    if (!fin)
        return;

    while (fin >> books[booksCount].date_start 
               >> books[booksCount].date_end 
               >> books[booksCount].rating 
               >> books[booksCount].author 
               >> books[booksCount].name)
    {
        booksCount++;
    }

    fin.close();
}

void saveBookToFile(const char *filename, Book b)
{
    ofstream fout(filename, ios::app);

    if (!fout)
    {
        cout << "Ошибка при сохранении файла!" << endl;
        return;
    }

    fout << b.date_start << " " 
         << b.date_end << " " 
         << b.rating << " " 
         << b.author << " " 
         << b.name << endl;

    fout.close();
}

void addBook()
{
    if (booksCount >= MAX_BOOKS_AMOUNT)
    {
        cout << "Превышен лимит книг!" << endl;
        return;
    }

    Book b;

    inputDateWithValidation("Введите дату начала чтения книги (дд.мм.гггг): ", b.date_start);
    inputDateWithValidation("Введите дату окончания чтения книги (дд.мм.гггг): ", b.date_end);

    cout << "Введите оценку: ";
    cin >> b.rating;
    clearBuffer();

    cout << "Введите имя автора: ";
    cin.getline(b.author, MAX_AUTHOR);

    cout << "Введите название книги: ";
    cin.getline(b.name, MAX_NAME_LEN);

    books[booksCount++] = b;
    saveBookToFile("books.txt", b);

    cout << "Книга добавлена!\n";
}

void showAllBooks()
{
    if (booksCount == 0)
    {
        cout << "Нет данных о книгах.\n";
        return;
    }

    cout << "\n--- Все книги ---\n";
    cout << left << setw(15) << "Дата начала" 
                << setw(15) << "Дата окончания" 
                << setw(10) << "Оценка" 
                << setw(25) << "Автор" 
                << "Название" << endl;
    cout << "--------------------------------------------------------------------\n";

    for (int i = 0; i < booksCount; i++)
    {
        cout << left << setw(15) << books[i].date_start
                    << setw(15) << books[i].date_end
                    << setw(10) << books[i].rating
                    << setw(25) << books[i].author
                    << books[i].name << endl;
    }
}

void showStats()
{
    if (booksCount == 0)
    {
        cout << "Нет данных для анализа.\n";
        return;
    }

    cout << "\n--- Статистика ---\n";
    cout << "Всего прочитано книг: " << booksCount << endl;
}

void showMenu()
{
    cout << "\n=== Трекер книг ===\n";
    cout << "1. Добавить книгу\n";
    cout << "2. Показать все книги\n";
    cout << "3. Показать статистику\n";
    cout << "4. Выход\n";
    cout << "Выберите пункт: ";
}

int main()
{
    loadBooks("books.txt");

    int choice;

    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            showAllBooks();
            break;
        case 3:
            showStats();
            break;
        case 4:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор.\n";
        }

    } while (choice != 4);

    return 0;
}