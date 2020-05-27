//-----------------------------------------------------------------------------
// File: WavRead.cpp
//
// Desc: Wave file support for loading and playing Wave files using DirectSound 
//       buffers.
//
// Copyright (c) 1999 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#include <windows.h>
#include"../KdLibrary/MyLibrary.h"

//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

//-----------------------------------------------------------------------------
// Name: ReadMMIO()
// Desc: Support function for reading from a multimedia I/O stream
//-----------------------------------------------------------------------------
HRESULT ReadMMIO(HMMIO hmmioIn, MMCKINFO* pckInRIFF, WAVEFORMATEX** ppwfxInfo)
{
	MMCKINFO        ckIn;           // chunk info. for general use.
	PCMWAVEFORMAT   pcmWaveFormat;  // Temp PCM structure to load in.       

	*ppwfxInfo = NULL;

	if ((0 != mmioDescend(hmmioIn, pckInRIFF, NULL, 0)))
		return E_FAIL;

	if ((pckInRIFF->ckid != FOURCC_RIFF) ||
		(pckInRIFF->fccType != mmioFOURCC('W', 'A', 'V', 'E')))
		return E_FAIL;

	// Search the input file for for the 'fmt ' chunk.
	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (0 != mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK))
		return E_FAIL;

	// Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
	// if there are extra parameters at the end, we'll ignore them
	if (ckIn.cksize < (LONG)sizeof(PCMWAVEFORMAT))
		return E_FAIL;

	// Read the 'fmt ' chunk into <pcmWaveFormat>.
	if (mmioRead(hmmioIn, (HPSTR)&pcmWaveFormat,
		sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
		return E_FAIL;

	// Allocate the waveformatex, but if its not pcm format, read the next
	// word, and thats how many extra bytes to allocate.
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		if (NULL == (*ppwfxInfo = new WAVEFORMATEX))
			return E_FAIL;

		// Copy the bytes from the pcm structure to the waveformatex structure
		memcpy(*ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
		(*ppwfxInfo)->cbSize = 0;
	}
	else
	{
		// Read in length of extra bytes.
		WORD cbExtraBytes = 0L;
		if (mmioRead(hmmioIn, (CHAR*)&cbExtraBytes, sizeof(WORD)) != sizeof(WORD))
			return E_FAIL;

		*ppwfxInfo = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX) + cbExtraBytes];
		if (NULL == *ppwfxInfo)
			return E_FAIL;

		// Copy the bytes from the pcm structure to the waveformatex structure
		memcpy(*ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
		(*ppwfxInfo)->cbSize = cbExtraBytes;

		// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
		if (mmioRead(hmmioIn, (CHAR*)(((BYTE*)&((*ppwfxInfo)->cbSize)) + sizeof(WORD)),
			cbExtraBytes) != cbExtraBytes)
		{
			delete* ppwfxInfo;
			*ppwfxInfo = NULL;
			return E_FAIL;
		}
	}

	// Ascend the input file out of the 'fmt ' chunk.
	if (0 != mmioAscend(hmmioIn, &ckIn, 0))
	{
		delete* ppwfxInfo;
		*ppwfxInfo = NULL;
		return E_FAIL;
	}

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: WaveOpenFile()
// Desc: This function will open a wave input file and prepare it for reading,
//       so the data can be easily read with WaveReadFile. Returns 0 if
//       successful, the error code if not.
//-----------------------------------------------------------------------------
HRESULT WaveOpenFile(CHAR* strFileName, HMMIO* phmmioIn, WAVEFORMATEX** ppwfxInfo,
	MMCKINFO* pckInRIFF)
{
	HRESULT hr;
	HMMIO   hmmioIn = NULL;

	if (NULL == (hmmioIn = mmioOpen(strFileName, NULL, MMIO_ALLOCBUF | MMIO_READ)))
		return E_FAIL;

	if (FAILED(hr = ReadMMIO(hmmioIn, pckInRIFF, ppwfxInfo)))
	{
		mmioClose(hmmioIn, 0);
		return hr;
	}

	*phmmioIn = hmmioIn;

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: WaveStartDataRead()
// Desc: Routine has to be called before WaveReadFile as it searches for the
//       chunk to descend into for reading, that is, the 'data' chunk.  For
//       simplicity, this used to be in the open routine, but was taken out and
//       moved to a separate routine so there was more control on the chunks
//       that are before the data chunk, such as 'fact', etc...
//-----------------------------------------------------------------------------
HRESULT WaveStartDataRead(HMMIO* phmmioIn, MMCKINFO* pckIn,
	MMCKINFO* pckInRIFF)
{
	// Seek to the data
	if (-1 == mmioSeek(*phmmioIn, pckInRIFF->dwDataOffset + sizeof(FOURCC),
		SEEK_SET))
		return E_FAIL;

	// Search the input file for for the 'data' chunk.
	pckIn->ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (0 != mmioDescend(*phmmioIn, pckIn, pckInRIFF, MMIO_FINDCHUNK))
		return E_FAIL;

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: WaveReadFile()
// Desc: Reads wave data from the wave file. Make sure we're descended into
//       the data chunk before calling this function.
//          hmmioIn      - Handle to mmio.
//          cbRead       - # of bytes to read.   
//          pbDest       - Destination buffer to put bytes.
//          cbActualRead - # of bytes actually read.
//-----------------------------------------------------------------------------
HRESULT WaveReadFile(HMMIO hmmioIn, UINT cbRead, BYTE* pbDest,
	MMCKINFO* pckIn, UINT* cbActualRead)
{
	MMIOINFO mmioinfoIn;         // current status of <hmmioIn>

	*cbActualRead = 0;

	if (0 != mmioGetInfo(hmmioIn, &mmioinfoIn, 0))
		return E_FAIL;

	UINT cbDataIn = cbRead;
	if (cbDataIn > pckIn->cksize)
		cbDataIn = pckIn->cksize;

	pckIn->cksize -= cbDataIn;

	for (DWORD cT = 0; cT < cbDataIn; cT++)
	{
		// Copy the bytes from the io to the buffer.
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			if (0 != mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ))
				return E_FAIL;

			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
				return E_FAIL;
		}

		// Actual copy.
		*((BYTE*)pbDest + cT) = *((BYTE*)mmioinfoIn.pchNext);
		mmioinfoIn.pchNext++;
	}

	if (0 != mmioSetInfo(hmmioIn, &mmioinfoIn, 0))
		return E_FAIL;

	*cbActualRead = cbDataIn;
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: CWaveSoundRead()
// Desc: Constructs the class
//-----------------------------------------------------------------------------
CWaveSoundRead::CWaveSoundRead()
{
	m_pwfx = NULL;
}

//-----------------------------------------------------------------------------
// Name: ~CWaveSoundRead()
// Desc: Destructs the class
//-----------------------------------------------------------------------------
CWaveSoundRead::~CWaveSoundRead()
{
	Close();
	SAFE_DELETE(m_pwfx);
}

//-----------------------------------------------------------------------------
// Name: Open()
// Desc: Opens a wave file for reading
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead::Open(CHAR* strFilename)
{
	SAFE_DELETE(m_pwfx);

	HRESULT  hr;

	if (FAILED(hr = WaveOpenFile(strFilename, &m_hmmioIn, &m_pwfx, &m_ckInRiff)))
		return hr;

	if (FAILED(hr = Reset()))
		return hr;

	return hr;
}

//-----------------------------------------------------------------------------
// Name: Reset()
// Desc: Resets the internal m_ckIn pointer so reading starts from the 
//       beginning of the file again 
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead::Reset()
{
	return WaveStartDataRead(&m_hmmioIn, &m_ckIn, &m_ckInRiff);
}

//-----------------------------------------------------------------------------
// Name: Read()
// Desc: Reads a wave file into a pointer and returns how much read
//       using m_ckIn to determine where to start reading from
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead::Read(UINT nSizeToRead, BYTE* pbData, UINT* pnSizeRead)
{
	return WaveReadFile(m_hmmioIn, nSizeToRead, pbData, &m_ckIn, pnSizeRead);
}

//-----------------------------------------------------------------------------
// Name: Close()
// Desc: Closes an open wave file 
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead::Close()
{
	mmioClose(m_hmmioIn, 0);
	return S_OK;
}

#include "../FrameBase/wavread.h"

SoundBase::SoundBase()
{
}

SoundBase::~SoundBase()
{

}

void SoundBase::SetPos(D3DXVECTOR3& Pos)
{
	SoundPos = Pos;
}

bool SoundBase::Loadsound(const char* fname)
{
	HRESULT hr;


	// WAVEファイルを開く
	CWaveSoundRead WaveFile;
	WaveFile.Open((char*)fname);

	// セカンダリ・バッファを作成する
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	//(DSBCAPS_CTRL3D=３Ｄサウンドを使用)
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRL3D |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	//3DサウンドのHELアルゴリズムを選択
	dsbdesc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;

	// バッファを作る
	LPDIRECTSOUNDBUFFER pDSTmp;
	KD3D.GetlpDSound()->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&LDSB8);
	pDSTmp->Release();

	// セカンダリ・バッファにWaveデータを書き込む
	LPVOID lpvPtr1;		// 最初のブロックのポインタ
	DWORD dwBytes1;		// 最初のブロックのサイズ
	LPVOID lpvPtr2;		// ２番目のブロックのポインタ
	DWORD dwBytes2;		// ２番目のブロックのサイズ

	hr = LDSB8->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	if (FAILED(hr)) {
		return false;
	}

	// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
	if (DSERR_BUFFERLOST == hr)
	{
		LDSB8->Restore();
		hr = LDSB8->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ロック成功

		// ここで，バッファに書き込む
		// バッファにデータをコピーする
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// 書き込みが終わったらすぐにUnlockする．
		hr = LDSB8->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}

	//3Dのセカンダリバッファを作る
	LDSB8->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&LDS3B8);
	return true;
}


