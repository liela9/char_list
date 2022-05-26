#include <stdio.h>
#include <stdlib.h>
 
#define LINE_LENGTH 41

typedef struct node *ptr;
typedef struct node{
    char val[LINE_LENGTH];
    ptr next;
}node;

void addtolist(node *, char[]);
void printvalues(node *);
void freelist(node *);


int main(int argc, char *argv[]){
    FILE *fd;
    node *head, *h;
    int line, i;
    char ch[LINE_LENGTH];/*Every node will contain LINE_LENGTH characters*/

    h = (node *) malloc(sizeof(node));
    head = h;

    if(argc == 1){
        printf("\nMissing name of file\n");
        exit(0);
    }
    
    if(!(fd = fopen(argv[1], "r"))){ /*There is no such file*/
        printf("\nCannot open file\n");
        exit(0);
    }
    
    line = 0;
    while (!feof(fd)){/*Fill the nodes*/
        while (!feof(fd) && line < LINE_LENGTH){
            ch[line] = fgetc(fd);
            line++;
        }
        if(line == LINE_LENGTH){
            line = 0;
            addtolist(h, ch);
            h = h->next;
            for(i = 0; i < LINE_LENGTH; i++)
                ch[line] = 0;
        }
    }

    fclose(fd);/*Close the reading file*/
    printvalues(head);
    freelist(head);
    return(0);
}


void addtolist(node *h, char c[]){
    node *n;
    int i;

    n = (node *) malloc(sizeof(node));
    if (!n){ 
       printf("\nCannot build list \n");/*there isnt enough memory*/
       exit(0);
    }
    n->next = NULL;
    
    for(i = 0; i < LINE_LENGTH; i++)
        h->val[i] = c[i];

    h->next = n;
}

void printvalues(node *h){
    int j;
    
    while (h){
        printf("\n");
        for(j = 0; j < LINE_LENGTH; j++)
            printf("%c", h->val[j]);
        
        h = h->next;
    }
}


void freelist(node *h){
    node *n;
    
    while (h)
    {
        n = h;
        h = h->next;
        free(n);
    }
}
