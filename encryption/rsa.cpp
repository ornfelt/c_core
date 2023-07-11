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

Advantages:
Security: RSA algorithm is considered to be very secure and is widely used for secure data
transmission.

Public-key cryptography: RSA algorithm is a public-key cryptography algorithm, which means
that it uses two different keys for encryption and decryption. The public key is used to
encrypt the data, while the private key is used to decrypt the data.

Key exchange: RSA algorithm can be used for secure key exchange, which means that two
parties can exchange a secret key without actually sending the key over the network.

Digital signatures: RSA algorithm can be used for digital signatures, which means that a
sender can sign a message using their private key, and the receiver can verify the
signature using the sender’s public key.

Disadvantages:
Slow processing speed: RSA algorithm is slow compared to other encryption algorithms,
especially when dealing with large amounts of data.

Large key size: RSA algorithm requires large key sizes to be secure, which means that it
requires more computational resources and storage space.

Vulnerability to side-channel attacks: RSA algorithm is vulnerable to side-channel
attacks, which means that an attacker can use information leaked through side channels
such as power consumption, electromagnetic radiation, and timing analysis to extract the
private key.

Limited use in some applications: RSA algorithm is not suitable for some applications,
such as those that require constant encryption and decryption of large amounts of
data, due to its slow processing speed.

Below shows encryption and decryption of plain text messages containing alphabets and
numbers using their ASCII value:
*/

using namespace std;

set<int> prime; // a set will be the collection of prime numbers,
		// where we can select random primes p and q
int public_key;
int private_key;
int n;
// we will run the function only once to fill the set of
// prime numbers
void primefiller()
{
	// method used to fill the primes set is seive of
	// eratosthenes(a method to collect prime numbers)
	vector<bool> seive(250, true);
	seive[0] = false;
	seive[1] = false;
	for (int i = 2; i < 250; i++) {
		for (int j = i * 2; j < 250; j += i) {
			seive[j] = false;
		}
	} // filling the prime numbers
	for (int i = 0; i < seive.size(); i++) {
		if (seive[i])
			prime.insert(i);
	}
}
// picking a random prime number and erasing that prime
// number from list because p!=q
int pickrandomprime()
{
	int k = rand() % prime.size();
	auto it = prime.begin();
	while (k--)
		it++;
	int ret = *it;
	prime.erase(it);
	return ret;
}
void setkeys()
{
	int prime1 = pickrandomprime(); // first prime number
	int prime2 = pickrandomprime(); // second prime number
	// to check the prime numbers selected
	// cout<<prime1<<" "<<prime2<<endl;
	n = prime1 * prime2;
	int fi = (prime1 - 1) * (prime2 - 1);
	int e = 2;
	while (1) {
		if (__gcd(e, fi) == 1)
			break;
		e++;
	} // d = (k*Φ(n) + 1) / e for some integer k
	public_key = e;
	int d = 2;
	while (1) {
		if ((d * e) % fi == 1)
			break;
		d++;
	}
	private_key = d;
}
// to encrypt the given number
long long int encrypt(double message)
{
	int e = public_key;
	long long int encrpyted_text = 1;
	while (e--) {
		encrpyted_text *= message;
		encrpyted_text %= n;
	}
	return encrpyted_text;
}
// to decrypt the given number
long long int decrypt(int encrpyted_text)
{
	int d = private_key;
	long long int decrypted = 1;
	while (d--) {
		decrypted *= encrpyted_text;
		decrypted %= n;
	}
	return decrypted;
}
// first converting each character to its ASCII value and
// then encoding it then decoding the number to get the
// ASCII and converting it to character
vector<int> encoder(string message)
{
	vector<int> form;
	// calling the encrypting function in encoding function
	for (auto& letter : message)
		form.push_back(encrypt((int)letter));
	return form;
}
string decoder(vector<int> encoded)
{
	string s;
	// calling the decrypting function decoding function
	for (auto& num : encoded)
		s += decrypt(num);
	return s;
}
int main()
{
	primefiller();
	setkeys();
	string message = "Test Message WOOHOOO";
	// uncomment below for manual input
	// cout<<"enter the message\n";getline(cin,message);
	// calling the encoding function
	vector<int> coded = encoder(message);
	cout << "Initial message:\n" << message;
	cout << "\n\nThe encoded message(encrypted by public "
			"key)\n";
	for (auto& p : coded)
		cout << p;
	cout << "\n\nThe decoded message(decrypted by private "
			"key)\n";
	cout << decoder(coded) << endl;
	return 0;
}
