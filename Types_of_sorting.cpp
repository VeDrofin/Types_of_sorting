#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <chrono>


// creates a vector of random numbers with length n and less than range
std::vector<int> make_array(int n, int range)
{
    std::vector<int> list(n);
    for (int i = 0; i < n; i++)
        list[i] = (rand() * rand()) % range;
    return(list);
}

void ShellSort(int n, std::vector<int> mass)
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

void InsertionSort(int n, std::vector<int> mass)
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
    int size = 10000000; // enter the size of the array
    std::vector<int> mass = make_array(size, 100000000);

    std::ofstream out("sorting_time.txt", std::ios::app);

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    ShellSort(size, mass);
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    std::chrono::duration<double> sec = end - start;
    out << "Shell Sort: "
        << int(sec.count()) << " sec \n";

    start = std::chrono::system_clock::now();
    InsertionSort(size, mass);
    end = std::chrono::system_clock::now();
    sec = end - start;
    out << "Insertion Sort: "
        << int(sec.count()) << " sec \n";

    out.close();
}
