#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BOOKS_AMOUNT 1000
#define MAX_NAME_LEN 50
#define DATE_LEN 11
#define RATING_LEN 3
#define FILENAME "books.txt"
#define MAX_AUTHOR 100

typedef struct {
    char date_start[DATE_LEN];
    char date_end[DATE_LEN];
    char rating[RATING_LEN];
    char author[MAX_AUTHOR];
    char name[MAX_NAME_LEN];
} Books;

Books books[MAX_BOOKS_AMOUNT];
int booksCount = 0;

int isValidDate(const char* date) {
    if (strlen(date) != 10) return 0;
    
    if (date[2] != '.' || date[5] != '.') return 0;
    
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && !isdigit(date[i])) {
            return 0;
        }
    }
    
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + 
               (date[8] - '0') * 10 + (date[9] - '0');
    
    
    if (month < 1 || month > 12) return 0;
    
    int daysInMonth;
    switch (month) {
        case 2:
            if (year % 4 == 0 ) {
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
    
    if (day < 1 || day > daysInMonth) return 0;
    
    return 1;
}

void inputDateWithValidation(const char* prompt, char* date) {
    do {
        printf("%s", prompt);
        scanf("%10s", date);
        
        if (!isValidDate(date)) {
            printf("Ошибка: неверный формат даты! Используйте формат дд.мм.гггг\n");
        } else {
            break;
        }
    } while (1);
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void showMenu() {
    printf("\n=== Трекер книг v1.0 ===\n");
    printf("1. Добавить книгу\n");
    printf("2. Показать все книги\n");
    printf("3. Показать статистику прочитанных книг\n");
    printf("4. Выход\n");
    printf("Выберите пункт: ");
}

void saveBookToFile(const char *filename, Books b) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Ошибка при сохранении файла!\n");
        return;
    }

    fprintf(file, "%11s %11s %3s %100s %49s\n", b.date_start, b.date_end, b.rating, b.author, b.name);
    fclose(file);
}

void addBook() {
    if (booksCount >= MAX_BOOKS_AMOUNT){
        printf("Превышен лимит добавляемых книг!\n");
        return;
    }

    Books b;
    
    inputDateWithValidation("Введите дату начала чтения книги (дд.мм.гггг): ", b.date_start);
    inputDateWithValidation("Введите дату окончания чтения книги (дд.мм.гггг): ", b.date_end);
    
    printf("Введите оценку: ");
    scanf("%5s", b.rating); 
    clearBuffer();

    printf("Введите имя автора: ");
    fgets(b.author, MAX_AUTHOR, stdin);
    b.author[strcspn(b.author, "\n")] = 0;
    
    printf("Введите название книги: ");
    fgets(b.name, MAX_NAME_LEN, stdin);
    b.name[strcspn(b.name, "\n")] = 0;

    books[booksCount++] = b;
    saveBookToFile(FILENAME, b);
    printf("Данные о книге добавлены!\n");
}

void loadBooks(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;

    while (fscanf(file, "%11s %11s %3s %100s %49s", 
                  books[booksCount].date_start,
                  books[booksCount].date_end,
                  books[booksCount].rating,
                  books[booksCount].author,
                  books[booksCount].name) == 5) {
        booksCount++;
    }

    fclose(file);
}

void showAllBooks() {
    if (booksCount == 0) {
        printf("Нет данных о прочтении книг.\n");
        return;
    }

    printf("\n--- Все книги ---\n");
    printf("%-40s%-45s%-15s%-30s%-s\n", "Дата начала чтения", "Дата окончания чтения", "Оценка", "Автор", "Название");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < booksCount; i++) {
        printf("%-24s%-26s%-10s%-35s%-s \n", 
               books[i].date_start,
               books[i].date_end,
               books[i].rating,
               books[i].author,
               books[i].name);
    }
}

void showStats() {
    if (booksCount == 0) {
        printf("Нет данных для анализа.\n");
        return;
    }
    
    printf("\n--- Статистика ---\n");
    printf("Всего прочитано: %d \n", booksCount);
}

int main() {
    loadBooks(FILENAME);
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);
        switch (choice) {
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
                 printf("Вы вышли из программы.\n");
                break;
            default:
                printf("Такого выбора нет");
        }
    } while (choice != 4);

    return 0;
}
