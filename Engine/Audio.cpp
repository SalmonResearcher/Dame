#include <xaudio2.h>
#include <vector>
#include "Audio.h"

#define SAFE_DELETE_ARRAY(p) if(p){delete[] p; p = nullptr;}

#define SAFE_DELETE_ARRAY(p) if(p){delete[] p; p = nullptr;}

namespace Audio
{
    IXAudio2* pXAudio = nullptr;
    IXAudio2MasteringVoice* pMasteringVoice = nullptr;

    struct AudioData
    {
        XAUDIO2_BUFFER buf = {};
        IXAudio2SourceVoice** pSourceVoice = nullptr;
        int svNum;
        std::string fileName;
    };
    std::vector<AudioData> audioDatas;
}

void Audio::Initialize()
{
    CoInitializeEx(0, COINIT_MULTITHREADED);
    XAudio2Create(&pXAudio);
    pXAudio->CreateMasteringVoice(&pMasteringVoice);
}

int Audio::Load(std::string fileName, bool isLoop, int svNum)
{
    for (int i = 0; i < audioDatas.size(); i++)
    {
        if (audioDatas[i].fileName == fileName)
        {
            return i;
        }
    }

    struct Chunk
    {
        char id[5] = "";
        unsigned int size = 0;
    };

    HANDLE hFile;
    hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD dwBytes = 0;

    Chunk riffChunk = { 0 };
    ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL);
    ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL);

    char wave[4] = "";
    ReadFile(hFile, &wave, 4, &dwBytes, NULL);

    Chunk formatChunk = { 0 };
    while (formatChunk.id[0] != 'f') {
        ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL);
    }
    ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL);

    WAVEFORMATEX fmt;
    ReadFile(hFile, &fmt.wFormatTag, 2, &dwBytes, NULL);
    ReadFile(hFile, &fmt.nChannels, 2, &dwBytes, NULL);
    ReadFile(hFile, &fmt.nSamplesPerSec, 4, &dwBytes, NULL);
    ReadFile(hFile, &fmt.nAvgBytesPerSec, 4, &dwBytes, NULL);
    ReadFile(hFile, &fmt.nBlockAlign, 2, &dwBytes, NULL);
    ReadFile(hFile, &fmt.wBitsPerSample, 2, &dwBytes, NULL);

    Chunk data = { 0 };
    while (true)
    {
        ReadFile(hFile, &data.id, 4, &dwBytes, NULL);
        if (strcmp(data.id, "data") == 0)
            break;
        else
        {
            ReadFile(hFile, &data.size, 4, &dwBytes, NULL);
            char* pBuffer = new char[data.size];
            ReadFile(hFile, pBuffer, data.size, &dwBytes, NULL);
        }
    }

    ReadFile(hFile, &data.size, 4, &dwBytes, NULL);
    char* pBuffer = new char[data.size];
    ReadFile(hFile, pBuffer, data.size, &dwBytes, NULL);
    CloseHandle(hFile);

    AudioData ad;
    ad.fileName = fileName;
    ad.buf.pAudioData = (BYTE*)pBuffer;
    ad.buf.Flags = XAUDIO2_END_OF_STREAM;
    if (isLoop) ad.buf.LoopCount = XAUDIO2_LOOP_INFINITE;
    ad.buf.AudioBytes = data.size;
    ad.pSourceVoice = new IXAudio2SourceVoice * [svNum];

    for (int i = 0; i < svNum; i++)
    {
        pXAudio->CreateSourceVoice(&ad.pSourceVoice[i], &fmt);
    }
    ad.svNum = svNum;
    audioDatas.push_back(ad);

    return (int)audioDatas.size() - 1;
}

void Audio::Play(int ID, bool forceRestart, float pitch, float volume)
{
    for (int i = 0; i < audioDatas[ID].svNum; i++)
    {
        XAUDIO2_VOICE_STATE state;
        audioDatas[ID].pSourceVoice[i]->GetState(&state);

        if (forceRestart || state.BuffersQueued == 0)
        {
            if (state.BuffersQueued > 0)
            {
                audioDatas[ID].pSourceVoice[i]->Stop();
                audioDatas[ID].pSourceVoice[i]->FlushSourceBuffers();
            }

            audioDatas[ID].pSourceVoice[i]->SubmitSourceBuffer(&audioDatas[ID].buf);
            audioDatas[ID].pSourceVoice[i]->Start();
            audioDatas[ID].pSourceVoice[i]->SetFrequencyRatio(pitch);
            audioDatas[ID].pSourceVoice[i]->SetVolume(volume);
            break;
        }
    }
}
void Audio::Stop(int ID)
{
    for (int i = 0; i < audioDatas[ID].svNum; i++)
    {
        audioDatas[ID].pSourceVoice[i]->Stop();
        audioDatas[ID].pSourceVoice[i]->FlushSourceBuffers();
    }
}

void Audio::SetPitch(int ID, float pitch)
{
    for (int i = 0; i < audioDatas[ID].svNum; i++)
    {
        audioDatas[ID].pSourceVoice[i]->SetFrequencyRatio(pitch);
    }
}

void Audio::Release()
{
    for (int i = 0; i < audioDatas.size(); i++)
    {
        for (int j = 0; j < audioDatas[i].svNum; j++)
        {
            audioDatas[i].pSourceVoice[j]->DestroyVoice();
        }
        SAFE_DELETE_ARRAY(audioDatas[i].buf.pAudioData);
    }
    audioDatas.clear();
}

void Audio::AllRelease()
{
    CoUninitialize();
    if (pMasteringVoice)
    {
        pMasteringVoice->DestroyVoice();
    }
    pXAudio->Release();
}