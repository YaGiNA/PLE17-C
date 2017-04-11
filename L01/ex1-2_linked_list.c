#include <stdio.h>
#include <stdlib.h>

typedef double data_type;
typedef struct node_tag{
  data_type data;
  struct node_tag *next;
} node_type;

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

void raw_array(void){
  double num, sum_raw_array = 0;
  node_type *head;
  initialize(&head);
  while(1){
    scanf("%lf", &num);
    if(num == 0){break;}
    insert_rear(&head, num);
  }
  sum_raw_array = sum_of_nodes(head);
  printf("入力順: %g\n", sum_raw_array);
}

/*
void sorted_array(void){
  int n = 0, i = 0, j;
  double nums[20];
  double tmp, sum_sorted_array = 0;
  for(i=0; i<20; i++) {
    scanf("%lf", &nums[i]);
  }

  for (i=0; i<20;i++) {
    for (j=i+1; j<20; j++) {
      if (nums[i] > nums[j]) {
        tmp =  nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
      }
    }
  }

  for(i=0; i<20; i++){
    sum_sorted_array += nums[i];
  }
  printf("ソート順: %20.18e\n", sum_sorted_array);
}
*/

int main(void){
  raw_array();
  // sorted_array();
}
