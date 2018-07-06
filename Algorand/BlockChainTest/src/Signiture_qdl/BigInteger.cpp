#include "BigInteger.h"

const BigInteger ZERO( 0ll ), ONE( 1ll );

BigInteger::BigInteger( const std::string& HashValue ):is_negative(false)
{
	std::string t(HashValue);
    if (t.size() && t.at(0)=='-') {
        if (t.size() > 1)
            is_negative = true;
        t = t.substr(1);
    }
    int cnt = (32-(t.size()%32))%32;// 数的长度不是32的倍数,补足0
    std::string temp;

    for (int i=0; i<cnt; ++i)
        temp.push_back('0');

    t = temp+t;

    for (size_t i=0; i<t.size(); i+=32) {
        base_t sum = 0;
        for (int j=0; j<32; ++j) {    // 32位 2 进制组成大整数的一位
            char ch = t[i+j];
			int num;
			if( ch == '1' ) num = 1; else num = 0;
            sum = ((sum<<1) | (num));
        }
        Num.push_back(sum);
    }
    std::reverse(Num.begin(), Num.end());// 高位在后
    ClearZero();// 去除高位的0
}

void BigInteger::Zhuan( ULL x )
{
	Num.clear(); 
  is_negative = x < 0; 
  //error//if( x < 0 ) x = -x;
	if( x == 0 ) {
		Num.push_back( 0 );
		return;
	}
	while( x > 0 )
	{
		Num.push_back(x % Sys);
		x /= Sys;
	}
}

std::string BigInteger::IntoBinaryS() const
{
	std::string ch1; char cc;
	ch1.clear();
	if( (*this) == ZERO ) {
		ch1 += '0';
		return ch1;
	}
	int l = Num.size();
	for( int i = 0; i < l; ++i ) {
		base_t t = Num[i]; //cout << Num[i] << endl;
		for( int j = 0; j < 32; ++j )
		{
			base_t bi = t & 1;
			if( bi ) cc = '1'; else cc = '0';
			ch1 += cc;
			t >>= 1;
		}
	}
//	cout << ch1 << endl;
	int l1 = ch1.length(); int l2 = 256 - l1;
	for( int i = 0; i < l2; ++i ) ch1 += '0';
	reverse( ch1.begin(), ch1.end());
	return ch1;
}

void BigInteger::ShiftLeft( int x ) 
{
	int nmove = (x>>Sys_M);
	int nres = x&Sys_MO;
	int nzero = nmove + (nres!=0);
	for( int i = 0; i < nzero; ++i ) Num.push_back(0);
	
	int Len = Num.size();
	if( nmove ) 
	{
		int l = Len - (nres!=0);
		for( int i = l-1; i >= nmove; -- i ) Num[i] = Num[i-nmove];
		for( int i = 0; i < nmove; ++i ) Num[i] = 0ll;
	}

	if( nres ) 
	{
		base_t t = Sys_Big;
		t <<= Sys_Bit - nres;
		
		base_t temp = 0ll; 
		for( int i = 0; i < Num.size(); ++i )
		{
			base_t tmp = Num[i];
			Num[i] = ((tmp<<nres) | temp);
			temp = (tmp&t)>>(Sys_Bit-nres);
//			cout << "Num = " << Num[i] << endl;
		}
	}
	ClearZero();
//	puts("");
//	printf("--------------");TestOut();
}

void BigInteger::ShiftRight( int x )
{
	Bit Val(*this);
	if( x >= Val.size() ) {
		Num.clear(); Num.push_back( 0 );
		return;
	}
	int nmove = x>>Sys_M;
	int nres = x&Sys_MO;
	
	int Len = Num.size();
	if( nmove )
	{
		for( int i = 0; i < nmove; ++i ) Num[i] = Num[i+nmove];
		for( int i = Len-1; i >= Len - nmove; --i ) Num[i] = 0;
		for( int i = 0; i < nmove; ++i ) Num.pop_back();
	}
	
	Len = Num.size();
	if( nres )
	{
		int t = Sys_Big;
		t >>= Sys_Bit - nres;
		
		ULL temp = 0;
		for( int i = Len-1; i >= 0; --i )
		{
			ULL tmp = Num[i];
			Num[i] = ((tmp>>nres) | temp);
			temp = (tmp&t) << (Sys_Bit-nres);
		}
	}
	ClearZero();
}

void BigInteger::ClearZero()
{
	int tot = 0,Len = Num.size();
	
	for( int i = Len-1; i >= 0; --i ) if( !Num[i] ) tot++; else break;

	if( tot == Len ) tot --;
	
	for( int i = 0; i < tot; ++i ) Num.pop_back();
	
}

void BigInteger::TestOut() const
{
	if(is_negative) std::cout <<"-"; for( int i = Num.size()-1; i>=0; --i ) std::cout<<Num[i]<<" "; puts("");
}

BigInteger BigInteger::abs() const
{
	BigInteger ans;
	ans.Num = Num;
	return ans;
}

