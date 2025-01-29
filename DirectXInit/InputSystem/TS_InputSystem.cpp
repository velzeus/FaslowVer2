#include "TS_InputSystem.h"

namespace TS {
	TS_InputSystem* TS_InputSystem::GetInstance()
	{
		// インスタンスがなければインスタンを生成
		static TS_InputSystem instance;
		return &instance;
	}


	void TS_InputSystem::Init(bool& _isLoop)
	{
		if (isInitialized == false) {
			isInitialized = true;
			memset(curtKayState, 0, sizeof(curtKayState));
			memset(prevKayState, 0, sizeof(prevKayState));
		}
	}

	void TS_InputSystem::Update()
	{

		// 前回のキー保存
		memcpy(prevKayState, curtKayState, sizeof(prevKayState));

		// 現在のキー取得
		for (int i = 0; i < 256;++i) {
			curtKayState[i] = GetAsyncKeyState(i);
		}

		if (GetTrigger(MK_LEFT)) {
			GetCursorPos(&clickPosition);
			ScreenToClient(GetActiveWindow(), &clickPosition); // クライアント座標に変換
		}
		if (GetRelease(MK_LEFT)) {
			// 現在のマウスカーソル位置を取得
			GetCursorPos(&releasePosition);
			ScreenToClient(GetActiveWindow(), &releasePosition); // クライアント座標に変換
		}

	}

	void TS_InputSystem::Uninit()
	{
	}


	bool TS_InputSystem::GetTrigger(int _keyNumber) {

		// ビットマスクを使って入力を取る
		// 最上位ビットが押されているかの判定
		// 0なら押されていないのでfalse
		// 0以外なら押されているのでtrueとなる

		// 前の入力が押されていない時
		bool isPrevNotPressd = (prevKayState[_keyNumber] & 0x8000) == 0;

		// 今の入力が押されている時
		bool isCurtPressd = (curtKayState[_keyNumber] & 0x8000) != 0;


		return isPrevNotPressd && isCurtPressd;
	}

	bool TS_InputSystem::GetRelease(int _keyNumber) {

		// 前の入力が押されている時
		bool isPrevPressd = (prevKayState[_keyNumber] & 0x8000) != 0;

		// 今の入力が押されていない時
		bool isCurtNotPressd = (curtKayState[_keyNumber] & 0x8000) == 0;


		return isPrevPressd && isCurtNotPressd;
	}

	bool TS_InputSystem::GetPress(int _keyNumber) {
		// 前の入力が押されている時
		bool isPrevPressd = (prevKayState[_keyNumber] & 0x8000) != 0;

		// 今の入力が押されている時
		bool isCurtPressd = (curtKayState[_keyNumber] & 0x8000) != 0;
		return isPrevPressd && isCurtPressd;
	}

	POINT TS_InputSystem::GetClickPosition() const
	{
		return clickPosition;
	}

	POINT TS_InputSystem::GetReleasePosition() const
	{
		return releasePosition;
	}




	TS_InputSystem::TS_InputSystem() {
		memset(curtKayState, 0, sizeof(curtKayState));
		memset(prevKayState, 0, sizeof(prevKayState));
	}
	TS_InputSystem::~TS_InputSystem()
	{



	};
}