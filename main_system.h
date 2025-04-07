#include<iostream>
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<conio.h>

using namespace std;

void passgenarater(char pass[]);

class Bank
{
public:
    int selection;
    void MainMenu();

private:
    void Account();
    void Create_an_account();
    void Search_an_account();
    void All_Customars_account();
    void Delete_an_account();
    void update_an_account();

    void Transactions();
    void Deposit_Amount();
    void Transfer_Amount();
    void Withdraw_Amount();

    struct account_info
    {
        int deposit_amount;
        char first_name[20];
        char last_name[20];
        char account_number[30];
        char phone_no[20];
        char password[30];
        char gender[10];
        char married[10];
        char address[100];
        char district[20];
        char country[30];

        struct
        {
            int day;
            int month;
            int year;
        } birth;
    };

    struct all_user
    {
        char account_number[30];
    } customers;

};

void Bank::MainMenu()
{
    cout<<"================================== Main Menu ==================================\n"<<endl;
    cout<<"\t\t1.Account"<<endl<<endl<<"\t\t2.Transactions"<<endl<<endl<<"\t\t3.Exit"<<endl<<endl;
menu:
    cout<<"Choose An Option From 1-to-3: ";
    cin>>selection;

    if(selection == 1)
    {
        Account();
    }
    else if(selection == 2)
    {
        Transactions();
    }
    else if(selection == 3)
    {
        exit(0);
    }
    else
    {
        printf("\nYou Enter Wrong Number. Please Enter Correctly\n\n\a");
        goto menu;
    }
};

void Bank::Account()
{
    cout<<"\n================================== Account ===================================\n"<<endl;
    cout<<"\n\t\t1.Create an account\n";
    cout<<"\n\t\t2.Search an account\n";
    cout<<"\n\t\t3.All Customer's account\n";
    cout<<"\n\t\t4.Delete an account\n";
    cout<<"\n\t\t5.Update an account\n";
    cout<<"\n\t\t6.Main Menu\n";
account:
    cout<<"\nChoose An Option From 1-to-6: ";
    cin>>selection;

    if(selection == 1)
    {
        Create_an_account();
    }
    else if(selection == 2)
    {
        Search_an_account();
    }
    else if(selection == 3)
    {
        All_Customars_account();
    }
    else if(selection == 4)
    {
        Delete_an_account();
    }
    else if(selection == 5)
    {
        update_an_account();
    }
    else if(selection == 6)
    {
        MainMenu();
    }
    else
    {
        printf("\nYou Enter Wrong Number. Please Enter Correctly\n\a");
        goto account;
    }
};

