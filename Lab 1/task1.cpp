// 23k-0526

#include <iostream>
using namespace std;

class Bank
{
    double *balance;

public:
    Bank()
    {
        balance = new double;
        *balance = 0;
    }

    Bank(double initial_balance)
    {
        balance = new double;
        *balance = initial_balance;
    }

    Bank(const Bank &account)
    {
        balance = new double;
        *balance = *(account.balance);
    }

    ~Bank()
    {
        delete balance;
    }

    void display() const
    {
        cout << "Balance: " << *balance << endl;
    }

    void incrementAndDecrementInBalance(double amount)
    {
        *balance += amount;
    }
};

int main()
{
    Bank account1;
    Bank account2(1000);
    Bank account3 = account2; // Calls the copy constructor
    account3.incrementAndDecrementInBalance(-200);

    cout << "Account 1:" << endl;
    account1.display();
    cout << "Account 2:" << endl;
    account2.display();
    cout << "Account 3:" << endl;
    account3.display();

    return 0;
}
