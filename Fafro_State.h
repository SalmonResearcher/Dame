#pragma once

class Fafro;

//ファフロッキーのステート基底クラス
class Fafro_State
{
public:
	//更新
	virtual void Update(Fafro* _pFafro) {};
	
	//ステートごとの処理
	virtual void Process(Fafro* _pfafro) {};

	//ステートの変更（now or prevで迷ってる）
	void ChangeState(Fafro_State* now, Fafro_State* next);
};

