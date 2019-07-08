#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

class hashtable
{
    public:
        hashtable();
        int key1,key2;
        char string1[30];
        char string2[30];
        void pushback(int,char[],int);
}hashTable[10];

char hashindex[10];

hashtable::hashtable()
{
    strcpy(string1,"");
    strcpy(string2,"");
}

void hashtable::pushback(int key,char string[30],int index)
{
    if(strcmp(string1,"")==0)
    {
        strcpy(this->string1,string);
        this->key1=key;
        hashindex[index]='0';
    }
    else if(strcmp(string2,"")==0)
    {
        strcpy(this->string2,string);
        this->key2=key;
        hashindex[index]='1';
    }
}

int hashFunc(int key)
{
    int per_inc=(1+key)%11;
    int per_inc1=key%11;
    int result=((per_inc+per_inc1)%13)%11;
    int count=0;
    while(hashindex[result]=='1')
    {
        result=((result+per_inc1)%13)%11;
    }
    return result;
}

void find(int key,char string[30])
{
    cout<<"\nFind function\n";
    int per_inc=(1+key)%11;
    int per_inc1=key%11;
    int result=((per_inc+per_inc1)%13)%11;
    int count=0;
    while(!(strcmp(hashTable[result].string1,string)==0 || strcmp(hashTable[result].string2,string)==0)
           && hashindex[result]!='*')
    {
        result=((result+per_inc1)%13)%11;
        count++;
        if(count==10)
            break;
    }
    if(strcmp(hashTable[result].string1,string)==0 || strcmp(hashTable[result].string2,string)==0)
    {
        cout<<"Data found in the Hashtable\n";
    }
    else
        cout<<"Data not found in the Hashtable";
}

void deletedata(int key,char string[30])
{
    cout<<"\nFind function\n";
    int per_inc=(1+key)%11;
    int per_inc1=key%11;
    int result=((per_inc+per_inc1)%13)%11;
    int count=0;
    while(!(strcmp(hashTable[result].string1,string)==0 || strcmp(hashTable[result].string2,string)==0)
           && hashindex[result]!='*')
    {
        result=((result+per_inc1)%13)%11;
        count++;
        if(count==10)
            break;
    }
    if(strcmp(hashTable[result].string1,string)==0 )
    {
        if(hashindex[result]=='1')
            hashindex[result]='0';
        else
            hashindex[result]='*';
        strcpy(hashTable[result].string1,"");
        cout<<"Data deleted in the Hashtable\n";
    }
    else if(strcmp(hashTable[result].string2,string)==0)
    {
        if(hashindex[result]=='1')
            hashindex[result]='0';
        else
            hashindex[result]='*';
        strcpy(hashTable[result].string2,"");
        cout<<"Data deleted in the Hashtable\n";
    }
    else
        cout<<"Data not found in the Hashtable";
}

void insert(int key,char string[30])
{
        int index=hashFunc(key);
        hashTable[index].pushback(key,string,index);
}

void display()
{
    cout<<"\n\n\tHASHTABLE\n\n";
    for(int i=0;i<10;i++)
    {
        if(hashindex[i]!='*')
        {
            cout<<i<<"\t"<<hashTable[i].key1<<"\t"<<hashTable[i].string1<<"\n";
            if(hashindex[i]=='1')
            {
                cout<<i<<"\t"<<hashTable[i].key2<<"\t"<<hashTable[i].string2<<"\n";
            }
        }
    }
}

int main()
{
    strcpy(hashindex,"**********");
    fstream fp;
    int key,input_key;
    char name[30],input_name[30];
    fp.open("Hash1.txt",ios::in);
    int choice,count=0;
    while(fp>>key>>name)
    {
        count++;
        cout<<count<<"\t"<<key<<"\t"<<name<<"\n";
        insert(key,name);
    }
    insert(key,name);
    fp.close();
    while(1)
    {
        cout<<"\n1.Find Data\n2.Delete Data\n3.Display Table\n4.Exit\nEnter your choice : ";
        cin>>choice;
        fflush(stdin);
        switch(choice)
        {
            case 1: cout<<"\nEnter the key of your fruit that you want to find : ";
                    cin>>input_key;
                    cout<<endl<<"Enter the name of your fruit that you want to find : ";
                    cin>>input_name;
                    cout<<"\n"<<input_key<<"\t"<<input_name;
                    find(input_key,input_name);
                    break;
            case 2: cout<<"\nEnter the key of your fruit that you want to find : ";
                    cin>>input_key;
                    cout<<endl<<"Enter the name of your fruit that you want to find : ";
                    cin>>input_name;
                    cout<<"\n"<<input_key<<"\t"<<input_name;
                    deletedata(input_key,input_name);
                    break;
            case 3:display();break;
            case 4:exit(0);
            default:cout<<"Invalid choice\n";
        }
    }
}
