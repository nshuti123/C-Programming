#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<dirent.h>
#include<time.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct user{ // The credentials of the user will be stored in the structure

    char fullName[50];
    char phoneNumber[12];
    char pinNumber[7];
    char status[20];
    float amount;

};

struct admin{

    char Fullname[50];
    char Username[50];
    char Phonenumber[12];
    char Password[15];

};

struct transfer{

    char Sendername[50];
    char receivername[50];
    char time[50];
    char status[20];
    float amount;
};

void takeinput(char ch[50]){

    fgets(ch,50,stdin);
    ch[strlen(ch)-1]=0;

}

void takephone(char ch[12]){

    fgets(ch,12,stdin);
    ch[strlen(ch)-1]=0;

}

void takepin(char pwd[7]){

    int i;
    char ch;
    while (1)
    {
        ch= getch();

        if(ch == ENTER || ch == TAB){
            pwd[i]='\0';
            break;
        }
        else if(ch == BCKSPC)
        {
            if (i>0)
            {
                i--;
                printf("\b \b");
            }
            
        }
        else{
            pwd[i++]= ch;
            printf("* \b");
        }
    }
    

}

void takepassword(char pwd[12]){

    int i;
    char ch;
    while (1)
    {
        ch= getch();

        if(ch == ENTER || ch == TAB){
            pwd[i]='\0';
            break;
        }
        else if(ch == BCKSPC)
        {
            if (i>0)
            {
                i--;
                printf("\b \b");
            }
            
        }
        else{
            pwd[i++]= ch;
            printf("* \b");
        }
    }
    

}

void signup(){

    FILE *fp;
    struct user user;
    char pinNumber2[7],filename[12];

    system("cls");

    printf("\n\n\t\t ----- Creating a User -----");

    printf("\n\nEnter User Fullname*: \t");
    takeinput(user.fullName);

    printf("Enter User Phone Number*: \t");
    takephone(user.phoneNumber);

    printf("Enter User Pin Number (Input 5 numbers)*: \t");
    takepin(user.pinNumber); 

    printf("\nConfirm User Pin Number*: \t");
    takepin(pinNumber2);

    strcpy(user.status,"Active");

    user.amount = 0;

    if (strcmp(user.pinNumber,pinNumber2)== 0)
    {
        
        strcpy(filename,user.phoneNumber);

        fp= fopen(strcat(filename,".txt"),"w");

        fwrite(&user,sizeof(struct user),1,fp);

        if(fwrite != 0){
            printf("\n\n User Registered successfuly");
        } 
        else{
            printf("\n\nUser is not registrated :(");
        }
    }
    else{
        printf("\n\nYour pin didn't match");
        Beep(750,300);
    }
    
   fclose(fp); 

}

