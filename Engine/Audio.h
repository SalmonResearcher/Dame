#pragma once
#include <string>

//-----------------------------------------------------------
//サウンドを管理する（XAudio使用）
//-----------------------------------------------------------
namespace Audio
{
	//初期化
	void Initialize();

	//サウンドファイル(.wav）をロード
	//すでに同じ名前のファイルをロード済みの場合は、既存のデータの番号を返す
	//引数：fileName	ファイル名
	//引数：isLoop		ループ再生させたいならtrue
	//引数：svNum　		同時に鳴らす最大数（省略可）
	//戻値：そのデータに割り当てられた番号
	int Load(std::string fileName, bool isLoop = false, int svNum = 1);

	//わかりにくかったのでsummaryを使用
	/// <summary>
	/// 再生
	/// </summary>
	/// <param name="ID">サウンドの番号</param>
	/// <param name="forceRestart">再生関数が呼ばれるたびにサウンドを再生しなおす？</param>
	/// <param name="pitch">音の高さ</param>
	/// <param name="volume">音量</param>
	void Play(int ID, bool forceRestart = false, float pitch = 1.0f, float volume = 1.0f);

	//停止
	//引数：handle	止めたいサウンドの番号
	void Stop(int ID);

	//ピッチ調整
	void SetPitch(int ID, float pitch);

	//シーンごとの解放（ロードしたサウンドを解放）
	void Release();

	//本体も解放
	void AllRelease();
};
