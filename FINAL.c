#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct problems_text{     //structure for saving problems informations
    char problem[200],    //the text that explain problem
         f_decide[200],   //first decide
         s_decide[200];   //second decide
    int f_people,         //first decide effect on people consent
        f_court,          //first decide effect on court consent
        f_treasury,       //first decide effect on treasury consent
        s_people,         //second decide effect on people consent
        s_court,          //second decide effect on court consent
        s_treasury,       //second decide effect on treasury consent
        occ;              //how times the problem can occurrence
    struct problems_text *next;
};

struct problems_text *create_node(void){  //Function for Create linked list
    struct problems_text *head,
                         *temp;
    head=(struct problems_text *)malloc(sizeof(struct problems_text));  //allocating storage
    temp=head;

    FILE *p,
         *q;

    char s1[200],
         s2[200],
         s3[200],
         s4[200],
         s5[200];

    int i,j=0;

    p=fopen("D:\\mohammad\\CHOICES.txt","r"); //opening choices file
    if(p==NULL){                              //checking this file is existed or not
        printf("Cant Open File!");
        return(0);
    }

    while((fgets(s1,200,p))!=NULL){  //calculate number of line in choices file
        ++i;
    }
    fclose(p);                       //closing file according to do not lost any data

    p=fopen("D:\\mohammad\\CHOICES.txt","r"); //open file again
    if(p==NULL){                              //checking this file is existed or not
        printf("Cant Open File!");
        return(0);
    }

    while((fgets(s1,200,p))!=NULL){  //transfer files information to linked lists
    strcpy(s2,"D:\\\\mohammad\\\\"); //creating address of problems file
    strcat(s2,s1);                   //creating address of problems file

    if(s2[strlen(s2)-1]=='\n'){
    s2[strlen(s2)-1]='\0';}

    q=fopen(s2,"r");                 //open second file that is for problems
    if(q==NULL){                     //checking this file is existed or not
        printf("Cant Open File!");
        return(0);
    }
    fgets(s3,200,q);                 //saving problem
    strcpy(temp->problem,s3);

    fgets(s4,200,q);
    strcpy(temp->f_decide,s4);      //saving first decide

    fscanf(q,"%d",&temp->f_people);    //saving the effect of first decide on people
    fscanf(q,"%d",&temp->f_court);     //saving the effect of first decide on court
    fscanf(q,"%d",&temp->f_treasury);  //saving the effect of first decide on treasury

    fseek(q,2,SEEK_CUR);               //according to windows

    fgets(s5,200,q);                   //saving second decide
    strcpy(temp->s_decide,s5);

    fscanf(q,"%d",&temp->s_people);    //saving the effect of second decide on people
    fscanf(q,"%d",&temp->s_court);     //saving the effect of second decide on court
    fscanf(q,"%d",&temp->s_treasury);  //saving the effect of second decide on treasury

    temp->occ=3;                       //initializing how time a problem can occur

    fclose(q);                         //close the file that is for problems text

    if(j==i-1){                        //for point the last node to NULL
        temp->next=NULL;
    }
    else{
        temp->next=(struct problems_text *)malloc(sizeof(struct problems_text));  //allocate storage for next node
        temp=temp->next;
    }
    ++j;
    }
    return head;
};

struct problems_text *delete_front(struct problems_text *head){  //function for deleting first node
    struct problems_text *temp;
    temp=(struct problems_text *)malloc(sizeof(struct problems_text)); //allocating storage
    temp=head;
    temp=temp->next;
    free(head);
    return temp;
};

struct problems_text *delete_next(struct problems_text *head,struct problems_text *curr_node) //function for deleting selected node
{
    struct problems_text *c,*temp=head;
    while(temp->next!=curr_node){
        temp=temp->next;
    }
    c=temp->next->next;
    temp->next=c;
    return head;
};

struct problems_text *delete_end(struct problems_text *head){  //function for deleting last node
    struct problems_text *temp=head;
    while(temp->next->next!=NULL){
        temp=temp->next;
    }
    free(temp->next);
    temp->next=NULL;
    return head;
};


int main()
{
    struct problems_text *p;
    p=create_node();
    p=delete_end(p);
    p=p->next->next->next->next;
    printf("%s%s%d\n%d\n%d\n%s%d\n%d\n%d\n%d",p->problem,p->f_decide,p->f_people,p->f_court,p->f_treasury,p->s_decide,p->s_people,p->s_court,p->s_treasury,p->occ);
}
