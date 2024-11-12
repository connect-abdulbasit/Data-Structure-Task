// 23k-0526

#include <iostream>
using namespace std;

class Exam
{
    string *studentName;
    string *dateOfExam;
    double *marks;

public:
    Exam()
    {
        studentName = new string;
        dateOfExam = new string;
        marks = new double;
    }
    void setStudentName(string name)
    {
        *(this->studentName) = name;
    }

    void setDateOfExam(string date)
    {
        *(this->dateOfExam) = date;
    }

    void setMarks(double marks)
    {
        *(this->marks) = marks;
    }

    void display()
    {
        cout << "Name " << *studentName << endl;
        cout << "Date " << *dateOfExam << endl;
        cout << "Marks " << *marks << endl;
    }
    ~Exam()
    {
        delete studentName;
        delete dateOfExam;
        delete marks;
    }
};

int main()
{
    Exam e1;
    e1.setStudentName("basit");
    e1.setDateOfExam("20 aug 2024");
    e1.setMarks(98);
    Exam e2 = e1;
    Exam e3;
    e3 = e1;
    e2.setStudentName("ali mobin");
    cout << "-------------------------------------" << endl;
    e1.display();
    e2.display();
    cout << "-------------------------------------" << endl;
    e3.setStudentName("qadir");
    e1.display();
    e2.display();
    e3.display();
    cout << "-------------------------------------" << endl;
    return 0;
}