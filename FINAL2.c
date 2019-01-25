#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>

struct parameters{       //structure for three main parameters in the game
    int people,          //people parameter
        court,           //court parameter
        treasury;        //treasury parameter
    float average;       //average of three main parameter that is must be upper than 10 to not lose
};

int print_name(char name[]){          //function for saving emperor's name
    int select;                       //for continue a game or start a new game
    printf("Enter your name:\n\n");   //saving emperor name
    gets(name);
    printf("\n");
    printf("Welcome %s,Select one of these options:\n\n",name);
    printf("[1] Start a new game\n\n[2] Resume the game\n\n");
    scanf("%d",&select);              //user select start a new game or continue the game
    printf("\n");
    return select;
}

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

    int line_c,line_p=0;        //define a variable for counting lie of CHOICES file and another one for counting problems file

    p=fopen("D:\\mohammad\\CHOICES.txt","r"); //opening choices file
    if(p==NULL){                              //checking this file is existed or not
        printf("Can't Open File!");
        return(0);
    }

    while((fgets(s1,200,p))!=NULL){  //calculate number of line in choices file
        ++line_c;
    }
    fclose(p);                       //closing file according to do not lost any data

    p=fopen("D:\\mohammad\\CHOICES.txt","r"); //open file again
    if(p==NULL){                              //checking this file is existed or not
        printf("Can't Open File!");
        return(0);
    }

    while((fgets(s1,200,p))!=NULL){  //transfer files information to linked lists
    strcpy(s2,"D:\\\\mohammad\\\\"); //creating address of problems file
    strcat(s2,s1);                   //creating address of problems file

    if(s2[strlen(s2)-1]=='\n'){
    s2[strlen(s2)-1]='\0';}

    q=fopen(s2,"r");                 //open second file that is for problems
    if(q==NULL){                     //checking this file is existed or not
        printf("Can't Open File!");
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

    if(line_p==line_c-1){              //for point the last node to NULL
        temp->next=NULL;
    }
    else{
        temp->next=(struct problems_text *)malloc(sizeof(struct problems_text));  //allocate storage for next node
        temp=temp->next;
    }
    ++line_p;
    }
    return head;
};

int count_node(void){       //function for counting number of nodes
    FILE *p;
    int line_c=0;
    char s[200];

    p=fopen("D:\\mohammad\\CHOICES.txt","r");
    if(p==NULL){
        printf("Cant Open File!");
        return(0);
    }
    while((fgets(s,200,p))!=NULL){
        ++line_c;
    }
    fclose(p);
    return line_c;
}

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

void save_game(char e_name[200],char mood[20],struct parameters s,struct problems_text *p,int n_node){ //a function for saving game

    FILE *q;

    struct problems_text *temp=p;

    int *arr_occ;                              //an array for saving how many times node can occur
    arr_occ=(int *)calloc(n_node,sizeof(int));
    for(int i=0; i<n_node; ++i){
        *(arr_occ+i)=temp->occ;
        temp=temp->next;
    }

    char add[200];

    strcpy(add,"D:\\\\mohammad\\\\save\\\\"); //building address of save folder
    strcat(add,e_name);
    strcat(add,".bin");

    q=fopen(add,"wb");
    if(q==NULL){
        printf("Can't Create The File!");
        exit(0);
    }

    fwrite(e_name,sizeof(char),strlen(e_name)+1,q);  //write data in file
    fwrite(mood,sizeof(char),strlen(mood)+1,q);
    fwrite(arr_occ,sizeof(arr_occ),1,q);
    fwrite(&s,sizeof(s),1,q);

    fclose(q);
}

