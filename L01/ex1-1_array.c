#include <stdio.h>

int main(void){
  float nums[20];
  FILE *fp;
  char *fname = "numbers.txt";
 
  fp = fopen(fname, "r");
  if(fp == NULL) {
    printf("ファイルを開くことが出来ませんでした．¥n");
    return;
  }
  
  int n = 0, i = 0;
  float num;
  /*  ファイルが終わりでない　「かつ」　配列を飛び出さないうちは，読み込みを続ける  */
  while ( ! feof(fp) && n < 21) {
    fscanf(fp, "%f", &num);
    nums[n] = num;
    printf("%e\n", nums[n]);
    n++;
  }
  fclose(fp);
  return 0;
}
