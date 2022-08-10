#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

#define buffer 30

int optionType;
int menuOption;

int selectOption(void);
int createAccount(void);
int logIn(void);
void mainMenu(void);
void transactionMenu(void);
void logOut(void);
   

struct savingsRecord
    {
        char fullName[buffer];
        char email[buffer];
        char passWord[buffer];
        float income;
        float expense;
        char date[11];
        char description[100];
        int mortgage;
        int homeUtilities;
        int transportation;
        int groceries;
        int leisureEntertainment;
        int salary;
        int retirement;
};


struct savingsRecord sRecord;


//Main Function
int main()
{
    system("clear");
    printf("\t\t\t\t-------Expense Tracker System-------\n\n");
    printf("Please choose an option below.\n\n");
    printf("1. Create Account\n");
    printf("2. Login\n");
    printf("3. Logout\n\n");
    
    while(1)
    {
        int ok = 0;
        int choice = selectOption();
        
        if(choice == 1)
        {
            while (ok == 0)
            {
                ok = createAccount();
                {
                    while (1)
                    {
                        logIn();
                        mainMenu();
                    }
                }
            }
            ok = 0;
        }
        
        else if(choice == 2)
        {
            while (ok == 0)
            {
                ok = logIn();
                {
                    while (1)
                    {
                        mainMenu();
                    }
                }
            }
            ok = 0;
        }
        
        else if(choice == 3)
        {
            printf("Bye Bye, see you later!!\n");
            break;
        }
       
        else
        {
            printf("\nWrong input, please try again!\n\n");
        }
    }
    return 0;
}


int selectOption(void)
{
    printf("Choose between choices 1,2, or 3: ");
    scanf("%d",&optionType);
    return optionType;
}


int createAccount(void)
{
    char fname[buffer];
    char email[buffer];
    char pword[buffer];
    FILE *fp;
    
    printf("\t\t\t\t ---------------------------------\n");
    printf("\t\t\t\t   Welcome To User Registration\n");
    printf("\t\t\t\t ---------------------------------\n");
    
    fp = fopen("sRecord.txt", "w");
    
    if (fp == NULL)
    {
        printf("Error!");
        exit(1);
    }
    
    printf("Enter your full name to get started: ");
    scanf(" %[^\n]", fname);
    printf("\nEnter your email address: ");
    scanf(" %[^\n]", email);
    printf("\nCreate a password: ");
    scanf(" %[^\n]", pword);
 
    fprintf(fp, "%s\n%s\n%s\n", fname, email, pword);
    rewind(fp);
    fscanf(fp, "%[^\n] %[^\n] %[^\n]", fname, email, pword);
    
    strcpy(sRecord.fullName, fname);
    strcpy(sRecord.email, email);
    strcpy(sRecord.passWord, pword);

    printf("\nCongulations, Registration Completed Successfully!!!\n");
    fclose(fp);
    
    return 0;
}


int logIn(void)
{
    char email[buffer];
    char pword[buffer];
    FILE *fp;
    
    fp = fopen("sRecord.txt","r");
    
    if (fp == NULL)
    {
        fputs("Error at opening File!",fp);
        exit(1);
    }
    
    printf("\t\t\t\t ---------------------------------");
    printf("\n\t\t\t\t\t   Welcome To User Login\n");
    printf("\t\t\t\t ---------------------------------");
    printf("\nPlease Enter your login credentials below\n\n");
   
    printf("\nEnter Email: ");
    scanf(" %[^\n]", email);
    printf("\nEnter Password: ");
    scanf(" %[^\n]", pword);
        
    while(fread(&sRecord, sizeof(sRecord), 1, fp))
    {
        if(strcmp(email,sRecord.email) == 0 && strcmp(pword,sRecord.passWord) == 0)
        {
            printf("\nSuccessful Login\n");
            break;
        }
        else
        {
            printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
        }
    }
    fclose(fp);
    
    return 0;
}

