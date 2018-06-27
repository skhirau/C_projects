#pragma once

#include<stdio.h>
#include<conio.h>
#include<ctype.h>

/**
addbook
showallbook
showspecificbook
editbook
deletebook

*/


struct
{
    ///object ki id(b.BID) aur file mein id same hai
    ///sirf loop chalate wakt,(cursor set karte wakt)
    ///hum id se ek kam value lete hain
    char bookname[100];
    int BID;
    char author[100];
    float price;
    char status,writeoff;
}b;

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



int getbookid()
{
    FILE *f;
    f = fopen("BOOKS.DAT","rb");

    if (f != NULL)
    {
        fseek(f,0,SEEK_END);
        int n = (ftell(f))/sizeof(b);
        //printf("\n\nopening and closing in getid\n\n");
        fclose(f);
        return n ;
    }

    //printf("\n\nReturning id = 0 value.\n\n");

    fclose(f);
    return 0 ;
    ///matlab internally BID ek kam chal rahi hai.
}

void getbook(int i) ///object b mein user se value lene ka jugaad
{
    char ch ;
    ///b.BID = getbookid(); iski jaroorat nahi hai
    printf("\nBOOK ID         :  %d",i);
    printf("\nEnter book name : \n");
    fflush(stdin);
    gets(b.bookname);
    printf("\nEnter Author name :\n");
    fflush(stdin);
    gets(b.author);
    printf("\nEnter price of the book : \n");
    scanf("%f",&b.price);
    /*
    printf("\nEnter book status (y/n)\n");
    fflush(stdin);
    b.status = getchar();
    while (!(b.status == 'y' || b.status =='n'))
    {
        printf("\nINVALID ENTRY.");
        printf("\nEnter book status again (y/n)\n");
        fflush(stdin);
        b.status = getchar();

    }
    */

    if (b.status == 'y')
    {
        printf("\nIs book written off or not ?(y/n)\n");
        fflush(stdin);
        b.writeoff = getchar();
        while (!(b.writeoff == 'y' || b.writeoff =='n'))
        {
            printf("\nINVALID ENTRY.");
            printf("\nIs book written off or not ?(y/n)Enter again \n");
            fflush(stdin);
            b.writeoff = getchar();

        }

    }/**
    else   ///by default b.writeoff = 'n' in addbook(),so else is unnecessary.
    {
        b.writeoff = 'n';
    }*/

    if (b.writeoff == 'y')
        b.status = 'n';



    return ;

}

void addbook() ///yahan read and write stream,dono ka use hota hai.
{
    char ch ;

    do
    {
        system("cls");
        b.BID = getbookid();
        b.BID++;
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

void showallbooks()
{
    FILE *p;
    p = fopen("BOOKS.DAT","rb");

    if (p == NULL)
    {
        printf("\nThere are currently no books in the library.");
        printf("\nPress any key.");
        getch();
        return ;
    }

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

int showspecificbook(int i) ///O.K.   ///sirf id lene ka kaam yahan nahi hai
{
    int n,a ;
    b.BID = i ;
    FILE *p ;
    p = fopen("BOOKS.DAT","rb");
    if (p == NULL)
    {
        printf("\nThere are no books available in the library.");
        fclose(p);

        return 0;
    }

    /// yahan aagaya matlab books.dat mein kuch to hai

    fseek(p,0,SEEK_END);
    n = ftell(p)/sizeof(b); ///yahan b object lagega
    fseek(p,0,SEEK_SET);

    while (b.BID < 1 || b.BID > n)
    {
        printf("\nINVALID BOOK ID.\nEnter Book ID again.\t");
        scanf("%d",&b.BID);
    }

    ///yahan aagaye matlab bookid sahi mil gayi.


    a = b.BID;
    a-- ;
    fseek(p,a*sizeof(b),SEEK_SET); ///cursor set
    fread(&b,sizeof(b),1,p);  ///object b mein value aagayi,
                              ///cursor ek object position aage badgaya
    showb(); ///b ko print kardiya


    fclose(p);
    return 1 ;
}


void editbook()
{
    int t ;
    char ch ;
    FILE *p ;

    do
    {

        printf("\nEnter book id     :     ");
        scanf("%d",&b.BID);

        t = showspecificbook(b.BID); ///Yahan object mein value aa chuki hogi
                             ///Cursor ek object position aage bad chuka hoga.
                             ///BOOKS.DAT exist karta hai ya nai yahin check ho chuka hai
                             ///id sahi hai ya nahi yahin check ho chuka hai.
        if (t == 0)
        {
            printf("\nNo edition is possible.");
            return ;
        }

        printf("\nDo u want to edit the book details ?(y/n) \t");
        fflush(stdin);
        ch = getchar();
        ch = tolower(ch);
        if (ch != 'y')
        {
            printf("\nBOOK details are not edited.");
            return ;
        }

///BOOKS.DAT is opened here
        p = fopen("BOOKS.DAT","r+b");
                    ///p will not be null



        getbook(b.BID); ///object mein user se value leli,b.BID kahin change nahi hua hai
        ///loop chalate wakt hum b.BID se ek value kam chalate hain
        t = b.BID ;
        t-- ;
        fseek(p,t*sizeof(b),SEEK_SET);     ///cursor set again
        fwrite(&b,sizeof(b),1,p);          ///overwritten on file

        printf("\nAfter editing  :\n\n");

        t = b.BID ;
        t--;
        fseek(p,t*sizeof(b),SEEK_SET);     ///cursor set again
        fread(&b,sizeof(b),1,p);
        showb();

        fclose(p);
///BOOKS.DAT is closed here

        printf("\nDo u want to edit details of another book ?(y/n) \t");
        fflush(stdin);
        ch = getchar();
        ch = tolower(ch);

    }while(ch == 'y');

    return;
}


/**

void MainMenu()
{
    int op;
    int i;///for passing values during calling.
    do
    {
        system("cls");
        printf("\t\t\t\tMAIN MENU :\n");
        printf("\n\t\t\t1.ADD BOOK");
        printf("\n\t\t\t2.SHOW ALL BOOKS");
        printf("\n\t\t\t3.SHOW SPECIFIC BOOK");
        printf("\n\t\t\t4.EDIT BOOK");
        printf("\n\t\t\t5.DELETE BOOK");
        printf("\n\n\t\t\t6.EXIT     ");
        printf("\nEnter your choice number\t");
        scanf("%d",&op);
        system("cls");

        switch(op)
        {
            case 1 :
                addbook();
                break ;
            case 2 :
                showallbooks();
                break ;
            case 3 :
                printf("\nEnter book id     :  \t ");
                scanf("%d",&i);

                showspecificbook(i);
                printf("\nPress any key.");
                getch() ;
                break ;
            case 4 :
                editbook();
                break ;
            case 5 :
                //deletebook();
                break ;
        }


    }while (op >= 1 && op<=5 );



}



int main()
{
    MainMenu();
    //getbook();

    //showallbooks();
    //editbook();
    printf("\nPress any key.");
    getch();
    return 0 ;
}


*/
