#include<iostream>
#include<string>
#include<NTL/ZZ.h>
#include<NTL/ZZ_p.h>
#include<NTL/mat_ZZ_p.h>
#include<NTL/vec_ZZ_p.h>
using namespace std;
using namespace NTL;
struct equation
{
	mat_ZZ_p matrix;//矩阵
	vec_ZZ_p vector;/*向量*/
	equation(int num_x,int num_equation)
	{
		matrix.SetDims(num_equation, num_x);
		vector.SetLength(num_equation);
	}
};
equation input()
{
	string a = "110101190001011009";
	string b = "236265196008162472";
	string c = "65256919760524176X";
	equation eq(3, 3);
	eq.vector[0] = 3;//反向查表得到效验码对应的Y
	eq.vector[1] = 10;
	eq.vector[2] = 2;
	int arr[14] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5 };
	int sum = 0;
	for (int i = 0; i < 14; i++)
	{
		sum += arr[i] * (a.at(i) - 48);/*ascll*/
	}
	eq.vector[0] -= sum;
	sum = 0;
	for (int i = 0; i < 14; i++)
	{
		sum += arr[i] * (b.at(i) - 48);
	}
	eq.vector[1] -= sum;
	sum = 0;
	for (int i = 0; i < 14; i++)
	{
		sum += arr[i] * (c.at(i) - 48);
	}
	eq.vector[2] -= sum;
	eq.matrix[0][0] = a.at(14) - 48;
	eq.matrix[0][1] = a.at(15) - 48;
	eq.matrix[0][2] = a.at(16) - 48;
	eq.matrix[1][0] = b.at(14) - 48;
	eq.matrix[1][1] = b.at(15) - 48;
	eq.matrix[1][2] = b.at(16) - 48;
	eq.matrix[2][0] = c.at(14) - 48;
	eq.matrix[2][1] = c.at(15) - 48;
	eq.matrix[2][2] = c.at(16) - 48;
	return eq;
}
void solve_equation(equation eq)
{
	vec_ZZ_p solution;
	solution.SetLength(3);
	ZZ_p d = determinant(eq.matrix);
	solve(d, eq.matrix, solution, eq.vector);
	cout << "x = " << solution[0] << endl;
	cout << "y = " << solution[1] << endl;
	cout << "z = " << solution[2] << endl;
}
int main()
{
	ZZ_p::init(ZZ(11));
	solve_equation(input());
	return 0;
}