#include <iostream>
using namespace std;

int getMax(int arr[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }

    return max;
}
void display(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void ascendingcountSort(int arr[], int it, int n)
{
    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++)
    {
        count[(arr[i] / it) % 10]++;
    }
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / it) % 10]-- - 1] = arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}
void descendingCountSort(int arr[], int it, int n)
{
    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++)
    {
        count[9 - (arr[i] / it) % 10]++;
    }
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        output[--count[9 - (arr[i] / it) % 10]] = arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}
void ascendingOrderWithRadix(int arr[], int n)
{
    int max;
    max = getMax(arr, n);
    for (int i = 1; ((max / i)) > 0; i = i * 10)
    {
        ascendingcountSort(arr, i, n);
    }
}
void descendingOrderWithRadix(int arr[], int n)
{
    int max;
    max = getMax(arr, n);
    for (int i = 1; ((max / i)) > 0; i = i * 10)
    {
        descendingCountSort(arr, i, n);
    }
}
int main()
{
    const int num = 10;
    int arr[num] = {50, 412, 32, 5, 9, 3, 2, 1, 98, 1000};
    ascendingOrderWithRadix(arr, num);
    cout << "Ascending Order:" << endl;
    for (int i = 0; i < num; i++)
    {
        cout << arr[i] << " ";
    }
    descendingOrderWithRadix(arr, num);

    cout << "\nDescending Order:" << endl;
    for (int i = 0; i < num; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}