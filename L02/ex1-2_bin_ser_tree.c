#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SUCCESS 0
#define FAILURE 0

typedef double data_type;
typedef struct node_tag {
    data_type data;
    struct node_tag *left;
    struct node_tag *right;
} node_type; /* ノードの型 */


void initialize(node_type **pp){
    *pp = NULL;
}


node_type *new_node(data_type x) {
    node_type *temp;
    temp = (node_type *)malloc(sizeof(node_type));
    if (temp == NULL) return NULL;
    else {
        temp->data = x;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
}


int insert(node_type **pp, data_type x) {
    node_type *temp;
    if (*pp == NULL) {
        temp = new_node(x);
        if (temp == NULL) return FAILURE;
        *pp = temp;
        return SUCCESS;
    }else {
        if (fabs(x) <= fabs((*pp)->data)) insert(&((*pp)->left), x);
        else if (fabs(x) > fabs((*pp)->data)) insert(&((*pp)->right), x);
    }
    return SUCCESS;
}


double tree_size(node_type *p) {
    double sump=0, left=0, right=0;
    if(p->left != NULL){
        left=tree_size(p->left);
    }
    printf("%g\n", p->data);
    if(p->right != NULL){
        right=tree_size(p->right);
    }
    sump = left + right + p->data;
    return sump;
}



int main(void){
    node_type *root;
    initialize(&root);
    double num, sum_sorted = 0;
    while(1){
        scanf("%lf", &num);
        if(num == 0){break;}
        insert(&root, num);
    }

    printf("----------------絶対値昇順をした場合の要素----------------\n");
    sum_sorted = tree_size(root);
    printf("\n");
    printf("ソート順: %g\n", sum_sorted);

    // list_free(root);
    return 0;

}
