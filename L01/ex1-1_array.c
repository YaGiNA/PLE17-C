#include <stdio.h>

void raw_array(void){
  int i = 0, j;
  double nums[20];
  double tmp, sum_raw_array = 0;
  sum_raw_array = 0;
  for(i=0; i<20; i++) {
    scanf("%lf", &nums[i]);
    sum_raw_array += nums[i];
  }

  printf("入力順: %e\n", sum_raw_array);
}

void sorted_array(void){
  int n = 0, i = 0, j;
  double nums[20];
  double tmp, sum_sorted_array = 0;
  for(i=0; i<20; i++) {
    scanf("%lf", &nums[i]);
  }

  /* 数値を昇順にソート */
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

int main(void){
  raw_array();
  sorted_array();
}