int BigInteger::compareto( const BigInteger& val ) const
{
	if (is_negative != val.is_negative) {// 符号不同,负数必小
    if (is_negative == true) return -1;
        return 1;
    }
    int flag = 0;
    if ( Num.size() < val.Num.size() )// 位数较小
        flag = -1;
    else if ( Num.size() > val.Num.size() )// 位数较大
        flag = 1;
    else {    // 位数相等,从高位开始一一比较
        for (std::vector<base_t>::const_reverse_iterator it=Num.rbegin(), ite=val.Num.rbegin(); it!=Num.rend(); ++it, ++ite)
            if ((*it) != (*ite)) {
                flag = (*it)<(*ite) ? -1 : 1;    // 高位小,则小
                break;
            }
    }
    if (is_negative)    // 如为负数,小的反而大
        flag = -flag;
    return flag;
}

BigInteger operator + ( const BigInteger& aa, const BigInteger &bb )
{
/*	BigInteger ret,a,b;
	if( aa > bb ) a = aa, b = bb; else a = bb, b = aa; 
	int t = a.Num.size() - b.Num.size(); int Len = a.Num.size();
	
	for( int i = 0; i < t; ++i ) b.Num.push_back(0);
	
	for( int i = 0; i < Len; ++i )
	{
		ret.Num[i] += (a.Num[i] + b.Num[i]); ret.Num.push_back(0);
		if( ret.Num[i] > ret.Sys ) ret.Num[i+1] += ret.Num[i] / ret.Sys, ret.Num[i] %= ret.Sys;
	}
	
	ret.ClearZero();
	return ret;*/
    BigInteger ans,val; ans = aa; val = bb;
    if ( ans.is_negative == val.is_negative ) // 同号
	{
        int len = val.Num.size() - ans.Num.size();

        while ((len--) > 0)    // 被加数位数少,高位补0
            ans.Num.push_back(0);

        int carry = 0;    // 进位
        for ( size_t i=0; i<val.Num.size(); ++i ) 
		{
            base_t temp = ans.Num[i];
            ans.Num[i] += val.Num[i]+carry;    // 无符号数相加,超出取其余数
            // 进位:一种是有无进位都超出,一种是有进位才超出(比如十进制相加,9+9+1,得9,9+0+0,得9)
            carry = (temp > ans.Num[i] ? 1 : ( temp > (temp+val.Num[i]) ? 1 : 0) );
        }

        for (size_t i=val.Num.size(); i<ans.Num.size() && carry!=0; ++i) {// 还有进位
            base_t temp = ans.Num[i];
            ans.Num[i] += carry;
            carry = temp > ans.Num[i];
        }

        if (carry)    // 还有进位
            ans.Num.push_back(carry);
    }
    else {    // 异号
        BigInteger a = aa.abs();
        BigInteger b = val.abs();
        int flag = a.compareto(b);
        // 绝对值相等,则结果为0,否则用绝对值大的减去小的,符号随绝对值大的
        if (flag == -1) {
            ans = b - a;
            ans.is_negative = val.is_negative;
        }
        else if (flag == 0)
            ans = ZERO;
        else {
            ans = a - b;
            ans.is_negative = aa.is_negative;
        }
    }
    return ans;
}

BigInteger operator - ( const BigInteger& aa, const BigInteger& bb )
{
/*	BigInteger ret; ret.Num.clear();
	int Len = a.Num.size();
	for( int i = 0; i < Len; ++i ) ret.Num.push_back( a.Num[i] - b.Num[i] );
	for( int i = 0; i < Len; ++i ) if( ret.Num[i] < 0 ) ret.Num[i+1] -= 1, ret.Num[i] += a.Sys;
	ret.ClearZero();
	return ret;*/
    BigInteger ans,val; ans = aa; val = bb;
    BigInteger a = aa.abs();
    BigInteger b = val.abs();
    if (ans.is_negative == val.is_negative) {// 同号
        int flag = a.compareto(b);
        if (flag == 1) {// a的绝对值大于b的绝对值,直接减
            int borrow = 0;    // 借位
            // 大数减小数
            for (size_t i=0; i<val.Num.size(); ++i) {
                base_t temp = ans.Num[i];
                ans.Num[i] -= val.Num[i]+borrow;
                // 借位:一种是有无借位都超出,另一种是有借位才超出(比如十进制相减,9-0-0,得9,9-9-1,得9)
                borrow = temp<ans.Num[i] ? 1 : (temp-borrow<val.Num[i] ? 1 : 0);
            }
            for (size_t i=val.Num.size(); i<ans.Num.size() && borrow!=0; ++i) {// 还有借位
                base_t temp = ans.Num[i];
                ans.Num[i] -= borrow;
                borrow = temp < (base_t)borrow;
            }
            ans.ClearZero();// 去掉高位多余的0
        }
        else if (flag == 0)
            ans = ZERO;
        else {// a的绝对值小于b的绝对值
            ans = b - a;
            ans.is_negative = !aa.is_negative;
        }
    }
    else {    // 异号
        ans = a + b;    // 转换为加法
        ans.is_negative = aa.is_negative;
    }
    return ans;
}

