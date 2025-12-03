#include <iostream>
#include <limits>
using namespace std;


float dayAverage(float* row, int h) {
    float sum = 0;
    for (int i = 0; i < h; i++) {
        sum += *(row + i);
    }
    return sum / h;
}
float overallAverage(float** p, int d, int h) {
    float totalSum = 0;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < h; j++) {
            totalSum += *(*(p + i) + j);
        }
    }
    return totalSum / (d * h);
}
void showHotDays(float** p, int d, int h) {
    float totalAvg = overallAverage(p, d, h);
    cout << "Общая средняя температура: " << totalAvg << endl;

    bool hasHotDays = false;
    cout << "Теплые дни:" << endl;
    for (int i = 0; i < d; i++) {
        float dayAvg = dayAverage(*(p + i), h);
        if (dayAvg > totalAvg) {
            cout << "День " << i + 1 << " (среднее = " << dayAvg << ")" << endl;
            hasHotDays = true;
        }
    }
    if (!hasHotDays) {
        cout << "Теплые дни отсутствуют." << endl;
    }
}


void lab4() {
    int d, h;

    while (true) {
        cout << "Введите количество дней (1-30): ";
        cin >> d;
        if (cin.fail() || d <= 0 || d > 30) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Количество дней должно быть от 1 до 30." << endl;
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Введите количество измерений в дне (1-24): ";
        cin >> h;
        if (cin.fail() || h <= 0 || h > 24) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Количество измерений должно быть от 1 до 24." << endl;
        }
        else {
            break;
        }
    }

    float** data = new float* [d];
    for (int i = 0; i < d; i++) {
        *(data + i) = new float[h];
    }

    for (int i = 0; i < d; i++) {
        cout << "День " << i + 1 << " (введите " << h << " значений от -50 до 50): ";
        for (int j = 0; j < h; j++) {
            while (true) {
                cin >> *(*(data + i) + j);
                if (cin.fail() || *(*(data + i) + j) < -50 || *(*(data + i) + j) > 50) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ошибка! Введите значение от -50 до 50: ";
                }
                else {
                    break;
                }
            }
        }
    }

    showHotDays(data, d, h);

    for (int i = 0; i < d; i++) {
        delete[] * (data + i);
    }
    delete[] data;
}





int main() {
    setlocale(LC_ALL, "Russian");
    lab4();
    return 0;
}