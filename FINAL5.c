#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

struct parameters{       //structure for three main parameters in the game
    int people,          //people parameter
        court,           //court parameter
        treasury;        //treasury parameter
    float average;       //average of three main parameter that is must be upper than 10 to not lose
};

int print_name(char name[]){                     //function for saving emperor's name
    int select1,
        select2;                                  //for continue a game or start a new game
    printf("\t\t\t***Nation Falling Game***\n\n");
    printf("[1] Stat Game\n[2] Add a new problem\n[3] Statics\n[4] Introduction\n[5] Exit\n\n");
    scanf("%d",&select1);

    if(select1==1){
    system("cls");
    printf("\t\t\t***Nation Falling Game***\n\n");
    printf("Enter your name:\n\n");              //saving emperor name
    fflush(stdin);
    gets(name);                                  //for take emperor name from user
    printf("\n");
    printf("Welcome %s,Select one of these options:\n\n",name);
    printf("[1] Start a new game\n\n[2] Resume the game\n\n");
    scanf("%d",&select2);                         //user select start a new game or continue the game
    printf("\n");
    return select2;
    }

    else if(select1==2){
    system("cls");
    printf("\t\t\t***Nation Falling Game***\n\n");

    struct parameters e[2];

    char problem[300],
         decide1[300],
         decide2[300];
    printf("Enter text of problem :\n");
    fflush(stdin);
    gets(problem);
    printf("\n");
    printf("Enter text of first decide :\n");
    fflush(stdin);
    gets(decide1);
    printf("\n");
    printf("Enter effect of first decide on people :\n");
    scanf("%d",&e[0].people);
    printf("Enter effect of first decide on court :\n");
    scanf("%d",&e[0].court);
    printf("Enter effect of first decide on treasury :\n");
    scanf("%d",&e[0].treasury);
    printf("\n");
    printf("Enter text of second decide :\n");
    fflush(stdin);
    gets(decide2);
    printf("\n");
    printf("Enter effect of second decide on people :\n");
    scanf("%d",&e[1].people);
    printf("Enter effect of second decide on court :\n");
    scanf("%d",&e[1].court);
    printf("Enter effect of second decide on treasury :\n");
    scanf("%d",&e[1].treasury);

    FILE *q;
    q=fopen("D:\\mohammad\\CHOICES.txt","r");
    if(q==NULL){
        printf("Can't Open File!!");
        return(0);
    }
    char s[500];
    int counter=0;
    while((fgets(s,500,q))!=NULL){
        ++counter;
    }
    fclose(q);
    q=fopen("D:\\mohammad\\CHOICES.txt","a");
    if(q==NULL){
        printf("Can't Open File!!");
        return(0);
    }
    fprintf(q,"\n%s","c");
    fprintf(q,"%d",counter+1);
    fprintf(q,"%s",".txt");
    fclose(q);

    char add[200];
    char temp[5];
    strcpy(add,"D:\\\\mohammad\\\\c");
    sprintf(temp,"%d",counter+1);
    strcat(add,temp);
    strcat(add,".txt");
    q=fopen(add,"a");
    if(q==NULL){
        printf("Can't Open File!!");
        return(0);
    }
    fprintf(q,"%s\n",problem);
    fprintf(q,"%s\n",decide1);
    fprintf(q,"%d\n%d\n%d\n",e[0].people,e[0].court,e[0].treasury);
    fprintf(q,"%s\n",decide2);
    fprintf(q,"%d\n%d\n%d\n",e[1].people,e[1].court,e[1].treasury);
    fclose(q);
    return(0);
    }

    else if(select1==3){

    }

    else if(select1==4){
    system("cls");
    printf("\t\t\t***Nation Falling Game***\n\n");

    FILE *p;
    p=fopen("D:\\mohammad\\Introduction.txt","r");
    if(p==NULL){
        printf("Can't Open File!!");
        return(0);
    }
    char s[3000];
    while(fgets(s,3000,p)!=NULL)
    puts(s);
    fclose(p);
    getch();
    return(0);
    }

    else if(select1==5){
        return(0);
    }
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
    head=(struct problems_text *)malloc(sizeof(struct problems_text));    //allocating storage
    temp=(struct problems_text *)malloc(sizeof(struct problems_text));    //allocating storage
    temp=head;                                                            //assigning two pointer to structure

    FILE *p,                                                              //define two file
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

    p=fopen("D:\\mohammad\\CHOICES.txt","r");  //opening file process
    if(p==NULL){
        printf("Cant Open File!");
        return(0);
    }
    while((fgets(s,200,p))!=NULL){            //counting line of CHOICE text file
        ++line_c;
    }
    fclose(p);
    return line_c;
}

