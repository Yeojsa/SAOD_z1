//��������� �.�.
#pragma once
#include <string> 
#include <iostream> 
#include <ctime> 
#include <cstdlib> 
#include <chrono> 
#include <fstream> 


using namespace std;

/// ��������� ������� ��� ��������� ������� ���������� �������
/// check - ��������� �� �������
template <typename check>
void checktime(check func) {
    auto start = chrono::high_resolution_clock::now();// ��������� �������� ������� ������ ���������� �������

    func(); // ����� ���������� �������

    auto end = chrono::high_resolution_clock::now(); // ��������� �������� ������� ����� ���������� �������

    chrono::duration<double> duration = end - start; // ���������� ������������ ���������� �������
    cout << duration.count() << " seconds" << endl; // ����� �������
}

/// ��������� ������� ��� ������ ��������� � ������ �������
/// arr - ��������� �� ������ �������, size - ������ �������, n - �������, ������� ���������� �����
template<typename D>
D search_start(const D* arr, size_t size, D n) {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == n) {
            return i; // ���� ������� ������
        }
    }
    return -1; // ���� ������� �� ������
}

/// ��������� ������� ��� ������ ��������� � ����� �������
/// arr - ��������� �� ������ �������, size - ������ �������, n - �������, ������� ���������� �����
template<typename D>
D search_tail(const D* arr, size_t size, D n) {
    for (long long i = size - 1; i >= 0; --i) {
        if (arr[i] == n) {
            return i; // ���� ������� ������
        }
    }
    return -1; // ���� ������� �� ������
}


/// ���������� ������� ���������� ����������
/// size - ������ �������, mind - ����������� �������� ����������, maxd - ������������ �������� ����������
template<typename D>
D* array_fill(size_t  size, D mind, D maxd) {
    D* arr = new D[size]; // ��������� ������ ��� �������
    // ���������� �������
    for (size_t i = 0; i < size; i++) {
        arr[i] = rand() % (maxd - mind + 1) + mind;
    }
    return arr; // ����������� ���������
}

/// ���������� ���������� �����
/// arr - ��������� �� ������ �������, size - ������ �������, filename - ��� ����� ��� ������
template<typename D>
void writefile(const D* arr, size_t size, const string& filename) {
    ofstream outputFile(filename); // �������� �����
    if (!outputFile.is_open()) {
        cerr << "������!" << endl; // ��������� �� ������
        return;
    }
    for (size_t i = 0; i < size; i++) {
        outputFile << arr[i] << " ";
    }
    outputFile.close(); // �������� �����
}

/// �������� ������������ �� ������ �� �����������
/// arr - ��������� �� ������ �������, size - ������ �������
template<typename D>
bool checksort(const D* arr, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}
/// �������� ������������ �� ������ �� ��������
/// arr - ��������� �� ������ �������, size - ������ �������
template<typename D>
bool checkreversort(const D* arr, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        if (arr[i] < arr[i + 1]) {
            return false;
        }
    }
    return true;
}

/// ���������� ��������� �����
/// arr - ��������� �� ������ �������, size - ������ �������, filename - ��� ����� ��� ������
template<typename D>
void writebinfile(const D* arr, size_t size, const string& filename) {
    ofstream outputFile(filename, ios::binary); // �������� �����
    if (!outputFile.is_open()) {
        cerr << "������!" << endl; // ����� ��������� �� ������
        return;
    }
    outputFile.write(reinterpret_cast<const char*>(arr), size * sizeof(D));
    outputFile.close(); // �������� �����
}

/// ��������� ������� ��� ������ ��������� c ������� ��������� ������
/// arr - ��������� �� ������ �������, l - ����� �������� �������, r - ������ �������� ������� , n - �������, ������� ���������� �����
template<typename D>
D binsearch(const D* arr, D l, D r, D n) {
    while (l <= r) {
        D m = l + (r - l) / 2; //���������� ��������
       
        if (arr[m] == n)  // ���� ������� ��������� � �������� �������
            return m;

        if (arr[m] > n) // ���� ������� ������ �������� � �������� �������, ������ ������� ��������� � ����� �������� �������
            r = m - 1;

        else  // ���� ������� ������ �������� � �������� �������, ������ ������� ��������� � ������ �������� �������
            l = m + 1;
    }

    return -1;
}

/// ��������� ������� ��� ������ ��������� c ������� ����������������� ������
/// arr - ��������� �� ������ �������, min - ����������� �������� ��������� ������, max - ������������ �������� ��������� ������ , n - �������, ������� ���������� �����
template<typename D>
D interpolsearch(const D* arr, D min, D max, D n) {

    while (min <= max && n >= arr[min] && n <= arr[max]) {
       
        D pos = min + ((n - arr[min]) * (max - min)) / (arr[max] - arr[min]);  // ������� ������������ 

        if (arr[pos] == n) // ���� ������� � ������� ��������������
            return pos;

        if (arr[pos] > n)  // � ����� �����
            max = pos - 1;

        else // � ������ �����
            min = pos + 1;
    }

    return -1;
}