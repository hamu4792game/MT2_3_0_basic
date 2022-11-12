#pragma once

struct Vec2 {
	float x;
	float y;
};

struct Matrix3x3
{
	float m[3][3];
};

//	積
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

//	拡縮行列の作成関数
Matrix3x3 MakeScaleMatrix(Vec2 scale);

//	回転行列の作成関数
Matrix3x3 MakeRotateMatrix(float theta);

//	平行移動行列の作成関数
Matrix3x3 MakeTranslateMatrix(Vec2 translate);

//	二次元ベクトルを同次座標として変換する
Vec2 Transform(Vec2 vector, Matrix3x3 matrix);

//	座標変換
Vec2 Change(Vec2 pos);

//
static const int kRowHeight = 20;
static const int kColumnWidth = 50;

//	行列の描画
void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix);

//	ベクトルの描画
void VectorScreenPrintf(int x, int y, Vec2 vector);
