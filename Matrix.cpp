#include "Matrix.h"
#include <assert.h>
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

//	アフィン変換行列の作成関数 (SRT)
Matrix3x3 MakeAffineMatrix(Vec2 scale, float rotate, Vec2 translate) {
	rotate *= M_PI / 180.0f;
	Matrix3x3 result;
	//	初期化
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			result.m[y][x] = 0.0f;
		}
	}
	//	代入
	result.m[0][0] = scale.x * cosf(rotate);
	result.m[0][1] = scale.x * sinf(rotate);
	result.m[1][0] = scale.y * -sinf(rotate);
	result.m[1][1] = scale.y * cosf(rotate);
	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1.0f;

	return result;
}


//	二次元ベクトルを同次座標として変換する
Vec2 Transform(Vec2 vector, Matrix3x3 matrix) {
	Vec2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0);
	result.x /= w;
	result.y /= w;
	return result;
}

//	座標変換
Vec2 Change(Vec2 pos) {
	pos.y = pos.y * -1 + 500;
	return pos;
}


//	行列の描画
void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix) {
	for (int row = 0; row < 3; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight,
				"%.02f", matrix.m[row][column]);
		}
	}
}

//	ベクトルの描画
void VectorScreenPrintf(int x, int y, Vec2 vector) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
}
