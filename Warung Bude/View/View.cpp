#include "../Controllel/Systen.h"
#include "../Controllel/Controller.h"

int main()
{
    systemAndDate();
    puts("1. Add Dish");
    puts("2. Remove Dish");   
    puts("3. Add Customer");
    puts("4. Search Customer");
    puts("5. View Warteg");
    puts("6. Order");
    puts("7. Payment");
    puts("8. Exit Warteg");

    int choose = 0;
    do{
        printf(">> ");
        scanf("%d",&choose); getchar();
    }while(choose < 1 || choose > 8);

    switch(choose)
    {
        case 1:
            clear();
            addDish();
            clear();
            main();
            break;
        case 2:
            clear();
            removeDish();
            clear();
            main();
            break;
        case 3:
            clear();
            addCustomer();
            clear();
            main();
            break;
        case 4:
            clear();
            searchCustomer();
            clear();
            main();
            break;
        case 5:
            clear();
            viewWarteg();
            clear();
            main();
            break;
        case 6:
            clear();
            order();
            clear();
            main();
            break;
        case 7:
            clear();
            payment();
            clear();
            main();
            break;
        default:
            clear();
            exit();
    }
}