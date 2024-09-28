#pragma once
#include <string>

//-----------------------------------------------------------
//�T�E���h���Ǘ�����iXAudio�g�p�j
//-----------------------------------------------------------
namespace Audio
{
	//������
	void Initialize();

	//�T�E���h�t�@�C��(.wav�j�����[�h
	//���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�
	//�����FfileName	�t�@�C����
	//�����FisLoop		���[�v�Đ����������Ȃ�true
	//�����FsvNum�@		�����ɖ炷�ő吔�i�ȗ��j
	//�ߒl�F���̃f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName, bool isLoop = false, int svNum = 1);

	//�킩��ɂ��������̂�summary���g�p
	/// <summary>
	/// �Đ�
	/// </summary>
	/// <param name="ID">�T�E���h�̔ԍ�</param>
	/// <param name="forceRestart">�Đ��֐����Ă΂�邽�тɃT�E���h���Đ����Ȃ����H</param>
	/// <param name="pitch">���̍���</param>
	/// <param name="volume">����</param>
	void Play(int ID, bool forceRestart = false, float pitch = 1.0f, float volume = 1.0f);

	//��~
	//�����Fhandle	�~�߂����T�E���h�̔ԍ�
	void Stop(int ID);

	//�s�b�`����
	void SetPitch(int ID, float pitch);

	//�V�[�����Ƃ̉���i���[�h�����T�E���h������j
	void Release();

	//�{�̂����
	void AllRelease();
};
