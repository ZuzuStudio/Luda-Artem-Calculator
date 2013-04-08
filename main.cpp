#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "SQ_Source.h"

using namespace std;

int get_priority(Data element);
Data get_operation (Data element, Data b, Data a);

int main(int argc, char**argv)
{
    char *str = new char[128];
    char str_help[]="help";
    char str_exit[]="exit";
    char str_h[]="--help";

    if (argc>1)
    {
        for(int i=1; i<argc; ++i)
            strcat(str,argv[i]);
        if(!strcmp(str,str_h))
        {
            cout<<"\nCalculator\n\n";
            return 0;
        }
    }

    while(strcmp(str,str_exit))
    {
        if (argc==1)
        {
            cout<<">";
            cin.getline(str,128);
            if(!strcmp(str,str_exit))
            {
                cout<<"\nThe program is ended\n"<<endl;
                return 0;
            }
            if (!strcmp(str,str_help))
            {
                cout<<"\n1.Enter some numbers and signs"<<endl;
                cout<<"2.To exit the program enter 'exit'"<<endl;
                cout<<"\n>";
                cin.getline(str,128);
            }

        }

        int length;
        length=strlen(str);

        Queue row_str;
        Data new_element;

        for(int i=0; i<length; )
        {
            if(str[i]>='0' && str[i]<='9' )
            {
                new_element.is_number=true;
                new_element.number=atof(&str[i]);
                row_str.push_back(new_element);
                while((str[i]>='0' && str[i]<='9') || str[i]=='.' || str[i]=='e')
                {
                    if(str[i]=='e')
                        ++i;

                    ++i;
                }
            }
            else
            {
                if (str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/' || str[i]=='^' || str[i]=='(' || str[i]==')')
                {
                    new_element.is_number=false;
                    new_element.operation=str[i];
                    row_str.push_back(new_element);
                }
                ++i;
            }
        }

        Queue rpn;
        Stack op;

        while(!row_str.is_empty())
        {
            new_element=row_str.on_front();
            row_str.pop_front();

            if (new_element.is_number)
                rpn.push_back(new_element);
            else if (op.is_empty())
                op.push(new_element);
            else if ((get_priority(op.on_top()) < get_priority(new_element)) || new_element.operation=='(')
                op.push(new_element);
            else if(new_element.operation==')')
            {
                while (op.on_top().operation!='(')
                {
                    rpn.push_back(op.on_top());
                    op.pop();
                }
                op.pop();
            }
            else
            {
                while(!op.is_empty() && (get_priority(op.on_top()) >= get_priority(new_element)))
                {
                    rpn.push_back(op.on_top());
                    op.pop();
                }
                op.push(new_element);
            }
        }

        while(!op.is_empty())
        {
            rpn.push_back(op.on_top());
            op.pop();
        }

        Data a, b, c;
        Stack result;

        while(!rpn.is_empty())
        {
            new_element=rpn.on_front();
            rpn.pop_front();

            if(new_element.is_number)
            {
                c=new_element;
                result.push(new_element);
            }
            else if (new_element.operation=='+' || new_element.operation=='-' || new_element.operation=='*' || new_element.operation=='/' || new_element.operation=='^')
            {
                a=result.on_top();
                result.pop();
                b=result.on_top();
                result.pop();
                c=get_operation(new_element,b,a);
                result.push(c);
            }
            else
            {
                cout<<"\nError! Invalid operation '"<<new_element.operation<<"'!\n";
                return 0;
            }
        }
        cout<<endl<<"Result is: "<<c.number<<endl<<endl;
        if (argc>1) return 0;
    }
    return 0;
}


int get_priority(Data element)
{
    switch(element.operation)
    {
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case '*':
        return 2;
        break;
    case '/':
        return 2;
        break;
    case '^':
        return 3;
        break;
    default:
        return 0;
    }
    return 0;
}

Data get_operation (Data element, Data b, Data a)
{
    Data c;
    switch(element.operation)
    {
    case '+':
        c.number=b.number+a.number;
        break;
    case '-':
        c.number=b.number-a.number;
        break;
    case '*':
        c.number=b.number*a.number;
        break;
    case '/':
        c.number=b.number/a.number;
        break;
    case '^':
        c.number=pow(b.number,a.number);
        break;
    }
    return c;
}
