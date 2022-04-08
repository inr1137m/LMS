#include<stdio.h>
#include<mysql.h>
#include<string.h>
//Header files
char host[10]="localhost";
char dbuser[10]="root";
char dbpwd[10]="1234";
//global variable declaration part
void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    // mysql_close(con);
}
int main(int argc, char **argv)
{
    int start_scn(MYSQL *con);
    int log_sin(MYSQL *con);
    int admin(MYSQL *con,int id);
    int user(MYSQL *con,int id);
    int normaluser(MYSQL *con);
    int about();
    int dbcon();
    int datime(MYSQL *con);
    int bookname(MYSQL *con,char *bbid);
    int datedif(MYSQL *con,char *isd,char *crd);
    int report(MYSQL *con);
    int backup_restore(MYSQL *con);
    //
    MYSQL *connection=dbcon();
    mysql_query(connection,"'\'x");
    start_scn(connection);
}
int start_scn(MYSQL *con)
{
    mysql_query(con,"'\'x");
    int oPt;
    system("cls");
    printf("\nLIBRARY MANAGEMENT SYSTEM\n");
    printf("-------------------------\n");
    printf("\n  1 -> LOGIN / SIGNUP");
    printf("\n  2 -> NORMAL USER");
    printf("\n  3 -> ABOUT");
    printf("\n\n PRESS '0' FOR EXIT\n");
    printf("\n -> ");
    scanf("%d",&oPt);
    switch(oPt)
    {
    case 0:
    {
        exit(0);
    }
    case 1:
    {
        log_sin(con);
    }
    case 2:
    {
        normaluser(con);
    }
    case 3:
    {
        about();
    }
    default :
    {
        printf("\n  PLEASE ENTER CORRECT OPTION\n");
        start_scn(con);
    }
    }
}
int log_sin(MYSQL *con)
{

    int opt,utype;
    char name[20],dsig[20],pwd[10],fk[10],mno[15];
    char *sid,*spwd;
    char query[1024];
    int id,i,flag=0;
    system("cls");
    printf("\nLOGIN / SIGNUP\n");
    printf("\n  1 -> LOGIN\n  2 -> SIGNUP\n  0 -> BACK\n  -> ");
    scanf("%d",&opt);
    if(opt>2)
    {
        printf("\n  PLEASE ENTER CORRECT OPTION\n");
        log_sin(con);
    }
    if(opt==1)
    {
        do
        {
            printf("\nLOGIN\n-----\n");
            printf("\n\n ENTER YOUR USER ID\t: ");
            scanf("%d",&id);
            printf("\n\n ENTER YOUR PASSWORD\t: ");
            scanf("%s",&pwd);
            if(id<1000)
            {
                flag=0;
            }
            if(id>999)
            {
                if(id<2000)
                {
                    utype=1;
                    sprintf(query,"SELECT Pwd FROM AUSER where Id='%d'",id);
                    if(mysql_query(con,query))
                    {
                        finish_with_error(con);
                    }
                    flag=1;
                }
            }
            if(id>1999)
            {
                utype=0;
                sprintf(query,"SELECT Pwd FROM LUSER where Id='%d'",id);
                if(mysql_query(con,query))
                {
                    finish_with_error(con);
                }
                flag=1;
            }
            if(flag==1)
            {
                MYSQL_RES *result = mysql_store_result(con);
                if (result == NULL)
                {
                    finish_with_error(con);
                }
                int num_fields = mysql_num_fields(result);
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(result)))
                {
                    for(i = 0; i < num_fields; i++)
                    {
                        spwd=row[i];
                        //if(strcmp(row[i],pwd)==0)
                        //flag=1;
                    }
                    printf("\n");
                }
                mysql_free_result(result);
            }
            if(strcmp(spwd,pwd)==0)
            {
                opt=0;
                if(utype==1)
                {
                    printf("\nadmin\n");
                    admin(con,id);
                }
                if(utype==0)
                {
                    printf("\nuser\n");
                    user(con,id);
                }
            }
            else
            {
                flag=0;
            }
            if(flag==0)
            {
                printf("\nTHE USER ID OR PASSWORD IS WRONG, PLEASE TRY AGAIN !\n");
                printf("\nPRESS '0'-MENU '1'-RETRY : ");
                scanf("%d",&opt);
            }
        }
        while(opt==1);
    }
    if(opt==2)
    {
        do
        {
            printf("\nSIGN UP\n-------\n");
            printf("\nENTER THE FOLLOWING DETAILS TO REGISTER\n");
            printf("\n* PLEASE ENTER VALUES WITHOUT SPACE.\n");
            printf("\nFULL NAME\t:  ");
            scanf("%s",name);
            printf("\n1-STUDENT 2-TEACHER 3-OTHERS\n\nDESIGNATION\t:  ");
            scanf("%d",&opt);
            if(opt==1)
                strcpy(dsig,"STUDENT");
            if(opt==2)
                strcpy(dsig,"TEACHER");
            if(opt==3)
                strcpy(dsig,"OTHER");
            printf("\nPASSWORD\t:  ");
            scanf("%s",pwd);
            printf("\nFORGET KEY\t:  ");
            scanf("%s",fk);
            printf("\nMOBILE NUMBER\t:  ");
            scanf("%s",&mno);
            printf("\nPRESS '0'-CANCEL '1'-CONTINUE : ");
            scanf("%d",&opt);
            if(opt==0)
                log_sin(con);
            if(opt==1)
            {
                sprintf(query,"INSERT INTO LUSER VALUES(0,'%s','%s','%s','%s','%s',0,0,0,0,0,0)",name,dsig,pwd,fk,mno);
                if(mysql_query(con,query))
                {
                    finish_with_error(con);
                }
                flag=1;
            }
            if(flag)
            {
                sprintf(query,"SELECT * FROM LUSER");
                if (mysql_query(con,query))
                {
                    finish_with_error(con);
                }
                MYSQL_RES *result = mysql_store_result(con);
                if (result == NULL)
                {
                    finish_with_error(con);
                }
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(result)))
                {
                    for(i = 0; i < 1; i++)
                    {
                        sid=row[i];
                    }
                    //printf("\n");
                }
                mysql_free_result(result);
                printf("\nACCOUNT CREATED SUCCESSFULLY !\n");
                printf("\nYOUR USER ID\t:  %s",sid);
                printf("\nYOUR PASSWORD\t:  %s\n",pwd);
            }
            else
            {
                printf("\nSOMETHING WENT WRONG !... PLEASE TRY AGAIN LATER.\n");
            }
            printf("\nPRESS '0'-MENU '1'-RETRY : ");
            scanf("%d",&opt);
        }
        while(opt==1);
    }
    if(opt==0)
    {
        start_scn(con);
    }
}
int admin(MYSQL *con,int id)
{
    int opt,bid,tc,ac,i,uid,flag=NULL;
    char name[20],dsig[20],pwd[10],fk[10],mno[15],bkname[30],*bname,bkauthor[20],*bauthor,bkrack[30],*rack,ikey[30],*skey;
    char query[1024],*tmp[7],*dattime;
adminpoint:
    do
    {

        system("cls");
        printf("\nLOGGED IN AS : %d(ADMINISTRATOR)\n",id);
        printf("\n   1 -> BOOK ISSUE & RETURN");
        printf("\n   2 -> TOOLS / UTILITIES");
        printf("\n   3 -> PROFILE SETTINGS");
        printf("\n\n PRESS '0' FOR LOGOUT\n");
        printf("\n -> ");
        scanf("%d",&opt);
        switch(opt)
        {
        case 0:
        {
            printf("\n LOGGED OUT SUCCESSFULLY !...\n");
            break;
        }
        case 1:
        {
            if(opt==1)
            {
                do
                {
                    char *difc[6],*bisrt[12],tuid[10],*book[5],*cbid;
                    int j;
                    system("cls");
                    mysql_query(con,"'\'x");
                    printf("\n BOOK ISSUE & RETURN\n ===================\n");
                    printf("\n  1 -> ISSUE (OR)RETURN BOOK");
                    printf("\n  0 -> BACK\n -> ");
                    scanf("%d",&opt);
                    if(opt==1)
                    {
                        //issue
                        printf("\n ENTER THE USER ID  :  ");
                        scanf("%s",tuid);
                        if(mysql_query(con,"SELECT Uid FROM BISRT"))
                        {
                            finish_with_error(con);
                        }
                        else
                        {
                            MYSQL_RES *result = mysql_store_result(con);
                            if (result == NULL)
                            {
                                finish_with_error(con);
                            }
                            else
                            {
                                int num_fields = mysql_num_fields(result);
                                MYSQL_ROW row;
                                while ((row = mysql_fetch_row(result)))
                                {
                                    for(i = 0; i < num_fields; i++)
                                    {
                                        if((strcmp(row[i],tuid))==0)
                                        {
                                            flag=1;
                                            break;
                                        }
                                    }
                                }
                                mysql_free_result(result);
                            }
                        }
                        if(flag==1)
                        {
                            do
                            {
                                system("cls");
                                printf("\n DETAILS OF ISSUED BOOKS TO USER ( %s ) : ",tuid);
                                printf("\n ------------------------- \n");
                                sprintf(query,"SELECT * FROM BISRT WHERE Uid='%s'",tuid);
                                if(mysql_query(con,query))
                                {
                                    finish_with_error(con);
                                    break;
                                }
                                MYSQL_RES *result = mysql_store_result(con);
                                if (result == NULL)
                                {
                                    finish_with_error(con);
                                }
                                int num_fields = mysql_num_fields(result);
                                MYSQL_ROW row;
                                while ((row = mysql_fetch_row(result)))
                                {
                                    for(i=0; i<num_fields; i++)
                                    {
                                        bisrt[i]=row[i];
                                    }
                                }
                                char *b1,*b2,*b3,*b4,*b5;
                                mysql_free_result(result);
                                printf("\n S.NO\tBOOK NAME(ID , ISSUED DATE , DAYS COUNT)");
                                printf("\n ====\t=======================================");
                                b1=bookname(con,bisrt[1]);
                                printf("\n  1. \t %s ( %s , %s ,",b1,bisrt[1],bisrt[2]);
                                dattime=datime(con);
                                difc[0]=datedif(con,bisrt[2],dattime);
                                printf(" %s )\n",difc[0]);
                                b2=bookname(con,bisrt[3]);
                                printf("\n  2. \t %s ( %s , %s ,",b2,bisrt[3],bisrt[4]);
                                dattime=datime(con);
                                difc[1]=datedif(con,bisrt[4],dattime);
                                printf(" %s )\n",difc[0]);
                                b3=bookname(con,bisrt[5]);
                                printf("\n  3. \t %s ( %s , %s ,",b3,bisrt[5],bisrt[6]);
                                dattime=datime(con);
                                difc[2]=datedif(con,bisrt[6],dattime);
                                printf(" %s )\n",difc[0]);
                                b4=bookname(con,bisrt[7]);
                                printf("\n  4. \t %s ( %s , %s ,",b4,bisrt[7],bisrt[8]);
                                dattime=datime(con);
                                difc[3]=datedif(con,bisrt[8],dattime);
                                printf(" %s )\n",difc[0]);
                                b5=bookname(con,bisrt[9]);
                                difc[4]=datedif(con,bisrt[10],dattime);
                                printf("\n  5. \t %s ( %s , %s ,",b5,bisrt[9],bisrt[10]);
                                dattime=datime(con);
                                difc[4]=datedif(con,bisrt[10],dattime);
                                printf(" %s )\n",difc[0]);
                                //printf("\n%s\n",bookname(con,bisrt[9]));
                                printf("\n\n  PRESS '1' - ISSUE, '2' - RETURN, '0' - BACK  \n -> ");
                                scanf("%d",&opt);
                                if(opt==1)
                                {
                                    //
                                    printf("\n\n BOOK ISSUE FOR USER (%s) : \n --------------------------\n",tuid);
                                    sprintf(query,"SELECT B1,B2,B3,B4,B5 FROM LUSER WHERE Id='%s'",tuid);
                                    if (mysql_query(con,query))
                                    {
                                        flag=0;
                                        finish_with_error(con);
                                    }
                                    else
                                    {
                                        flag=1;
                                    }
                                    if(flag==1)
                                    {
                                        MYSQL_RES *result = mysql_store_result(con);
                                        if (result == NULL)
                                        {
                                            finish_with_error(con);
                                        }
                                        int num_fields = mysql_num_fields(result);
                                        MYSQL_ROW row;
                                        while ((row = mysql_fetch_row(result)))
                                        {
                                            for(i = 0; i < num_fields; i++)
                                            {
                                                // printf("%s \t",row[i]);
                                                tmp[i]=row[i];
                                            }
                                        }
                                        mysql_free_result(result);
                                        int bc1,bc2,bc3,bc4,bc5;
                                        bc1=(strcmp(tmp[0],"0"));
                                        bc2=(strcmp(tmp[1],"0"));
                                        bc3=(strcmp(tmp[2],"0"));
                                        bc4=(strcmp(tmp[3],"0"));
                                        bc5=(strcmp(tmp[4],"0"));
                                        if(bc1==0)
                                        {
                                            printf("\n ENTER 1st BOOK ID :  ");
                                            scanf("%d",&bid);
                                            dattime=datime(con);
                                            sprintf(query,"UPDATE BISRT SET B1='%d',D1='%s' WHERE Uid='%s'",bid,dattime,tuid);
                                            if(mysql_query(con,query))
                                            {
                                                finish_with_error(con);
                                            }
                                            else
                                            {
                                                sprintf(query,"UPDATE LUSER SET B1=1 WHERE Id='%s'",tuid);
                                                if(mysql_query(con,query))
                                                {
                                                    finish_with_error(con);
                                                }
                                                else
                                                {
                                                    printf("\n BOOK(%d) ISSUED SUCCESSFULLY\n",bid);
                                                    printf("\n PRESS '0' : ");
                                                    scanf("%d",&opt);
                                                }
                                            }
                                        }
                                        else if(bc2==0)
                                        {
                                            printf("\n ENTER 2ND BOOK ID :  ");
                                            scanf("%d",&bid);
                                            dattime=datime(con);
                                            sprintf(query,"UPDATE BISRT SET B2='%d',D2='%s' WHERE Uid='%s'",bid,dattime,tuid);
                                            if(mysql_query(con,query))
                                            {
                                                finish_with_error(con);
                                            }
                                            else
                                            {
                                                sprintf(query,"UPDATE LUSER SET B2=1 WHERE Id='%s'",tuid);
                                                if(mysql_query(con,query))
                                                {
                                                    finish_with_error(con);
                                                }
                                                else
                                                {
                                                    printf("\n BOOK(%d) ISSUED SUCCESSFULLY\n",bid);
                                                    printf("\n PRESS '0' : ");
                                                    scanf("%d",&opt);
                                                }
                                            }
                                        }
                                        else if(bc3==0)
                                        {
                                            printf("\n ENTER 3RD BOOK ID :  ");
                                            scanf("%d",&bid);
                                            dattime=datime(con);
                                            sprintf(query,"UPDATE BISRT SET B3='%d',D3='%s' WHERE Uid='%s'",bid,dattime,tuid);
                                            if(mysql_query(con,query))
                                            {
                                                finish_with_error(con);
                                            }
                                            else
                                            {
                                                sprintf(query,"UPDATE LUSER SET B3=1 WHERE Id='%s'",tuid);
                                                if(mysql_query(con,query))
                                                {
                                                    finish_with_error(con);
                                                }
                                                else
                                                {
                                                    printf("\n BOOK(%d) ISSUED SUCCESSFULLY\n",bid);
                                                    printf("\n PRESS '0' : ");
                                                    scanf("%d",&opt);
                                                }
                                            }
                                        }
                                        else if(bc4==0)
                                        {
                                            printf("\n ENTER 4TH BOOK ID :  ");
                                            scanf("%d",&bid);
                                            dattime=datime(con);
                                            sprintf(query,"UPDATE BISRT SET B4='%d',D4='%s' WHERE Uid='%s'",bid,dattime,tuid);
                                            if(mysql_query(con,query))
                                            {
                                                finish_with_error(con);
                                            }
                                            else
                                            {
                                                sprintf(query,"UPDATE LUSER SET B4=1 WHERE Id='%s'",tuid);
                                                if(mysql_query(con,query))
                                                {
                                                    finish_with_error(con);
                                                }
                                                else
                                                {
                                                    printf("\n BOOK(%d) ISSUED SUCCESSFULLY\n",bid);
                                                    printf("\n PRESS '0' : ");
                                                    scanf("%d",&opt);
                                                }
                                            }
                                        }
                                        else if(bc5==0)
                                        {
                                            printf("\n ENTER 5TH BOOK ID :  ");
                                            scanf("%d",&bid);
                                            dattime=datime(con);
                                            sprintf(query,"UPDATE BISRT SET B5='%d',D5='%s' WHERE Uid='%s'",bid,dattime,tuid);
                                            if(mysql_query(con,query))
                                            {
                                                finish_with_error(con);
                                            }
                                            else
                                            {
                                                sprintf(query,"UPDATE LUSER SET B5=1 WHERE Id='%s'",tuid);
                                                if(mysql_query(con,query))
                                                {
                                                    finish_with_error(con);
                                                }
                                                else
                                                {
                                                    printf("\n BOOK(%d) ISSUED SUCCESSFULLY\n",bid);
                                                    printf("\n PRESS '0' : ");
                                                    scanf("%d",&opt);
                                                }
                                            }
                                        }
                                        else
                                        {
                                            printf("\n NO MORE BOOKS TO THIS USER \n");
                                            printf("\n PRESS '0' TO CONTINUE :  ");
                                            scanf("%d",&opt);
                                        }
                                    }
                                }
                                else if(opt==2)
                                {
                                    printf("\n\n BOOK RETURN FOR USER (%s) : \n --------------------------\n",tuid);
                                    sprintf(query,"SELECT B1,B2,B3,B4,B5 FROM LUSER WHERE Id='%s'",tuid);
                                    if (mysql_query(con,query))
                                    {
                                        flag=0;
                                        finish_with_error(con);
                                    }
                                    else
                                    {
                                        flag=1;
                                    }
                                    if(flag==1)
                                    {
                                        MYSQL_RES *result = mysql_store_result(con);
                                        if (result == NULL)
                                        {
                                            finish_with_error(con);
                                        }
                                        int num_fields = mysql_num_fields(result);
                                        MYSQL_ROW row;
                                        while ((row = mysql_fetch_row(result)))
                                        {
                                            for(i = 0; i < num_fields; i++)
                                            {
                                                //printf("%s \t",row[i]);
                                                tmp[i]=row[i];
                                            }
                                        }
                                        mysql_free_result(result);
                                        int br1,br2,br3,br4,br5,sck;
                                        char rbid[10];
                                        br1=(strcmp(tmp[0],"1"));
                                        br2=(strcmp(tmp[1],"1"));
                                        br3=(strcmp(tmp[2],"1"));
                                        br4=(strcmp(tmp[3],"1"));
                                        br5=(strcmp(tmp[4],"1"));
                                        printf("\n ENTER THE S.NO OF BOOK FROM ABOVE LIST ( 1 - 5 ) :  ");
                                        scanf("%d",&opt);
                                        if(opt==1)
                                        {
                                            printf("\n ENTER THE BOOK ID :  ");
                                            scanf("%s",rbid);
                                            sck=(strcmp(bisrt[1],rbid));
                                            if(sck==0)
                                            {

                                                if(br1==0)
                                                {
                                                    sprintf(query,"UPDATE BISRT SET B1=0,D1=0 WHERE Uid='%s'",tuid);
                                                    if(mysql_query(con,query))
                                                    {
                                                        finish_with_error(con);
                                                    }
                                                    else
                                                    {
                                                        sprintf(query,"UPDATE LUSER SET B1=0 WHERE Id='%s'",tuid);
                                                        if(mysql_query(con,query))
                                                        {
                                                            finish_with_error(con);
                                                        }
                                                        else
                                                        {
                                                            printf("\n BOOK( %s ) RETURNED SUCCESSFULLY\n",rbid);
                                                            printf("\n PRESS '0' : ");
                                                            scanf("%d",&opt);
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                printf("\n INVALID BOOK ID ON TH S.NO...!\n\n PRESS '0' TO CONTINUE :  ");
                                                scanf("%d",&opt);
                                            }
                                        }
                                        else if(opt==2)
                                        {
                                            printf("\n ENTER THE BOOK ID :  ");
                                            scanf("%s",rbid);
                                            sck=(strcmp(bisrt[3],rbid));
                                            if(sck==0)
                                            {

                                                if(br2==0)
                                                {
                                                    sprintf(query,"UPDATE BISRT SET B2=0,D2=0 WHERE Uid='%s'",tuid);
                                                    if(mysql_query(con,query))
                                                    {
                                                        finish_with_error(con);
                                                    }
                                                    else
                                                    {
                                                        sprintf(query,"UPDATE LUSER SET B2=0 WHERE Id='%s'",tuid);
                                                        if(mysql_query(con,query))
                                                        {
                                                            finish_with_error(con);
                                                        }
                                                        else
                                                        {
                                                            printf("\n BOOK( %s ) RETURNED SUCCESSFULLY\n",rbid);
                                                            printf("\n PRESS '0' : ");
                                                            scanf("%d",&opt);
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                printf("\n INVALID BOOK ID ON TH S.NO...!\n\n PRESS '0' TO CONTINUE :  ");
                                                scanf("%d",&opt);
                                            }
                                        }
                                        else if(opt==3)
                                        {
                                            printf("\n ENTER THE BOOK ID :  ");
                                            scanf("%s",rbid);
                                            sck=(strcmp(bisrt[5],rbid));
                                            if(sck==0)
                                            {

                                                if(br3==0)
                                                {
                                                    sprintf(query,"UPDATE BISRT SET B3=0,D3=0 WHERE Uid='%s'",tuid);
                                                    if(mysql_query(con,query))
                                                    {
                                                        finish_with_error(con);
                                                    }
                                                    else
                                                    {
                                                        sprintf(query,"UPDATE LUSER SET B3=0 WHERE Id='%s'",tuid);
                                                        if(mysql_query(con,query))
                                                        {
                                                            finish_with_error(con);
                                                        }
                                                        else
                                                        {
                                                            printf("\n BOOK( %s ) RETURNED SUCCESSFULLY\n",rbid);
                                                            printf("\n PRESS '0' : ");
                                                            scanf("%d",&opt);
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                printf("\n INVALID BOOK ID ON TH S.NO...!\n\n PRESS '0' TO CONTINUE :  ");
                                                scanf("%d",&opt);
                                            }
                                        }
                                        else if(opt==4)
                                        {
                                            printf("\n ENTER THE BOOK ID :  ");
                                            scanf("%s",rbid);
                                            sck=(strcmp(bisrt[7],rbid));
                                            if(sck==0)
                                            {

                                                if(br4==0)
                                                {
                                                    sprintf(query,"UPDATE BISRT SET B4=0,D4=0 WHERE Uid='%s'",tuid);
                                                    if(mysql_query(con,query))
                                                    {
                                                        finish_with_error(con);
                                                    }
                                                    else
                                                    {
                                                        sprintf(query,"UPDATE LUSER SET B4=0 WHERE Id='%s'",tuid);
                                                        if(mysql_query(con,query))
                                                        {
                                                            finish_with_error(con);
                                                        }
                                                        else
                                                        {
                                                            printf("\n BOOK( %s ) RETURNED SUCCESSFULLY\n",rbid);
                                                            printf("\n PRESS '0' : ");
                                                            scanf("%d",&opt);
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                printf("\n INVALID BOOK ID ON TH S.NO...!\n\n PRESS '0' TO CONTINUE :  ");
                                                scanf("%d",&opt);
                                            }
                                        }
                                        else if(opt==5)
                                        {
                                            printf("\n ENTER THE BOOK ID :  ");
                                            scanf("%s",rbid);
                                            sck=(strcmp(bisrt[9],rbid));
                                            if(sck==0)
                                            {

                                                if(br5==0)
                                                {
                                                    sprintf(query,"UPDATE BISRT SET B5=0,D5=0 WHERE Uid='%s'",tuid);
                                                    if(mysql_query(con,query))
                                                    {
                                                        finish_with_error(con);
                                                    }
                                                    else
                                                    {
                                                        sprintf(query,"UPDATE LUSER SET B5=0 WHERE Id='%s'",tuid);
                                                        if(mysql_query(con,query))
                                                        {
                                                            finish_with_error(con);
                                                        }
                                                        else
                                                        {
                                                            printf("\n BOOK( %s ) RETURNED SUCCESSFULLY\n",rbid);
                                                            printf("\n PRESS '0' : ");
                                                            scanf("%d",&opt);
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                printf("\n INVALID BOOK ID ON TH S.NO...!\n\n PRESS '0' TO CONTINUE :  ");
                                                scanf("%d",&opt);
                                            }
                                        }
                                        else
                                        {
                                            printf("\n INVALID OPTION...\n PRESS '0' TO CONTINUE :  ");
                                            scanf("%d",&opt);
                                        }
                                    }
                                }
                                else if(opt>2)
                                {
                                    printf("\n  WRONG OPTION, TRY AGAIN...! \n");
                                }
                                else if(opt==0)
                                {
                                    opt=1;
                                }
                            }
                            while(opt!=1);

                        }

                        else
                        {
                            printf("\n THE USER DOESN'T HAVE ANY BOOK TRANSACTIONIS\n");
                            printf("\n PRESS '1' - RETRY (OR) '0' - BACK  :  ");
                            scanf("%d",&opt);
                        }
                    }
                    if(opt>1)
                    {
                        printf("\n INVALID OPTION... TRY AGAIN...!\n");
                        opt=1;
                    }
                }
                while(opt!=0);
                if(opt==0)
                {
                    opt=1;
                    break;
                }
            }
        }
        case 2:
        {
            if(opt==2)
            {
                do
                {
                    system("cls");
                    printf("\nTOOLS \ UTILITIES\n----- - ---------");
                    printf("\n   1 -> NOTIFICATIONS");
                    printf("\n   2 -> USER DETAILS");
                    printf("\n   3 -> BOOK DETAILS");
                    printf("\n   4 -> REPORT");
                    printf("\n   5 -> BACKUP & RESTORE");
                    printf("\n   0 -> BACK \n");
                    printf("\n -> ");
                    scanf("%d",&opt);

                    switch (opt)
                    {
                    case 0:
                    {
                        goto adminpoint;
                        //opt==0;
                        // break;
                    }
                    case 1:
                    {
                        char words[20],note[300];
                        int i;
                        char *dateetime;
                        do
                        {
                            if(mysql_query(con,"CREATE TABLE IF NOT EXISTS NOTIFY(SNO INT NOT NULL PRIMARY KEY,Ndt DATETIME NOT NULL,Note TEXT,Aid int)"))
                            {
                                finish_with_error(con);
                            }
                            else
                            {
                                dateetime=datime(con);
                                sprintf(query,"INSERT INTO NOTIFY VALUES(1,'%s','SAMPLE TEXTS','%d')",dateetime,id);
                                if(mysql_query(con,query))
                                {
                                    finish_with_error(con);
                                }
                            }
                            system("cls");
                            printf("\nNOTIFICATIONS\n=============");
                            printf("\n\nCURRENT NOTIFICATION : \n------- ------------");
                            if (mysql_query(con, "SELECT * FROM NOTIFY"))
                            {
                                finish_with_error(con);
                            }
                            MYSQL_RES *result = mysql_store_result(con);
                            if (result == NULL)
                            {
                                finish_with_error(con);
                            }
                            int num_fields = mysql_num_fields(result);
                            MYSQL_ROW row;
                            while ((row = mysql_fetch_row(result)))
                            {
                                for(i = 0; i < num_fields; i++)
                                {
                                    tmp[i]=(row[i] ? row[i] : "NULL");
                                }
                            }
                            mysql_free_result(result);
                            printf("\n\n  PUBLISHER ID\t\t:\t%s",tmp[3]);
                            printf("\n  DATE & TIME\t\t:\t%s",tmp[1]);
                            printf("\n  PUBLISHED TEXT\t:\t%s",tmp[2]);
                            printf("\n\nPRESS '1' - EDIT (OR) '0' - BACK : ");
                            scanf("%d",&opt);
                            if(opt==1)
                            {
                                printf("\n\n TYPE THE NOTIFICATION WITHIN 200 WORDS : \n --------------------------------------");
                                printf("\n TYPE .* FOR END\n ---------------\n->");
                                do
                                {
                                    scanf("%s",words);
                                    strcat(note," ");
                                    strcat(note,words);
                                }
                                while((strcmp(words,".*"))!=0);
                                printf("\nNOTIFICATION TO PUBLISH :\n-----------------------\n\n%s\n",note);
                                printf("\nPRESS '1' - PUBLISH (OR) '0' - CANCEL : ");
                                scanf("%d",&opt);
                                dateetime=datime(con);
                                if(opt==1)
                                {
                                    sprintf(query,"UPDATE NOTIFY SET Ndt='%s',Note='%s',Aid='%d' WHERE SNO=1",dateetime,note,id);
                                    if(mysql_query(con,query))
                                    {
                                        finish_with_error(con);
                                    }
                                    else
                                    {
                                        printf("NOTIFICATION PUBLISHED SUCCESSFULLY...!");
                                    }
                                    printf("\nPRESS '1' TO CONTINUE : ");
                                    scanf("%d",&opt);
                                }
                                if(opt==0)
                                {
                                    opt=1;
                                }
                            }
                            if(opt==0)
                            {
                                opt=1;
                                break;
                            }
                            if(opt>1)
                            {
                                printf("\nINVALID OPTION\n");
                                opt=1;
                            }
                        }
                        while(opt!=0);
                    }
                    case 2:
                    {
                        if(opt==2)
                            do
                            {
                                int flag;
                                system("cls");
                                printf("\nUSER DETAILS\n---- -------\n");
                                printf("\n   1 -> ADD / DELETE (ADMINISTRATORS)");
                                printf("\n   2 -> ADD / DELETE (STANDARD USERS)");
                                printf("\n\n PRESS '0' FOR BACK\n");
                                printf("\n -> ");
                                scanf("%d",&opt);
                                if(opt==1)
                                {
                                    printf("\nLIST OF ADMINISTRATORS\n---- -- --------------\n");
                                    if (mysql_query(con, "SELECT * FROM AUSER"))
                                    {
                                        finish_with_error(con);
                                    }
                                    MYSQL_RES *result = mysql_store_result(con);
                                    if (result == NULL)
                                    {
                                        finish_with_error(con);
                                    }
                                    int num_fields = mysql_num_fields(result);
                                    MYSQL_ROW row;
                                    printf("\nID\t\tNAME\t\tDESIGNATION\tPASSWORD\tFORGOT KEY\tMOBILE");
                                    printf("\n--\t\t----\t\t-----------\t--------\t----------\t------\n");
                                    while ((row = mysql_fetch_row(result)))
                                    {
                                        for(i = 0; i < num_fields; i++)
                                        {
                                            printf("%s\t\t", row[i] ? row[i] : "NULL");
                                        }
                                        printf("\n");
                                    }
                                    printf("\n-------------------------------------------------------------------------------------------\n");
                                    mysql_free_result(result);
                                    printf("\n  1 -> ADD\t 2 -> DELETE\t 0 -> BACK\n\n -> ");
                                    scanf("%d",&opt);
                                    if(opt==1)
                                    {
                                        printf("\n* PLEASE ENTER VALUES WITHOUT SPACE.\n");
                                        printf("\n FULL NAME\t:  ");
                                        scanf("%s",name);
                                        printf("\n DESIGNATION\t:  ");
                                        scanf("%s",dsig);
                                        printf("\n PASSWORD\t:  ");
                                        scanf("%s",pwd);
                                        printf("\n FORGET KEY\t:  ");
                                        scanf("%s",fk);
                                        printf("\n MOBILE NUMBER\t:  ");
                                        scanf("%s",mno);
                                        printf("\n PRESS '0'-CANCEL '1'-CONTINUE : ");
                                        scanf("%d",&opt);
                                        sprintf(query,"INSERT INTO AUSER(Name,Dsig,Pwd,Fk,Mno) VALUES('%s','%s','%s','%s','%s')",name,dsig,pwd,fk,mno);
                                        if(mysql_query(con,query))
                                        {
                                            finish_with_error(con);
                                        }
                                        flag=1;
                                    }
                                    if(opt==2)
                                    {
                                        printf("\n ENTER THE USER ID TO DELETE ACCOUNT : ");
                                        scanf("%d",&i);
                                        printf("\n");
                                        sprintf(query,"DELETE FROM AUSER WHERE ID='%d'",i);
                                        if(mysql_query(con,query))
                                        {
                                            finish_with_error(con);
                                        }
                                        flag=2;
                                    }
                                    if(opt==0)
                                    {
                                        opt=1;
                                        break;
                                    }
                                    if(opt>2)
                                    {
                                        printf("\n INVALID CHOICE... TRY AGAIN...");
                                        opt=1;
                                        break;
                                    }
                                    if(flag==1)
                                    {
                                        sprintf(query,"SELECT * FROM AUSER");
                                        if (mysql_query(con,query))
                                        {
                                            finish_with_error(con);
                                        }
                                        MYSQL_RES *result = mysql_store_result(con);
                                        if (result == NULL)
                                        {
                                            finish_with_error(con);
                                        }
                                        MYSQL_ROW row;
                                        while ((row = mysql_fetch_row(result)))
                                        {
                                            for(i = 0; i < 1; i++)
                                            {
                                                tmp[0]=row[i];
                                            }
                                        }
                                        mysql_free_result(result);
                                        printf("\n ACCOUNT CREATED SUCCESSFULLY !\n");
                                        printf("\n  NEW ADMIN ID\t:  %s",tmp[0]);
                                        printf("\n  NEW ADMIN PASSWORD\t:  %s\n",pwd);
                                        printf("\n  PRESS '0' - BACK \n -> ");
                                        scanf("%d",&opt);
                                    }
                                    else if(flag==2)
                                    {
                                        printf("\n THE ACCOUNT DELETED SUCCESSFULLY\n");
                                        printf("\n PRESS '0' - BACK \n -> ");
                                        scanf("%d",&opt);
                                    }
                                    else
                                    {
                                        printf("\n SOMETHING WENT WRONG !... PLEASE TRY AGAIN LATER.\n");
                                    }
                                }
                                else if(opt==2)
                                {
                                    printf("\n ENTER THE USER ID TO DELETE ACCOUNT : ");
                                    scanf("%d",&i);
                                    printf("\n");
                                    sprintf(query,"DELETE FROM LUSER WHERE ID='%d'",i);
                                    if(mysql_query(con,query))
                                    {
                                        printf("\n SOMETHING WENT WRONG !... PLEASE TRY AGAIN LATER.\n");
                                        finish_with_error(con);
                                        break;
                                    }
                                    printf("\n THE ACCOUNT (ID %d) DELETED SUCCESSFULLY\n",i);
                                    printf("\n PRESS '0' - BACK \n -> ");
                                    scanf("%d",&opt);
                                }
                                else if(opt==0)
                                {
                                    opt=1;
                                    break;
                                }
                                else
                                {
                                    printf("\nINVALID CHOICE... TRY AGAIN...");
                                    opt=1;
                                    break;
                                }

                            }
                            while(opt!=0);
                    }
                    case 3:
                    {
                        if(opt==3)
                        {
                            do
                            {
                                mysql_query(con,"'\'x");
                                system("cls");
                                printf("\n BOOK DETAILS\n ============\n");
                                printf("\n   1 -> BOOK SEARCH");
                                printf("\n   2 -> ADD BOOK DETAILS");
                                printf("\n   2 -> EDIT BOOK DETAILS");
                                printf("\n   3 -> DELETE BOOK DETAILS");
                                printf("\n   0 -> BACK");
                                printf("\n  -> ");
                                scanf("%d",&opt);
                                printf("\n------------------------------");
                                if(opt==1)
                                {
                                    do
                                    {

                                        system("cls");
                                        printf("\n BOOK SEARCH\n ===========\n");
                                        printf("\n   1 -> SEARCH BY BOOK ID");
                                        printf("\n   2 -> SEARCH BY BOOK NAME / AUTHOR");
                                        printf("\n   0 -> BACK\n\n  -> ");
                                        scanf("%d",&opt);
                                        if(opt==0)
                                        {
                                            opt=1;
                                            break;
                                        }
                                        else
                                        {
                                            if(opt==1)
                                            {
                                                int flag=0;
                                                char sbid[10];
                                                printf("\n\nENTER THE BOOK ID TO SEARCH : ");
                                                scanf("%s",sbid);
                                                sprintf(query,"SELECT * FROM BOOKS WHERE Bid='%s'",sbid);
                                                if (mysql_query(con,query))
                                                {
                                                    finish_with_error(con);
                                                }
                                                MYSQL_RES *result = mysql_store_result(con);
                                                if (result == NULL)
                                                {
                                                    finish_with_error(con);
                                                }
                                                int num_fields = mysql_num_fields(result);
                                                MYSQL_ROW row;
                                                while ((row = mysql_fetch_row(result)))
                                                {
                                                    for(i = 0; i < num_fields; i++)
                                                    {
                                                        tmp[i]=row[i];
                                                        if((strcmp(sbid,row[0]))==0)
                                                        {
                                                            flag=1;
                                                        }
                                                        else
                                                        {
                                                            flag=0;
                                                        }
                                                    }
                                                    //printf("\n");
                                                }
                                                mysql_free_result(result);
                                                if(flag==1)
                                                {
                                                    printf("\n\n  BOOK ID\t\t: %s",tmp[0]);
                                                    printf("\n  BOOK NAME\t\t: %s",tmp[1]);
                                                    printf("\n  BOOK AUTHOR\t\t: %s",tmp[2]);
                                                    printf("\n  LOCATION OF BOOK\t: %s",tmp[4]);
                                                }
                                                else
                                                {
                                                    printf("\nTHE BOOK-ID DOESN'T MATCHES ANY BOOK...!");
                                                }
                                                printf("\n\n  PRESS '0' - BACK \n -> ");
                                                scanf("%d",&opt);
                                            }
                                            if(opt==2)
                                            {
                                                printf("\n\nENTER THE BOOK NAME / AUTHOR TO SEARCH : ");
                                                scanf("%s",ikey);
                                                skey=strupr(ikey);
                                                sprintf(query,"SELECT * FROM BOOKS WHERE MATCH (Bname,Bauthor) AGAINST('%s' IN NATURAL LANGUAGE MODE)",skey);
                                                if (mysql_query(con,query))
                                                {
                                                    finish_with_error(con);
                                                }
                                                MYSQL_RES *result = mysql_store_result(con);
                                                if (result == NULL)
                                                {
                                                    finish_with_error(con);
                                                }
                                                int num_fields = mysql_num_fields(result);
                                                MYSQL_ROW row;
                                                printf("\n SEARCH RESULTS : ");
                                                printf("\n ================\n");
                                                printf("\n   BOOK-ID\tBOOK-NAME( AUTHOR , LOCATION )");
                                                printf("\n   ------------------------------------------------\n");
                                                while ((row = mysql_fetch_row(result)))
                                                {
                                                    for(i = 0; i < num_fields; i++)
                                                    {
                                                        tmp[i]=row[i];
                                                    }
                                                    printf("\n   %s\t%s ( %s , %s )",tmp[0],tmp[1],tmp[2],tmp[4]);
                                                }
                                                mysql_free_result(result);
                                                printf("\n\n   PRESS '0' - BACK \n\n -> ");
                                                scanf("%d",&opt);
                                            }
                                            if(opt>2)
                                            {
                                                printf("\n WRONG OPTION, TRY AGAIN");
                                            }
                                        }
                                    }
                                    while(opt!=1);
                                }
                                if(opt==2)
                                {
                                    printf("\n\nTHIS MENU IS USED FOR ADDING NEW BOOKS ONLY");
                                    printf("\n\nNOTE : USE HYPHEN ( - ) SYMBOL FOR SPACES");
                                    printf("\n\n ENTER BOOK NAME\t: ");
                                    scanf("%s",bkname);
                                    bname=strupr(bkname);
                                    printf("\n\n AUTHOR OF THE BOOK\t: ");
                                    scanf("%s",bkauthor);
                                    bauthor=strupr(bkauthor);
                                    printf("\n\n NUMBER OF COPIES\t: ");
                                    scanf("%d",&tc);
                                    printf("\n\n LOCATION OF BOOK\t: ");
                                    scanf("%s",bkrack);
                                    rack=strupr(bkrack);
                                    dattime=datime(con);
                                    printf("\n\nPRESS '0' - CONTINUE (OR) '1' - CANCEL : ");
                                    scanf("%d",&opt);
                                    printf("\n------------------------------");
                                    if(opt==0)
                                    {
                                        sprintf(query,"INSERT INTO BOOKS(Bname,Bauthor,Tcop,Rack,Dtm) VALUES('%s','%s','%d','%s','%s')",bname,bauthor,tc,rack,dattime);
                                        if(mysql_query(con,query))
                                        {
                                            finish_with_error(con);
                                        }
                                        else
                                        {
                                            sprintf(query,"SELECT Bid FROM BOOKS WHERE Dtm='%s'",dattime);
                                            if (mysql_query(con,query))
                                            {
                                                finish_with_error(con);
                                            }
                                            MYSQL_RES *result = mysql_store_result(con);
                                            if (result == NULL)
                                            {
                                                finish_with_error(con);
                                            }
                                            int num_fields = mysql_num_fields(result);
                                            MYSQL_ROW row;
                                            while ((row = mysql_fetch_row(result)))
                                            {
                                                for(i = 0; i < num_fields; i++)
                                                {
                                                    bid=row[i];
                                                }
                                            }
                                            mysql_free_result(result);
                                            printf("\n NEW BOOK ADDED SUCCESSFULLY !\n");
                                            printf("\n  NEW BOOK ID\t:  %s",bid);
                                            printf("\n  PLEASE NOtE THE BOOK ID FOR LATER USE\n");
                                            printf("\n  PRESS '1' - BACK \n -> ");
                                            scanf("%d",&opt);
                                        }

                                    }
                                }
                                if(opt==3)
                                {
                                    mysql_query(con,"'\'x");
                                    int etc,eac;
                                    printf("\n\nENTER THE BOOK ID TO EDIT : ");
                                    scanf("%d",&bid);
                                    sprintf(query,"SELECT * FROM BOOKS WHERE Bid='%d'",bid);
                                    if (mysql_query(con,query))
                                    {
                                        finish_with_error(con);
                                    }
                                    MYSQL_RES *result = mysql_store_result(con);
                                    if (result == NULL)
                                    {
                                        finish_with_error(con);
                                    }
                                    int num_fields = mysql_num_fields(result);
                                    MYSQL_ROW row;
                                    while ((row = mysql_fetch_row(result)))
                                    {
                                        for(i = 0; i < num_fields; i++)
                                        {
                                            tmp[i]=row[i];
                                            etc=row[3];
                                            eac=row[4];
                                        }
                                    }
                                    mysql_free_result(result);
                                    printf("\n\n  BOOK ID\t\t: %s",tmp[0]);
                                    printf("\n  BOOK NAME\t\t: %s",tmp[1]);
                                    printf("\n  BOOK AUTHOR\t\t: %s",tmp[2]);
                                    printf("\n  TOTAL COPIES\t\t: %s",tmp[3]);
                                    printf("\n  LOCATION OF BOOK\t: %s",tmp[4]);
                                    printf("\n  ADDED DATE & TIME\t: %s",tmp[5]);
                                    printf("\n\n  PRESS '0' - EDIT (OR) 1' - BACK \n -> ");
                                    scanf("%d",&opt);
                                    printf("\n------------------------------");
                                    if(opt==0)
                                    {
                                        printf("\n\nNOTE : USE HYPHEN ( - ) SYMBOL FOR SPACES");
                                        printf("\n\nEDIT BOOK ON ID : %d",bid);
                                        printf("\n\n ENTER BOOK NAME\t: ");
                                        scanf("%s",bkname);
                                        bname=strupr(bkname);
                                        printf("\n\n AUTHOR OF THE BOOK\t: ");
                                        scanf("%s",bkauthor);
                                        bauthor=strupr(bkauthor);
                                        printf("\n\n NUMBER OF COPIES\t: ");
                                        scanf("%d",&tc);
                                        printf("\n\n LOCATION OF BOOK\t: ");
                                        scanf("%s",bkrack);
                                        rack=strupr(bkrack);
                                        dattime=datime(con);
                                        printf("\n\nPRESS '0' - CONTINUE (OR) '1' - CANCEL : ");
                                        scanf("%d",&opt);
                                        printf("\n------------------------------");
                                        if(opt==0)
                                        {
                                            sprintf(query,"UPDATE BOOKS SET Bname='%s',Bauthor='%s',Tcop='%d',Rack='%s',Dtm='%s' WHERE Bid='%d'",bname,bauthor,tc,rack,dattime,bid);
                                            if(mysql_query(con,query))
                                            {
                                                finish_with_error(con);
                                            }
                                            else
                                            {
                                                printf("\n BOOK DETAILS EDITED SUCCESSFULLY...!");
                                                printf("\n  PRESS '1' - BACK \n -> ");
                                                scanf("%d",&opt);
                                            }
                                        }

                                    }
                                }
                                if(opt==4)
                                {
                                    printf("\n\n THIS MENU IS FOR DELETING A BOOK.");
                                    printf("\n\n ENTER THE BOOK ID TO DELETE : ");
                                    scanf("%d",&bid);
                                    printf("\n\nPRESS '0' - CONTINUE (OR) '1' - CANCEL : ");
                                    scanf("%d",&opt);
                                    printf("\n------------------------------");
                                    if(opt==0)
                                    {
                                        sprintf(query,"DELETE FROM BOOKS WHERE Bid='%d'",bid);
                                        if(mysql_query(con,query))
                                        {
                                            finish_with_error(con);
                                        }
                                        else
                                        {
                                            printf("\n BOOK DELETED SUCCESSFULLY...!");
                                            printf("\n\n  PRESS '1' - BACK \n -> ");
                                            scanf("%d",&opt);
                                        }
                                    }
                                }
                                if(opt>4)
                                {
                                    printf("\n\n INVALID OPTION, TRY AGAIN... !");
                                }
                            }
                            while(opt!=0);
                        }
                    }
                    case 4:
                    {
                        if(opt==4)
                        {
                            opt=report(con);
                        }
                    }
                    case 5:
                    {
                        backup_restore(con);
                    }
                    default :
                    {
                        printf("\nINVALID CHOICE... TRY AGAIN...");
                        opt=1;
                        break;
                    }
                    }
                }
                while(opt!=0);
            }
        }
        case 3:
        {
            if(opt==3)
            {
                do
                {
                    system("cls");
                    printf("\nADMINISTRATOR PROFILE SETTINGS\n------------- ------- --------\n");
                    sprintf(query,"SELECT * FROM AUSER where Id='%d'",id);
                    if (mysql_query(con,query))
                    {
                        finish_with_error(con);
                    }
                    MYSQL_RES *result = mysql_store_result(con);
                    if (result == NULL)
                    {
                        finish_with_error(con);
                    }
                    int num_fields = mysql_num_fields(result);
                    MYSQL_ROW row;
                    while ((row = mysql_fetch_row(result)))
                    {
                        for(i = 0; i < num_fields; i++)
                        {
                            tmp[i]=row[i];
                            //printf("%s ", row[i]);
                        }
                        //printf("\n");
                    }
                    mysql_free_result(result);
                    printf("\nUSER ID\t\t:\t%s\n\nNAME\t\t:\t%s\n\nDESIGNATION\t:\t%s\n\nPASSWORD\t:\t%s\n\nFORGET KEY\t:\t%s\n\nMOBILE NO\t:\t%s\n",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]);
                    printf("\nPRESS '1' - EDIT PROFILE (OR) '0' - BACK : ");
                    scanf("%d",&opt);
                    if(opt==1)
                    {
                        printf("\n* PLEASE ENTER VALUES WITHOUT SPACE.\n");
                        printf("\nFULL NAME\t:  ");
                        scanf("%s",name);
                        printf("\nDESIGNATION\t:  ");
                        scanf("%s",dsig);
                        printf("\nPASSWORD\t:  ");
                        scanf("%s",pwd);
                        printf("\nFORGET KEY\t:  ");
                        scanf("%s",fk);
                        printf("\nMOBILE NUMBER\t:  ");
                        scanf("%s",mno);
                        printf("\nPRESS '1'-CONTINUE (OR) '0'-CANCEL : ");
                        scanf("%d",&opt);
                        if(opt==1)
                        {
                            sprintf(query,"UPDATE AUSER SET Name='%s',Dsig='%s',Pwd='%s',Fk='%s',Mno='%s' WHERE Id='%d'",name,dsig,pwd,fk,mno,id);
                            if(mysql_query(con,query))
                            {
                                finish_with_error(con);
                            }
                            printf("\nPROFILE EDITED SUCCESSFULLY !\n");
                            printf("\nPRESS '1' TO CONTINUE : ");
                            scanf("%d",&opt);
                        }
                        if(opt==0)
                        {
                            opt=1;
                            break;
                        }
                    }
                    if(opt==0)
                    {
                        opt=1;
                        break;
                    }
                    if(opt>1)
                    {
                        printf("\nINVALID OPTION... TRY AGAIN...");
                        opt=1;
                    }
                }
                while(opt!=1);
            }
        }
        default :
        {
            printf("\n  PLEASE ENTER CORRECT OPTION\n");
        }
        }
    }
    while(opt!=0);
}
int user(MYSQL *con,int id)
{
    int opt,i;
    char name[20],dsig[20],pwd[10],fk[10],mno[15],ikey[30],*skey;
    char query[1024],*tmp[6];
    do
    {
        system("cls");
        printf("\nLOGGED IN AS : %d(USER)\n",id);
        printf("\n   1 -> NOTIFICATIONS");
        printf("\n   2 -> BOOK SEARCH");
        printf("\n   3 -> BOOK HISTORY");
        printf("\n   4 -> PROFILE SETTINGS");
        printf("\n\n PRESS '0' FOR LOGOUT\n");
        printf("\n -> ");
        scanf("%d",&opt);
        switch(opt)
        {
        case 0:
        {
            printf("\n LOGGED OUT SUCCESSFULLY !...\n");
            break;
        }
        case 1:
        {
            do
            {
                system("cls");
                printf("\nNOTIFICATIONS\n=============");
                if (mysql_query(con, "SELECT * FROM NOTIFY"))
                {
                    finish_with_error(con);
                }
                MYSQL_RES *result = mysql_store_result(con);
                if (result == NULL)
                {
                    finish_with_error(con);
                }
                int num_fields = mysql_num_fields(result);
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(result)))
                {
                    for(i = 0; i < num_fields; i++)
                    {
                        tmp[i]=(row[i] ? row[i] : "NULL");
                    }
                }
                mysql_free_result(result);
                printf("\n\n\n DATE & TIME : %s",tmp[1]);
                printf("\t\tPUBLISHER ID : %s",tmp[3]);
                printf("\n ------------------------------------------------------------------");
                printf("\n\n\n  \t%s",tmp[2]);
                printf("\n\n\n ------------------------------------------------------------------");
                printf("\n\n\n PRESS '0' - BACK : ");
                scanf("%d",&opt);
                if(opt==0)
                {
                    opt=1;
                    break;
                }
                if(opt>0)
                {
                    printf("\nINVALID OPTION\n");
                    opt=1;
                }
            }
            while(opt!=1);
        }
        case 2:
        {
            if(opt==2)
            {
                do
                {

                    system("cls");
                    printf("\n BOOK SEARCH\n ===========\n");
                    printf("\n   1 -> SEARCH BY BOOK ID");
                    printf("\n   2 -> SEARCH BY BOOK NAME / AUTHOR");
                    printf("\n   0 -> BACK\n\n  -> ");
                    scanf("%d",&opt);
                    if(opt==0)
                    {
                        opt=1;
                        break;
                    }
                    else
                    {
                        if(opt==1)
                        {
                            int flag=0;
                            char sbid[10];
                            printf("\n\nENTER THE BOOK ID TO SEARCH : ");
                            scanf("%s",sbid);
                            sprintf(query,"SELECT * FROM BOOKS WHERE Bid='%s'",sbid);
                            if (mysql_query(con,query))
                            {
                                finish_with_error(con);
                            }
                            MYSQL_RES *result = mysql_store_result(con);
                            if (result == NULL)
                            {
                                finish_with_error(con);
                            }
                            int num_fields = mysql_num_fields(result);
                            MYSQL_ROW row;
                            while ((row = mysql_fetch_row(result)))
                            {
                                for(i = 0; i < num_fields; i++)
                                {
                                    tmp[i]=row[i];
                                    if((strcmp(sbid,row[0]))==0)
                                    {
                                        flag=1;
                                    }
                                    else
                                    {
                                        flag=0;
                                    }
                                }
                                //printf("\n");
                            }
                            mysql_free_result(result);
                            if(flag==1)
                            {
                                printf("\n\n  BOOK ID\t\t: %s",tmp[0]);
                                printf("\n  BOOK NAME\t\t: %s",tmp[1]);
                                printf("\n  BOOK AUTHOR\t\t: %s",tmp[2]);
                                printf("\n  LOCATION OF BOOK\t: %s",tmp[4]);
                            }
                            else
                            {
                                printf("\nTHE BOOK-ID DOESN'T MATCHES ANY BOOK...!");
                            }
                            printf("\n\n  PRESS '0' - BACK \n -> ");
                            scanf("%d",&opt);
                        }
                        if(opt==2)
                        {
                            printf("\n\nENTER THE BOOK NAME / AUTHOR TO SEARCH : ");
                            scanf("%s",ikey);
                            skey=strupr(ikey);
                            sprintf(query,"SELECT * FROM BOOKS WHERE MATCH (Bname,Bauthor) AGAINST('%s' IN NATURAL LANGUAGE MODE)",skey);
                            if (mysql_query(con,query))
                            {
                                finish_with_error(con);
                            }
                            MYSQL_RES *result = mysql_store_result(con);
                            if (result == NULL)
                            {
                                finish_with_error(con);
                            }
                            int num_fields = mysql_num_fields(result);
                            MYSQL_ROW row;
                            printf("\n SEARCH RESULTS : ");
                            printf("\n ================\n");
                            printf("\n   BOOK-ID\tBOOK-NAME( AUTHOR , LOCATION )");
                            printf("\n   ------------------------------------------------\n");
                            while ((row = mysql_fetch_row(result)))
                            {
                                for(i = 0; i < num_fields; i++)
                                {
                                    tmp[i]=row[i];
                                }
                                printf("\n   %s\t%s ( %s , %s )",tmp[0],tmp[1],tmp[2],tmp[4]);
                            }
                            mysql_free_result(result);
                            printf("\n\n   PRESS '0' - BACK \n\n -> ");
                            scanf("%d",&opt);
                        }
                        if(opt>2)
                        {
                            printf("\n WRONG OPTION, TRY AGAIN");
                        }
                    }
                }
                while(opt!=1);
                //booksearch
            }
        }
        case 3:
        {
            if(opt==3)
            {
                //Book history
                char *bir[11],*difc[6],*dattime;
                sprintf(query,"SELECT * FROM BISRT WHERE Uid='%d'",id);
                if(mysql_query(con,query))
                {
                    finish_with_error(con);
                }
                else
                {
                    MYSQL_RES *result = mysql_store_result(con);
                    if (result == NULL)
                    {
                        finish_with_error(con);
                    }
                    else
                    {
                        int num_fields = mysql_num_fields(result);
                        MYSQL_ROW row;
                        while ((row = mysql_fetch_row(result)))
                        {
                            for(i = 0; i < num_fields; i++)
                            {
                                bir[i]=row[i];
                            }
                        }
                        printf("\n BOOK HISTORY : ");
                        printf("\n -------------- \n");
                        char *b1,*b2,*b3,*b4,*b5;
                        mysql_free_result(result);
                        printf("\n S.NO\tBOOK NAME(ID , ISSUED DATE , DAYS COUNT)");
                        printf("\n ====\t=======================================");
                        b1=bookname(con,bir[1]);
                        printf("\n  1. \t %s ( %s , %s ,",b1,bir[1],bir[2]);
                        dattime=datime(con);
                        difc[0]=datedif(con,bir[2],dattime);
                        printf(" %s )\n",difc[0]);
                        b2=bookname(con,bir[3]);
                        printf("\n  2. \t %s ( %s , %s ,",b2,bir[3],bir[4]);
                        dattime=datime(con);
                        difc[1]=datedif(con,bir[4],dattime);
                        printf(" %s )\n",difc[1]);
                        b3=bookname(con,bir[5]);
                        printf("\n  3. \t %s ( %s , %s ,",b3,bir[5],bir[6]);
                        dattime=datime(con);
                        difc[2]=datedif(con,bir[6],dattime);
                        printf(" %s )\n",difc[2]);
                        b4=bookname(con,bir[7]);
                        printf("\n  4. \t %s ( %s , %s ,",b4,bir[7],bir[8]);
                        dattime=datime(con);
                        difc[3]=datedif(con,bir[8],dattime);
                        printf(" %s )\n",difc[3]);
                        b5=bookname(con,bir[9]);
                        difc[4]=datedif(con,bir[10],dattime);
                        printf("\n  5. \t %s ( %s , %s ,",b5,bir[9],bir[10]);
                        dattime=datime(con);
                        difc[4]=datedif(con,bir[10],dattime);
                        printf(" %s )\n",difc[4]);
                        printf("\n\n  PRESS '1' - BACK  \n -> ");
                        scanf("%d",&opt);
                    }
                }
            }
        }
        case 4:
        {
            if(opt==4)
                do
                {
                    system("cls");
                    printf("\nUSER PROFILE SETTINGS\n---- ------- --------\n");
                    sprintf(query,"SELECT Id,Name,Dsig,Pwd,Fk,Mno FROM LUSER where Id='%d'",id);
                    if (mysql_query(con,query))
                    {
                        finish_with_error(con);
                    }
                    MYSQL_RES *result = mysql_store_result(con);
                    if (result == NULL)
                    {
                        finish_with_error(con);
                    }
                    int num_fields = mysql_num_fields(result);
                    MYSQL_ROW row;
                    while ((row = mysql_fetch_row(result)))
                    {
                        for(i = 0; i < num_fields; i++)
                        {
                            tmp[i]=row[i];
                        }
                    }
                    mysql_free_result(result);
                    printf("\nUSER ID\t\t:\t%s\n\nNAME\t\t:\t%s\n\nDESIGNATION\t:\t%s\n\nPASSWORD\t:\t%s\n\nFORGET KEY\t:\t%s\n\nMOBILE NO\t:\t%s\n",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]);
                    printf("\nPRESS '1' - EDIT PROFILE (OR) '0' - BACK : ");
                    scanf("%d",&opt);
                    if(opt==1)
                    {
                        printf("\n* PLEASE ENTER VALUES WITHOUT SPACE.\n");
                        printf("\nFULL NAME\t:  ");
                        scanf("%s",name);
                        printf("\n1-STUDENT 2-TEACHER 3-OTHERS\n\nDESIGNATION\t:  ");
                        scanf("%d",&opt);
                        if(opt==1)
                            strcpy(dsig,"STUDENT");
                        if(opt==2)
                            strcpy(dsig,"TEACHER");
                        if(opt==3)
                            strcpy(dsig,"OTHER");
                        printf("\nPASSWORD\t:  ");
                        scanf("%s",pwd);
                        printf("\nFORGET KEY\t:  ");
                        scanf("%s",fk);
                        printf("\nMOBILE NUMBER\t:  ");
                        scanf("%s",mno);
                        printf("\nPRESS '1'-CONTINUE (OR) '0'-CANCEL : ");
                        scanf("%d",&opt);
                        if(opt==1)
                        {
                            sprintf(query,"UPDATE LUSER SET Name='%s',Dsig='%s',Pwd='%s',Fk='%s',Mno='%s' WHERE Id='%d'",name,dsig,pwd,fk,mno,id);
                            if(mysql_query(con,query))
                            {
                                finish_with_error(con);
                            }
                            printf("\nPROFILE EDITED SUCCESSFULLY !\n");
                            printf("\nPRESS '1' TO CONTINUE : ");
                            scanf("%d",&opt);
                        }
                        if(opt==0)
                        {
                            opt=1;
                            break;
                        }
                    }
                    if(opt==0)
                    {
                        opt=1;
                        break;
                    }
                    if(opt>1)
                    {
                        printf("\nINVALID OPTION... TRY AGAIN...");
                        opt=1;
                    }
                }
                while(opt!=1);
        }
        default :
        {
            printf("\n  PLEASE ENTER CORRECT OPTION\n");
        }
        }
    }
    while(opt!=0);
}
int normaluser(MYSQL *con)
{
    int opt,i;
    char ikey[30],*skey,*tmp[6];
    char query[1024];
    system("cls");
    printf("\n NORMAL USER\n ===========\n");
    printf("\n   1 -> NOTIFICATIONS");
    printf("\n   2 -> BOOK SEARCH");
    printf("\n   0 -> BACK");
    printf("\n\n -> ");
    scanf("%d",&opt);
    if(opt==0)
    {
        start_scn(con);
    }
    if(opt==1)
    {
        do
        {
            system("cls");
            printf("\nNOTIFICATIONS\n=============");
            if (mysql_query(con, "SELECT * FROM NOTIFY"))
            {
                finish_with_error(con);
            }
            MYSQL_RES *result = mysql_store_result(con);
            if (result == NULL)
            {
                finish_with_error(con);
            }
            int num_fields = mysql_num_fields(result);
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result)))
            {
                for(i = 0; i < num_fields; i++)
                {
                    tmp[i]=(row[i] ? row[i] : "NULL");
                }
            }
            mysql_free_result(result);
            printf("\n\n\n DATE & TIME : %s",tmp[1]);
            printf("\t\tPUBLISHER ID : %s",tmp[3]);
            printf("\n ------------------------------------------------------------------");
            printf("\n\n\n  \t%s",tmp[2]);
            printf("\n\n\n ------------------------------------------------------------------");
            printf("\n\n\n PRESS '0' - BACK : ");
            scanf("%d",&opt);
            if(opt==0)
            {
                opt=1;
                normaluser(con);
            }
            if(opt>0)
            {
                printf("\nINVALID OPTION\n");
                opt=1;
            }
        }
        while(opt!=1);
        //notifications
    }
    if(opt==2)
    {
        do
        {

            system("cls");
            printf("\n BOOK SEARCH\n ===========\n");
            printf("\n   1 -> SEARCH BY BOOK ID");
            printf("\n   2 -> SEARCH BY BOOK NAME / AUTHOR");
            printf("\n   0 -> BACK\n\n  -> ");
            scanf("%d",&opt);
            if(opt==0)
            {
                opt=1;
                normaluser(con);
                break;
            }
            if(opt==1)
            {
                int flag=0;
                char sbid[10];
                printf("\n\nENTER THE BOOK ID TO SEARCH : ");
                scanf("%s",sbid);
                sprintf(query,"SELECT * FROM BOOKS WHERE Bid='%s'",sbid);
                if (mysql_query(con,query))
                {
                    finish_with_error(con);
                }
                MYSQL_RES *result = mysql_store_result(con);
                if (result == NULL)
                {
                    finish_with_error(con);
                }
                int num_fields = mysql_num_fields(result);
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(result)))
                {
                    for(i = 0; i < num_fields; i++)
                    {
                        tmp[i]=row[i];
                        if((strcmp(sbid,row[0]))==0)
                        {
                            flag=1;
                        }
                        else
                        {
                            flag=0;
                        }
                    }
                    //printf("\n");
                }
                mysql_free_result(result);
                if(flag==1)
                {
                    printf("\n\n  BOOK ID\t\t: %s",tmp[0]);
                    printf("\n  BOOK NAME\t\t: %s",tmp[1]);
                    printf("\n  BOOK AUTHOR\t\t: %s",tmp[2]);
                    printf("\n  LOCATION OF BOOK\t: %s",tmp[4]);
                }
                else
                {
                    printf("\nTHE BOOK-ID DOESN'T MATCHES ANY BOOK...!");
                }
                printf("\n\n  PRESS '0' - BACK \n -> ");
                scanf("%d",&opt);
            }
            if(opt==2)
            {
                printf("\n\nENTER THE BOOK NAME / AUTHOR TO SEARCH : ");
                scanf("%s",ikey);
                skey=strupr(ikey);
                sprintf(query,"SELECT * FROM BOOKS WHERE MATCH (Bname,Bauthor) AGAINST('%s' IN NATURAL LANGUAGE MODE)",skey);
                if (mysql_query(con,query))
                {
                    finish_with_error(con);
                }
                MYSQL_RES *result = mysql_store_result(con);
                if (result == NULL)
                {
                    finish_with_error(con);
                }
                int num_fields = mysql_num_fields(result);
                MYSQL_ROW row;
                printf("\n SEARCH RESULTS : ");
                printf("\n ================\n");
                printf("\n   BOOK-ID\tBOOK-NAME( AUTHOR , LOCATION )");
                printf("\n   ------------------------------------------------\n");
                while ((row = mysql_fetch_row(result)))
                {
                    for(i = 0; i < num_fields; i++)
                    {
                        tmp[i]=row[i];
                    }
                    printf("\n   %s\t%s ( %s , %s )",tmp[0],tmp[1],tmp[2],tmp[4]);
                }
                mysql_free_result(result);
                printf("\n\n   PRESS '0' - BACK \n\n -> ");
                scanf("%d",&opt);
            }
            if(opt>2)
            {
                printf("\n WRONG OPTION, TRY AGAIN");
            }
        }
        while(opt!=1);
        //booksearch
    }
    if(opt>2)
    {
        printf("\n WRONG OPTION, TRY AGAIN");
    }
}
int about()
{
    int opt;
    do
    {
        system("cls");
        printf("\n  LIBRARY MANAGEMENT SYSTEM\n");
        printf("  -------------------------\n");
        printf("\n   * THIS SOFTWARE WAS DEVELOPED BY TEAM - 3.\n\n   * THE TEAM MEMBERS ARE : \n");
        printf("\n       -> ANBUSELVI . M\n");
        printf("       -> ARUNKUMAR . P\n");
        printf("       -> HASKERI BEGUM . T\n");
        printf("       -> IYYANAR . M\n\n");
        printf("\n  THANK YOU !\n  -----------\n\n PRESS '0' - BACK  :  ");
        scanf("%d",&opt);
    }
    while(opt!=0);
}
int dbcon()
{
    MYSQL *con=mysql_init(NULL);
    if(con==NULL)
    {
        printf("\n\tPROBLEM IN CONNECTION TO DATABASE\n");
        printf("\n\tERROR MESSAGE :  ");
        fprintf(stderr, "%s\n", mysql_error(con));
    }
    if (mysql_real_connect(con,host,dbuser,dbpwd,NULL,0,NULL,0)==NULL)
    {
        printf("\n\tPROBLEM IN AUTHENTICATION WITH MYSQL\n");
        printf("\n\tERROR MESSAGE :  ");
        finish_with_error(con);
        mysql_close(con);
    }
    printf("\n\tPROCESS IN CREATING DATABASE... PLEASE WAIT...\n");
    if (mysql_query(con, "CREATE DATABASE IF NOT EXISTS LMS"))
    {
        printf("\n\tPROBLEM IN CREATING DATABASE\n");
        printf("\n\tERROR MESSAGE :  ");
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
    }
    if(mysql_query(con,"USE LMS"))
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
    }
    if(mysql_query(con,"CREATE TABLE IF NOT EXISTS AUSER(Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,Name TEXT,Dsig TEXT,Pwd TEXT,Fk TEXT,Mno TEXT)"))
    {
        finish_with_error(con);
    }
    mysql_query(con,"INSERT INTO AUSER VALUES(1000,'TEST','ADMIN','APWD','AFK','AMNO')");
    mysql_query(con,"CREATE TABLE IF NOT EXISTS LUSER(Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,Name TEXT,Dsig TEXT,Pwd TEXT,Fk TEXT,Mno TEXT,Bis INT,B1 INT,B2 INT,B3 INT,B4 INT,B5 INT)");
    mysql_query(con,"INSERT INTO LUSER(Id,Name,Dsig,Pwd,Fk,Mno)values(2000,'TEST','USER','UPWD','UFK','UMNO')");
    if(mysql_query(con,"CREATE TABLE IF NOT EXISTS BOOKS(Bid INT NOT NULL AUTO_INCREMENT PRIMARY KEY,Bname TEXT,Bauthor TEXT,Tcop INT,Rack TEXT,Dtm DATETIME,FULLTEXT (Bname,Bauthor))"))
    {
        finish_with_error(con);
    }
    else
    {
        mysql_query(con,"INSERT INTO BOOKS(Bid)Values(1000)");
    }
    mysql_query(con,"CREATE TABLE IF NOT EXISTS NOTIFY(SNO INT NOT NULL PRIMARY KEY,Ndt DATETIME NOT NULL,Note TEXT,Aid int)");
    mysql_query(con,"CREATE TABLE IF NOT EXISTS BISRT(Uid INT PRIMARY KEY,B1 text,D1 DATETIME,B2 TEXT,D2 DATETIME,B3 TEXT,D3 DATETIME,B4 TEXT,D4 DATETIME,B5 TEXT,D5 DATETIME)");
    return con;
}
int datime(MYSQL *con)
{
    char *dtime;
    int i;
    if (mysql_query(con,"SELECT NOW()"))
    {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL)
    {
        finish_with_error(con);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        for(i = 0; i < num_fields; i++)
        {
            dtime=(row[i] ? row[i] : "UNKNOWN");
        }
    }
    mysql_free_result(result);
    return dtime;
}
int bookname(MYSQL *con,char *bbid)
{
    char query[1024],*tn;
    int i;
    sprintf(query,"SELECT Bname FROM BOOKS WHERE Bid='%s'",bbid);
    if (mysql_query(con,query))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
        {
            for(i = 0; i < num_fields; i++)
            {
                tn=row[i]?row[i]:"null";
            }
        }
        mysql_free_result(result);
    }
    return tn;
}
int datedif(MYSQL *con,char *isd,char *crd)
{
    char query[1024],*difr;
    int i;
    mysql_query(con,"'\'x");
    sprintf(query,"SELECT DATEDIFF('%s','%s')",crd,isd);
    if(mysql_query(con,query))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if (result == NULL)
        {
            finish_with_error(con);
        }
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
        {
            for(i = 0; i < num_fields; i++)
            {
                difr=row[i];
            }
        }
        mysql_free_result(result);
    }
    return difr;
}
int report(MYSQL *con)
{
    int i,opt,a,u,b;
    char query[1024];
    system("cls");
    printf("\n REPORT\n ====== ");
    if (mysql_query(con, "SELECT * FROM AUSER"))
    {
        finish_with_error(con);
    }
    MYSQL_RES *result1 = mysql_store_result(con);
    if (result1 == NULL)
    {
        finish_with_error(con);
    }
    a = mysql_num_rows(result1);
    mysql_free_result(result1);
    printf("\n\n  NUMBER OF ADMINISTRATORS  :  %d",a);
    if (mysql_query(con, "SELECT * FROM LUSER"))
    {
        finish_with_error(con);
    }
    MYSQL_RES *result2 = mysql_store_result(con);
    if (result2 == NULL)
    {
        finish_with_error(con);
    }
    u = mysql_num_rows(result2);
    mysql_free_result(result2);
    printf("\n\n  NUMBER OF USERS  :  %d",u);
    if (mysql_query(con, "SELECT * FROM BOOKS"))
    {
        finish_with_error(con);
    }
    MYSQL_RES *result3 = mysql_store_result(con);
    if (result3 == NULL)
    {
        finish_with_error(con);
    }
    b = mysql_num_rows(result3);
    mysql_free_result(result3);
    printf("\n\n  NUMBER OF BOOKS  :  %d",b);
    printf("\n\nPRESS '0' - BACK  :  ");
    scanf("%d",&opt);
    if(opt==0)
    {
        opt=1;
        return opt;
    }
    else
    {
        printf("\n WRONG OPTION, TRY AGAIN...!");
    }
}
int backup_restore(MYSQL *con)
{
    int opt,i;
    do
    {
        FILE *BF;
        char *tmprw[20];
        system("cls");
        printf("\n BACKUP & RESTORE\n ================\n");
        printf("\n   1 -> BACKUP DATA");
        printf("\n   2 -> RESTORE DATA");
        printf("\n   0 -> BACK\n\n   -> ");
        scanf("%d",&opt);
        if(opt==1)
        {
            printf("\n\nBACKUP DATA :\n-------------\n");
            system(" if not exist c:\\LMS_BACKUP mkdir c:\\LMS_BACKUP");
            BF=fopen("c://LMS_BACKUP//ADMIN.TXT","w");
            printf("\n PLEASE WAIT...\n\n\n\tBACKUP IN PROGRESS...!\n");
            if(mysql_query(con,"SELECT * FROM AUSER"))
            {
                finish_with_error(con);
            }
            MYSQL_RES *result = mysql_store_result(con);
            if (result == NULL)
            {
                finish_with_error(con);
            }
            int num_fields = mysql_num_fields(result);
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result)))
            {
                for(i = 0; i < num_fields; i++)
                {
                    // sscanf(row[i],"%s",&tmprw[i]);
                    tmprw[i]=row[i];
                }
                fprintf(BF,"%s,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\n",tmprw[0],tmprw[1],tmprw[2],tmprw[3],tmprw[4],tmprw[5]);
            }
            mysql_free_result(result);
            fclose(BF);
            printf("\n\t  -> ADMINISTRATOR DETAILS => 100%...");
            //

            BF=fopen("c://LMS_BACKUP//USER.TXT","w");
            if(mysql_query(con,"SELECT * FROM LUSER"))
            {
                finish_with_error(con);
            }
            MYSQL_RES *result1 = mysql_store_result(con);
            if (result1 == NULL)
            {
                finish_with_error(con);
            }
            int num_fields1 = mysql_num_fields(result1);
            MYSQL_ROW row1;
            while ((row1 = mysql_fetch_row(result1)))
            {
                for(i = 0; i < num_fields1; i++)
                {
                    // sscanf(row[i],"%s",&tmprw[i]);
                    tmprw[i]=row1[i];
                }
                fprintf(BF,"%s,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\n",tmprw[0],tmprw[1],tmprw[2],tmprw[3],tmprw[4],tmprw[5],tmprw[6],tmprw[7],tmprw[8],tmprw[9],tmprw[10],tmprw[11]);
            }
            mysql_free_result(result1);
            fclose(BF);
            printf("\n\t  -> USER DETAILS => 100%...");
            //

            BF=fopen("c://LMS_BACKUP//BOOKS.TXT","w");
            if(mysql_query(con,"SELECT * FROM BOOKS"))
            {
                finish_with_error(con);
            }
            MYSQL_RES *result2 = mysql_store_result(con);
            if (result2 == NULL)
            {
                finish_with_error(con);
            }
            int num_fields2 = mysql_num_fields(result2);
            MYSQL_ROW row2;
            while ((row2 = mysql_fetch_row(result2)))
            {
                for(i = 0; i < num_fields2; i++)
                {
                    // sscanf(row[i],"%s",&tmprw[i]);
                    tmprw[i]=row2[i];
                }
                fprintf(BF,"%s,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\n",tmprw[0],tmprw[1],tmprw[2],tmprw[3],tmprw[4],tmprw[5]);
            }
            mysql_free_result(result);
            fclose(BF);
            printf("\n\t  -> BOOKS DETAILS => 100%...");
            //

            BF=fopen("c://LMS_BACKUP//BISRT.TXT","w");
            if(mysql_query(con,"SELECT * FROM BISRT"))
            {
                finish_with_error(con);
            }
            MYSQL_RES *result3 = mysql_store_result(con);
            if (result3 == NULL)
            {
                finish_with_error(con);
            }
            int num_fields3 = mysql_num_fields(result3);
            MYSQL_ROW row3;
            while ((row3 = mysql_fetch_row(result3)))
            {
                for(i = 0; i < num_fields3; i++)
                {
                    // sscanf(row[i],"%s",&tmprw[i]);
                    tmprw[i]=row3[i];
                }
                fprintf(BF,"%s,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\n",tmprw[0],tmprw[1],tmprw[2],tmprw[3],tmprw[4],tmprw[5],tmprw[6],tmprw[7],tmprw[8],tmprw[9],tmprw[10]);
            }
            mysql_free_result(result1);
            fclose(BF);
            printf("\n\t  -> BOOK ISSUE DETAILS => 100%...");
            //

            BF=fopen("c://LMS_BACKUP//NOTIFY.TXT","w");
            if(mysql_query(con,"SELECT * FROM NOTIFY"))
            {
                finish_with_error(con);
            }
            MYSQL_RES *result4 = mysql_store_result(con);
            if (result4 == NULL)
            {
                finish_with_error(con);
            }
            int num_fields4 = mysql_num_fields(result4);
            MYSQL_ROW row4;
            while ((row4 = mysql_fetch_row(result4)))
            {
                for(i = 0; i < num_fields4; i++)
                {
                    // sscanf(row[i],"%s",&tmprw[i]);
                    tmprw[i]=row4[i];
                }
                fprintf(BF,"%s,\"%s\",\"%s\",\"%s\",\n",tmprw[0],tmprw[1],tmprw[2],tmprw[3]);
            }
            mysql_free_result(result1);
            fclose(BF);
            printf("\n\t  -> NOTIFICATION DETAILS => 100%...");
            printf("\n\n BACKUP COMPLETED SUCCESSFULLY...!");
            printf("\n\n YOUR BACKUP FILES ARE STORED IN LOCATION  :  \"C:\\LMS_BACKUP\" ");
            printf("\n\n PRESS '1' TO CONTINUE  :  ");
            scanf("%d",&opt);
        }
        if(opt==2)
        {
            printf("\n\nRESTORE DATA :\n--------------\n");
            printf("\n\n *. WARNING : RESTORING WITH BACKUP WILL ERASE THE CURRENT CONTENT IN DATABASE .*");
            printf("\n\n PRESS '1' - RESTORE (OR) '0' - CANCEL\n\n   -> ");
            scanf("%d",&opt);
            if(opt==1)
            {
                //restore
                BF=fopen("c://LMS_BACKUP//ADMIN.TXT","r");
                if(BF==NULL)
                {
                    printf("\n   NO BACKUP DATA FOUND !");
                    printf("\n   PLEASE COPY THE BACKUP TO THIS LOCATION AND TRY AGAIN  :  \"C:\LMS_BACKUP\"");
                }
                else
                {
                    mysql_query(con,"DELETE FROM AUSER");
                    mysql_query(con,"LOAD DATA LOCAL INFILE 'C:/LMS_BACKUP/ADMIN.TXT' INTO TABLE AUSER FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'");
                    printf("\n\t  -> ADMINISTRATOR DETAILS => 100%...");
                    mysql_query(con,"DELETE FROM LUSER");
                    mysql_query(con,"LOAD DATA LOCAL INFILE 'C:/LMS_BACKUP/USER.TXT' INTO TABLE LUSER FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'");
                    printf("\n\t  -> USER DETAILS => 100%...");
                    mysql_query(con,"DELETE FROM BOOKS");
                    mysql_query(con,"LOAD DATA LOCAL INFILE 'C:/LMS_BACKUP/BOOKS.TXT' INTO TABLE BOOKS FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'");
                    printf("\n\t  -> BOOK DETAILS => 100%...");
                    mysql_query(con,"DELETE FROM BISRT");
                    mysql_query(con,"LOAD DATA LOCAL INFILE 'C:/LMS_BACKUP/BISRT.TXT' INTO TABLE BISRT FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'");
                    printf("\n\t  -> BOOK ISSUE DETAILS => 100%...");
                    mysql_query(con,"DELETE FROM NOTIFY");
                    mysql_query(con,"LOAD DATA LOCAL INFILE 'C:/LMS_BACKUP/NOTIFY.TXT' INTO TABLE NOTIFY FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'");
                    printf("\n\t  -> NOTIFICATION DETAILS => 100%...");
                    printf("\n\n RESTORE COMPLETED SUCCESSFULLY...!");
                    printf("\n\n RESTART THE APPLICATION TO WORK PROPERLY...! ");
                    printf("\n\n PRESS '1' TO CONTINUE  :  ");
                    scanf("%d",&opt);
                }
                fclose(BF);
            }
            if(opt>1)
            {
                printf("\n WRONG OPTION... PLEASE TRY AGAIN ... !");
            }
        }
        if(opt>2)
        {
            printf("\n INVALID OPTION, TRY AGAIN...!");
        }
    }
    while(opt!=0);
}
