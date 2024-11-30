#include <iostream>
using namespace std;

class Member{
    public:
    string name;
    int age;
    int id;
    Member(string name,int age,int id){
        this->name=name;
        this->age=age;
        this->id=id;
    }
};
class HashTable{
    public:
    Member** table;
    int size;
    int hashFunction(int id){
        return id%size;
    }
    HashTable(int size){
        this->size=size;
        table=new Member*[size];
        for(int i=0;i<size;i++){
            table[i]=NULL;
        }
    }

    void insert(int id, string name, int age) {
        int index = hashFunction(id);
        int startIndex = index;
        while (table[index] != NULL && table[index]->id != id) {
            index = (index + 1) % size;
            if (index == startIndex) {
                cout << "Table is full" << endl;
                return;
            }
        }
        table[index] = new Member(name, age, id);
    }
void deleteMember(int id){
    int index=hashFunction(id);
    int current=index;
   do {
   if(table[index]->id==id){
    table[index]=NULL;
   break;
   }
   index=hashFunction(index+1);
   } while(current!=index);
  
};
void search(int id){
    int index=hashFunction(id);
    int current=index;
    do {
        if(table[index]!=NULL&&table[index]->id==id){ 
            cout<<"Member found"<<endl;
            cout<<"Name: "<<table[index]->name<<endl;
            cout<<"Age: "<<table[index]->age<<endl;
            cout<<"ID: "<<table[index]->id<<endl;
            return;
        }
       
        index=hashFunction(index+1);
    }while(index!=current);
    cout<<"Member not found"<<endl;
}

void display(){
    for(int i=0;i<7;i++){
        if(table[i]!=NULL){
            cout<<"Name: "<<table[i]->name<<endl;
            cout<<"Age: "<<table[i]->age<<endl;
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
    HashTable h(7);
    for(int i=10;i<=60;i+=10){
        h.insert(i,to_string(i),i);
    }
    cout<<"After insertion"<<endl;
    h.display();
    cout<<"\n\n\n";

    h.search(30);
    h.search(50);
    h.search(70);

    h.deleteMember(20);
    h.deleteMember(40);
    cout<<"\n\n\n";
    
    cout<<"After deletion"<<endl;
    h.display();
    cout<<"\n\n\n";


    h.insert(70,"70",70);
    h.insert(80,"80",80);
    cout<<"After insertion"<<endl;
    h.display();
    cout<<"\n\n\n";


    return 0;
}

