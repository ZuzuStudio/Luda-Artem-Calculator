#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct RPN
{
    double number;
    char operation;
    bool is_number;
};

struct List
{
    RPN Info;
    List *Next;
};

void push_back(List *&begin, List *&end, RPN dt);
RPN pop_front(List *&begin, List *&end);
RPN on_Front(List *&begin);
bool isEmpty(List *begin);

int main()
{
    List *begin=NULL;
    List *end=NULL;

    cout<<">";

    string s;
    getline(cin,s);
    int length=0;
    for(int i=0; s[i]!='\0'; ++i)
        length++;

    char str[length];
    for(int i=0; i<length; ++i)
        str[i]=s[i];

    for(int i=0; i<length; ++i)
        cout<<s[i];
    cout<<endl;
    for(int i=0; i<length; ++i)
        cout<<str[i];
    cout<<endl;

    RPN new_element;
    for(int i=0; i<length; )
    {
        if(str[i]>'0' && str[i]<='9')
        {
            new_element.is_number=true;
            new_element.number=atof(str);
            push_back(begin,end,new_element);

            for(int j=i; (str[j]>'0' && str[j]<='9') || str[j]=='.'; ++j)
                str[j]='0';

            while (str[i]>='0' && str[i]<='9')
                ++i;
        }
        else
        {
            new_element.is_number=false;
            new_element.operation=str[i];
            push_back(begin,end,new_element);
            str[i]='0';

            while (str[i]>='0' && str[i]<='0')
                ++i;
        }
        for(int i=0; i<length; ++i)

            cout<<str[i]<<' ';
        cout<<endl;
    }

    while(!isEmpty(begin))
    {
        new_element=pop_front(begin,end);
        if(new_element.is_number)
            cout<<new_element.number<<' ';
        else cout<<new_element.operation<<' ';
    }
    return 0;
}

void push_back(List *&begin, List *&end, RPN dt)
{
    List *temp=NULL;
    temp=new List;
    temp->Info=dt;
    temp->Next=NULL;
    if (end)
    {
        end->Next=temp;
    }
    end=temp;
    if (!begin)
    {
        begin=end;
    }
}

RPN pop_front(List *&begin, List *&end)
{
    List *temp=begin;
    begin=begin->Next;
    RPN dt=temp->Info;
    delete temp;
    temp=NULL;
    if (!begin)
        end=NULL;
    return dt;
}

bool isEmpty(List *begin)
{
    return !begin;
}

RPN on_Front(List *&begin)
{
    return begin->Info;
}
