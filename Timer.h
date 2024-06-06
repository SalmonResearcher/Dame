#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



class Timer :public GameObject
{
private:
	Text* num;

	int frame;
	bool active;
	int drawX;
	int drawY;


public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Timer(GameObject* parent);

	~Timer();


	//������
	void Initialize() override; 

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	void Draw(int _x, int _y,int _timer);

	void Draw(int _x, int _y);

	//�J��
	void Release() override;

	void SetLimit(float seconds);

	void Start();

	void Stop();

	bool IsFinished();

};