void login(){

    FILE *fp,*dsp;
    int userfound=0;
    char phoneNumber[12],filename[12],name[50];
    char name2[50];
    char pinNumber[7];
    struct user usr,usr1;
    struct transfer rep;
    char cont='y';
    char status[]="Transfer";
    float amount;
    int choice=0;


    printf("\n\n\t\t ----- Welcome Please Login -----");

    printf("\n\nEnter your Phone number:\t");
    takephone(phoneNumber);
    printf("\nEnter your Pin number:\t");
    takepin(pinNumber);

    strcpy(filename,phoneNumber);

    fp = fopen(strcat(filename,".txt"),"r");

    if (fp == NULL)
    {
        printf("\n\n Account doesn't exist :(");
        Beep(800,300);
    }
    else
    {
            
            fread(&usr,sizeof(struct user),1,fp);
        
            fclose(fp);


           if (strcmp(pinNumber,usr.pinNumber) == 0)
           {
               system("cls"); 
             strcpy(name,usr.fullName);

             

                while (cont == 'y')
             {
                
                system("cls");
                printf("\n\n\t\t ----- %s -----",usr.fullName);
                printf("\n\t\t         =========");
                printf("\n\n\n What do you want to do");
                printf("\n\n =========");
                printf("\n\n 1.Check balance inquiry\n 2.Deposit money\n 3.Withdraw money\n 4.Transfer money");
                printf("\n\n Enter your choice:\t");

                scanf("%d",&choice);

                switch (choice)
                {
                case 1:
                    printf("\n|Your balance is: %.2fRwf",usr.amount);
                    break;
                
                case 2:

                        printf("\n\nEnter the amount you want to deposit: ");
                        scanf("%f",&amount);

                        strcpy(usr.fullName,name);

                        usr.amount = usr.amount + amount ; 

                        fp = fopen(filename,"w");
                        fwrite(&usr,sizeof(struct user),1,fp);
                        if (fwrite != 0)
                        {
                            printf("\n\n\t----- Cash was Deposited successfully :)");
                           
                        }
                        else
                        {
                            printf("\n\n\t----- Cash was not Deposited :(");
                        }
                        fclose(fp);
                    break;
                case 3:

                        printf("\n\nEnter the amount you want to withdraw: ");
                        scanf("%f",&amount);

                        strcpy(usr.fullName,name);

                        if (strcmp(usr.status,"Blocked") == 0)
                        {
                            printf("\n\nYour Account is Blocked You can't withdraw money");
                        }
                        else
                        {
                            if(amount > usr.amount)
                            {
                                printf("\n\nInsufficient Balance to withdraw money");
                            }
                            else
                            {
                                usr.amount = usr.amount - amount ;

                                fp = fopen(filename,"w");
                                fwrite(&usr,sizeof(struct user),1,fp);
                                if (fwrite != 0)
                                {
                                    printf("\n\n\t----- Cash withdrew successfully. Amount: %.2f Rwf",amount);
                                }
                                else
                                {
                                    printf("\n\n\t----- Sorry something went wrong :(");
                                }
                            }
                        }

                        fclose(fp);
                    break;
                case 4:
                    printf("\n\nEnter the phone number you want to transfer money: ");
                    scanf("%s",phoneNumber);
                    printf("\n Enter the amount you want to transfer: ");
                    scanf("%f",&amount);

                    strcpy(filename,phoneNumber);

                    fp= fopen(strcat(filename,".txt"),"r");
                    // strcpy(name2,usr1.fullName);

                    fread(&usr1,sizeof(struct user),1,fp);
                    fclose(fp);

                    if (fp == 0) // put the condition here Block
                    {
                        printf("\n\nAccount doesnot exist");
                    }
                    else
                    {
                        if (amount > usr.amount)
                        {
                            printf("\n\nInsufficient Balance");
                        }
                        else{
                            
                            

                            strcpy(name2,usr1.fullName);

                            fp = fopen(filename,"w");

                            strcpy(usr1.fullName,name2);
                            usr1.amount = usr1.amount + amount;

                            fwrite(&usr1,sizeof(struct user),1,fp);
                            fclose(fp);

                            if (fwrite != 0)
                            {
                                 printf("\n\nYou have successfully transfered %.2fRwf to %s",amount,usr1.phoneNumber);
                                 strcpy(filename,usr.phoneNumber);
                                 fp = fopen(strcat(filename,".txt"),"w");
                                 strcpy(usr.fullName,name);
                                 usr.amount = usr.amount - amount;

                                 fwrite(&usr,sizeof(struct user),1,fp);
                                 fclose(fp);
                                 }
                            
                                dsp = fopen("report.dat","a+");

                                time_t now = time(NULL);
                                char* str_time = ctime(&now);

                                strcpy(rep.Sendername,usr.fullName);
                                strcpy(rep.receivername,usr1.fullName);
                                rep.amount = amount;
                                strcpy(rep.status,status);
                                strcpy(rep.time,str_time);

                                fwrite(&rep,sizeof(struct transfer),1,dsp);

                                fclose(dsp);
                        }
                        
                    }
                    

                    break;
                default:
                    printf("\n Invalid Input!! Try again...");
                    break;
                }

                 printf("\n\nDo you want to continue the transaction [y/n]: ");
                 scanf("%s",&cont);

              }
                

                printf("\n\nThank you for using MTN Mobile Money :)");
                

            }
            else{
                printf("\n\nYour Pin Number is incorect :( ");
                Beep(750,300);
            }

        
    }
    
    


    
fclose(fp);

}

void signupAdmin(){

    FILE *fp;
    struct admin admin;
    char password2[15];

    printf("\n\n\t\t ----- Creating an Admin -----");

    printf("\n\nEnter Admin Fullname*: \t");
    takeinput(admin.Fullname);

    printf("Enter  Admin username*: \t");
    takeinput(admin.Username);

    printf("Enter Admin Phone Number*: \t");
    takephone(admin.Phonenumber);

    printf("Enter Admin Password *: \t");
    takepassword(admin.Password);

    printf("\nConfirm Admin Password*: \t");
    takepassword(password2);

    if (strcmp(admin.Password,password2)==0)
    {
        fp= fopen("admin.dat","a+");
        fwrite(&admin,sizeof(struct admin),1,fp);
        if (fwrite != 0)
        {
            printf("\n\nThe user is registrated succesfully :) ");
            // printf("\n\nThank you for using MTN Mobile Money :)");
        }
        else{

            printf("\n\nThe user is not registered :( ");
        }
    }
    else{
        printf("\n\nThe password didn't match try again later...");
        Beep(750,300);
    }
    
    fclose(fp);

}

