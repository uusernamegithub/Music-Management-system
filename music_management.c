#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50
#define MAX_NARRATOR_LENGTH 50
#define MAX_GENRE_LENGTH 20
#define MAX_PREFERENCE_TYPE_LENGTH 20
#define MAX_LENGTH_OF_EMAIL 100
#define MAX_LENGTH_OF_NAME 100
#define TS_LEN 5


typedef struct Author {                     
    char authorName[MAX_AUTHOR_LENGTH];
    struct Author* next;  
}Author;

typedef struct Audiobook {
    int audiobookID;
    char title[MAX_TITLE_LENGTH];
    Author* authors;  
    char narrator[MAX_NARRATOR_LENGTH];
    char duration[7];
    char genre[MAX_GENRE_LENGTH];
    float rating;
    int no_of_users;
    struct Audiobook* next; 
}Audiobook;

typedef struct preferenceNode {
    char preferenceType[MAX_PREFERENCE_TYPE_LENGTH];
    char preferenceValue[50];
    struct preferenceNode* next;
}preferenceNode;

typedef struct audiobookLog {
    int ID; 
    Audiobook* book;
    char timestamp[TS_LEN];
    float rating ;
    struct audiobookLog* next;  
}audiobookLog;

typedef struct User {
    int userID;
    char name[MAX_LENGTH_OF_NAME];
    char email[MAX_LENGTH_OF_EMAIL];
    preferenceNode* preferences;
    audiobookLog* audiobookLogs;  
    struct User* next; 
}userList;



void initialise_Audiobook(Audiobook* AB);
void initialise_user(userList* UL);
void display_audiobooks(Audiobook* AB);
void display_users(userList* UL);
userList* middle_UL(userList* head);
userList* mergelist_for_user_id(userList* left , userList* right);
userList* sort_userlist_based_on_user_id(userList* head);
void edit_Audiobook(Audiobook **AB,int id);
void Add_Audiobook(Audiobook **AB);
void delete_audiobook(Audiobook **AB ,userList **UL,char s[],int is_s_author);
void search_audiobook(Audiobook *AB,char s[],int flag);
void Add_user_profile(userList **UL);
void add_to_user_library(userList **UL,Audiobook **AB );
void Listening_progress(userList **UL);
void all_AB_7(int user_ID , userList* UL);
void genre_AB_7(int user_ID , char genre_ip[] , userList* UL);
void rate_AB(int user_ID , int AB_ID , int new_rating , userList* UL);
void most_pop_AB(Audiobook* AB);
void listening_history_user(int user_ID , userList* UL);
void merge_user_libraries(int user_id_1 , int user_id_2 , userList* UL);
void listening_history_AB(int AB_ID , userList* UL);
Audiobook *sort_audiobooklist_based_on_rating(Audiobook *head);
void new_file(Audiobook* AB , userList* UL);


void initialise_Audiobook(Audiobook* AB){
    AB -> audiobookID = 0;
    AB -> title[0] = '\0';
    AB -> authors = NULL;
    AB -> narrator[0] = '\0';
    AB -> duration[0] = '\0';
    AB -> genre[0] = '\0';
    AB -> rating = 0.0;
    AB -> no_of_users = 0;
    AB -> next = NULL;
}

void initialise_user(userList* UL){
    UL -> userID = 0;
    UL -> name[0] = '\0';
    UL -> email[0] = '\0';
    UL -> preferences = NULL;
    UL -> audiobookLogs = NULL;
    UL -> next = NULL;
}

void display_audiobooks(Audiobook* AB){
    Audiobook* temp = AB;
    while(temp != NULL){
        printf("audiobook ID   :  %d\n" , temp -> audiobookID);
        printf("audiobook title   :  %s\n" , temp -> title);
        Author* trav = (temp -> authors);
        printf("authors  :\n");
        while(trav){
            printf("       %s\n" , trav -> authorName);
            trav = trav -> next;
        }
        printf("narrator   :  %s\n" , temp -> narrator);
        printf("duration   :  %s\n" , temp -> duration);
        printf("genre   :  %s\n" , temp -> genre);
        printf("rating   :  %f\n" , temp -> rating);
        printf("no of users rated   :  %d\n\n" , temp -> no_of_users);
        temp = temp -> next;
    }
    printf("end of audio book list\n\n\n");
}

void display_users(userList* UL){
    userList* temp = UL;
    while(temp){
        printf("user ID   :  %d\n" , temp -> userID);
        printf("name   :  %s\n" , temp -> name);
        printf("email   :  %s\n" , temp -> email);
        preferenceNode* pn = temp -> preferences;
        printf("preferences   :\n");
        while(pn){
            printf("preference type   :  %s\n" , pn -> preferenceType);
            printf("     %s\n" , pn -> preferenceValue);
            pn = pn -> next;
        }
        printf("\n");
        audiobookLog* al = temp -> audiobookLogs;
        printf("user library   :\n");
        while(al){
            printf("audio book ID   :  %d\n" , al -> ID);
            printf("time stamp   :  %s\n" , al -> timestamp);
            printf("rating   :  %f\n\n" , al -> rating);
            al = al -> next;
        }
        printf("\n");
        temp = temp -> next;
    }
    printf("end of user list\n\n");
}

// Audiobook* insert_AB(Audiobook* AB , Audiobook* temp_AB){
//     Audiobook* retval = temp_AB;
//     if(AB){
//         Audiobook* curr = AB;
//         Audiobook* prev = NULL;
//         while(curr && curr -> audiobookID < temp_AB -> audiobookID){
//             prev = curr;
//             curr = curr -> next;
//         }
//         if(prev == NULL){
//             temp_AB -> next = AB;
//         }
//         else{
//             if(curr == NULL){
//                 prev -> next = temp_AB;
//                 retval = AB;
//             }
//             else{
//                 prev -> next = temp_AB;
//                 temp_AB -> next = curr;
//                 retval = AB;
//             }
//         }
//     }
//     return retval;
// }

// userList* insert_UL(userList* UL , userList* temp_UL){
//     userList* retval = temp_UL;
//     if(UL){
//         userList* curr = UL;
//         userList* prev = NULL;
//         while(curr && curr -> userID < temp_UL -> userID){
//             prev = curr;
//             curr = curr -> next;
//         }
//         if(prev == NULL){
//             temp_UL -> next = UL;
//         }
//         else{
//             if(curr == NULL){
//                 prev -> next = temp_UL;
//                 retval = UL;
//             }
//             else{
//                 prev -> next = temp_UL;
//                 temp_UL -> next = curr;
//                 retval = UL;
//             }
//         }
//     }
//     return retval;
// }

