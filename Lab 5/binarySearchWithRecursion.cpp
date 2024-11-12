#include <iostream>
using namespace std;

int binarySearchWithRecursion(int num, int arr[], int low, int high)
{
    if (low > high)
    {
        return -1;
    }
    int mid = low + (high - low) / 2;
    if (num == arr[mid])
    {
        return mid;
    }
    else if (num > arr[mid])
    {
        return binarySearchWithRecursion(num, arr, mid + 1, high);
    }
    else
    {
        return binarySearchWithRecursion(num, arr, low, mid - 1);
    }
}

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int index = binarySearchWithRecursion(4, arr, 0, 9);
    if (index != -1)
    {
        cout << "4 is found at " << index << " index" << endl;
    }
    else
    {
        cout << "Not Found" << endl;
    }

    return 0;
}