#ifndef SignatureBasedOnRSA_H_
#define SignatureBasedOnRSA_H_

#include <cstring>
#include <cmath>
#include <fstream>
#include "RSA.h"
#include "BigInteger.h"

/*
class SignatureBasedOnRSA{
	
	public:
		SignatureBasedOnRSA() {
			rsa.Initialize( 128 );
		}
		BigInteger Sign( const std::string& HashValue ); //签名
		// 传入一个 256 位二进制字符串，在其中转化为了一个（1<<32）进制的大整数，经过私钥加密
		// 密文也为一个大整数，转化为 256 位 BinaryString传出。
		
		
		void GetKey( BigInteger& N, BigInteger& E, BigInteger& D );
		//通过 N，E，两个参数，将公钥传出， 解密需要两个整数。
		
		bool Vertify( const std::string& HashValue, const BigInteger& CODE, const BigInteger& N, const BigInteger&E  );
		//原文为 HashValue， 格式同上， CODE 即密文， 格式同 HashValue， 然后用公钥解密 CODE， 看解出值是否与 HashValue 一致。
		RSA rsa;
		
		BigInteger EncryptWith( const string& HashValue, const BigInteger& N, const BigInteger& D );
		BigInteger DecryptWith( const BigInteger& CODE, const BigInteger& N, const BigInteger&E  );
		void ComputeKey( int p, int q, BigInteger& N, BigInteger& E, BigInteger& D );
};
*/
namespace SignatureBasedOnRSA {
  RSA rsa;

  void InitKey(std::ifstream& fin) {
    rsa.Initialize(fin);
  }
  BigInteger Sign(const std::string& HashValue); //签名
  // 传入一个 256 位二进制字符串，在其中转化为了一个（1<<32）进制的大整数，经过私钥加密
  // 密文也为一个大整数，转化为 256 位 BinaryString传出。


  void GetKey(BigInteger& N, BigInteger& E, BigInteger& D);
  //通过 N，E，两个参数，将公钥传出， 解密需要两个整数。
  //N 是 mod, E是公钥，D是私钥

  bool Vertify(const std::string& HashValue, const BigInteger& CODE, const BigInteger& N, const BigInteger&E);
  //原文为 HashValue， 格式同上， CODE 即密文， 格式同 HashValue， 然后用公钥解密 CODE， 看解出值是否与 HashValue 一致。
  

  BigInteger EncryptWith(const std::string& HashValue, const BigInteger& N, const BigInteger& D);
  BigInteger DecryptWith(const BigInteger& CODE, const BigInteger& N, const BigInteger&E);
  //void ComputeKey(int p, int q, BigInteger& N, BigInteger& E, BigInteger& D);
};
#endif