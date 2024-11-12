#include <iostream>
using namespace std;
void display(int **ptr, int *columns, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns[i]; j++)
        {
            cout << ptr[i][j] << " ";
        }
        cout << endl;
    }
}
void updatedTheSize(int **ptr, int *column, int newColumnSize, int row)
{
    int *temp;
    for (int i = 0; i < row; i++)
    {

        temp = new int[column[i]];
        for (int j = 0; j < column[i]; j++)
        {
            temp[j] = ptr[i][j];
        }
        ptr[i] = new int[newColumnSize];
        for (int j = 0; j < newColumnSize; j++)
        {
            ptr[i][j] = 0;
        }

        for (int j = 0; j < column[i]; j++)
        {
            ptr[i][j] = temp[j];
        }

        column[i] = newColumnSize;
        delete[] temp;
    }
}
int main()
{
    const int row = 5;
    int column[row], newColumnSize = 10;
    int *temp;
    int **ptr = new int *[row];
    for (int i = 0; i < row; i++)
    {
        column[i] = i + 1;
        ptr[i] = new int[column[i]];
        for (int j = 0; j < column[i]; j++)
        {
            ptr[i][j] = i;
        }
    }
    cout << "Before updating the size \n"
         << endl;
    display(ptr, column, row);
    updatedTheSize(ptr, column, newColumnSize, row);
    cout << "After updating the size \n"
         << endl;
    display(ptr, column, row);
    for (int i = 0; i < row; i++)
    {
        delete[] ptr[i];
    }
    delete ptr;
    return 0;
}
