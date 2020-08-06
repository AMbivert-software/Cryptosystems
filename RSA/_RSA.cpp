#include "_RSA.h"
//public interface:
_RSA::_RSA(uint32_t maxSimpleRangeValue)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	uint32_t firstP = getRandomPrimeNumber(maxSimpleRangeValue);
	uint32_t secondQ = getRandomPrimeNumber(maxSimpleRangeValue);
	createKeys(firstP, secondQ);
}

uint64_t _RSA::getMult()
{
	return m_multPsQ;
}

uint64_t _RSA::getOpenKey()
{
	return m_openExp;
}

uint64_t _RSA::getCloseKey()
{
	return m_closeKey;
}

void _RSA::createNewKey(uint32_t maxSimpleRangeValue)
{
	uint32_t firstP = getRandomPrimeNumber(maxSimpleRangeValue);
	uint32_t secondQ = getRandomPrimeNumber(maxSimpleRangeValue);
	createKeys(firstP, secondQ);
}

std::vector<uint64_t> _RSA::encodedStringOfCharMessage(std::string message)
{
	std::vector<uint64_t>messageCryptVector;
	messageCryptVector.resize(message.size());
	for (size_t i = 0; i < message.size(); ++i)
	{
		messageCryptVector[i] = RapidExponentiation(static_cast<uint64_t>(message[i]), m_openExp, m_multPsQ);
	}
	return messageCryptVector;
}

std::vector<uint64_t> _RSA::encodedStringOfUnicodeMessage(std::wstring message)
{
	std::vector<uint64_t>messageCryptVector;
	messageCryptVector.resize(message.size());
	for (size_t i = 0; i < message.size(); ++i)
	{
		messageCryptVector[i] = RapidExponentiation(static_cast<uint64_t>(message[i]), m_openExp, m_multPsQ);
	}
	return messageCryptVector;
}

std::string _RSA::getDeCodedCharMessage(std::vector<uint64_t> cryptMessage)
{
	std::string DeCodeMessage;
	DeCodeMessage.resize(cryptMessage.size());

	for (size_t i = 0; i < cryptMessage.size(); ++i)
	{
		DeCodeMessage[i] = static_cast<char>(RapidExponentiation((cryptMessage[i]), m_closeKey, m_multPsQ));
	}
	return DeCodeMessage;
}

std::wstring _RSA::getDeCodedUnicodeMessage(std::vector<uint64_t> cryptMessage)
{
	std::wstring DeCodeMessage;
	DeCodeMessage.resize(cryptMessage.size());

	for (size_t i = 0; i < cryptMessage.size(); ++i)
	{
		DeCodeMessage[i] = static_cast<wchar_t>(RapidExponentiation((cryptMessage[i]), m_closeKey, m_multPsQ));
	}
	return DeCodeMessage;
}

//private interface
bool _RSA::getPrimeNumber(uint32_t number) {
	uint32_t sq = (uint32_t)sqrt(number);
	if (number % 2 != 0)
		for (size_t i = 3; i < sq; i += 2)
			if ((number % i) == 0) return 0;
	if (number % 2 == 0) return 0;
	return 1;
}

uint32_t _RSA::getRandomPrimeNumber(uint32_t maxSimpleRangeValue)
{
	bool flag = true;
	uint32_t randNum = 0;
	while (flag) {
		randNum = 1 + rand() % maxSimpleRangeValue;
		flag = !getPrimeNumber(randNum);
	}
	return randNum;
}

void _RSA::createKeys(uint64_t firstP, uint64_t secondQ)
{
	m_multPsQ = firstP * secondQ;
	uint64_t expOfEllerFunc = ((uint64_t)firstP - 1) * ((uint64_t)secondQ - 1);
	m_openExp = getRandomPrimeNumber(static_cast<uint32_t>(expOfEllerFunc));
	m_closeKey = getInverseMod(m_openExp, expOfEllerFunc);
};

int64_t _RSA::findingGCDexEuclidAlgorithm(int64_t a, int64_t b, int64_t& x, int64_t& y) { //Extended Euclidean algorithm.
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	int64_t x1, y1;
	int64_t d = findingGCDexEuclidAlgorithm(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

int64_t _RSA::getInverseMod(int64_t a, int64_t mod) { //The inverse of a modulo.
	int64_t x, y;
	findingGCDexEuclidAlgorithm(a, mod, x, y);
	x = (x % mod + mod) % mod;
	return x;
}

uint64_t _RSA::getSquareNumber(uint64_t number) { //Get square of number.
	return number * number;
}

uint64_t _RSA::RapidExponentiation(uint64_t number, uint64_t exp, uint64_t mod) //Rapid exponentiation.
{
	if (exp == 0) return 1;
	else
	{
		if (exp & 1U) return number * RapidExponentiation(number, exp - 1, mod) % mod;
		else return getSquareNumber(RapidExponentiation(number, exp / 2, mod)) % mod;
	}
}