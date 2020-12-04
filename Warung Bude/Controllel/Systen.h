#include<stdlib.h>
#include<time.h>
#include<stdio.h>

void clear()
{
    for(int i = 0;i<30;i++) puts("");
}

void systemAndDate()
{
    #ifdef _WIN64
        printf("Windows 64-bit");
    #elif _WIN32
        printf("Windows 32-bit");
    #elif __APPLE__ || __MACH__
        printf("Mac OSX");
    #elif __linux__
        printf("Linux");
    #elif __FreeBSD__
        printf("FreeBSD");
    #elif __unix || __unix__
        printf("Unix");
    #else
        printf("Other");
    #endif
        puts("");
        time_t tanggal;
        time(&tanggal);
        printf("%s", asctime(localtime(&tanggal)));
}

void exit()
{
    puts("Please expand your terminal to fullscreen!");
    printf("Press enter to continue...."); getchar();
    clear();
    char temp[255];
    FILE *fp = fopen("../Model/splash-screen.txt","r");
    while(fscanf(fp,"%[^\n]\n",temp) != EOF)
    {
        printf("%s\n",temp);
    }

}