#include <iostream>
using namespace std;
#define size 7
int sort(int unSortArray[], int current, int min)
{
    static int n = 0;
    if (size == current)
    {
        return min;
    }
    if (unSortArray[current] < unSortArray[min])
    {
        min = current;
    }
    int minimum = sort(unSortArray, current + 1, min);
    if (minimum != n && current == n)
    {
        int temp = unSortArray[minimum];
        unSortArray[minimum] = unSortArray[n];
        unSortArray[n] = temp;
    }
    if (current == n && n != size)
    {
        n++;
        sort(unSortArray, current + 1, min + 1);
    }
    return minimum;
}

int main()
{
    int unSortArray[7] = {5, 4, 3, 2, 1, 89, 45};
    for (int i = 0; i < 7; i++)
    {
        cout << unSortArray[i] << ",";
    }
    cout << endl;
    sort(unSortArray, 0, 0);
    for (int i = 0; i < 7; i++)
    {
        cout << unSortArray[i] << ",";
    }
    cout << endl;

    return 0;
}