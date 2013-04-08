#include "SQ_Source.h"

////////////////////STACK////////////////////

Stack::Stack():
    top(0)
{
}

Stack::~Stack()
{
    clear();
}

Stack::List::List(Data new_data):
    data(new_data), next(0)
{
}

Stack::List::~List()
{
    data.number=0;
    data.operation=0;
    data.is_number=0;
}

void Stack::push(Data new_data)
{
    List *p=0;
    p=new List(new_data);
    p->next=top;
    top=p;
    p=0;
}

void Stack::pop()
{
    if(!is_empty())
    {
        List *p=0;
        p=top;
        top=top->next;
        delete p;
        p=0;
    }
}

Data Stack::on_top() const
{
    if(is_empty())
        throw -1;
    return top->data;
}

bool Stack::is_empty() const
{
    return top==0;
}

void Stack::clear()
{
    while(top)
    {
        List *p;
        p=top;
        top=top->next;
        delete p;
        p=0;
    }
}

////////////////////QUEUE////////////////////

Queue::Queue():
    first(0),end(0)
{
}

Queue::~Queue()
{
    clear();
}

Queue::List::List(Data new_data):
    data(new_data), next(0)
{
}

Queue::List::~List()
{
    data.number=0;
    data.operation=0;
    data.is_number=0;
    next=0;
}

void Queue::push_back(Data new_data)
{
    List *p = new List(new_data);

    if(first)
    {
        end->next=p;
        end=p;
    }
    else
    {
        end=first=p;
    }
    p = 0;
}

void Queue::pop_front()
{
    List *p;
    p = first;
    first = first->next;
    if(!first)
        end=0;
    p->next = 0;
    delete p;
    p = 0;
}

Data Queue::on_front() const
{
    if(is_empty())
        throw -1;
    return first->data;
}

bool Queue::is_empty() const
{
    return first==0;
}

void Queue::clear()
{
    while(first)
    {
        List *p;
        p=first;
        first=first->next;
        delete p;
        p=0;
    }
    end=0;
}


