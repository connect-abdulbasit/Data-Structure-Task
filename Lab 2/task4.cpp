#include <iostream>
using namespace std;

int main()
{
    const int numberOfCourses = 4;
    const string course[numberOfCourses] = {"SE",
                                            "AI",
                                            "CS",
                                            "DS"};
    const int creditForCourses[numberOfCourses] = {3, 4, 2, 1};
    double **GPA = new double *[numberOfCourses];

    for (int i = 0; i < numberOfCourses; i++)
    {
        GPA[i] = new double[creditForCourses[i]];
    }
    for (int i = 0; i < numberOfCourses; i++)
    {
        cout << "For " << course[i] << endl;
        for (int j = 0; j < creditForCourses[i]; j++)
        {
            cout << j + 1 << " core course gpa" << endl;
            cin >> GPA[i][j];
        }
    }
    cout << "Displaying the GPA for different courses" << endl;
    for (int i = 0; i < numberOfCourses; i++)
    {
        cout << course[i] << "\t";
        for (int j = 0; j < creditForCourses[i]; j++)
        {
            cout << GPA[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < numberOfCourses; i++)
    {
        delete[] GPA[i];
    }
    delete GPA;

    return 0;
}