#!/usr/bin/env python
# coding: utf-8

# In[4]:


from sage.all import *
import math

# 计算素因数分解
def fenjie(n):
    #创建元组存储因子
    fs = [] 
    # 检查偶数因子
    count = 0
    while n % 2 == 0:
        n //= 2
        count += 1
    if count > 0:
        fs.append((2, count)) 
    
    # 检查奇数因子
    f = 3 #从2之后的最小因子3开始
    while f * f <= n:
        count = 0
        while n % f == 0:
            n //= f
            count += 1
        if count > 0:
            fs.append((f, count))
        f += 2
    
    if n > 1:
        fs.append((n, 1))
    
    return fs

# range(p)暴力搜索计算离散对数
def find(g, h, p):
    for x in range(p):
        if pow(g, x, p) == h:  #g**x mod p == h
            return x
    return None

# 实现Pohlig-Hellman算法
def pohlig_hellman(g, h, p):
    # 1. 获取群的阶p-1的素因数分解
    fs = fenjie(p - 1)
    
    # 存储每个素因子阶的离散对数解
    s = []
    
    # 2. 处理每个素因子阶
    for q, i in fs:
        q_i = q ** i
        
        # 3. 计算当前素因子阶的问题：g**x ≡ h (mod p)，但是阶为q_i
        # 通过暴力搜索计算离散对数
        s_i = find(g, h, p)
        if s_i is None:
            raise ValueError(f"子问题无解，检查输入参数")
        
        s.append(s_i)
    
    # 4. 使用孙子定理合并解
    x = crt(s, [q ** i for q, i in fs])
    
    return x

p = 17
g = 3     
h = 10  

# Pohlig-Hellman算法
result = pohlig_hellman(g, h, p)
print("离散对数结果:", result)


# In[ ]:




