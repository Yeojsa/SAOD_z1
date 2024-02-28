// Выполнил Богодухов А.А.

#include <iostream> 
#include <ctime> 
#include <string> 
#include "Modul.h"
#include <algorithm>
#include <cassert>
#include <iomanip>

using namespace std;

/// проверка данных
void testcheck() {
    int testarr[] = { 1, 2, 3, 4, 5 };
    int testarrays[] = { -4, 8, 2, 1, 34 };

    assert(checksort(testarr, 5) == true); // проверка отсортирован ли массив
    assert(checksort(testarrays, 5) == false); // проверка отсортирован ли массив
    
    assert(checkreversort(testarr, 5) == false); // проверка отсортирован ли массив по убыванию 
    
    assert(search_start(testarr, 5, 4) != -1); // проверка есть ли элемент в массиве
    assert(search_start(testarr, 5, 8) == -1); // проверка есть ли элемент в массиве
    assert(search_start(testarr, 5, 4) == 3); // проверка есть ли элемент в массиве
    assert(search_start(testarr, 5, 5) != 3); // проверка есть ли элемент в массиве

    assert(search_tail(testarr, 5, 4) != -1); // проверка есть ли элемент в массиве
    assert(search_tail(testarr, 5, 8) == -1); // проверка есть ли элемент в массиве
    assert(search_tail(testarr, 5, 4) == 3); // проверка есть ли элемент в массиве
    assert(search_tail(testarr, 5, 5) != 3); // проверка есть ли элемент в массиве
   
    assert(binsearch(testarr, 0, 5 - 1, 8) == -1); // проверка есть ли элемент в массиве
    assert(binsearch(testarr, 0, 5 - 1, 4) != -1); // проверка есть ли элемент в массиве
    assert(binsearch(testarr, 0, 5 - 1, 4) == 3); // проверка есть ли элемент в массиве
    assert(binsearch(testarr, 0, 5 - 1, 5) != 3); // проверка есть ли элемент в массиве

    assert(interpolsearch(testarr, 0, 5 - 1, 4) != -1); // проверка есть ли элемент в массиве
    assert(interpolsearch(testarr, 0, 5 - 1, 8) == -1); // проверка есть ли элемент в массиве
    assert(interpolsearch(testarr, 0, 5 - 1, 4) == 3); // проверка есть ли элемент в массиве
    assert(interpolsearch(testarr, 0, 5 - 1, 5) != 3); // проверка есть ли элемент в массиве
    
    sort(testarrays, testarrays + 5); // сортировка массива
    assert(checksort(testarrays, 5) == true); // проверка отсортирован ли массив
    
    writefile(testarr, 5, "test.txt"); // запись в файл

    ifstream inputFile("test.txt"); // открытие файла
    int n;
    // проверка соответствуют ли данные в файле с массивом
    for (int i = 0; i < 5; ++i) {
        inputFile >> n;
        assert(n == testarr[i]);
    }
    inputFile.close(); // закрытие файла 


}

/// функция вывода позиции элемента при поиске 
void print_result(long long result) {
    if (result != -1) {
        cout << "The element was found in the position " << result << endl;
    }
    else {
        cout << "The element was not found" << endl;
    }
}


int main(int argc, char* argv[])
{

    cout << fixed << setprecision(7);
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    testcheck(); /// проверка данных

    size_t size = 1'000'000; // размер массива
    string  filename = "test.txt"; // имя текстового файла
    string  filenamebin = "test.bin"; // имя бинарного файла

    // проверка наличия аргумента командной строки
    if (argc != 4) {
        cerr << "Using: " << argv[0] << "min, max, src " << endl;
        return 1;
    }

    int min = atoi(argv[1]); // минимальное значение диапазона
    int max = atoi(argv[2]); // максимальное значение диапазона
    int src = atoi(argv[3]);  // элемент в массиве

    //cout << "Введите минимальное значение диапозона: ";
    //cin >> min;
    //cout << "Введите максимальное значение диапозона: ";
    //cin >> max;
    //cout << "Введите число для поиска:  ";
    //cin >> src;
    

    /* лямбда функция для просмотра времени функции заполнения массива, где
       [&] - захват всех переменных из текущей области видимости по ссылке 
       () - список параметров функции
       {} - тело лямбда функции */
    cout << "Time to fill the array: ";
    checktime([&]() { return array_fill<long long>(size, min, max); });
    long long* array = array_fill<long long>(size, min, max);
 
    cout << "Time to check whether the array is sorted in ascending order: ";
    // лямбда функция для просмотра времени функции отсортирован ли массив по возрастанию
    checktime([&]() { return checksort(array, size); });

    cout << "Time to check whether the array is sorted in descending order: ";
    // лямбда функция для просмотра времени функции отсортирован ли массив по убыванию
    checktime([&]() { return checkreversort(array, size); });

    cout << "Time to fill in a text file: ";
    // лямбда функция для просмотра времени функции записи массива в текстовый файл
    checktime([&]() { return writefile(array, size, filename); });

    cout << "The time of filling the binary file: ";
    // лямбда функция для просмотра времени функции записи массива в бинарный файл
    checktime([&]() { return writebinfile(array, size, filenamebin); });
    
    cout << "Time to search for an element from the beginning of the array:  ";
    // лямбда функция для просмотра времени функции поиска элемента в массиве с начала
    checktime([&]() { return search_start<long long>(array, size, src); });
    long long res_start = search_start<long long>(array, size, src);
    print_result(res_start);
    
    cout << "Time to search for an element from the end of the array:  ";
    // лямбда функция для просмотра времени функции поиска элемента в массиве с конца 
    checktime([&]() { return search_tail<long long>(array, size, src); });
    long long res_tail = search_tail<long long>(array, size, src);
    print_result(res_tail);

    cout << "Array sorting time: ";
    // лямбда функция для просмотра времени функции сортировки массива
    checktime([&]() { return sort(array, array + size); });
   
    cout << "The time to search for an element using the binary method: ";
    // лямбда функция для просмотра времени функции сортировки массива
    checktime([&]() { return binsearch<long long>(array, 0, size - 1, src); });
    long long res_bin = binsearch<long long>(array, 0, size - 1, src);
    print_result(res_bin);

    cout << "Time to search for an element using the interpolation method: ";
    // лямбда функция для просмотра времени функции сортировки массива
    checktime([&]() { return interpolsearch<long long>(array, 0, size - 1, src); });
    long long res_interpol = interpolsearch<long long>(array, 0, size - 1, src);
    print_result(res_interpol);

    delete[] array; // освобождение памяти 
    return 0;
}