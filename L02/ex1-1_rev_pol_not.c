#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define True 1
#define False 0
#define NUMBER '0'

typedef char data_type; /* データの型 */
typedef struct node_tag {
    data_type data; /* データ */
    struct node_tag *next; /* 後続ノードへのポインタ */
} node_type; /* ノードの型 */
node_type *stack;

void initialize(node_type **pp) /* スタックの初期化 */
{
    *pp = NULL; /* スタックは空（先頭ノードなし） */
}

node_type *new_node(data_type x, node_type *p)
{
    node_type *temp;
    temp = (node_type *)malloc(sizeof(node_type));
    /* メモリの割当て */
    if (temp == NULL) return NULL; /* メモリ割当て失敗 */
    else { /* ノードの各メンバーの値の設定 */
    temp->data = x;
    temp->next = p;
    return temp;
 }
}

int is_empty(node_type *p) /* 空スタックのとき真、 */
{ /* そうでないならば偽を返す */
    if (p == NULL) return True; /* 空スタックのとき */
    else return False; /* 空スタックでないとき */
}

data_type top(node_type *p)
{
    if (p == NULL) /* 空スタックのとき */
      return '\0'; /* ナル文字を返す */
    else /* 空スタックでないとき */
      return p->data; /* スタックの先頭のデータを返す */
}

int push(node_type **pp, data_type x)
{
    node_type *temp;
    temp = new_node(x, *pp); /* 関数new_nodeの呼出し */
    if (temp == NULL) return 1;
    *pp = temp;
    return 0;
}

data_type *pop(node_type **pp){
    node_type *temp;
    data_type *data;
    if (*pp != NULL) {
      printf("the stack is empty.");
	return "\0";
    }
    *data = (*pp)->data;
    temp = (*pp)->next;
    free(*pp); /* メモリの解放 */
    *pp = temp;
   return data;
}



// 以下、http://home.a00.itscom.net/hatada/c-tips/rpn/rpn02.htmlより引用
// 演算子の優先順位を返す
int rank(char *op) {
    if (*op == '*' || *op == '/' || *op == '%') return 4;
    if (*op == '+' || *op == '-') return 5;
    return 99;
}

char** convert(char *token[], int length) {
    node_type *stack;
    initialize(&stack);
    data_type *pToken;
    char** buffer = calloc(length+1, sizeof(char*));
    int n, nBuf = 0;
    data_type *tmp;
    for (n = 0; n < length; n++) {
        if (isdigit(*token[n])) {
            // 数値ならば、バッファに追加
	    buffer[nBuf++] = token[n];
	    printf("%c", token[n]);
        } else if (*token[n] == ')') {
            // '('までスタックからポップし、バッファへ. '(' と ')' は捨てる.
            while ((pToken = pop(&stack)) != '\0' && *pToken != '(')
	        buffer[nBuf++] = pToken;
            if (*pToken == '\n') error("'(' がない");
        } else if (*token[n] == '(') {
	    push(&stack, *token[n]);
        } else if (top(stack) == '\0') {
	    push(&stack, *token[n]);
	} else if (token[n] == "="){
  	    tmp = pop(&stack);
	    push(&stack, *token[n]);
        } else {
            while (top(stack) != '\0') {
	      data_type intop = top(stack);
  	        if (rank(token[n]) > rank(&intop)) {
                    // 現在のトークンはスタック最上位のトークンより優先順位が低い
                    buffer[nBuf++] = pop(&stack);
                } else {
     		    push(&stack, *token[n]);
                    break;
                }
            }
        }
    }
}

void printRPN(char *buffer[]) {
    int n;
    for (n = 0; buffer[n] != NULL; n++)
        printf("%s ", buffer[n]);
}

// 引用終了

int main(void){
    char *frml1[] = {"A", "=", "(", "5", "-", "4", ")", "/", "2", "+", "3", "*", "6"};
    data_type **buf1 = convert(frml1, sizeof(frml1)/sizeof(char*));
    printRPN(buf1);
}