BigInteger operator * ( const BigInteger& aa, const BigInteger& bb )
{
/*	BigInteger ret;
	ret.Len = a.Len + b.Len;
	for( int i = 1; i <= a.Len; ++i )
		for( int j = 1; j <= b.Len; ++j ) 
		{
			ret.Num[i+j-1] += a.Num[i] * b.Num[j];
		}
		
	for( int i = 1; i <= ret.Len; ++i ) 
		if( ret.Num[i] > ret.Sys ) ret.Num[i+1] += ret.Num[i]/ ret.Sys, ret.Num[i] %= ret.Sys;
	while( !ret.Num[ret.Len] ) ret.Len --;
	return ret;*/
	BigInteger ret,a,b;
	if( aa > bb ) a = aa, b = bb; else a = bb, b = aa;
	
	BigInteger::Bit t( b ); int l = t.size();
	for( int i = l-1; i >= 0; --i ) 
	if( t.IS1( i ) )
	{
		BigInteger tmp = a;
		tmp.ShiftLeft( i );
//		tmp.TestOut(); cout<<""<<endl;
//		ret.TestOut(); tmp.TestOut();
		ret = ret + tmp;
//		ret.TestOut(); cout <<""<<endl<<""<<endl;
	}
	ret.is_negative = !(a.is_negative == b.is_negative);
	return ret;
}

BigInteger operator / ( BigInteger a, const BigInteger &b )
{
	BigInteger tmp;
	BigInteger ret = a.DivideAndMod( b, tmp );
	return ret;
}

BigInteger BigInteger::MOD( const BigInteger &MO )
{
	BigInteger ret;
	DivideAndMod( MO, ret );
	if( ret.is_negative ) ret = ret + MO;
	return ret;
}

BigInteger BigInteger::DivideAndMod( const BigInteger& val, BigInteger& m )
{
    BigInteger a = abs();
    BigInteger b = val.abs();
    int flag = a.compareto(b);
    if (flag == 0)// 绝对值相等
        return (is_negative==val.is_negative) ? BigInteger(1) : BigInteger(-1);
    if (flag == -1) {
        m = *this;
        return ZERO;
    }
    BigInteger ans;

    Bit Bit_b(b);
    // 位数对齐
    while (true) {// a的绝对值大于b的绝对值
        Bit Bit_a(a);
        int len = Bit_a.size()-Bit_b.size();
        BigInteger temp;
        // 找到移位
        while (len >= 0) {
			temp = b;
            temp.ShiftLeft(len);
            if (temp.compareto(a) != 1)// 找到最大的左移位数使得当前的a大于等于b
                break;
            --len;
        }
        if (len < 0)    // 当前的a小于b了
            break;
        base_t tot = 0;
        while (temp.compareto(a) != 1) {
            a = a - temp;
            ++tot;    // 统计当前的a最多大于等于几个移位后的b
        }
        temp = BigInteger(tot);
        if (len) temp.ShiftLeft(len);// 移位后表明当前的a是b的几倍
        ans = ans + temp;
    }
    ans.is_negative = !(is_negative==val.is_negative);
    m.Num = a.Num;
    m.is_negative = is_negative;
    return ans;
}	

BigInteger ModPow( const BigInteger &a, const BigInteger &ex, const BigInteger &m )
{
	BigInteger ret; ret.Zhuan(1ll);
	BigInteger::Bit t( ex ); int l = t.size();
	
	for( int i = l-1; i >= 0; --i )
	{
		ret = ret * ret; ret = ret.MOD( m );
		if( t.IS1(i) ) ret = ret * a, ret = ret.MOD( m );
	}
	return ret;
}

BigInteger ModInverse( const BigInteger &x, const BigInteger &m )
{
    BigInteger a[3], b[3], t[3];
    // 以下进行初等变换
    a[0] = 0; a[1] = 1; a[2] = x;
    b[0] = 1; b[1] = 0; b[2] = m;

    for (t[2]=a[2].MOD(b[2]); !(t[2] == ZERO); t[2]=a[2].MOD(b[2])) {
        BigInteger temp = a[2]/b[2],Mul;
        for (int i=0; i<3; ++i) {
			Mul = temp * b[i];
            t[i] = a[i] - Mul;// 不超过一次a[2]-temp*b[2]就变为大数减小数
            a[i] = b[i];
            b[i] = t[i];
        }
    }
    if ( b[2] == ONE ) {// 最大公约数为1,存在乘法逆元
        if ( b[1].is_negative )// 逆元为负数
            b[1] = b[1] + m;// 变为正数,使其在m的剩余集中
        return b[1];
    }
    return ZERO;// 最大公约数不为1,无乘法逆元
}

bool operator > ( const BigInteger &a, const BigInteger &b )
{
	return a.compareto(b) == 1;
}

bool operator < ( const BigInteger &a, const BigInteger &b )
{
	return a.compareto(b) == -1;
}

bool operator == ( const BigInteger &a , const BigInteger &b )
{
	return a.compareto(b) == 0;
}