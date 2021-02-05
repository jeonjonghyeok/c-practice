#include <stdio.h>
/*#include "add.h"
#include "div.h"
#include "mul.h"
#include "sub.h"
*/
void Add(int a, int b);

int main(){
  int a,b;
  char op;

  printf("숫자/숫자/부호 각각 입력");
  scanf("%d %d %s",&a,&b,&op);

  printf("%c",op);

  switch(op){
    case '+' : 
      Add(a,b);
      break;
    default:
      printf("잘못 입력");
      return 0;
      
  }



  return 0;

}

void Add(int a, int b){
  printf("%d + %d = %d",a,b,a+b);
}
