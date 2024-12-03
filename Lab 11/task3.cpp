#include <iostream>
using namespace std;

class Student{
    int id;
    string name;
    public:
    Student(int id, string name){
        this->id = id;
        this->name = name;
    }
    friend class HashTable;
};
class HashTable{
Student **table;
int size;
int numberOfStudents;
double loadFactor;
int hashFunction(int id){
    return id%size;
}
void checkLoad() {
        double load = ((double)numberOfStudents / size);
        if (load > loadFactor) { 
            int newSize = size * 2;
            while (!isPrime(newSize)) {
                newSize++;
            }

            Student **newTable = new Student*[newSize];
            for (int i = 0; i < newSize; i++) {
                newTable[i] = NULL;
            }

            int oldSize = size;
            size = newSize;

            for (int i = 0; i < oldSize; i++) {
                if (table[i] != NULL) {
                    int index = hashFunction(table[i]->id);
                    while (newTable[index] != NULL) {
                        index = (index + 1) % size;
                    }
                    newTable[index] = new Student(table[i]->id, table[i]->name);
                }
            }

            delete[] table;
            table = newTable;
        }
    }
bool isPrime(int n){
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}
public:
HashTable(int size,double loadFactor){
    this->size = size;
    numberOfStudents=0;
    this->loadFactor = loadFactor;
    table = new Student*[size];
    for(int i=0;i<size;i++){
        table[i] = NULL;
    }
}
void insert(int id,string name){
    int index = hashFunction(id);
    int startIndex = index;
    while(table[index]!=NULL){
        index = (index+1)%size;
    }
    table[index] = new Student(id,name);
    numberOfStudents++;
checkLoad();
}

void search(int id){
    int index = hashFunction(id);
    int current = index;
    do{
        if(table[index]!=NULL&&table[index]->id==id){
            cout<<"Student found"<<endl;
            cout<<"Name: "<<table[index]->name<<endl;
            cout<<"ID: "<<table[index]->id<<endl;
            return;
        }
        index = hashFunction(index+1);
    }while(index!=current);
    cout<<"Student not found"<<endl;
}

void display(){
    for(int i=0;i<size;i++){
        if(table[i]!=NULL){
            cout<<"Name: "<<table[i]->name<<endl;
            cout<<"ID: "<<table[i]->id<<endl;
        }else{
            cout<<"Empty"<<endl;
        }
        cout<<"----------------------------------------"<<endl;
    }
}
};

int main()
{
    
    HashTable table(7, 0.75);

    table.insert(12, "Student 12");
    table.insert(22, "Student 22");
    table.insert(32, "Student 32");
    table.insert(42, "Student 42");
    table.insert(52, "Student 52");
    table.insert(62, "Student 62");

cout<<"After insertion"<<endl;
    table.display();

cout<<"\n\nSearching Students\n";
    table.search(22);
    table.search(42);
    table.search(72);

    table.insert(72, "Student 72");
    table.insert(82, "Student 82");

    cout<<"\n\nAfter insertion"<<endl;

    table.display();

    return 0;
}
