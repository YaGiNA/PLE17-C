#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_tag{
    char name[16];
    int score;
    struct node_tag *next;
}node_type;

void initialize(node_type **pp){
    *pp = NULL;
}

node_type *new_node(char name[16], int score, node_type *p){
    node_type *temp;
    temp = (node_type *)malloc(sizeof(node_type));
    if (temp == NULL) return NULL; /* メモリ割当て失敗 */
    else { /* ノードの各メンバーの値の設定 */
        temp->score = score;
        strcpy(temp->name, name);
        temp->next = p;
        return temp;
    }
}

void list_free(node_type *header)
{
    node_type *temp = header;
    node_type *swap = NULL;

    while(temp != NULL){
        swap = temp->next;
        free(temp);
        temp = swap;
    }
}


int insert_rear(node_type **pp, char name[16], int score){
    int i;
    node_type *temp;
    if(temp == NULL){
        return 0;
    }
    while(*pp != NULL && strcmp(name, (*pp)->name) > 0){
        pp = &((*pp)->next);
    }
    temp = new_node(name, score, *pp);
    *pp = temp;
    return 1;
}

void print_nodes(node_type *p){
    while(p != NULL){
        printf("%s: %d\n", p->name, p->score);
        p = p->next;
    }
}

/* ソートはマージソートを適用
static node_type *merge_list(node_type *list1, node_type *list2)
{
    node_type dummy = {0};
    node_type *p = NULL;
    p = &dummy;

    while((list1 != NULL) && (list2 != NULL)){
        if(list1->student->score <= list2->student->score){
            p->next = list1;
            p = list1;
            list1 = list1->next;
        }else{
            p->next = list2;
            p = list2;
            list2 = list2->next;
        }
    }

    if(list1 == NULL){
        p->next = list2;
    }else{
        p->next = list1;
    }
    return dummy.next;
}*/
/*
node_type *merge_sort(node_type *header)
{
    node_type *partition = NULL;
    node_type *forward   = header;
    node_type *backward  = header->next;
    if((header == NULL) || (header->next == NULL)) return(header);


    if(backward != NULL) backward = backward->next;
    while((backward != NULL) && (backward->next != NULL)){
        forward = forward->next;
        backward = backward->next->next;
    }


    partition = forward->next;
    forward->next = NULL;


    return merge_list(merge_sort(header), merge_sort(partition));
}
*/
int main(void){
    node_type *head;
    initialize(&head);
    char end[] = "END";
    FILE *f;
    char file_name[] = "student.txt";
    int score;
    char name[16];
    /* ファイルオープン */
    if ((f = fopen(file_name, "r")) == NULL) {
        fprintf(stderr, "%s\n", "error: can't read file.");
        return EXIT_FAILURE;
    }
    while(fscanf(f, "%s%d", name, &score) != EOF){
        if(strcmp(name, end) == 0){break;}
        insert_rear(&head, name, score);
    }
    fclose(f);

    printf("----------------name入力順----------------\n");
    print_nodes(head);
/*
    head = merge_sort(head);
    printf("----------------昇順ソートをした場合の要素----------------\n");
    sum_sorted_array = sum_of_nodes(head);
    printf("ソート順: %g\n", sum_sorted_array);
*/
    list_free(head);
    return 0;
}
