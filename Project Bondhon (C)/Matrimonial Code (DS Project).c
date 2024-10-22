#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int id_initializer = 100101;

void read_id_initializer(void)
{
    FILE *id_ini;
    id_ini=fopen("ID_initializer.dat","rb");
    if(id_ini == NULL)
    {
        return;
    }
    fread(&id_initializer,sizeof(id_initializer),1,id_ini);
    fclose(id_ini);
}

void save_id_initializer(void)
{
    FILE *id_ini;
    id_ini=fopen("ID_initializer.dat","wb");
    if(id_ini == NULL)
    {
        exit(0);
    }
    fwrite(&id_initializer,sizeof(id_initializer),1,id_ini);
    fclose(id_ini);
}

typedef struct user_node
{
    int approval_status;/// 0 for pending, 1 for approved, -1 declined, -2 Banned
    int profile_status;///0 for hidden, 1 for public
    int user_id;
    int user_pass;
    char name[50];
    int gender;///1-Male, 2-Female
    int age; /// min, max
    char DOB[20];
    int religion;///1-Islam, 2-Christian, 3-Hindu, 4-Buddha
    float height;
    char blood_group[5];
    char email[50];
    char phone[20];
    char nid[20];
    int division;/// 1-Dhaka, 2-Chittagong, 3-Rajshahi
    /// 4-Khulna, 5-Sylhet, 6-Barisal, 7-Rangpur
    /// 8-Mymensingh


    char district[50];
    char detailed_address[1000];
    int job_status; ///0-all, 1-Job, 2-Business, 3-Student, 4-Unemployed
    char marital_status[20];
    char edu_info[1000];
    char about_me[10000];

    int saved_bio_list[20];
    struct user_node *prev;
    struct user_node *next;
} userNode; //user node is a doubly linked list

userNode *head;

void userNode_initializer()
{
    head = (userNode*)malloc(sizeof(userNode));
    if(head == NULL)
    {
        printf("Memory initialization failed!\n\n");
        exit(0);
    }
    head->approval_status = 0;
    head->profile_status = 0;
    head->user_id = 100100;
    head->user_pass = 0;
    head->prev = NULL;
    head->next = NULL;
}


///Common
void displayWelcomeMessage(void);
void displayEndMessage(void);
int front_menu(void);
void read_data_from_file(void);


///admin
int admin_login(void);
void admin_menu(void);
void all_user_list(void);//done

void approve_new_user(void);
void pending_user_list(void);
void take_decision_for_pending_new_user(void);
void ban_allow_user(void);
void ban_allow_user_updater(int ch);


///Guest
void guest_menu(void);
void view_partial_user_profile(int userID);
void user_profile_list_view_both_gender(int Division);
void user_profile_list_view_single_gender(int Gender, int Division);
void view_user_profile_guest_mode(int Gender);


///User
void user_guide(void);//waiting
void user_signup(void);//done
int user_login(void);//done

void user_menu(int userID);
int user_acc_status(int userID);//done
void edit_user_profile(int userID);//done
int want_to_change(void);//done
void view_full_user_profile(int userID);//done
void apply_otp(void);//done
void unlock_biodata(int userID);//done
void show_unlocked_biodata(int userID);//done
void biodata_list_view(int userID);//done
void biodata_detailed_view(int userID);//done
void publish_unpublish_profile(int userId);//done

int main(void)
{
    displayWelcomeMessage();
    userNode_initializer();
    read_id_initializer();
    read_data_from_file();
    int ch;//for taking user input from the main menu
    int adm;//for admin login verification.
    int usr;//for user login verification.
    while(1)
    {
        ch = front_menu();
        if(ch == 0) break;

        switch(ch)
        {
        case 1:
            user_guide();///User Guid
            break;
        case 2:
            ///Admin Login
            adm = admin_login();
            if(adm == -1) continue;
            else if(adm == 1) admin_menu();
            break;
        case 3:
            ///User Signup
            user_signup();
            break;
        case 4:
            ///User Login
            usr = user_login();
            if(usr == -1) continue;
            else user_menu(usr);
            break;
        case 5:
            ///Guest Login
            guest_menu();
            break;
        case 6:
            ///About Devol
            developersinfo();
            break;
        default:
            printf("\n\nWrong input! Please Give valid  input.\n\n\n");
            system("pause");
        }
    }
    save_data_to_file();
    save_id_initializer();
    displayEndMessage();

    return 0;
}

///Common
// Function to display the welcome message
void displayWelcomeMessage(void)
{
    system("cls");
    printf ("\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|\n");
    printf ("\t\t\t\t*                                             *\n");
    printf ("\t\t\t\t|                                             |\n");
    printf ("\t\t\t\t*                                             *\n");
    printf ("\t\t\t\t|           Take Salam & Greetings            |\n");
    printf ("\t\t\t\t*                                             *\n");
    printf ("\t\t\t\t| ....... Welcome To Our Bondhon App .......  |\n");
    printf ("\t\t\t\t*                                             *\n");
    printf ("\t\t\t\t|           Find Your Life Partner            |\n");
    printf ("\t\t\t\t*                                             *\n");
    printf ("\t\t\t\t|                                             |\n");
    printf ("\t\t\t\t*                                             *\n");
    printf ("\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|\n");
    system("pause");
}

// Function to display the end message
void displayEndMessage(void)
{
    system("cls");
    printf ("\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|\n");
    printf ("\t\t\t\t*                                                     *\n");
    printf ("\t\t\t\t|                                                     |\n");
    printf ("\t\t\t\t*                                                     *\n");
    printf ("\t\t\t\t|           Thanks To Watching Our Code               |\n");
    printf ("\t\t\t\t*                                                     *\n");
    printf ("\t\t\t\t| ... We Hope You Have Found Your Perfect Partner ... |\n");
    printf ("\t\t\t\t*                                                     *\n");
    printf ("\t\t\t\t|                                                     |\n");
    printf ("\t\t\t\t*                                                     *\n");
    printf ("\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|\n");
}

