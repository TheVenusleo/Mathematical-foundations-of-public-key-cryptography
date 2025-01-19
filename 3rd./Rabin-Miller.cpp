#include<iostream>
#include<NTL/ZZ.h>
#include<NTL/ZZ_p.h>
using namespace std;
using namespace NTL;
bool Rabin_Miller(ZZ m)
{
	ZZ a = RandomBnd(m - 3) + 2;
	if (GCD(a, m) > ZZ(1))
	{
		cout << "m是合数" << endl;
		return false;
	}
	int s = 0;
	ZZ d = m - 1;
	while (d % 2 == 0)
	{
		d /= 2;
		s++;
	}
	ZZ_p a_modm;
	conv(a_modm, a);
	ZZ_p temp;
	temp = power(a_modm, d);
	if (temp == ZZ_p(1) || temp == ZZ_p(-1))
	{
		cout << "m是素数" << endl;
		return true;
	}
	for (int i = 1; i < s; i++)
	{
		int sum = 1;
		for (int j = 0; j < i; j++)
		{
			sum *= 2;
		}
		temp = power(a_modm, sum * d);
		if (temp == ZZ_p(-1))
		{
			cout << "m是素数" << endl;
			return true;
		}
	}
	cout << "m是合数" << endl;
	return false;
}
int main()
{
	ZZ m;
	cin >> m;
	ZZ_p::init(m);
	Rabin_Miller(m);
	return 0;
}