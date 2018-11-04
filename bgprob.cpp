#include <string>
#include <iostream>

/*
 * Converts a number to the appropriate string of bits given by the length
 *
 * c 		input number
 * length 	length of bitstring
 *
 * returns
 * string	bitstring of c
 */
std::string cts(unsigned int c, unsigned int length) {
	std::string s = std::string(length, '0');
	for (unsigned int i = 0; i < length; i++) {
		if ((c>>i)&1) s[length-1-i] = '1';
	}
	return s;
}

/*
 * Modulous power per Fermats little theorem
 *
 * a 		base
 * x		exponenet
 * q		modulous
 *
 * returns
 * int 		a^x mod q
 */
unsigned long powmod(unsigned long long a, unsigned long long x, unsigned long long q)
{
    unsigned long long r = 1;
    x = x%q;
    while(x > 0)
    {
        if ((x&0x1) == 1)
        {
            r = (r*a)%q;
        }
        x = x>>1;
        a = (a*a)%q;
    }
    return r;
}

int main(int argc, char* argv[])
{
	int p = 499;
	int q = 547;
	int a = -57;
	int b = 52;
	unsigned int n = p*q;
	unsigned int x0 = 159201;
	// In his case the message is stored as an unsigned int (32 bits)
	// Since the message is only 20 bits long, the least significant 12 bits are 0s
	unsigned int m = 0x9c10c000;
	int mlength = 20;

	unsigned int x = x0;
	std::cout << "x0: " << x << std::endl;
	unsigned int c[] = {0,0};

	std::cout << "Message: " << cts(m>>12, 20) << std::endl;

	// Encryption
	for (int i = 0; i < mlength/4; i++)
	{
		x = powmod(x,2,n);
		c[0] += (((x&0xf)^(m>>((7-i)*4)))&0xf)<<((7-i)*4);
		//std::cout << "x" << i+1 << ": " << x << std::endl;
	}
	c[1] = powmod(x,2,n);
	// c is the ciphertext
	std::cout << "Encrypted Message: " << cts(c[0]>>12, 20) << std::endl << "x_(t+1): " << c[1] << std::endl;

	// Decryption
	unsigned int d1 = powmod((p+1)/4, mlength/4 + 1, p-1);
	unsigned int d2 = powmod((q+1)/4, mlength/4 + 1, q-1);
	unsigned int u = powmod(c[1], d1, p);
	unsigned int v = powmod(c[1], d2, q);
	// std::cout << d1 << " " << d2 << " " << u << " " << v << std::endl;
	long dx0 = (v*a*p + u*b*q);
	while (dx0 < 0) dx0 += n;
	dx0 = dx0%n;
	std::cout << "x0: " << dx0 << std::endl;
	unsigned int dx = dx0;
	unsigned int dm = 0;
	for (int i = 0; i < mlength/4; i++)
	{
		dx = powmod(dx,2,n);
		dm += (((dx&0xf)^(c[0]>>((7-i)*4)))&0xf)<<((7-i)*4);
		//std::cout << "x" << i+1 << ": " << x << std::endl;
	}
	std::cout << "Decrypted Message: " << cts(dm>>12, 20) << std::endl;
}
