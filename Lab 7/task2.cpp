#include <iostream>
#include <string>
using namespace std;
void merge(string names[], double arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    double L[n1], R[n2];
    string L1[n1], R1[n2];
    int j = 0;
    for (int i = l; i < n1 + l; i++)
    {
        L[j] = arr[i];
        L1[j] = names[i];
        j++;
    }
    j = 0;
    for (int i = m + 1; i < n2 + m + 1; i++)
    {
        R[j] = arr[i];
        R1[j] = names[i];
        j++;
    }
    int i = 0, k = l;
    j = 0;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            names[k] = L1[i];
            i++;
            k++;
        }
        else
        {
            arr[k] = R[j];
            names[k] = R1[j];
            j++;
            k++;
        }
    }
    if (i < n1)
    {
        while (i < n1)
        {
            arr[k] = L[i];
            names[k] = L1[i];
            i++;
            k++;
        }
    }
    if (j < n2)
    {
        while (j < n2)
        {
            arr[k] = R[j];
            names[k] = R1[j];
            j++;
            k++;
        }
    }
}
void mergeSort(string names[], double arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(names, arr, l, m);
        mergeSort(names, arr, m + 1, r);

        merge(names, arr, l, m, r);
    }
}

int main()
{
    double timeInSeconds[10];
    string nameOfRunners[10];
    for (int i = 0; i < 10; i++)
    {
        cout << "Enter the time in seconds for runner " << i + 1 << endl;
        cin >> timeInSeconds[i];
        cout << "Enter the name of runner " << i + 1 << endl;
        cin >> nameOfRunners[i];
    }
    mergeSort(nameOfRunners, timeInSeconds, 0, 9);
    cout << "Top 5 fastest runners:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << i + 1 << "- " << nameOfRunners[i] << "\t-\t" << timeInSeconds[i] << "\tseconds" << endl;
    }
    return 0;
}