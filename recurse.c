#include <stdio.h>

int factorial(int n) {
   //base case
   if(n == 0) {
      return 1;
   } else {
      return n * factorial(n-1);
   }
}

int fibbonacci(int n) {
   if(n == 0){
      return 0;
   } else if(n == 1) {
      return 1;
   } else {
      return (fibbonacci(n-1) + fibbonacci(n-2));
   }
}

int main() {
	int n = 4;
	int i, fib, fsum = 0;

	printf("Factorial of %d: %d\n" , n , factorial(n));
	printf("Fibbonacci of %d: " , n);
	
	for(i = 0; i<n; i++) {
		fib = fibbonacci(i);
		printf("%d ", fib); 
		fsum += fib;
	}
   printf("\nFibbonacci sum of %d: " , fsum);
}