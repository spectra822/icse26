#include <stdio.h>

typedef unsigned int	U32;
typedef unsigned char	U08;

#define INPUT_NUM_MIN	1							/* 入力値の範囲下限 */
#define INPUT_NUM_MAX	1000000000					/* 入力値の範囲上限 */

static U32 CalcGcd_U32(U32 u32_large_num, U32 u32_small_num);



/***********************************************************************************
 ++module <main>
 ++outline
	メイン関数
 ++arguments
	<>	<u32_return_val>	[戻り値]
 ++supp
	<戻り値>
		0：正常終了
		1：異常終了
	<引数>
		なし
	<補足説明>
		なし
 ++end_module
************************************************************************************/
int main(void)
{
													/* 入力値1 */
	U32 u32_x   = 0;								/* 変数定義 */
	U32 u32_y   = 0;								/* 入力値2 */
	U32 u32_gcd = 0;								/* 最大公約数(Greatest Common Divisor) */
	U08 u08_return_val = (U08)0;					/* 戻り値 */
	
	scanf("%d %d", &u32_x, &u32_y);					/* 数値入力 */
	
	if( (u32_x < INPUT_NUM_MIN) || (INPUT_NUM_MAX < u32_x)
		|| (u32_y < INPUT_NUM_MIN) || (INPUT_NUM_MAX < u32_y) )		/* 入力値が範囲外だった場合 */
	{
		u08_return_val = (U08)1;					/* 戻り値に1を設定 */
	}
	else
	{
		if(u32_x > u32_y)							/* 1つ目の入力値の方が大きかった場合 */
		{
			u32_gcd = CalcGcd_U32(u32_x, u32_y);	/* 最大公約数の計算 */
		}
		else
		{
			u32_gcd = CalcGcd_U32(u32_y, u32_x);	/* 最大公約数の計算 */
		}
		
		printf("%d\n", u32_gcd);					/* 最大公約数の表示 */
	}
	
	return u08_return_val;
}



/***********************************************************************************
 ++module <CalcGcd_U32>
 ++outline
	2つの自然数の最大公約数を計算する関数
 ++arguments
	<>	<>				[最大公約数]
	<>	<u32_large_num>	[大きい方の自然数]
	<>	<u32_small_num>	[小さい方の自然数]
 ++supp
	<戻り値>
		最大公約数
	<引数>
		u32_large_num：大きい方の自然数
		u32_small_num：小さい方の自然数
	<補足説明>
		ヒントによると、「x>yの場合、xとyの最大公約数は、yとx%yの最大公約数と一致する」らしい
		→ x%yの結果がゼロになるまでxにyの値を、yにx%yの結果を格納し続け、
		   x%yの結果がゼロになった時のyが最大公約数
 ++end_module
************************************************************************************/
static U32 CalcGcd_U32(U32 u32_large_num, U32 u32_small_num)
{
														/* u32_large_num % u32_small_numの結果を保持する変数 */
	U32 u32_rem = 0;									/* 変数定義 */
	
	while(1)											/* u32_large_num % u32_small_numの結果がゼロではない間ループ */
	{
		if(0 == u32_small_num)							/* 除数がゼロの場合 */
		{
			break;
		}
		else
		{
			u32_rem = u32_large_num % u32_small_num;	/* u32_large_num % u32_small_numを計算 */
			
			if(0 == u32_rem)							/* u32_large_num % u32_small_numの結果がゼロの場合 */
			{
				break;
			}
			else
			{
				u32_large_num = u32_small_num;			/* u32_large_numを更新 */
				u32_small_num = u32_rem;				/* u32_small_numを更新 */
			}
		}
	}
	
	return u32_small_num;
}