struct problems_text *delete_front(struct problems_text *head){  //function for deleting first node
    struct problems_text *temp;
    temp=(struct problems_text *)malloc(sizeof(struct problems_text)); //allocating storage
    temp=head;                                                         //assigning two pointer
    head=head->next;

    return head;
};

struct problems_text *delete_next(struct problems_text *head,struct problems_text *curr_node) //function for deleting selected node
{
    struct problems_text *c,*temp;
    temp=(struct problems_text *)malloc(sizeof(struct problems_text)); //allocating memory
    c=(struct problems_text *)malloc(sizeof(struct problems_text));    //allocating memory
    temp=head;
    while(temp->next!=curr_node){
        temp=temp->next;
    }
    c=temp->next->next;
    temp->next=c;
    return head;
};

void *delete_end(struct problems_text *head){  //function for deleting last node
    struct problems_text *temp;
    temp=(struct problems_text *)malloc(sizeof(struct problems_text)); //allocating memory
    temp=head;
    while(temp->next->next!=NULL){
        temp=temp->next;
    }

    temp->next=NULL;
};

int save_game(char e_name[200],char mood[20],struct parameters s,int n_nodes,int *arr_node){ //a function for saving game

    struct parameters{   //define a structure for tree main parameters
        int people,
            court,
            treasury;
        float average;
    }t;

    struct save{               //define a structure to save it in a file
        char e_name[200],      //saving emperor name
             mood[20];         //saving mood of quit from game
        struct parameters p;   //saving tree main parameters
    }save_g;

    FILE *q;

    char add[200];             //define a string according to saving address of the folder that we should save in it

    int *arr_nodes;            //define a array for saving occurrence of every node

    strcpy(add,"D:\\\\mohammad\\\\save\\\\"); //building address of save folder
    strcat(add,e_name);
    strcat(add,".bin");

    q=fopen(add,"wb");        //opening file process
    if(q==NULL){
        printf("Can't Create The File!");
        return(0);
    }

    arr_nodes=(int *)calloc(n_nodes,sizeof(int));  //allocating memory

    strcpy(save_g.e_name,e_name);
    strcpy(save_g.mood,mood);
    for(int i=0; i<=n_nodes-1; ++i)
        arr_nodes[i]=arr_node[i];
    save_g.p.people=s.people;
    save_g.p.court=s.court;
    save_g.p.treasury=s.treasury;
    save_g.p.average=s.average;

    fwrite(&save_g,sizeof(save_g),1,q);            //write data in file
    fwrite(arr_nodes,sizeof(int),n_nodes,q);
    fclose(q);                                     //closing file according to don't lose any data
}

