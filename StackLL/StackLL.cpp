
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
}*top = NULL;

void push(int x)
{
    struct Node* t;
    t = (struct Node*)malloc(sizeof(struct Node));

    if (t == NULL)
    {
        printf("stack is full\n");
    }
    else
    {
        t->data = x;
        t->next = top;
        top = t;
    }
}

int pop()
{
    struct Node* t;
    int x = -1;
    if (top == NULL)
    {
        printf("Stack is Empty\n");
    }
    else
    {
        t = top;
        top = top->next;
        x = t->data;
        free(t);
    }
    return x;
}

void Display()
{
    struct Node* p;
    p = top;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int isBalanced(char* exp)
{
    int i;

    for (i = 0; exp[i] != NULL; i++)
    {
        if (exp[i] == '(')
            push(exp[i]);
        else if (exp[i] == ')')
        {
            if (top == NULL)
            {
                printf("The string is NOT Balance\n");
                return 0;
            }
                 
            pop();
        }
    }
    if (top == NULL)
    {
        printf("The string is Balance\n");
        return 1;
    }
    else
    {
        printf("The string is NOT Balance\n");
        return 0;
    }
}

int pre(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    return 0;
}

int isOperand(char x)
{
    if (x == '+' || x == '-' || x == '*' || x == '/')
        return 0;
    else 
        return 1;
}

char* convert(char* infix)
{
    struct stack* st;
    char* postfix = new char[strlen(infix) + 2];
    int i = 0, j = 0;

    while (infix[i] != NULL)
    {
        if (isOperand(infix[i]))
            postfix[j++] = infix[i++];
        else
        {
            if (pre(infix[i]) > pre(top->data))
                push(infix[i++]);
            else
                postfix[j++] = pop();
        }
    }
    
    while (top != NULL)
        postfix[j++] = pop();
    postfix[j] = '\0';

    return postfix;
}

int eval(char* postfix) 
{
    struct Node* st;
    int i = 0, x, y, r = 0;
    for (i = 0; postfix[i] != '\0'; i++)
    {
        if (isOperand(postfix[i]))
            push(postfix[i]-'0');
        else
        {
            y = pop();
            x = pop();
            switch (postfix[i])
            {
            case'+': 
                r = x + y;
                break;
            case'-':
                r = x - y;
                break;
            case'*':
                r = x * y;
                break;
            case'/':
                r = x / y;
                break;
            }
            push(r);
        }
    }
    return top->data;
}

int main()
{
    char exp[] = "((a+b)*(c-d)))";
    push('#');
    char postfix[] = "234*+82/-";

    //isBalanced(exp);

    //Display();

    //printf("%d ", pop());

    printf("Result is %d\n", eval(postfix));

    return 0;
}
