#include<stdio.h>
#include "../Model/Dish.h"
#include "../Model/CustomerOrder.h"

void addDish()
{
    char nameDish[255];
    do{
        bool flag = true; 
        printf("Insert the name of the dish [Lowercase Letters]: ");
        scanf("%[^\n]",nameDish); getchar();
        for(int i = 0;nameDish[i] != '\0';i++)
        {
            if(nameDish[i] >= 'A' && nameDish[i] <= 'Z')
            {
                flag = false;
                break;
            }
        }
        if(flag == true) break;
    }while(true);

    int dishPrice;
    do{
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d",&dishPrice); getchar();
        if(dishPrice >= 1000 && dishPrice <= 50000) break;
    }while(true);

    int qty;
    do{
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d",&qty); getchar();
        if(qty >= 1 && qty <= 999) break;
    }while(true);

    printf("The dish has been added\n");
    printf("Press enter to continue...."); getchar();
    insertDish(nameDish,dishPrice,qty);
}

void removeDish()
{
    puts("\tBude's Menu\n");
    puts("================================================================\n");
    puts("No.    Name                     Quantity            Price");
    viewDish();
    puts("================================================================\n");

    char dishNameRemove[255];
    printf("Insert dish's name to be deleted: ");
    scanf("%[^\n]",dishNameRemove); getchar();
    DeleteDish(dishNameRemove);
    puts("");
    
    printf("Press enter to continue..."); getchar();
}

void addCustomer()
{
    char customerName[255];
    do{
        int flag = 1;
        printf("Insert the customer's name [Without space]: ");
        scanf("%[^\n]",customerName); getchar();
        for(int i = 0;i<customerName[i] != '\0';i++)
        {
            if(customerName[i] == ' ')
            {
                flag = 0;
                break;
            }
        }
        if(flag == 1) break;
    }while(true);
    insertTable((char*)customerName);
    puts("\nCustomer has been added!\n");
    printf("Press enter to continue"); getchar();

}

void searchCustomer()
{
    char searchCustomerName[255];
    printf("Insert the customer's name to be searched: ");
    scanf("%[^\n]",searchCustomerName); getchar();
    int found = searchCustomer(searchCustomerName);
    (found == 1) ? printf("%s is present\n",searchCustomerName) : printf("%s is not present\n",searchCustomerName);
    printf("Press enter to continue..."); getchar();
}

void viewWarteg()
{
    puts("Customer's List\n");
    viewCustomer();
    puts("");
    printf("Press enter to continue..."); getchar();
}

void order()
{
    char customerName[255];
    do{
        printf("Insert the customer's name: ");
        scanf("%[^\n]",customerName); getchar();
        int found = searchCustomer(customerName);
        if(found == -1)
        {
            printf("Customer's name haven't found!"); getchar();
            return;
        }
        else if(found == 1)
        {
            break;
        }
    }while(true);

    int amount;
    do{
        printf("Insert the amount of dish: ");
        scanf("%d",&amount); getchar();
        int foodType = countDishType();
        if(amount > foodType) printf("Restaurant only have %d menu\n",foodType);
        else break;
    }while(true);

    for(int i = 1;i <= amount;i++)
    {
        char dishName[255],dishTemp[255];
        int quantity;
        do{
            int flag = 0,koordinat;
            printf("[%d] Insert the dish name and quantity: ",i);
            scanf("%[^\n]",dishTemp); getchar();
            int len = strlen(dishTemp);
            for(int j = 0;j<len;j++)
            {
                if((dishTemp[j] != 'x' || dishTemp[j] != 'X') && (dishTemp[j+1] >= '1' && dishTemp[j+1] <= '9'))
                {
                    koordinat = j;
                    for(int k = 0;k<j;k++)
                    {
                        if(k == j-1)
                        {
                            dishName[k] = '\0';
                        }
                        else{
                            dishName[k] = dishTemp[k];
                        }
                    }
                }
            }
            quantity = quantityCount(len,koordinat,dishTemp);   

            int found = searchDish(dishName);
            if(found == 1) 
            {
                int dishQty = searchDishQty(dishName);
                if(quantity > dishQty)
                {
                    puts("You ordered too much");
                    printf("Press enter to continue..."); getchar();
                    return;
                }
                int dishPrice = searchDishPrice(dishName);
                orderPush(customerName,dishName,dishPrice,quantity);
                break;
            }
        }while(true);
    }
    puts("Order Success!");
    printf("Press enter to continue..."); getchar();
}

void payment()
{
    int customerIndex;
    do{
        printf("Insert the customer's Index : ");
        scanf("%d",&customerIndex);  getchar();
        int countPeople = countPerson();
        if(customerIndex > countPeople || customerIndex < 1) puts("Index is out bonds");
        else break;
    }while(true);
    personPay(customerIndex);
}
