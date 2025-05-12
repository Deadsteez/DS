#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Queue{
    char* data[100];
    int F,R;
};

struct Queue *q;

int isEmptyQ(){
    return q->F ==-1;
}

int isFullQ(){
    return q->R==100;
}

void EnQ(char * s){

    if(isFullQ()){
        printf("Queue is full");
        return;
    }

    if(isEmptyQ()){
        q->F=q->R=0;
    }
    else{
        q->R++;
    }
        
    q->data[q->R] = (char*)malloc(strlen(s) + 1);
    strcpy(q->data[q->R], s);
}

char* DeQ(){
    if(isEmptyQ()){
        printf("Queue is empty");
        return NULL;
    }

    char* s=q->data[q->F];

    if(q->F==q->R){
        q->F=q->R=-1;
    }

    else{
        q->F++;
    }

    return s;
}

int main(){
    q = (struct Queue*)malloc(sizeof(struct Queue));

    q->F=-1;
    q->R=-1;

    int choice;
    char * front;
    char * removed;
    char name[20];
    printf("1. Add New passenger\n");
    printf("2. Remove front passenger\n");
    printf("3. Display first passenger\n");
    printf("4. Exit");
    
    do{
        printf("Enter choice:\n");
        scanf("%d",&choice);
        switch (choice){
        
        case 1:
            
            printf("Enter passenger name:\n");
            scanf("%s",name);
            EnQ(name);
            break;

        case 2:  
            removed=DeQ();
            printf("%s has left the queue\n",removed);
            break;

        case 3:
            front=q->data[q->F];
            printf("Passenger %s is at the front\n",front);
            break;
        
        case 4:
            printf("Total passengers still in Queue : %d ",(q->R-q->F+1));
            break;
        
            default:
            printf("Enter correct choice number");
        }
    }while(choice!=4);
}

