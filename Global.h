#pragma once
namespace Global
{
	extern int killcount;
	extern int jewel;
	extern int jewelKill;


	void SetKillCount(int count);
	void AddKillCount(int count);
	int GetKillCount();

	void AddJewel(int count);
	int GetJewel();

	void AddJewelKill(int count);
	int GetJewelKill();

	void SetScore(int count);
}