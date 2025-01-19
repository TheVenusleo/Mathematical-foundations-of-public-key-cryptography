#include<iostream>
#include<NTL/ZZ.h>
using namespace std;
using namespace NTL;
ZZ continued_fraction_attack(ZZ N, ZZ e, ZZ C)
{
	ZZ t;
	ZZ delta;
	ZZ x = N;
	ZZ y = e;
	ZZ a;
	ZZ p_array[3] = { ZZ(0), ZZ(0), ZZ(1) };
	ZZ q_array[3] = { ZZ(0), ZZ(1), N / e };
	while (true)
	{
		x -= x / y * y;
		swap(x, y);
		a = x / y;//Euclid算法
		p_array[0] = p_array[1];
		p_array[1] = p_array[2];
		q_array[0] = q_array[1];
		q_array[1] = q_array[2];
		p_array[2] = a * p_array[1] + p_array[0];
		q_array[2] = a * q_array[1] + q_array[0];
		if ((e * q_array[2] - 1) % p_array[2] != 0)continue;
		t = N - (e * q_array[2] - 1) / p_array[2] + 1;
		delta = t * t - 4 * N;
		if (delta < 0)continue;
		if (sqr(SqrRoot(delta)) != delta)continue;
		if ((t - SqrRoot(delta)) % 2 != 0)continue;
		break;
	}
	ZZ p = (t + SqrRoot(delta)) / 2;
	ZZ q = (t - SqrRoot(delta)) / 2;
	if (p * q != N)
	{
		cout << "failed" << endl;
		return ZZ(0);
	}
	ZZ φN = (p - 1) * (q - 1);
	ZZ d = InvMod(e, φN);
	ZZ r = PowerMod(C % p, d % (p - 1), p);
	ZZ R = PowerMod(C % q, d % (q - 1), q);
	CRT(r, p, R, q);//使用中国剩余定理解密
	ZZ m = r % N;
	cout << "破解出的明文m=" << m << endl;
	return m;
}
int main()
{
	ZZ p = GenPrime_ZZ(1024);
	ZZ q = GenPrime_ZZ(1024);
	ZZ N = p * q;
	ZZ φN = (p - 1) * (q - 1);
	ZZ upper_bound = SqrRoot(SqrRoot(N)) / 3;
	ZZ d = RandomBnd(upper_bound - 2) + 2;//d要满足1<d<(1/3)N^(1/4)才可进行连分数攻击
	while (GCD(d, φN) > 1)
	{
		d = RandomBnd(upper_bound - 2) + 2;
	}
	ZZ e = InvMod(d, φN);
	ZZ m = RandomBnd(N);
	//cout << "p=" << p << endl;
	//cout << "q=" << q << endl;
	//cout << "N=" << N << endl;
	//cout << "e=" << e << endl;
	//cout << "d=" << d << endl;
	cout << "生成出的明文m=" << m << endl;
	ZZ a = PowerMod(m % p, e % (p - 1), p);
	ZZ A = PowerMod(m % q, e % (q - 1), q);
	CRT(a, p, A, q);//使用中国剩余定理加密
	ZZ C = a % N;
	if (continued_fraction_attack(N, e, C) == m)
	{
		cout << "攻击成功" << endl;
	}
	else
	{
		cout << "攻击失败" << endl;
	}
	return 0;
}