void Bank::Create_an_account()
{
    account_info user;
    char genderck;
    char re_password[30];
    char path[40] = "data_base\\";
    char customers_path[40] = "data_base\\all_customers.txt";
    FILE *fp;

    printf("\nCreate an account:");
    printf("\n\tFirst Name: ");
    scanf("%s",user.first_name);

    printf("\tLast Name: ");
    scanf("%s",user.last_name);

    cout<<endl;

accunt_number:

    printf("\tAccount Number: ");
    scanf("%s",user.account_number);

    strcat(path,user.account_number);
    strcat(path,".bin");

    fp = fopen(path,"rb");
    if(fp != NULL)
    {
        printf("\n\aThis account number is available. Please enter another account number.\n\n");
        strcpy(path,"data_base\\");
        fclose(fp);
        goto accunt_number;
    }
    fclose(fp);

    strcpy(customers.account_number,user.account_number);

    cout<<endl;

password:

    printf("\tEnter Password: ");
    passgenarater(user.password);
    printf("\n\tRepeat The Password: ");
    passgenarater(re_password);

    if((strcmp(user.password,re_password)) != 0)
    {
        printf("\n\n\aPassword are not match. Please enter password again.\n\n");
        goto password;
    }

    cout<<endl;

    printf("\n\tDeposit Amount: ");
    scanf("%d",&user.deposit_amount);

    printf("\n\tEnter birth day:\n");
    printf("\t\tDay: ");
    scanf("%d",&user.birth.day);
    printf("\t\tMonth: ");
    scanf("%d",&user.birth.month);
    printf("\t\tYear: ");
    scanf("%d",&user.birth.year);

    cout<<endl;

    scanf("%*c");

    printf("\tPhone Number: ");
    gets(user.phone_no);

    cout<<endl;

    printf("\tSelect Gender (if male press m else press f): ");
    scanf("%s",&genderck);
    if(genderck == 'm' || genderck == 'M')
    {
        strcpy(user.gender,"Male");
    }
    else
    {
        strcpy(user.gender,"Female");
    }

    cout<<endl;

    cout<<"\tSelect:"<<endl<<"\t\t1.Married"<<endl<<"\t\t2.Unmarried"<<endl;
    printf("\tEnter 1 or 2: ");
    scanf("%d",&selection);

    if(selection == 1)
    {
        strcpy(user.married,"Married");
    }
    else if(selection == 2)
    {
        strcpy(user.married,"Unmarried");
    }

    cout<<endl;

    scanf("%*c");

    printf("\tAddress: ");
    gets(user.address);
    cout<<endl;
    printf("\tDistrict: ");
    gets(user.district);
    cout<<endl;
    printf("\tCountry: ");
    gets(user.country);

    fp = fopen(path,"wb");
    fwrite(&user,sizeof(user),1,fp);
    fclose(fp);

    fp = fopen(customers_path,"a");
    fprintf(fp,"%s\n",customers.account_number);
    fclose(fp);

    printf("\n\tYour Account Is Created. Thank You\n");

    cout<<endl;

    cout<<"Press '0' to go the Main Menu: ";
    scanf("%d",&selection);

    cout<<endl;

    if(selection == 0)
    {
        MainMenu();
    }
};

