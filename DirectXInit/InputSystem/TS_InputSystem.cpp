#include "TS_InputSystem.h"

namespace TS {
	TS_InputSystem* TS_InputSystem::GetInstance()
	{
		// �C���X�^���X���Ȃ���΃C���X�^���𐶐�
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

		// �O��̃L�[�ۑ�
		memcpy(prevKayState, curtKayState, sizeof(prevKayState));

		// ���݂̃L�[�擾
		for (int i = 0; i < 256;++i) {
			curtKayState[i] = GetAsyncKeyState(i);
		}

		if (GetTrigger(MK_LEFT)) {
			GetCursorPos(&clickPosition);
			ScreenToClient(GetActiveWindow(), &clickPosition); // �N���C�A���g���W�ɕϊ�
		}
		if (GetRelease(MK_LEFT)) {
			// ���݂̃}�E�X�J�[�\���ʒu���擾
			GetCursorPos(&releasePosition);
			ScreenToClient(GetActiveWindow(), &releasePosition); // �N���C�A���g���W�ɕϊ�
		}

	}

	void TS_InputSystem::Uninit()
	{
	}


	bool TS_InputSystem::GetTrigger(int _keyNumber) {

		// �r�b�g�}�X�N���g���ē��͂����
		// �ŏ�ʃr�b�g��������Ă��邩�̔���
		// 0�Ȃ牟����Ă��Ȃ��̂�false
		// 0�ȊO�Ȃ牟����Ă���̂�true�ƂȂ�

		// �O�̓��͂�������Ă��Ȃ���
		bool isPrevNotPressd = (prevKayState[_keyNumber] & 0x8000) == 0;

		// ���̓��͂�������Ă��鎞
		bool isCurtPressd = (curtKayState[_keyNumber] & 0x8000) != 0;


		return isPrevNotPressd && isCurtPressd;
	}

	bool TS_InputSystem::GetRelease(int _keyNumber) {

		// �O�̓��͂�������Ă��鎞
		bool isPrevPressd = (prevKayState[_keyNumber] & 0x8000) != 0;

		// ���̓��͂�������Ă��Ȃ���
		bool isCurtNotPressd = (curtKayState[_keyNumber] & 0x8000) == 0;


		return isPrevPressd && isCurtNotPressd;
	}

	bool TS_InputSystem::GetPress(int _keyNumber) {
		// �O�̓��͂�������Ă��鎞
		bool isPrevPressd = (prevKayState[_keyNumber] & 0x8000) != 0;

		// ���̓��͂�������Ă��鎞
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