#pragma once

#define D_KEYCODE_MAX (256) //�L�[�{�[�h�̑���

class InputControl
{
private:
	//���݂̓��͏��
	static char now_key[D_KEYCODE_MAX];

	//�O�t���[���̓��͏��
	static char old_key[D_KEYCODE_MAX];

public:
	//�X�V����
	static void Update();

	//�L�[�����������Ă���Ƃ�
	static bool GetKey(int key_code);

	//�L�[���������u��
	static bool GetKeyDown(int key_code);

	//�L�[�𗣂����u��
	static bool GetKeyUp(int key_code);

private:
	//�L�[�z��͈̓`�F�b�N
	static bool CheckKeyCodeRange(int key_code);
};


