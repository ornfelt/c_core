#include <stdio.h>
#include <math.h>

float Q_rsqrt( float number )
{
	printf("\nnumber = %.10f", number);
	long i; // Declare 32-bit number
	float x2, y; // 32-bit decimal numbers
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	//printf("\n0x5f3759df = %ld", 0x5f3759df); // equals: 1597463007
	
	//i  = 1597463007 - ( i >> 1 );               // what the fuck?
	//i  = ( i ^= 1010101011111 );               // what the fuck?
	
	printf("\ni = %ld", i);
	//i  = ( i | 1111111111 );
	//i  = ( i & 1101110101 );
	// This works since floats are stored in scientific notation, similar to 4.3217 × 10^3
	i  = ( i & 1597463007 );
	//i  = ( i >> 1 );
	printf("\ni = %ld", i);
	// Now we have the bits of our solution, so we reverse the steps from the evil bit hack. This gives a good approximation.
	y  = * ( float * ) &i;
	printf("\ny = %.10f", y);

	//y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	return y;
}


// from: https://betterexplained.com/articles/understanding-quakes-fast-inverse-square-root/
float InvSqrt(float x){
	float xhalf = 0.5f * x;
	int i = *(int*)&x;            // store floating-point bits in integer
	i = 0x5f3759df - (i >> 1);    // initial guess for Newton's method
	// printf("\ni: %d", i);
	x = *(float*)&i;              // convert new bits into float
	printf("\nx: %f", x);
	x = x*(1.5f - xhalf*x*x);     // One round of Newton's method
	return x;
}

int main() {
  printf("Comparison of inverse square root calculations:");
  //float myFloat = 123.5F;
  float myFloat = 100000.5F;
  float fast_sqrt = Q_rsqrt(myFloat);
  printf("\n%.6f", fast_sqrt);

  // other code (result is the same as fast):
  //float fast_sqrt_two = InvSqrt(myFloat);
  //printf("\nOther: %f", fast_sqrt_two);

  return 0;
}