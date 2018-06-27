#pragma once

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"BOOKSDAT.C"
#include"MEMBERSDAT.C"

struct date
{
    int y,m,day ;
};


struct
{
    int BID ;
    int MID ;
    struct date issdate;
    struct date duedate ;

}i;

struct
{
    //int hserial;
    int BID ;
    int MID ;
    char bookname[100];
    char membername[100];
    struct date issdate;
    struct date duedate;
    struct date returndate;
    int fine ;

}h;

void showi()
{
    printf("\nBID          :      %d",i.BID);
    printf("\nMID          :      %d",i.MID);
    printf("\nIssue date   :      %d-%d-%d",i.issdate.y,i.issdate.m,i.issdate.day);
    printf("\nDue   date   :      %d-%d-%d",i.duedate.y,i.duedate.m,i.duedate.day);
    printf("\n\n\n");

}

void showh()
{
    printf("\nBID          :      %d",h.BID);
    printf("\nMID          :      %d",h.MID);
    printf("\nBook   name  :      %s",h.bookname);
    printf("\nMember name  :      %s",h.membername);
    printf("\nIssue  date  :      %d-%d-%d",h.issdate.y,h.issdate.m,h.issdate.day);
    printf("\nDue    date  :      %d-%d-%d",h.duedate.y,h.duedate.m,h.duedate.day);
    printf("\nReturn date  :      %d-%d-%d",h.duedate.y,h.duedate.m,h.duedate.day);
    printf("\nFine Paid    :      %d",h.fine);
    printf("\n\n\n");

}


void showcurrentissuedbooks()
{
    int x,n;
    FILE *p ;
    p = fopen("ISSUE.DAT","rb");
    if (p == NULL)
    {
        printf("\nCurrently no books are issued.");
        return ;
    }

    fseek(p,0,SEEK_SET);
    x = ftell(p)/sizeof(i);

    fseek(p,0,SEEK_END);
    n = ftell(p)/sizeof(i);

    if (n-x == 0)
    {
        printf("_________________");
        printf("\nCurrently no books are issued.");
        return ;
    }


    fseek(p,0,SEEK_END);
    n = ftell(p)/sizeof(i);

    fseek(p,0,SEEK_SET);

    for (x = 0 ; x <= n-1 ; x++)
    {
        fread(&i,sizeof(i),1,p);
        showi();
    }

    return ;

}

void showtransactions()
{
    int x,n;
    FILE *p ;
    p = fopen("HISTORY.DAT","rb");
    if (p == NULL)
    {
        printf("\nNo books are issued yet.");
        return ;
    }

    /**
    fseek(p,0,SEEK_SET);
    x = ftell(p)/sizeof(i);

    fseek(p,0,SEEK_END);
    n = ftell(p)/sizeof(i);

    if (n-x == 0)
    {
        printf("\nCurrently no books are issued.");
        return ;
    }

    */

    fseek(p,0,SEEK_END);
    n = ftell(p)/sizeof(h);

    fseek(p,0,SEEK_SET);

    for (x = 0 ; x <= n-1 ; x++)
    {
        fread(&h,sizeof(h),1,p);
        showh();
    }

    return ;

}


