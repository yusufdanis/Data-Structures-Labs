#include <stdio.h>
#include <stdlib.h>

struct employee{
    int ID;
    int freeAt;
    int totalTime;
    struct employee *next;
};

struct customer{
    int ID;
    int startTime;
    int processTime;
    int waitingTime;
    int helper;
    struct customer *front;
    struct customer *rear;
    struct customer *next;
};

typedef struct employee employee;
typedef struct customer customer;

employee *new_employee(employee *top, int id){ //Insert employees by id
    employee *ptr = malloc(sizeof(employee));
    ptr->ID = id;
    ptr->freeAt = 0;
    ptr->totalTime = 0;

    if (top == NULL){
        ptr->next =  NULL;
        top = ptr;
    }
    else{
        ptr->next = top;
        top = ptr;
    }

    return top;
}

void help_customer(customer *c, employee *top){ //Match customer with suitable employee
    if (top==NULL){
        return;
    }

    else if(c->startTime>=top->freeAt){
        c->helper = top->ID;
        top->freeAt = c->startTime + c->processTime;
        top->totalTime = top->totalTime + c->processTime;
    }
    else{
        help_customer(c, top->next);
    }
}

customer *new_customer(customer *c, employee *top, int id, int start, int process){ //New customer
    customer *ptr = malloc(sizeof(customer));
    ptr->ID = id;
    ptr->startTime = start;
    ptr->processTime = process;

    help_customer(ptr,top);
    while (ptr->helper == 0){
        ptr->startTime = ptr->startTime + 1;
        ptr->waitingTime++;
        help_customer(ptr,top);
    }
    
    if (c->front == NULL){
        c->front = ptr;
        c->rear = ptr;
        c->next = NULL;
    }
    else{
        c->rear->next = ptr;
        c->rear = ptr;
        c->rear->next = NULL;
    }

    return c;
}

void customerStats(customer *c){ //Printing customer stats at the end of the transactions
    customer *ptr = malloc(sizeof(customer));
    ptr = c->front;

    if(ptr == NULL){
        printf("\nQUEUE IS EMPTY");
    }
    else{
        printf("\n");
        while (ptr!=c->rear){
            printf("%d ", ptr->ID);
            printf("%d ", ptr->helper);
            printf("%d ", ptr->startTime);
            printf("%d ", ptr->startTime + ptr->processTime); //Calculating finish time
            printf("%d\n", ptr->waitingTime);
            ptr = ptr->next;
        }

        printf("%d ", ptr->ID);
            printf("%d ", ptr->helper);
            printf("%d ", ptr->startTime);
            printf("%d ", ptr->startTime + ptr->processTime); ////Calculating finish time
            printf("%d\n\n", ptr->waitingTime);
    }
}

void employeeStats(employee *top){ //Printing employee stats at the end of the transactions
    employee *ptr = malloc(sizeof(employee));
    ptr = top;
    
    if (top==NULL){
        printf("\nSTACK IS EMPTY");
    }
    else{
        while (ptr!=NULL){
            printf("%d ", ptr->ID);
            printf("%d\n", ptr->totalTime);
            ptr = ptr->next;
        }
    }
}



int main(){
    employee *e = NULL; //ASK TO LECTURER
    for(int i=1;i<7;i++){   //Initialize employees
        e = new_employee(e,i);
    }

    customer *c;
    int id;
    int start;
    int process;
    while(1){   //Initialize customers and making transactions
        scanf("%d", &id);
        if (id==-1){
            break;
        }
        scanf("%d", &start);
        scanf("%d", &process);
        c = new_customer(c, e, id, start, process);
    }

    customerStats(c);
    employeeStats(e);
}