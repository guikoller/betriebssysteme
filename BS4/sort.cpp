#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <thread>
#include "sort_merge.h"

using namespace std;

#define SIZE 1000000

int main(int argc, char *argv[])
{
    vector<int> data(SIZE);
    vector<int> to_sort(SIZE);

    // Fill the array with random numbers using srand
    srand(time(0));
    for (int i = 0; i < SIZE; i++)
    {
        data[i] = rand() % 100;
        to_sort[i] = data[i];
    }

    if (argc == 1)
    {
        cout << "MIT THREDS" << endl;
        // create two thread to sort the left and right arrays
        thread t1(quickSort, &to_sort[0], 0, SIZE / 2 - 1);
        thread t2(quickSort, &to_sort[0], SIZE / 2, SIZE - 1);
        t1.join();
        t2.join();
        // merge the two sorted arrays
        merge(&to_sort[0], &data[0], SIZE);
    }
    else
    {
        cout << "OHNE THREDS" << endl;
        quickSort(&to_sort[0], 0, SIZE / 2 - 1);
        quickSort(&to_sort[0], SIZE / 2, SIZE - 1);
        merge(&to_sort[0], &data[0], SIZE);
    }

    if (is_sorted(data.begin(), data.end()))
        cout << "Array is sorted.\n";
    else
        cout << "Array is not sorted.\n";

    return 0;
}