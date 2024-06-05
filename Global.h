#pragma once
namespace Global
{
	extern int killcount;
	extern int jewel;
	extern int jewelKill;

	void SetKillCount(int count);
	void AddKillCount(int count);
	int GetKillCount();

	void SetJewel(int count);
	int GetJewel();

	void SetJewelKill(int count);
	int GetJewelKill();

}