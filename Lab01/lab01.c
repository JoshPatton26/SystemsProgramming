#include <stdio.h>

int main(int argc, char* argv[]){

  int givenNum, i = 0;
  int isPrime = 0;

  printf("Enter an integer: ");
  scanf("%d", &givenNum);

  int n = givenNum/2;

  //Base case for 0-1 set isPrime to false(1).
  if(givenNum < 2){
    isPrime = 1;
  }

  //Loop from 2 to the given value and determin whether 
  //is is perfectly divisable by i. If so, set isPrime to false(1).
  for(i=2; i <= n; i++){
    if((givenNum % i) == 0){
      isPrime = 1;
      break;
    }
  }

  //Print results based off whether isPrime is true(0) or false(1).
  if(isPrime == 0){
    printf("The number is prime\n");
  }else{
    printf("The number is not prime\n");
  }

  return 0;
}
// https://www.programiz.com/c-programing/examples/prime-number was used only for help
// with the syntax. All the logic is the same as the program I wrote in CS330.