void mainMenu()
{
    int menuOption;
    FILE *fp;
    
    system("clear");
    printf("\n\n\n");
    printf("\t\t\t\t\t\t\t-------------------------------------");
    printf("\n\t\t\t\t\t\t\t\t\t * Expense Tracker System *\n");
    printf("\t\t\t\t\t\t\t-------------------------------------");
    
    fp = fopen("sRecord.txt", "r");
    
    printf("\n\n\nWelcome back, %s\n\n\n\n", fgets(sRecord.fullName, buffer, fp));
    fclose(fp);
    
    printf("Please select a menu option below:\n\n");
    printf("1. Transaction Menu\n\n");
    printf("2. Log Out Account\n\n");
    
    printf("Enter your choice: ");
    scanf("%d", &menuOption);
    
    while (1)
    {
        if(menuOption == 1)
        {
            transactionMenu();
        }
        else if(menuOption == 2)
        {
            logOut();
            break;
        }
        else
        {
            printf("\n\tWrong input. Try again!\n");
        }
    }
    
    return;
}
    
    
void transactionMenu()
{
    int choice;
    int category;
    float income = 0, expense = 0;
    FILE *fp;
    
    printf("\n1: Add Income\n2: Add Expense\n\n");
    printf("Please select an option: ");
    scanf("%d", &choice);
    
    fp = fopen("sRecord.txt", "a+");
    
    if(fp == NULL)
    {
        printf("Cannot open file at this time!");
        exit(1);
    }
    
    printf("\n\nEnter Date (DD/MM/YYYY): ");
    scanf(" %[^\n]", sRecord.date);
    fprintf(fp, "\nDate: %s", sRecord.date);
    
    printf("\nSelect category:\n1.Mortgage\n2.Home & Utilities\n3.Transportation\n4.Groceries\n5.Leisure & Entertainment\n6.Salary\n7.Retirement\n\n");
    printf("Enter choice here: ");
    scanf("%d", &category);
    
    if(category == 1)
    {
        fprintf(fp, "\n%d for Mortgage", sRecord.mortgage);
    }
    else if(category == 2)
    {
        fprintf(fp, "\n%d for Home & Utilities", sRecord.homeUtilities);
    }
    else if(category == 3)
    {
        fprintf(fp, "\n%d for Transportation", sRecord.transportation);
    }
    else if(category == 4)
    {
        fprintf(fp, "\n%d for Groceries", sRecord.groceries);
    }
    else if(category == 5)
    {
        fprintf(fp, "\n%d for Leisure & Entertainment", sRecord.leisureEntertainment);
    }
    else if (category == 6)
    {
        fprintf(fp, "\n%d for Salary", sRecord.salary);
    }
    else if (category == 7)
    {
        fprintf(fp, "\n%d for Retirement", sRecord.retirement);
    }
    
    printf("\nEnter description (100 characters max.): ");
    scanf(" %[^\n]", sRecord.description);
    fprintf(fp, "\nDescription: %s", sRecord.description);
    
    printf("\nEnter transaction amount in USD: ");
    
    if(choice == 1)
    {
        scanf("%f", &sRecord.income);
        expense = 0;
            
        fprintf(fp, "Income: %f", sRecord.income);
            
        printf("\nYour income information was added successfully:\n %s\n %d\n %s\n %f\n\n", sRecord.date, sRecord.salary, sRecord.description, sRecord.income);
        
        mainMenu();
    }
    else if(choice == 2)
    {
        scanf("%f", &sRecord.expense);
        income = 0;
            
        fprintf(fp, "Expense: %f", sRecord.expense);

        printf("\nYour expense information was added successfully:\n %s\n %d\n %s\n %f\n\n", sRecord.date, sRecord.mortgage, sRecord.description, sRecord.expense);
        
        mainMenu();
    }
    else
    {
        printf("Incorrect input, please try again!");
    }
    
    fclose(fp);
    
}

void logOut()
{
    printf("Bye Bye, see you later!!");
    return;
}
           
