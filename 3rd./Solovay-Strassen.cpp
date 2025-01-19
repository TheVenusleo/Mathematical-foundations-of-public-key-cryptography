#include <iostream>
#include<NTL/ZZ.h>
#include<NTL/BasicThreadPool.h>
using namespace std;
using namespace NTL;
//计算jacobi（a/m）
bool  Solovay_Strassen(const ZZ& m, int interations)
{
	if (m <= 1)
	{
		return false;//1不是素数
	}
	else if (m == 2)
	{
		return true;//2是素数

	}
	else if (m % 2 == 0)
	{
		return false;//此时一定为合数

	}
	for (int i = 0; i < interations; ++i)
	{
		ZZ a = RandomBnd(m - 2) + 1;//随机选取1<a<m
		if(GCD(a,m)==!1)
		{
			return false;//如果（a，m）不等于时为合数
		}
		ZZ index = (m - 1) / 2;
		ZZ a_index_mod = PowerMod(a, index, m);//计算a的（m-1）/2次方modm
	    int  jacobi = Jacobi(a, m);
		ZZ jacobii = conv<ZZ>(jacobi);
		ZZ result = jacobii % m;
		if(a_index_mod!=result)
		{
			return false;
		}
	}

	return true;

}




int main() {
	ZZ m;
	int interations = 10;
	cout << "请输入需要测试的数m:" << endl;
	cin >> m;
	if (Solovay_Strassen(m, interations))
	{
		cout << m << "为素数(可能为素数)" << endl;
	}
	else {
		cout << m << "一定为合数" << endl;
	}
	return 0;



}