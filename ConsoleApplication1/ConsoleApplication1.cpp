#include <iostream>
#include <time.h>
#include <chrono>
#include <random>
#include <string>
#include <windows.h>
#include <iomanip>
#include <vector>
using namespace std;

void tableHeader(string param)
{
    cout << setw(25) << left << "Алгоритм" << setw(35) << left << param << setw(15) << left << "Итерации" << setw(15) << left << "Сравнения" << setw(15) << left << "Обмены" << left << "Время,мкс" << endl;
}

void tableRow(string name, string param, int iter, int c, int m, int time)
{
    cout << setw(25) << left << name << setw(35) << left << param << setw(15) << left << iter  << setw(15) << left <<  c << setw(15) << left << m << left << time << endl;
}

void inclusionSort(int* b, int n, string param)
{
    int* a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
    int iter(0), c(0), m(0);
    auto begin = std::chrono::steady_clock::now();

    for (int i = 1; i < n; i++) {
        bool iterFlag = false;
        int j = i;
        int temp = a[i];
        c++;
        while (j > 0 && a[j-1] > temp) {
            iterFlag = true;
            iter++;
            c += 2;
            m++;
            a[j] = a[j - 1];
            j--;
        }
        c++;
        a[j] = temp;
        if (!iterFlag) iter++;
    }
    c++;
    
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    
    delete [] a;
    tableRow("Inclusion Sort", param, iter, c, m, elapsed_ms.count());
    
}

void selectionSort(int* b, int n, string param)
{
    int* a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
    int iter(0), c(0), m(0);

    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++)
    {
        int numMin = i;
        int min = a[numMin];
        c++;
        for (int j = i; j < n; j++)
        {
            c++;
            iter++;
            if (a[j] < min)
            {
            
                min = a[j];
                numMin = j;
            }
            c++;
        }
        c++;
        int temp = a[numMin];
        a[numMin] = a[i];
        a[i] = temp;
        m++;
    }
    c++;
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    
    delete [] a;

    tableRow("Selection Sort", param, iter, c, m, elapsed_ms.count());
}

void bubbleSort(int* b, int n, string param) 
{
    int* a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
    int iter(0), c(0), m(0);

    auto begin = std::chrono::steady_clock::now();
    for (int i = n - 1; i > 0; i--)
    {
        c++;
        for (int j = 0; j < i; j++) 
        {
            c++;
            iter++;
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                m++;
            }
            c++;
        }
        c++;
    }
    c++;
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    delete [] a;
    tableRow("Bubble Sort", param, iter, c, m, elapsed_ms.count());
}

void quickSort(int a[], int L, int R, int& iter, int& c, int& m) {

    if (L >= R)
    {
        c++;
        iter++;
        return;
    }
    c++;
    int left = L;
    int right = R;
    int x = a[(left + right) / 2];
    while (left <= right) {
        c++;
        while (a[left] < x)
        {
            iter++;
            c++;
            left++;
        }
        c++;
        while (a[right] > x)
        {
            iter++;
            c++;
            right--;
        }
        c++;
        if (left <= right) {
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;
            left++;
            right--;
            m++;
        }
        c++;
    }
    quickSort(a, L, left - 1, iter, c, m);
    quickSort(a, left, R, iter, c, m);
}


void quickSort(int b[], int n, string param) {  
    int* a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
    int iter(0), c(0), m(0);
    auto begin = std::chrono::steady_clock::now();
    quickSort(a, 0, n - 1, iter, c, m);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    delete[]a;
    tableRow("Quick Sort", param, iter, c, m, elapsed_ms.count());
}


void generateArray_N(int* &a, int n)
{
    a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
    }
}

void generateArray_S(int* &a, int n)
{
    a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
}

void generateArray_R(int* &a, int n)
{
    a = new int[n];
    for (int i = n - 1, j = 0; i >=0; i--, j++)
    {
        a[j] = i;
    }
}

void generateArray_P(int* &a, int n, int p)
{
    a = new int[n];
    for (int i = 0; i < n / 100 * p; i++)
    {
        a[i] = i;
    }
    for (int i = n / 100 * p; i < n; i++)
    {
        a[i] = n / 100 * p -1 + rand() % 1000;
    }
}