int new_game(struct problems_text *p,char e_name[200],int n_node){  //function when emperor want start a new game
    int decide,           //define a variable for when emperor select between two decide to problem
        ran_node,         //define a variable for witch node should be selected
        n_nodes;          //define a variable to don't lose number of nodes
    n_nodes=n_node;

    int save;            //define a variable for when ask emperor to save game or not

    int *arr_node;       //define an array according to save occurrence of every node
    arr_node=(int *)calloc(n_nodes,sizeof(int));  //allocating memory
    for(int j=0; j<=n_nodes-1; ++j)
        arr_node[j]=3;

    char mood[20];                   //define a string to save mood of quit from game

    struct problems_text *q=p;       //assigning two pointer to structure

    time_t t=time(NULL);             //according to select a node randomly
        srand(t);

    struct parameters i;            //initialize tree main parameter to 50
    i.people=50;
    i.court=50;
    i.treasury=50;
    i.average=(i.people+i.court+i.treasury)/3;

    while((i.people!=0 && i.court!=0 && i.treasury!=0) && (i.average>=10)){   //when one of tree main parameter be less than 10

        q=p;

        printf("People: %d Court: %d Treasury: %d\n\n",i.people,i.court,i.treasury); //printing value of tree main parameter

        ran_node=rand()%n_node;                                                      //select one problem randomly
        for(int i=0; i<ran_node; ++i){
            q=q->next;
        }

        int j=0,           //initialize an array according to have occurrence of nodes
            check=0,
            check1=0;
        for(int i=0; i<=n_nodes-1; ++i){
                if(check1!=0)
                break;
            if(arr_node[i]>=1){
                ++check;
            }
            if(check==ran_node+1){
                arr_node[i]-=1;
                ++check1;
            }
        }

        q->occ-=1;                    //when a node selected we should reduce the times that each node can occur

        printf("%s\n\n",q->problem);  //printing text of problem
        printf("[1] %s\n\n[2] %s\n\n",q->f_decide,q->s_decide);
        scanf("%d",&decide);          //emperor select between two problem
        printf("\n");

        if(decide==-1){
            printf("Do you want to save your current game?\n[1] Yes,save   [2] No,Don't save\n\n");
            scanf("%d",&save);        //user select between save game or not
            printf("\n");
            if(save==1){
                printf("Ok!Goodbye.");
                strcpy(mood,"Not Defeat");
                mood[10]='\0';
                save_game(e_name,mood,i,n_nodes,arr_node);  //saving game
                getch();
                return(0);
            }
            else if(save==2){
                printf("Ok!Goodbye.");
                getch();
                return(0);
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

        if(q->occ==0){                 //according to delete a node from all of problems

            if(n_node!=1){             //if number of nodes that is remain be more than one node
            if(ran_node==0){
                p=delete_front(p);     //deleting first node
            }
            else if(ran_node==n_node-1){
                delete_end(p);         //deleting last node
            }
            else{
                p=delete_next(p,q);    //deleting a special node that is not first one not last one
            }
            --n_node;                  //reducing number of nodes
            }
            else if(n_node==1){        //if one node is remain
                /*free(q);
                free(p);*/

                p=create_node();       //create all nodes(problems) again
                n_node=n_nodes;

                for(int j=0; j<=n_nodes-1; ++j)
                arr_node[j]=3;
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
        mood[6]='\0';
                save_game(e_name,mood,i,n_nodes,arr_node);
                getch();
                return(0);
               }
    else if(save==2){
        printf("Ok!Goodbye.");
        getch();
        return(0);
    }
}

int continue_game(struct problems_text *p,char e_name[200],int n_node){  //function when user want to resume the game

    struct load{                //define a structure for saving data
        char e_name[200],       //emperor name
             mood[20];          //mood of quit from game
        struct parameters l;    //define a structure for tree main parameter
    }load_g;

    int *arr_occ;               //define an array for having number of occurrence of nodes
    arr_occ=(int *)malloc(n_node*sizeof(int)); //allocating memory

    FILE *q;

    int select;                 //define a variable for when user decide between start a new game or not

    char add[200],              //define a string for address of the folder that we should read data from it
         mood[20];

    strcpy(add,"D:\\\\mohammad\\\\save\\\\"); //building address of save folder
    strcat(add,e_name);
    strcat(add,".bin");

    q=fopen(add,"rb");                        //opening file process
    if(q==NULL){
        printf("You don't have any save game!!\n\n");
        printf("Do you want to start a new game?\n\n[1] Yes   [2] No\n\n");
        scanf("%d",&select);
        printf("\n");
        if(select==1){
            system("cls");
            new_game(p,e_name,n_node);        //calling new_game function
        }
        else if(select==2){
            printf("Ok!Goodbye.");
            getch();
            return(0);
        }
    }

    fread(&load_g,sizeof(load_g),1,q);
    fread(arr_occ,sizeof(int),n_node,q);

    fclose(q);

    if((strcmp(load_g.mood,"Defeat"))==0){    //if user save game in defeat mood game will stat new
        printf("People: %d Court: %d Treasury: %d\n\n",load_g.l.people,load_g.l.court,load_g.l.treasury);
        printf("You have lost!!!\n\n");
        Sleep(5000);
        system("cls");
        new_game(p,e_name,n_node);
    }

    else if((strcmp(load_g.mood,"Not Defeat"))==0){

        system("cls");

        int decide,           //define a variable for when emperor select between two decide to problem
            ran_node,         //define a variable for witch node should be selected
            n_nodes,          //define a variable to don't lose number of nodes
            counter=0;        //define a counter for when we assign array elements to occurrence of nodes
        n_nodes=n_node;

        n_node=0;
        for(int i=0; i<=n_nodes-1; ++i){  //for counting how many nodes are remain
            if(*(arr_occ+i)>=1)
                ++n_node;
        }

        int save;               //define a variable for when ask emperor to save game or not

        char mood[20];          //define a string to save mood of quit from game

        struct problems_text *temp,*q=p;

        p->occ=*(arr_occ);      //delete nodes that number of occurrence is zero
        q=q->next;
        for(int i=1; i<=n_nodes-1; ++i){
            if((i==n_nodes-1) && (*(arr_occ+i)==0)){
                delete_end(p);
            }
            else if((i!=n_nodes-1) && (*(arr_occ+i)==0)){
                p=delete_next(p,q);
                ++counter;
            }

                q=p->next;
                for(int j=0; j<i-counter; ++j){
                    q=q->next;
                }
        }
        if(p->occ==0){
            p=delete_front(p);
        }

        counter=0;             //initialize counter variable to zero that is for assigning occurrence of nodes
        temp=p;
        while(counter!=n_nodes){
            if(*(arr_occ+counter)==0){
                ++counter;
            }
            else{
                p->occ=*(arr_occ+counter);
                p=p->next;
                ++counter;
            }
        }
        p=temp;

        time_t t=time(NULL);              //according to select a node randomly
        srand(t);

    while((load_g.l.people!=0 && load_g.l.court!=0 && load_g.l.treasury!=0) && (load_g.l.average>=10)){   //when one of tree main parameter be less than 10

        q=p;

        printf("People: %d Court: %d Treasury: %d\n\n",load_g.l.people,load_g.l.court,load_g.l.treasury); //printing value of tree main parameter

        ran_node=rand()%n_node;           //select one problem randomly
        for(int i=0; i<ran_node; ++i){
            q=q->next;
        }

        int j=0,                          //initialize an array according to have occurrence of nodes
            check=0,
            check1=0;

        for(int i=0; i<=n_nodes-1; ++i){  //initializing an array to have occurrence of nodes
                if(check1!=0)
                break;
            if(arr_occ[i]>=1){
                ++check;
            }
            if(check==ran_node+1){
                arr_occ[i]-=1;
                ++check1;
            }
        }

        q->occ-=1;                    //when a node selected we should reduce the times that each node can occur

        printf("%s\n\n",q->problem);  //printing text of problem
        printf("[1] %s\n\n[2] %s\n\n",q->f_decide,q->s_decide);
        scanf("%d",&decide);          //emperor select between two problem
        printf("\n");

        if(decide==-1){
            printf("Do you want to save your current game?\n[1] Yes,save   [2] No,Don't save\n\n");
            scanf("%d",&save);        //user select between save game or not
            printf("\n");
            if(save==1){
                printf("Ok!Goodbye.");
                strcpy(mood,"Not Defeat");
                mood[10]='\0';
                save_game(e_name,mood,load_g.l,n_nodes,arr_occ);  //saving game
                getch();
                return(0);
            }
            else if(save==2){
                printf("Ok!Goodbye.");
                getch();
                return(0);
            }
        }

        else if(decide==1){
            load_g.l.people+=q->f_people;
            load_g.l.court+=q->f_court;
            load_g.l.treasury+=q->f_treasury;
        }
        else if(decide==2){
            load_g.l.people+=q->s_people;
            load_g.l.court+=q->s_court;
            load_g.l.treasury+=q->s_treasury;
        }
        if(load_g.l.people<0){
            load_g.l.people=0;
        }
        if(load_g.l.people>100){
            load_g.l.people=100;
        }
        if(load_g.l.court<0){
            load_g.l.court=0;
        }
        if(load_g.l.court>100){
            load_g.l.court=100;
        }
        if(load_g.l.treasury<0){
            load_g.l.treasury=0;
        }
        if(load_g.l.treasury>100){
            load_g.l.treasury=100;
        }
        load_g.l.average=(load_g.l.people+load_g.l.court+load_g.l.treasury)/3;

        if(q->occ==0){                 //according to delete a node from all of problems

            if(n_node!=1){             //if number of nodes that is remain be more than one node
            if(ran_node==0){
                p=delete_front(p);     //deleting first node
            }
            else if(ran_node==n_node-1){
                delete_end(p);         //deleting last node
            }
            else{
                p=delete_next(p,q);    //deleting a special node that is not first one not last one
            }
            --n_node;                  //reducing number of nodes
            }
            else if(n_node==1){        //if one node is remain
                /*free(q);
                free(p);*/

                p=create_node();       //create all nodes(problems) again
                n_node=n_nodes;

                for(int j=0; j<=n_nodes-1; ++j)
                arr_occ[j]=3;
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
        mood[6]='\0';
                save_game(e_name,mood,load_g.l,n_nodes,arr_occ);
                getch();
                return(0);
               }
    else if(save==2){
        printf("Ok!Goodbye.");
        getch();
        return(0);
    }
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
        system("cls");
        new_game(p,name,n_node);
    }
    else if(select==2){
        continue_game(p,name,n_node);
    }
}
