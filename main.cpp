#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// ==================================================
// структура самолёта
// ==================================================

struct Plane
{
    string model;         // марка самолёта
    string flightNumber;  // номер рейса
    double height;        // высота
};

// ==================================================
// проверка номера рейса
// формат должен быть:
// РЕЙС1234
// ==================================================

bool isValidFlightNumber(string flight)
{
    // минимальная длина:
    // "РЕЙС" + хотя бы 1 цифра
    if (flight.length() <= 6)
    {
        return false;
    }

    // проверяем первые символы
    if (flight.substr(0, 6) != "FLIGHT")
    {
        return false;
    }

    // проверяем что дальше идут только цифры
    for (int i = 6; i < flight.length(); i++)
    {
        if (!isdigit(flight[i]))
        {
            return false;
        }
    }

    return true;
}

// ==================================================
// проверка высоты
// ==================================================

bool isValidHeight(double height)
{
    // высота не может быть отрицательной
    // и не должна быть слишком большой
    if (height < 0 || height > 20)
    {
        return false;
    }

    return true;
}

// ==================================================
// определение высотного эшелона
// 0-2  -> 1
// 2-4  -> 2
// 4-6  -> 3
// и т.д.
// ==================================================

int getEchelon(double height)
{
    return static_cast<int>(height / 2) + 1;
}

// ==================================================
// пузырьковая индексная сортировка
// сортируем НЕ структуры, а массив индексов
// ==================================================

void bubbleSortIndexes(Plane planes[], int indexes[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            // получаем эшелоны соседних самолётов
            int echelon1 = getEchelon(planes[indexes[j]].height);
            int echelon2 = getEchelon(planes[indexes[j + 1]].height);

            // если левый больше правого
            // меняем только ИНДЕКСЫ
            if (echelon1 > echelon2)
            {
                int temp = indexes[j];
                indexes[j] = indexes[j + 1];
                indexes[j + 1] = temp;
            }
        }
    }
}

// ==================================================
// вывод таблицы
// ==================================================

void printMatrix(Plane planes[], int indexes[], int size)
{
    // вывод заголовка таблицы
    cout << left
         << setw(20) << "Model"
         << setw(20) << "Flight"
         << setw(15) << "Height"
         << setw(15) << "Echelon"
         << endl;

    cout << "----------------------------------------------------------------"
         << endl;

    // вывод данных
    for (int i = 0; i < size; i++)
    {
        int index = indexes[i];

        cout << left
             << setw(20) << planes[index].model
             << setw(20) << planes[index].flightNumber
             << setw(15) << fixed << setprecision(1) << planes[index].height
             << setw(15) << getEchelon(planes[index].height)
             << endl;
    }
}

// ==================================================
// MAIN
// ==================================================

int main()
{
    // открываем файл
    ifstream fin("data.txt");

    // проверка открытия файла
    if (!fin)
    {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    // максимальное количество записей
    const int SIZE = 100;

    // массив самолётов
    Plane planes[SIZE];

    // индексный массив
    int indexes[SIZE];

    // количество считанных записей
    int count = 0;

    // ==================================================
    // чтение данных из файла
    // ==================================================

    while (fin >> planes[count].model
               >> planes[count].flightNumber
               >> planes[count].height)
    {
        // проверка номера рейса
        if (!isValidFlightNumber(planes[count].flightNumber))
        {
            cout << "Ошибка номера рейса: "
                 << planes[count].flightNumber
                 << endl;

            continue;
        }

        // проверка высоты
        if (!isValidHeight(planes[count].height))
        {
            cout << "Ошибка высоты: "
                 << planes[count].height
                 << endl;

            continue;
        }

        // заполняем индексный массив
        indexes[count] = count;

        count++;
    }

    fin.close();

    // если файл пустой
    if (count == 0)
    {
        cout << "Нет корректных данных!" << endl;
        return 1;
    }

    // ==================================================
    // сортировка индексов
    // ==================================================

    bubbleSortIndexes(planes, indexes, count);

    // ==================================================
    // вывод результата
    // ==================================================

    printMatrix(planes, indexes, count);

    return 0;
}