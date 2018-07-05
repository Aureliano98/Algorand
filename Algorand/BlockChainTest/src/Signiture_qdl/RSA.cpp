#include "RSA.h"

const BigInteger ZERO( 0 );
const BigInteger ONE(1);
const BigInteger TWO(2);

void RSA::Initialize( unsigned len )
{
	srand((unsigned)time(NULL));
    // 产生大素数p和q
    P = RandomPrime(len, 5);// 出错概率为(1/4)^6
    Q = RandomPrime(len, 5);
    // 计算出n
    N = P*Q;
	// 计算出n的欧拉函数
    Euler = (P-ONE)*(Q-ONE);
    // 设置加解密指数e和d
    GetExponent(Euler);
}

void RSA::Initialize(std::ifstream& fin)
{
  std::string buffer;
  std::getline(fin, buffer);
  P = BigInteger(buffer);
  std::getline(fin, buffer);
  Q = BigInteger(buffer);
  // 计算出n
  N = P * Q;
  // 计算出n的欧拉函数
  Euler = (P - ONE)*(Q - ONE);
  // 设置加解密指数e和d
  GetExponent(Euler);
  

}
void RSA::GetExponent( const BigInteger& Eul )
{
	BigInteger PDD(65537);
    E = PDD;
    D = ModInverse( E, Eul );
}

BigInteger RSA::PublicEncrypt(const BigInteger & m) {
    return ModPow( m, E, N );
}

/**
 * 函数功能:使用私钥进行解密
 * 参数含义:c表示要解密的密文
 */
BigInteger RSA::PrivateDecrypt(const BigInteger & c) {
    return ModPow( c, D, N );
}

/**
 * 函数功能:使用私钥进行加密
 * 参数含义:m表示要加密的明文
 */
BigInteger RSA::PrivateEncrypt(const BigInteger & m) {
    return PrivateDecrypt(m);
}

/**
 * 函数功能:使用公钥进行解密
 * 参数含义:c表示要解密的密文
 */
BigInteger RSA::PublicDecrypt(const BigInteger & c) {
    return PublicEncrypt(c);
}

BigInteger RSA::RandomOddNum( unsigned Len )
{
	if( !Len ) return BigInteger(1);
	std::string ch;
	ch.clear();
	for( int i = 0; i < Len; ++i )
	{
		int t = rand()%2; char cc;
		if( t ) cc = '1'; else cc = '0';
		ch = ch + cc;
	}
	return BigInteger(ch);
}

BigInteger RSA::RandomSmaller( const BigInteger& val )
{
	unsigned t = 0;
	do{
		t = rand();
	}while( t == 0 );
	
	BigInteger Mod( t );
	BigInteger ans = Mod.MOD( val );
	if( ans == ZERO ) ans = val - ONE;
	return ans;
}

BigInteger RSA::RandomPrime( unsigned len, const unsigned kd )
{
	BigInteger ans = RandomOddNum(len);
	int tot = 0;
	while( !IsPrime( ans, kd ) )
	{		
		ans = ans + TWO,tot ++;
		if( tot == 500 ) ans = RandomOddNum(len), tot = 0;
	}
	return ans;
}

bool RSA::IsPrime( const BigInteger& NUM, const unsigned kd )
{
	if ( NUM == ONE ) return false;    // 1不是素数
    if ( NUM == TWO ) return true;    // 2是素数

    BigInteger t = NUM-ONE;
    BigInteger::Bit B(t);// 二进制数
    if ( B.IS1(0) == 1 ) return false; // 减一之后为奇数,原数为偶数
     // num-1 = 2^s*d
     size_t s = 0;    // 统计二进制末尾有几个0
     BigInteger d; d = t;
     for ( size_t i = 0; i < B.size(); ++i ) {
         if (!B.IS1(i)) {
             ++s;
             d.ShiftRight(1);// 计算出d
         }
         else
             break;
     }
 
     for ( size_t i = 0; i < kd; ++i ) {// 测试k次
         BigInteger a = RandomSmaller( NUM );// 生成一个介于[1,num-1]之间的随机数a
         BigInteger x = ModPow( a, d, NUM );
         if ( x == ONE )// 可能为素数
             continue;
         bool ok = true;
         // 测试所有0<=j<s,a^(2^j*d) mod num != -1
         for (size_t j=0; j<s && ok; ++j) {
             if (x == t)
                 ok = false;    // 有一个相等,可能为素数
             x = x*x; x = x.MOD(NUM);
         }
         if (ok)    // 确实都不等,一定为合数
             return false;
     }
     return true;    // 通过所有测试,可能为素数
}