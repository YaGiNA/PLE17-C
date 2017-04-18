#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double data_type;
typedef struct node_tag{
    data_type data;
    struct node_tag *next;
}node_type;

void initialize(node_type **pp){
    *pp = NULL;
}

node_type *new_node(data_type x, node_type *p){
    node_type *temp;
    temp = (node_type *)malloc(sizeof(node_type));
    if (temp == NULL) return NULL; /* メモリ割当て失敗 */
    else { /* ノードの各メンバーの値の設定 */
        temp->data = x;
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


int insert_rear(node_type **pp, data_type x){
    node_type *temp;
    temp = new_node(x, NULL);
    if(temp == NULL){
        return 0;
    }
    while(*pp != NULL){
        pp = &((*pp)->next);
    }
    *pp = temp;
    return 1;
}

double sum_of_nodes(node_type *p){
    double sum;
    while(p != NULL){
        printf("%g\n", p->data);
        sum = sum + p->data;
        p = p->next;
    }
    return sum;
}

/* ソートはマージソートを適用 */
static node_type *merge_list(node_type *list1, node_type *list2)
{
    node_type dummy = {0};
    node_type *p = NULL;
    p = &dummy;

    while((list1 != NULL) && (list2 != NULL)){
        if(fabs(list1->data) <= fabs(list2->data)){
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
}

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

int main(void){
    node_type *head;
    initialize(&head);
    double num, sum_raw_array = 0, sum_sorted_array = 0;
    while(1){
        scanf("%lf", &num);
        if(num == 0){break;}
        insert_rear(&head, num);
    }

    printf("----------------そのまま入力した場合の要素----------------\n");
    sum_raw_array = sum_of_nodes(head);
    printf("入力順: %g\n", sum_raw_array);

    head = merge_sort(head);
    printf("----------------絶対値昇順をした場合の要素----------------\n");
    sum_sorted_array = sum_of_nodes(head);
    printf("ソート順: %g\n", sum_sorted_array);

    list_free(head);
    return 0;
}
