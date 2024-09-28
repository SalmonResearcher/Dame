#pragma once
namespace Global
{
	extern int killcount;
	extern int jewel;
	extern int jewelKill;
	extern const float MUSIC_VOLUME;
	extern const float SE_VOLUME;

	extern int jewelScore;
	extern int killScore;



	void SetKillCount(int count);
	void AddKillCount(int count);
	int GetKillCount();

	void AddJewel(int count);
	int GetJewel();

	void AddJewelKill(int count);
	int GetJewelKill();

	void SetScore(int count);

	void SetJewelScore(int baseScore);
	void SetKillScore(int baseScore);

	int GetJewelScore();
	int GetKillScore();
}