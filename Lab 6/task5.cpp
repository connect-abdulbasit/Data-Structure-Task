#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int **Arr, int x, int y, int n)
{

    if (x >= 0 && x < n && y >= 0 && y < n && Arr[x][y] == 1)
    {
        return true;
    }
    return false;
}
bool MAZE(int **Arr, int x, int y, int n, vector<char> &paths)
{
    if (x == n - 1 && y == n - 1)
    {
        for (int i = 0; i < paths.size(); i++)
        {
            cout << paths[i];
        }
        cout << endl;
        return true;
    }

    if (isSafe(Arr, x, y, n))
    {
        paths.push_back('D');
        MAZE(Arr, x + 1, y, n, paths);

        paths.pop_back();
        paths.push_back('R');
        MAZE(Arr, x, y + 1, n, paths);

        paths.pop_back();
    }
    return false;
}
int main()
{
    int **arr;
    arr = new int *[5];
    for (int i = 0; i < 5; i++)
    {
        arr[i] = new int[5];
        for (int j = 0; j < 5; j++)
        {
            if (i == 0 || j == 0 || i == 4 || j == 4)
            {
                arr[i][j] = 1;
            }
            else
            {

                arr[i][j] = 0;
            }
        }
    }
    cout << "Displaying maze\n"
         << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "OUTPUT:" << endl;
    vector<char> path;
    MAZE(arr, 0, 0, 5, path);
    for (int i = 0; i < 5; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}