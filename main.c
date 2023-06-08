#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

#define maximum_contacts 50 // maximum number of contacts can be stored in the system
#define maximum_users 50    // maximum number of uers can be stored in the system

// struct to keep information about users signing up
typedef struct
{
    char username[20];
    char password[20];
} user_t;

user_t users[maximum_users]; // stores user_t elements

int no_users = 0; // number of users in user_t struct

// struct to keep information about contacts added to the system
typedef struct
{
    char name[20];
    char tpnum[20];
    char address[100];
    char email[20];
    char added_user[20];
} contact_t;

contact_t contacts[maximum_contacts]; // stores contact_t elements

int no_contacts = 0; // number of contacts stored in contacts_t struct

void disableEcho()
{
    // make the text field invisible when a password is entered
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void enableEcho()
{
    // make the text fields visible after the password
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

user_t log_user; // to store information about current user

bool login_checker(user_t user)
{
    // compares username and password entered by the user and returns true if compatible
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

void start_page(); // first page of the application

void addContact();
void searchContact();
void deleteContact();
void contact_list();

void clearInputBuffer()
{
    // clears the input buffer before calling the getchar() function
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Discard characters
    }
}

void cont_page()
{
    // prints "press enter to continue"
    // procedes when an enter is entered
    printf("Press enter to continue\n");
    clearInputBuffer();
    getchar();
    printf("Continuing...\n");
}

void home_page()
{
    // home page after logging in
    // shows features of the application
    // directed to corresponding page to the input entered

    int res3; // respose at the home page

    printf("------------Home------------\n");
    printf("Logged in as %s\n", log_user.username);
    printf("1. Add Contact\n2. Search Contact\n3. Delete Contact\n4. Contact List\n5. Log Out\n");
    printf("Enter an option: ");
    scanf("%d", &res3);

    if (res3 == 1)
    {
        system("clear");
        addContact();
    }

    else if (res3 == 2)
    {
        system("clear");
        searchContact();
    }

    else if (res3 == 3)
    {
        system("clear");
        deleteContact();
    }

    else if (res3 == 4)
    {
        system("clear");
        contact_list();
    }

    else if (res3 == 5)
    {
        system("clear");
        start_page();
    }

    else
    {
        system("clear");
        printf("Invalid input.\a\n");
        cont_page();
        home_page();
    }
}

void login_page()
{
    // asks for username and password
    // compared by the login_checker() function

    user_t cur_user;

    printf("------------Log In------------\n");
    printf("Enter Username: ");
    scanf("%s", cur_user.username);
    printf("Enter Password: ");
    disableEcho();
    scanf("%s", cur_user.password);
    enableEcho();
    printf("\n");

    if (login_checker(cur_user))
    {
        system("clear");
        log_user = cur_user;
        home_page();
    }

    else
    {
        system("clear");
        printf("Invalid Username or Password.\a\n");
        cont_page();
        system("clear");
        start_page();
    }
}

void signup_page()
{
    // to create new accounts
    // asks for username and password
    // prompts to re-enter the password
    // account will be created if two passwords are matching

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
        cont_page();

        users[no_users] = newUser;
        system("clear");
        no_users++;
    }

    else
    {
        system("clear");
        printf("Password does not match.\a\n");
        cont_page();
        system("clear");
        signup_page();
    }

    printf("-------------------------------------\n");
    printf("1. Log In\n2. Sign Up another user\n");
    printf("Enter an option: ");
    scanf("%d", &res2);

    if (res2 == 1)
    {
        system("clear");
        login_page();
    }

    else if (res2 == 2)
    {
        system("clear");
        signup_page();
    }

    else
    {
        system("clear");
        printf("Invalid input\a\n");
        cont_page();
        system("clear");
        start_page();
    }
}

void addContact()
{
    // adds information of contacts

    contact_t newContact;
    char cur_username[20];
    char cur_pw[20];

    printf("------------Add Contact------------\n");
    printf("Enter name: ");
    scanf(" %[^\n]", newContact.name);
    printf("Enter telephone number: ");
    scanf("%s", newContact.tpnum);
    printf("Enter address: ");
    scanf(" %[^\n]", newContact.address);
    printf("Enter email address: ");
    scanf("%s", newContact.email);

    strcpy(newContact.added_user, log_user.username);

    printf("Contact Added Successfully.\n");
    contacts[no_contacts] = newContact;
    no_contacts++;

    cont_page();
    system("clear");
    home_page();
}

void searchContact()
{
    // search contacts by their name or the telephone number

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
        scanf(" %[^\n]", ser_name);

        int i;
        for (i = 0; i < no_contacts; i++)
        {
            if (!(strcmp(ser_name, contacts[i].name)))
            {
                break;
            }
        }

        system("clear");
        printf("Name: %s\n", contacts[i].name);
        printf("Telephone Number: %s\n", contacts[i].tpnum);
        printf("Address: %s\n", contacts[i].address);
        printf("Email: %s\n", contacts[i].email);
        cont_page();
        system("clear");
        home_page();
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
        }

        system("clear");
        printf("Name: %s\n", contacts[i].name);
        printf("Telephone Number: %s\n", contacts[i].tpnum);
        printf("Address: %s\n", contacts[i].address);
        printf("Email: %s\n", contacts[i].email);
        cont_page();
        system("clear");
        home_page();
    }

    else
    {
        printf("Invalid input.\n");
        cont_page();
        system("clear");
        home_page();
    }
}

