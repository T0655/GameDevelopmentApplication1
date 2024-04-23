#pragma once

/*
��Βl�ɕϊ�
���� �����̐������Βl�ɕϊ�����e���v���[�g
���� T value �ϊ�����l
�߂�l T �ϊ���̒l
*/
template<typename T>
T Abs(T value)
{
	T result;

	if (value > 0)
	{
		//value�����̒l
		result = value;
	}
	else
	{
		//value�����̒l
		result = -value;
	}

	return result;
}

/*
�ő�l��Ԃ��e���v���[�g�̊֐�
�����@�����Ŏw�肳�ꂽ��̒l�̍ő�l��Ԃ�
�����@T a �v�Z�p�f�[�^�@T b �v�Z�p�f�[�^
�߂�l�@T�@�ő�l
*/
template <typename T>
T Max(T a, T b)
{
	T result;

	//�l���傫������result�ɐݒ�
	if (a < b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}

/*
�ŏ��l��Ԃ��e���v���[�g�̊֐�
�����@�����Ŏw�肳�ꂽ��̒l�̍ŏ��l��Ԃ�
�����@T a �v�Z�p�f�[�^�@T b �v�Z�p�f�[�^
�߂�l�@T�@�ő�l
*/
template <typename T>
T Min(T a, T b)
{
	T result;

	//�l������������result�ɐݒ�
	if (a > b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}