void issuebook()
{
    char ch ;
    int op,bx,bn,mx,mn,ix,in,t ;

    do
    {
        FILE *pb,*pm,*pi ;

        printf("\nEnter book id     :  \t ");
        scanf("%d",&i.BID);

        int j = showspecificbook(i.BID); ///this function will take care of everything.

        if (j == 0) ///means BOOKS.DAT doesn't exist
            return ;
        ///yahan aagaye matlab specific-book show ho gayi.

        printf("\nEnter member id   :  \t ");
        scanf("%d",&i.MID);

        j = showspecificmember(i.MID); ///this function will take care of everything.

        if (j == 0) ///means MEMBERS.DAT doesn't exist
            return ;
        ///yahan aagaye matlab specific-member show ho gayi.


        ///ab finally issue karna hai

        printf("\nDo u want to issue the book ?(y/n)");
        fflush(stdin);
        ch = getchar();

        if (ch != 'y')
        {
            printf("BOOK NOT ISSUED.");
            return;
        }
///BOOKS.DAT file is opened here.
///MEMBERS.DAT file is opened here
        pb = fopen("BOOKS.DAT","r+b");
        pm = fopen("MEMBERS.DAT","r+b");

        t = i.BID; ///yahan i.BID liya hua hai,isliye koi problem nahi hui
                   /// because yahan tak i.BID mein koi change nahi aya hai.
        t--;
        fseek(pb,t*sizeof(b),SEEK_SET);
        fread(&b,sizeof(b),1,pb); ///object read hoga to cursor ek object position aage badjaaega
        if (b.status != 'y')
        {
            printf("\nBook is not currently available.");
            return ;
        }
        printf("\npehhhhhhhhhhle");
        showb();


        t = i.MID;
        t--;
        fseek(pm,t*sizeof(m),SEEK_SET);
        fread(&m,sizeof(m),1,pm); ///object read hoga to cursor ek object position aage badjaaega
        if (m.isMember != 'y' )
        {
            printf("\nYou currently are not a member of library. BOOK can't be issued.");
            return ;
        }
        showm();

        if (m.totalbooks == 3)
        {
            printf("\nU have reached the maximum limit of the total books that can be issued to a person.");
            printf("\nMORE BOOKs can't be issued to u.");
            return ;

        }

        b.status = 'n';
        m.totalbooks++;      ///object mein hogaya change,object overriden.

        t = i.BID;
        t--;
        fseek(pb,t*sizeof(b),SEEK_SET);/// again cursor position set.
        fwrite(&b,sizeof(b),1,pb); ///overriden on books.dat

        t = i.MID;
        t--;
        fseek(pm,t*sizeof(m),SEEK_SET); ///again cursor position set.
        fwrite(&m,sizeof(m),1,pm); ///overriden on members.dat

        printf("\nbaaaaaaad mein");
        showb();  ///yahan sirf object show ho raha hai.
        showm();

        fclose(pb);
        fclose(pm);
///BOOKS.DAT is closed here
///MEMBERS.DAT is closed here

///ISSUE.DAT file is opened here.
        pi = fopen("ISSUE.DAT","w+b");

        printf("\nEnter issue date");
        printf("Year yyyy    :      ");
        scanf("%d",&i.issdate.y);
        printf("Month  m     :      ");
        scanf("%d",&i.issdate.m);
        printf("Day   day    :      ");
        scanf("%d",&i.issdate.day);

        printf("\nEnter Due date");
        printf("Year yyyy    :      ");
        scanf("%d",&i.duedate.y);
        printf("Month  m     :      ");
        scanf("%d",&i.duedate.m);
        printf("Day   day    :      ");
        scanf("%d",&i.duedate.day);

        fseek(pi,0,SEEK_END);///cursor set in ISSUE.DAT file.
        fwrite(&i,sizeof(i),1,pi);///object i ki values are written in the ISSUE.DAT file

        fclose(pi);
///ISSUE.DAT file is closed here.
        printf("\n\nBOOK ISSUED.");

        printf("\nDo u want to issue more book ?");
        fflush(stdin);
        ch = getchar();
        ch = tolower(ch);


    }while (ch == 'y');


    return ;/// can be used with void functions too
            /// as a jump statement for exiting control from the function.

}

