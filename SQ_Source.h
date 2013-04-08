#ifndef SQ_SOURCE_H_INCLUDED
#define SQ_SOURCE_H_INCLUDED

struct Data
{
    double number;
    char operation;
    bool is_number;
};

////////////////////STACK////////////////////

class Stack
{
public:
    Stack();
    ~Stack();
    void push(Data new_data);
    void pop();
    Data on_top() const;
    bool is_empty() const;
    void clear();
private:
    struct List
    {
        List(Data new_data);
        ~List();
        Data data;
        List *next;

    }*top;
};

////////////////////QUEUE////////////////////

class Queue
{
public:
    Queue();
    ~Queue();
    void push_back(Data new_data);
    void pop_front();
    Data on_front() const;
    bool is_empty() const;
    void clear();
private:
    struct List
    {
        List(Data new_data);
        ~List();
        Data data;
        List *next;
    }*first,*end;
};

#endif // S&Q_SOURCE_H_INCLUDED