void SoundBase::Copysound(const char* Key, int Init, int Loop)
{
	/*
	List tmp;
	//コピー
	LPDIRECTSOUNDBUFFER lpSTmp;
	KD3D.GetlpDSound()->DuplicateSoundBuffer(SE_List[Key].LDSB8, &lpSTmp);
	lpSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&tmp.LDSB8);
	tmp.LDSB8->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&tmp.LDS3B8);
	tmp.LDS3B8->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);
	List.emplace_back(tmp);
	List[(List.size() - 1)].SEPos = PosAdd;
	tmp.LDS3B8->SetPosition(List[(List.size() - 1)].SEPos.x, List[(List.size() - 1)].SEPos.y, List[(List.size() - 1)].SEPos.z, DS3D_IMMEDIATE);
	lpSTmp->Release();
	if (Init)	List[(List.size() - 1)].LDSB8->SetCurrentPosition(0);
	if (Loop)	List[(List.size() - 1)].LDSB8->Play(0, 0, DSBPLAY_LOOPING);
	else		List[(List.size() - 1)].LDSB8->Play(0, 0, 0);
	*/
}


void SoundBase::Update()
{
	//lpSListener->SetPosition();

/*
	for (int i = 0; i < List.size(); i++)
	{
		DWORD sFlg;
		List[i].LDSB8->GetStatus(&sFlg);
		if (!(sFlg & DSBSTATUS_PLAYING)) {
			List.erase(List.begin() + i);
			break;
		}
	}
	*/
}


void SoundBase::Playsound(const char* Key, bool Init, bool Loop)
{
	if (Init)
	{
		RESOURCE_MNG.GetSound(Key)->LDSB8->SetCurrentPosition(0);
	}
	if (!Loop)
	{
		RESOURCE_MNG.GetSound(Key)->LDSB8->Play(0, 0, 0);
	}
	else
	{
		RESOURCE_MNG.GetSound(Key)->LDSB8->Play(0, 0, DSBPLAY_LOOPING);
	}
}