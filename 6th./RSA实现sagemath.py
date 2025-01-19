#!/usr/bin/env python
# coding: utf-8

# In[1]:


#编写一般RSA算法
def RSA(p,q,n,phi_n,e,d,m):
    t_1 = time.time()
    #加密
    c = power_mod(m, e, n)
    print("c = ",c)
    
    #解密
    M = power_mod(int(c),int(d),int(n))
    
    #验证
    if(int(M) == int(m)):
        print("RSA算法成功实现")
    else:
        print("RSA算法出错")
    t_2 = time.time()
    
    #计算时间
    time_1 = t_2 - t_1
    return time_1


# In[2]:


#编写CRT算法
def CRT(p,q,n,e,d,m):
    t_3 = time.time()
    #加密
    c = power_mod(m, e, n)
    print("c = ",c)
    
    #解密
    d_p = d % (p - 1)
    d_q = d % (q - 1)

    q_inv = pow(q,-1,p)#q在模p下的逆元

    m_p = power_mod(c,int(d_p),p)
    m_q = power_mod(c,int(d_q),q)#对p,q分别解密
    M = (int(m_q) + int(q) * int(((m_p - m_q) * q_inv % p)) % n)

    #验证
    if(int(M) == int(m)):
        print("CRT算法成功实现")
    else:
        print("CRT算法出错")
    t_4 = time.time()
    
    #计算时间
    time_2 = t_4 - t_3
    return time_2


# In[3]:


import time
#生成密钥
p = random_prime(2^1024, lbound=2^(1024-1))
q = random_prime(2^1024, lbound=2^(1024-1))
n = p * q
phi_n = (p - 1) * (q - 1)
e = 65537
d = pow(e,-1,phi_n)
m = randint(1,10**23)
print("m = ",m)


# In[4]:


#调用函数，计算时间差
time_1 = RSA(p,q,n,phi_n,e,d,m)
print("RSA算法所用时间为：",time_1)
time_2 = CRT(p,q,n,e,d,m)
print("CRT算法所用时间为：",time_2)

if(time_1 > time_2):
    print("CRT算法所需时间更短，两种算法所需时间的差值为：",(time_1 - time_2))
else:
    print("?")

