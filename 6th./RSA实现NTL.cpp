#include<iostream>
#include<chrono>
#include<NTL/ZZ.h>
using namespace std;
using namespace NTL;
using namespace std::chrono;
ZZ generate_prime(long bits)
{
	ZZ prime;
	GenPrime(prime, bits);
	return prime;
}
ZZ prime(long bits)
{
	ZZ prime1 = generate_prime(bits);
	ZZ prime2 = generate_prime(bits);
	return prime1, prime2;
}
ZZ generate_keys(ZZ& n, ZZ& e, ZZ& d, long bits,ZZ prime1,ZZ prime2)
{
	prime(bits);
	n = prime1 * prime2;//模数
	ZZ o = (prime1 - 1) * (prime2 - 1);

	e = ZZ(65537);
	while (GCD(e, o) != 1)
	{
		e += 2;
	}

	d = InvMod(e, o);
	return n, e, d,prime1,prime2;
}
ZZ encrypt(ZZ& m, ZZ& e, ZZ& n)
{
	return PowerMod(m, e, n);
}

ZZ decrypt(ZZ& c, ZZ& d, ZZ prime1, ZZ prime2, ZZ& n)
{
	ZZ d1 = d % (prime1 - 1);
	ZZ d2 = d % (prime2 - 1);
	ZZ m1 = PowerMod(c, d1, prime1);
	ZZ m2 = PowerMod(c, d2, prime2);
	ZZ q_ = InvMod(prime2, prime1);
	ZZ h = (q_ * (m1 - m2)) % prime1;
	if (h < 0)
	{
		h += prime1;
	}
	ZZ m = m2 + h * prime2;
	return m;
}

int main()
{

	long bits = 1024;
	ZZ n, e, d,prime1,prime2;
	ZZ prime(long bits);
	generate_keys(n, e, d, bits,prime1,prime2);
	ZZ m;
	cin >> m;
	auto start = high_resolution_clock::now();
	ZZ c = encrypt(m, e, n);
	cout << "加密密文为" << c << endl;
	cout << "解密为" << decrypt(c, d, prime1,prime2,n) << endl;
	if (m == decrypt(c, d,prime1,prime2,n))
	{
		cout << "解密正确" << endl;

	}
	else
	{
		cout << "解密错误" << endl;
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start).count();

	cout << "消耗时间为" << duration << " ms" << endl;
	return 0;
}