void new_game(struct problems_text *p,char e_name[200],int n_node){  //function when emperor want start a new game
    int decide,           //define a variable for when emperor select between two decide to problem
        ran_node,         //define a variable for witch node should be selected
        n_nodes;          //define a variable to don't lose number of nodes
    n_nodes=n_node;

    int save;            //define a variable for when ask emperor to save game or not

    char mood[20];

    struct problems_text *q=p;
    time_t t=time(NULL);  //according to select a node randomly
        srand(t);

    struct parameters i;
    i.people=50;
    i.court=50;
    i.treasury=50;
    i.average=(i.people+i.court+i.treasury)/3;

    while((i.people!=0 && i.court!=0 && i.treasury!=0) && (i.average>=10)){

        q=p;

        printf("People: %d Court: %d Treasury: %d\n\n",i.people,i.court,i.treasury);

        ran_node=rand()%n_node;
        for(int i=0; i<ran_node; ++i){
            q=q->next;
        }
        q->occ-=1;        //when a node selected we should reduce the times that each node can occur

        printf("%s\n\n",q->problem);
        printf("[1] %s\n\n[2] %s\n\n",q->f_decide,q->s_decide);
        scanf("%d",&decide);
        printf("\n");

        if(decide==-1){
            printf("Do you want to save your current game?\n[1] Yes,save   [2] No,Don't save\n\n");
            scanf("%d",&save);
            printf("\n");
            if(save==1){
                printf("Ok!Goodbye.");
                strcpy(mood,"Not Defeat");
                   if(q->occ==0){

                     if(n_node!=1){
                     if(ran_node==0){
                        p=delete_front(p);
                    }
                     else if(ran_node==n_node-1){
                        p=delete_end(p);
                      }
                     else{
                        p=delete_next(p,q);
                      }
                     --n_node;
                    }
                     else if(n_node==1){
                            free(q);
                            free(p);
                            p=(struct problems_text *)malloc(sizeof(struct problems_text));
                            q=(struct problems_text *)malloc(sizeof(struct problems_text));
                            p=create_node();
                            n_node=n_nodes;
                   }

                   }
                save_game(e_name,mood,i,p,n_node);
                getch();
                exit(0);
            }
            else if(save==2){
                printf("Ok!Goodbye.");
                getch();
                exit(0);
            }
        }

        else if(decide==1){
            i.people+=q->f_people;
            i.court+=q->f_court;
            i.treasury+=q->f_treasury;
        }
        else if(decide==2){
            i.people+=q->s_people;
            i.court+=q->s_court;
            i.treasury+=q->s_treasury;
        }
        if(i.people<0){
            i.people=0;
        }
        if(i.people>100){
            i.people=100;
        }
        if(i.court<0){
            i.court=0;
        }
        if(i.court>100){
            i.court=100;
        }
        if(i.treasury<0){
            i.treasury=0;
        }
        if(i.treasury>100){
            i.treasury=100;
        }
        i.average=(i.people+i.court+i.treasury)/3;

        if(q->occ==0){

            if(n_node!=1){
            if(ran_node==0){
                p=delete_front(p);
            }
            else if(ran_node==n_node-1){
                p=delete_end(p);
            }
            else{
                p=delete_next(p,q);
            }
            --n_node;
            }
            else if(n_node==1){
                free(q);
                free(p);
                p=(struct problems_text *)malloc(sizeof(struct problems_text));
                q=(struct problems_text *)malloc(sizeof(struct problems_text));
                p=create_node();
                n_node=n_nodes;
            }

        }

    }
    printf("You lost!!!\n\n");
    printf("Do you want to save your current game?\n[1] Yes,save   [2] No,Don't save\n\n");
    scanf("%d",&save);
    printf("\n");
    if(save==1){
        printf("Ok!Goodbye.");
        strcpy(mood,"Defeat");
          if(q->occ==0){

                     if(n_node!=1){
                     if(ran_node==0){
                        p=delete_front(p);
                    }
                     else if(ran_node==n_node-1){
                        p=delete_end(p);
                      }
                     else{
                        p=delete_next(p,q);
                      }
                     --n_node;
                    }
                     else if(n_node==1){
                            free(q);
                            free(p);
                            p=(struct problems_text *)malloc(sizeof(struct problems_text));
                            q=(struct problems_text *)malloc(sizeof(struct problems_text));
                            p=create_node();
                            n_node=n_nodes;
                   }

                   }
                save_game(e_name,mood,i,p,n_node);
                getch();
               }
    else if(save==2){
        printf("Ok!Goodbye.");
        getch();
    }
}

int main()
{
    struct problems_text *p;
    char name[200];
    int select,
        n_node;

    p=create_node();
    select=print_name(name);
    n_node=count_node();

    if(select==1){
        new_game(p,name,n_node);
    }
}
