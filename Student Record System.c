#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>


COORD coord = {0,0};
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void add_account();
void edit_account();
void result();
void delete_account();
void show_studentinfo();
struct student
{
    char student_name[50];
    int roll_no;
    int std;
    char div;
    int D_O_B;
    int result;
} s;
void rectangle()
{
    //system("color 3");
    int i;
    gotoxy(100,1);
    printf("%c",187);
    gotoxy(100,25);
    printf("%c",188);
    for(i=1; i<100; i++)
    {
        gotoxy(i,1);
        printf("%c",205);
        gotoxy(i,25);
        printf("%c",205);
    }
    gotoxy(1,25);
    printf("%c",200);
    gotoxy(1,1);
    printf("%c",201);
    for(i=2; i<25; i++)
    {
        gotoxy(100,i);
        printf("%c",186);
        gotoxy(1,i);
        printf("%c",186);

    }
    gotoxy(100,7);
    printf("%c",185);
    gotoxy(1,7);
    printf("%c",204);
    for(i=2; i<100; i++)
    {
        gotoxy(i,7);
        printf("%c",205);
    }
    gotoxy(40,7);
    printf("%c",203);
    gotoxy(40,25);
    printf("%c",202);
    for(i=8; i<25; i++)
    {
        gotoxy(40,i);
        printf("%c",186);
    }
    printf("\n");

    // getch();
}
void title()
{
    gotoxy(41,3);
    printf("SAURABH VIDHYALYA");
    gotoxy(41,4);
    printf("Chandkheda, Ahmadvad");
    gotoxy(1,26);
    //getch();
}
void choice()
{
    int choice;
    while(1)
    {
        rectangle();
        gotoxy(3,9);
        printf("1 Add student account.");
        gotoxy(3,11);
        printf("2 Edit student details.");
        gotoxy(3,13);
        printf("3 Student result.");
        gotoxy(3,15);
        printf("4 Delete student account.");
        gotoxy(3,17);
        printf("5 Show student details.");
        gotoxy(3,19);
        printf("6. Exit.");
        gotoxy(3,21);
        printf("Your choice:- ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            add_account();
            break;
        case 2:
            edit_account();
            break;
        case 3:
            result();
            break;
        case 4:
            delete_account();
            break;
        case 5:
            show_studentinfo();
            break;
        case 6:
            return 0;
            break;
        gotoxy(1,30);
        }
    }

}

void clearWindow()
{
    int i,j;
    for(i = 41; i < 100; i++)
    {
        for(j = 8; j < 25; j++)
        {
            gotoxy(i,j);
            printf(" ");
        }
    }
    return;
}
main()
{
    system("color 02");
    rectangle();
    title();
    choice();
    //show_studentinfo();
    return 0;
}

void add_account()
{
    clearWindow();
    FILE *fp;
    fp=fopen("Student.bin","ab+");
    fseek(fp,0,SEEK_END);
    gotoxy(42,9);
    printf("Enter Student Name:- ");
    fflush(stdin);
    gets(s.student_name);
    gotoxy(42,11);
    printf("Enter student Roll.No:- ");
    scanf("%d",&s.roll_no);
    gotoxy(42,13);
    printf("Enter student std:- ");
    scanf("%d",&s.std);
    gotoxy(42,15);
    printf("Enter student Div:- ");
    fflush(stdin);
    scanf("%c",&s.div);
    gotoxy(42,17);
    printf("Enter student Birth date:- ");
    fflush(stdin);
    scanf("%d",&s.D_O_B);
    fwrite(&s,sizeof(s),1,fp);
    fclose(fp);
}

void edit_account()
{
    clearWindow();
    gotoxy(42,8);
    FILE* fp;
    fp=fopen("Student.bin","rb+");
    rewind(fp);
    char name[50];
    gotoxy(42,9);
    printf("Enter student name you want edit account:- ");
    fflush(stdin);
    gets(name);
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        if(strcmp(s.student_name,name)==0)
        {
            gotoxy(42,11);
            printf("\nEnter Student Name:- ");
            gets(s.student_name);
            fflush(stdin);
            gotoxy(42,13);
            printf("Enter Studnety Roll.No:- ");
            scanf("%d",&s.roll_no);
            fflush(stdin);
            gotoxy(42,15);
            printf("Enter Student std:- ");
            scanf("%d",&s.std);
            fflush(stdin);
            gotoxy(42,17);
            printf("Enter Student div:- ");
            scanf("%c",&s.div);
            fflush(stdin);
            gotoxy(42,19);
            printf("Enter Student birth date:- ");
            scanf("%d",&s.D_O_B);
            fflush(stdin);
            gotoxy(42,21);
            fwrite(&s,sizeof(s),1,fp);
            break;
        }
    }
    fclose(fp);
}

void result()
{
  FILE *fp;
  fp=fopen("Student.bin","rb+");
  int temp_roll_no;
  gotoxy(42,11);
  printf("Enter student Roll.no:- ");
  scanf("%d",&temp_roll_no);
  while(fread(&s,sizeof(s),1,fp)==1)
  {
      if(temp_roll_no=s.roll_no)
      {
          gotoxy(42,13);
          printf("Enter student result:- ");
          scanf("%d",&s.result);
          fseek(fp,0,SEEK_CUR);
          fwrite(&s,sizeof(s),1,fp);
      }
  }
  fclose(fp);
}

void delete_account()
{
    clearWindow();
    FILE *fp,*ft;
    char name[50];
    fp=fopen("Student.bin","rb+");
    gotoxy(42,9);
    printf("Enter name of student to delete:- ");
    fflush(stdin);
    gets(name);
    ft = fopen("Temp.bin","wb+");
    rewind(fp);
    while(fread(&s,sizeof(s),1,fp) == 1)
    {
        if(strcmp(s.student_name,name) != 0)
        {
            fwrite(&s,sizeof(s),1,ft);
        }
    }
    fclose(fp);
    fclose(ft);
    remove("Student.bin");
    rename("Temp.bin","Student.bin");
    fp=fopen("Student.bin","rb+");

}
void show_studentinfo()
{
   ///implement yourself
}
