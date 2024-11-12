#include <iostream>
using namespace std;

void haveCommonFriends(int firstPerson, int secondPerson, bool Friend2DArray[5][5])
{
    int found = 0;
    for (int i = 0; i < 5; i++)
    {
        if (Friend2DArray[firstPerson][i] == true && Friend2DArray[secondPerson][i])
        {
            cout << firstPerson << " and " << secondPerson << " both have " << i << " as a common friend" << endl;
            found++;
        }
    }
    if (found == 0)
    {
        cout << "No Common friends" << endl;
    }
    else
    {
        cout << "Total number of friends " << found << endl;
    }
}
int main()
{
    bool Friend2DArray[5][5] = {{false, true, false, true, true},
                                {true, false, true, false, true},
                                {false, true, false, false, false},
                                {true, false, false, false, true},
                                {true, true, false, true, false}};

    cout << "Displaying the chart" << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << Friend2DArray[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "0 and 4 Person\n"
         << endl;
    haveCommonFriends(0, 4, Friend2DArray);
    cout << endl;

    cout << "1 and 2 Person\n"
         << endl;
    haveCommonFriends(1, 2, Friend2DArray);

    return 0;
}