void deleteContact()
{
    // asks for the username and password of the user
    // if it is correct directed to the delete page
    // can delete cantacts by searching by name and telephone number

    char en_username[20];
    char en_pw[20];
    printf("Enter your username: ");
    scanf("%s", en_username);
    printf("Enter your password: ");
    disableEcho();
    scanf("%s", en_pw);
    enableEcho();
    printf("\n");
    char del_name[20];
    char del_tp[20];
    int res5; // response in delete contact page
    if (!(strcmp(en_username, log_user.username)))
    {
        system("clear");
        printf("------------Search Contact------------\n");
        printf("1. Search by name\n2. Search by Telephone Number\n");
        printf("Enter an option: ");
        scanf("%d", &res5);

        if (res5 == 1)
        {
            system("clear");
            printf("Enter the name you want to delete: ");
            scanf(" %[^\n]", del_name);

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

                printf("Invalid name.\a\n");
                cont_page();
                system("clear");
                home_page();
            }

            else
            {
                if (!(strcmp(contacts[i].added_user, log_user.username)))
                {

                    for (i; i < no_contacts - 1; i++)
                    {
                        contacts[i] = contacts[i + 1];
                    }

                    no_contacts--;
                    printf("Contact has been deleted.\n");
                    cont_page();
                    system("clear");
                    home_page();
                }

                else
                {
                    printf("You can't delete contacts added by other users.\a\n");
                    cont_page();
                    system("clear");
                    home_page();
                }
            }
        }

        else if (res5 == 2)
        {
            system("clear");
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
                printf("Invalid telephone number.\a\n");
                cont_page();
                system("clear");
                home_page();
            }

            else
            {

                if (!(strcmp(contacts[i].added_user, log_user.username)))
                {

                    for (i; i < no_contacts - 1; i++)
                    {
                        contacts[i] = contacts[i + 1];
                    }

                    no_contacts--;
                    printf("Contact has been deleted.\n");
                    cont_page();
                    system("clear");
                    home_page();
                }

                else
                {
                    printf("You can't delete contacts added by other users.\a\n");
                    cont_page();
                    system("clear");
                    home_page();
                }
            }
        }
    }

    else
    {
        printf("Invalid username password combination.\a\n");
        cont_page();
        system("clear");
        home_page();
    }
}

void contact_list()
{
    // lists contacts stored in the system
    // prints "no contacts to show" when the contacts array is empty
    system("clear");
    printf("------------Contact List------------\n");

    if (no_contacts)
    {
        printf("+-------------------------+---------------+------------------------------------------------|------------------------|\n");
        printf("|Name                     |Telephone      |Address                                         |email                   |\n");
        printf("+-------------------------+---------------+------------------------------------------------|------------------------|\n");
        for (int i = 0; i < no_contacts; i++)
        {
            // printf("%s\t%s\t\n", contacts[i].name, contacts[i].tpnum);
            printf("|%-25s|%-15s|%-48s|%-24s|\n", contacts[i].name, contacts[i].tpnum, contacts[i].address, contacts[i].email);
        }
        printf("+-------------------------+---------------+------------------------------------------------|------------------------|\n");
        cont_page();
        system("clear");
        home_page();
    }

    else
    {
        system("clear");
        printf("No contacts to show.\n");
        cont_page();
        system("clear");
        home_page();
    }
}

void start_page()
{
    // initial page of the application

    int res1; // respond to login or sign up

    printf("-------------------------------------\n");
    printf("Welcome to the Contact Management System\n");
    printf("Select an option\n1. Login\n2. Sign Up\n3. Quit\n");
    printf("-------------------------------------\n");
    printf("Enter an option: ");
    scanf("%d", &res1);

    if (res1 == 1)
    {
        system("clear");
        login_page();
    }

    else if (res1 == 2)
    {
        system("clear");
        signup_page();
    }

    else if (res1 == 3)
    {
        system("clear");
        exit(0);
    }

    else
    {
        system("clear");
        printf("Invalid Input!!\n");
        cont_page();
        system("clear");
        home_page();
    }
}

int main()
{
    system("clear");

    start_page();

    return 0;
}