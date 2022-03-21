#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
void gotoxy(int x,int y)
{
    COORD coord= {0,0};             //This function allows us move the cursor in the output screen
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void delay(int seconds)
{
    int milliseconds = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}
void drawframe()
{
    int i;
    gotoxy(0,0);
    printf("%c",201);               // ascii codes of the edges of the frame
    for(i=1; i<45; i++)printf("%c",205);
    printf("%c",187);
    gotoxy(0,1);
    printf("%c",186);               //186 is code for the vertical walls of the frame
    for(i=1; i<45; i++)printf(" ");
    printf("%c",186);
    gotoxy(0,2);
    printf("%c",186);
    for(i=1; i<45; i++)printf(" ");
    printf("%c",186);
    gotoxy(0,3);
    printf("%c",186);
    for(i=1; i<45; i++)printf(" ");
    printf("%c",186);
    gotoxy(0,4);
    printf("%c",186);
    for(i=1; i<45; i++)printf(" ");
    printf("%c",186);
    gotoxy(0,5);
    printf("%c",186);
    for(i=1; i<45; i++)printf(" ");
    printf("%c",186);
    gotoxy(0,6);
    printf("%c",186);
    for(i=1; i<45; i++)printf(" ");
    printf("%c",186);
    gotoxy(0,7);
    printf("%c",200);
    for(i=1; i<45; i++)printf("%c",205);
    printf("%c",188);                 //lower right edge of the frame
}
void ShowConsoleCursor(int x )
{
    HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cp;
    GetConsoleCursorInfo(out,&cp);
    cp.bVisible=x;                 //shows the cursor or hides it
    SetConsoleCursorInfo(out,&cp);
}
typedef struct
{
    int day;
    int month;
    int year;
} Date;
typedef struct
{
    char lastname[50];
    char firstname[50];
    Date birthdate;
    char address[50];
    char phonenumber[50];     //must be character array as no calculations occur on phone number and must contain 0 at the beginning
    char email[50];
} customer;
int validate_name(char name[])
{
    int i=0;
    for(i=0; i<strlen(name); i++)
    {
        if(!isalpha(*(name+i)))
            if(name[i]=='-'&&i!=0)
                continue;
            else
                return 0;                  //returns 0 making the name invalid as it contains something other than letters
        if(i==0)
        {
            if(*name>=97)
                *name=*name-32;     //it makes the first letter upper case if it's entered as lower case letter
        }
        else if(*(name+i)<=90)         //it ensures that all other letters are lower case, and changes them to lower case if they were upper case
            *(name+i)=*(name+i)+32;
    }
    return 1;
}
int validate_date(char d[],char m[],char y[])
{
    int i;
    for( i=0; i<strlen(y); i++)
    {
        if(isalpha(y[i])) return 0;       //the numbers were passed as character arrays to test for the presence of digits

    }
    for( i=0; i<strlen(m); i++)
    {
        if(isalpha(m[i])) return 0;

    }
    for( i=0; i<strlen(d); i++)
    {
        if(isalpha(d[i])) return 0;

    }
    int a,b,c;
    a=atoi(d);         //convert each entry to integer data types to make comparisons
    b=atoi(m);
    c=atoi(y);
    if(!d||!m||!y)
        return 0;
    if(a>31||a<1)
        return 0;
    if(b>12||b<1)
        return 0;
    if(c<1||c>2022)
        return 0;
    if(b==2&&a>29)
        return 0;
    if(b%2==0&&a>30)
        return 0;
    return 1;     //meaning that the date is valid
}
int validate_phonenumber(char phone[],char c)
{
    int i=0;
    if(c=='1')
    {
        if(strlen(phone)==11)   //in case of mobile number
        {
            if(phone[1]!='1')
                return 0;
            if(phone[2]!='1'&&phone[2]!='0'&&phone[2]!='2'&&phone[2]!='5')
                return 0;
            if(*phone!='0')     //it must start with 0
                return 0;
            while(*(phone+i))
            {
                if(!isdigit(*(phone+i)))      //ensure that the elements are all digits
                    return 0;
                i++;
            }
        }
        else if(strlen(phone)==10||strlen(phone)==9)       //in case of land line number
        {
            if(*phone!='0')
                return 0;
            while(*(phone+i))
            {
                if(!isdigit(*(phone+i)))
                    return 0;
                i++;
            }
        }
        else
            return 0;
    }
    else
    {
        while(*(phone+i))
        {
            if(!isdigit(*(phone+i)))
                return 0;
            i++;
        }
        if(strlen(phone)<1)
            return 0;
    }
    return 1;
}
int validate_prefix(char pre[])
{
    if(strlen(pre)<1)     //prefix must be at least one character
        return 0;
    if(pre[0]=='.'||pre[0]=='-'||pre[0]=='#'||pre[0]=='_'||pre[0]=='$'||pre[0]=='^'||pre[0]=='*'||pre[0]=='@'||pre[0]=='!'||pre[0]=='%'||pre[0]=='&'||pre[0]=='('||pre[0]==')')     //must not start with a symbol
        return 0;
    for(int i=0; i<strlen(pre); i++)
    {
        if(pre[i]=='#')      //must not contain hash
            return 0;
        if(pre[i]==' ')
            return 0;
        if(pre[i]=='.'||pre[i]=='-'||pre[i]=='#'||pre[i]=='_'||pre[i]=='$'||pre[i]=='^'||pre[i]=='*'||pre[i]=='@'||pre[i]=='!'||pre[i]=='%'||pre[i]=='&'||pre[i]=='('||pre[i]==')')
        {
            if(i==strlen(pre)-1)           //must not end with a symbol
                return 0;
            if(pre[i]==pre[i+1])           //must not have two consecutive symbols
                return 0;
        }
    }
    return 1;
}
int validate_domain(char dom[])
{
    int dcount=0;
    if(strlen(dom)<1)
        return 0;
    if(dom[0]=='.'||dom[0]=='-'||dom[0]=='#'||dom[0]=='_'||dom[0]=='$'||dom[0]=='^'||dom[0]=='*'||dom[0]=='@'||dom[0]=='!'||dom[0]=='%'||dom[0]=='&'||dom[0]=='('||dom[0]==')')
        return 0;
    for(int i=0; i<strlen(dom); i++)
    {
        if(dom[i]=='@')
            return 0;
        if(dom[i]==' ')
            return 0;
        if(dom[i]=='#')
            return 0;
        if(dom[i]=='.')
            dcount++;
        if(dom[i]=='.'||dom[i]=='-'||dom[i]=='#'||dom[i]=='_'||dom[i]=='$'||dom[i]=='^'||dom[i]=='*'||dom[i]=='@'||dom[i]=='!'||dom[i]=='%'||dom[i]=='&'||dom[i]=='('||dom[i]==')')
        {
            if(i==strlen(dom)-1)
                return 0;
            if(dom[i]==dom[i+1])
                return 0;
        }
    }
    if(dcount<1)       //must contain at least one dot
        return 0;
    char* token=strtok(dom,".");
    while(token)
    {
        if(strlen(token)<2)   //the number of characters after dot must be at least 2
            return 0;
        token=strtok(NULL,".");
    }
    return 1;
}
int validate_email(char em[])
{
    char prefix[50];
    char domain[50];
    char*em2=malloc(strlen(em)+1);
    strcpy(em2,em);       // as the original email will be ruined by strtok function
    char*token=strtok(em,"@");
    if(strcmp(token,em2)==0) //to ensure that th email contains @
        return 0;
    strcpy(prefix,token);
    if(!validate_prefix(prefix))
        return 0;
    token=strtok(NULL,"");   //to make sure that the email contains something after @
    if(!token)
        return 0;
    strcpy(domain,token);
    if(!validate_domain(domain))
        return 0;
    strcpy(em,em2);     //copy the elements back to the original array
    free(em2);
    return 1;
}
Date construct_d(int d,int m,int y)
{
    Date da;
    da.day=d;
    da.month=m;
    da.year=y;
    return da;
}
customer* construct_c(char lname[],char fname[],Date bdate,char add[],char phonen[],char email[] )
{
    customer*c=malloc(sizeof(customer));
    while(!validate_name(lname))
    {
        printf("\nInvalid Last Name,Enter name again:");
        scanf(" %s",lname);
    }
    strcpy(c->lastname,lname);
    while(!validate_name(fname))
    {
        printf("\nInvalid First Name,Enter name again:");
        scanf(" %s",fname);
    }
    strcpy(c->firstname,fname);
    while(!validate_date(bdate.day,bdate.month,bdate.year))
    {
        printf("\nInvalid date,Enter date again in the form dd-mm-yyyy:");
        scanf("%d-%d-%d",&bdate.day,&bdate.month,&bdate.year);
    }
    c->birthdate.day=bdate.day;
    c->birthdate.month=bdate.month;
    c->birthdate.year=bdate.year;
    /*while(!validate_phonenumber(phonen))
    {
        printf("\nInvalid phonenumber, Enter phonenumber again: ");
        scanf(" %s",phonen);
    }
    strcpy(c->phonenumber,phonen);*/
    char ch;
    while(!validate_email(email))
    {
        printf("\nInvalid email, Enter email again: ");
        ch=getchar();
        gets(email);
    }
    strcpy(c->email,email);
    strcpy(c->address,add);
    return c;
}
int counter=0;     //counts number of records
customer records[100];   //stores records
char Filname[50];        //stores name of file directory
int fcount=0;
void LOAD()
{
    char name[50],c,arr[100],arr2[50];
    printf("Enter file name : ");
    gets(name);
    printf("---------------------------------------------------------------------------------------------------------\n");
    strcpy(Filname,name);    //copy to global variable
    counter=0;
    FILE*f=fopen(Filname,"r");
    if(f==NULL)
    {
        printf("\aError loading file.Returning to main menu\n");
        delay(2);      //program will sleep for 2 seconds
        system("cls");
        mainmenu();
        exit(0);      //make sure that the file exists
    }
    while(!feof(f))
    {
        fscanf(f,"%[^,],",records[counter].lastname);
        fscanf(f,"%[^,],",records[counter].firstname);
        fscanf(f,"%d-%d-%d,",&records[counter].birthdate.day,&records[counter].birthdate.month,&records[counter].birthdate.year);
        fscanf(f,"%[^,],",records[counter].address);     //store the information in the directory in the global arrays
        fscanf(f,"%[^,],",records[counter].phonenumber);
        fscanf(f,"%s\n",records[counter].email);
        counter++;     //count the number of records in file directory
    }
    fclose(f);
}
int ncount=0;    //decide which path to take in quit function
void search_name()
{
    int found=0;
    ncount=1;         //no modification in directory
    char key[30],s[2],upr[30];
    if(!fcount)
    {
        LOAD();
        fcount++;
    }
    printf("Enter the last name of the contact you wish to search for: ");
    gets(key);
    printf("---------------------------------------------------------------------------------------------------------");
    validate_name(key);    //to make sure that the entered name is valid
    int i;
    for(i=0; i<counter; i++)
    {
        strcpy(upr,records[i].lastname);
        strupr(upr);               //to decrease errors of lower case
        if(strcmp(strupr(key),upr)==0)
        {
            found=1;    //print the arrays matching criteria
            printf("\nRecord number %d :\nFirst name is: %s\nBirthdate is : %02d-%02d-%02d\nThe address is : %s\nThe phone number is : %s\nThe email : %s\n",i+1,records[i].firstname,records[i].birthdate.day,records[i].birthdate.month,records[i].birthdate.year,records[i].address,records[i].phonenumber,records[i].email);
        }
    }
    if(found==0)
    {
        printf("\n\aThe contact is not found\nIf you want to search for another contact enter Y, otherwise enter N : ");
        gets(s);
        while(strcmp(s,"Y")&&strcmp(s,"y")&&strcmp(s,"N")&&strcmp(s,"n"))
        {
            printf("---------------------------------------------------------------------------------------------------------\n");
            printf("Invalid character, Retry : ");
            gets(s);
        }
        if(strcmp(s,"Y")==0|| strcmp(s,"y")==0)
            search_name();
        else if(strcmp(s,"N")==0|| strcmp(s,"n")==0)
            quit();
    }
    else
    {
        printf("\n---------------------------------------------------------------------------------------------------------\n Do you want to search for another contact enter Y, otherwise enter N : ");
        gets(s);
        while(strcmp(s,"Y")&&strcmp(s,"y")&&strcmp(s,"N")&&strcmp(s,"n"))
        {
            printf("---------------------------------------------------------------------------------------------------------\n");
            printf("Invalid character, Retry : ");
            gets(s);
        }
        if(strcmp(s,"Y")==0|| strcmp(s,"y")==0)
            search_name();
        else if(strcmp(s,"N")==0|| strcmp(s,"n")==0)
            quit();
    }

}
void SAVE()
{
    FILE*fptr=fopen(Filname,"w");  //same file name used when operating on file
    if(!fptr)
    {
        printf("Error loading file.\a\n");
        exit(0);
    }
    for(int i=0; i<counter; i++)
    {
        fprintf(fptr,"%s,%s,%02d-%02d-%02d,%s,%s,%s\n",records[i].lastname,records[i].firstname,records[i].birthdate.day,records[i].birthdate.month,records[i].birthdate.year,records[i].address,records[i].phonenumber,records[i].email);
    }
    fcount=0;
    fclose(fptr);
    char c1=getchar();          //absorbs the new line form scanf in quit function
}
void quit()
{
    char in;
    char c1;
    printf("---------------------------------------------------------------------------------------------------------");
    if(!ncount)          //if there was modification in file
    {
        printf("\n\aYour changes have not been saved.\nEnter number of the option you wish to take:");
        printf("\nOption 1: Save changes and exit\nOption 2: Quit without saving\nOption 3: Save changes and return to main menu\nOption 4: Discard changes and return to main menu\nEnter your choice: ");
        do
        {
            scanf("%c",&in);       //we made it a character data type so as the user enters a letter an infinite loop is avoided
            printf("---------------------------------------------------------------------------------------------------------\n");
            switch(in)
            {
            case '1':
                SAVE();
                printf("\aYour changes were saved successfully\nThank you");
                exit(0);
                break;
            case '2':
                printf("\aYour changes were discarded\nThank you");
                exit(0);
                break;
            case '3':
                SAVE();
                printf("\aYour changes were saved successfully, returning to main menu");
                delay(2);
                fcount=0;
                system("cls");  //clears output screen for main menu
                mainmenu();
                break;
            case '4':
                c1=getchar();
                fcount=0;
                printf("\aYour changes were discarded, returning to main menu");
                delay(2);
                system("cls");
                fcount=0;    //to allow user to enter new file name
                mainmenu();
                break;
            default:
                c1=getchar();   //to absorb new line from scanf
                printf("\aInvalid option number, enter option number again:");
            }
        }
        while(in!='1'&&in!='2'&&in!='3'&&in!='4');
    }
    else     //no modification in file
    {
        ncount=0;
        printf("\nEnter the number of the option you want to take\nOption 1: Exit\nOption 2 : Return to main menu\nEnter your choice :");
        do
        {
            scanf("%c",&in);
            printf("---------------------------------------------------------------------------------------------------------\n");
            switch(in)
            {
            case '1':
                printf("Thank you");
                exit(0);
                break;
            case '2':
                c1=getchar();  //to absorb newline form scanf
                printf("\aReturning to main menu");
                delay(2);
                system("cls");
                fcount=0;     //to enter new file name for any function
                mainmenu();
                break;
            default:
                c1=getchar();    //to absorb the new line form scanf
                printf("\aInvalid option number, enter option number again:");
            }
        }
        while(in!='1'&&in!='2');
    }
}
void ADD()
{
    char x[30],y[30],z[30];
    char q1,s[2],q2;
    if(!fcount)
    {
        LOAD();
        fcount++;   //so that the user does not to enter file name again
    }
    printf("Enter last name:");
    gets(records[counter].lastname);
    while(!validate_name(records[counter].lastname))
    {
        printf("\n\aInvalid last name,Enter name again:");
        gets(records[counter].lastname);
    }
    printf("Enter first name:");
    gets(records[counter].firstname);
    while(!validate_name(records[counter].firstname))
    {
        printf("\n\aInvalid first name,Enter name again:");
        gets(records[counter].firstname);
    }
    printf("Enter date in format dd-mm-yyyy: ");
    scanf("%[^-]-",x);
    scanf("%[^-]-",y);     // we take them as character arrays to detect if the user entered something other than digit
    scanf("%[^\n]",z);
    while(!validate_date(x,y,z))
    {
        printf("\n\aInvalid date,Enter date again in the form dd-mm-yyyy:");
        scanf("%[^-]-",x);
        scanf("%[^-]-",y);
        scanf("%[^\n]",z);
    }
    records[counter].birthdate.day=atoi(x);
    records[counter].birthdate.month=atoi(y);   //convert them to integer data types
    records[counter].birthdate.year=atoi(z);
    printf("Enter Address:");
    q1=getchar();     //to absorb new line from previous scanf
    gets(records[counter].address);
    printf("To add a local number enter 1.\nTo add an international number/hotline enter 2.\nEnter your choice:");
    scanf("%c",&q2);
    q1=getchar();
    while(q2!='1'&&q2!='2')
    {
        printf("\n\aInvalid choice, Enter your choice again: ");
        scanf("%c",&q2);
        q1=getchar();
    }
    printf("Enter Phone number:");
    gets(records[counter].phonenumber);
    while(!validate_phonenumber(records[counter].phonenumber,q2))
    {
        printf("\n\aInvalid phone number, Enter phone number again: ");
        gets(records[counter].phonenumber);
    }
    printf("Enter email:");
    gets(records[counter].email);
    while(!validate_email(records[counter].email))
    {
        printf("\n\aInvalid email, Enter email again: ");
        gets(records[counter].email);
    }
    printf("\nThe record that will be added is:\nLast name: %s\nFirst name: %s\nBirthdate: %02d-%02d-%02d\nThe address: %s\nThe phone number: %s\nThe email: %s\n",records[counter].lastname,records[counter].firstname,records[counter].birthdate.day,records[counter].birthdate.month,records[counter].birthdate.year,records[counter].address,records[counter].phonenumber,records[counter].email);
    counter++;    //to increase the number of records
    printf("\n---------------------------------------------------------------------------------------------------------\nDo you want to add another record \nIf you want to add another record enter Y, otherwise enter N : ");
    gets(s);
    while(strcmp(s,"Y")&&strcmp(s,"y")&&strcmp(s,"N")&&strcmp(s,"n"))
    {
        printf("---------------------------------------------------------------------------------------------------------\n");
        printf("Invalid character, Retry : ");
        gets(s);
    }
    if(strcmp(s,"Y")==0|| strcmp(s,"y")==0)
        ADD();
    else if(strcmp(s,"N")==0|| strcmp(s,"n")==0)
        quit();
}
void Delete()
{
    int found=0,place;
    char key[30],s[2],key2[30],upr1[30],upr2[30];
    if(!fcount)
    {
        LOAD();
        fcount++;
    }
    printf("Enter the last name of the contact(s) you wish to delete: ");
    gets(key);
    while(!validate_name(key))
    {
        printf("\n\aInvalid last name,Enter name again:");
        gets(key);
    }
    printf("\nEnter the first name of the contact(s) you wish to delete: ");
    gets(key2);
    while(!validate_name(key2))
    {
        printf("\n\aInvalid first name,Enter name again:");
        gets(key2);
    }
    int i;
    for(i=0; i<counter; i++)   //linear search
    {

        if(strcmp(key,records[i].lastname)==0&&strcmp(key2,records[i].firstname)==0)
            printf("\nRecord number %d :\nLast name: %s\nFirst name: %s\nBirthdate: %02d-%02d-%02d\nThe address: %s\nThe phone number: %s\nThe email: %s\n\n",i+1,records[i].lastname,records[i].firstname,records[i].birthdate.day,records[i].birthdate.month,records[i].birthdate.year,records[i].address,records[i].phonenumber,records[i].email);
    }
    for(i=0; i<counter; i++)
    {

        if(strcmp(key,records[i].lastname)==0&&strcmp(key2,records[i].firstname)==0)
        {
            while(strcmp(key,records[i].lastname)==0&&strcmp(key2,records[i].firstname)==0)    //to prevent error of two consecutive records matching criteria
            {
                found=1;
                place=i;
                if(place==counter-1) // if it is the last record
                {
                    counter--;
                    break;   //break otherwise infinite loop
                }
                else
                {
                    for(int j=place; j<counter; j++)
                    {
                        records[j]=records[j+1];    //overwrite the selected record by the following records
                    }
                    counter--;    //remove the selected record
                }
            }
        }
    }
    if(found)
    {
        quit();
    }
    else
    {
        printf("\n\aThe contact is not found\nIf you want to delete another contact enter Y, otherwise enter N : ");
        gets(s);
        while(strcmp(s,"Y")&&strcmp(s,"y")&&strcmp(s,"N")&&strcmp(s,"n"))
        {
            printf("\nInvalid character, Retry : ");
            gets(s);
        }
        if(strcmp(s,"Y")==0|| strcmp(s,"y")==0)
        {
            Delete();
        }
        else if(strcmp(s,"N")==0|| strcmp(s,"n")==0)
        {
            ncount=1;    //meaning that no modification occurred on the arrays
            quit();
        }
    }
}
int submain()
{
    int pos=1;
    char ch;
    drawframe();
    HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);  //control the foreground and background of text
    ShowConsoleCursor(0);   //hide cursor
    do
    {
        SetConsoleTextAttribute(console,15);   //black background white text
        gotoxy(1,1);
        printf("1-Modify lastname ");
        gotoxy(1,2);
        printf("2-Modify firstname ");
        gotoxy(1,3);
        printf("3-Modify birthdate ");
        gotoxy(1,4);
        printf("4-Modify address ");
        gotoxy(1,5);
        printf("5-Modify phonenumber ");
        gotoxy(1,6);
        printf("6-Modify email ");
        printf("\n\n");    //construct menu
        switch(pos)
        {
        case 1 :
            SetConsoleTextAttribute(console,240);   //shaded background on selection
            gotoxy(1,1);
            printf("1-Modify lastname ");
            break;
        case 2:
            SetConsoleTextAttribute(console,240);
            gotoxy(1,2);
            printf("2-Modify firstname ");
            break;
        case 3:
            SetConsoleTextAttribute(console,240);
            gotoxy(1,3);
            printf("3-Modify birthdate ");
            break;
        case 4:
            SetConsoleTextAttribute(console,240);
            gotoxy(1,4);
            printf("4-Modify address ");
            break;
        case 5:
            SetConsoleTextAttribute(console,240);
            gotoxy(1,5);
            printf("5-Modify phonenumber ");
            break;
        case 6:
            SetConsoleTextAttribute(console,240);
            gotoxy(1,6);
            printf("6-Modify email ");
            break;
        }
        ch=getch();
        if(ch==-32)ch=getch();
        if(ch==72)
        {
            pos--;
            if(pos==0)pos=6;  //if moving up from first option in menu brings cursor back to the last option
        }
        if(ch==80)
        {
            pos++;
            if(pos==7)pos=1; //brings cursor back to first menu
        }
    }
    while(ch!=13);    //exit loop when entered character is a new line
    SetConsoleTextAttribute(console,15);   //return to default foreground and background
    gotoxy (0,8);
    ShowConsoleCursor(1);   //make cursor appear
    return pos;    //position marking which field to be modified
}
void MODIFY()
{
    char x[30],y[30],z[30];
    int found=0,f=0,place,i,m;
    char key[30],s[2],q1,q2;
    if(!fcount)
    {
        LOAD();
        fcount++;
    }
    int places[counter];   //array containing records that match the entered last name
    printf("Enter the last name of the contact you wish to modify: ");
    gets(key);
    while(!validate_name(key))
    {
        printf("---------------------------------------------------------------------------------------------------------\n");
        printf("\aInvalid last name,Enter name again:");
        gets(key);
    }
    for(i=0; i<counter; i++)
    {
        if(strcmp(key,records[i].lastname)==0) //linear search
        {
            places[found]=i;    //store the index of the matching elements
            found++;     //add matching records to places array, if more than one record have the
            place=i;    //to mark the index of the matching element
        }
    }
    if(found!=0)
    {
        printf("\nContact(s) with last name %s:\n ",key);
        for(i=0; i<found; i++)
        {
            printf("\nRecord number %d:\nLast name: %s\nFirst name: %s\nBirthdate: %02d-%02d-%02d\nThe address: %s\nThe phone number : %s\nThe email: %s\n",places[i]+1,records[places[i]].lastname,records[places[i]].firstname,records[places[i]].birthdate.day,records[places[i]].birthdate.month,records[places[i]].birthdate.year,records[places[i]].address,records[places[i]].phonenumber,records[places[i]].email);
        }
        if(found>1)    //meaning more than one record match the entered last name
        {
            printf("\nEnter the record number you wish to modify:");
            scanf("%d",&place);
            place--;   //as the print statement was place+1
            for(int j=0; j<found; j++)
            {
                if(places[j]==place)   //to make sure that the user's selection is within the options
                {
                    f=1;
                    printf("\nSelected record: \nRecord number %d:\nLast name: %s\nFirst name: %s\nBirthdate: %02d-%02d-%02d\nThe address: %s\nThe phone number: %s\nThe email: %s",place+1,records[place].lastname,records[place].firstname,records[place].birthdate.day,records[place].birthdate.month,records[place].birthdate.year,records[place].address,records[place].phonenumber,records[place].email);
                    char sh=getchar();  //to absorb newline form scanf
                    break;
                }
            }
            while(!f)  //if the user's entry was not one of the displayed options
            {
                printf("\nThe record number you entered is not one of the displayed options.\nEnter the record number you wish to modify:");
                scanf("%d",&place);
                place--;
                for(int j=0; j<found; j++)
                {
                    if(places[j]==place)
                    {
                        f=1;
                        printf("\nSelected record: \nRecord number %d:\nLast name: %s\nFirst name: %s\nBirthdate: %02d-%02d-%02d\nThe address: %s\nThe phone number: %s\nThe email: %s",place+1,records[place].lastname,records[place].firstname,records[place].birthdate.day,records[place].birthdate.month,records[place].birthdate.year,records[place].address,records[place].phonenumber,records[place].email);
                        char sh=getchar();   //to absorb newline form scanf
                        break;
                    }
                }
            }
        }
        printf("\n---------------------------------------------------------------------------------------------------------\n");
        printf("\aChoose the field you want to modify from the following menu.");
        do
        {
            delay(4);
            system("cls");  //clear screen for menu
            drawframe();
            m=submain();   //position of cursor returned for submain corresponding to element
            switch(m)   //choose which element of data to modify in the record
            {
            case 1:
                printf("\nThe current last name is %s.\nEnter modified lastname:",records[place].lastname);
                gets(records[place].lastname);
                while(!validate_name(records[place].lastname))
                {
                    printf("\n\aInvalid last name,Enter name again:");
                    gets(records[place].lastname);
                }
                break;
            case 2:
                printf("\nThe current firstname is %s.\nEnter modified firstname:",records[place].firstname);
                gets(records[place].firstname);
                while(!validate_name(records[place].firstname))
                {
                    printf("\n\aInvalid first name,Enter name again:");
                    gets(records[place].firstname);
                }
                break;
            case 3:
                printf("\nThe current birthdate is %02d-%02d-%02d.\nEnter date in format dd-mm-yyyy: ",records[place].birthdate.day,records[place].birthdate.month,records[place].birthdate.year);
                scanf("%[^-]-",x);
                scanf("%[^-]-",y);
                scanf("%[^\n]",z);
                while(!validate_date(x,y,z))
                {
                    printf("\n\aInvalid date,Enter date again in the form dd-mm-yyyy:");
                    scanf("%[^-]-",x);
                    scanf("%[^-]-",y);
                    scanf("%[^\n]",z);
                }
                records[place].birthdate.day=atoi(x);
                records[place].birthdate.month=atoi(y);
                records[place].birthdate.year=atoi(z);
                q1=getchar();  //to absorb newline from scanf
                break;
            case 4:
                printf("\nThe current address is %s.\nEnter modified address:",records[place].address);
                gets(records[place].address);
                break;
            case 5:
                printf("\nThe current phone number is %s.\n",records[place].phonenumber);
                printf("To add a local number enter 1.\nTo add an international number/hot-line enter 2.\nEnter your choice:");
                scanf("%c",&q2);
                q1=getchar();
                while(q2!='1'&&q2!='2')
                {
                    printf("\n\aInvalid choice, Enter your choice again: ");
                    scanf("%c",&q2);
                    q1=getchar();
                }
                printf("Enter modified phone number:");
                gets(records[place].phonenumber);
                while(!validate_phonenumber(records[place].phonenumber,q2))
                {
                    printf("\n\aInvalid phone number, Enter phone number again: ");
                    gets(records[place].phonenumber);
                }
                break;
            case 6:
                printf("\nThe current email is %s.\nEnter modified email:",records[place].email);
                gets(records[place].email);
                while(!validate_email(records[place].email))
                {
                    printf("\n\aInvalid email, Enter email again: ");
                    gets(records[place].email);
                }
                break;
            }
            printf("\n\aIf you want to modify another field enter y if you want to modify,otherwise n:");
            gets(s);
            while(strcmp(s,"Y")&&strcmp(s,"y")&&strcmp(s,"N")&&strcmp(s,"n"))
            {
                printf("\n\aInvalid character, Retry : ");
                gets(s);
            }

        }
        while(strcmp(s,"Y")==0||strcmp(s,"y")==0);   //loop terminates when the user no longer wants to modify data
        printf("\nModified record: \nRecord number %d:\nLast name: %s\nFirst name: %s\nBirthdate: %02d-%02d-%02d\nThe address: %s\nThe phone number: %s\nThe email: %s\n",place+1,records[place].lastname,records[place].firstname,records[place].birthdate.day,records[place].birthdate.month,records[place].birthdate.year,records[place].address,records[place].phonenumber,records[place].email);
        printf("\n---------------------------------------------------------------------------------------------------------\nDo you want to modify for another contact enter Y, otherwise enter N : ");
        gets(s);
        while(strcmp(s,"Y")&&strcmp(s,"y")&&strcmp(s,"N")&&strcmp(s,"n"))
        {
            printf("---------------------------------------------------------------------------------------------------------\n");
            printf("\aInvalid character, Retry : ");
            gets(s);
        }
        if(strcmp(s,"Y")==0|| strcmp(s,"y")==0)
            MODIFY();
        else if(strcmp(s,"N")==0|| strcmp(s,"n")==0)
            quit();
    }
    else
    {
        printf("---------------------------------------------------------------------------------------------------------\n");
        printf("\aThe contact is not found\nIf you want to modify another contact enter Y, otherwise enter N : ");
        gets(s);
        while(strcmp(s,"Y")&&strcmp(s,"y")&&strcmp(s,"N")&&strcmp(s,"n"))
        {
            printf("\n\aInvalid character, Retry : ");
            gets(s);
        }
        if(strcmp(s,"Y")==0|| strcmp(s,"y")==0)
        {
            MODIFY();
        }
        else if(strcmp(s,"N")==0|| strcmp(s,"n")==0)
        {
            ncount=1;    //as last name does not exist in directory and no modification on arrays
            quit();
        }
    }
}
void swap(customer *a,customer *b)    //swap records in sorting
{
    customer temp= *a;
    *a=*b;
    *b=temp;
}
void SortByLname()
{
    LOAD();
    int i, pass;
    for( pass=0; pass<counter-1; pass++) //using bubble sort
        for(i=0; i<counter-pass-1; i++)
        {
            if(strcmp(records[i].lastname,records[i+1].lastname)==1)  //sorting ascending order of last name
                swap(&records[i],&records[i+1]);
        }
}
void SortByDOB()
{
    LOAD();
    int i, pass;
    float a1,a2;
    for( pass=0; pass<counter-1; pass++)
    {
        for(i=0; i<counter-1-pass; i++)
        {
            a1=(records[i].birthdate.day/365.0)+(records[i].birthdate.month/12.0)+records[i].birthdate.year;
            a2=(records[i+1].birthdate.day/365.0)+(records[i+1].birthdate.month/12.0)+records[i+1].birthdate.year;   //convert the date of birth to age in years then compare
            if(a1>a2)
                swap(&records[i],&records[i+1]);
        }
    }
}
void printDOB()   //print elements sorted by DOB
{
    SortByDOB();
    for(int i=0; i<counter; i++)
    {
        printf("\nRECORD NUMBER %d : \n%s\n%s\n%02d-%02d-%02d\n%s\n%s\n%s\n",i+1,records[i].lastname,records[i].firstname,records[i].birthdate.day,records[i].birthdate.month,records[i].birthdate.year,records[i].address,records[i].phonenumber,records[i].email);
    }
    quit();     //option to save the records sorted in the directory
}
void printLname()
{
    SortByLname();
    for(int i=0; i<counter; i++)
    {
        printf("\nRECORD NUMBER %d : \n%s\n%s\n%02d-%02d-%02d\n%s\n%s\n%s\n",i+1,records[i].lastname,records[i].firstname,records[i].birthdate.day,records[i].birthdate.month,records[i].birthdate.year,records[i].address,records[i].phonenumber,records[i].email);
    }
    quit();
}
void mainmenu()
{
    int pos=1;
    char ch;
    drawframe();
    HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
    ShowConsoleCursor(0);
    do
    {
        SetConsoleTextAttribute(console,15);
        gotoxy(1,1);
        printf("1-Add a record ");
        gotoxy(1,2);
        printf("2-Modify a record ");
        gotoxy(1,3);
        printf("3-Delete a record ");
        gotoxy(1,4);
        printf("4-Print records sorted by date of birth ");
        gotoxy(1,5);
        printf("5-Print records sorted by Last name ");
        gotoxy(1,6);
        printf("6-Search for a record ");  //construct menu
        printf("\n\n");
        switch(pos)
        {
        case 1 :
            SetConsoleTextAttribute(console,240);
            gotoxy(1,1);
            printf("1-Add a record ");
            break;
        case 2:
            SetConsoleTextAttribute(console,240);
            gotoxy(1,2);
            printf("2-Modify a record ");
            break;
        case 3:
            SetConsoleTextAttribute(console,240);
            gotoxy(1,3);
            printf("3-Delete a record ");
            break;
        case 4:
            SetConsoleTextAttribute(console,240);
            gotoxy(1,4);
            printf("4-Print records sorted by date of birth ");
            break;
        case 5:
            SetConsoleTextAttribute(console,240);
            gotoxy(1,5);
            printf("5-Print records sorted by Last name ");
            break;
        case 6:
            SetConsoleTextAttribute(console,240);
            gotoxy(1,6);
            printf("6-Search for a record ");
            break;
        }
        ch=getch();
        if(ch==-32)ch=getch();  //if input is space
        if(ch==72)
        {
            pos--;     //decrement position if input is arrow up
            if(pos==0)pos=6;
        }
        if(ch==80)
        {
            pos++;     //increment position if input is arrow down
            if(pos==7)pos=1;
        }
    }
    while(ch!=13);
    SetConsoleTextAttribute(console,15);
    gotoxy (0,8);
    ShowConsoleCursor(1);
    switch(pos)  //position of cursor corresponding to which task
    {
    case 1:
        ADD();
        break;
    case 2:
        MODIFY();
        break;
    case 3:
        Delete();
        break;
    case 4:
        printDOB();
        break;
    case 5:
        printLname();
        break;
    case 6:
        search_name();
        break;
    }
}
int main()
{
    printf("Welcome to our phonebook!\n---------------------------------------------------------------------------------------------------------\nFor better output layout apply full screen mode, press any key to continue.");
    char q6=getch();
    delay(1);
    system("cls");
    mainmenu();
    return 0;
}
