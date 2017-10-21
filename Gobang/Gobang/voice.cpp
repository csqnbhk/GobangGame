#include"voice.h"

DWORD CALLBACK voice::MicCallback(HWAVEIN hwavein, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{  
	voice*pVoice = (voice*)dwInstance;
	switch (uMsg)
	{
	case WIM_OPEN:
		cout << "设备已经打开.." << endl;
		break;

	case WIM_DATA:
	{
		cout << "缓冲区%d存满..." << ((LPWAVEHDR)dwParam1)->dwUser << endl;
		memcpy(pVoice->Out_Buf, ((LPWAVEHDR)dwParam1)->lpData, BUFFSIZE);
		waveOutWrite(pVoice->m_hWaveOut, &pVoice->lpOutWaveHdr, sizeof(WAVEHDR));
		waveInAddBuffer(hwavein, (LPWAVEHDR)dwParam1, sizeof(WAVEHDR));
		break;
	}
	case WIM_CLOSE:
		cout << "设备已经关闭..." << endl;
		break;
	default:
		break;
	}
	return 0;
}


voice::voice()
{

	this->In_Buf1 = new char[BUFFSIZE];
	this->In_Buf2 = new char[BUFFSIZE];
	this->Out_Buf = new char[BUFFSIZE];

}
voice::~voice()
{
	delete[] this->In_Buf1;
	delete[] this->In_Buf2;
	delete[] this->Out_Buf;

}
void voice::RecordVoiceStart()
{

	this->WaveInitFormat(&this->Out_waveform, 1, 8000, 8);
	MMRESULT mmResult = waveOutOpen(&this->m_hWaveOut, WAVE_MAPPER, &this->Out_waveform, 0, NULL, CALLBACK_NULL);
	if (mmResult == MMSYSERR_NOERROR)
	{

		this->lpOutWaveHdr.lpData = this->Out_Buf;
		this->lpOutWaveHdr.dwBufferLength = BUFFSIZE;
		this->lpOutWaveHdr.dwUser = 1;
		this->lpOutWaveHdr.dwFlags = 0;
		mmResult = waveOutPrepareHeader(this->m_hWaveOut, &this->lpOutWaveHdr, sizeof(WAVEHDR));
		if (mmResult == MMSYSERR_NOERROR)
		{
			cout << "播放缓冲区准备成功" << endl;
		}
	}

	this->WaveInitFormat(&this->In_waveform, 1, 8000, 8);
	mmResult = waveInOpen(&this->m_hWaveIn, WAVE_MAPPER, &this->In_waveform, (DWORD)&MicCallback,(DWORD)this, CALLBACK_FUNCTION);
	if (mmResult == MMSYSERR_NOERROR)
	{

		this->lpInWaveHdr[0].lpData = this->In_Buf1;
		this->lpInWaveHdr[0].dwBufferLength = BUFFSIZE;
		this->lpInWaveHdr[0].dwUser = 1;
		this->lpInWaveHdr[0].dwFlags = 0;
		mmResult = waveInPrepareHeader(this->m_hWaveIn, &this->lpInWaveHdr[0], sizeof(WAVEHDR));
		if (mmResult == MMSYSERR_NOERROR)
		{
			cout << "录音缓冲区1准备成功" << endl;
		}

		this->lpInWaveHdr[1].lpData = this->In_Buf2;
		this->lpInWaveHdr[1].dwBufferLength = BUFFSIZE;
		this->lpInWaveHdr[1].dwUser = 2;
		this->lpInWaveHdr[1].dwFlags = 0;
		mmResult = waveInPrepareHeader(this->m_hWaveIn, &this->lpInWaveHdr[1], sizeof(WAVEHDR));
		if (mmResult == MMSYSERR_NOERROR)
		{
			cout << "录音缓冲区2准备成功" << endl;
		}

		mmResult = waveInAddBuffer(this->m_hWaveIn, &this->lpInWaveHdr[0], sizeof(WAVEHDR));
		if (mmResult == MMSYSERR_NOERROR)
		{
			cout << "录音缓冲区1加入录音设备" << endl;
		}
		mmResult = waveInAddBuffer(this->m_hWaveIn, &this->lpInWaveHdr[1], sizeof(WAVEHDR));
		if (mmResult == MMSYSERR_NOERROR)
		{
			cout << "录音缓冲区2加入录音设备" << endl;
		}

		mmResult=waveInStart(this->m_hWaveIn);
		if (mmResult == MMSYSERR_NOERROR)
		{
			cout << "录音开始" << endl;
		}


	}
	
	

}
void voice::WaveInitFormat(LPWAVEFORMATEX m_WaveFormat, WORD nCh, DWORD nSampleRate, WORD BitsPerSample)
{
	m_WaveFormat->wFormatTag = WAVE_FORMAT_PCM;
	m_WaveFormat->nChannels = nCh;
	m_WaveFormat->nSamplesPerSec = nSampleRate;
	m_WaveFormat->nAvgBytesPerSec = nSampleRate * nCh * BitsPerSample / 8;
	m_WaveFormat->nBlockAlign = m_WaveFormat->nChannels * BitsPerSample / 8;
	m_WaveFormat->wBitsPerSample = BitsPerSample;
	m_WaveFormat->cbSize = 0;

}

