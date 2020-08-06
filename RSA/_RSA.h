#pragma once
#include <iostream>
#include <vector>
#include <ctime>



// COPYRIGHT:
/*
:::::::::::::::::::::::::::::::::::::::::
	https://uk.wikipedia.org/wiki/RSA
:::::::::::::::::::::::::::::::::::::::::


RSA (Rivest, Shamir, Adleman)
RSA is an algorithm used by modern computers to encrypt and decrypt messages.
It is an asymmetric cryptographic algorithm. Asymmetric means that there are two different keys.
This is also called public key cryptography, because one of the keys can be given to anyone.
The other key must be kept private.
The algorithm is based on the fact that finding the factors of a large composite number is difficult:
when the factors are prime numbers, the problem is called prime factorization.
It is also a key pair (public and private key) generator.

The keys for the RSA algorithm are generated the following way:

	1. Choose two different large random prime numbers p & q.
	2. Calculate n = p*q.
	3. Calculate f(n) = (p-1)*(q-1).
	4. Choose an integer 'e' such that 1 < e < f(n),
		and 'e' is co-prime to f(n)
		'e' is released as the public key exponent.
	5. Comput 'd' to satisfy the congruence relatin d*e ~~ 1 mod f(n)

EXAMPLE:
	1. p = 3557. & q = 2579.
	2. n = p * q = 3557 * 2579 = 9173503.
	3. f(n) = (p - 1) * (q - 1) = 9167368.
	4. e = 3 (a good option would be:  3, 17 or 65537)
	5. d = (pow(e, -1) mod f(n))
	   d = 6111579
	6. {e, n} = {3, 9173503}.
	7. {d, n} = {6111579, 9173503}.
   coding:
	message = 111111
	code_message = pow(m, e) mod n =
				   pow(111111, 3) mod 9173503
				   = 4051753
   decoding:
	message = pow(code_message, d) mod n
	= pow(4051753, 6111579) mod 9173503
	= 111111

*/

class _RSA
{
public:
	_RSA(uint32_t maxSimpleRangeValue = 6144);
	~_RSA() {}

	uint64_t getMult(); // return Multiply of first&second simple numbers.
	uint64_t getOpenKey(); // return open key for coding data.
	uint64_t getCloseKey(); // return close key for decoding data.

	void createNewKey(uint32_t maxSimpleRangeValue = 6144); //reCreate Keys for encode

	std::vector<uint64_t> encodedStringOfCharMessage(std::string message); //get a vector of encoded numbers of CharString.
	std::vector<uint64_t> encodedStringOfUnicodeMessage(std::wstring message); //get a vector of encoded numbers of UnicodeString.
	std::string getDeCodedCharMessage(std::vector<uint64_t> cryptMessage); //get the decoded CharString.
	std::wstring getDeCodedUnicodeMessage(std::vector<uint64_t> cryptMessage); //get the the decoded UnicodeString.

	
private:
	uint64_t m_multPsQ;
	uint64_t m_openExp;
	uint64_t m_closeKey;

	bool getPrimeNumber(uint32_t number); //checking for a Prime number.
	uint32_t getRandomPrimeNumber(uint32_t maxSimpleRangeValue); //get random Prime number.

	void createKeys(uint64_t firstP, uint64_t secondQ); //a multiplication of numbers & opennExponent & close Key.

	int64_t findingGCDexEuclidAlgorithm(int64_t a, int64_t b, int64_t& x, int64_t& y); //Extended Euclidean algorithm.

	int64_t getInverseMod(int64_t a, int64_t mod); //The inverse of a modulo.
	
	uint64_t getSquareNumber(uint64_t x); //square of number.

	uint64_t RapidExponentiation(uint64_t number, uint64_t exp, uint64_t mod = LLONG_MAX); //Rapid exponentiation.

};

