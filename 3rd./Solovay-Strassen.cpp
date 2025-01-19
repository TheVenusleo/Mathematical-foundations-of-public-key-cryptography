#include <iostream>
#include<NTL/ZZ.h>
#include<NTL/BasicThreadPool.h>
using namespace std;
using namespace NTL;
//����jacobi��a/m��
bool  Solovay_Strassen(const ZZ& m, int interations)
{
	if (m <= 1)
	{
		return false;//1��������
	}
	else if (m == 2)
	{
		return true;//2������

	}
	else if (m % 2 == 0)
	{
		return false;//��ʱһ��Ϊ����

	}
	for (int i = 0; i < interations; ++i)
	{
		ZZ a = RandomBnd(m - 2) + 1;//���ѡȡ1<a<m
		if(GCD(a,m)==!1)
		{
			return false;//�����a��m��������ʱΪ����
		}
		ZZ index = (m - 1) / 2;
		ZZ a_index_mod = PowerMod(a, index, m);//����a�ģ�m-1��/2�η�modm
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
	cout << "��������Ҫ���Ե���m:" << endl;
	cin >> m;
	if (Solovay_Strassen(m, interations))
	{
		cout << m << "Ϊ����(����Ϊ����)" << endl;
	}
	else {
		cout << m << "һ��Ϊ����" << endl;
	}
	return 0;



}