#pragma once
#include<iostream>
#include<Windows.h>

//===================================================
// キーコード
// @{
//===================================================

// キーボード
// @{
#define KB_A 0x41	// A
#define KB_B 0x42	// B
#define KB_C 0x43	// C
#define KB_D 0x44	// D
#define KB_E 0x45	// E
#define KB_F 0x46	// F
#define KB_G 0x47	// G
#define KB_H 0x48	// H
#define KB_I 0x49	// I
#define KB_J 0x4A	// J
#define KB_K 0x4B	// K
#define KB_L 0x4C	// L
#define KB_N 0x4D	// N
#define KB_M 0x4E	// M
#define KB_O 0x4F	// O
#define KB_P 0x50	// P
#define KB_Q 0x51	// Q
#define KB_R 0x52	// R
#define KB_S 0x53	// S
#define KB_T 0x54	// T
#define KB_U 0x55	// U
#define KB_V 0x56	// V
#define KB_W 0x57	// W
#define KB_X 0x58	// X
#define KB_Y 0x59	// Y
#define KB_Z 0x5A	// Z
// @}


// 数字キー
// @{
#define KB_0 0X30	// 0
#define KB_1 0X31	// 1
#define KB_2 0X32	// 2
#define KB_3 0X33	// 3
#define KB_4 0X34	// 4
#define KB_5 0X35	// 5
#define KB_6 0X36	// 6
#define KB_7 0X37	// 7
#define KB_8 0X38	// 8
#define KB_9 0X39	// 9
// @}


// ファンクションキー
// @{
#define KB_F1	VK_F1	// F1
#define KB_F2	VK_F2	// F2
#define KB_F3	VK_F3	// F3
#define KB_F4	VK_F4	// F4
#define KB_F5	VK_F5	// F5
#define KB_F6	VK_F6	// F6
#define KB_F7	VK_F7	// F7
#define KB_F8	VK_F8	// F8
#define KB_F9	VK_F9	// F9
#define KB_F10	VK_F10	// F10
#define KB_F11	VK_F11	// F11
#define KB_F12	VK_F12	// F12
// @}


// 矢印キー
// @{
#define KB_LEFT		VK_LEFT		// 左(←)矢印キー
#define KB_UP		VK_UP		// 上(↑)矢印キー
#define KB_RIGHT	VK_RIGHT	// 右(→)矢印キー
#define KB_DOWN		VK_DOWN		// 下(↓)矢印キー
// @}


// 特殊キー
// @{
#define KB_ESC		VK_ESCAPE	// ESCキー
#define KB_SPC		VK_SPACE	// スペース
#define KB_ENT		VK_RETURN	// エンター
#define KB_BACK		VK_BACK		// バックスペース
#define KB_TAB		VK_TAB		// Tabキー
#define KB_SFT		VK_SHIFT	// シフト
#define KB_CTRL		VK_CONTROL	// コントロール
#define KB_ALT		VK_MENU		// オルト
#define KB_CLO		VK_CAPITAL	// Caps Lock
#define KB_NLO		VK_NUMLOCK	// Num Lock
#define KB_SLO		VK_SCROLL	// Scroll Lock
#define KB_PAUSE	VK_PAUSE	// ポーズ/ブレイク
#define KB_PSC		VK_SNAPSHOT	// ポイントスクリーン
// @}


//	テンキー
// @{
#define NP_0	VK_NUMPAD0	// テンキー(0)
#define NP_1	VK_NUMPAD1	// テンキー(1)
#define NP_2	VK_NUMPAD2	// テンキー(2)
#define NP_3	VK_NUMPAD3	// テンキー(3)
#define NP_4	VK_NUMPAD4	// テンキー(4)
#define NP_5	VK_NUMPAD5	// テンキー(5)
#define NP_6	VK_NUMPAD6	// テンキー(6)
#define NP_7	VK_NUMPAD7	// テンキー(7)
#define NP_8	VK_NUMPAD8	// テンキー(8)
#define NP_9	VK_NUMPAD9	// テンキー(9)
// @}

#define NP_ADD	VK_ADD		// テンキー(+)
#define NP_SUB	VK_SUBTRACT	// テンキー(-)
#define NP_MUL	VK_MULTIPLY	// テンキー(*)
#define NP_DIV	VK_DIVIDE	// テンキー(/)


// マウス
// @{
#define MK_LEFT		VK_LBUTTON	// マウス左ボタン
#define MK_RIGHT	VK_RBUTTON	// マウス右ボタン
#define MK_MID		VK_MBUTTON	// マウスホイールボタン
#define MK_X1		VK_XBUTTON1	// マウスサブボタン１
#define MK_X2		VK_XBUTTON2	// マウスサブボタン２
// @}

//===================================================
// @}
//===================================================



class TS_InputSystem
{
public:
	static TS_InputSystem* GetInstance();


	void Init(bool& _isLoop);
	void Update();
	void Uninit();

	bool GetTrigger(int _keyNumber); // 押した時
	bool GetRelease(int _keyNumber); // 離した時
	bool GetPress(int _keyNumber);   // 押し続けている間


	POINT GetClickPosition() const; // 左クリックした座標を取得
	POINT GetReleasePosition() const; // 左クリックを離した座標を取得


private:
	
	// 外部からインスタンスを生成できなくする
	TS_InputSystem();
	~TS_InputSystem();
	
	POINT clickPosition; // 左クリックした位置
	POINT releasePosition; // 左クリックを離した位置
	

	// コピーコンストラクタと代入演算子も削除
	// 複数のインスタンスを防ぐ
	TS_InputSystem(const TS_InputSystem&) = delete;
	TS_InputSystem& operator=(const TS_InputSystem&) = delete;


	// 初期化フラグ
	bool isInitialized = false;

	SHORT curtKayState[256];
	SHORT prevKayState[256];
};

