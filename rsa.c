#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Key {
    int n;
    int e;
    int d;
    int c;
    int m;
} Key;

int modularPower(int base, int exponent, int mod)
{
    if(mod == 1)
    {
        return 0;
    }
    int c = 1;
    int i;
    for (i = 1; i <= exponent; i++)
    {
        c = (c * base) % mod;
    }
    return c;
}
int gcd(int a, int b)
{
    int t;
    while (b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int makePrime()
{
    while(1)
    {
        int num = rand() % 100;
        if (isPrime(num))
        {
            return num;
        }
    }
}

int findE(int _i)
{
    int a = 3;
    while (1)
    {
        if (gcd(a, _i) == 1)
        {
            return a;
        }
        a += 2;
    }
}

int findD(int _i, int e)
{
    double a = (double) _i;
    double b = (double) e;
    double d;
    int temp;
    double d2;
    double k = 1;
    while (1)
    {
        d = (k * a + 1)/b;
        int temp = (int) d;
        double d2 = (double) temp;
        if (d2 == d)
        {
            return temp;
        }
        k += 1;
    }
}

int isPrime(int n)
{
    if (n <= 1)
    {
        return 0;
    }
    else if (n <= 3)
    {
        return 1;
    }
    else if (n % 2 == 0 || n % 3 == 0)
    {
        return 0;
    }
    int i = 5;
    while ((i*i) <= n)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return 0;
        }
        i += 6;
    }
    return 1;
}

Key keyCreation(int p, int q)
{
    int _i, k, temp;
    struct Key key;
    key.n = p * q;
    _i = (p - 1)*(q - 1);
    key.e = findE(_i);
    key.d = findD(_i, key.e);
    
    return key;
    
}

Key encrypt(int n, int m, int e)
{
    struct Key key1;
    key1.c = modularPower(m, e, n);
    return key1;
}

Key decrypt(int n, int c, int d)
{
    struct Key key2;
    key2.m = modularPower(c, d, n);
    return key2;
}

int main()
{
    struct Key a;
    struct Key b;
    struct Key c;
    
    int m, p, q;
    srand(time(NULL));
    
    printf("%s", "Please enter m: ");
    scanf("%d", &m);
    
    p = makePrime();
    q = makePrime();
    
    printf("The values of p and q are %d and %d respectively\n", p, q);
    a = keyCreation(p, q);
    printf("The values of n, e, and d are %d, %d, and %d respectively\n", a.n, a.e, a.d);
    b = encrypt(a.n, m, a.e);
    printf("The value of c is %d\n", b.c);
    c = decrypt(a.n, b.c, a.d);
    printf("The resultant decryption of m is: %d", c.m);
    
    return 0;
}