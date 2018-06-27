#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include"BOOKSDAT.C"
#include"MEMBERSDAT.C"


/**

///1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
/**
                                FOR MAKING NEW BOOK ENTRY (from BOOKSDAT.C)
/

struct
{
    char bookname[100];
    int BID;
    char author[100];
    float price;
    char status,writeoff;
}b;

int getbookid()
{
    FILE *f;
    f = fopen("BOOKS.DAT","rb");

    if (f != NULL)
    {
        fseek(f,0,SEEK_END);
        int n = (ftell(f))/sizeof(b);
        fclose(f);
        return n ;
    }

    fclose(f);
    return 0 ;
}

void addbook() ///yahan read and write stream,dono ka use hota hai.
{
    char ch ;

    do
    {
        system("cls");
        b.BID = getbookid();
        b.BID++; ///pehle BID loonga, fir file open karoonga

        FILE *p ;
        p = fopen("BOOKS.DAT","r+b");
        if (p!= NULL)
            fseek(p,0,SEEK_END);   ///We will start writing from the end.
        else
            p = fopen("BOOKS.DAT","w+b");

        printf("\nBOOK ID         :  %d",b.BID);

        printf("\nEnter book name : \n");
        fflush(stdin);
        gets(b.bookname);
        printf("\nEnter Author name :\n");
        fflush(stdin);
        gets(b.author);
        printf("\nEnter price of the book : \n");
        scanf("%f",&b.price);
        b.status = 'y';
        b.writeoff = 'n';

        /// yahan tak--> object b mein dalgayi values.
        ///File mein daalne ke liye--> b to file

        printf("\n\n\nDo u want to save the data ? (y/n) \t");
        fflush(stdin);
        ch = getchar();
        ch = tolower(ch);
        if (ch == 'y')
            fwrite(&b,sizeof(b),1,p);

        printf("\n\nDo u want to add more data ? (y/n) ? \t");
        fflush(stdin);
        ch = getchar();
        ch = tolower(ch);
        fclose(p);

    }while(ch =='y');


}

///9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999


///oigooe
///1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
/**
                                FOR MAKING SHOW BOOK object b (from BOOKSDAT.C)
/

void showb()
{
    printf("\bBook id     :    %d",b.BID);
    printf("\nBook name   :    %s",b.bookname);
    printf("\nAuthor name :    %s",b.author);
    printf("\nBook Price  :    %0.2f",b.price);
if (b.status == 'y')
    printf("\nBook Status :    AVAILABLE");
else
    printf("\nBook Status :    NOT AVAILABLE");
    printf("\nWriteoff    :    %c",b.writeoff);
    printf("\n\n\n");

}

///9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999






///1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
/**
                                FOR MAKING SHOW ALL BOOKS (from BOOKSDAT.C)
/

void showallbooks()
{
    FILE *p;
    p = fopen("BOOKS.DAT","rb");
    fseek(p,0,SEEK_END);
    int n = (ftell(p))/sizeof(b);
    fseek(p,0,SEEK_SET);
    int i ;

    for (i = 0 ; i <= n-1 ; i++)
    {
        fread(&b,sizeof(b),1,p);
        showb();
    }
    printf("\nPress any key.");
    getch();
    fclose(p);

}
///9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999





///1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
/**
                                FOR MAKING NEW MEMBER ENTRY (from MEMBERSDAT.C)
/
struct
{
    char membername[100];
    int MID;
    ///if i left any possible member-variables here
    int fine;
    char isMember;
    int totalbooks ;
}m;

int getmemberid()  ///o.k.
{
    FILE *f;
    f = fopen("MEMBERS.DAT","rb");

    if (f != NULL)
    {
        fseek(f,0,SEEK_END);
        int n = (ftell(f))/sizeof(m);
        fclose(f);
        return n ;
    }

    fclose(f);
    return 0 ;
}


void addmember() ///O.K.
{
    char ch ;

    do
    {
        system("cls");
        m.MID = getmemberid();
        m.MID++;
        FILE *p ;
        p = fopen("MEMBERS.DAT","r+b");
        if (p!= NULL)
            fseek(p,0,SEEK_END);   ///We will start writing from the end.
        else
            p = fopen("MEMBERS.DAT","w+b");

        printf("\nMEMBER ID         :  %d",m.MID);

        printf("\nEnter member name : \n");
        fflush(stdin);
        gets(m.membername);

        m.isMember = 'y';
        ///By default,fine and totalbooks ki value 0 hogi,
        ///jo already hi 0 se initialized hai, (m is a GLOBAL variable.)

        /// yahan tak--> object b mein dalgayi values.
        ///File mein daalne ke liye--> b to file

        printf("\n\n\nDo u want to save the data ? (y/n) \t");
        fflush(stdin);
        ch = getchar();
        ch = tolower(ch);
        if (ch == 'y')
            fwrite(&m,sizeof(m),1,p);

        printf("\n\nDo u want to add more data ? (y/n) ? \t");
        fflush(stdin);
        ch = getchar();
        ch = tolower(ch);
        fclose(p);

    }while(ch =='y');


}



///9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999



///1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
/**
                                FOR MAKING SHOW MEMBER object m (from MEMBERSDAT.C)
/
void showm()  ///o.k.
{
    printf("\nmember id     :    %d",m.MID);
    printf("\nmember name   :    %s",m.membername);

if (m.isMember == 'y')
    printf("\nMember Status :    MEMBER");
else
    printf("\nMember Status :    NOT A MEMBER/MEMBERSHIP EXPIRED");

    printf("\nFine due      :    %d",m.fine );
    printf("\n\nTOTAL BOOKS ISSUED  :     %d",m.totalbooks);
    printf("\n\n\n");

}

///9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999


///1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
/**
                                FOR MAKING SHOW ALL MEMBERS (from MEMBERSDAT.C)
/
void showallmembers()  ///o.k.
{
    FILE *p;
    p = fopen("MEMBERS.DAT","rb");
    fseek(p,0,SEEK_END);
    int n = (ftell(p))/sizeof(m);
    fseek(p,0,SEEK_SET);
    int i ;

    for (i = 0 ; i <= n-1 ; i++)
    {
        fread(&m,sizeof(m),1,p);
        showm();
    }
    printf("\nPress any key.");
    getch();
    fclose(p);

}



///9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999

*/



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
                //newentriesmenu();
                break ;
            case 2 :
                //editmenu();
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
        printf("\n\t\t\t3.    EXIT      ");



        printf("\nEnter your choice number\t");
        scanf("%d",&op);
        system("cls");

        switch(op)
        {
            case 1 :
                //newentriesmenu();
                break ;
            case 2 :
                //editmenu();
                break ;


        }


    }while (op >= 1 && op<=2 );


}

void reportmenu()
{
    int op;
    do
    {
        system("cls");
        printf("\t\t\t\tREPORTS MENU :\n   ");
        printf("\n\t\t\t1.REPORTS ON  BOOKS     ");
        printf("\n\t\t\t2.REPORTS ON  MEMBERS   ");
        printf("\n\t\t\t3.    EXIT      ");



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
        printf("\n\t\t\t3.TRNASACTIONS  ");
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
