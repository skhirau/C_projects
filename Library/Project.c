#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include"BOOKSDAT.C"
#include"MEMBERSDAT.C"
#include"ISSUEDAT.C"




void newentriesmenu()
{
    int op;
    do
    {
        system("cls");
        printf("\t\t\t\tENTRY MENU : \n ");
        printf("\n\t\t\t1.NEW BOOK      ");
        printf("\n\t\t\t2.NEW MEMBER    ");
        printf("\n\t\t\t3.    EXIT      ");



        printf("\nEnter your choice number\t");
        scanf("%d",&op);
        system("cls");

        switch(op)
        {
            case 1 :
                addbook();
                break ;
            case 2 :
                addmember();
                break ;


        }


    }while (op >= 1 && op<=2 );


}

void editmenu()
{
    int op;
    do
    {
        system("cls");
        printf("\t\t\t\tEDIT MENU :\n   ");
        printf("\n\t\t\t1.EDIT BOOK     ");
        printf("\n\t\t\t2.EDIT MEMBER   ");
        printf("\n\t\t\t3.    EXIT      ");



        printf("\nEnter your choice number\t");
        scanf("%d",&op);
        system("cls");

        switch(op)
        {
            case 1 :
                editbook();
                break ;
            case 2 :
                editmember();
                break ;


        }


    }while (op >= 1 && op<=2 );


}

void transactionsmenu()
{
    int op;
    do
    {
        system("cls");
        printf("\t\t\t\tTRANSACTIONS MENU :\n   ");
        printf("\n\t\t\t1.ISSUE BOOK     ");
        printf("\n\t\t\t2.RETURN BOOK   ");
        printf("\n\t\t\t3.Show total transactions");
        printf("\n\t\t\t4.Show Currently Issued Books ");
        printf("\n\t\t\t5.    EXIT      ");



        printf("\nEnter your choice number\t");
        scanf("%d",&op);
        system("cls");

        switch(op)
        {
            case 1 :
                issuebook();
                break ;
            case 2 :
                returnbook();
                break ;
            case 3 :
                showtransactions();
                printf("press any key");
                getch();
                break ;
            case 4 :
                showcurrentissuedbooks();
                printf("press any key");
                getch();
                break ;


        }


    }while (op >= 1 && op<=4 );


}

void reportmenu()
{
    int op,d;
    do
    {
        system("cls");
        printf("\t\t\t\tREPORTS MENU :\n   ");
        printf("\n\t\t\t1.REPORTS ON  BOOKS     ");
        printf("\n\t\t\t2.REPORTS ON  MEMBERS   ");
        printf("\n\t\t\t3.Show Specific Book    ");
        printf("\n\t\t\t4.Show Specific Member  ");
        printf("\n\t\t\t5.    EXIT      ");



        printf("\nEnter your choice number\t");
        scanf("%d",&op);
        system("cls");

        switch(op)
        {
            case 1 :
                showallbooks();
                break ;
            case 2 :
                showallmembers();
                break ;
            case 3 :

                printf("\nEnter book id     :  \t ");
                scanf("%d",&d);

                showspecificbook(d);
                printf("\nPress any key.");
                getch() ;
                break ;
            case 4 :
                printf("\nEnter member id   :  \t ");
                scanf("%d",&d);

                showspecificmember(d);
                printf("\nPress any key");
                getch();

                break ;


        }


    }while (op >= 1 && op<=2 );


}



void MainMenu()
{
    int op;
    do
    {
        system("cls");
        printf("\t\t\t\tMAIN MENU :\n   ");
        printf("\n\t\t\t1.NEW ENTRIES   ");
        printf("\n\t\t\t2.EDIT          ");
        printf("\n\t\t\t3.TRANSACTIONS  ");
        printf("\n\t\t\t4.REPORTS       ");
        printf("\n\t\t\t5.    EXIT      ");

        printf("\nEnter your choice number\t");
        scanf("%d",&op);
        system("cls");

        switch(op)
        {
            case 1 :
                newentriesmenu();
                break ;
            case 2 :
                editmenu();
                break ;
            case 3 :
                transactionsmenu();
                break ;
            case 4 :
                reportmenu();
                break ;

        }


    }while (op >= 1 && op<=4 );

}///function ends here


int main()
{
    MainMenu();
    printf("\nPress any key.");
    //getch();
    return (0) ;
}
