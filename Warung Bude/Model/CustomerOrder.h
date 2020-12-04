#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MAX = 26;
int hashTable[MAX];

unsigned long djb2(char *str)   {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
    return hash % MAX;
}

struct CustomerOrder{
    char dishName[255];
    int dishPrice_per_qty;
    int qty;
    CustomerOrder *next;
    // CustomerOrder *headCustomerOrder, *tailCustomerOrder;
};

struct Table{
    char PersonName[255];;
    CustomerOrder *order;
    Table *next;
}*headTable[MAX],*tailTable[MAX];

CustomerOrder *createNewOrder(char *dishName,int dishPrice_per_qty,int qty)
{
    CustomerOrder *newOrder = (CustomerOrder*)malloc(sizeof(CustomerOrder));
    strcpy(newOrder->dishName,dishName);
    newOrder->dishPrice_per_qty = dishPrice_per_qty;
    newOrder->qty = qty;
    newOrder->next= NULL;
    return newOrder;
}

Table *createNewTable(char *personName)
{
    Table *newTable = (Table*)malloc(sizeof(Table));
    strcpy(newTable->PersonName,personName);
    newTable->next = NULL;
    return newTable;
}

void insertTable(char *personName)
{
    int index = djb2(personName);
    if(!headTable[index])
    {
        Table *newTable = createNewTable(personName);
        headTable[index] = tailTable[index] = newTable;
    }
    else{
        Table *newTable = createNewTable(personName);
        tailTable[index]->next = newTable;
        tailTable[index] = newTable;
    }
}

int searchCustomer(char *personName)
{
    for(int i = 0;i<MAX;i++)
    {
        Table *curr = headTable[i];
        while(curr)
        {
            if(strcmp(curr->PersonName,personName) == 0)
            {
                return 1;
            }
            curr = curr->next;
        }
    }
    return -1;
}

void viewCustomer()
{
    int count = 1;
    for(int i = 0;i<MAX;i++)
    {
        if(headTable[i])
        {
            Table *curr = headTable[i];
            while(curr)
            {
                printf("%d. %s\n",count,curr->PersonName);
                curr = curr->next;
                count++;    
            }
        }
    }
}

void orderPush(char *personName, char *dishName,int dishPrice, int qty)
{
    int flag = 0;
    for(int i = 0;i<MAX;i++)
    {
        if(headTable[i])
        {
            Table *curr = headTable[i];
            while(curr)
            {
                if(strcmp(curr->PersonName,personName) == 0)
                {
                    flag = 1;
                    break;
                }
                curr = curr->next;
            }
            if(flag == 1)
            {
                if(!(curr->order))
                {
                    curr->order = createNewOrder(dishName,dishPrice,qty);
                }  
                else{
                    while(curr->order->next)
                    {
                        curr->order = curr->order->next;
                    }
                    curr->order->next = createNewOrder(dishName,dishPrice,qty);
                } 
                break;
            }
        }
    }
}

void popALL(int index)
{
    int count = 0;
    for(int i = 0;i<MAX;i++)
    {
        if(headTable[i])
        {
            Table *curr = headTable[i];
            while(curr)
            {
                count++;
                if(count = index)
                {
                    do{
                        if(!(curr->order->next))
                        {
                            curr->order = NULL;
                            free(curr->order);
                        }
                        else{
                            CustomerOrder *temp = curr->order->next;
                            curr->order = NULL;
                            free(curr->order);
                            curr->order = temp;
                        }
                    }while(curr->order);
                }
                curr = curr->next;
            }
        }
    }
}

void personPay(int index) 
{ 
    int count = 0;
    for(int i = 0;i<MAX;i++)
    {
        if(headTable[i])
        {
            Table *curr = headTable[i];
            while(curr)
            {
                count++;
                if(count == index) 
                {
                    printf("%s\n",curr->PersonName);
                    if(!curr->order)
                    {
                        puts("You haven't Order yet!");
                        printf("Please enter to continue.."); getchar();
                        return;
                    }
                    else{
                        int countFood = 0;
                        int totalFood = 0;
                        while(curr->order)
                        {
                            countFood++;
                            printf("[%d]. %s x%d\n",countFood,curr->order->dishName,curr->order->qty);
                            totalFood += curr->order->dishPrice_per_qty * curr->order->qty;
                            curr->order = curr->order->next;
                        }
                        printf("Total : %d\n",totalFood);
                        printf("Please enter to continue.."); getchar();
                        return;
                    }
                }
                curr = curr->next;
            }
        }
    }
}

int countPerson()
{
    int count = 0;
    for(int i = 0;i<MAX;i++)
    {
        if(headTable[i])
        {
            Table *curr = headTable[i];
            while(curr)
            {
                count++;
                curr = curr->next;
            }
        }
    }
    return count;
}

