#include "Global.h"
namespace Global
{
	int killcount;
	int jewel;
	int jewelKill;

	int score;

	const float MUSIC_VOLUME = 0.06f;
	const float SE_VOLUME = 0.1f;

	void SetKillCount(int count) { killcount = count; }
	void AddKillCount(int count) {killcount += count;}
	int GetKillCount() { return killcount; }

	void AddJewel(int count) { jewel += count; }
	int GetJewel() { return jewel; }

	void AddJewelKill(int count) { jewelKill += count; }
	int GetJewelKill() { return jewelKill; }

	void SetScore(int count) { score = count; };
}