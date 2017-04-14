#include <stdio.h>
#include <math.h>

void raw_array(double *nums){
    printf("----------------そのまま入力した場合の要素----------------\n");
    double sum_raw_array;
    int i;
    for(i=0; i<21; ++i){
        sum_raw_array += nums[i];
    }
    printf("入力順: %g\n", sum_raw_array);
}

void sorted_array(double *nums){
    printf("----------------昇順ソートをした場合の要素----------------\n");
    int i, j;
    double sum_sorted_array, tmp;
    /* 数値を昇順にソート */
    for (i=0; i<21;i++) {
        for (j=i+1; j<21; j++) {
            if (fabs(nums[i]) > fabs(nums[j])) {
                tmp =    nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
        }
    }

    for(i=0; i<21; i++){
        sum_sorted_array += nums[i];
        printf("%g\n", nums[i]);
    }
    printf("ソート順: %g\n", sum_sorted_array);
}

int main(void){
    int i = 0, j;
    double nums[21];
    double tmp, sum_raw_array = 0;
    sum_raw_array = 0;
    for(i=0; i<21; i++) {
        scanf("%lf", &nums[i]);
        sum_raw_array += nums[i];
        printf("%g\n", nums[i]);
    }
    raw_array(nums);
    sorted_array(nums);
}