void Bank::Search_an_account()
{
    FILE *fp;
    char path[40]="data_base\\";
    char userck[30];
    char passwordck[30];
    account_info exist_user;
    printf("\nSearch an account:\n");
user_pass:

    printf("\tAccount Number: ");
    scanf("%s",userck);
    printf("\tPassword: ");
    passgenarater(passwordck);

    strcat(path,userck);
    strcat(path,".bin");

    fp = fopen(path,"rb");
    if( fp != NULL)
    {
        fread(&exist_user,sizeof(exist_user),1,fp);
    }
    else
    {
        printf("\n\n\aYou enter wrong account number. Please enter correctly.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass;
    }
    fclose(fp);

    if(strcmp(passwordck,exist_user.password) == 0)
    {
        printf("\n\n");
        printf("\tName: %s %s\n",exist_user.first_name,exist_user.last_name);
        printf("\tAccount Number: %s\n",exist_user.account_number);
        printf("\tDeposit Amount: %dTk\n",exist_user.deposit_amount);
        printf("\tDate of Birth (dd/mm/yy): %d/%d/%d\n",exist_user.birth.day,exist_user.birth.month,exist_user.birth.year);
        printf("\tGender: %s\n",exist_user.gender);
        printf("\tPhone Number: %s\n",exist_user.phone_no);
        printf("\tAddress: %s, %s, %s\n",exist_user.address,exist_user.district,exist_user.country);
        printf("\n********************************************************************************\n");
    }
    else
    {
        printf("\n\n\aPassword is wrong. Enter The password again.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass;
    }

    cout<<"Press '0' to go the Main Menu: ";
    cin>>selection;

    cout<<endl;

    if(selection == 0)
    {
        MainMenu();
    }
};

void Bank::All_Customars_account()
{
    FILE *fp;
    FILE *account;
    account_info all_customers;
    int i = 0;
    char all_account_path[40] = "data_base\\all_customers.txt";
    char path[40] = "data_base\\";
    char arr[20];
    char ch;
    char name[30];

    cout<<"\n\t\t\t--------------------------------\n";
    cout<<"\t\t\t List Of All Customer's Acoount \n";
    cout<<"\t\t\t--------------------------------\n\n";
    cout<<"\t   Account Holder Name"<<"\t "<<"Account Number"<<"\t    "<<"Deposit Ammount\n";
    cout<<"\t==============================================================\n\n";

    fp = fopen(all_account_path,"r");

    if(fp == NULL)
    {
        printf("Fail\n");
    }
    while(1)
    {

        ch = fgetc(fp);

        if(ch != '\n')
        {
            arr[i++] = ch;
        }

        if ( ch == EOF )
        {
            break ;
        }

        if(ch == '\n')
        {
            arr[i] = '\0';
            strcat(path,arr);
            strcat(path,".bin");
            account = fopen(path,"rb");

            if(account == NULL)
            {
                fclose(account);
                strcpy(path,"data_base\\");
                i = 0;
                continue;
            }

            fread(&all_customers,sizeof(all_customers),1,account);

            strcpy(name,all_customers.first_name);
            strcat(name," ");
            strcat(name,all_customers.last_name);
            printf("\t%20s\t%13s\t%17dTk\n",name,all_customers.account_number,all_customers.deposit_amount);

            fclose(account);

            strcpy(path,"data_base\\");
            i = 0;
        }

    }

    fclose(fp);

    cout<<"\nPress '0' to go the Main Menu: ";
    cin>>selection;
    if(selection == 0)
    {
        MainMenu();
    }
};

void Bank::Delete_an_account()
{
    FILE *fp;
    char account_number[30];
    char userck[30];
    char passwordck[30];
    char path[40] = "data_base\\";
    account_info exist_user;

user_pass_del:

    printf("\n\t Enter The Account Number: ");
    scanf("%s",account_number);
    printf("\t Enter The Password: ");
    passgenarater(passwordck);

    strcat(path,account_number);
    strcat(path,".bin");

    fp = fopen(path,"rb");
    if( fp != NULL)
    {
        fread(&exist_user,sizeof(exist_user),1,fp);
    }
    else
    {
        printf("\n\n\aYou enter wrong account number. Please enter correctly.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass_del;
    }
    fclose(fp);

    if(strcmp(passwordck,exist_user.password) == 0)
    {
        remove(path);
        printf("\n\nSuccessfully Delete The Account\n\n");
        printf("\n********************************************************************************\n");
    }
    else
    {
        printf("\n\n\aPassword is wrong. Enter The password again.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass_del;
    }

    cout<<"\nPress '0' to go the Main Menu: ";
    cin>>selection;
    if(selection == 0)
    {
        MainMenu();
    }
};

void Bank::update_an_account()
{
    FILE *fp;
    char path[40]="data_base\\";
    char userck[30];
    char passwordck[30];
    char genderck;
    char re_password[30];
    account_info exist_user,user;
    printf("\nSearch an account:\n");
user_pass:

    printf("\tAccount Number: ");
    scanf("%s",userck);
    printf("\tPassword: ");
    passgenarater(passwordck);

    strcat(path,userck);
    strcat(path,".bin");

    fp = fopen(path,"rb");
    if( fp != NULL)
    {
        fread(&exist_user,sizeof(exist_user),1,fp);
    }
    else
    {
        printf("\n\n\aYou enter wrong account number. Please enter correctly.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass;
    }
    fclose(fp);

    cout<<endl;

    if(strcmp(passwordck,exist_user.password) == 0)
    {
        fp = fopen(path,"wb");

        printf("\n\tFirst Name: ");
        scanf("%s",user.first_name);

        printf("\tLast Name: ");
        scanf("%s",user.last_name);

        cout<<endl;

        strcpy(user.account_number,userck);

password:

        printf("\tEnter Password: ");
        passgenarater(user.password);
        printf("\n\tRepeat The Password: ");
        passgenarater(re_password);

        if((strcmp(user.password,re_password)) != 0)
        {
            printf("\n\n\aPassword are not match. Please enter password again.\n\n");
            goto password;
        }

        cout<<endl;

        printf("\n\tDeposit Amount: ");
        scanf("%d",&user.deposit_amount);

        printf("\n\tEnter birth day:\n");
        printf("\t\tDay: ");
        scanf("%d",&user.birth.day);
        printf("\t\tMonth: ");
        scanf("%d",&user.birth.month);
        printf("\t\tYear: ");
        scanf("%d",&user.birth.year);

        cout<<endl;

        scanf("%*c");

        printf("\tPhone Number: ");
        gets(user.phone_no);

        cout<<endl;

        printf("\tSelect Gender (if male press m else press f): ");
        scanf("%s",&genderck);
        if(genderck == 'm' || genderck == 'M')
        {
            strcpy(user.gender,"Male");
        }
        else
        {
            strcpy(user.gender,"Female");
        }

        cout<<endl;

        cout<<"\tSelect:"<<endl<<"\t\t1.Married"<<endl<<"\t\t2.Unmarried"<<endl;
        printf("\tEnter 1 or 2: ");
        scanf("%d",&selection);

        if(selection == 1)
        {
            strcpy(user.married,"Married");
        }
        else if(selection == 2)
        {
            strcpy(user.married,"Unmarried");
        }

        cout<<endl;

        scanf("%*c");

        printf("\tAddress: ");
        gets(user.address);
        cout<<endl;
        printf("\tDistrict: ");
        gets(user.district);
        cout<<endl;
        printf("\tCountry: ");
        gets(user.country);

        fwrite(&user,sizeof(user),1,fp);

        fclose(fp);
    }
    else
    {
        printf("\n\n\aPassword is wrong. Enter The password again.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass;
    }

    cout<<"Press '0' to go the Main Menu: ";
    cin>>selection;
    if(selection == 0)
    {
        MainMenu();
    }
};


void Bank::Transactions()
{
    cout<<"\n================================ Transactions =================================\n"<<endl;
    cout<<"\n\t\t1.Deposit Amount\n";
    cout<<"\n\t\t2.Withdraw Amount\n";
    cout<<"\n\t\t3.Transfer Amount\n";
    cout<<"\n\t\t4.Main Menu\n";
transactions:
    cout<<"\nChoose An Option From 1-to-4: ";
    cin>>selection;

    if(selection == 1)
    {
        Deposit_Amount();
    }
    else if(selection == 2)
    {
        Withdraw_Amount();
    }
    else if(selection == 3)
    {
        Transfer_Amount();
    }
    else if(selection == 4)
    {
        MainMenu();
    }
    else
    {
        printf("\nYou Enter Wrong Number. Please Enter Correctly\n\a");
        goto transactions;
    }

};

void Bank::Deposit_Amount()
{
    FILE *fp;
    char path[40]="data_base\\";
    char userck[30];
    char passwordck[30];
    int deposit_amount;
    account_info exist_user;
    printf("\n\nDeposit Money:\n");
user_pass:

    printf("\tAccount Number: ");
    scanf("%s",userck);
    printf("\tPassword: ");
    passgenarater(passwordck);

    strcat(path,userck);
    strcat(path,".bin");

    fp = fopen(path,"rb");
    if( fp != NULL)
    {
        fread(&exist_user,sizeof(exist_user),1,fp);
    }
    else
    {
        printf("\n\n\aYou enter wrong account number. Please enter correctly.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass;
    }
    fclose(fp);

    if(strcmp(passwordck,exist_user.password) == 0)
    {
        printf("\n\tEnter Deposit Amount: ");
        scanf("%d",&deposit_amount);

        exist_user.deposit_amount += deposit_amount;

        fp = fopen(path,"wb");
        fwrite(&exist_user,sizeof(exist_user),1,fp);
        fclose(fp);

        printf("\n\n\t\aTransaction Is Successful\n");
    }
    else
    {
        printf("\n\n\aPassword is wrong. Enter The password again.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass;
    }

    cout<<"Press '0' to go the Main Menu: ";
    cin>>selection;

    cout<<endl;

    if(selection == 0)
    {
        MainMenu();
    }
};

void Bank::Withdraw_Amount()
{
    FILE *fp;
    char path[40]="data_base\\";
    char userck[30];
    char passwordck[30];
    int withdraw_amount;
    account_info exist_user;
    printf("\nDeposit Money:\n");
user_pass:

    printf("\tAccount Number: ");
    scanf("%s",userck);
    printf("\tPassword: ");
    passgenarater(passwordck);

    strcat(path,userck);
    strcat(path,".bin");

    fp = fopen(path,"rb");
    if( fp != NULL)
    {
        fread(&exist_user,sizeof(exist_user),1,fp);
    }
    else
    {
        printf("\n\n\aYou enter wrong account number. Please enter correctly.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass;
    }
    fclose(fp);

    if(strcmp(passwordck,exist_user.password) == 0)
    {
        printf("\nEnter Withdraw Amount: ");
        scanf("%d",&withdraw_amount);

        exist_user.deposit_amount -= withdraw_amount;

        fp = fopen(path,"wb");
        fwrite(&exist_user,sizeof(exist_user),1,fp);
        fclose(fp);

        printf("\n\n\t\aTransaction Is Successful\n");
    }
    else
    {
        printf("\n\n\aPassword is wrong. Enter The password again.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass;
    }

    cout<<"Press '0' to go the Main Menu: ";
    cin>>selection;

    cout<<endl;

    if(selection == 0)
    {
        MainMenu();
    }
};

void Bank::Transfer_Amount()
{
    FILE *fp;
    FILE *num_fp;
    char path[40]="data_base\\";
    char userck[30];
    char passwordck[30];
    int transfer_amount;
    char num_path[40] = "data_base\\";
    char num[30];
    account_info exist_user, transfer_user;
    printf("\nDeposit Money:\n");
user_pass:

    printf("\tAccount Number: ");
    scanf("%s",userck);
    printf("\tPassword: ");
    passgenarater(passwordck);

    strcat(path,userck);
    strcat(path,".bin");

    fp = fopen(path,"rb");
    if( fp != NULL)
    {
        fread(&exist_user,sizeof(exist_user),1,fp);
    }
    else
    {
        printf("\n\n\aYou enter wrong account number. Please enter correctly.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass;
    }
    fclose(fp);

    if(strcmp(passwordck,exist_user.password) == 0)
    {

num_transfer:
        printf("\n\nEnter Transfer Account Number: ");
        scanf("%s",num);
        printf("\nEnter Transfer Amount: ");
        scanf("%d",&transfer_amount);

        strcat(num_path,num);
        strcat(num_path,".bin");

        num_fp = fopen(num_path,"rb");

        if( num_fp != NULL)
        {
            fread(&transfer_user,sizeof(transfer_user),1,num_fp);

            exist_user.deposit_amount -= transfer_amount;

            transfer_user.deposit_amount += transfer_amount;

        }
        else
        {
            printf("\n\n\aYou enter wrong transfer account number. Please enter correctly.\n\n");
            strcpy(num_path,"data_base\\");
            goto num_transfer;
        }
        fclose(num_fp);

        fp = fopen(path,"wb");
        fwrite(&exist_user,sizeof(exist_user),1,fp);
        fclose(fp);

        num_fp = fopen(num_path,"wb");
        fwrite(&transfer_user,sizeof(transfer_user),1,num_fp);
        fclose(num_fp);

        printf("\n\n\t\aTransaction Is Successful\n");
    }
    else
    {
        printf("\n\n\aPassword is wrong. Enter The password again.\n\n");
        strcpy(path,"data_base\\");
        goto user_pass;
    }

    cout<<"Press '0' to go the Main Menu: ";
    cin>>selection;

    cout<<endl;

    if(selection == 0)
    {
        MainMenu();
    }
};


void passgenarater(char pass[])
{
    int i = 0;
    char ch;

    while(1)
    {
        ch = getch();
        if(ch == 8)
        {
            if(i>0)
            {
                pass[--i];
            }
            continue;
        }
        if(ch == 13)
        {
            break;
        }
        putchar('*');
        pass[i++] = ch;
    }
    pass[i] = '\0';
}
