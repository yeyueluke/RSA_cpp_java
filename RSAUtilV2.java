import java.util.Scanner; //键盘扫描类
public class RSAUtilV2 
{
    static class Rsa
    {
        //公开&&私有密钥中的n
        private int n;
        //公开密钥中的e
        private int e;
        //私有密钥中的d；
        private int d;
        //密文C
        private long c[] = new long[100];
        //明文M
        private int m[] = new int [100];
        Scanner input = new Scanner(System.in);
        
        //设置公开密钥与私有密钥
        public void sheZhiMY()
        {
            System.out.println("请输入两个素数p与q，系统将自动生成公开密钥与私有密钥");
            int p=173;//input.nextInt();
            int q=773;//input.nextInt();
            //生成n
            this.n = p*q;
            //生成e
            for(int i=2;i<(q-1)*(p-1);i++)
            {
                int g = Match.maxDivisor(i,(q-1)*(p-1));
                if(g==1)
                {
                    this.e = i;
                    break;
                }
            }
            //私有密钥生成
            for(int i=1; ;i++)
            {
                int temp = (int)Match.ramainder(this.e*i,(q-1)*(p-1));
                if(temp==1)
                {
                    this.d=i;
                    break;
                }
            }
            System.out.println("公有密钥为("+this.e+","+this.n+");私有密钥为（"+this.d+","+this.n+").");
        }
        
        public int BianaryTransform(int num, int bin_num[])
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
        public long  Modular_Exonentiation(long  a, int b, int n)
        {
        	  int c = 0;
        	  int bin_num[] = new int[1000];
        	  long d = 1;
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
        //加密
        public void jiaMi()
        {
            System.out.println("请输入要加密的明文");
            for(int i = 0; i < 100; i++)
                this.m[i] = (i + 'a') % 255;//input.nextInt();
            for(int i = 0; i < 100; i++)
                //this.c[i] = Match.ramainder((long)Math.pow( this.m[i], this.e),this.n);
            	this.c[i] = Modular_Exonentiation(m[i], e, n);
            for(int i = 0; i < 100; i++)
            {
            	if( i % 16 == 0)
            		System.out.println("");
            	System.out.print(" "+this.c[i]);
            	
            }
        }
        //解密
        public void jieMi(){
            System.out.println("请输入要解密的密文");
            //this.c = input.nextInt();
            for(int i = 0; i < 100; i++)
            	//溢出Math.pow(this.c[i],this.d)
                //this.m[i] = (int)Match.ramainder((long)Math.pow(this.c[i],this.d),this.n);
            	this.m[i] = (int)Modular_Exonentiation(c[i], d, n);
            for(int i = 0; i < 100; i++)
            {
            	if( i % 16 == 0)
            		System.out.println("");
            	System.out.print(" "+ this.m[i]);
        
            }
        }
    }
    //求余数和最大公约数的数学工具
    static class Match
    {
        //求最大公约数
        public static int maxDivisor(int a, int b){
            int n = a;
            int m = b;
            int r = 0;
            while(m != 0)
            {
                r = n%m;
                n = m;
                m = r;
            }
            return n;
        }
        //求余
        public static long ramainder(long dividend, int dividor) 
        {
        	  long a = dividend / dividor;
        	  long b = a * dividor;
            return dividend - dividend / dividor * dividor;
        }
    }

    public static void main(String[] args) 
    {
        Rsa rsa = new Rsa();
        System.out.println("java double max value="+ Double.MAX_VALUE);
        System.out.println("java long max value="+ Long.MAX_VALUE);
        rsa.sheZhiMY();
        rsa.jiaMi();
        rsa.jieMi();
    }
}
