#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;

int Plaintext[100];//明文
long long Ciphertext[100];//密文
int n, e = 0, d;

//二进制转换
int BianaryTransform(int num, int bin_num[])
{
	int i = 0, mod = 0;

	//转换为二进制，逆向暂存temp[]数组中
	while (num != 0)
	{
		mod = num % 2;
		bin_num[i] = mod;
		num = num / 2;
		i++;
	}

	//返回二进制数的位数
	return i;
}

//反复平方求幂
long long Modular_Exonentiation(long long a, int b, int n)
{
	int c = 0, bin_num[1000];
	long long d = 1;
	int k = BianaryTransform(b, bin_num) - 1;

	for (int i = k; i >= 0; i--)
	{
		c = 2 * c;
		d = (d * d) % n;
		if (bin_num[i] == 1)
		{
			c = c + 1;
			d = (d * a) % n;
		}
	}
	return d;
}
#define NN  100000000
//生成1000以内素数
int ProducePrimeNumber(int prime[])
{
	int c = 0;
	int *vis = new int[NN + 1];
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i <= NN; i++)
	{
		if (!vis[i])
		{
			prime[c++] = i;
			for (int j = i*i; j <= NN; j += i)
				vis[j] = 1;
		}
	}
	
	return c;
}

//欧几里得扩展算法
int Exgcd(int m, int n, int &x)
{
	int x1, y1, x0, y0, y;
	x0 = 1; y0 = 0;
	x1 = 0; y1 = 1;
	x = 0; y = 1;
	int r = m % n;
	int q = (m - r) / n;
	while (r)
	{
		x = x0 - q * x1; 
		y = y0 - q * y1;
		x0 = x1; 
		y0 = y1;
		x1 = x; 
		y1 = y;
		m = n; 
		n = r; 
		r = m % n;
		q = (m - r) / n;
	}
	return n;
}

int maxDivisor(int a, int b)
{
	int n = a;
	int m = b;
	int r = 0;
	while (m != 0){
		r = n % m;
		n = m;
		m = r;
	}
	return n;
}
long long ramainder(long long dividend, int dividor) 
{
	long long a = dividend / dividor;
	return dividend - dividend / dividor * dividor;
}
//RSA初始化
void RSA_Initialize()
{

	clock_t start, end;
	//取出1000内素数保存在prime[]数组中
	int *prime = new int[NN];
	start = clock();

	int count_Prime = ProducePrimeNumber(prime);
	end = clock() - start;
	printf("用时%lf毫秒\n", (double)end);
	/*for (int i = 0; i < count_Prime; i++)
	{
		if (i % 16 == 0)
			cout << endl;
		cout << prime[i] << "  ";
	}
	*/
	cout << endl;
	//随机取两个素数p,q
	srand((unsigned)time(NULL));
	int ranNum1 = rand() % count_Prime;
	int ranNum2 = rand() % count_Prime;
	int p = 173;// prime[ranNum1], 
	int q = 773;// prime[ranNum2];
	cout << "p " << p << " q " << q << endl;
	n = p*q;

	int On = (p - 1)*(q - 1);

#if 0
	//用欧几里德扩展算法求e,d
	for (int j = 3; j < On; j += 1331)//固定数不合适，仅适用于<1000 的情况
	{
		int gcd = Exgcd(j, On, d);
		if (gcd == 1 && d > 0)
		{
			e = j;
			break;
		}

	}
#endif
#if 1
	for (int i = 2; i< On; i++)
	{
		int g = maxDivisor(i, On);
		if (g == 1)
		{
			e = i;
			break;
		}
	}
	//私有密钥生成
	for (int i = 1;; i++)
	{
		int temp = ramainder(e * i, On);
		if (temp == 1)
		{
			d = i;
			break;
		}
	}
#endif
}

//RSA加密
void RSA_Encrypt()
{
	cout << "Public Key (e, n) : e = " << e << " n = " << n << '\n';
	cout << "Private Key (d, n) : d = " << d << " n = " << n << '\n' << '\n';

	int i = 0;
	for (i = 0; i < 100; i++)
		Ciphertext[i] = Modular_Exonentiation(Plaintext[i], e, n);
		//Ciphertext[i] = ramainder(Plaintext[i], e);

	cout << "Use the public key (e, n) to encrypt:" << '\n';
	for (i = 0; i < 100; i++)
	{
		if (i % 16 == 0)
			cout << endl;
		cout << Ciphertext[i] << " ";
		
	}
	cout << '\n' << '\n';
}

//RSA解密
void RSA_Decrypt()
{
	int i = 0;
	for (i = 0; i < 100; i++)
		Ciphertext[i] = Modular_Exonentiation(Ciphertext[i], d, n);
		//Ciphertext[i] = ramainder(pow(Ciphertext[i],d), n);
	cout << "Use private key (d, n) to decrypt:" << '\n';
	for (i = 0; i < 100; i++)
	{
		if (i % 16 == 0)
			cout << endl;
		cout << Ciphertext[i] << " ";
		
	}
	cout << '\n' << '\n';
}


//算法初始化
void Initialize()
{
	int i;
	srand((unsigned)time(NULL));
	for (i = 0; i < 100; i++)
		//	Plaintext[i] = rand() % 1000;
		Plaintext[i] = (i + 'a') % 255;
	

	cout << "Generate 100 random numbers:" << '\n';
	for (i = 0; i < 100; i++)
	{
		if (i % 16 == 0)
			cout << endl;
		cout << Plaintext[i] << " ";
	}
	cout << '\n' << '\n';
}

int main()
{
	Initialize();

	while (!e)
		RSA_Initialize();

	RSA_Encrypt();

	RSA_Decrypt();
	system("Pause");
	return 0;
}