void developersinfo(void)
{
    system("cls");
    printf("\t\t\t\t*-*-*-*-*-**-*-*-*-*-**-*-*-*-*-*-*-*-*-*-**-*-*-*-*-**-*-*-*\n");
    printf("\t\t\t\t|                   Developers list                         |\n");
    printf("\t\t\t\t*-*-*-*-*-**-*-*-*-*-**-*-*-*-*-*-*-*-*-*-**-*-*-*-*-**-*-*-*\n");
    printf ("\t\t\t----------------------------------------------------------------------------\n");
    printf ("\t\t\t\t.............................................................\n");
    printf ("\t\t\t\t| Name   : Md. Nawshin Zaman (Project Manager)              |\n");
    printf ("\t\t\t\t| ID     : 0242310005101554                                 |\n");
    printf ("\t\t\t\t| Section: 64_A                                             |\n");
    printf ("\t\t\t\t| Contact: 01996707921                                      |\n");
    printf ("\t\t\t\t| E-mail : zaman2305101554@diu.edu.bd                       |\n");
    printf ("\t\t\t\t............................................................\n\n");
    printf ("\t\t\t\t.............................................................\n");
    printf ("\t\t\t\t| Name   : Md. Rafiur Rahman (Software Architect)           |\n");
    printf ("\t\t\t\t| ID     : 0242310005101857                                 |\n");
    printf ("\t\t\t\t| Section: 64_A                                             |\n");
    printf ("\t\t\t\t| Contact: 01783290879                                      |\n");
    printf ("\t\t\t\t| E-mail : rafiur2305101857@diu.edu.bd                      |\n");
    printf ("\t\t\t\t............................................................\n\n");
    printf ("\t\t\t\t.............................................................\n");
    printf ("\t\t\t\t| Name   : Md. Rajibul Alam Rajib (Database Officer)        |\n");
    printf ("\t\t\t\t| ID     : 0242310005101812                                 |\n");
    printf ("\t\t\t\t| Section: 64_A                                             |\n");
    printf ("\t\t\t\t| Contact: 01310511163                                      |\n");
    printf ("\t\t\t\t| E-mail : rajib2305101812@diu.edu.bd                       |\n");
    printf ("\t\t\t\t............................................................\n\n");
    printf ("\t\t\t\t.............................................................\n");
    printf ("\t\t\t\t| Name   : Md. Parvez Kabir Sakib (Web Manager+Editor)      |\n");
    printf ("\t\t\t\t| ID     : 0242310005101470                                 |\n");
    printf ("\t\t\t\t| Section: 64_A                                             |\n");
    printf ("\t\t\t\t| Contact: 01761612529                                      |\n");
    printf ("\t\t\t\t| E-mail : sakib23105101470@diu.edu.bd                      |\n");
    printf ("\t\t\t\t............................................................\n\n");
    printf ("\t\t\t\t.............................................................\n");
    printf ("\t\t\t\t| Name   : Md. Tarik Ahammed (Quality Assurance Engineer)   |\n");
    printf ("\t\t\t\t| ID     : 0242310005101050                                 |\n");
    printf ("\t\t\t\t| Section: 64_A                                             |\n");
    printf ("\t\t\t\t| Contact: 01955222740                                      |\n");
    printf ("\t\t\t\t| E-mail : ahammed23105101050@diu.edu.bd                    |\n");
    printf ("\t\t\t\t.............................................................\n\n");
    printf ("\t\t\t----------------------------------------------------------------------------\n");
    printf("\n\n");
    system("pause");
}

void read_data_from_file(void)
{
    FILE *fp;
    fp = fopen("bondhon_database.dat", "rb");
    userNode u;
    userNode *temp;
    if(fp == NULL)
    {
        return;
    }

    userNode *t_head = head;

    while(t_head->next != NULL)
    {
        t_head = t_head->next;
    }

    while(fread(&u,sizeof(u),1,fp))
    {
        temp=(userNode*)malloc(sizeof(userNode));

        ///Work start
        for(int i = 0; i < 20;  i++)
        {
            temp->saved_bio_list[i] = u.saved_bio_list[i];
        }

        strcpy(temp->email, u.email);
        temp->user_id = u.user_id;
        temp->user_pass = u.user_pass;
        strcpy(temp->name, u.name);
        temp->gender = u.gender;
        temp->age =u.age;
        strcpy(temp->DOB, u.DOB);
        temp->religion = u.religion;
        temp->height = u.height;
        strcpy(temp->blood_group, u.blood_group);
        strcpy(temp->phone, u.phone);
        strcpy(temp->nid, u.nid);
        temp->division = u.division;
        strcpy(temp->district, u.district);
        strcpy(temp->detailed_address, u.detailed_address);
        temp->job_status = u.job_status;
        strcpy(temp->marital_status, u.marital_status);
        strcpy(temp->edu_info, u.edu_info);
        strcpy(temp->about_me, u.about_me);
        temp->approval_status = u.approval_status;
        temp->profile_status = u.profile_status;

        temp->prev = t_head;
        temp->next = NULL;
        t_head->next = temp;
        t_head = t_head->next;
    }
    fclose(fp);
}

void save_data_to_file(void)
{
    FILE *fp;
    fp = fopen("bondhon_database.dat", "wb");
    userNode u;

    if(fp==NULL)
    {
        return;
    }
    userNode *t_head = head;
    t_head = t_head->next;

    while(t_head!=NULL)
    {
        ///start
        for(int i = 0; i < 20;  i++)
        {
            u.saved_bio_list[i] = t_head->saved_bio_list[i];
        }

        strcpy(u.email, t_head->email);
        u.user_id = t_head->user_id;
        u.user_pass = t_head->user_pass;
        strcpy(u.name, t_head->name);
        u.gender = t_head->gender;
        u.age =t_head->age;
        strcpy(u.DOB, t_head->DOB);
        u.religion = t_head->religion;
        u.height = t_head->height;
        strcpy(u.blood_group, t_head->blood_group);
        strcpy(u.phone, t_head->phone);
        strcpy(u.nid, t_head->nid);
        u.division = t_head->division;
        strcpy(u.district, t_head->district);
        strcpy(u.detailed_address, t_head->detailed_address);
        u.job_status = t_head->job_status;
        strcpy(u.marital_status, t_head->marital_status);
        strcpy(u.edu_info, t_head->edu_info);
        strcpy(u.about_me, t_head->about_me);
        u.approval_status = t_head->approval_status;
        u.profile_status = t_head->profile_status;
        ///end

        fwrite(&u,sizeof(u),1,fp);
        t_head = t_head->next;
    }
    fclose(fp);
}

