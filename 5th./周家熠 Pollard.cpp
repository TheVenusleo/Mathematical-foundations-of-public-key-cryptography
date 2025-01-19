#include<iostream>
#include<NTL/ZZ.h>
#include<NTL/ZZ_p.h>
using namespace std;
using namespace NTL;
ZZ Pollard_ρ(ZZ p, ZZ g, ZZ h)
{
	ZZ ai, aj, bi, bj = ZZ(0);
	ZZ xi = ZZ(1); ZZ xj = ZZ(1);
	while (true)
	{
		switch (xi % 3)
		{
			case 0: xi = xi * g % p; ai = (ai + 1) % (p - 1); break;
			case 1: xi = xi * h % p; bi = (bi + 1) % (p - 1); break;
			case 2: xi = xi * xi % p; ai = ai * 2 % (p - 1);  bi = bi * 2 % (p - 1); break;
		}
		switch (xj % 3)
		{
			case 0: xj = xj * g % p; aj = (aj + 1) % (p - 1); break;
			case 1: xj = xj * h % p; bj = (bj + 1) % (p - 1); break;
			case 2: xj = xj * xj % p; aj = aj * 2 % (p - 1);  bj = bj * 2 % (p - 1); break;
		}
		switch (xj % 3)
		{
			case 0: xj = xj * g % p; aj = (aj + 1) % (p - 1); break;
			case 1: xj = xj * h % p; bj = (bj + 1) % (p - 1); break;
			case 2: xj = xj * xj % p; aj = aj * 2 % (p - 1);  bj = bj * 2 % (p - 1); break;
		}
		if (xi == xj)break;
	}
	ZZ a = (bi - bj) % (p - 1);
	if (a == 0)
	{
		cout << "failed" << endl;
		return ZZ(0);
	}
	ZZ b = (aj - ai) % (p - 1);
	ZZ gcd = GCD(a, p - 1);
	ZZ r = b / gcd * InvMod(a / gcd, (p - 1) / gcd) % ((p - 1) / gcd);
	ZZ_p g_mod, h_mod;
	conv(g_mod, g);
	conv(h_mod, h);
	for (int i = 0; i < gcd; i++)
	{
		if (power(g_mod, r + i * (p - 1) / gcd) == h_mod)return (r + i * (p - 1) / gcd);
	}
}
int main()
{
	ZZ p, g, h;
	cout << "请依次输入p g h" << endl;
	cin >> p >> g >> h;
	ZZ_p::init(p);
	cout << Pollard_ρ(p, g, h) << endl;
	return 0;
}