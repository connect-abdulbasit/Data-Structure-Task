#include <iostream>
using namespace std;

class Account{
int accNo;
string name;
public:
Account(int accNo,string name){
    this->accNo=accNo;
    this->name=name;
}
friend class Bank;
};
class Bank{
Account **acc;
int size;
int hashFunction1(int index){
return index%size;
}
int hashFunction2(int index){
    return 7-(index%7);
}
public:
Bank(int size){
    this->size=size;
    acc=new Account*[size];
    for(int i=0;i<size;i++){
      acc[i]=NULL;
    }
}

void insert(int accNo,string name){
    int index=accNo%size;
    if(acc[index]==NULL){ 
        acc[index]=new Account(accNo,name);
    }else{
        int index2=hashFunction2(accNo);
        int count=1;
        while(acc[index+count*index2]!=NULL){ 
        count++;
        }
        acc[index+count*index2]=new Account(accNo,name);
    }
}
void search(int accNo){
    int index=accNo%size;
    
        if(acc[index]!=NULL&&acc[index]->accNo==accNo){
            cout<<"Account found"<<endl;
            return;
        }
    
    int index2=hashFunction2(accNo);
    int count=1;
    while(acc[index+count*index2]!=NULL){
        if(acc[index+count*index2]->accNo==accNo){
            cout<<"Account found"<<endl;
            return;
        }
        count++;
    }
    cout<<"Account not found"<<endl;
}

void deleteAcc(int accNo){
    int index=accNo%size;
    int index2=hashFunction2(accNo);
    int count=0;
    while(acc[index+count*index2]!=NULL){
        if(acc[index+count*index2]->accNo==accNo){
            delete acc[index+count*index2];
            acc[index+count*index2]=NULL;
            cout<<"Deleted"<<endl;
            return;
        }
        count++;
    }
}
void display(){
    for(int i=0;i<size;i++){
        if(acc[i]!=NULL){
            cout<<acc[i]->accNo<<" "<<acc[i]->name<<endl;
        }
    }
}
~Bank(){
    for(int i=0;i<size;i++){
        if(acc[i]!=NULL){
            delete acc[i];
        }
    }
    delete[] acc;
}
};

int main()
{

    Bank bank(11);


    bank.insert(101, "Customer 101");
    bank.insert(111, "Customer 111");
    bank.insert(121, "Customer 121");
    bank.insert(131, "Customer 131");
    bank.insert(141, "Customer 141");
    bank.insert(151, "Customer 151");

cout<<"After insertion"<<endl;
    bank.display();
cout<<"\n\n\n";
    bank.search(111);
    bank.search(141);
    bank.search(161);

cout<<"\n\n\n";

    bank.deleteAcc(111);
    bank.deleteAcc(131);


cout<<"\n\nAfter deletion"<<endl;
    bank.display();

  
    bank.insert(161, "Customer 161");
    bank.insert(171, "Customer 171");

cout<<"\n\nAfter insertion"<<endl;
    bank.display();

    return 0;
}

