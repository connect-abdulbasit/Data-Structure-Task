#include <iostream>
using namespace std;
int main()
{
    int numberOfRows;
    cout << "Enter number of rows:";
    cin >> numberOfRows;
    int *numberOfSeatsPerRow = new int[numberOfRows];
    for (int i = 0; i < numberOfRows; i++)
    {
        cout << "Enter the number of seats in " << i + 1 << " row" << endl;
        cin >> numberOfSeatsPerRow[i];
    }

    string **seatsInHall = new string *[numberOfRows];
    for (int i = 0; i < numberOfRows; i++)
    {
        seatsInHall[i] = new string[numberOfSeatsPerRow[i]];
    }
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfSeatsPerRow[i]; j++)
        {
            cout << "Enter the name of the person in " << i + 1 << " row and " << j + 1 << " seat" << endl;
            cin >> seatsInHall[i][j];
        }
    }
    cout << "Displaying the seating arrangement" << endl;
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfSeatsPerRow[i]; j++)
        {
            cout << seatsInHall[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < numberOfRows; i++)
    {
        delete[] seatsInHall[i];
    }
    delete seatsInHall;
    delete[] numberOfSeatsPerRow;
    return 0;
}