#include <stdio.h>
#include <math.h>

// Also see: https://sv.wikipedia.org/wiki/Inversa_kvadratlagen

// Explanation from reddit:
// 0x53759df is equal to 87513567 in decimal, but that's not overly exciting.
// Why it works in this case is far from obvious,
// and the derivation requires some knowledge of approximation methods and how floating
// point numbers are structured under the hood.

// Explaining how the function itself works is easier. The input, x, is the number that
// you want the inverse square root of. First we tell the computer to interpret x as
// an integer (even though it originally is given as a floating point type), and call that 'i'. 
// Then we take i and subtract half of it from the magic number. (x >> 1 is another way to
// get x/2 in this case.) After that, we'll just take the result and convert it back to
// floating point representation.
// The last line before the return is somewhat unrelated to the previous process.
// It is one iteration of a numerical root finding algorithm (Newton's Method) that improves
// the accuracy of the result.

// Also see: https://betterexplained.com/articles/understanding-quakes-fast-inverse-square-root/
// AND: https://thatonegamedev.com/math/fast-square-root-quake-iii/

/**
Function to estimate the inverse square root (the reciprocal or multiplicative inverse), 1 / sqrt(x).
Takes number that we're supposed to take the inversed square root of.
This code gets 1 / sqrt(x) using only multiplication and bit-shift operations.
Uses the fact that: in some sense the bit representation of a number is its own logarithm.
// To make the guess, it takes floating-point number in scientific notation, and negates and
// halves the exponent to get something close the the inverse square root.
// It then runs a round of Newton's approximation method to further refine the estimate and
// then, we've got something near the inverse square root.
*/
float Q_rsqrt( float number )
{
	long i; // Declare 32-bit number
	float x2, y; // 32-bit decimal numbers
	const float threehalfs = 1.5F;

	// Copy half of the input into x2 and the whole number to y
	x2 = number * 0.5F;
	y  = number;
	
	/**
	We stored our number into y. We now need to do some bit manipulation.
	Floats don't come with the tools we need to do.
	Floats are inherently tied to the IEEE Standard 754, so they were never designed to do bit manipulation.
	IEEE standard: first bit is sign bit (0: positive, 1: negative), the quake calculation is always positive, the next 8 bits are the exponent. (example: 2^x, x is exponent). The last 23 bits are the mantisa: For example, the mantissa of both log1020≈1.3010 and log10200≈2.3010 is 0.3010.
	
	Some tricks: bit shift a long to the left doubles it, to the right halves it (if the number is odd, then rounding occurs).
	
	What we want to do is put the bits, one to one, into a long (not just (long) y, since that rounds the number).
	The way you achieve this is by converting the memory address, not the number.
	First, we get the address of y (address of a float).
	Then convert that address from a floats address to a long's address. This doesn't change the address, but C now thinks that the number living at the address is a long. We have tricked C.
	This is how we get the bits of a number into the variable i.
	The bit shifting trick mentioned above works on exponents: bit shift to the left doubles and the right halves it: 
	Double an exponent squares the number and halving it gives the square root
	*/
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	//printf("\ni= %ld", i); // This won't make much sense (since it should be float...)
	
	/** 
	Remember, we want: 1 / sqrt(y)
	We instead calculate: log of 1 / sqrt(y).
	We can rewrite that to: log (y^-(1/2)).
	Then we have a division, but remember that we can do bitshift, hence: "- (i >> 1)".
	Why 0x5f3759df? 
	Since our logarithm is actually scaled and shifted...
	The "magic number" is a fix for the remnants of the errors by scaling factor and shifting.
	0x53759df is equal to 87513567 in decimal
	*/
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	
	// Now we have the bits of our solution, so we reverse the steps from the evil bit hack. This gives a good approximation.
	y  = * ( float * ) &i;
	//printf("\ny= %f", y);
	
	/** 
	The third step, gives us a better solution than the approximation:
	Newton iteration: newtons method finds a root for a given function. Derivative: dy/dx
	
	// Newguess = y - (error(y)) / (error'(y) where error(y) = y^-2 -i and error'(y) = -2y^-3
	// Which leads to: Newguess = y(1.5 - 0.5iy^2)
	One iteration: y = y * (threehalfs - (x2 * y * y));
	above is an iteration of f(y) = (1/y^2) - x.
	Notice that when y is a root of the function f(y) is equivalent to y being the inverse sqrt of x...
	*/
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

float findSQRT(float N) { return sqrt(N); }

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
  float myFloat = 2.5F;
  float fast_sqrt = Q_rsqrt(myFloat);
  printf("\n%.6f", fast_sqrt);

  // other code (result is the same as fast):
  //float fast_sqrt_two = InvSqrt(myFloat);
  //printf("\nOther: %f", fast_sqrt_two);

  // Comparison to the more correct (but slower) calculation:
  float slow_sqrt = (1/findSQRT(myFloat));
  printf("\n%f", slow_sqrt);
  return 0;
}