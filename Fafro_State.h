#pragma once

class Fafro;

//ファフロッキーのステート基底クラス
class Fafro_State
{
public:
	//更新
	void Update(Fafro* _pFafro) {};
	
	//ステートごとの処理
	void Process(Fafro* _pFafro) {};

	//ステートの変更
	void ChangeState(Fafro_State* prev, Fafro_State* next);
};

