#include<stdio.h>
#include<string.h>
#include<conio.h>

struct person
{
    char name[50];
    int age;
    char result_db[50];
    char result_bp[50];
};

void takeinput(char c[50])
{
    fgets(c,50,stdin);
    c[strlen(c)-1]=0;
}

void insert()
{
    FILE *fp;
    struct person p;

    printf("\n\n\tInsert Form");
    printf("\n\t==========");

    printf("\n\nEnter Patient Name: ");
    takeinput(p.name);
    printf("\nEnter Patient Age: ");
    scanf("%d",&p.age);
    printf("\nEnter Patient Result for Diabetes: ");
    scanf("%s",p.result_db);
    printf("\nEnter Patient Result for Blood Pressure: ");
    scanf("%s",p.result_bp);

    fp = fopen("patients.txt","a+");

    if (fp ==NULL)
    {
        printf("\n\nFile does't exist");
    }
    else
    {
        fwrite(&p,sizeof(struct person),1,fp);

        if (fwrite !=0 )
        {
            printf("\n\nPatient Recorded");
        }
        else
        {
            printf("\n\nPatient not recorded");
        }
        
    }

    fclose(fp);
    
}

void display()
{
    FILE *fp;
    struct person p;
    int i=1;

    fp = fopen("patients.txt","r");

    printf("\n\n\tList Of Patients");
    printf("\n\t================");
    
    printf("\n\nN0\tBlood Pressure\tDiabetes\tPatient Age\tPatient Name");
    printf("\n==\t==============\t========\t===========\t============");

    while (fread(&p,sizeof(struct person),1,fp))
    {
        printf("\n\n%d\t%s\t%s\t%d\t\t%s",i,p.result_bp,p.result_db,p.age,p.name);
        i++;
    }
    
    
    fclose(fp);
}
void s_disease()
{
    FILE *fp;
    struct person p;
    int i=1;

    fp = fopen("patients.txt","r");

    printf("\n\n\tList Of Patients with One single Disease");
    printf("\n\t========================================");
    
    printf("\n\nN0\tBlood Pressure\tDiabetes\tPatient Age\tPatient Name");
    printf("\n==\t==============\t========\t===========\t============");

    while (fread(&p,sizeof(struct person),1,fp))
    {
        if (strcmp(p.result_bp,"Negative") == 0 && strcmp(p.result_db,"Positive") == 0 || strcmp(p.result_db,"Negative") == 0 && strcmp(p.result_bp,"Positive") == 0)
        {
            printf("\n\n%d\t%s\t%s\t%d\t\t%s",i,p.result_bp,p.result_db,p.age,p.name);
            i++;
        }
        
    }
    
    
    fclose(fp);    
}

int main()
{
    int c;
    char ch='y';

    while (ch == 'y')
    {
        printf("\n\n\t\tWelcome To Rwanda Biomedical Center Non Communicable Diseases");
        printf("\n\t\t==========================================================");

        printf("\n\nMain Menu");
        printf("\n=========");

        printf("\n\n1. Record Patient\n2. View Patient\n3. View Patient with a single disease\n\nEnter your choice: ");
        scanf("%d",&c);
        fgetc(stdin);

        switch (c)
        {
        case 1:
            insert();
            break;
         case 2:
            display();
            break;
         case 3:
            s_disease();
            break;
        default:
            printf("\n\nInvalid input try again...");
            break;
        }

        printf("\n\nDo you want to continue using the system[y/n] ");
        scanf("%s",&ch);
    }

    printf("\n\nGoodbyee :))");
    printf("\n\n");
    
    return 0;
}