void display(){

        FILE *output_file,*input_file;
        DIR *dir;
        struct dirent *entry;
        struct user user;
        char direct_path[]="E:\STUDIES\Semester Three\C Programming Fundamentals\C Programming project - Mobile Money Transaction Handling";
        char output_file_name[]="users.txt";
        char extension[]=".txt";

        output_file = fopen(output_file_name,"w");

        if (output_file == NULL)
        {
            printf("\n\nUnable to open File :(");
            Beep(750,300);
        }
       
       dir = opendir(direct_path);

       if (dir == NULL)
       {
        printf("\n\nUnable to open the Directory :(");
       }

            while ((entry = readdir(dir)) != NULL)
            {
                    if (strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
                    {
                       continue;
                    }

                    if (strstr(entry->d_name,extension) == NULL)
                    {
                        continue;
                    }
                   
                        char input_file_path[1000];
                        sprintf(input_file_path, "%s%s", direct_path, entry->d_name);

                        input_file = fopen(input_file_path,"r");

                        if (input_file == NULL)
                        {
                            printf("\n\nUnable to open the file %s:(",input_file_path);
                            continue;
                        }

                        
                            int c;
                            while ((c = fgetc(input_file)) != EOF)
                            {
                                fputc(c,output_file);
                            }

                            fclose(input_file);
                                  
                    
            }
            

       closedir(dir);
       fclose(output_file);


       output_file = fopen(output_file_name,"r");
       int i=1;

       printf("\n\n\t ----- LIST OF USERS -----");
        printf("\n\t       =============");

        printf("\n\nN0\tFull Name\t\tPhone Number\tAmount\t\tStatus");
        printf("\n==\t=========\t\t============\t======\t\t======");
        while(fread(&user,sizeof(struct user),1,output_file))
        {

         printf("\n\n%i\t%s\t\t%s\t%.1fRwf\t%s",i,user.fullName,user.phoneNumber,user.amount,user.status);
            i++;
        }
        
        fclose(output_file);
        

}

void search(){

    FILE *output_file;

        struct user user;
        char output_file_name[]="users.txt";

       output_file = fopen(output_file_name,"r");
       char a[11];
       int userfound=0;

        printf("\n\n\t ----- Search Option -----");
        printf("\n\t       =============");
        printf("\n\nEnter user phone number: ");
        scanf("%s",&a);

        printf("\n\n\t ----- USER -----");
        printf("\n\t       ====");

        printf("\n\nFull Name\t\tPhone Number\tAmount\t\tStatus");
        printf("\n=========\t\t============\t======\t\t======");
        
        while (fread(&user,sizeof(struct user),1,output_file))
        {
            if (strcmp(user.phoneNumber,a) == 0)
            {
                userfound = 1;
               printf("\n\n%s\t\t%s\t%.1fRwf\t%s",user.fullName,user.phoneNumber,user.amount,user.status);

            }
            
        }

        if (userfound == 0)
        {
            printf("\n\nUser not found !!");
            Beep(800,300);
        }
    


        fclose(output_file);

}

void report(){

    FILE *dsp;
    struct transfer rep;
        dsp = fopen("report.dat","r");
        
        int i=1;

       printf("\n\n\t ----- Report Of Transactions -----");
       printf("\n\t       ======================");

        printf("\n\nN0\tSender Name\tStatus\t\tReceiver Name\tAmount\t\tTime");
        printf("\n==\t===========\t======\t\t=============\t======\t\t====");
        while(fread(&rep,sizeof(struct transfer),1,dsp))
        {

         printf("\n\n%i\t%s\t%s\t%s\t%.1fRwf %s",i,rep.Sendername,rep.status,rep.receivername,rep.amount,rep.time);
            i++;
        }
        

}

void blockUser(){

        FILE *output_file,*input_file;
        DIR *dir;
        struct dirent *entry;
        struct user user;
        char direct_path[]="E:\STUDIES\Semester Three\C Programming Fundamentals\C Programming project - Mobile Money Transaction Handling";
        char extension[]=".txt";

        char phoneNumber[12];
        

        system("cls");



        printf("\n\n Enter The number Of the Account you want to Block: ");
        scanf("%s",phoneNumber);
       
       dir = opendir(direct_path);

       if (dir == NULL)
       {
        printf("\n\nUnable to open the Directory :(");
       }

            while ((entry = readdir(dir)) != NULL)
            {
                    if (strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
                    {
                       continue;
                    }

                    if (strstr(entry->d_name,extension) == NULL)
                    {
                        continue;
                    }
                   
                        char input_file_path[1000];
                        sprintf(input_file_path, "%s%s", direct_path, entry->d_name);

            if (strstr(input_file_path,phoneNumber) != NULL)
                        {
                            input_file = fopen(input_file_path,"r");
                            fread(&user,sizeof(struct user),1,input_file);
                            fclose(input_file);

                            input_file = fopen(input_file_path,"w");

                            strcpy(user.status,"Blocked");
                            fwrite(&user,sizeof(struct user),1,input_file);

                            printf("\n\nAccount with Phone Number %s is successfuly %s",user.phoneNumber,user.status);
                            fclose(input_file);
                           break;
                        }
                                  
                    
            }
          

       closedir(dir);

}

void unblockUser(){

        FILE *output_file,*input_file;
        DIR *dir;
        struct dirent *entry;
        struct user user;
        char direct_path[]="E:\STUDIES\Semester Three\C Programming Fundamentals\C Programming project - Mobile Money Transaction Handling";
        char extension[]=".txt";

        char phoneNumber[12];
        

        system("cls");



        printf("\n\n Enter The number Of the Account you want to Unblock: ");
        scanf("%s",phoneNumber);
       
       dir = opendir(direct_path);

       if (dir == NULL)
       {
        printf("\n\nUnable to open the Directory :(");
       }

            while ((entry = readdir(dir)) != NULL)
            {
                    if (strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
                    {
                       continue;
                    }

                    if (strstr(entry->d_name,extension) == NULL)
                    {
                        continue;
                    }
                   
                        char input_file_path[1000];
                        sprintf(input_file_path, "%s%s", direct_path, entry->d_name);

            if (strstr(input_file_path,phoneNumber) != NULL)
                        {
                            input_file = fopen(input_file_path,"r");
                            fread(&user,sizeof(struct user),1,input_file);
                            fclose(input_file);

                            input_file = fopen(input_file_path,"w");

                            strcpy(user.status,"Active");
                            fwrite(&user,sizeof(struct user),1,input_file);

                            printf("\n\nAccount with Phone Number %s is successfully Activated",user.phoneNumber,user.status);
                            fclose(input_file);
                           break;
                        }
                                  
                    
            }
          

       closedir(dir);

}


void loginAdmin()
{

    FILE *fp;
    int userfound=0;
    char username[50],password[15];
    struct admin admin;
    struct user user;
    char cont='y';
    int choice;


    printf("\n\n\t\t ----- Welcome Please Login -----");

    printf("\n\nEnter your Username:\t");
    takephone(username);
    printf("\nEnter your Password:\t");
    takepassword(password);

    fp = fopen("admin.dat","r");
    
     while (fread(&admin,sizeof(struct admin),1,fp))
        {
                if(strcmp(admin.Username,username) == 0)
                {
                    if (strcmp(admin.Password,password) == 0)
                    {
                        
                        while (cont == 'y')
                        {
                            system("cls");
                            printf("\n\n\t ----- Welcome admin %s",admin.Fullname);


                            printf("\n\n MainMenu");
                            printf("\n ========");
                            printf("\n\n 1.Create an Administrator\n 2.Create a User\n 3.Display user's record\n 4.Search a User\n 5.Report of transaction\n 6.Block Users\n 7.Unblock Users\n\nChoose your Option:\t");
                            scanf("%d",&choice);
                            fgetc(stdin);

                            switch(choice)
                                {
                                    case 1:
                                        signupAdmin();
                                        break;
                                    case 2:
                                        signup();
                                        break;
                                    case 3:
                                        display();
                                        break;
                                    case 4:
                                        search();
                                        break;
                                    case 5:
                                        report();
                                        break;
                                    case 6:
                                        blockUser();
                                        break;
                                    case 7:
                                        unblockUser();
                                        break;     
                                    default:
                                        printf("\n\nWrong choice! Choose again...");
                                        break;

                                }
                            
                                
                            printf("\n\n\nDo you want to continue using the sytem [y/n]: ");
                            scanf("%s",&cont);

                            printf("\n\n\t ----- MTN Mobile Money:)");

                        }
                        
                    }
                    else
                        {
                            printf("\n\nYour password is incorrect try again...");
                            Beep(750,300);
                        }
                         userfound = 1;
                }
                    
        
        }
            
          if (userfound == 0)

                        {
                            printf("\n\nUser not found !!");
                            Beep(750,300);
                        }

            
fclose(fp);

    
}

int main(){

    int choice;

printf("\n\n\t\t\t -------- Welcome To MTN Mobile Money Transaction System -------- \n\n");
    
printf("\n\n MainMenu");
printf("\n ========");
printf("\n\n 1.Login as an Administrator\n 2.Login as a User\n 3.Exit\n\nChoose your Option:\t");
scanf("%d",&choice);
fgetc(stdin);

switch(choice)
        {
        case 1:
            loginAdmin();
            break;
        case 2:
            login();
            break;
        case 3:
            printf("\n\n MTN Mobile Money :)");
            break;

        default:
            printf("\n\nWrong choice! Choose again...");
        }

printf("\n\n\n\n");
    return 0;
}
