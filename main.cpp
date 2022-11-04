#include <Novice.h>
#include "Matrix.h"

const char *kWindowTitle = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// ライブラリの初期化
	int kWindowWidth = 1280, kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	float theta = 0.1f;

	struct Object
	{
		Vec2 centerPos;
		Vec2 size;
		Vec2 LT;
		Vec2 RT;
		Vec2 LB;
		Vec2 RB;
	};
	Object object{
		{400,100},
		{200,100},
		{100,50},
		{300,50},
		{100,150},
		{300,150},
	};

	int block = Novice::LoadTexture("white1x1.png");

	//	行列の作成
	Matrix3x3 rotateMatrix = MakeRotateMatrix(theta);
	Matrix3x3 translateMatrix = MakeTranslateMatrix(object.centerPos);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_D])
		{
			object.centerPos.x += 10;
		}
		if (keys[DIK_A])
		{
			object.centerPos.x -= 10;
		}

		//	行列の作成
		Matrix3x3 rotateMatrix = MakeRotateMatrix(theta);
		Matrix3x3 translateMatrix = MakeTranslateMatrix(object.centerPos);

		Matrix3x3 worldMatrix = Multiply(rotateMatrix, translateMatrix);


		Vec2 worldLeftTop		= Transform(object.LT, worldMatrix);
		Vec2 worldRightTop		= Transform(object.RT, worldMatrix);
		Vec2 worldLeftBottom	= Transform(object.LB, worldMatrix);
		Vec2 worldRightBottom	= Transform(object.RB, worldMatrix);


		

		worldLeftTop.x += object.centerPos.x;
		worldLeftTop.y += object.centerPos.y;


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Vec2 screenLeftTop		= Change(worldLeftTop);
		Vec2 screenRightTop		= Change(worldRightTop);
		Vec2 screenLeftBottom	= Change(worldLeftBottom);
		Vec2 screenRightBottom	= Change(worldRightBottom);


		Novice::DrawQuad(screenLeftTop.x, screenLeftTop.y,
			screenRightTop.x, screenRightTop.y,
			screenLeftBottom.x, screenLeftBottom.y,
			screenRightBottom.x, screenRightBottom.y,
			0, 0, 1, 1, block, 0xffffffff);


		Novice::ScreenPrintf(0, 0, "%02f", object.centerPos.x);
		Novice::ScreenPrintf(100, 0, "%02f", object.centerPos.y);
		Novice::ScreenPrintf(0, 20, "%f", screenLeftTop);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
