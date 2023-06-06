#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

#define maximum_contacts 50
#define maximum_users 100

typedef struct
{
    char username[20];
    char password[20];
} user_t;

user_t users[maximum_users];

int no_users = 0; // number of users in user_t struct

typedef struct
{
    char name[20];
    char tpnum[20];
    char address[100];
    char email[20];
    char added_user[20];
} contact_t;

contact_t contacts[maximum_contacts];

int no_contacts = 0; // number of contacts stored in contacts_t struct

void disableEcho()
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void enableEcho()
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

user_t log_user;

bool login_checker(user_t user)
{
    for (int i = 0; i <= no_users; i++)
    {
        if (strcmp(users[i].username, user.username) == 0)
        {
            if (strcmp(users[i].password, user.password) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

void start_page();

void addContact();
void searchContact();
void deleteContact();
void contact_list();

void home_page()
{
    int res3; // respose at the home page

    printf("------------Home------------\n");
    printf("1. Add Contact\n2. Search Contact\n3. Delete Contact\n4. Contact List\n5. Log Out\n");
    printf("Enter an option: ");
    scanf("%d", &res3);

    if (res3 == 1)
    {
        addContact();
    }

    else if (res3 == 2)
    {
        searchContact();
    }

    else if (res3 == 3)
    {
        deleteContact();
    }

    else if (res3 == 4)
    {
        contact_list();
    }

    else if (res3 == 5)
    {
        start_page();
    }

    else
    {
        printf("Invalid input.\n");
        home_page();
    }
}

void login_page()
{
    user_t cur_user;

    printf("------------Log In------------\n");
    printf("Enter Username: ");
    scanf("%s", cur_user.username);
    printf("Enter Password: ");
    disableEcho();
    scanf("%s", cur_user.password);
    enableEcho();

    if (login_checker(cur_user))
    {
        printf("logging successful!!\n");
        log_user = cur_user;
        home_page();
    }

    else
    {
        printf("Invalid Username or Password.\n");
        start_page();
    }
}

void signup_page()
{
    int res2; // response after sign up
    user_t newUser;
    char com_pw[20]; // compare the password

    printf("------------Sign Up------------\n");
    printf("Enter a Username: ");
    scanf("%s", newUser.username);
    printf("Enter a Password: ");
    disableEcho();
    scanf("%s", newUser.password);
    enableEcho();
    printf("\n");
    printf("Enter Password again: ");
    disableEcho();
    scanf("%s", com_pw);
    enableEcho();
    printf("\n");

    if (!(strcmp(newUser.password, com_pw)))
    {
        printf("Sign Up Succssfull.\n");
        users[no_users] = newUser;
        no_users++;
    }

    else
    {
        printf("Password does not match.\n");
        signup_page();
    }

    printf("-------------------------------------\n");
    printf("1. Log In\n2. Sign Up another user\n");
    printf("Enter an option: ");
    scanf("%d", &res2);

    if (res2 == 1)
    {
        login_page();
    }

    else if (res2 == 2)
    {
        signup_page();
    }
}

void addContact()
{
    contact_t newContact;
    char cur_username[20];
    char cur_pw[20];

    printf("------------Add Contact------------\n");
    printf("Enter name: ");
    scanf("%s", newContact.name);
    printf("Enter telephone number: ");
    scanf("%s", newContact.tpnum);
    printf("Enter address: ");
    scanf("%s", newContact.address);
    printf("Enter email address: ");
    scanf("%s", newContact.email);

    printf("Enter your username: ");
    scanf("%s", cur_username);
    printf("Enter your password: \n");
    disableEcho();
    scanf("%s", cur_pw);
    enableEcho();

    // strcpy(newContact.added_user, cur_username);

    if (!(strcmp(cur_username, log_user.username)))
    {
        if (!(strcmp(cur_pw, log_user.password)))
        {
            printf("Contact Added Successfully.\n");
            contacts[no_contacts] = newContact;
            no_contacts++;
            home_page();
        }
    }

    else
    {
        printf("Invalid username password combination.\n");
        home_page();
    }
}

void searchContact()
{
    int res4;
    char ser_name[20];
    char ser_tp[20];

    printf("------------Search Contact------------\n");
    printf("1. Search by name\n2. Search by Telephone Number\n");
    printf("Enter an option: ");
    scanf("%d", &res4);

    if (res4 == 1)
    {
        printf("Enter the name: ");
        scanf("%s", ser_name);

        int i;
        for (i = 0; i < no_contacts; i++)
        {
            if (!(strcmp(ser_name, contacts[i].name)))
            {
                break;
            }

            // if (i = no_contacts - 1)
            // {
            //     return;
            // }
        }

        printf("Name: %s\n", contacts[i].name);
        printf("Telephone Number: %s\n", contacts[i].tpnum);
        printf("Address: %s\n", contacts[i].address);
        printf("Email: %s\n", contacts[i].email);
    }

    else if (res4 == 2)
    {
        printf("Enter the telephone number: ");
        scanf("%s", ser_tp);

        int i;
        for (i = 0; i < no_contacts; i++)
        {
            if (!(strcmp(ser_tp, contacts[i].tpnum)))
            {
                break;
            }

            // if (i = no_contacts - 1)
            // {
            //     return;
            // }
        }

        printf("Name: %s\n", contacts[i].name);
        printf("Telephone Number: %s\n", contacts[i].tpnum);
        printf("Address: %s\n", contacts[i].address);
        printf("Email: %s\n", contacts[i].email);
    }
}

void deleteContact()
{
    char en_username[20];
    char en_pw[20];
    printf("Enter your username: ");
    scanf("%s", en_username);
    printf("Enter your password: \n");
    disableEcho();
    scanf("%s", en_pw);
    enableEcho();
    char del_name[20];
    char del_tp[20];
    int res5; // response in delete contact page
    if (!(strcmp(en_username, log_user.username)))
    {
        printf("------------Search Contact------------\n");
        printf("1. Search by name\n2. Search by Telephone Number\n");
        printf("Enter an option: ");
        scanf("%d", &res5);

        if (res5 == 1)
        {
            printf("Enter the name you want to delete: ");
            scanf("%s", del_name);

            int i = 0;

            while (strcmp(del_name, contacts[i].name))
            {
                i++;
                if (i == no_contacts)
                {
                    break;
                }
            }

            if (i == no_contacts)
            {
                printf("Invalid name.\n");
            }

            else
            {

                for (i; i < no_contacts - 1; i++)
                {
                    contacts[i] = contacts[i + 1];
                }

                no_contacts--;
                printf("Contact has been deleted.\n");
                home_page();
            }
        }

        else if (res5 == 2)
        {
            printf("Enter the telephone number you want to delete: ");
            scanf("%s", del_tp);

            int i = 0;

            while (strcmp(del_tp, contacts[i].tpnum))
            {
                i++;
                if (i == no_contacts)
                {
                    break;
                }
            }

            if (i == no_contacts)
            {
                printf("Invalid telephone number.\n");
            }

            else
            {

                for (i; i < no_contacts - 1; i++)
                {
                    contacts[i] = contacts[i + 1];
                }

                no_contacts--;
                printf("Contact has been deleted.\n");
                home_page();
            }
        }
    }

    else
    {
        printf("Invalid username password combination.");
        home_page();
    }
}

void contact_list()
{
    printf("------------Contact List------------\n");
    printf("name\ttelephone\t\n");
    for (int i = 0; i < no_contacts; i++)
    {
        printf("%s\t%s\t\n", contacts[i].name, contacts[i].tpnum);
    }
    home_page();
}

void start_page()
{
    int res1; // respond to login or sign up

    printf("-------------------------------------\n");
    printf("Welcome to the Contact Management System\n");
    printf("Select an option\n1. Login\n2. Sign Up\n3. Quit\n");
    printf("-------------------------------------\n");
    printf("Enter an option: ");
    scanf("%d", &res1);

    if (res1 == 1)
    {
        login_page();
    }

    else if (res1 == 2)
    {
        signup_page();
    }

    else if (res1 == 3)
    {
        exit(0);
    }

    else
    {
        printf("Invalid Input!!\n");
        home_page();
    }
}

int main()
{
    bool logged = false;

    start_page();

    return 0;
}