int front_menu(void)
{
    system("cls");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|\n");
    printf ("\t\t\t\t\t|*               Front menu                  *|\n");
    printf ("\t\t\t\t\t|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf("\t\t\t\t\t------------------------------------------------\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|                1. User Guide                |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|                2. Admin login               |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|                3. User Sign up              |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|                4. User login                |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|                5. Guest login               |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|                6. About Developers          |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|                0. Exit                      |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("Please Enter Your Choice: ");

    int ch;
    scanf("%d",&ch);
    return ch;
}


///Admin part start
int admin_login(void)
{
    system("cls");
    while(1)
    {
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("\t\t\t\t\t|     Admin Verification menu       |\n");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        char presetID[] = "123456";
        char presetPassword[] = "123456";

        char id[20];
        char pass[20];

        printf("Enter your ID: ");
        fflush(stdin);
        scanf("%s", id);

        printf("Enter your password: ");
        fflush(stdin);
        scanf("%s", pass);

        if (strcmp(id, presetID) == 0 && strcmp(pass, presetPassword) == 0)
        {
            return 1;
        }
        else
        {
            printf("Login failed. Invalid ID or password.\n");
            printf("Press:\n");
            printf("1. Try Again\n");
            printf("0. Go back to Main menu\n");
            printf("Enter your choice: ");
            int ch;
            scanf("%d", &ch);
            if(ch == 1)
            {
                system("cls");
                continue;
            }
            else
            {
                break;
            }
        }
    }
    return -1;

}

void admin_menu(void)
{
    while(1)
    {
        system("cls");
        printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|\n");
    printf ("\t\t\t\t\t|*               Admin Menu                  *|\n");
    printf ("\t\t\t\t\t|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf("\t\t\t\t\t------------------------------------------------\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|       1. See User List and Number           |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|       2. New user approval                  |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|       3. Ban or Allow user                  |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|       4. Delete Biodata                     |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
    printf ("\t\t\t\t\t...............................................\n");
    printf ("\t\t\t\t\t|       0. Go back to main menu               |\n");
    printf ("\t\t\t\t\t...............................................\n\n");
        //printf(". Create OTP\n"); //this option will be developed in future if needed
        //printf(". Change Admin ID and Pass\n"); //this option will be developed in future if needed

        int ch;
        scanf("%d",&ch);
        if(ch == 0) break;

        switch(ch)
        {
        case 1:
            all_user_list();
            break;
        case 2:
            approve_new_user();
            break;
        case 3:
            ban_allow_user();
            break;
        case 4:
            delete_user_bio();
            break;
        }
    }
}


void all_user_list(void)
{
    userNode *t_head = head;
    t_head = t_head->next;

    int total = 0;
    system("cls");
    printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("\t\t\t\t\t|        All Bio Data List          |\n");
    printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("ID      Gender      Profile Status\n");

    while(t_head != NULL)
    {
        total++;
        printf("%-6d  ", t_head->user_id);

        if(t_head->gender == 1) printf("Male        ");///
        else printf("Female      ");///

        switch(t_head->approval_status)
        {
        case 0:
            printf("Pending Approval\n");
            break;
        case 1:
            printf("Approved!\n");
            break;
        case -1:
            printf("Declined!\n");
            break;
        case -2:
            printf("Banned!\n");
            break;
        }

        t_head = t_head->next;
    }

    printf("\n\n\n");
    printf("Number of Total User is: %d\n\n\n", total);
    system("pause");
}

void approve_new_user(void)
{
    //Queue view
    while(1)
    {
        system("cls");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("\t\t\t\t\t|      New User Approval Menu       |\n");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("\t\t\t\t\t----------------------------------------------------\n");
        printf ("\t\t\t\t..............................................................\n");
        printf ("\t\t\t\t|       1. Check Pending user list                           |\n");
        printf ("\t\t\t\t............................................................\n\n");
        printf ("\t\t\t\t..............................................................\n");
        printf ("\t\t\t\t|       2. Take decision for the first user of the list      |\n");
        printf ("\t\t\t\t............................................................\n\n");
        printf ("\t\t\t\t..............................................................\n");
        printf ("\t\t\t\t|       0. Go back to                                        |\n");
        printf ("\t\t\t\t............................................................\n\n");
        printf("Enter your choice: ");
        int ch;
        do
        {
            scanf("%d", &ch);
            if(ch < 0 && ch > 2)
            {
                printf("Wrong Option!\n");
                system("pause");
            }
        }
        while(ch < 0 && ch > 2);

        if(ch == 0) break;
        switch(ch)
        {
        case 1:
            pending_user_list();
            break;
        case 2:
            take_decision_for_pending_new_user();
            break;
        }

    }
}

void pending_user_list(void)
{
    userNode *t_head = head;
    t_head = t_head->next;

    system("cls");
    printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("\t\t\t\t\t|        Pending User List          |\n");
    printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("ID      Gender\n");
    while(t_head != NULL)
    {
        if(t_head->approval_status == 0)
        {
            printf("%-6d  ", t_head->user_id);

            if(t_head->gender == 1) printf("Male\n");
            else printf("Female\n");
        }
        t_head = t_head->next;
    }
    printf("\n\n\n");
    system("pause");
}

void take_decision_for_pending_new_user(void)
{
    userNode *t_head = head;
    t_head = t_head->next;
    system("cls");
    printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("\t\t\t\t\t|       Decision Making Menu        |\n");
    printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    int check = 0;
    while(t_head != NULL)
    {
        if(t_head->approval_status == 0)
        {
            check = 1;
            break;
        }
        t_head = t_head->next;

    }

    if(check == 0)
    {
        printf("No Pending user available Right now!\n\n\n");
        system("pause");
        return;
    }

    printf("First User ID in the Queue: %d\n", t_head->user_id);
    printf("Press:\n");
    printf("1. Approve\n");
    printf("2. Decline\n");
    printf("0. Go back to Approval Menu\n");

    printf("Enter your choice: \n");
    int ch;
    do
    {
        scanf("%d", &ch);
        if(ch < 0 && ch > 2)
        {
            printf("Wrong Option!\n");
            system("pause");
        }
    }
    while(ch < 0 && ch > 2);

    if(ch == 1)
    {
        t_head->approval_status = 1;
        printf("User ID: %d has been Approved!\n\n\n", t_head->user_id);
    }
    else if(ch == 2)
    {
        t_head->approval_status = -1;
        printf("User ID: %d has been Declined!\n\n\n", t_head->user_id);
    }
    else
    {
        return;
    }
    system("pause");
}

void ban_allow_user(void)
{
    system("cls");
    while(1)
    {
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("\t\t\t\t\t|        Ban or Allow User          |\n");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf ("\t\t\t\t..............................................................\n");
        printf ("\t\t\t\t|       1. Ban user Biodata from public database             |\n");
        printf ("\t\t\t\t............................................................\n\n");
        printf ("\t\t\t\t..............................................................\n");
        printf ("\t\t\t\t|       2. Allow banned user in public database              |\n");
        printf ("\t\t\t\t............................................................\n\n");
        printf ("\t\t\t\t..............................................................\n");
        printf ("\t\t\t\t|       0. Go Back to Admin menu                             |\n");
        printf ("\t\t\t\t............................................................\n\n");
        int ch;
        do
        {
            printf("Enter your choice: ");
            scanf("%d",&ch);
            if(ch < 0 && ch >2)
            {
                printf("Wrong option! Try again\n");
            }
        }
        while(ch < 0 && ch >2);

        if (ch == 0) break;

        int userID;
        int check = 0;
        switch(ch)
        {
        case 1:
            ban_allow_user_updater(-2);
            break;
        case 2:
            ban_allow_user_updater(1);
            break;

        }
    }
}

void ban_allow_user_updater(int ch)
{
    int userID;
    printf("Please enter user ID: ");
    scanf("%d", &userID);

    userNode *t_head = head;
    int check = 0;
    while(t_head != NULL)
    {
        if(t_head->user_id == userID)
        {
            check = 1;
            break;
        }
        t_head = t_head->next;
    }

    if(check == 0)
    {
        printf("User not found! Sending you back to Admin Menu\n\n\n");
        system("pause");
        return;
    }
    else
    {
        if(ch == -2)
        {
            t_head->approval_status = -2;
            printf("User has been banned successfully!\n\n\n");
            system("pause");
        }
        else if(ch == 1)
        {
            t_head->approval_status = 1;
            printf("User has been Allowed successfully!\n\n\n");
            system("pause");
        }
    }
}

void delete_user_bio(void)
{
    int userID;
    printf("Please enter user ID: ");
    scanf("%d", &userID);
    if (userID == 100100)
    {
        printf("Forbidden Operation!!! Sending you back to Admin Menu\n\n\n");
        system("pause");
        return;
    }

    userNode *t_head = head;
    int check = 0;

    while(t_head != NULL)
    {
        if(t_head->user_id == userID)
        {
            check = 1;
            break;
        }

        t_head = t_head->next;
    }
    if(check == 0)
    {
        printf("User not found! Sending you back to Admin Menu\n\n\n");
    }
    else
    {
        userNode *del;
        t_head = t_head->prev;

        if(t_head->next->next == NULL)
        {
            del = t_head->next;
            t_head->next = NULL;
            del->prev = NULL;
            free(del);
            printf("ID: %d has been removed successfully!\n\n\n", userID);
        }
        else
        {
            del = t_head->next;
            t_head->next = del->next;
            del->next->prev = del->prev;
            del->next = NULL;
            del->prev = NULL;
            free(del);
            printf("ID: %d has been removed successfully!\n\n\n", userID);
        }
    }
    system("pause");
}

///Guest Part Start
void guest_menu(void)
{
    while(1)
    {
        system("cls");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-\n");
        printf("\t\t\t\t\t|Welcome to Project \"Bondhon\"s Guest Menu|\n");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-\n");
        printf ("\t\t\t\t...........................................................\n");
        printf ("\t\t\t\t|       1. Watch all Biodatas (Male + Female)             |\n");
        printf ("\t\t\t\t.........................................................\n\n");
        printf ("\t\t\t\t...........................................................\n");
        printf ("\t\t\t\t|       2. Watch Male only                                |\n");
        printf ("\t\t\t\t.........................................................\n\n");
        printf ("\t\t\t\t...........................................................\n");
        printf ("\t\t\t\t|       3. Watch Female only                              |\n");
        printf ("\t\t\t\t....................................................... .\n\n");
        printf ("\t\t\t\t.........................................................\n\n");
        printf ("\t\t\t\t|       0. Go back to Main Menu                           |\n");
        printf ("\t\t\t\t.........................................................\n\n");
        printf("Enter your Choice: \n");

        int ch;
        do
        {
            scanf("%d", &ch);
            if(ch < 0 && ch >3)
            {
                printf("Wrong option, Try Again!\n\n\n");
                system("pause");
            }
        }
        while(ch < 0 && ch >3);

        if(ch == 0) break;

        switch(ch)
        {
        case 1:
            view_user_profile_guest_mode(0); ///all profile
            break;
        case 2:
            view_user_profile_guest_mode(1); ///Only Male
            break;
        case 3:
            view_user_profile_guest_mode(2); ///Only Female
            break;
        }
    }
}

void view_partial_user_profile(int userID)
{
    system("cls");
    userNode *t_head = head;
    int check = 0;
    while(t_head != NULL)
    {
        if(t_head->user_id == userID)
        {
            check = 1;
            break;
        }
        t_head = t_head->next;
    }

    if(check == 0)
    {
        printf("User Not Found! Please Try again.\n\n\n");
        system("pause");
        return;
    }
    else
    {
        printf("\t\t\tUser ID: %d\n", userID);
        printf("-------------------------------------------\n", userID);
        printf("Name              : %s\n", t_head->name);

        if(t_head->gender == 1) printf("Gender            : Male\n");
        else printf("Gender            : Female\n");

        printf("Age               : %d\n", t_head->age);
        printf("*Date of Birth*   : #Only Available After The Biodata is Unlocked#\n");

        switch(t_head->religion)
        {
        case 1:
            printf("Religion          : Islam\n");
            break;
        case 2:
            printf("Religion          : Christian\n");
            break;
        case 3:
            printf("Religion          : Hindu\n");
            break;
        case 4:
            printf("Religion          : Buddha\n");
            break;
        }

        printf("Height            : %.2f\n", t_head->height);
        printf("Blood Group       : %s\n", t_head->blood_group);
        printf("*Email Address*   : #Only Available After The Biodata is Unlocked#\n");
        printf("*Phone Number*    : #Only Available After The Biodata is Unlocked#\n");
        printf("*NID Number*      : #Only Available After The Biodata is Unlocked#\n");

        switch(t_head->division)
        {
        case 1:
            printf("Division          : Dhaka\n");
            break;
        case 2:
            printf("Division          : Chittagong\n");
            break;
        case 3:
            printf("Division          : Rajshahi\n");
            break;
        case 4:
            printf("Division          : Khulna\n");
            break;
        case 5:
            printf("Division          : Sylhet\n");
            break;
        case 6:
            printf("Division          : Barishal\n");
            break;
        case 7:
            printf("Division          : Rangpur\n");
            break;
        case 8:
            printf("Division          : Mymensingh\n");
            break;
        }

        printf("District          : %s\n", t_head->district);

        printf("*Detailed Address*: #Only Available After The Biodata is Unlocked#\n");

        switch(t_head->job_status)
        {
        case 1:
            printf("Job Status        : Company\n");
            break;
        case 2:
            printf("Job Status        : Business\n");
            break;
        case 3:
            printf("Job Status        : Student\n");
            break;
        case 4:
            printf("Job Status        : Unemployed\n");
            break;
        }

        printf("Marital Status    : %s\n", t_head->marital_status);
        printf("Educational Info  : ");
        char EI[1000];
        strcpy(EI, t_head->edu_info);
        int i = 0;
        while(EI[i] != '\0')
        {
            if(EI[i] == '*') printf("\n                    ");
            else printf("%c", EI[i]);
            i++;
        }
        printf("\n");

        printf("About Me          :");
        char AM[10000];
        strcpy(AM, t_head->about_me);
        i = 0;
        while(AM[i] != '\0')
        {
            if(AM[i] == '*') printf("\n                    ");
            else printf("%c", AM[i]);
            i++;
        }
        printf("\n\n\n\n");
        system("pause");
    }
}

void view_user_profile_guest_mode(int Gender) ///User profiles will be viewed using stack formate. Latest Users will be shown at upper positions
{
    while(1)
    {
        system("cls");;
        printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("\t\t\t\t\t\t|   View user Profiles (Guest mode)   |\n");
        printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf ("\t\t\t\t\t.....................................\n");
        printf ("\t\t\t\t\t|       1. List view                |\n");
        printf ("\t\t\t\t\t...................................\n\n");
        printf ("\t\t\t\t\t.....................................\n");
        printf ("\t\t\t\t\t|       2. Detailed view            |\n");
        printf ("\t\t\t\t\t...................................\n\n");
        printf ("\t\t\t\t\t.....................................\n");
        printf ("\t\t\t\t\t|       0. Go back                  |\n");
        printf ("\t\t\t\t\t...................................\n\n");
        printf("Enter Choice: ");
        int ch;
        do
        {
            scanf("%d", &ch);
            if(ch < 0 && ch > 2)
            {
                printf("Wrong Option!\n\n\n");
                system("pause");
            }
        }
        while(ch < 0 && ch > 2);

        if(ch == 0) break;

        int userID, Division;
        switch(ch)
        {
        case 1:
            printf("Select Division : \n");
            printf("0. All\n1. Dhaka\n2. Chittagong\n3. Rajshahi\n4. Khulna\n");
            printf("5. Sylhet\n6. Barishal\n7. Rangpur\n8. Mymenshingh\n");
            printf("Choose: ");
            do
            {
                scanf("%d", &Division);
            }
            while((Division < 0)||(Division > 8));

            if(Gender == 0) user_profile_list_view_both_gender(Division);
            else user_profile_list_view_single_gender(Gender, Division);

            break;
        case 2:
            system("cls");
            printf("Enter User ID: ");
            scanf("%d", &userID);
            view_partial_user_profile(userID);
            break;

        }
    }

}

void user_profile_list_view_both_gender(int Division)
{
    userNode *t_head = head;
    while(t_head->next != NULL)
    {
        t_head = t_head->next;
    }

    system("cls");
    printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-\n");
    printf("\t\t\t\t\t\t|   Biodata list:   |\n");
    printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-\n");
    printf("ID      Gender  Name                     Age  Division\n");

    if(Division == 0)
    {
        while(t_head->prev != NULL)
        {
            if(t_head->approval_status == 1  && t_head->profile_status == 1)
            {
                printf("%-6d  ", t_head->user_id);///

                if(t_head->gender == 1) printf("Male    ");///
                else printf("Female  ");///

                printf("%-24s %d  ", t_head->name, t_head->age);///

                switch(t_head->division)
                {
                case 1:
                    printf(" Dhaka\n");
                    break;
                case 2:
                    printf(" Chittagong\n");
                    break;
                case 3:
                    printf(" Rajshahi\n");
                    break;
                case 4:
                    printf(" Khulna\n");
                    break;
                case 5:
                    printf(" Sylhet\n");
                    break;
                case 6:
                    printf(" Barishal\n");
                    break;
                case 7:
                    printf(" Rangpur\n");
                    break;
                case 8:
                    printf(" Mymensingh\n");
                    break;
                }
            }
            t_head = t_head->prev;
        }
        system("pause");
    }
    else
    {
        while(t_head->prev != NULL)
        {
            if(t_head->division == Division && t_head->approval_status == 1  && t_head->profile_status == 1)
            {
                printf("%-6d  ", t_head->user_id);///

                if(t_head->gender == 1) printf("Male    ");///
                else printf("Female  ");///

                printf("%-24s %d  ", t_head->name, t_head->age);///

                switch(t_head->division)
                {
                case 1:
                    printf(" Dhaka\n");
                    break;
                case 2:
                    printf(" Chittagong\n");
                    break;
                case 3:
                    printf(" Rajshahi\n");
                    break;
                case 4:
                    printf(" Khulna\n");
                    break;
                case 5:
                    printf(" Sylhet\n");
                    break;
                case 6:
                    printf(" Barishal\n");
                    break;
                case 7:
                    printf(" Rangpur\n");
                    break;
                case 8:
                    printf(" Mymensingh\n");
                    break;
                }
            }

            t_head = t_head->prev;
        }
        system("pause");

    }
}

void user_profile_list_view_single_gender(int Gender, int Division)
{
    userNode *t_head = head;
    while(t_head->next != NULL)
    {
        t_head = t_head->next;
    }

    system("cls");
    printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-\n");
    printf("\t\t\t\t\t\t|   Biodata list:   |\n");
    printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-\n");
    printf("ID      Gender  Name                     Age  Division\n");

    if(Division == 0)
    {
        while(t_head->prev != NULL)
        {
            if(t_head->gender == Gender && t_head->approval_status == 1  && t_head->profile_status == 1)
            {
                printf("%-6d  ", t_head->user_id);///

                if(t_head->gender == 1) printf("Male    ");///
                else printf("Female  ");///

                printf("%-24s %d  ", t_head->name, t_head->age);///

                switch(t_head->division)
                {
                case 1:
                    printf(" Dhaka\n");
                    break;
                case 2:
                    printf(" Chittagong\n");
                    break;
                case 3:
                    printf(" Rajshahi\n");
                    break;
                case 4:
                    printf(" Khulna\n");
                    break;
                case 5:
                    printf(" Sylhet\n");
                    break;
                case 6:
                    printf(" Barishal\n");
                    break;
                case 7:
                    printf(" Rangpur\n");
                    break;
                case 8:
                    printf(" Mymensingh\n");
                    break;
                }
            }
            t_head = t_head->prev;
        }
        system("pause");
    }
    else
    {
        while(t_head->prev != NULL)
        {
            if(t_head->gender == Gender && t_head->division == Division && t_head->approval_status == 1  && t_head->profile_status == 1)
            {
                printf("%-6d  ", t_head->user_id);///

                if(t_head->gender == 1) printf("Male    ");///
                else printf("Female  ");///

                printf("%-24s %d  ", t_head->name, t_head->age);///

                switch(t_head->division)
                {
                case 1:
                    printf(" Dhaka\n");
                    break;
                case 2:
                    printf(" Chittagong\n");
                    break;
                case 3:
                    printf(" Rajshahi\n");
                    break;
                case 4:
                    printf(" Khulna\n");
                    break;
                case 5:
                    printf(" Sylhet\n");
                    break;
                case 6:
                    printf(" Barishal\n");
                    break;
                case 7:
                    printf(" Rangpur\n");
                    break;
                case 8:
                    printf(" Mymensingh\n");
                    break;
                }
            }
            t_head = t_head->prev;
        }
        system("pause");
    }
}

///User part start

void user_guide(void)
{
    printf("Under Development!\n\n\n");
    system("pause");
}


void user_signup(void)
{
    userNode *t_head = head;
    while(t_head->next != NULL)
    {
        t_head = t_head->next;
    }

    for(int i = 0; i < 20;  i++)
    {
        t_head->saved_bio_list[i] = 0;
    }

    printf("Enter Your Email: ");
    fflush(stdin);
    char email[50];
    gets(email);

    int userID = id_initializer;
    id_initializer += 1;
    printf("Your User ID is                   : %d (Please save the ID for later use)\n", userID);
    int pass;
    do
    {
        printf("Enter Pass Word (Must be 6 digits): ");
        scanf("%d", &pass);
        if((pass < 100000) || (pass > 999999))
        {
            printf("Password is not a 6 digit integer.\nTry Again.\n");
        }
    }
    while((pass < 100000) || (pass > 999999));

    printf("Sign up Successful!\n\n");
    system("pause");

    system("cls");

    userNode* temp;
    temp = (userNode*)malloc(sizeof(userNode));

    temp->user_id = userID;
    temp->user_pass = pass;
    strcpy(temp->email, email);

    printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-**-*-*\n");
    printf("\t\t\t\t\t\t|   Welcome to Profile creation menu   |\n");
    printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-**-*-*\n");
    printf("Please Fill up the form below:\n\n");
    printf("Name            : ");
    char name[50];
    fflush(stdin);
    gets(name);
    strcpy(temp->name, name);

    printf("Select Gender   : \n");
    printf("1. Male\n2.Female\n");
    printf("Choose: ");
    do
    {
        scanf("%d",&temp->gender);
    }
    while((temp->gender < 1)||(temp->gender > 2));

    printf("Age             : ");
    scanf("%d",&temp->age);

    printf("Date of Birth   : ");
    char dob[20];
    fflush(stdin);
    gets(dob);
    strcpy(temp->DOB, dob);

    printf("Select Religion : \n");
    printf("1. Muslim\n2. Christian\n3. Hindu\n4. Buddha\n");
    printf("Choose: ");
    do
    {
        scanf("%d", &temp->religion);
    }
    while((temp->religion < 1)||(temp->religion > 4));

    printf("Height          : ");
    scanf("%f", &temp->height);

    printf("Blood Group     : ");
    char BG[5];
    fflush(stdin);
    gets(BG);
    strcpy(temp->blood_group, BG);

    printf("Phone Number    : ");
    char phone[20];
    fflush(stdin);
    gets(phone);
    strcpy(temp->phone, phone);

    printf("NID Number      : ");
    char nid[20];
    fflush(stdin);
    gets(nid);
    strcpy(temp->nid, nid);

    printf("Select Division : \n");
    printf("1. Dhaka\n2. Chittagong\n3. Rajshahi\n4. Khulna\n");
    printf("5. Sylhet\n6. Barishal\n7. Rangpur\n8. Mymenshingh\n");
    printf("Choose: ");
    do
    {
        scanf("%d", &temp->division);
    }
    while((temp->division < 1)||(temp->division > 8));

    printf("District        : ");
    char district[50];
    fflush(stdin);
    gets(district);
    strcpy(temp->district, district);

    printf("Detailed Address: ");
    char DA[1000];
    fflush(stdin);
    gets(DA);
    strcpy(temp->detailed_address, DA);

    printf("Select Job      : \n");
    printf("1. Company\n2. Business\n3. Student\n4. Unemployed\n");
    printf("Choose: ");
    do
    {
        scanf("%d", &temp->job_status);
    }
    while((temp->job_status < 1) || (temp->job_status > 4));

    printf("Marital Status  : ");
    char MS[20];
    fflush(stdin);
    gets(MS);
    strcpy(temp->marital_status, MS);

    printf("Educational Info: ");
    char EI[1000];
    fflush(stdin);
    gets(EI);
    strcpy(temp->edu_info, EI);

    printf("About You       : ");
    char AY[10000];
    fflush(stdin);
    gets(AY);
    strcpy(temp->about_me, AY);

    temp->approval_status = 0;
    temp->profile_status = 1;

    temp->prev = t_head;
    temp->next = NULL;
    t_head->next = temp;

    system("cls");
    printf("Sing Up Successful!\n Your ID is %d. Please save the Id for later Usage.", userID);
    system("pause");
}

int user_login(void)
{
    userNode *t_head = head;
    system("cls");
    printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("\t\t\t\t\t\t|   User Verification menu   |\n");
    printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("Enter your ID:");
    int userID;
    scanf("%d", &userID);

    int check = 0;
    while(t_head != NULL)
    {
        if(t_head->user_id == userID)
        {
            check = 1;
            break;
        }
        t_head = t_head->next;
    }

    if(check == 1)
    {
        while(1)
        {
            printf("Enter Password: ");
            int pass;
            scanf("%d", &pass);

            if(t_head->user_pass == pass)
            {
                return userID;
            }
            else
            {
                printf("Wrong Password!\n");
                printf("Enter: \n");
                printf("1. Try again\n");
                printf("2. Recover Password\n");
                printf("0. Go back to main menu\n");

                int ch;
                do
                {
                    printf("Your Choice: ");
                    scanf("%d", &ch);
                    if(ch < 0 && ch > 2) printf("Wrong option!\n");
                }
                while(ch < 0 && ch > 2);

                int otp;
                switch(ch)
                {
                case 1:
                    continue;
                    break;
                case 2:
                    system("cls");
                    printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
                    printf("\t\t\t\t\t\t|   Password Recovery Menu   |\n");
                    printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
                    printf("Enter the OTP sent to your phone: ");
                    scanf("%d", &otp);

                    if(otp == 1234)
                    {
                        printf("Your ID is  : %d\n", t_head->user_id);
                        printf("Your Pass is: %d\n\n\n", t_head->user_pass);
                        printf("Sending you back to the Main menu.\n");
                        system("pause");
                        return -1;

                    }
                    else
                    {
                        printf("Wrong OTP!\nSending you back to the Main menu.\n");
                        system("pause");
                        return -1;
                    }
                case 0:
                    return -1;
                }
            }
        }
    }
    else
    {
        printf("User not found!\n\n\n");
        printf("Enter:\n");
        printf("1. Search Id by email\n");
        printf("0. Return to Main Menu\n");

        int ch;
        do
        {
            printf("Your Choice: ");
            scanf("%d", &ch);
            if(ch < 0 && ch > 1) printf("Wrong Option!");
        }
        while(ch < 0 && ch > 1);

        switch(ch)
        {
        case 1:
            printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
            printf("\t\t\t\t\t\t|   ID and Password Recovery Menu   |\n");
            printf("\t\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
            printf("Enter your Email: ");
            char email[50];
            fflush(stdin);
            gets(email);

            check = 0;
            t_head = head;
            while(t_head != NULL)
            {
                if(strcmp(t_head->email, email) == 0)
                {
                    check = 1;
                    break;
                }
                t_head = t_head->next;
            }

            if(check == 1)
            {
                printf("Enter the OTP sent to your phone: ");
                int otp;
                scanf("%d", &otp);
                if(otp == 1234)
                {
                    printf("\n\nYour ID is  : %d", t_head->user_id);
                    printf("Your Pass is: %d", t_head->user_pass);
                    printf("Sending you back to the Main menu.\n");
                    system("pause");
                    return -1;
                }
                else
                {
                    printf("Wrong OTP!\nSending you back to the Main menu.\n");
                    system("pause");
                    return -1;
                }
            }
            else
            {
                printf("Email is not Registered!\n");
                system("pause");
                return -1;
            }


        case 0:
            return -1;
        }
    }
}

void user_menu(int userID)
{
    while(1)
    {
        system("cls");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("\t\t\t\t\t|           User Menu (ID: %d)              |\n", userID);
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("\t\t\t\t--------------------------------------------------------------------\n");
        printf ("\t\t\t\t..................................................................\n");
        printf ("\t\t\t\t|       1. Check Account Status                                  |\n");
        printf ("\t\t\t\t................................................................\n\n");
        printf ("\t\t\t\t...................................................................\n");
        printf ("\t\t\t\t|       2. Edit Profile                                          |\n");
        printf ("\t\t\t\t................................................................\n\n");
        printf ("\t\t\t\t..................................................................\n");
        printf ("\t\t\t\t|       3. Apply for an OTP.(One OPT to unlock one Bio-data)     |\n");
        printf ("\t\t\t\t................................................................\n\n");
        printf ("\t\t\t\t..................................................................\n");
        printf ("\t\t\t\t|       4. Unlock a BIO                                          |\n");
        printf ("\t\t\t\t................................................................\n\n");
        printf ("\t\t\t\t..................................................................\n");
        printf ("\t\t\t\t|       5. Watch Unlocked Bio datas                              |\n");
        printf ("\t\t\t\t................................................................\n\n");
        printf ("\t\t\t\t..................................................................\n");
        printf ("\t\t\t\t|       6. Publish or Unpublish Own profile                      |\n");
        printf ("\t\t\t\t................................................................\n\n");
        printf ("\t\t\t\t..................................................................\n");
        printf ("\t\t\t\t|       0. Go back to main menu                                  |\n");
        printf ("\t\t\t\t................................................................\n\n");

        int ch;
        scanf("%d",&ch);

        if(ch == 0) break;

        int ApprovalStatus;
        switch(ch)
        {
        case 1:
            ApprovalStatus = user_acc_status(userID);
            if(ApprovalStatus == 1)
            {
                printf("Profile has been approved!\n\n\n");
                system("pause");
            }
            else if(ApprovalStatus == -1)
            {
                printf("Profile has been declined!\nPlease Contact Admin for further query!\nContact:018xxxxxxx\n\n\n");
                system("pause");
            }
            else if(ApprovalStatus == -2)
            {
                printf("User has been Banned!\nPlease Contact Admin for further query!\nContact:018xxxxxxx\n\n\n");
                system("pause");
            }
            else
            {
                printf("Approval Pending. Thank you for having patience!\n\n\n");
                system("pause");
            }
            break;
        case 2:
            edit_user_profile(userID);
            break;
        case 3:
            apply_otp();
            break;
        case 4:
            unlock_biodata(userID);
            break;
        case 5:
            show_unlocked_biodata(userID);
            break;
        case 6:
            publish_unpublish_profile(userID);
            break;
        }
    }
}

int user_acc_status(int userID)
{
    userNode *t_head = head;
    while(t_head->user_id != userID)
    {
        t_head = t_head->next;
    }
    return t_head->approval_status;
}

void edit_user_profile(int userID)
{
    userNode *t_head;
    t_head = head;

    while(t_head->user_id != userID)
    {
        t_head = t_head->next;
    }

    int ch;

    ///Name
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your Name: %s\n", t_head->name);
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter new name: ");
        char name[50];
        fflush(stdin);
        gets(name);
        strcpy(t_head->name, name);
        printf("Name has been changed Successfully!!\n\n\n");
        system("pause");
    }

    ///Age
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your Age: %d\n", t_head->age);
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter New Age: \n");
        int age;
        scanf("%d", &age);
        t_head->age = age;
        printf("Age has been changed Successfully!\n\n\n");
        system("pause");
    }

    ///Date of birth
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your *Date of Birth*: %s\n", t_head->DOB);
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter new Date of birth: \n");
        char dob[20];
        fflush(stdin);
        gets(dob);
        strcpy(t_head->DOB, dob);
        printf("Date of birth has been changed successfully!\n\n\n");
        system("pause");
    }

    ///Religion
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your \n");
    switch(t_head->religion)
    {
    case 1:
        printf("religion: Islam\n");
        break;
    case 2:
        printf("religion: Christian\n");
        break;
    case 3:
        printf("religion: Hindu\n");
        break;
    case 4:
        printf("religion: Buddha\n");
        break;
    }

    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nSelect Religion : \n");
        printf("1. Muslim\n2. Christian\n3. Hindu\n4. Buddha\n");
        printf("Choose: ");
        int op;
        do
        {
            scanf("%d", &op);
            if(op < 1 && op >4) printf("Wrong option!");
        }
        while(op < 1 && op >4);

        t_head->religion =  op;
        printf("Religion has been changed successfully!\n\n\n");
        system("pause");
    }

    ///Height
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Height: %.2f\n", t_head->height);
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter new height: \n");
        float height;
        scanf("%f", &height);
        t_head->height = height;
        printf("Height has been changed successfully!\n\n\n");
        system("pause");
    }

    /// Email Address
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your *Email Address*: %s\n", t_head->email);
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter new Email Adress: \n");
        char email[50];
        fflush(stdin);
        gets(email);
        strcpy(t_head->email, email);
        printf("Email has been changed successfully!\n\n\n");
        system("pause");
    }

    ///Phone number
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your *Phone Number*: %s\n", t_head->phone);
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter new Phone number: \n");
        char phone[20];
        fflush(stdin);
        gets(phone);
        strcpy(t_head->phone, phone);
        printf("Phone Number has been changed successfully!\n\n\n");
        system("pause");
    }

    ///Division
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your ");
    switch(t_head->division)
    {
    case 1:
        printf("division is: Dhaka\n");
        break;
    case 2:
        printf("division is: Chittagong\n");
        break;
    case 3:
        printf("division is: Rajshahi\n");
        break;
    case 4:
        printf("division is: Khulna\n");
        break;
    case 5:
        printf("division is: Sylhet\n");
        break;
    case 6:
        printf("division is: Barishal\n");
        break;
    case 7:
        printf("division is: Rangpur\n");
        break;
    case 8:
        printf("division is: Mymensingh\n");
        break;
    }
    ch = want_to_change();
    if(ch == 1)
    {
        printf("Select Division : \n");
        printf("1. Dhaka\n2. Chittagong\n3. Rajshahi\n4. Khulna\n");
        printf("5. Sylhet\n6. Barishal\n7. Rangpur\n8. Mymenshingh\n");
        printf("Choose: ");
        do
        {
            scanf("%d", &t_head->division);
        }
        while((t_head->division < 1)||(t_head->division > 8));
        printf("Division has been changed successfully!\n\n\n");
        system("pause");
    }

    ///District
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your district: %s\n", t_head->district);
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter new district: \n");
        char district[50];
        fflush(stdin);
        gets(district);
        strcpy(t_head->district, district);
        printf("District has been changed successfully!\n\n\n");
        system("pause");
    }

    ///Detailed Address
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your current address is: ");
    char DA[1000];
    strcpy(DA, t_head->detailed_address);
    int i = 0;
    while(DA[i] != '\0')
    {
        if(DA[i] == '*') printf("\n\t\t\t\t\t");
        else printf("%c", DA[i]);
        i++;
    }
    printf("\n");
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter new Address: \n");
        char address[1000];
        fflush(stdin);
        gets(address);
        strcpy(t_head->detailed_address, address);
        printf("Address has been updated successfully!\n\n\n");
        system("pause");
    }

    ///Job Status
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your current ");
    switch(t_head->job_status)
    {
    case 1:
        printf("job status: Company\n");
        break;
    case 2:
        printf("job status: Business\n");
        break;
    case 3:
        printf("job status: Student\n");
        break;
    case 4:
        printf("job status: Unemployed\n");
        break;
    }
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nSelect new job: \n");
        printf("1. Company\n2. Business\n3. Student\n4. Unemployed\n");
        printf("Choose: ");
        do
        {
            scanf("%d", &t_head->job_status);
            if((t_head->job_status < 1) || (t_head->job_status > 4))
            {
                printf("Wrong option!\n");
            }
        }
        while((t_head->job_status < 1) || (t_head->job_status > 4));
        printf("Religion has been changed successfully!\n\n\n");
        system("pause");
    }

    ///Marital Status
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Your Current marital status: %s\n", t_head->marital_status);
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter current marital status: \n");
        char marital_status[20];
        fflush(stdin);
        gets(marital_status);
        strcpy(t_head->marital_status, marital_status);
        printf("Marital status has been Updated successfully!\n\n\n");
        system("pause");
    }

    ///Edu info
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Current Educational Info: ");
    char EI[1000];
    strcpy(EI, t_head->edu_info);
    i = 0;
    while(EI[i] != '\0')
    {
        if(EI[i] == '*') printf("\n                           ");
        else printf("%c", EI[i]);
        i++;
    }
    printf("\n");
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter Educational info Again fully: \n");
        char EdInfo[1000];
        fflush(stdin);
        gets(EdInfo);
        strcpy(t_head->edu_info, EdInfo);
        printf("Educational information has been changed successfully!\n\n\n");
        system("pause");
    }

    ///about me
    system("cls");
    printf("\t\t\tUser ID: %d\n", userID);
    printf("-------------------------------------------\n");
    printf("Current Informations about you: ");
    char AM[10000];
    strcpy(AM, t_head->about_me);
    i = 0;
    while(AM[i] != '\0')
    {
        if(AM[i] == '*') printf("\n                                ");
        else printf("%c", AM[i]);
        i++;
    }
    printf("\n");
    ch = want_to_change();
    if(ch == 1)
    {
        printf("\nEnter Info About you Again fully: \n");
        char AM[1000];
        fflush(stdin);
        gets(AM);
        strcpy(t_head->about_me, AM);
        printf("Informations about you has been changed successfully!\n\n\n");
        system("pause");
    }
    system("cls");
    printf("Now viewing Full Profile after the edit.....\n\n\n");
    system("pause");
    view_full_user_profile(userID);
}

