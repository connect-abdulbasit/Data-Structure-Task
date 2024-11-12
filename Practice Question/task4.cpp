#include <iostream>
using namespace std;
#define size 5
int recursiveArraySum(int *arr[], int sizes[], int dim)
{
    if (sizes[dim] == 1 && dim == size - 1)
    {
        return arr[0][0];
    }
    if (sizes[dim] == 1)
    {
        sizes[dim]--;
        return arr[0][sizes[dim]] + recursiveArraySum(arr + 1, sizes, dim + 1);
    }
    sizes[dim]--;

    return arr[0][sizes[dim]] + recursiveArraySum(arr, sizes, dim);
}

int main()
{
    int **jaggedArray = new int *[size];
    int *sizes = new int[size];
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        cout << "Enter the size at " << i + 1 << endl;
        cin >> sizes[i];
        jaggedArray[i] = new int[sizes[i]];
        for (int j = 0; j < sizes[i]; j++)
        {
            jaggedArray[i][j] = count++;
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < sizes[i]; j++)
        {
            cout << jaggedArray[i][j] << " ";
        }
        cout << endl;
    }
    cout << "RESULT: " << recursiveArraySum(jaggedArray, sizes, 0);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < sizes[i]; j++)
        {
            delete jaggedArray[i];
        }
        delete[] jaggedArray;
    }

    return 0;
}