void returnbook()
{

    char ch ;
    int op,bx,bn,mx,mn,ix,in,hx,hn,t ;

    do
    {
        FILE *pb,*pm,*pi,*ph,*pt ;  ///notice ---> loop ke andar variables declaration

        printf("\nEnter book id     :  \t ");
        scanf("%d",&i.BID);

        int j = showspecificbook(i.BID); ///this function will take care of everything.

        if (j == 0) ///means BOOKS.DAT doesn't exist
            return ;
                ///yahan aagaye matlab specific-book show ho gayi.

        printf("\nEnter member id   :  \t ");
        scanf("%d",&i.MID);

        j = showspecificmember(i.MID); ///this function will take care of everything.

                ///This checking is unnecessary because humara issuebook() function aesa hai ki
                ///agar book issue hui hogi to book ka status jaroor change hua hoga.
                ///BUT still i m cheching this because then i don't have to check that
                ///ISSUE.DAT EXISTS or not.
        if(b.status =='y')
        {
            printf("\nThis book was not issued to anyone.So how it can be returned.");
            printf("\nU cannot return the book.");
            return ;
        }

        if (j == 0) ///means MEMBERS.DAT doesn't exist
            return ;
                ///yahan aagaye matlab specific-member show ho gayi.


                ///ab finally book return karna hai
        printf("\nDo u want to return the book ?(y/n)");
        fflush(stdin);
        ch = getchar();
        ch = tolower(ch);

        if (ch != 'y')
        {
            printf("\nBOOK not returned.");
            return ;
        }




///h mein likhne se pehle mujhe i open karwana padega to know issuedate,duedate
///ISSUE.DAT IS OPENED HERE.
        pi = fopen("ISSUE.DAT","r+b");
                        //HUMARA issuebook() function aesa hai ki agar book issue hui hogi
                        //to ISSUE.DAT mein entry jaroor hui hogi
                        //Also initially I have checked the book status,so
                        //it takes care of ISSUE.DAT
                        ///So i m not going to check if ISSUE.DAT exists or not
        ///if(pi == NULL) ///pi will not be null.


///files BOOKS.DAT,MEMBERS.DAT ARE OPENED HERE
        pb = fopen("BOOKS.DAT","r+b");
        pm = fopen("MEMBERS.DAT","r+b");

        fseek(pi,0,SEEK_END);
        in = ftell(pi)/sizeof(i);
        fseek(pi,0,SEEK_SET);

        t = i.BID ;
        for (ix = 0 ; ix <= in-1 ; ix++)
        {
            fread(&i,sizeof(i),0,pi); ///doing for knowing i.issuedate and i.duedate
            if (i.BID == t)
                break ;

        }
                        ///object i mein values aa chuki hogi,file khuli rakne ka
                        /// koi matlab nahi banta
        fclose(pi);
///ISSUE.DAT is closed here

        t = i.BID;
        t--;
        fseek(pb,t*sizeof(b),SEEK_SET);
        fread(&b,sizeof(b),1,pb); ///object read hoga to cursor ek object position aage badjaaega


        t = i.MID;
        t--;
        fseek(pm,t*sizeof(m),SEEK_SET);
        fread(&m,sizeof(m),1,pm); ///object read hoga to cursor ek object position aage badjaaega




        h.BID = i.BID ;
        h.MID = i.MID ;
        ///h.bookname = b.bookname ; string aese copy nahi hoti hai.
        strcpy(h.bookname,b.bookname); ///in the order of ///h.bookname = b.bookname ;
        ///h.membername = m.membername ;
        strcpy(h.membername,m.membername);
        h.issdate = i.issdate ;
        h.duedate = i.duedate ;

        printf("\nEnter return date.");
        printf("Year yyyy    :      ");
        scanf("%d",&h.returndate.y);
        printf("Month  m     :      ");
        scanf("%d",&h.returndate.m);
        printf("Day   day    :      ");
        scanf("%d",&h.returndate.day);

        m.fine += ( (h.returndate.m-h.duedate.m)*50 + (h.returndate.day - h.duedate.day)*2 );
        h.fine  =  m.fine ;

                ///object h mein values aa gayi.
                ///h ko fwrite karna hai
///HISTORY.DAT IS OPENED HERE.
        ph = fopen("HISTORY.DAT","r+b");
        if (ph == NULL)
            ph = fopen("HISTORY.DAT","w+b");
        else
            fseek(ph,0,SEEK_END);

        fwrite(&h,sizeof(h),1,ph);
        fclose(ph);
///HISTORY.DAT IS CLOSED HERE.


        b.status = 'y';
        m.totalbooks--;      ///object mein hogaya change,object overwritten.

        t = i.BID;
        t--;
        fseek(pb,t*sizeof(b),SEEK_SET);/// again cursor position set.
        fwrite(&b,sizeof(b),1,pb); ///overwritten on books.dat

        t = i.MID;
        t--;
        fseek(pm,t*sizeof(m),SEEK_SET); ///again cursor position set.
        fwrite(&m,sizeof(m),1,pm); ///overwritten on members.dat


                ///books.dat and members.dat are modified

        printf("\nbaaaaaaad mein\n\n");

        t = i.BID;
        t--;
        fseek(pb,t*sizeof(b),SEEK_SET);
        fread(&b,sizeof(b),1,pb); ///object read hoga to cursor ek object position aage badjaaega


        t = i.MID;
        t--;
        fseek(pm,t*sizeof(m),SEEK_SET);
        fread(&m,sizeof(m),1,pm); ///object read hoga to cursor ek object position aage badjaaega




        showb();  ///files mein overwrite hone ke baad,files show ho rahi hai.(not object)
        showm();

        fclose(pb);
        fclose(pm);
///BOOKS.DAT and MEMBERS.DAT are closed here


                ///issue.dat mein delete karna hai.
                ///so,issue.dat ko again open karna padega

///ISSUE.DAT IS OPENED HERE.
        pi = fopen("ISSUE.DAT","r+b");
                ///HUMARA issuebook() function aesa hai ki agar book issue hui hogi
                ///to ISSUE.DAT mein entry jaroor hui hogi
                ///Also initially I have checked the book status,so
                ///it takes care of ISSUE.DAT
                ///So i m not going to check if ISSUE.DAT exists or not
        ///if(pi == NULL) ///pi will not be null.

        fseek(pi,0,SEEK_END);
        in = ftell(pi)/sizeof(i);
        fseek(pi,0,SEEK_SET);

        t = i.BID ;
///TEMP.DAT is opened here
        pt = fopen("TEMP.DAT","w+b");

        for (ix = 0 ; ix <= in-1 ; ix++)
        {
            fread(&i,sizeof(i),0,pi);
            if (i.BID != t)
                fwrite(&i,sizeof(i),1,pt);

        }

        fclose(pi);
        fclose(pt);
///ISSUE.DAT is closed here
///TEMP.DAT is closed here
        remove("ISSUE.DAT");
        rename("TEMP.DAT","ISSUE.DAT");


        printf("Do u want to return another book ?(y/n)");
        fflush(stdin);
        ch = getchar();



    }while(ch == 'y');



    return ;/// can be used with void functions too
            /// as a jump statement for exiting control from the function.
}

/**
int main()
{

    //issuebook();
    //showallmembers();

    showcurrentissuedbooks();
    printf("\npress any key");
    getch();

    showtransactions();
    printf("\npress any key");
    getch();

    //returnbook();

    getch();
    return 0 ;
}
*/