userList* middle_UL(userList* head){
    userList* slow = head;
    userList* fast = head;
    while(fast -> next != NULL && fast -> next -> next != NULL){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow;
}

userList* mergelist_for_user_id(userList* left , userList* right)
{
    if(left==NULL){
        return right;
    }
    else if(right==NULL){
        return left;
    }
    else{
    userList* ans = (userList*)malloc(sizeof(userList)); 
    userList* curr = ans;
    while(left != NULL && right != NULL){
        if(left -> userID < right -> userID){
            curr -> next = left;
            left = left -> next;
        }
        else{
            curr -> next = right;
            right = right -> next;
        }
        curr = curr -> next;
    }
    if(left != NULL){
        curr->next=left;
    }
    else if(right != NULL){
        curr -> next = right;
    }
    return ans -> next;
    }
}

userList* sort_userlist_based_on_user_id(userList* head){
        if (head == NULL || head -> next == NULL){
            return head;
        }
        else{
            userList *newhead= head;
            userList *mid = middle_UL(head);
            newhead = mid -> next;
            mid -> next = NULL;
            userList* left = sort_userlist_based_on_user_id(head);
            userList* right = sort_userlist_based_on_user_id(newhead);
            return  mergelist_for_user_id(left , right);
        }
}


/*  1 -- b*/

void edit_Audiobook(Audiobook **AB,int id)
{
    Audiobook *temp=*AB;
    int found=0;
    while(temp!=NULL && found==0)
    {
        if(temp->audiobookID==id)
        {
            found=1;
        }
        else
        {
            temp=temp->next;
        }
    }
    if(found==0)
    {
        printf("NO AUDIOBOOK EXISTS WITH GIVEN ID \n");
    }
    else
    {   
        int f=0;
        int flag;
        char s[MAX_AUTHOR_LENGTH];
        while(f==0)
        {
         printf("Enter  1  if you wish to modify the Title of Audiobook      \n");
         printf("Enter  2  if you wish to modify the  Author of Audiobook \n");
         printf("Enter  3  if you wish to modify the duration of Audiobook \n");

          scanf("%d",&flag);
          if(flag<1||flag>3)
           {
                printf("plese enter a valid number ::\n");
           }
           else{
            f=1;
           }
         }
         if(flag==1)
         {
            printf("Enter the Title of Audiobook  : ");
            scanf("%s",s);
            strcpy(temp->title,s);
            printf("Data successfully modified \n");
         }
         else if(flag==2)
         {  
            char s1[MAX_AUTHOR_LENGTH];
            found=0;
            printf("Enter the Author of Audiobook  :");
            scanf("%s",s);
            printf("Enter the Author of Audiobook whom you wish to Replace : ");
            scanf("%s",s1);
            Author *A=temp->authors;
            while(A!=NULL && found==0)
            {
                if(strcmp(A->authorName,s1)==0)
                {
                    found=1;
                }
                else
                {
                    A=A->next;
                }
            }
            if(found==0)
            {
                printf("The entered Author do not exist \n");
            }
            else
            {
                strcpy(A->authorName,s);
                printf("Data successfully modified \n");
                
            }
         }
         else if(flag==3)
         {
             printf("Enter the Duration of Audiobook in HH:MM format : ");
             scanf("%s",s);
             strcpy(temp->duration,s);
             printf("Data successfully modified \n");
         }
       }
}

/*1 -a */

void Add_Audiobook(Audiobook **AB)
{   
    
    int n;
    int aud_id;
    printf("Enter the details of new Audiobook  : \n ");
    printf("Enter the audiobook ID : ");
    scanf("%d",&aud_id);
    Audiobook *l=*AB;
    int found_=0;
    while(l!=NULL)
    {
        if(l->audiobookID==aud_id)
        {
            found_=1;
        }
        l=l->next;
    }
    if(found_==0)
    {
        Audiobook *new=(Audiobook*)malloc(sizeof(Audiobook));
        initialise_Audiobook(new);
        new->audiobookID=aud_id;
        printf("Enter the Title of Audiobook : ");
    scanf("%s",new->title);
    printf("Enter number of authors of Audiobook : ");
    scanf("%d",&n);
    char s[MAX_AUTHOR_LENGTH];
    for(int i=0;i<n;i++)
    {
        printf("Enter the name of Author : ");
        scanf("%s",s);
        Author *A = (Author *)malloc(sizeof(Author));
        strcpy(A->authorName,s);
        A->next=new->authors;
        new->authors=A;
    }
    printf("Enter the Narrator of Audiobook : ");
    scanf("%s",new->narrator);
    printf("Enter the Duration of Audiobook : ");
    scanf("%s",new->duration);
    printf("Enter the genre of Audiobook : ");
    scanf("%s",new->genre);

    Audiobook *lptr=*AB;
    Audiobook *nptr=*AB;
    while( lptr!=NULL && new->audiobookID > lptr->audiobookID)
    {
        lptr=lptr->next;
    }
    if(lptr==*AB)
    {
        new->next=lptr;
        *AB=new;
    }
    else
    {
        while(nptr->next!=lptr)
        {
            nptr=nptr->next;
        }
        nptr->next=new;
        new->next=lptr;
    }
    printf("Audiobook successfully Added \n");
    }
    else
    {
        printf("There already exists an Audiobook in Audiobook list with provided ID \n");
    }
}

/* 2 */

void delete_audiobook(Audiobook **AB ,userList **UL,char s[],int is_s_author)
{   
    Audiobook *temp=*AB;
    Audiobook *prev=*AB;
    Author *A;
    int found=0;
    if(is_s_author==1)
    {
        while(temp!=NULL && found==0)
        {   
            A=temp->authors;
            while(A!=NULL && found==0 )
            {
                if(strcmp(A->authorName,s)==0)
                {
                    found=1;
                }
                else
                {
                    A=A->next;
                }
            }
            if(found==0)
            {
            prev=temp;
            temp=temp->next;
            }
        }
        if(found==0)
        {
            printf("no Audio file exists with given authors \n");
        }
        else
        {  
            userList *temp1 = *UL;
            audiobookLog *AL;
            audiobookLog *prev_log;
            while(temp1!=NULL)
            {
                AL=temp1->audiobookLogs;
                prev_log=temp1->audiobookLogs;
                while(AL!=NULL)
                {   
                    if(AL->ID==temp->audiobookID)
                    {   
                        
                        if(prev_log==AL && AL==temp1->audiobookLogs)
                       {  
                      
                          temp1->audiobookLogs=AL->next;
                          AL->next=NULL;
                          free(AL);
                          break;

                        }
                       else{
                         
                           prev_log->next=AL->next;
                           AL->next=NULL;
                           free(AL);
                           break; 
                          }
                    }
                    else
                    {   
                       
                        prev_log=AL;
                        AL=AL->next;
                    }
                }
            
                temp1=temp1->next;
            }

           if(prev==temp && temp==*AB)
           {
              *AB=temp->next;
              free(temp);
           }
           else{
           prev->next=temp->next;
           temp->next=NULL;
           free(temp);
           }
           printf("audiobook deleted successfully \n");
        }
    }
    else if(is_s_author==0)
    {
        while(temp!=NULL && found==0)
        {   
            if(strcmp(temp->title,s)==0)
            {
                found=1;
            }
            else{
            prev=temp;
            temp=temp->next;
            }
        }
        if(found==0)
        {
            printf("no Audio file exists with given title \n");
        }
        else
        {     
            userList *temp1 = *UL;
            audiobookLog *AL;
            audiobookLog *prev_log;
            while(temp1!=NULL)
            {
                AL=temp1->audiobookLogs;
                prev_log=temp1->audiobookLogs;
                while(AL!=NULL)
                {   
                    if(AL->ID==temp->audiobookID)
                    {   
                        
                        if(prev_log==AL && AL==temp1->audiobookLogs)
                       {  
                      
                          temp1->audiobookLogs=AL->next;
                          AL->next=NULL;
                          free(AL);
                          break;

                        }
                       else{
                         
                           prev_log->next=AL->next;
                           AL->next=NULL;
                           free(AL);
                           break; 
                          }
                    }
                    else
                    {   
                       
                        prev_log=AL;
                        AL=AL->next;
                    }
                }
            
                temp1=temp1->next;
            }
            if(prev==temp && temp==*AB)
           {
              *AB=temp->next;
              free(temp);
           }
           else{
           prev->next=temp->next;
           temp->next=NULL;
           free(temp);
           }
           printf("audiobook deleted successfully \n");
        }
    }
}

/* 3 */

void search_audiobook(Audiobook *AB,char s[],int flag)
{   
    Audiobook *temp=AB;
    int f=0;
    if(flag==1)
    {
        while(temp!=NULL)
        {
            if(strcmp(temp->title,s)==0)
            {
                printf("Audiobook matching requirements is found :");
                printf("Audiobook Id  : %d \n",temp->audiobookID);
                f=1;
            }
            temp=temp->next;
        }
    }
    else if(flag==2)
    {
        while(temp!=NULL)
        {
            if(strcmp(temp->genre,s)==0)
            {
                printf("Audiobook matching requirements is found :");
                printf("Audiobook Id  : %d \n",temp->audiobookID);
                f=1;
            }
            temp=temp->next;
        }
    }
    else if(flag==3)
    {   
        Author *A;
        while(temp!=NULL)
        {   
            A=temp->authors;
            while(A!=NULL)
            {
            if(strcmp(A->authorName,s)==0)
            {
                printf("Audiobook matching requirements is found :");
                printf("Audiobook Id  : %d \n",temp->audiobookID);
                f=1;
            }
            A=A->next;
           }
         temp=temp->next;
       } 
    }
    if(f==0)
    {
        printf("No such Audiobook Exists \n ");
    }
}

/*4 */

void Add_user_profile(userList **UL)
{   
     printf("Enter the details of the User  : \n");
     int iD;
     printf("Enter the userID  : ");
     scanf("%d",&iD);
     int found_=0;
     userList *u=*UL;
     while(u!=NULL)
     {
        if(u->userID==iD)
        {
            found_=1;
        }
        u=u->next;
     }
     
     if(found_==0)
     {
        userList *new=(userList*)malloc(sizeof(userList));
        initialise_user(new);
        new->userID=iD;
        
     printf("Enter the Name of the user : ");
     scanf("%s",new->name);
     printf("Enter the Email Address of user : ");
     char s[MAX_LENGTH_OF_EMAIL];
     scanf("%s",s);
     userList *lptr=*UL;
     while(lptr!=NULL)
     {
        if(strcmp(lptr->email,s)==0)
        {
            printf("This Email already Exists Please enter a new one : ");
            scanf("%s",s);
            lptr=*UL;
        }
        else
        {
            lptr=lptr->next;
        }
     }
     if(lptr==NULL)
     {
        strcpy(new->email,s);
     }
    
    char f[MAX_GENRE_LENGTH];
    printf("Do you have any preffered genre ? ");
    printf("if yes ! then enter the genre ,  else  enter No    :  ");
    scanf("%s",f);

    if(strcmp(f,"No")!=0)
    {   
        preferenceNode *p=(preferenceNode*)malloc(sizeof(preferenceNode));
        strcpy( p->preferenceType,"genre");
        strcpy(p->preferenceValue,f);
        p->next=new->preferences;
        new->preferences=p;
    }
    printf("Do you have any preffered author ? ");
    printf("if yes ! then enter the name of author  ,  else  enter No    :  ");
    scanf("%s",f);
    if(strcmp(f,"No")!=0)
    {   
        preferenceNode *q=(preferenceNode*)malloc(sizeof(preferenceNode));
        strcpy( q->preferenceType,"author");
        strcpy(q->preferenceValue,f);
        q->next=new->preferences;
        new->preferences=q;
    }
     printf("Do you have any preffered narrator ? ");
    printf("if yes ! then enter the name of narrator  ,  else  enter No     :  ");
    scanf("%s",f);
    if(strcmp(f,"No")!=0)
    {   
        preferenceNode *r=(preferenceNode*)malloc(sizeof(preferenceNode));
        strcpy( r->preferenceType,"narrator");
        strcpy(r->preferenceValue,f);
        r->next=new->preferences;
        new->preferences=r;
    }
userList *ptr=*UL;
userList *sptr=*UL;
    while( ptr!=NULL && new->userID > ptr->userID)
    {
        ptr=ptr->next;
    }
    if(ptr==*UL)
    {
        new->next=ptr;
        *UL=new;
    }
    else
    {
        while(sptr->next!=ptr)
        {
            sptr=sptr->next;
        }
        sptr->next=new;
        new->next=ptr;
    }

    printf("new user added successfully to userlist  \n");
     }
    else if(found_==1)
    {
        printf("The Entered userId Already Exists  \n");
    }

 }

/*5 */
void add_to_user_library(userList **UL,Audiobook **AB )
{   
    int id;
    char ch;
    printf("Enter the following Details to update the user library  :\n");
    printf("Enter the user ID  :  ");
    scanf("%d",&id);
    userList *temp=*UL;
    while(temp!=NULL && temp->userID!=id)
    {
         temp=temp->next;
    }
    if(temp==NULL)
    {
        printf("No user exists with given  id \n");
    }
    else
    {
        printf("enter y  if you wish to add an Audiobook to log  \n");
        printf("enter n  if you wish to delete an Audiobook from log \n ");
        printf("enter  :  ");
        fflush(stdin);
        scanf("%c",&ch);
        if(ch=='y')
        {   

            printf("Enter the Details of Audiobook : \n");
            int id;
            printf("Enter the id of Audiobook   :"  );
            scanf("%d",&id);
            audiobookLog *temp_log=temp->audiobookLogs;
            int flag=0;
            while(temp_log!=NULL)
            {
                if(id==temp_log->ID)
                {
                    flag=1;
                }
                temp_log=temp_log->next;
            }
            if(flag==1)
            {
                printf("This Audiobook Already Exists in Audiobooklog of User \n");
            }
            else
            {
                       
                Audiobook *temp_=*AB;
                int f=0;
                while(temp_!=NULL && f==0)
                {
                    if(temp_->audiobookID==id)
                    {
                        f=1;
                    }
                    else{
                        temp_=temp_->next;
                    }

                }
                if(f==1)
                {   
                    audiobookLog *p=(audiobookLog*)malloc(sizeof(audiobookLog));
                    p->ID=id;
                    strcpy(p->timestamp,"00:00\n");
                    p->rating=0.0;
                    p->book=temp_;
                    audiobookLog *t=temp->audiobookLogs;
                    audiobookLog *nptr=temp->audiobookLogs;
                    while( t!=NULL && p->ID > t->ID)
                    {
                     t=t->next;
                    }
                    if(t==temp->audiobookLogs)
                    {
                         p->next=t;
                        temp->audiobookLogs=p;
                    }
                     else
                    {  
        
                        while(nptr->next!=t)
                        {
                         nptr=nptr->next;
                        }
                        nptr->next=p;
                        p->next=t;
                    }     
                    printf("new audiobook added successfully  \n");
                }
                else if(f==0)
                 {
                     printf("The Entered audiobook is not part of AudioBook List  \n");
                 }
            }


        }

        else if(ch=='n')
        {  
            int found=0;
           printf("Enter Id of Audiobook you wish to delete   : ");
           scanf("%d",&id);
           audiobookLog *t=temp->audiobookLogs;
           audiobookLog *prev=temp->audiobookLogs;

           while(t!=NULL&&found==0)
           {
              if(t->ID==id)
              {
                found=1;
              }
              else
              {
                prev=t;
                t=t->next;
              }
           }
           if(found==0)
           {
               printf("No audiobook with provided id exists in users audio log book \n");
           }
           else
           {
              if(t->rating!=0)
              {
                
                int sum=t->book->no_of_users*t->book->rating;
                t->book->no_of_users--;
                sum-=t->rating;
                t->book->rating=sum/t->book->no_of_users;
              }  
              
              if(prev==t && t== temp->audiobookLogs)
              {
                temp->audiobookLogs=t->next;
                t->next=NULL;
                free(t);
              }
              else
              {
                prev->next=t->next;
                t->next=NULL;
                free(t);
              }
              printf("audiobook deleted successfully from users log  \n");
           }
        }
    }
}
 
 /*6 */

 /*Adds two timestamps to give a new timestamp */
 /*eg ,,  05:30 + 00:35 = 06:05 */
char *addstrings(char old[], char new[]) {
    int old_hours = (old[0] - '0') * 10 + (old[1] - '0');
    int old_minutes = (old[3] - '0') * 10 + (old[4] - '0');
    int new_hours = (new[0] - '0') * 10 + (new[1] - '0');
    int new_minutes = (new[3] - '0') * 10 + (new[4] - '0');
    int total_hours = old_hours + new_hours;
    int total_minutes = old_minutes + new_minutes;
    if (total_minutes > 59) {
        total_hours += total_minutes / 60;
        total_minutes %= 60;
    }
    char *result = (char *)malloc(6 * sizeof(char)); 
     result[0] = total_hours / 10 + '0';
    result[1] = total_hours % 10 + '0';
    result[2] = ':';
    result[3] = total_minutes / 10 + '0';
    result[4] = total_minutes % 10 + '0';
    result[5] = '\0';
    return result;
}
 
 /*Updates timestamp of a audiobook log of user  */
void Listening_progress(userList **UL)
{  
    int n;
   printf("Enter details of   ID of user to update the listening progress  :");
   scanf("%d",&n);
   int found=0;
   userList *temp=*UL;
   while(temp!=NULL && found==0)
   {                                    /*traversing and finding wheater user with given id exists or not */
    if(temp->userID==n)
    {
        found=1;
    }
    else
    {
        temp=temp->next;
    }
   }
   if(found==0)
   {
    printf("you have entered an invalid user  \n");
   }
   else
   {
      printf("Enter the Id of Audibook you would wish to update  :");
      scanf("%d",&n);
      audiobookLog *t=temp->audiobookLogs;
      found=0;
      while(t!=NULL && found==0)
      {
        if(t->ID==n)                   /*traversing and finding wheater Audiobook log  with given id exists or not in user  */
        {
            found=1;
        }
        else
        {
            t=t->next;
        }
      }
      if(found==0)
      {
        printf("you have entered an invalid user  \n");
      }
      else
      {   
          char ts[5];
          printf("Enter the new Timestamp  :  ");
          scanf("%s",ts);
          strcpy(t->timestamp,addstrings(t->timestamp,ts)); /*updating timestamp of Audiobook log of user */
          printf("timestamp updated successfully  \n");   
      }
   }
}



// merge

audiobookLog* divide(audiobookLog* head){
    if(head == NULL || head->next == NULL){
        return head;
    }
    audiobookLog* slow = head;
    audiobookLog* fast = head;
    audiobookLog* prev = NULL;

    while(fast != NULL && fast->next != NULL){
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if(prev != NULL){
        prev->next = NULL; 
    }
    return slow;
}


audiobookLog* merge(audiobookLog* head_1 , audiobookLog* head_2){
    audiobookLog* head;
    audiobookLog* trav_1 = head_1;
    audiobookLog* trav_2 = head_2;
    if(trav_2 == NULL){
        head = trav_1;
    }
    else if(trav_1 == NULL){
        head = trav_2;
    }
    else{
        if(strcmp(trav_1 -> timestamp , trav_2 -> timestamp) >= 0){
            head = trav_1;
            trav_1 = trav_1 -> next;
        }
        else{
            head = trav_2;
            trav_2 = trav_2 -> next;
        }
        audiobookLog* trav_head = head;
        while(trav_1 && trav_2){
            if(strcmp(trav_1 -> timestamp , trav_2 -> timestamp) >= 0){
                trav_head -> next = trav_1;
                trav_head = trav_1;
                trav_1 = trav_1 -> next;
            }
            else{
                trav_head -> next = trav_2;
                trav_head = trav_2;
                trav_2 = trav_2 -> next;
            }
        }
        while(trav_1){
            trav_head -> next = trav_1;
            trav_head = trav_1;
            trav_1 = trav_1 -> next;
        }
        while(trav_2){
            trav_head -> next = trav_2;
            trav_head = trav_2;
            trav_2 = trav_2 ->next;
        }
        trav_head -> next = NULL;
    }
    return head;
}

audiobookLog* merge_sort_timestamp(audiobookLog* head_abl){
    audiobookLog* head = head_abl;
    if (head && head->next){
        audiobookLog* half = divide(head);
        half = merge_sort_timestamp(half);
        head = merge_sort_timestamp(head);  
        head = merge(head, half);
    }
    return head;
}

//IN 7 TH DISPLAY ALL AUDIOBOOKS
void all_audiobooks(int user_ID , userList* UL){
    userList* trav_UL = UL;
    while(trav_UL && trav_UL -> userID < user_ID){
        trav_UL = trav_UL -> next;
    }
    if(trav_UL == NULL || trav_UL -> userID != user_ID){
        printf("user ID is not found in the user list\n");
    }
    else{
        audiobookLog* trav_abl = trav_UL -> audiobookLogs;
        audiobookLog* head_abl = NULL;

        audiobookLog* trav_head;
        while(trav_abl){
            audiobookLog* temp_abl = (audiobookLog*)malloc(sizeof(audiobookLog));
            temp_abl -> ID = trav_abl -> ID;
            temp_abl -> book = trav_abl -> book;
            strcpy(temp_abl -> timestamp , trav_abl -> timestamp);
            temp_abl -> rating = trav_abl -> rating;
            temp_abl -> next = NULL;
            if(head_abl){
                trav_head -> next = temp_abl;
                trav_head = temp_abl;
            }
            else{
                head_abl = temp_abl;
                trav_head = head_abl;
            }
            trav_abl = trav_abl -> next;
        }
        head_abl = merge_sort_timestamp(head_abl);
        trav_head = head_abl;
        while(trav_head){
            printf("audiobook ID   :  %d\n" , trav_head -> ID);
            printf("timestamp   :  %s\n\n" , trav_head -> timestamp);
            trav_head = trav_head -> next;
        }
        printf("end\n\n");
    }
}

// 7 TH BY GENRE
void by_genre(int user_ID , char genre_ip[] , userList* UL){
    userList* trav_UL = UL;
    while(trav_UL && trav_UL -> userID < user_ID){
        trav_UL = trav_UL -> next;
    }
    if(trav_UL == NULL || trav_UL -> userID != user_ID){
        printf("user ID is not found in the user list\n");
    }
    else{
        audiobookLog* trav_abl = trav_UL -> audiobookLogs;
        audiobookLog* head_abl = NULL;

        audiobookLog* trav_head;
        while(trav_abl){
            if(strcmp(trav_abl -> book -> genre , genre_ip) == 0){
                audiobookLog* temp_abl = (audiobookLog*)malloc(sizeof(audiobookLog));
                temp_abl -> ID = trav_abl -> ID;
                temp_abl -> book = trav_abl -> book;
                strcpy(temp_abl -> timestamp , trav_abl -> timestamp);
                temp_abl -> rating = trav_abl -> rating;
                temp_abl -> next = NULL;
                if(head_abl){
                    trav_head -> next = temp_abl;
                    trav_head = temp_abl;
                }
                else{
                    head_abl = temp_abl;
                    trav_head = head_abl;
                }
            }
            trav_abl = trav_abl -> next;
        }
        head_abl = merge_sort_timestamp(head_abl);
        trav_head = head_abl;
        while(trav_head){
            printf("audiobook ID   :  %d\n" , trav_head -> ID);
            printf("genre   :  %s\n" , trav_head -> book -> genre);
            printf("timestamp   :  %s\n\n" , trav_head -> timestamp);
            trav_head = trav_head -> next;
        }
        printf("end\n\n");
    }
}

audiobookLog* merge_ABL_7(audiobookLog* head_1 , audiobookLog* head_2){
    audiobookLog* head;
    audiobookLog* trav_1 = head_1;
    audiobookLog* trav_2 = head_2;
    if(trav_2 == NULL){
        head = trav_1;
    }
    else if(trav_1 == NULL){
        head = trav_2;
    }
    else{
        if(trav_1 -> ID < trav_2 -> ID){
            head = trav_1;
            trav_1 = trav_1 -> next;
        }
        else{
            head = trav_2;
            trav_2 = trav_2 -> next;
        }
        audiobookLog* trav_head = head;
        while(trav_1 && trav_2){
            if(trav_1 -> ID < trav_2 -> ID){
                trav_head -> next = trav_1;
                trav_head = trav_1;
                trav_1 = trav_1 -> next;
            }
            else{
                trav_head -> next = trav_2;
                trav_head = trav_2;
                trav_2 = trav_2 -> next;
            }
        }
        while(trav_1){
            trav_head -> next = trav_1;
            trav_head = trav_1;
            trav_1 = trav_1 -> next;
        }
        while(trav_2){
            trav_head -> next = trav_2;
            trav_head = trav_2;
            trav_2 = trav_2 ->next;
        }
        trav_head -> next = NULL;
    }
    return head;
}

audiobookLog* merge_sort_ABL_7(audiobookLog* head_abl){
    audiobookLog* head = head_abl;
    if (head && head->next){
        audiobookLog* half = divide(head);
        half = merge_sort_ABL_7(half);
        head = merge_sort_ABL_7(head);  
        head = merge_ABL_7(head, half);
    }
    return head;
}

// 7 TH ANOTHER METHOD

// ALL AUDIO BOOKS
void all_AB_7(int user_ID , userList* UL){
    userList* trav_UL = UL;
    while(trav_UL && trav_UL -> userID < user_ID){
        trav_UL = trav_UL -> next;
    }
    if(trav_UL == NULL || trav_UL -> userID != user_ID){
        printf("user ID is not found in the user list\n");
    }
    else{
        trav_UL -> audiobookLogs = merge_sort_timestamp(trav_UL -> audiobookLogs);
        audiobookLog* trav_head = trav_UL -> audiobookLogs;
        while(trav_head){
            printf("audiobook ID   :  %d\n" , trav_head -> ID);
            printf("genre   :  %s\n" , trav_head -> book -> genre);
            printf("timestamp   :  %s\n\n" , trav_head -> timestamp);
            trav_head = trav_head -> next;
        }
        printf("end\n\n");
        trav_UL -> audiobookLogs = merge_sort_ABL_7(trav_UL -> audiobookLogs);
    }
}

// BY GENRE
 
void genre_AB_7(int user_ID , char genre_ip[] , userList* UL){
    userList* trav_UL = UL;
    while(trav_UL && trav_UL -> userID < user_ID){
        trav_UL = trav_UL -> next;
    }
    if(trav_UL == NULL || trav_UL -> userID != user_ID){
        printf("user ID is not found in the user list\n");
    }
    else{
        trav_UL -> audiobookLogs = merge_sort_timestamp(trav_UL -> audiobookLogs);
        audiobookLog* trav_head = trav_UL -> audiobookLogs;
        while(trav_head){
            if(strcmp(trav_head -> book -> genre , genre_ip) == 0){
                printf("audiobook ID   :  %d\n" , trav_head -> ID);
                printf("genre   :  %s\n" , trav_head -> book -> genre);
                printf("timestamp   :  %s\n\n" , trav_head -> timestamp);
            }
            trav_head = trav_head -> next;
        }
        printf("end\n\n");
        trav_UL -> audiobookLogs = merge_sort_ABL_7(trav_UL -> audiobookLogs);
    }
}

//  8 RATE_AUDIOBOOK


void rate_AB(int user_ID , int AB_ID , int new_rating , userList* UL){
    userList* trav_UL = UL;
    while(trav_UL && trav_UL -> userID < user_ID){       /*searching for the user in userlist  */
        trav_UL = trav_UL -> next;
    }
    if(trav_UL == NULL || trav_UL -> userID != user_ID){
        printf("enter valid user ID\n");
    }
    else{
        audiobookLog* trav_AB = trav_UL -> audiobookLogs;
        while(trav_AB && trav_AB ->ID < AB_ID){
            trav_AB = trav_AB -> next;                /*searching for Audiobook log in user's Audiobook logs */
        }
        if(trav_AB == NULL || trav_AB ->ID != AB_ID){
            printf("audiobook is not present in the given user ID\n");
        }
        else{
            int temp = trav_AB -> book -> no_of_users;
            temp = (trav_AB -> book -> rating) * temp;        /*updating no.of.users rated and rating of Audiobook in Audiobooklist */
            if(trav_AB -> rating != 0.0){
                temp -= trav_AB -> rating;
            }
            else{
                (trav_AB -> book -> no_of_users)++;
            }
            temp += new_rating;
            trav_AB -> book -> rating = temp /((trav_AB -> book -> no_of_users) * 1.0);
            trav_AB -> rating = new_rating;
            printf("rating has been recorded\n");
        }
    }
}

// 9 TH MOST POPULAR AUDIOBOOK

/*displays audiobook/audiobooks  with highest rating */
void most_pop_AB(Audiobook* AB){
    Audiobook* trav_AB = AB;
    Audiobook* max_rating = AB;
    while(trav_AB){
        if(trav_AB -> rating > max_rating -> rating){
            max_rating = trav_AB;                        /*finding Audiobook with highest rating */
        }
        trav_AB = trav_AB -> next;
    }
    if(max_rating -> rating == 0.0) printf("no rating have been given yet\n");
    else{
       trav_AB=AB;
       while(trav_AB)
       {
           if(trav_AB->rating == max_rating->rating)
           {

                printf("audiobook ID   :  %d\n" , trav_AB -> audiobookID);
                printf("title   :  %s\n" , trav_AB -> title);
                Author* trav_athr = trav_AB -> authors;
                printf("authors   :\n");
                while(trav_athr){
                   printf("    %s\n" , trav_athr -> authorName);
                   trav_athr = trav_athr -> next;
                }
                printf("rating   : %f\n\n" , trav_AB -> rating);

           }
           trav_AB=trav_AB->next;
       }
    }
}


//converting timestamp into hours and minutes

int convert(char timestamp[]){
    int retval = (int)(timestamp[0] - '0');
    retval = (retval * 10) + (int)(timestamp[1] - '0');
    retval = retval * 60;
    int min = (int)(timestamp[3] - '0');
    min = (10 * min) + (int)(timestamp[4] - '0');
    retval += min;
    return retval; 
}

// 10 LISTENING_HISTORY_REPORT_USER

/*Dislays total listening time of a user and also data of all Audiobook logs */
void listening_history_user(int user_ID , userList* UL){
    userList* trav_UL = UL;
    while(trav_UL && trav_UL -> userID < user_ID){   /*searching for a user */
        trav_UL = trav_UL -> next;
    }
    if(trav_UL == NULL || trav_UL -> userID != user_ID) printf("user id is not present\n");
    else{
        int total_list_time = 0;
        audiobookLog* trav_abl = trav_UL -> audiobookLogs;
        printf("deatails of audiobooks   : \n");
        while(trav_abl){          /*traversing through */
            printf("audiobook ID   :  %d\n" , trav_abl -> ID);
            printf("title   :  %s\n" , trav_abl -> book -> title);
            Author* trav_athr = trav_abl -> book -> authors;
            printf("authors   :\n");
            while(trav_athr){
                printf("    %s\n" , trav_athr -> authorName);
                trav_athr = trav_athr -> next;
            }
            printf("timestamp   :  %s\n" , trav_abl -> timestamp);
            printf("\n");
            total_list_time += convert(trav_abl -> timestamp);   /*updating total Listening time */
            trav_abl = trav_abl -> next;
        }
        printf("total listening time  :  %d  hr   %d  min\n" , total_list_time / 60 , total_list_time % 60);
    }
}

// 11 TH QUESTION MERGE USELIST LIBRARY AUDIOBOOK ID


audiobookLog* middle_UL_ABL(audiobookLog* head){
    audiobookLog* slow = head;
    audiobookLog* fast = head;
    while(fast -> next != NULL && fast -> next -> next != NULL){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow;
}

audiobookLog* merge_11_ABID(audiobookLog* left , audiobookLog* right)
{
    if(left==NULL){
        return right;
    }
    else if(right==NULL){
        return left;
    }
    else{
    audiobookLog* ans = (audiobookLog*)malloc(sizeof(audiobookLog)); 
    audiobookLog* curr = ans;
    while(left != NULL && right != NULL){
        if(left -> ID < right -> ID){
            curr -> next = left;
            left = left -> next;
        }
        else{
            curr -> next = right;
            right = right -> next;
        }
        curr = curr -> next;
    }
    if(left != NULL){
        curr->next=left;
    }
    else if(right != NULL){
        curr -> next = right;
    }
    return ans -> next;
    }
}

audiobookLog* sort_11_ABID(audiobookLog* head){
        if (head == NULL || head -> next == NULL){
            return head;
        }
        else{
            audiobookLog* newhead = head;
            audiobookLog* mid = middle_UL_ABL(head);
            newhead = mid -> next;
            mid -> next = NULL;
            audiobookLog* left = sort_11_ABID(head);
            audiobookLog* right = sort_11_ABID(newhead);
            return  merge_11_ABID(left , right);
        }
}

// 11TH QUESTION MERGE ACCORDING TO TITLE AND AUTHOR

audiobookLog* merge_title(audiobookLog* left , audiobookLog* right)
{
    if(left==NULL){
        return right;
    }
    else if(right==NULL){
        return left;
    }
    else{
    audiobookLog* ans = (audiobookLog*)malloc(sizeof(audiobookLog)); 
    audiobookLog* curr = ans;
    while(left != NULL && right != NULL){
        if(strcmp(left -> book -> title , right -> book -> title) < 0){
            curr -> next = left;
            left = left -> next;
        }
        else if(strcmp(left -> book -> title , right -> book -> title) > 0){
            curr -> next = right;
            right = right -> next;
        }
        else{
            Author* trav_left = left -> book -> authors;
            Author* trav_right = right -> book -> authors;
            int flag = 0;
            while(trav_left && trav_right && flag == 0){
                if(strcmp(trav_left -> authorName , trav_right -> authorName) > 0){
                    curr -> next = left;
                    left = left -> next;
                    flag = 1;
                }
                else if(strcmp(trav_left -> authorName , trav_right -> authorName) < 0){
                    curr -> next = right;
                    right = right -> next;
                    flag = 1;
                }
                else{
                    trav_left = trav_left -> next;
                    trav_right = trav_right -> next;
                }
            }
            if(flag == 0){
                if(trav_left == NULL){
                    curr -> next = left;
                    left = left -> next;
                }
                else{
                    curr -> next = right;
                    right = right -> next;
                }
            }
        }
        curr = curr -> next;
    }
    if(left != NULL){
        curr->next=left;
    }
    else if(right != NULL){
        curr -> next = right;
    }
    return ans -> next;
    }
}

audiobookLog* sort_title(audiobookLog* head){
        if (head == NULL || head -> next == NULL){
            return head;
        }
        else{
            audiobookLog* newhead = head;
            audiobookLog* mid = middle_UL_ABL(head);
            newhead = mid -> next;
            mid -> next = NULL;
            audiobookLog* left = sort_title(head);
            audiobookLog* right = sort_title(newhead);
            return  merge_title(left , right);
        }
}

// 11 TH MERGE_USER_LIBRARIES
audiobookLog* create_abl(audiobookLog* abl){
    audiobookLog* ret_abl = (audiobookLog*)malloc(sizeof(audiobookLog));
    ret_abl -> ID = abl -> ID;
    ret_abl -> book = abl -> book;
    strcpy(ret_abl -> timestamp , "00:00\n");
    ret_abl -> rating = 0.0;
    ret_abl -> next = NULL;
    return ret_abl;
}

void merge_user_libraries(int user_id_1 , int user_id_2 , userList* UL){
    userList* trav = UL;
    userList* u_1 = NULL;
    userList* u_2 = NULL;
    while(trav){
        if(trav -> userID == user_id_1){
            u_1 = trav;
        }
        else if(trav -> userID == user_id_2){
            u_2 = trav;
        }
        trav = trav -> next;
    }
    if(u_1 == NULL || u_2 == NULL){
        printf("enter valid ID\n");
    }
    else{
        audiobookLog* abl_1 = u_1 -> audiobookLogs;
        audiobookLog* abl_2 = u_2 -> audiobookLogs;
        audiobookLog* prev_1 = NULL;
        audiobookLog* prev_2 = NULL;
        while(abl_1 && abl_2){
            if(abl_1 -> ID < abl_2 -> ID){
                audiobookLog* temp = create_abl(abl_1);
                temp -> next = abl_2;
                if(prev_2 == NULL) {
                    u_2 -> audiobookLogs = temp;
                }
                else{
                    prev_2 -> next = temp;
                }
                prev_1 = abl_1;
                abl_1 = abl_1 -> next;
                prev_2 = temp;
            }
            else if(abl_1 -> ID > abl_2 -> ID){
                audiobookLog* temp = create_abl(abl_2);
                temp -> next = abl_1;
                if(prev_1 == NULL) u_1 -> audiobookLogs = temp;
                else prev_1 -> next = temp;
                prev_1 = temp;
                prev_2 = abl_2;
                abl_2 = abl_2 -> next;
            }
            else{
                prev_1 = abl_1;
                prev_2 = abl_2;
                abl_1 = abl_1 -> next;
                abl_2 = abl_2 -> next;
            }
        }
        while(abl_1){
            audiobookLog* temp = create_abl(abl_1);
            prev_2 -> next = temp;
            prev_2 = temp;
            abl_1 = abl_1 -> next;
        }
        while(abl_2){
            audiobookLog* temp = create_abl(abl_2);
            prev_1 -> next = temp;
            prev_1 = temp;
            abl_2 = abl_2 -> next;
        }
        printf("succesfully merged\n\n");
        u_1 -> audiobookLogs = sort_title(u_1 -> audiobookLogs);
        audiobookLog* print_abl = u_1 -> audiobookLogs;
        while(print_abl){
            printf("audio book ID   :  %d\n" , print_abl -> ID);
            printf("title   :  %s\n" , print_abl -> book -> title);
            Author* trav_athr_11 = print_abl -> book -> authors;
            printf("authors   :\n");
            while(trav_athr_11){
                printf("    %s\n" , trav_athr_11 -> authorName);
                trav_athr_11 = trav_athr_11 -> next;
            }
            print_abl = print_abl -> next;
        }
        u_1 -> audiobookLogs = sort_11_ABID(u_1 -> audiobookLogs);
    }
}

//  12  LISTENING HISTORY REPORT AUDIOBOOK

/*prints total listening time of a Audiobook in the whole userlist */
void listening_history_AB(int AB_ID , userList* UL){
    userList* trav_UL = UL;
    int total_list_time = 0;
    int flag = 0;
    while(trav_UL){         /*traversing through userlist */
        audiobookLog* trav_abl = trav_UL -> audiobookLogs;
        while(trav_abl && trav_abl -> ID != AB_ID && trav_abl -> ID < AB_ID){
            trav_abl = trav_abl -> next;                   /*searching for Audiobook in user Audiobook log*/
        }
        if(flag == 0 && trav_abl && trav_abl -> ID == AB_ID){
            printf("audiobook ID   :  %d\n" , AB_ID);             /*Audiobook is first time found --> print info  */
            printf("title   :  %s\n" , trav_abl -> book -> title);
            printf("author names   :\n");
            Author* trav_athr = trav_abl -> book -> authors;
            while(trav_athr){
                printf("     %s\n" , trav_athr -> authorName);
                trav_athr = trav_athr -> next;
            }
            printf("total listening time  :  ");
            flag = 1;
        }
        if(trav_abl && trav_abl -> ID == AB_ID){
            total_list_time += convert(trav_abl -> timestamp); /*updates total listening time */
        }
        trav_UL = trav_UL -> next;
    }
    if(flag == 0)
    { 
        printf("audiobook is not present\n");
    }
    else
    {
         printf("%d hr  %d min\n" , total_list_time / 60 , total_list_time % 60);
    }
}

//13 th question 
  
/*finding the middle node of linked list for the Merge Sort  */
Audiobook *middle(Audiobook *head){
    Audiobook *slow = head;
    Audiobook *fast = head;
    while(fast->next !=NULL && fast->next->next !=NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
/*this Merges two Linked List which are already Sorted based on rating */
Audiobook* mergelist_for_rating(Audiobook *left,Audiobook *right)
{
    if(left==NULL)
    {
        return right;
    }
    else if(right==NULL)
    {
        return left;
    }
    else if(left==NULL && right==NULL)
    {
        return NULL;
    }
    else
    {
    Audiobook *ans = (Audiobook*)malloc(sizeof(Audiobook)); 
    Audiobook *curr = ans;
    while(left != NULL && right!=NULL)
    {
        if(left->rating < right->rating)
        {
            curr->next = left;
            left=left->next;
        }
        else
        {
            curr->next = right;
            right=right->next;
        }
        curr=curr->next;
    }
    if(left!=NULL)
    {
        curr->next=left;
    }
    else if(right!=NULL)
    {
        curr->next=right;
    }
    return ans->next;
    }
}
/*Sorts the linked List based on Rating */
Audiobook *sort_audiobooklist_based_on_rating(Audiobook *head)
{
        if (head == NULL || head->next == NULL)
        {
            return head;
        }
        else
        {
            Audiobook *newhead= head;
            Audiobook *mid = middle(head);
            newhead= mid->next;
            mid->next=NULL;
            Audiobook *left = sort_audiobooklist_based_on_rating(head);
            Audiobook *right = sort_audiobooklist_based_on_rating(newhead);
            return  mergelist_for_rating(left,right);
        }
}

/*this Merges two Linked List which are already Sorted based on id */
Audiobook* mergelist_for_id(Audiobook *left,Audiobook *right)
{
    if(left==NULL)
    {
        return right;
    }
    else if(right==NULL)
    {
        return left;
    }
    else if(left==NULL && right==NULL)
    {
        return NULL;
    }
    else
    {
    Audiobook *ans = (Audiobook*)malloc(sizeof(Audiobook)); 
    Audiobook *curr = ans;
    while(left != NULL && right!=NULL)
    {
        if(left->audiobookID < right->audiobookID)
        {
            curr->next = left;
            left=left->next;
        }
        else
        {
            curr->next = right;
            right=right->next;
        }
        curr=curr->next;
    }
    if(left!=NULL)
    {
        curr->next=left;
    }
    else if(right!=NULL)
    {
        curr->next=right;
    }
    return ans->next;
    }
}
/*Sorts the linked List based on id */
Audiobook *sort_audiobooklist_based_on_id(Audiobook *head)
{
        if (head == NULL || head->next == NULL)
        {
            return head;
        }
        else
        {
            Audiobook *newhead= head;
            Audiobook *mid = middle(head);
            newhead= mid->next;
            mid->next=NULL;
            Audiobook *left = sort_audiobooklist_based_on_id(head);
            Audiobook *right = sort_audiobooklist_based_on_id(newhead);
            return  mergelist_for_id(left,right);
        }
}


/*After completion of all operations this function is called and it updates all the information into a new file
named new_dspd.txt   */

void new_file(Audiobook* AB , userList* UL){
    
    FILE* file;
    file = fopen("new_dspd.txt", "w");  /*opening file in write mode */

    Audiobook* trav_AB = AB;
    char line[50];                    /*this line is temporarily used to update info into the file */

    while (trav_AB) {                 /*traversing AudioBook list to update audiobook info into file  */
        fprintf(file, "@\n");         /*every Audiobook starts with '@' */
        sprintf(line, "%d", trav_AB->audiobookID);    /*converting int to char array */
        fprintf(file, "%s\n\n", line);

        fprintf(file, "%s\n\n", trav_AB->title);

        Author* trav_athr = trav_AB->authors;
        while (trav_athr) {
            fprintf(file, "%s\n", trav_athr->authorName);
            trav_athr = trav_athr->next;
        }
        fprintf(file, "\n");

        fprintf(file, "%s\n\n", trav_AB->narrator);
        fprintf(file, "%s\n\n", trav_AB->duration);
        fprintf(file, "%s\n\n", trav_AB->genre);

        sprintf(line, "%f", trav_AB->rating);     /*converting float into char array */
        fprintf(file, "%s\n\n", line);

        sprintf(line, "%d", trav_AB->no_of_users);       /*converting int to char array */
        fprintf(file, "%s\n\n", line);

        trav_AB = trav_AB->next;
    }

    userList* trav_UL = UL;           /*traversing user list to update user info into file  */
    while (trav_UL) {
        fprintf(file, "#\n");        /*Every user starts with '#' */
        sprintf(line, "%d", trav_UL->userID);           /*converting int to char array */
        fprintf(file, "%s\n\n", line);

        fprintf(file, "%s\n\n", trav_UL->name);
        fprintf(file, "%s\n\n", trav_UL->email);

        preferenceNode* trav_pn = trav_UL->preferences;
        while (trav_pn) {
            fprintf(file, "%s\n", trav_pn->preferenceType);
            fprintf(file, "%s\n", trav_pn->preferenceValue);
            trav_pn = trav_pn->next;
        }
        fprintf(file, "\n");

        audiobookLog* trav_abl = trav_UL->audiobookLogs;
        while (trav_abl) {
            sprintf(line, "%d", trav_abl->ID);      /*converting int to char array */
            fprintf(file, "%s\n", line);
            fprintf(file, "%s", trav_abl->timestamp);
            sprintf(line, "%f", trav_abl->rating);      /*converting float to char array */
            fprintf(file, "%s\n", line);
            trav_abl = trav_abl->next;
        }
        fprintf(file, "\n");
        trav_UL = trav_UL->next;
    }

    fclose(file);
    printf("successfully created a new file\n");
}



int main(){
    userList* UL = NULL;
    Audiobook* AB = NULL;
    
    /*inputting the audiobook info and userinfo from the file newfile_dspd.txt  */
    FILE* file;
    file = fopen("newfile_dspd.txt" , "r");   /*opening file in read mode */
    if(file == NULL){
        printf("error in opening file\n");
        return 1;
    }

    char line[1024];          /*this char array fetches data from file and inputs it into every structures */
    int flag = 0;
    int mode = 1;
    userList* temp_UL = (userList*)malloc(sizeof(userList));
    Audiobook* temp_AB = (Audiobook*)malloc(sizeof(Audiobook));

    while(fgets(line , sizeof(line) , file) != NULL){          /*loop runs till file is empty */
        line[strlen(line) - 1] = '\0';
        if(line[0] == '@'){                             /*if line[0]==@ the its an Audiobook */
            initialise_Audiobook(temp_AB);
            flag = 0;
            mode = 1;
        }

        else if(line[0] == '#'){                     /*if line[0]==# the its a uselist  */
            initialise_user(temp_UL);
            flag = 1;
            mode = 1;
        }
        
        else{
            if(line[0] == '\0'){             /*Every mode corresponds to new type of information */
                mode++;
                if(flag == 0 && mode == 9){
                    if(AB){                   /*inserting new audiobook at start of linked list */
                        temp_AB -> next = AB;
                        AB = temp_AB;
                    }
                    else{
                        AB = temp_AB;
                    }
                    temp_AB = (Audiobook*)malloc(sizeof(Audiobook));
                }
                else if(flag == 1 && mode == 6){
                    temp_UL -> audiobookLogs = sort_11_ABID(temp_UL -> audiobookLogs);
                    if(UL){                                                                  /*inserting new user at start of linked list */
                        temp_UL -> next = UL;
                        UL = temp_UL;
                    }
                    else{
                        UL = temp_UL;
                    }
                    temp_UL = (userList*)malloc(sizeof(userList));
                }
            }

            else{
                if(flag == 0){      /*flag==0    -->  audiobook info is being updated */
                    switch(mode){
                        case 1:
                             temp_AB -> audiobookID = atoi(line);
                    
                             break;
                        case 2:
                             strcpy(temp_AB -> title , line);
                             //printf("%s\n" , temp_AB -> title);
                             break;
                        case 3:
                        {
                            //printf("case 3\n");
                             Author* athr = (Author*)malloc(sizeof(Author));
                             strcpy(athr -> authorName , line);
                             //printf("%s\n" , athr -> authorName);
                             athr -> next = NULL;
                             Author* temp_author = (temp_AB -> authors);
                             while(temp_author && temp_author -> next){
                                temp_author = temp_author -> next;
                             }
                             if(temp_author == NULL) temp_AB -> authors = athr;
                             else temp_author -> next = athr;
                             
                             break;
                        }
                        case 4:
                             strcpy(temp_AB -> narrator , line);
                             break;
                        case 5:
                             strcpy(temp_AB -> duration , line);
                             //printf("%s\n" , temp_AB -> duration);
                             break;
                        case 6:
                             strcpy(temp_AB -> genre , line);
                             //printf("%s\n" , temp_AB -> genre);
                             break;
                        case 7:
                             temp_AB -> rating = atof(line);
                             break;
                        case 8:
                             temp_AB -> no_of_users = atoi(line);
                        default:
                             break;
                    }
                }
                else{               /*flag==1    -->  user info is being updated */
                    switch(mode){
                        case 1:
                             temp_UL -> userID = atoi(line);
                             //printf("%d\n" , temp_UL -> userID);
                             break;
                        case 2:
                             strcpy(temp_UL -> name , line);
                             break;
                        case 3:
                             strcpy(temp_UL -> email , line);
                             break;
                        case 4:
                        {
                             preferenceNode* temp_pn = temp_UL -> preferences;
                             while(temp_pn && temp_pn -> next){
                                temp_pn = temp_pn -> next;
                             }
                             preferenceNode* pfrn = (preferenceNode*)malloc(sizeof(preferenceNode));
                             strcpy(pfrn -> preferenceType , line);
                             fgets(line , sizeof(line) , file);
                             strcpy(pfrn -> preferenceValue , line);
                             pfrn -> next = NULL;
                             if(temp_pn == NULL){
                                temp_UL -> preferences = pfrn;
                             }
                             else{
                                temp_pn -> next = pfrn;
                             }
                             break;
                        }
                        case 5:
                        {
                             audiobookLog* abl = (audiobookLog*)malloc(sizeof(audiobookLog));
                             abl -> ID = atoi(line);
                             fgets(line , sizeof(line) , file);
                             strcpy(abl -> timestamp , line);
                             fgets(line , sizeof(line) , file);
                             abl -> rating = atof(line);
                             Audiobook* temp_book = AB;
                             while(abl -> ID != temp_book -> audiobookID){
                                temp_book = temp_book -> next;               /*searching for Audiobook in audiobook list */
                             }
                             abl -> book = temp_book;
                             abl -> next = NULL;
                             audiobookLog* trav_abl_ip = temp_UL -> audiobookLogs;
                             if(trav_abl_ip){
                                abl -> next = trav_abl_ip;
                                temp_UL -> audiobookLogs = abl;
                             }
                             else{
                                temp_UL -> audiobookLogs = abl;
                             }
                             break;
                        }
                        default:
                             break;
                    }
                }
            }
        }
    }

    AB = sort_audiobooklist_based_on_id(AB);  /*sorting audiobook based on id*/
    UL = sort_userlist_based_on_user_id(UL);  /*sorting user list based on id */


  printf("Welcome to online grpund portal :\n");
  int t_flag=0;
  while(t_flag==0)
  {
        system("cls");
        printf("Enter  1  if  you wish to Add or Edit an AudioBook  \n");
        printf("Enter  2  if  you wish to  delete an AudioBook  \n");
        printf("Enter  3  if  you wish  to  search an AudioBook  \n");
        printf("Enter  4  if  you wish to Add a User to UserList \n");
        printf("Enter  5  if  you wish  to add an Audiobook to Audiobook log of an User \n");
        printf("Enter  6  if  you wish  to  update the Timestamp of AudioBook  \n");
        printf("Enter  7  if  you wish to Display User Libraries \n");
        printf("Enter  8  if  you wish to Rate an AudioBook \n");
        printf("Enter  9  if  you wish to find out the Most Popular AudioBook \n");
        printf("Enter  10  if  you wish to diaplay Listening Progress Report of user \n");
        printf("Enter  11  if  you wish to Merge two User Libraries \n");
        printf("Enter  12  if  you wish to display Listening History report of an Audiobook \n");
        printf("Enter  13  if  you wish to sort Audiobooks based on Rating \n\n");
       
        int n,flag_=0;
       while(flag_==0)
       {
          printf("Enter a Valid Number (1-13)  :   "); 
          scanf("%d",&n);
          if(n<1||n>13)
         {
            printf(" Please  Enter  a  Valid  Number ! ! ! \n");
         }
         else
        {
          flag_=1; 
        }
       }

        switch(n){

            case 1:
            {
                int s;
                int g=0;
                while(g==0)
                {
                    printf("Enter 1 if you wish to add an AudioBook   \n");
                    printf("Enter 2 if you wish to edit an AudioBook   \n");
                    printf("enter  :  ");
                    scanf("%d",&s);
                    if(s==1||s==2)
                    {
                        g=1;
                    }
                    else
                    {
                        printf("Please Enter a valid number :  \n");
                    }
                }
                if(s==1)
                {
                    Add_Audiobook(&AB);
                }
                else if(s==2)
                {
                    printf("Enter the following details to edit a Audiobook \n");
                    int id ;
                    printf("Enter the Audiobook ID  : ");
                    scanf("%d",&id);
                    edit_Audiobook(&AB,id);
                    printf("\n");
                }
                break;
            }
            case 2:
            {
                 char s[MAX_TITLE_LENGTH];
                 int flag_;
                 int f=0;
                 printf("enter the following details to delete a Audiobook :: \n");
                 while(f==0)
                 {
                     printf("enter  1  if you wish to delete  based on Authors name      \n");
                     printf("Enter  0  if you wish to delete  base on Title of Audiobook \n");
                     scanf("%d",&flag_);
                     if(flag_<0||flag_>1)
                     {
                         printf("plese enter a valid number ::\n");
                         
                     }
                     else{
                             f=1;
                         }
                }
                 if(flag_==1)
                 {
                       printf("Enter the Authors name :\n");
                 }
                else{
                     printf("Enter the Title of Audiobook :\n");
                    }
                  fflush(stdin);
                  scanf("%s",&s);
                  fflush(stdin);
                  delete_audiobook(&AB,&UL,s,flag_);
                  printf("\n");
                  break;

            }
            case 3:
            {
                 char st[MAX_TITLE_LENGTH];
                 int flag1;
                 int f1=0;
                 printf("enter the following details to search for an Audiobook :: \n");
                  while(f1==0)
                 {
                      printf("Enter  1  if you wish to search based on Title of Audiobook      \n");
                      printf("Enter  2  if you wish to search  based on Genre of Audiobook \n");
                      printf("Enter  3  if you wish to search  based on Author of Audiobook \n");

                      scanf("%d",&flag1);
                      if(flag1<1||flag1>3)
                     {
                         printf("plese enter a valid number ::\n");
                     }
                      else{
                           f1=1;
                          }
                 }
                 if(flag1==1)
                 {
    
                    printf("Enter the Title of Audiobook :\n");
                 }
                else if(flag1==2){
                      printf("Enter the genre of Audiobook :\n");
                 }
                else{
                      printf("Enter the Author of Audiobook :\n");
                    }
                fflush(stdin);
                scanf("%s",&st);
                 fflush(stdin);
                 search_audiobook(AB,st,flag1);
                 printf("\n");
                 break;
            }
            case 4:
            {
                Add_user_profile(&UL);
                break;

            }
            case 5:
            {
                add_to_user_library(&UL,&AB);
                break;
            }
            case 6:
            {
                Listening_progress(&UL);
                break;
            }
            case 7:
            {
                int user_ID_7;
                int case_7;
                printf("enter user ID  :  ");
                scanf("%d" , &user_ID_7);
                printf("enter 1 to display all audiobooks\n");
                printf("enter 2 to display according to genre\n");
                scanf("%d" , &case_7);
                if(case_7 == 1){
                    all_AB_7(user_ID_7 , UL);
                }
                else if(case_7 == 2){
                    char pref_genre[50];
                    printf("enter preferred genre  :  ");
                    scanf("%s" , &pref_genre);
                    genre_AB_7(user_ID_7 , pref_genre , UL);
                }
                else{
                    printf("enter valid number\n");
                }
                break;
            }
            case 8:
            {
                int AB_ID_8;
                int user_ID_8;
                int new_rating;
                printf("enter the user ID  :  ");
                scanf("%d" , &user_ID_8);
                printf("enter the audiobook ID  :  ");
                scanf("%d" , &AB_ID_8);
                printf("enter the new rating  :  ");
                scanf("%d" , &new_rating);
                rate_AB(user_ID_8 , AB_ID_8 , new_rating , UL);
                break;
            }
            case 9:
            {
                most_pop_AB(AB);
                break;
            }
            case 10:
            {
                int user_ID_10;
                printf("enter the user ID  : ");
                scanf("%d" , &user_ID_10);
                listening_history_user(user_ID_10 , UL);
                break;
            }
            case 11:
            {
                int user_ID_1 , user_ID_2;
                printf("enter user ID 1   :  ");
                scanf("%d" , &user_ID_1);
                printf("enter user ID 2   :  ");
                scanf("%d" , &user_ID_2);
                merge_user_libraries(user_ID_1 , user_ID_2 , UL);
                break;
            }
            case 12:
            {
                int book_ID_12;
                printf("enter the audiobook ID  :  ");
                scanf("%d" , &book_ID_12);
                listening_history_AB(book_ID_12 , UL);
                break;
            }
            case 13:
            {
                 AB=sort_audiobooklist_based_on_rating(AB);
                 display_audiobooks(AB);

                 AB=sort_audiobooklist_based_on_id(AB);
                //  display_audiobooks(AB);
                break;
            }
            
        }
       printf("\n\n");
       printf("Enter y if you wish to continue the operation  \n");
       printf("Enter n  to  terminate the operation  \n");
       printf("Enter     :   ");
       char ch;
       fflush(stdin);
       scanf("%c",&ch);
       if(ch=='n')
       {
           t_flag=1;
       }
  }
     system("cls");
     new_file(AB , UL);
     display_audiobooks(AB);
     display_users(UL);
     printf("Thank you\n");
    return 0;
}