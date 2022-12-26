#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <chrono>
#include <string>


// creates a vector of random numbers with length n and less than range
int * make_array(int n, int range)
{
    int * list = new int[n];
    for (int i = 0; i < n; i++)
        list[i] = (rand() * rand()) % range;
    return(list);
}
void swap(int * arr, int i, int I) {
    int temp = arr[i];
    arr[i] = arr[I];
    arr[I] = temp;
}

void HeapSort1(int * arr, int size, int i) {
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
void HeapSort2(int * arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        HeapSort1(arr, size, i);
    }

    for (int i = size - 1; i >= 0; i--) {
        swap(arr, 0, i);
        HeapSort1(arr, i, 0);
    }
}

void ShellSort(int n, int * mass)
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
    //for (int i : mass)
    //    std::cout << i << ' ';
}

void InsertionSort(int n, int * mass)
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

int main()
{
    srand(time(NULL));

    int size2 = 100000; // For IsertionSort
    int size = 10000000; // enter the size of the array
    std::ofstream out("sorting_time.txt", std::ios::app);
    for (int p = 0; p < 10; p++) {
        std::cout << "cont " << p << std::endl;
        int * mass = make_array(size,  size);
        int * mass2 = make_array(size2, size2);
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        HeapSort2(mass2, size2);
        std::cout << "step 1" << std::endl;
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
        std::chrono::duration<double> sec = end - start;
        out << "HeapSort" << std::endl
            << int(sec.count()) << std::endl;

        start = std::chrono::system_clock::now();
        ShellSort(size, mass);
        std::cout << "step 2" << std::endl;
        end = std::chrono::system_clock::now();
        sec = end - start;
        out << "ShellSort" << std::endl
            << int(sec.count()) << std::endl;

        start = std::chrono::system_clock::now();
        InsertionSort(size2, mass2);
        std::cout << "step 3" << std::endl;
        end = std::chrono::system_clock::now();
        sec = end - start;
        out << "InsertionSort" << std::endl
            << int(sec.count()) << std::endl;
    }
    double time; std::string line;
    out.close();
    //Подсчет рез-та в файл "Final Res.txt"
    std::ofstream out2("Final Res.txt");
    std::ifstream file("sorting_time.txt");
    if (file.is_open() && out2.is_open()) {
        double HeapS = 0, Shell = 0, Insert = 0, Summtime = 0; // Суммарные времена
        int HeapSc = 0, Shellc = 0, Insertc = 0; //Кол - во включений ф-й
        for (int i = 1; i <= 3 * 10; i++) {
            getline(file,line);
            if (line == "HeapSort") {
                getline(file, line);
                time = std::stod(line);
                HeapS += time;
                HeapSc += 1;
                Summtime += time;
            }
            if (line == "ShellSort") {
                getline(file, line);
                time = std::stod(line);
                Shell += time;
                Shellc += 1;
                Summtime += time;
            }
            if (line == "InsertionSort") {
                getline(file, line);
                time = std::stod(line);
                Insert += time;
                Insertc += 1;
                Summtime += time;
            }
        }
        out2 << "RES_FOR_HEAP_SORT : " << (double)HeapS / HeapSc << "sec \n"
            << "RES_FOR_SHELL_SORT : " << (double)(Shell / Shellc) << "sec \n"
            << "RES_FOR_INSERT_SORT : " << (double)(Insert / Insertc) << "sec \n";
        out2.close();
        file.close();
    }
    return 0;
}