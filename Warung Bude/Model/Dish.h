#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MAX_ELEMENT = 26;

struct Dish{
    char dishName[255];
    int dishPrice;
    int qty;
    Dish *next,*prev;
}*headDish[MAX_ELEMENT],*tailDish[MAX_ELEMENT];

unsigned long DJB2(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
    return hash % MAX_ELEMENT;
}

Dish *createNewDish(char *dishName,int dishPrice, int qty)
{
    Dish *newDish = (Dish*)malloc(sizeof(Dish));
    strcpy(newDish->dishName,dishName);
    newDish->dishPrice = dishPrice;
    newDish->qty = qty;
    newDish->prev = newDish->next = NULL;
    return newDish;
}

void insertDish(char *foodName,int dishPrice, int dishQty)
{
    int index = DJB2(foodName);

    if(!headDish[index])
    {
        headDish[index] = tailDish[index] = createNewDish(foodName,dishPrice,dishQty);
    }
    else{
        Dish *newDish = createNewDish(foodName,dishPrice,dishQty);
        tailDish[index]->next = newDish;
        newDish->prev = tailDish[index];
        tailDish[index] = newDish;
    }
}

int searchDish(char *dishName)
{
    for(int i = 0;i<MAX_ELEMENT;i++)
    {
        Dish *curr = headDish[i];
        while(curr)
        {
            if(strcmp(curr->dishName,dishName) == 0)
            {
                return 1;
            }
            curr = curr->next;
        }
    }
    return -1;
}

void viewDish()
{
    int count = 0;
    for(int i = 0;i < MAX_ELEMENT;i++)
    {
        if(headDish[i])
        {
            Dish *curr = headDish[i];
            while(curr)
            {
                printf("%-6.d %-24s %03d                 Rp.%-5d\n",++count,curr->dishName,curr->qty,curr->dishPrice);
                curr = curr->next;
            }
        }
    }
    puts("");
}

void DeleteDish(char *dishRemove)
{
    int flag = 0;
    for(int i = 0;i < MAX_ELEMENT;i++)
    {
        if(headDish[i])
        {    
            if(headDish[i]->next == NULL && strcmp(headDish[i]->dishName,dishRemove) == 0)
            {
                headDish[i] = NULL;
                free(headDish[i]);
                flag = 1;
                break;
            }
            if(strcmp(headDish[i]->dishName,dishRemove) == 0)
            {
                struct Dish *temp = headDish[i]->next;
                headDish[i]->next  = NULL;
                headDish[i]->next = NULL;
                free(headDish[i]);
                headDish[i] = temp;
                headDish[i]->prev = NULL;
                flag = 1;                     
            }
            else if(strcmp(tailDish[i]->dishName,dishRemove) == 0)
            {
                struct Dish *temp = tailDish[i]->prev;
                tailDish[i]->next = tailDish[i]->prev = NULL;
                free(tailDish[i]);
                tailDish[i] = temp;
                tailDish[i]->next = NULL;
                flag = 1;
            }
            else {
                Dish *curr = headDish[i];
                while(curr)
                {
                    if(strcmp(curr->dishName,dishRemove) == 0)
                    {
                        flag = 1;
                        curr->prev->next = curr->next;
                        curr->next->prev = curr->prev;
                        curr->next = curr->prev = NULL;
                        free(curr);
                        break;
                    }
                    curr = curr->next;
                }
            }   
        }    
    }
    (flag == 0) ? puts("The dish wasn't found") : puts("The dish has been removed!"); 
}

int searchDishPrice(char *dishName)
{
    for(int i = 0;i<MAX_ELEMENT;i++)
    {
        Dish *curr = headDish[i];
        while(curr)
        {
            if(strcmp(curr->dishName,dishName) == 0)
            {
                return curr->dishPrice;
            }
            curr = curr->next;
        }
    }
    return 0;
}

int searchDishQty(char *dishName)
{
    for(int i = 0;i<MAX_ELEMENT;i++)
    {
        Dish *curr = headDish[i];
        while(curr)
        {
            if(strcmp(curr->dishName,dishName) == 0)
            {
                return curr->qty;
            }
            curr = curr->next;
        }
    }
    return 0;
}

int quantityCount(int len,int koordinat,char *dishTemp)
{
    int kali = 1;
    int total = 0;
    for(int k = len-1;k > koordinat;k--)
    {
       total += (dishTemp[k] - '0') * kali;
       kali *= 10;
    }
    return total;
}

int countDishType()
{
    int count = 0;
    for(int i = 0;i<MAX_ELEMENT;i++)
    {
        if(headDish[i])
        {
            Dish *curr = headDish[i];
            while(curr)
            {
                count++;
                curr = curr->next;
            }
        }
    }
    return count;
}