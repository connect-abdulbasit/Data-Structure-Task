#include <iostream>
using namespace std;
#define n 10
void bubbleSort(int unSortedArray[n])
{
    bool flag = true;
    for (int i = 0; flag; i++)
    {
        flag = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (unSortedArray[j] > unSortedArray[j + 1])
            {
                flag = true;
                swap(unSortedArray[j], unSortedArray[j + 1]);
            }
        }
    }
}
void selectionSort(int unSortedArray[n])
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (unSortedArray[minIndex] > unSortedArray[j])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(unSortedArray[i], unSortedArray[minIndex]);
        }
    }
}
void insertionSort(int unSortArray[n])
{
    for (int i = 0; i < n; i++)
    {
        int j = i - 1;
        int key = unSortArray[i];

        while (j >= 0 && key < unSortArray[j])
        {
            unSortArray[j + 1] = unSortArray[j];
            j--;
        }
        unSortArray[j + 1] = key;
    }
}
void shellSort(int unSortArray[n])
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = unSortArray[i];
            int j;
            for (j = i; j >= gap && unSortArray[j - gap] > unSortArray[j]; j -= gap)
            {
                unSortArray[j] = unSortArray[j - gap];
            }
            unSortArray[j] = temp;
        }
    }
}
void combSort(int unSortedArray[n])
{
    int gap = n;
    bool swapped = true;

    while (gap != 1 || swapped == true)
    {
        swapped = false;
        gap = (gap * 10) / 13;
        if (gap < 1)
        {
            gap = 1;
        }
        for (int i = 0; i + gap < n; i++)
        {
            if (unSortedArray[i] > unSortedArray[i + gap])
            {
                int temp = unSortedArray[i];
                unSortedArray[i] = unSortedArray[i + gap];
                unSortedArray[i + gap] = temp;
                swapped = true;
            }
        }
    }
}
int linearSearch(int array[], int number)
{
    for (int i = 0; i < n; i++)
    {
        if (array[i] == number)
        {

            return i;
        }
    }
    return -1;
}
int binarySearch(int array[], int number, int low, int high)
{
    int mid;
    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (array[mid] == number)
        {
            return mid;
        }
        else if (array[mid] > number)
        {
            high = mid - 1;
        }
        else
        {

            low = mid + 1;
        }
    }
    return -1;
}
int interpolationSearch(int array[], int number, int low, int high)
{
    while (low <= high && number <= array[high] && number >= array[low])
    {
        int probe = low + (high - low) * (number - array[low]) / (array[high] - array[low]);
        if (array[probe] == number)
        {
            return probe;
        }
        else if (array[probe] > number)
        {
            high = probe - 1;
        }
        else
        {

            low = probe + 1;
        }
    }
    return -1;
}
int main()
{
    int unSortedArray[n] = {45, 36, -1, 99, 100, 0, 2, 5, 4, 8};
    cout << "Before bubble sorting" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << unSortedArray[i] << " ";
    }
    cout << endl;
    bubbleSort(unSortedArray);
    cout << "After bubble sort" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << unSortedArray[i] << " ";
    }
    cout << endl;
    cout << endl;
    unSortedArray[1] = 10;
    unSortedArray[2] = -90;
    unSortedArray[3] = 0;
    cout << "Before selection sorting" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << unSortedArray[i] << " ";
    }
    cout << endl;
    selectionSort(unSortedArray);
    cout << "After selection sort" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << unSortedArray[i] << " ";
    }
    cout << endl;
    cout << endl;

    unSortedArray[1] = 10;
    unSortedArray[2] = 190;
    unSortedArray[3] = 0;
    cout << "Before shell sorting" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << unSortedArray[i] << " ";
    }
    cout << endl;
    shellSort(unSortedArray);
    cout << "After shell sort" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << unSortedArray[i] << " ";
    }
    cout << endl;
    cout << endl;

    unSortedArray[1] = 10;
    unSortedArray[2] = 89;
    unSortedArray[3] = 0;
    cout << "Before insertion sorting" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << unSortedArray[i] << " ";
    }
    cout << endl;
    insertionSort(unSortedArray);
    cout << "After insertion sort" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << unSortedArray[i] << " ";
    }
    cout << endl;
    cout << endl;

    unSortedArray[1] = 10;
    unSortedArray[2] = 9;
    unSortedArray[3] = 0;
    cout << "Before comb sorting" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << unSortedArray[i] << " ";
    }
    cout << endl;
    combSort(unSortedArray);
    cout << "After comb sort" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << unSortedArray[i] << " ";
    }
    cout << endl;
    cout << endl;

    cout << "linear Search of 9 is index " << linearSearch(unSortedArray, 9) << endl;
    cout << "binary Search of 99 is index " << binarySearch(unSortedArray, 99, 0, n - 1) << endl;
    cout << "interpolation Search of 0 is index " << interpolationSearch(unSortedArray, 0, 0, n - 1) << endl;
    return 0;
}