void generateArray_Ex1(int*& a, int n)
{
    a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000 *  (rand()%2 ? 1: - 1);
    }   
}


void bubbleSortEx1(int* a, int n)
{
    vector<int> buff;

    for (int i = 0; i < n; i++)
        if (a[i] < 0) buff.push_back(i);

    for (int i = buff.size()-1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[buff[j]] > a[buff[j + 1]])
            {
                int temp = a[buff[j]];
                a[buff[j]] = a[buff[j + 1]];
                a[buff[j + 1]] = temp;
            }
        }
    }

}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(NULL));
    int* a = nullptr;
    cout << "Задание 1" << endl << endl;
    tableHeader("Число элементов в массиве");
    
    generateArray_N(a, 20);
    inclusionSort(a, 20, "20");
    selectionSort(a, 20, "20");
    bubbleSort(a, 20, "20");
    quickSort(a, 20, "20");
    delete[] a;
    generateArray_N(a, 500);
    inclusionSort(a, 500, "500");
    selectionSort(a, 500, "500");
    bubbleSort(a, 500, "500");
    quickSort(a, 500, "500");
    delete[] a;
    generateArray_N(a, 1000);
    inclusionSort(a, 1000, "1000");
    selectionSort(a, 1000, "1000");
    bubbleSort(a, 1000, "1000");
    quickSort(a, 1000, "1000");
    delete[] a;
    generateArray_N(a, 3000);
    inclusionSort(a, 3000, "3000");
    selectionSort(a, 3000, "3000");
    bubbleSort(a, 3000, "3000");
    quickSort(a, 3000, "3000");
    delete[] a;
    generateArray_N(a, 5000);
    inclusionSort(a, 5000, "5000");
    selectionSort(a, 5000, "5000");
    bubbleSort(a, 5000, "5000");
    quickSort(a, 5000, "5000");
    delete[] a;
    generateArray_N(a, 10000);
    inclusionSort(a, 10000, "10000");
    selectionSort(a, 10000, "10000");
    bubbleSort(a, 10000, "10000");
    quickSort(a, 10000, "10000");
    delete[] a;

    cout << endl << "Задание 2" << endl << endl;
    tableHeader("Начальная упорядоченность, 1000");
    generateArray_S(a, 1000);
    inclusionSort(a, 1000, "Отсортированный");
    selectionSort(a, 1000, "Отсортированный");
    bubbleSort(a, 1000, "Отсортированный");
    quickSort(a, 1000, "Отсортированный");
    delete[] a;
    generateArray_R(a, 1000);
    inclusionSort(a, 1000, "Реверсивно отсортированный");
    selectionSort(a, 1000, "Реверсивно отсортированный");
    bubbleSort(a, 1000, "Реверсивно отсортированный");
    quickSort(a, 1000, "Реверсивно отсортированный");
    delete[] a;
    cout << endl;
    tableHeader("% отсортированных элементов, 1000");
    generateArray_P(a, 1000, 25);
    inclusionSort(a, 1000, "25");
    selectionSort(a, 1000, "25");
    bubbleSort(a, 1000, "25");
    quickSort(a, 1000, "25");
    delete[] a;
    generateArray_P(a, 1000, 50);
    inclusionSort(a, 1000, "50");
    selectionSort(a, 1000, "50");
    bubbleSort(a, 1000, "50");
    quickSort(a, 1000, "50");
    delete[] a;
    generateArray_P(a, 1000, 75);
    inclusionSort(a, 1000, "75");
    selectionSort(a, 1000, "75");
    bubbleSort(a, 1000, "75");
    quickSort(a, 1000, "75");
    delete[] a;

    cout << endl << "Задание 3" << endl << endl;
    generateArray_Ex1(a, 20);
    cout << "Сгенерированный массив:" << endl;
    for (int i = 0; i < 20; i++) cout << a[i] << " ";
    cout << endl << endl;
    bubbleSortEx1(a, 20);
    cout << "Отсортированный массив:" << endl;
    for (int i = 0; i < 20; i++) cout << a[i] << " ";
    cout << endl;
    delete[] a;
}
