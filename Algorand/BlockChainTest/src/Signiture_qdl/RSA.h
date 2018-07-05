#ifndef RSA_H_
#define RSA_H_

#include "BigInteger.h"
#include <cstring>
#include <ctime>
#include <fstream>

class RSA{
	public:
		BigInteger N,E; // 公钥
		
		RSA() {}
		RSA( const unsigned Len ){
			Initialize( Len );
		}

		~RSA(){}
		
		void Initialize( const unsigned Len );
    void Initialize(std::ifstream& fin);

		BigInteger PublicEncrypt( const BigInteger& );
		BigInteger PublicDecrypt( const BigInteger& );
		
		BigInteger PrivateEncrypt( const BigInteger& );
		BigInteger PrivateDecrypt( const BigInteger& );
		BigInteger P,Q; //
		BigInteger D; // 
		BigInteger Euler; // 
		
		BigInteger RandomOddNum( unsigned );
		bool IsPrime( const BigInteger &, unsigned );
		BigInteger RandomSmaller(const BigInteger &);// 随机创建一个更小的数
		BigInteger RandomPrime( unsigned, const unsigned);// 生成一个大素数,参数为其长度
		void GetExponent(const BigInteger &);// 根据提供的欧拉数生成公钥、私钥指数
};

#endif