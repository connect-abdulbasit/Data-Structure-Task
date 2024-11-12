#include <iostream>
using namespace std;
int main()
{
    const int row1 = 2, col1 = 3;
    const int col2 = 2, row2 = 3;
    int matrix1[row1][col1] = {{1, 2, 3}, {4, 5, 6}};
    int matrix2[row2][col2] = {{10, 11}, {20, 21}, {30, 31}};
    if (col1 == row2)
    {
        int result[row1][col2];
        int sum;
        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < col2; j++)
            {
                sum = 0;
                for (int k = 0; k < col1; k++)
                {
                    sum += matrix1[i][k] * matrix2[k][j];
                }
                result[i][j] = sum;
            }
        }
        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < col2; j++)
            {
                cout << result[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Not Possible" << endl;
    }
    return 0;
}
