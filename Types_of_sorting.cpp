#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <chrono>
#include <string>


// creates a vector of random numbers with length n and less than range
int* make_array(int n, int range)
{
    int* list = new int[n];
    for (int i = 0; i < n; i++)
        list[i] = (rand() * rand()) % range;
    return(list);
}

void swap(int* arr, int i, int I) {
    int temp = arr[i];
    arr[i] = arr[I];
    arr[I] = temp;
}

void HeapSort1(int* arr, int size, int i) {
    int big = i;
    for (int j = i * 2 + 1; j < i * 2 + 3 && j < size; j++) {
        if (arr[big] < arr[j]) {
            big = j;
        }
    }
    if (i != big) {
        swap(arr, i, big);
        HeapSort1(arr, size, big);
    }
}

void HeapSort2(int* arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        HeapSort1(arr, size, i);
    }

    for (int i = size - 1; i >= 0; i--) {
        swap(arr, 0, i);
        HeapSort1(arr, i, 0);
    }
}

void ShellSort(int* mass, int n)
{

    int i, j, step;
    int tmp;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++)
        {
            tmp = mass[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < mass[j - step])
                    mass[j] = mass[j - step];
                else
                    break;
            }
            mass[j] = tmp;
        }
}

int C[10000000];

void Merge(int*, int, int, int);

void MergeSort(int* A, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        MergeSort(A, low, mid);
        MergeSort(A, mid + 1, high);

        Merge(A, low, high, mid);
    }
}


void Merge(int* A, int low, int high, int mid)
{
    int u1, u2, k;
    u1 = low;
    u2 = mid + 1;
    k = low;
    while (u1 <= mid && u2 <= high)
    {
        if (A[u1] < A[u2])
        {
            C[k] = A[u1];
            k++;
            u1++;
        }
        else
        {
            C[k] = A[u2];
            u2++;
            k++;
        }
    }
    while (u1 <= mid)
    {
        C[k] = A[u1];
        k++;
        u1++;
    }
    while (u2 <= high)
    {
        C[k] = A[u2];
        k++;
        u2++;
    }
    for (int i = low; i <= high; i++)
    {
        A[i] = C[i];
    }

}

void InsertionSort(int* mass, int n)
{

    for (int i = 1; i < n; i++)
    {
        if (mass[i - 1] > mass[i])
        {
            int key = mass[i];
            int j = i - 1;
            mass[j + 1] = mass[j];
            for (j--; j >= 0; j--)
            {
                if (mass[j] > key)
                {
                    mass[j + 1] = mass[j];
                }
                else
                    break;
            }
            mass[++j] = key;
        }
    }

}

void QuickSort(int* arr, int b, int e)
{
    int l = b, r = e;
    int piv = arr[(l + r) / 2];
    while (l <= r)
    {
        while (arr[l] < piv)
            l++;
        while (arr[r] > piv)
            r--;
        if (l <= r)
            std::swap(arr[l++], arr[r--]);
    }
    if (b < r)
        QuickSort(arr, b, r);
    if (e > l)
        QuickSort(arr, l, e);
}

int main()
{
    srand(time(NULL));

    int size2 = 100000; // For IsertionSort
    int size = 10000000; // enter the size of the array

    int n;
    std::cout << "Enter the number of cycles: ";
    std::cin >> n;

    std::ofstream out("sorting time.txt", std::ios::app);
    for (int p = 0; p < 5; p++) {

        std::cout << "Set for this session: " << p+1 << " / " << n << std::endl;

        int* base_mass = make_array(size, 100000000);
        int* base_inmass = make_array(size2, 10000000);

        int* mass = new int[size];
        for (int i = 0; i < size; i++)
            mass[i] = base_mass[i];

        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        std::cout << "Heap sort" << std::endl;
        HeapSort2(mass, size);
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
        std::chrono::duration<double> sec = end - start;
        out << "HeapSort: " << double(sec.count()) << std::endl;

        for (int i = 0; i < size; i++)
            mass[i] = base_mass[i];

        start = std::chrono::system_clock::now();
        std::cout << "Shell Sort" << std::endl;
        ShellSort(mass, size);
        end = std::chrono::system_clock::now();
        sec = end - start;
        out << "ShellSort: " << double(sec.count()) << std::endl;

        for (int i = 0; i < size; i++)
            mass[i] = base_mass[i];

        start = std::chrono::system_clock::now();
        std::cout << "Shell Sort" << std::endl;
        MergeSort(mass, 0, size-1);
        end = std::chrono::system_clock::now();
        sec = end - start;
        out << "MergeSort: " << double(sec.count()) << std::endl;

        for (int i = 0; i < size; i++)
            mass[i] = base_mass[i];

        start = std::chrono::system_clock::now();
        std::cout << "Quick Sort" << std::endl;
        QuickSort(mass, 0, size - 1);
        end = std::chrono::system_clock::now();
        sec = end - start;
        out << "QuickSort: " << double(sec.count()) << std::endl;

        int* inmass = base_inmass;

        start = std::chrono::system_clock::now();
        std::cout << "Insertion sort" << std::endl;
        InsertionSort(inmass, size2);
        end = std::chrono::system_clock::now();
        sec = end - start;
        out << "InsertionSort: " << double(sec.count()) << std::endl;


    }
    double time; std::string line;
    out.close();
    //Подсчет рез-та в файл "Final Res.txt"
    std::ofstream write("result.txt");
    std::ifstream file("sorting time.txt");
    if (file.is_open()) {
        double HeapS = 0, Shell = 0, Insert = 0, MergeS = 0, Quick = 0; // Суммарные времена
        int HeapSc = 0, Shellc = 0, Insertc = 0, MergeC = 0, QuickC = 0; //Кол - во включений ф-й

        while (getline(file, line, ':'))
        {
            if (line == "HeapSort") {
                getline(file, line);
                time = std::stod(line);
                HeapS += time;
                HeapSc += 1;
            }
            else if (line == "ShellSort") {
                getline(file, line);
                time = std::stod(line);
                Shell += time;
                Shellc += 1;
            }
            else if (line == "InsertionSort") {
                getline(file, line);
                time = std::stod(line);
                Insert += time;
                Insertc += 1;
            }
            else if (line == "QuickSort") {
                getline(file, line);
                time = std::stod(line);
                Quick += time;
                QuickC += 1;
            }
            else if (line == "MergeSort") {
                getline(file, line);
                time = std::stod(line);
                MergeS += time;
                MergeC += 1;
            }
        }

        write << "Average heap sort time: \t" << (int)HeapS / HeapSc << " sec \n"
            << "Average shell sort time: \t" << (int)(Shell / Shellc) << " sec \n"
            << "Average insert sort time: \t" << (int)(Insert / Insertc) << " sec \n"
            << "Average merge sort time: \t" << (int)(MergeS / MergeC) << " sec \n"
            << "Average quick sort time: \t" << (int)(Quick / QuickC) << " sec \n";
        write.close();
        file.close();
    }
    return 0;
}