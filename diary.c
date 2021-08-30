#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>


int width = 50;

void createFile(FILE *diary);

void start();

void line();

//cleare the console
void cls();

//goto function
void gotoxy(int x,int y);

void delay(int number_of_seconds);


void main(){
    cls();
    start();
    FILE *diary;
    while(30){
        char c = getch();
        // printf("%d",c);

        switch (c)
        {
        case 97:
            cls();
            line();
            printf("%*s",width/2,"* * * * Add Task * * * *\n\n");
            printf("(Press esc to exit)\n(Enter to save)\n\n");
            time_t t = time(NULL);
            struct tm tm = *localtime(&t); 
            diary = fopen("my_diary.txt","a");
            fprintf(diary, "\n\n(%02d-%02d-%d)", tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900);
            fclose(diary);
            while(getch() != 27){
                char task[100];
                printf("Enter Task: ");
                scanf(" %[^\n]",&task);
                diary = fopen("my_diary.txt","a");
                fprintf(diary,"\n@) %s.",task);
                fclose(diary);
                printf("added\n");
            }
            printf("\n\nclosed\n(click a to re-start)\n(click esc to exit)");

            break;
        
        case 27:
            cls();
            line();
            start();
            break;

        case 98:
            cls();
            line();
            printf("%*s",width/2,"* * * * My Tasks * * * *\n\n");
            printf("(Press esc to exit)\n(Enter to view todo)\n\n");

            for(int i = 0 ; getch() != 27; i++){
                if(i == 1) break;
                diary = fopen("my_diary.txt","r");
                char c = fgetc(diary);
                while(c != EOF){
                    printf("%c",c);
                    c = fgetc(diary);
                    delay(1);
                }
                fclose(diary);
                printf("\n\nPress Esc to exit");
            }
            break;

        case 114:
            createFile(diary);
            printf("\n\n(File created)");
            break;

        case 48:
            exit(1);

        default:
            printf("Invalid Input\n");
        }
        
    }

}

//This function id is to clear the console screen
void cls(){
    printf("\e[1;1H\e[2J");
}

//this function to assigning location to text
void gotoxy(int x,int y){
printf("%c[%d;%df",0x1B,y,x);
}

//This function delays the program
void delay(int number_of_seconds){
    int milli_seconds = 70 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

//This creates animated line
void line(){
    for(int i = 0;i<10;i++){
        printf("_");
        delay(1);
    }
    for(int i = 0;i<5;i++){
        printf("*");
        delay(1);
    }
    for(int i = 0;i<10;i++){
        printf("_");
        delay(1);
    }
    cls();
}


//This is starting function
void createFile(FILE *diary){
    diary = fopen("my_diary.txt","w");
    fprintf(diary,"%s","My Diary\n\n");
    fclose(diary);
}

void start(){
    printf("%*s\n",width,"* * * * *  Welcome To Mydiary  * * * * *\n\n");
    printf("%s","Enter \"r\" for reset or create new file\n");
    printf("%s","Enter \"a\" for Add Todo\n");
    printf("%s","Enter \"b\" for View Todo\n\n\n");
    printf("%s","Enter \"0\" to exit\n");
}