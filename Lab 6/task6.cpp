#include <iostream>
using namespace std;
bool isSafe(int arr[5][5], char forest[5][5], int x, int y, int n)
{
    if (forest[x][y] == 'T' && arr[x][y] == 0 && x < n && y < n && x >= 0 && y >= 0)
    {
        return true;
    }
    return false;
}
int maxForest(int arr[5][5], char forest[5][5], int x, int y, int n)
{
    int count = 0;
    if (isSafe(arr, forest, x, y, n))
    {
        count++;
        arr[x][y] = 1;
        count += maxForest(arr, forest, x + 1, y, n);
        count += maxForest(arr, forest, x, y + 1, n);
        count += maxForest(arr, forest, x, y - 1, n);
        count += maxForest(arr, forest, x - 1, y, n);
        return count;
    }
    return 0;
}
int maxForestCount(int arr[5][5], char forest[5][5], int x, int y, int n)
{
    int max = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (arr[i][j] == 0 && forest[i][j] == 'T')
            {
                int count = maxForest(arr, forest, i, j, n);
                if (count > max)
                {
                    max = count;
                }
            }
        }
    }
    return max;
}
int main()
{
    char forest[5][5] = {{'T', 'T', 'T', 'W', 'W'},
                         {'T', 'W', 'W', 'T', 'T'},
                         {'T', 'W', 'W', 'T', 'T'},
                         {'T', 'W', 'T', 'T', 'T'},
                         {'W', 'W', 'T', 'T', 'T'}};
    int arr[5][5] = {0};
    cout << "Size of forest: " << maxForestCount(arr, forest, 0, 0, 5);

    return 0;
}