#include <iostream>
using namespace std;

int factorialNonTail(int num)
{
    if (num == 0 || num == 1)
    {
        return 1;
    }
    return num * factorialNonTail(num - 1);
}
int factorialTail(int num, int result = 1)
{
    if (num == 0)
    {
        return result;
    }
    return factorialTail(num - 1, num * result);
}
int main()
{
    cout << "Factorial with non tail recursion " << factorialNonTail(3) << endl;
    cout << "Factorial with tail recursion " << factorialTail(2);
    return 0;
}