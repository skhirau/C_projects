#pragma once

#include<stdio.h>
#include<conio.h>
#include<ctype.h>

/**
addmember
showallmember
showspecificmember
editmember
deletemember

*/


struct   ///o.k.
{
    ///object ki id(m.MID) aur file mein id same hai
    ///sirf loop chalate wakt,(cursor set karte wakt)
    ///hum id se ek kam value lete hain
    char membername[100];
    int MID;
    ///if i left any possible member-variables here
    int fine;
    char isMember;
    int totalbooks ;
}m;



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

void getmember(int i)
{
    char ch ;
    ///m.MID = getmemberid(); iski jaroorat nahi
    printf("\nMEMBER ID         :  %d",i);

    printf("\nEnter member name : \n");
    fflush(stdin);
    gets(m.membername);

    if (m.totalbooks == 0)
    {
        printf("\nDo u want to continue your membership ?(y/n) \n");
        fflush(stdin);
        m.isMember = getchar();
        while (!(m.isMember == 'y' || m.isMember =='n'))
        {
            printf("\nINVALID ENTRY.");
            printf("\nDo u want to continue your membership ?(y/n).Enter again \n");
            fflush(stdin);
            m.isMember = getchar();
        }
    }


    return ;

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



void showallmembers()  ///o.k.
{
    FILE *p;
    p = fopen("MEMBERS.DAT","rb");

    if(p == NULL)
    {
        printf("\nThere are currently no members of the library.");
        printf("\nPress any key.");
        getch();
        return ;
    }

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

int showspecificmember(int i) ///O.K.
{
    m.MID = i ;
    int n,a ;
    FILE *p ;
    p = fopen("MEMBERS.DAT","rb");

    if(p == NULL)
    {
        printf("\nTHere are no members of the library.");
        fclose(p);
        return 0 ;
    }

    ///yahan aa gaye matlab members.dat exist

    fseek(p ,0,SEEK_END);
    n = ftell(p )/sizeof(m); ///yahan m object lagega
    fseek(p ,0,SEEK_SET);

    while (m.MID < 1 || m.MID >  n)
    {
        printf("\nINVALID MEMBER ID.\nEnter MEMBER ID again.\t");
        scanf("%d",&m.MID);
    }

    ///yahan aagaye matlab memberid sahi mil gayi.

    a = m.MID ;
    a-- ;
    fseek(p,a*sizeof(m),SEEK_SET); ///cursor set
    fread(&m,sizeof(m),1,p);  ///object m mein value aagayi
                              ///cursor ek object position aage badgaya,
    showm(); ///m ko print kardiya


    fclose(p);
    return 1 ;


}

void editmember()
{
    int t ;
    char ch;
    FILE *p ;

    do
    {
        printf("\nEnter member id     :      ");
        scanf("%d",&m.MID);

        t = showspecificmember(m.MID); ///Yahan object mein value aa chuki hogi
                             ///Cursor ek object position aage bad chuka hoga.
                             ///MEMBERS.DAT exist karta hai ya nai yahin check ho chuka hai
                             ///id sahi hai ya nahi yahin check ho chuka hai.
        if (t == 0)
        {
            printf("\nNo edition is possible.");
            return ;
        }

        printf("\nDo u want to edit the member details ?(y/n) \t");
        fflush(stdin);
        ch = getchar();
        ch = tolower(ch);
        if (ch != 'y')
        {
            printf("\nMEMBER details are not edited.");
            return ;
        }

///MEMBERS.DAT is opened here
        p = fopen("MEMBERS.DAT","r+b");
                    ///p will not be null


        getmember(m.MID); ///object mein user se value leli,m.MID kahin change nahi hua hai
        ///loop chalate wakt hum m.MID se ek value kam chalate hain
        t = m.MID ;
        t-- ;
        fseek(p,t*sizeof(m),SEEK_SET); ///cursor set again
        fwrite(&m,sizeof(m),1,p);          ///overwritten on file

        printf("\nAfter editing  :\n\n");

        t = m.MID ;
        t--;
        fseek(p,t*sizeof(m),SEEK_SET);     ///cursor set again
        fread(&m,sizeof(m),1,p);
        showm();

        fclose(p);
///MEMBERS.DAT is closed here

        printf("\nDo u want to edit details of another member ?(y/n) \t");
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
    int i ;///for passing values during calling.
    do
    {
        system("cls");
        printf("\t\t\t\tMAIN MENU :\n");
        printf("\n\t\t\t1.ADD MEMBER");
        printf("\n\t\t\t2.SHOW ALL MEMBERS");
        printf("\n\t\t\t3.SHOW SPECIFIC MEMBER");
        printf("\n\t\t\t4.EDIT MEMBER");
        printf("\n\t\t\t5.DELETE MEMBER");
        printf("\n\n\t\t\t6.EXIT     ");
        printf("\nEnter your choice number\t");
        scanf("%d",&op);
        system("cls");

        switch(op)
        {
            case 1 :
                addmember();
                break ;
            case 2 :
                showallmembers();
                break ;
            case 3 :
                printf("\nEnter member id   :  \t ");
                scanf("%d",&i);
                showspecificmember(i);
                printf("\nPress any key");
                getch();
                break ;
            case 4 :
                editmember();
                break ;
            case 5 :
                //deletemember();
                break ;
        }


    }while (op >= 1 && op<=5 );



}


/**
int main()
{
    MainMenu();
    //getmember();

    //showallmembers();

    printf("\nPress any key.");
    getch();
    return 0 ;
}

*/