int want_to_change(void)
{
    int ch;
    do
    {
        printf("1. Change\n");
        printf("2. Leave it as it is\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        if(ch < 1 && ch > 2) printf("Wrong option!\n");
    }
    while(ch < 1 && ch > 2);

    return ch;
}

void view_full_user_profile(int userID)
{
    system("cls");
    userNode *t_head = head;
    int check = 0;
    while(t_head != NULL)
    {
        if(t_head->user_id == userID)
        {
            check = 1;
            break;
        }
        t_head = t_head->next;
    }

    if(check == 0)
    {
        printf("User Not Found! Please Try again.\n\n\n");
        system("pause");
        return;
    }
    else
    {
        printf("\t\t\tUser ID: %d\n", userID);
        printf("-------------------------------------------\n", userID);
        printf("Name              : %s\n", t_head->name);

        if(t_head->gender == 1) printf("Gender            : Male\n");
        else printf("Gender            : Female\n");

        printf("Age               : %d\n", t_head->age);
        printf("*Date of Birth*   : %s\n", t_head->DOB);

        switch(t_head->religion)
        {
        case 1:
            printf("Religion          : Islam\n");
            break;
        case 2:
            printf("Religion          : Christian\n");
            break;
        case 3:
            printf("Religion          : Hindu\n");
            break;
        case 4:
            printf("Religion          : Buddha\n");
            break;
        }

        printf("Height            : %.2f\n", t_head->height);
        printf("Blood Group       : %s\n", t_head->blood_group);
        printf("*Email Address*   : %s\n", t_head->email);
        printf("*Phone Number*    : %s\n", t_head->phone);
        printf("*NID Number*      : %s\n", t_head->nid);

        switch(t_head->division)
        {
        case 1:
            printf("Division          : Dhaka\n");
            break;
        case 2:
            printf("Division          : Chittagong\n");
            break;
        case 3:
            printf("Division          : Rajshahi\n");
            break;
        case 4:
            printf("Division          : Khulna\n");
            break;
        case 5:
            printf("Division          : Sylhet\n");
            break;
        case 6:
            printf("Division          : Barishal\n");
            break;
        case 7:
            printf("Division          : Rangpur\n");
            break;
        case 8:
            printf("Division          : Mymensingh\n");
            break;
        }

        printf("District          : %s\n", t_head->district);

        printf("*Detailed Address*: ");
        char DA[1000];
        strcpy(DA, t_head->detailed_address);
        int i = 0;
        while(DA[i] != '\0')
        {
            if(DA[i] == '*') printf("\n\t\t\t\t\t");
            else printf("%c", DA[i]);
            i++;
        }
        printf("\n");

        switch(t_head->job_status)
        {
        case 1:
            printf("Job Status        : Company\n");
            break;
        case 2:
            printf("Job Status        : Business\n");
            break;
        case 3:
            printf("Job Status        : Student\n");
            break;
        case 4:
            printf("Job Status        : Unemployed\n");
            break;
        }

        printf("Marital Status    : %s\n", t_head->marital_status);
        printf("Educational Info  : ");
        char EI[1000];
        strcpy(EI, t_head->edu_info);
        i = 0;
        while(EI[i] != '\0')
        {
            if(EI[i] == '*') printf("\n                    ");
            else printf("%c", EI[i]);
            i++;
        }
        printf("\n");

        printf("About Me          : ");
        char AM[10000];
        strcpy(AM, t_head->about_me);
        i = 0;
        while(AM[i] != '\0')
        {
            if(AM[i] == '*') printf("\n                    ");
            else printf("%c", AM[i]);
            i++;
        }
        printf("\n\n\n\n");

        system("pause");
    }
}

void apply_otp(void)
{
    system("cls");
    printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("\t\t\t\t\t|           OPT Generator:          |\n");
    printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("Enter the Mobile or Bank Number: ");
    char dump[50];
    //scanf("%d", &dump);
    fflush(stdin);
    gets(dump);
    printf("Enter Transaction ID           : ");

    fflush(stdin);
    gets(dump);

    printf("Number and ID matched!\n\n\nHere is your OTP: 1234\n(You can use a OTP to unlock only 1 Biodata)\n\n\n"); ///The OTP generator is a dummy function for now.
    system("pause");
}

void unlock_biodata(int userID)
{
    system("cls");
    userNode *t_head = head;

    while(t_head->user_id != userID)
    {
        t_head = t_head->next;
    }

    printf("Please enter the Biodata ID to unlock: ");
    int bioID;
    scanf("%d", &bioID);

    int check = 0;
    userNode *bio_head = head;
    while(bio_head != NULL)
    {
        if(bio_head->user_id == bioID)
        {
            check = 1;
            break;
        }
        bio_head = bio_head->next;
    }

    if(check == 0)
    {
        printf("The ID is wrong and not in the database.\n");
        system("pause");
        return;
    }

    printf("Please enter the OTP recieved via SMS: ");
    int otp;
    scanf("%d", &otp);

    int j;
    for(j = 19; j >= 0; j--)
    {
        if(t_head->saved_bio_list[j] == 0) break;
    }

    if(j < 0)//More development needed by using linked list. For now Maximum number of Bio that can be saved is 20.
    {
        printf("Reached Max limit for Unlocking Biodatas!\n");
        system("pause");
        return;
    }

    if(otp == 1234)
    {
        t_head->saved_bio_list[j] = bioID;
    }
    else
    {
        printf("\nWrong OTP! Sending you back to the User Menu.\n\n\n");
        system("pause");
        return;
    }

    printf("Biodata ID: %d has been unlocked! Watch unlocked Biodatas from User Menu.\n\n\n", bioID);
    system("pause");
}

void show_unlocked_biodata(userID)
{
    while(1)
    {
        system("cls");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("\t\t\t\t\t|    Unlocked Biodata Show Menut    |\n");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("1. ID List of all saved Biodata(s)\n");
        printf("2. Detailed biodata (You will need to know the user id)\n");
        printf("0. To go back to User Menu\n");

        int ch;
        scanf("%d", &ch);
        if(ch == 0) break;

        switch(ch)
        {
        case 1:
            biodata_list_view(userID);
            break;
        case 2:
            biodata_detailed_view(userID);
            break;
        }
    }
}

void biodata_list_view(int userID)
{
    userNode *t_head = head;

    while(t_head->user_id != userID)
    {
        t_head =t_head->next;
    }

    system("cls");
    printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("\t\t\t\t\t|          Unlocked ID List         |\n");
    printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    int check = 0;
    for(int i = 0; i < 20; i++)
    {
        if(t_head->saved_bio_list[i] > 0)
        {
            check++;
            printf("\t%d\n", t_head->saved_bio_list[i]);
        }
    }
    if(check == 0)
    {
        printf("You Have no saved Biodata!\n");
        system("pause");
        return;
    }
    printf("\n\n\n");
    system("pause");
}

void biodata_detailed_view(int userID)
{
    userNode *t_head = head;

    while(t_head->user_id != userID)
    {
        t_head =t_head->next;
    }

    system("cls");
    printf("Enter Unlocked ID to view full Biodata: ");
    int bioID;
    scanf("%d", &bioID);

    int check = 0;
    for(int i = 0; i < 20; i++)
    {
        if(t_head->saved_bio_list[i] == bioID)
        {
            check = 1;
            break;
        }
    }

    if(check == 0)
    {
        printf("You have not unlocked the Biodata. Sending you back to User menu.\n\n\n");
        system("pause");
    }
    view_full_user_profile(bioID);
}

void publish_unpublish_profile(int userID)
{
    userNode *t_head = head;

    while(t_head->user_id != userID)
    {
        t_head =t_head->next;
    }

    int ch = 0;
    do
    {
        system("cls");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("\t\t\t\t\t| User Preference about own profile |\n");
        printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
        printf("1. Publish Your Profile\n");
        printf("0. Unpublish Your Profile\n");
        scanf("%d", &ch);
        if(ch < 0 && ch > 1) printf("Wrong input!");
    }
    while(ch < 0 && ch > 1);

    if(ch == 1)
    {
        t_head->profile_status = 1;
        printf("Your profile Status is Public!\n\n\n");
        system("pause");
    }
    else
    {
        t_head->profile_status = 0;
        printf("Your profile is hidden from public!\n\n\n");
        system("pause");
    }
}
