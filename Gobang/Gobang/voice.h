/************************************************************************

    function:该文件主要实现声音采集
    author:Demon
    Time:2017/10/15

************************************************************************/

#pragma once
#include<windows.h>
#include<iostream>
#include<Mmsystem.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;
#define BUFFSIZE   1024*10
/*
主要API
waveInOpen
waveInPrepareHeader
waveOutOpen
waveOutPrepareHeader

*/

class voice
{
public:
	voice();
	~voice();
	
	void  WaveInitFormat(LPWAVEFORMATEX m_WaveFormat, WORD nCh, DWORD nSampleRate, WORD BitsPerSample);
	static DWORD CALLBACK MicCallback(HWAVEIN hwavein, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
	void Start();
protected:



private:
	
	WAVEFORMATEX Out_waveform;
	WAVEFORMATEX In_waveform;

	HWAVEOUT m_hWaveOut;
	HWAVEIN  m_hWaveIn;

	WAVEHDR lpOutWaveHdr;
	WAVEHDR lpInWaveHdr[2];

	char *In_Buf1, *In_Buf2;
	char *Out_Buf;


	


};