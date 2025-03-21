#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 内部定数
#define D_SIZE_MAX		205										// 最大サイズ

// 内部変数
static FILE *szpFpI;											// 入力
static int siW, siH;											// 幅・高さ
static int si2Mass[D_SIZE_MAX][D_SIZE_MAX];						// マス
static int si3Cnt[D_SIZE_MAX][D_SIZE_MAX][D_SIZE_MAX * 2];		// 個数[行][列][距離]

// 内部変数 - テスト用
#ifdef D_TEST
	static int siRes;
	static FILE *szpFpA;
	static int siTNo;
#endif

// １行出力
int
fOutLine(
	char *pcpLine				// <I> １行
)
{
	char lc1Buf[1024];

#ifdef D_TEST
	lc1Buf[0] = '\0';
	fgets(lc1Buf, sizeof(lc1Buf), szpFpA);
	if (strcmp(lc1Buf, pcpLine)) {
		siRes = -1;
	}
#else
	printf("%s", pcpLine);
#endif

	return 0;
}

// 最大値 - 取得
int
fGetMax(
	int piVal1					// <I> 値１
	, int piVal2				// <I> 値２
)
{
	if (piVal1 > piVal2) {
		return piVal1;
	}
	else {
		return piVal2;
	}
}

// 右下移動
int
fMove(
	int *pipRow					// <IO> 行
	, int *pipCol				// <IO> 列
)
{
	// 右上移動
	(*pipRow)--;
	(*pipCol)++;

	// マス外
	if (*pipRow < 0) {
		return -1;
	}
	if (*pipCol >= siW) {
		return -1;
	}

	return 0;
}

// 加算個数 - 取得
int
fGetAdd(
	int piRow					// <I> 行
	, int piCol					// <I> 列
	, int piRow2				// <I> 行２
	, int piCol2				// <I> 列２
)
{
	int liAdd = si2Mass[piRow][piCol];
	if (piRow == piRow2) {
		if (piCol == piCol2) {
			return liAdd;
		}
	}
	liAdd += si2Mass[piRow2][piCol2];

	return liAdd;
}

// 実行メイン
int
fMain(
)
{
	int i, j, liRet;
	char lc1Buf[1024];

	// データ - 初期化
	memset(si3Cnt, 0, sizeof(si3Cnt));

	// 幅・高さ - 取得
	fgets(lc1Buf, sizeof(lc1Buf), szpFpI);
	sscanf(lc1Buf, "%d%d", &siH, &siW);

	// マス - 取得
	for (i = 0; i < siH; i++) {
		for (j = 0; j < siW; j++) {
			fscanf(szpFpI, "%d", &si2Mass[i][j]);
		}
		fgets(lc1Buf, sizeof(lc1Buf), szpFpI);
	}

	// 個数 - 初期値
	si3Cnt[0][0][0] = si2Mass[0][0];

	// 移動回数でループ
	for (i = 0; i < siW + siH - 2; i++) {

		// １人目の位置でループ
		int liRow, liCol;
		if (i < siH) {
			liRow = i;
			liCol = 0;
		}
		else {
			liRow = siH - 1;
			liCol = i - liRow;
		}
		while (1) {

			// ２人目の位置でループ
			int liRow2 = liRow;
			int liCol2 = liCol;
			for (j = 0; ; j++) {

				// 下・下
				int liAdd = fGetAdd(liRow + 1, liCol, liRow2 + 1, liCol2);
				si3Cnt[liRow + 1][liCol][j] = fGetMax(si3Cnt[liRow + 1][liCol][j], si3Cnt[liRow][liCol][j] + liAdd);

				// 下・右
				liAdd = fGetAdd(liRow + 1, liCol, liRow2, liCol2 + 1);
				si3Cnt[liRow + 1][liCol][j + 1] = fGetMax(si3Cnt[liRow + 1][liCol][j + 1], si3Cnt[liRow][liCol][j] + liAdd);

				// 右・下
				if (j > 0) {
					liAdd = fGetAdd(liRow, liCol + 1, liRow2 + 1, liCol2);
					si3Cnt[liRow][liCol + 1][j - 1] = fGetMax(si3Cnt[liRow][liCol + 1][j - 1], si3Cnt[liRow][liCol][j] + liAdd);
				}

				// 右・右
				liAdd = fGetAdd(liRow, liCol + 1, liRow2, liCol2 + 1);
				si3Cnt[liRow][liCol + 1][j] = fGetMax(si3Cnt[liRow][liCol + 1][j], si3Cnt[liRow][liCol][j] + liAdd);

				// 次の位置
				liRet = fMove(&liRow2, &liCol2);
				if (liRet != 0) {
					break;
				}
			}

			// 次の位置
			liRet = fMove(&liRow, &liCol);
			if (liRet != 0) {
				break;
			}
		}
	}

	return si3Cnt[siH - 1][siW - 1][0];
}

// １回実行
int
fOne(
)
{
	int liRet;
	char lc1Buf[1024];

	// 入力 - セット
#ifdef D_TEST
	sprintf(lc1Buf, ".\\Test\\T%d.txt", siTNo);
	szpFpI = fopen(lc1Buf, "r");
	sprintf(lc1Buf, ".\\Test\\A%d.txt", siTNo);
	szpFpA = fopen(lc1Buf, "r");
	siRes = 0;
#else
	szpFpI = stdin;
#endif

	// 実行メイン
	liRet = fMain();

	// 出力
	sprintf(lc1Buf, "%d\n", liRet);
	fOutLine(lc1Buf);

	// 残データ有無
#ifdef D_TEST
	lc1Buf[0] = '\0';
	fgets(lc1Buf, sizeof(lc1Buf), szpFpA);
	if (strcmp(lc1Buf, "")) {
		siRes = -1;
	}
#endif

	// テストファイルクローズ
#ifdef D_TEST
	fclose(szpFpI);
	fclose(szpFpA);
#endif

	// テスト結果
#ifdef D_TEST
	if (siRes == 0) {
		printf("OK %d\n", siTNo);
	}
	else {
		printf("NG %d\n", siTNo);
	}
#endif

	return 0;
}

// プログラム開始
int
main()
{

#ifdef D_TEST
	int i;
	for (i = D_TEST_SNO; i <= D_TEST_ENO; i++) {
		siTNo = i;
		fOne();
	}
#else
	fOne();
#endif

	return 0;
}

