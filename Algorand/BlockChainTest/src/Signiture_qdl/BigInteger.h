#ifndef BigInteger_H_
#define BigInteger_H_

#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>

typedef unsigned long long ULL;
typedef unsigned base_t;

class BigInteger{ // 大整数相关计算
	
	public:
		BigInteger():is_negative(false) {
			Num.clear(); Num.push_back( 0 );
		}
		BigInteger( ULL x )
		{
			Zhuan( x );
		}
		
		
		void Zhuan( ULL x );  //把一个 long long 类型的数转成 BigInteger 型
		void ShiftLeft( int x ); // 左移 x 位
		void ShiftRight( int x ); // 右移 x 位
		void ClearZero();        // 去除高位多余的 0
		BigInteger DivideAndMod( const BigInteger& x, BigInteger& m ); // 整除，顺便余 
		BigInteger abs() const;
		int compareto( const BigInteger& val ) const;
		std::string IntoBinaryS() const;
		
		BigInteger( const std::string& HashValue ); // 由一个 256 位 01 二进制串转化为 Sys 进制的串，且高位在后，低位在前		
		friend BigInteger operator + (const BigInteger &aa, const BigInteger &bb ); // 加法
		friend BigInteger operator - (const BigInteger &aa, const BigInteger &bb ); // 减法，默认大数减小数
		friend BigInteger operator * (const BigInteger &aa, const BigInteger &bb ); // 乘法
		friend BigInteger operator / (BigInteger val, const BigInteger &b ); // 除法，整除
		friend bool operator < ( const BigInteger &a, const BigInteger &b );      // 重载小于符号
		friend bool operator > ( const BigInteger &a, const BigInteger &b );      // 重载大于符号
		friend bool operator == ( const BigInteger &a , const BigInteger &b );    // 重载等于符号
		friend BigInteger ModPow( const BigInteger &a, const BigInteger &ex, const BigInteger &m ); // 蒙哥马利幂模
		friend BigInteger ModInverse( const BigInteger &x, const BigInteger &m );
		//friend void Swap( BigInteger &a, BigInteger &b );
		BigInteger MOD( const BigInteger& MO ); // 取模运算
		void TestOut() const; // 输出
		~BigInteger(){};
		
	private:		
		bool is_negative;   // 1 负 0 正
		std::vector<base_t> Num;   // 大整数每一位
//		const static ULL Sys = 10ll; // 进制
		const static int Sys_M = 5; // 2^5 = 32
		const static int Sys_Bit = 32;
		const static ULL Sys = (1LL<<32);
		const static int Sys_MO = 0x1f; // 用来求 % 32
		const static int Sys_Big = 0xffffffff; // 2^32 -1 ,用来截取高位或者低位

		class Bit{
			public: 
				Bit( const BigInteger& BI )  // 把大整数转为 binary
				{
					Bit_Vec = BI.Num;
					BLen = BI.Num.size() << Sys_M;
					base_t Tmp = BI.Num[BI.Num.size()-1];
					base_t High_Bit = 1 << (Sys_Bit-1);
					
					if( Tmp == 0 ) BLen -= Sys_Bit;
						else {
							while( !(Tmp&High_Bit) )
							{
								--BLen;
								High_Bit >>= 1;
							}
						}							
				}
				
				bool IS1( int i ) // 判断第 i 位是否为 1
				{
					size_t t = i>>Sys_M;
					size_t pos = i&Sys_MO;
					base_t tt = Bit_Vec[t];
					return ( tt & (1<<pos) );
				}
				
				int size() {
					return BLen;
				}
			private:
				size_t BLen;
				std::vector <base_t> Bit_Vec;
		};
	friend class RSA;
};

#endif