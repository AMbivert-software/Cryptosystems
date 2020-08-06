		COPYRIGHT:
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

**The keys for the RSA algorithm are generated the following way:**

	1. Choose two different large random prime numbers p & q.
	2. Calculate n = p*q.
	3. Calculate f(n) = (p-1)*(q-1).
	4. Choose an integer 'e' such that 1 < e < f(n),
		and 'e' is co-prime to f(n)
		'e' is released as the public key exponent.
	5. Comput 'd' to satisfy the congruence relatin d*e ~~ 1 mod f(n).

**Example:**  
	1. p = 3557. & q = 2579.  
	2. n = p * q = 3557 * 2579 = 9173503.  
	3. f(n) = (p - 1) * (q - 1) = 9167368.  
	4. e = 3 (a good option would be:  3, 17 or 65537).  
	5. d = (pow(e, -1) mod f(n))  
	   d = 6111579.  
	6. {e, n} = {3, 9173503}.  
	7. {d, n} = {6111579, 9173503}.  
**coding:**  
	* message = 111111.  
	* code_message = pow(m, e) mod n =  
		     = pow(111111, 3) mod 9173503 =  
		     = 4051753.  
**decoding:**  
	* message = pow(code_message, d) mod n =  
	        = pow(4051753, 6111579) mod 9173503 =  
	        = 111111  
