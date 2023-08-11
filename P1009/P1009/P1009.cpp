#include<iostream>
using namespace std;
#define LEN 100

struct hp //高精度变量
{
    int a; //位数
    int str[LEN]; //每一位的数
};

struct hp init() //初始化
{
    hp x;
    for (int i = 0; i < LEN; i++) //全部赋值为0
    {
        x.str[i] = 0;
    }
    x.a = 99;
    return x;
}

//如果不将x_t变成全局变量，就会引发错误"Run-Time Check Failure #2 - Stack around the variable 'x' was corrupted." ?

struct hp in() //输入函数
{
    hp x_t;
    string a;
    cin >> a;
    x_t.a = a.length();
    for (int i = a.length(); i >= 1; i--)
    {
        x_t.str[i] = a[a.length() - i] - '0'; //注意str类型和int类型的转换
    }
    for (int i = a.length() + 1; i <= LEN - 1; i++) //其余赋值为0
    {
        x_t.str[i] = 0;
    }
    return x_t;
}

void out(struct hp x) //输出函数
{
    
    for (int i = LEN - 1; i >= 1; i--)
    {
        if (x.str[i] != 0)
        {
            x.a = i;
            break;
        }
    }
    for (int i = x.a; i >= 1; i--)
    {
        cout << x.str[i] << "";
    }
}

struct hp add(struct hp a, struct hp b) //加法
{
    hp x;
    int c = max(a.a, b.a); //取最大位数
    int k = 0;//进位
    for (int i = 1; i <= c; i++)
    {
        x.str[i] = (a.str[i] + b.str[i] + k) % 10; //取每一位
        k = (a.str[i] + b.str[i] + k) / 10; //进位
    }
    if (k == 1) //还有1位
    {
        x.a = c + 1;
        x.str[c + 1] = 1;
    }
    else //完了
    {
        x.a = c;
    }
    return x;
}

struct hp mult_t(struct hp a, int b, int d) // 多位数乘一位数 a代表多位数，b代表一位数，d代表一位数的位数
{
    hp x;
    x = init();
    int c = a.a; //取最大位数
    int k = 0;//进位
    for (int i = 1; i <= c; i++)
    {
        x.str[i] = (a.str[i] * b + k) % 10; //取每一位
        k = (a.str[i] * b + k) / 10; //进位
    }
    if (k >= 1) //还有1位
    {
        x.a = c + 1;
        x.str[c + 1] = k;
    }
    else //完了
    {
        x.a = c;
    }
    hp y;
    y = init();
    y.a = x.a + d - 1;
    for (int i = d; i <= x.a + d - 1; i++) //位数调整
    {
        y.str[i] = x.str[i - d + 1];
    }
    return y;
}

struct hp mult(struct hp a, struct hp b) //多位数乘多位数
{
    hp x;
    x = init();
    for (int i = 1; i <= a.a; i++)
    {
        x = add(x, mult_t(b, a.str[i], i));
    }
    for (int i = LEN - 1; i >= 1; i--)
    {
        if (x.str[i] != 0)
        {
            x.a = i;
            break;
        }
    }
    return x;
}

struct hp to_hp(int a)
{
    int b = a;
    int i = 1;
    hp x;
    while (b != 0)
    {
        x.str[i] = b % 10;
        b /= 10;
        i++;
    }
    x.a = i - 1;
    return x;
}

struct hp jc(int a)
{
    hp sum;
    sum = init();
    sum.str[1] = 1;
    for (int i = 1; i <= a; i++)
    {
        hp k = to_hp(i);
        sum = mult(sum, k);
    }
    return sum;
}

int main()
{
    int a;
    cin >> a;
    hp sum;
    sum = init();
    for (int i = 1; i <= a; i++)
    {
        sum = add(sum, jc(i));
    }
    out(sum);
}
/*
#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>
#define LEN 1000 //没分号
using namespace std;

struct hp
{
    char str[LEN];
    int a[LEN];
};

void init(struct hp* x)//hp初始化函数
{
    for (int i = 0; i < LEN; ++i)
    {
        x->a[i] = 0;
        x->str[1] = '\0';
    }
}

void in(struct hp* x)//输入函数
{
    scanf("&s", x->str);
    int len = strlen(x->str);
    for (int i = 0; i < len; ++i)
        x->a[i] = x->str[len - i - 1] - '0';
}

void add(struct hp x, struct hp y, struct hp* ans) //加法
{
    int len = 0;
    if (strlen(x.str) > strlen(y.str)) len = strlen(x.str);
    else len = strlen(y.str);//找出位数最大值
    for (int i = 0; i < len; i++)
    {
        ans->a[i] += x.a[i] + y.a[i];
        while (ans->a[i] >= 10)
        {
            ans->a[i] -= 10;
            ans->a[i + 1]++;
        }
    }
}

void minus(struct hp x, struct hp y, struct hp* ans)//减法
{
    int len = strlen(x.str);
    for (int i = 0; i < len; i++)
    {
        ans->a[i] += x.a[i] - y.a[i];
        while (ans->a[i] < 0)
        {
            ans->a[i] += 10;
            ans->a[i - 1]--;
        }
    }
}

void multi(struct hp x, struct hp y, struct hp* ans)
{
    int len1 = strlen(x.str);
    int len2 = strlen(y.str);
    struct hp A[LEN];
    for (int i = 0; i < len2; i++)
    {
        int n = y.a[i];
    }
}

void show(struct hp ans)//输出
{
    int j = LEN - 1;
    while (ans.a[j] == 0 && j >= 1) j--;
    while (j >= 0)
    {
        printf("%d", ans.a[j]);
        j--;
    }
    printf("\n");
}

int main()
{
    return 0;
}*/