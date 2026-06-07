/******************************************************************************
* КАФЕДРА No304 1 КУРС ПРОГИНЖ *
* Летняя Практика *
*-----------------------------------------------------------------------------*
* Project Type : macOS Console Application *
* Project Name : summerPractice *
* File Name : main_final2.cpp *
* Language : C/C++ *
* Programmer : Тарасов Артём *
* Modified By : *
* Created : 02/06/2026 *
* Comment(s) : Работа со структурами и индексной сортировкой *
******************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// ---------- Глобальные константы ----------

const char TEST_01[] = "test_01_positive.txt";
const char TEST_02[] = "test_02_sort.txt";
const char TEST_03[] = "test_03_height_zero.txt";
const char TEST_04[] = "test_04_height_eshelon_border.txt";
const char TEST_05[] = "test_05_height_middle.txt";
const char TEST_06[] = "test_06_height_upper_border.txt";
const char TEST_07[] = "test_07_height_too_high.txt";
const char TEST_08[] = "test_08_wrong_flight_prefix.txt";
const char TEST_09[] = "test_09_missing_height.txt";
const char TEST_10[] = "test_10_too_many_flight_digits.txt";
const char TEST_11[] = "test_11_too_many_fields.txt";
const char TEST_12[] = "test_12_letters_in_flight.txt";
const char TEST_13[] = "test_13_double_dot_height.txt";
const char TEST_14[] = "test_14_full_duplicate.txt";
const char TEST_15[] = "test_15_same_flight_different_model.txt";
const char TEST_16[] = "test_16_empty_file.txt";

const int MAX_PLANES = 100;      // максимум корректных записей
const int MAX_LINE = 201;        // максимум символов в строке файла
const int MAX_FIELD = 41;        // максимум символов в одном поле
const int MAX_DIGITS = 9;        // максимум цифр после слова РЕЙС

// ---------- Структура ----------

struct Plane
{
    char model[MAX_FIELD];       // марка ЛА
    char flight[MAX_FIELD];      // номер рейса
    double height;               // высота ЛА
};

// ---------- Прототипы функций ----------

// Назначение: найти длину строки в байтах.
// Параметры: text[] - строка.
// Возвращает: длину строки.
int myLength(const char text[]);

// Назначение: найти видимую длину строки для красивой таблицы.
// Параметры: text[] - строка.
// Возвращает: видимую длину строки.
int visualLength(const char text[]);

// Назначение: скопировать строку.
// Параметры: to[] - куда копируем, from[] - откуда копируем.
void myCopy(char to[], const char from[]);

// Назначение: сравнить две строки.
// Параметры: a[], b[] - строки для сравнения.
// Возвращает: 1, если строки равны, иначе 0.
int myEqual(const char a[], const char b[]);

// Назначение: проверить символ на цифру.
// Параметры: symbol - проверяемый символ.
// Возвращает: 1, если символ цифра, иначе 0.
int isDigit(char symbol);

// Назначение: разбить строку файла на марку, рейс и высоту.
// Параметры: line[] - строка файла, model[] - марка, flight[] - рейс, heightText[] - высота текстом.
// Возвращает: 1, если в строке ровно 3 поля, иначе 0.
int splitLine(const char line[], char model[], char flight[], char heightText[]);

// Назначение: выбрать имя файла по номеру теста.
// Параметры: num - номер теста.
// Возвращает: имя файла.
const char* chooseFileName(int num);

// Назначение: считать и проверить данные из файла.
// Параметры: fn[] - имя файла, p[] - массив самолетов, idx[] - индексы, n - количество корректных записей.
// Возвращает: 1, если корректные записи есть, иначе 0.
int readData(const char fn[], Plane p[], int idx[], int &n);

// Назначение: отсортировать индексы пузырьком по эшелонам.
// Параметры: p[] - массив самолетов, idx[] - индексы, n - количество записей.
void sortIndexes(const Plane p[], int idx[], int n);

// Назначение: вывести таблицу самолетов.
// Параметры: p[] - массив самолетов, idx[] - порядок вывода, n - количество записей, title[] - заголовок.
void printTable(const Plane p[], const int idx[], int n, const char title[]);

// ---------- Главная функция ----------

int main()
{
    cout << "============================================================" << endl;
    cout << "Ознакомительная практика. Вариант 21" << endl;
    cout << "Сортировка самолетов по высотным эшелонам" << endl;
    cout << "============================================================" << endl;

    cout << endl << "Выберите тестовый файл:" << endl;
    cout << "1  - " << TEST_01 << endl;
    cout << "2  - " << TEST_02 << endl;
    cout << "3  - " << TEST_03 << endl;
    cout << "4  - " << TEST_04 << endl;
    cout << "5  - " << TEST_05 << endl;
    cout << "6  - " << TEST_06 << endl;
    cout << "7  - " << TEST_07 << endl;
    cout << "8  - " << TEST_08 << endl;
    cout << "9  - " << TEST_09 << endl;
    cout << "10 - " << TEST_10 << endl;
    cout << "11 - " << TEST_11 << endl;
    cout << "12 - " << TEST_12 << endl;
    cout << "13 - " << TEST_13 << endl;
    cout << "14 - " << TEST_14 << endl;
    cout << "15 - " << TEST_15 << endl;
    cout << "16 - " << TEST_16 << endl;
    cout << "Номер теста: ";

    int num;                    // номер выбранного теста
    cin >> num;

    const char *fn = chooseFileName(num); // имя выбранного файла

    Plane *p = new Plane[MAX_PLANES];     // массив самолетов
    int *idx = new int[MAX_PLANES];       // массив индексов
    int n = 0;                            // количество корректных записей

    cout << endl << "Выбран файл: " << fn << endl;

    if (readData(fn, p, idx, n))
    {
        printTable(p, idx, n, "Корректные данные до сортировки");
        sortIndexes(p, idx, n);
        printTable(p, idx, n, "Корректные данные после сортировки");
    }
    else
    {
        cout << endl << "Таблица не выводится: корректных данных нет." << endl;
    }

    delete[] p;
    delete[] idx;

    return 0;
}

// ---------- Реализации функций ----------

int myLength(const char text[])
{
    int length = 0;

    while (text[length] != '\0')
    {
        length++;
    }

    return length;
}

int visualLength(const char text[])
{
    int length = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        unsigned char symbol = (unsigned char)text[i];

        if (symbol < 128 || (symbol & 192) != 128)
        {
            length++;
        }
    }

    return length;
}

void myCopy(char to[], const char from[])
{
    int i = 0;

    while (from[i] != '\0')
    {
        to[i] = from[i];
        i++;
    }

    to[i] = '\0';
}

int myEqual(const char a[], const char b[])
{
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return 0;
        }

        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}

int isDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

int splitLine(const char line[], char model[], char flight[], char heightText[])
{
    char fields[4][MAX_FIELD] = {};  // fields - поля строки: марка, рейс, высота, лишнее поле
    int fieldNumber = 0;             // fieldNumber - номер текущего поля
    int position = 0;                // position - позиция символа внутри текущего поля
    int tooLong = 0;                 // tooLong - признак слишком длинного поля

    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == ' ' || line[i] == '\t')
        {
            if (position > 0)
            {
                if (fieldNumber < 4)
                {
                    fields[fieldNumber][position] = '\0';
                }

                fieldNumber++;
                position = 0;
            }
        }
        else
        {
            if (fieldNumber < 4 && position < MAX_FIELD - 1)
            {
                fields[fieldNumber][position] = line[i];
                position++;
            }
            else
            {
                tooLong = 1;
            }
        }
    }

    if (position > 0)
    {
        if (fieldNumber < 4)
        {
            fields[fieldNumber][position] = '\0';
        }

        fieldNumber++;
    }

    if (tooLong || fieldNumber != 3)
    {
        return 0;
    }

    myCopy(model, fields[0]);
    myCopy(flight, fields[1]);
    myCopy(heightText, fields[2]);

    return 1;
}

const char* chooseFileName(int num)
{
    if (num == 2) return TEST_02;
    if (num == 3) return TEST_03;
    if (num == 4) return TEST_04;
    if (num == 5) return TEST_05;
    if (num == 6) return TEST_06;
    if (num == 7) return TEST_07;
    if (num == 8) return TEST_08;
    if (num == 9) return TEST_09;
    if (num == 10) return TEST_10;
    if (num == 11) return TEST_11;
    if (num == 12) return TEST_12;
    if (num == 13) return TEST_13;
    if (num == 14) return TEST_14;
    if (num == 15) return TEST_15;
    if (num == 16) return TEST_16;

    return TEST_01;
}

int readData(const char fn[], Plane p[], int idx[], int &n)
{
    ifstream fin(fn);           // поток для чтения файла
    char *line = new char[MAX_LINE];
    char m[MAX_FIELD];          // марка текущего ЛА
    char r[MAX_FIELD];          // номер текущего рейса
    char hs[MAX_FIELD];         // высота текущего ЛА текстом
    int ln = 0;                 // номер строки файла
    int err = 0;                // количество ошибок

    n = 0;

    if (!fin)
    {
        cout << endl << "Критическая ошибка: файл не открыт." << endl;
        delete[] line;
        return 0;
    }

    cout << endl << "Проверка строк входного файла" << endl;
    cout << "------------------------------------------------------------" << endl;

    while (fin.getline(line, MAX_LINE))
    {
        int ok = 1;             // признак корректности строки
        double h = 0.0;         // высота числом
        int pc = 0;             // количество точек в высоте
        int dc = 0;             // количество цифр в высоте
        int ap = 0;             // признак части после точки
        double div = 10.0;      // делитель для дробной части
        int dig = 0;            // количество цифр после слова РЕЙС
        const char pref[] = "РЕЙС";
        int pl = myLength(pref);

        ln++;
        cout << "Строка " << ln << ": " << line << endl;
        cout << "Ошибки: ";

        if (!splitLine(line, m, r, hs))
        {
            ok = 0;
            err++;
            cout << "строка должна содержать ровно 3 поля; ";
        }
        else
        {
            int rf = 1;            // признак правильного номера рейса
            int hf = 1;            // признак правильной высоты

            // Проверка формата рейса: РЕЙС + 1..9 цифр.
            for (int i = 0; i < pl; i++)
            {
                if (r[i] != pref[i])
                {
                    rf = 0;
                }
            }

            for (int i = pl; r[i] != '\0' && rf; i++)
            {
                if (!isDigit(r[i]))
                {
                    rf = 0;
                }

                dig++;
            }

            if (dig < 1 || dig > MAX_DIGITS)
            {
                rf = 0;
            }

            if (!rf)
            {
                err++;
                cout << "номер рейса должен иметь формат РЕЙС + 1..9 цифр; ";
            }

            // Проверка высоты и перевод ее из текста в число.
            if (hs[0] == '\0' || hs[0] == '.' || hs[0] == '-')
            {
                hf = 0;
            }
            else
            {
                for (int i = 0; hs[i] != '\0' && hf; i++)
                {
                    if (hs[i] == '.')
                    {
                        pc++;
                        ap = 1;

                        if (pc > 1 || hs[i + 1] == '\0')
                        {
                            hf = 0;
                        }
                    }
                    else if (isDigit(hs[i]))
                    {
                        dc++;

                        if (!ap)
                        {
                            h = h * 10.0 + double(hs[i] - '0');
                        }
                        else
                        {
                            h = h + double(hs[i] - '0') / div;
                            div *= 10.0;
                        }
                    }
                    else
                    {
                        hf = 0;
                    }
                }
            }

            if (dc == 0 || h < 0.0 || h > 20.0)
            {
                hf = 0;
            }

            if (!hf)
            {
                err++;
                cout << "высота должна быть числом от 0.0 до 20.0; ";
            }

            ok = rf && hf;

            // Проверка смысловых дублей.
            if (ok)
            {
                for (int i = 0; i < n; i++)
                {
                    if (myEqual(p[i].flight, r) && myEqual(p[i].model, m))
                    {
                        ok = 0;
                        err++;
                        cout << "полный дубль записи; ";
                    }
                    else if (myEqual(p[i].flight, r))
                    {
                        ok = 0;
                        err++;
                        cout << "один рейс указан с разными марками ЛА; ";
                    }
                }
            }
        }

        if (ok)
        {
            if (n < MAX_PLANES)
            {
                myCopy(p[n].model, m);
                myCopy(p[n].flight, r);
                p[n].height = h;
                idx[n] = n;
                n++;
                cout << "нет";
            }
            else
            {
                err++;
                cout << "массив корректных записей переполнен; ";
            }
        }

        cout << endl;
        cout << "------------------------------------------------------------" << endl;
    }

    fin.close();
    delete[] line;

    if (ln == 0)
    {
        cout << endl << "Критическая ошибка: файл пустой." << endl;
        return 0;
    }

    cout << endl << "Итог проверки:" << endl;
    cout << "Всего строк: " << ln << endl;
    cout << "Корректных строк: " << n << endl;
    cout << "Найдено ошибок: " << err << endl;

    return n > 0;
}

void sortIndexes(const Plane p[], int idx[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            int a = idx[j];     // индекс первого самолета
            int b = idx[j + 1]; // индекс второго самолета
            int ea = p[a].height >= 20.0 ? 10 : int(p[a].height / 2.0) + 1;
            int eb = p[b].height >= 20.0 ? 10 : int(p[b].height / 2.0) + 1;

            if (ea > eb || (ea == eb && p[a].height > p[b].height))
            {
                int t = idx[j]; // временная переменная для обмена
                idx[j] = idx[j + 1];
                idx[j + 1] = t;
            }
        }
    }
}

void printTable(const Plane p[], const int idx[], int n, const char title[])
{
    cout << endl << title << endl;
    cout << "+-----+----------------+----------------+---------+--------+" << endl;
    cout << "| N   | Марка ЛА       | Номер рейса    | Высота  | Эшелон |" << endl;
    cout << "+-----+----------------+----------------+---------+--------+" << endl;

    for (int i = 0; i < n; i++)
    {
        int k = idx[i];
        int e = p[k].height >= 20.0 ? 10 : int(p[k].height / 2.0) + 1;
        int sp;                 // количество пробелов для выравнивания

        cout << "| " << setw(3) << right << i + 1 << " | ";

        cout << left << p[k].model;
        sp = 14 - visualLength(p[k].model);
        for (int j = 0; j < sp; j++) cout << ' ';
        cout << " | ";

        cout << left << p[k].flight;
        sp = 14 - visualLength(p[k].flight);
        for (int j = 0; j < sp; j++) cout << ' ';
        cout << " | ";

        cout << right << setw(7) << fixed << setprecision(1) << p[k].height << " | ";
        cout << setw(6) << e << " |" << endl;
    }

    cout << "+-----+----------------+----------------+---------+--------+" << endl;
}
