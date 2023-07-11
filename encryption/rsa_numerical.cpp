#include <bits/stdc++.h>

/**
https://www.geeksforgeeks.org/rsa-algorithm-cryptography/

RSA algorithm is an asymmetric cryptography algorithm. Asymmetric actually means that it
works on two different keys i.e. Public Key and Private Key. As the name describes that
the Public Key is given to everyone and the Private key is kept private.

An example of asymmetric cryptography: 

    A client (for example browser) sends its public key to the server and requests some data.
    The server encrypts the data using the client’s public key and sends the encrypted data.
    The client receives this data and decrypts it.

Since this is asymmetric, nobody else except the browser can decrypt the data even if a
third party has the public key of the browser.

The idea! The idea of RSA is based on the fact that it is difficult to factorize a large
integer. The public key consists of two numbers where one number is a multiplication of
two large prime numbers. And private key is also derived from the same two prime numbers.
So if somebody can factorize the large number, the private key is compromised. Therefore
encryption strength totally lies on the key size and if we double or triple the key size,
the strength of encryption increases exponentially. RSA keys can be typically 1024 or 2048
bits long, but experts believe that 1024-bit keys could be broken in the near future. But
till now it seems to be an infeasible task.

Let us learn the mechanism behind the RSA algorithm : >> Generating Public Key: 

Select two prime no's. Suppose P = 53 and Q = 59.
Now First part of the Public key  : n = P*Q = 3127.
 We also need a small exponent say e : 
But e Must be 
An integer.
Not be a factor of Φ(n). 
1 < e < Φ(n) [Φ(n) is discussed below], 
Let us now consider it to be equal to 3.
    Our Public Key is made of n and e

>> Generating Private Key: 

We need to calculate Φ(n) :
Such that Φ(n) = (P-1)(Q-1)     
      so,  Φ(n) = 3016
    Now calculate Private Key, d : 
d = (k*Φ(n) + 1) / e for some integer k
For k = 2, value of d is 2011.

Now we are ready with our – Public Key ( n = 3127 and e = 3) and Private Key(d = 2011) Now
we will encrypt “HI”:

Convert letters to numbers : H  = 8 and I = 9
    Thus Encrypted Data c = 89e mod n. 
Thus our Encrypted Data comes out to be 1394

Now we will decrypt 1394 : 
    Decrypted Data = cd mod n. 
Thus our Encrypted Data comes out to be 89
8 = H and I = 9 i.e. "HI".

Below shows encryption and decryption of small numerical values
*/

using namespace std;

// Returns gcd of a and b
int gcd(int a, int h)
{
	int temp;
	while (1) {
		temp = a % h;
		if (temp == 0)
			return h;
		a = h;
		h = temp;
	}
}

// Code to demonstrate RSA algorithm
int main()
{
	// Two random prime numbers
	double p = 3;
	double q = 7;

	// First part of public key:
	double n = p * q;

	// Finding other part of public key.
	// e stands for encrypt
	double e = 2;
	double phi = (p - 1) * (q - 1);
	while (e < phi) {
		// e must be co-prime to phi and
		// smaller than phi.
		if (gcd(e, phi) == 1)
			break;
		else
			e++;
	}

	// Private key (d stands for decrypt)
	// choosing d such that it satisfies
	// d*e = 1 + k * totient
	int k = 2; // A constant value
	double d = (1 + (k * phi)) / e;

	// Message to be encrypted
	double msg = 12;

	printf("Message data = %lf", msg);

	// Encryption c = (msg ^ e) % n
	double c = pow(msg, e);
	c = fmod(c, n);
	printf("\nEncrypted data = %lf", c);

	// Decryption m = (c ^ d) % n
	double m = pow(c, d);
	m = fmod(m, n);
	printf("\nOriginal Message Sent = %lf", m);

	return 0;
}
