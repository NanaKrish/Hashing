#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class HashTableEntry
{
    public:
      int k;
      string v;
      HashTableEntry(int k, string v) {
         this->k= k;
         this->v = v;
      }
};

class hashtable
{
    public:
        HashTableEntry **t;
        int tsize;
        hashtable(int n)
        {
            tsize = n;
            t = new HashTableEntry * [n];
        }
        int hashfunc(int key)
        {
            int pic = (1+key)%11;
            int flag = 0;
            int in = key%tsize;
            int ke;
            while(t[in]!=0)
            {
                ke = key+pic;
                in = ke%tsize;
            }
            return in;
        }
        void insert(int key, string dat)
        {
            int h ;
            h = hashfunc(key);
            cout<<h;
           /* if (t[h] != NULL)
            {
                delete t[h];
            }*/
            t[h]->k = key;
            t[h]->v = dat;
        }
        string find1(int key)
        {
            int h;
            h = hashfunc(key);
            while(t[h]!=NULL && t[h]->k!=key)
            {
                h = h+1%tsize;
            }
            if(t[h]==NULL)
            {
                return "NULL";
            }
            else
            {
                return t[h]->v;
            }
        }
        void delelt(int key)
        {
            int h;
            h = hashfunc(key);
            while(t[h]!=NULL && t[h]->k!=key)
            {
                h = h+1%tsize;
            }
            if(t[h]==NULL)
            {
                return;
            }
            else if(t[h]->k==key)
            {
                t[h]->k=0;
                t[h]->v="";
            }
        }
        void displaytable()
        {
            int k=0;
            for(k=0; k<tsize; k++)
            {
                cout<<t[k]->k<<" "<<t[k]->v;
            }
        }
};

int main()
{
    cout<<"Enter the size of the hashtable necessary\n";
    int n;
    cin>>n;
    hashtable h1(n);
    int key;
    string val1, val2, val;
    fstream fin;
    fin.open("Hash2.txt", ios::in);
    int count = 1;
    while(fin>>key>>val1>>val2)
    {
        val = val1+" "+val2+"\0";
        cout<<count<<" "<<key<<" "<<val<<" "<<endl;
        h1.insert(key, val);
        count+=1;
        if(count==n+1)
        {
            break;
        }
    }
    fin.close();
    h1.displaytable();
}
