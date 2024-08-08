#include <bits/stdc++.h>
using namespace std;

void bubbleSort_s(int arr[] , int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


void bubbleSort_p(int arr[],int n)
{    
    for (int i = 0; i < n - 1; ++i)
    {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main()
{
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    int arr_s[size];
    int arr_p[size];

    for (int i = 0; i < size; i++)
    {
        arr_s[i] = rand() % size;
        arr_p[i] = arr_s[i];
    }

    auto start = chrono::high_resolution_clock::now();
    bubbleSort_s(arr_s,size);
    auto stop = chrono::high_resolution_clock::now();
    auto result = stop - start;
    auto duration = chrono::duration_cast<chrono::milliseconds>(result);

    cout << "\nSequential Bubble sort: " << duration.count() << " ms\n";

    auto start2 = chrono::high_resolution_clock::now();
    #pragma omp parallel num_threads(4)
    {
        
        bubbleSort_p(arr_s,size);
    
    }
    auto stop2 = chrono::high_resolution_clock::now();
    auto result2 = stop2 - start2;
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(result2);

    cout << "\nParallel Bubble sort: " << duration2.count() << " ms\n";

    // cout << "Sorted array: ";
    // for (int num : arr_s)
    // {
    //     cout << num << " ";
    // }

    return 0;
}
