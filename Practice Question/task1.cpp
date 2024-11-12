#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int guessTheNumber(int number, string Player[], int curr)
{
    int num, next;
    next = curr + 1;
    cout << Player[curr] << " turn:" << endl;
    cout << "Enter the guess number" << endl;
    cin >> num;
    if (num == number)
    {
        cout << Player[curr] << " wins" << endl;
        return 1;
    }
    if (num > number)
    {
        cout << "You guess a larger number" << endl;
    }
    else
    {
        cout << "You guess a smaller number" << endl;
    }
    cout << "------------------------------------" << endl;
    guessTheNumber(number, Player, next % 5);
    return 1;
}

int main()
{
    srand(time(0));
    int num = rand() % 100 + 1;
    cout << "Game begin:\nNumber has generated between (1-100)\n\n";
    string arr[5] = {"Basit", "Hani", "Ali", "Taaha", "Qadir"};
    guessTheNumber(num, arr, 0);
    return 0;
}