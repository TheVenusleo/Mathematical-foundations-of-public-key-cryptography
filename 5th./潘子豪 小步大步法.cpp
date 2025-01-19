#include <NTL/ZZ.h>
#include <vector>
#include <cmath>
#include <iostream>

using namespace NTL;
using namespace std;

ZZ BabyStepGiantStep(ZZ g, ZZ h, ZZ p) {
    // 首先计算 m = ⌈√N⌉，其中 N 为模数 p 的阶
    ZZ m = SqrRoot(p) + 1;

    // 使用 vector 存储小步表
    vector<pair<ZZ, ZZ>> baby_steps;

    // 然后计算所有小步值：g^a0 (mod p)
    ZZ cur = ZZ(1); // 初始值 g^0 = 1
    for (ZZ a0 = ZZ(0); a0 < m; a0++) {
        baby_steps.push_back(make_pair(cur, a0));  // 存储 (g^a0, a0)
        cur = (cur * g) % p;  // 递推计算 g^(a0+1)
    }

    // 计算 g^(-m) (模逆元的 m 次幂)
    ZZ g_m = PowerMod(g, -m, p);

    // 进行大步搜索：h * (g^(-m))^a1 (mod p)
    cur = h;  // 初始值为 h
    for (ZZ a1 = ZZ(0); a1 < m; a1++) {
        // 线性查找匹配的小步值
        for (const auto& entry : baby_steps) {
            if (entry.first == cur) {
                // 找到匹配的小步值
                ZZ a0 = entry.second;
                return a0 + a1 * m;  // a = a0 + a1 * m
            }
        }
        cur = (cur * g_m) % p;  // 更新为 h * (g^(-m))^(a1+1)
    }

    // 如果未找到解
    return ZZ(-1);
}

int main() {
   
    ZZ g, h, p;
    cout << "请输入模数 p: ";
    cin >>p;
    cout << "请输入基 g: ";
    cin >> g;
    cout << "请输入结果 h: ";
    cin >> h;
    ZZ result = BabyStepGiantStep(g, h, p);
    if (result != -1) {
        cout << "离散对数 a: " << result << endl;
    }
    else {
        cout << "未找到解。" << endl;
    }

    return 0;
}
