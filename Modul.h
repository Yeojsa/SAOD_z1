//Богодухов А.А.
#pragma once
#include <string> 
#include <iostream> 
#include <ctime> 
#include <cstdlib> 
#include <chrono> 
#include <fstream> 


using namespace std;

/// шаблонная функция для просмотра времени выполнения функции
/// check - указатель на функцию
template <typename check>
void checktime(check func) {
    auto start = chrono::high_resolution_clock::now();// получение текущего времени начала выполнения функции

    func(); // вызов переданной функции

    auto end = chrono::high_resolution_clock::now(); // получение текущего времени конца выполнения функции

    chrono::duration<double> duration = end - start; // вычисление длительности выполнения функции
    cout << duration.count() << " seconds" << endl; // вывод времени
}

/// шаблонная функция для поиска элементов с начала массива
/// arr - указатель на начало массива, size - размер массива, n - элемент, который необходимо найти
template<typename D>
D search_start(const D* arr, size_t size, D n) {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == n) {
            return i; // если элемент найден
        }
    }
    return -1; // если элемент не найден
}

/// шаблонная функция для поиска элементов с конца массива
/// arr - указатель на начало массива, size - размер массива, n - элемент, который необходимо найти
template<typename D>
D search_tail(const D* arr, size_t size, D n) {
    for (long long i = size - 1; i >= 0; --i) {
        if (arr[i] == n) {
            return i; // если элемент найден
        }
    }
    return -1; // если элемент не найден
}


/// заполнение массива рандомными значениями
/// size - размер массива, mind - минимальный диапозон заполнения, maxd - максимальнвц диапозон заполнения
template<typename D>
D* array_fill(size_t  size, D mind, D maxd) {
    D* arr = new D[size]; // выделение памяти для массива
    // заполнение массива
    for (size_t i = 0; i < size; i++) {
        arr[i] = rand() % (maxd - mind + 1) + mind;
    }
    return arr; // возвращение указателя
}

/// заполнение текстового файла
/// arr - указатель на начало массива, size - размер массива, filename - имя файла для записи
template<typename D>
void writefile(const D* arr, size_t size, const string& filename) {
    ofstream outputFile(filename); // открытие файла
    if (!outputFile.is_open()) {
        cerr << "Ошибка!" << endl; // сообщение об ошибке
        return;
    }
    for (size_t i = 0; i < size; i++) {
        outputFile << arr[i] << " ";
    }
    outputFile.close(); // закрытие файла
}

/// проверка отсортирован ли массив по возрастанию
/// arr - указатель на начало массива, size - размер массива
template<typename D>
bool checksort(const D* arr, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}
/// проверка отсортирован ли массив по убыванию
/// arr - указатель на начало массива, size - размер массива
template<typename D>
bool checkreversort(const D* arr, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        if (arr[i] < arr[i + 1]) {
            return false;
        }
    }
    return true;
}

/// заполнение бинарного файла
/// arr - указатель на начало массива, size - размер массива, filename - имя файла для записи
template<typename D>
void writebinfile(const D* arr, size_t size, const string& filename) {
    ofstream outputFile(filename, ios::binary); // открытие файла
    if (!outputFile.is_open()) {
        cerr << "Ошибка!" << endl; // вывод сообщения об ошибке
        return;
    }
    outputFile.write(reinterpret_cast<const char*>(arr), size * sizeof(D));
    outputFile.close(); // закрытие файла
}

/// шаблонная функция для поиска элементов c помощью бинарного поиска
/// arr - указатель на начало массива, l - левая половина массива, r - правая половина массива , n - элемент, который необходимо найти
template<typename D>
D binsearch(const D* arr, D l, D r, D n) {
    while (l <= r) {
        D m = l + (r - l) / 2; //нахождение середины
       
        if (arr[m] == n)  // если элемент находится в середине массива
            return m;

        if (arr[m] > n) // если элемент меньше значения в середине массива, значит элемент находится в левой половине массива
            r = m - 1;

        else  // если элемент больше значения в середине массива, значит элемент находится в правой половине массива
            l = m + 1;
    }

    return -1;
}

/// шаблонная функция для поиска элементов c помощью интерполяционного поиска
/// arr - указатель на начало массива, min - минимальное значение диапозона поиска, max - максимальное значение диапозона поиска , n - элемент, который необходимо найти
template<typename D>
D interpolsearch(const D* arr, D min, D max, D n) {

    while (min <= max && n >= arr[min] && n <= arr[max]) {
       
        D pos = min + ((n - arr[min]) * (max - min)) / (arr[max] - arr[min]);  // формула интерполяции 

        if (arr[pos] == n) // если элемент в текущем местоположении
            return pos;

        if (arr[pos] > n)  // в левой части
            max = pos - 1;

        else // в правой части
            min = pos + 1;
    }

    return -1;
}