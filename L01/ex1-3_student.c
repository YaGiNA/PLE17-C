#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

int sum_print_score(node_type *p){
  int sum_sorted_array = 0;
  while(p != NULL){
      printf("%s: %d\n", p->name, p->score);
      sum_sorted_array += p->score;
      p = p->next;
  }
  return sum_sorted_array;
}


int *copy_sort_node(node_type **p2, node_type **p1){
    node_type *temp;
    if(temp == NULL){
        return 0;
    }
    while (*p1 != NULL) {
        while(*p2 != NULL && (*p2)->score < (*p1)->score){
            printf("%s: %d VS %s: %d\n", (*p2)->name, (*p2)->score, (*p1)->name, (*p1)->score);
            p2 = &((*p2)->next);
        }
        printf("-------------\n");
        temp = new_node((*p1)->name, (*p1)->score, *p2);
        *p2 = temp;
        *p1 = (*p1)->next;
    }

    return 0;
}


int sum_of_nodes(node_type *p){
    int sum = 0;
    while(p != NULL){
        sum = sum + p->score;
        p = p->next;
    }
    return sum;
}

int main(void){
    node_type *head1;
    initialize(&head1);
    FILE *f;
    char file_name[] = "student.txt";
    char name[16];
    int score, sum_sorted_array = 0, i;
    /* ファイルオープン */
    if ((f = fopen(file_name, "r")) == NULL) {
        fprintf(stderr, "%s\n", "error: can't read file.");
        return EXIT_FAILURE;
    }
    printf("----------------辞書順----------------\n");
    while(fscanf(f, "%s%d", name, &score) != EOF){
        insert_rear(&head1, name, score);
    }
    fclose(f);
    i = sum_print_score(head1);

    printf("----------------score昇順----------------\n");
    node_type *head2;
    initialize(&head2);
    copy_sort_node(&head2, &head1);
    sum_sorted_array = sum_print_score(head2);
    printf("ソート順: %d\n", sum_sorted_array);
    list_free(head2);
    list_free(head1);
    return 0;
}
