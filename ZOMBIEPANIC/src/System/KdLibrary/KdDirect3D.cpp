#include "MyLibrary.h"

#include "KdDirect3D.h"




//================================================================================
//
// Direct3D9Ex������������B
//	�����FhWnd���Direct3D�Ŏg�p����E�B���h�E
//	�@�@�@Width�����
//�@�@�@�@Height�������
//�@�@�@�@Format����F���[�h
//�@�@�@�@FullScreen����t���X�N���[���t���O
//�@�߂�l�F�������TRUE
//�@�@�@�@�@���s���FALSE
//
//================================================================================
bool KdDirect3D::Init(HWND hWnd, int width, int height, bool fullscreen, std::string& errorMsg)
{
	HRESULT hr;

	//=======================================================
	// D3D�I�u�W�F�N�g�쐬
	//=======================================================
	hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &m_lpD3D);
	if(FAILED(hr)){
		return false;
	}

	//=======================================================
	// ���݂̉�ʃ��[�h���擾
	//=======================================================
	D3DDISPLAYMODE d3ddm;
	hr = m_lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if (FAILED(hr)) {
		Release();
		return false;
	}

	//=======================================================
	// �f�o�C�X�쐬�̂��߂̐ݒ�
	//=======================================================
	ZeroMemory( &m_d3dpp, sizeof(m_d3dpp) );
	m_d3dpp.BackBufferCount = 2;
	// �t���X�N���[�����[�h��
	if (fullscreen){
		m_d3dpp.Windowed = FALSE;
		m_d3dpp.BackBufferWidth = width;
		m_d3dpp.BackBufferHeight = height;
		m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		m_d3dpp.FullScreen_RefreshRateInHz = 60;
	}
	// �E�B���h�E���[�h��
	else{
		m_d3dpp.Windowed = TRUE;
		m_d3dpp.BackBufferWidth = 0;
		m_d3dpp.BackBufferHeight = 0;
		m_d3dpp.BackBufferFormat = d3ddm.Format;
	}
	m_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	// �X���b�v�G�t�F�N�g
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// ���j�^�̐���������҂��Ȃ�
	m_d3dpp.hDeviceWindow = hWnd;
	// Z �o�b�t�@�̎����쐬
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	// 24bitZ�o�b�t�@ + 8bit�X�e���V���o�b�t�@

	// �f�B�X�v���C���[�h�ݒ�(FullScreen���̂ݎg�p)
	D3DDISPLAYMODEEX dm;
	dm.Width = width;
	dm.Height = height;
	dm.Format = m_d3dpp.BackBufferFormat;
	dm.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;
	dm.RefreshRate = m_d3dpp.FullScreen_RefreshRateInHz;
	dm.Size = sizeof(dm);

	//=======================================================
	// �f�o�C�X�̍쐬
	//=======================================================
	// ��D3DCREATE_MULTITHREADED	�c�@�}���`�X���b�h�ł̃f�o�C�X���������
	// ��D3DCREATE_FPU_PRESERVE		�c�@float�̐��x���������Ɉێ�����(�����x��float���g��)
	DWORD flags = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE;

//	hr = m_lpD3D->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, flags, &m_d3dpp, (fullscreen ? &dm : nullptr), &m_lpD3DDev);
	hr = m_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, flags, &m_d3dpp, &m_lpD3DDev);
	if(FAILED(hr))
	{
		// ���s
		errorMsg = "Direct3D�̏������Ɏ��s", "Direct3D������";

		// �I������
		Release();
		return false;
	}

	//=======================================================
	// Caps�擾
	//=======================================================
	m_lpD3DDev->GetDeviceCaps(&m_Caps);
	
	//=======================================================
	// �f�t�H���g�̃o�b�N�o�b�t�@��Z�o�b�t�@�擾���Ă���
	//=======================================================
	m_lpD3DDev->GetRenderTarget(0, &m_OrgRenderTarget);
	m_lpD3DDev->GetDepthStencilSurface(&m_OrgDepthStencil);


	//=======================================================
	// �f�t�H���g�̃r���[�s��ƃv���W�F�N�V�����s���ݒ�
	//=======================================================
	// �܂��J�����̍s������
	D3DXMATRIX mView;
	D3DXMatrixTranslation(&mView, 0, 0, -10.0f);	// 
	// �t�s��Ńr���[�s��֕ϊ����Z�b�g
	D3DXMatrixInverse(&mView, 0, &mView);
	m_lpD3DDev->SetTransform(D3DTS_VIEW, &mView);

	// �ˉe�s��
	D3DXMATRIX mProj;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)width/height, 0.1f, 2000.0f);
	m_lpD3DDev->SetTransform(D3DTS_PROJECTION, &mProj);


	//���C�g�ݒ�
	CreateDirectionalLight(KdVec3(0.5f, -1.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR4(1.0f, 0.2f, 0.2f, 0.2f));

	//���C�g��L���ɂ���
	m_lpD3DDev->LightEnable(0, true);



	// �X�v���C�g�쐬.
	D3DXCreateSprite(m_lpD3DDev, &mpSprite);
	mpSprite->OnResetDevice();

	// �t�H���g�쐬
	D3DXCreateFont(m_lpD3DDev, 20, 20, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "�l�r �S�V�b�N", &mpFont);
	mpFont->OnResetDevice();

	//-------------------
	//DirectSound�̏�����
	//-------------------
	DirectSoundCreate8(NULL, &lpDSound, NULL);

	//�������x����ݒ�
	lpDSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);

	// �v���C�}���E�o�b�t�@�̍쐬
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	// �v���C�}���E�o�b�t�@���w��
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;

	// �o�b�t�@�����
	lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL);

	// �v���C�}���E�o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
	// �@�@�@�D�拦�����x���ȏ�̋������x�����ݒ肳��Ă���K�v������܂��D
	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX));
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;		// �Q�`�����l���i�X�e���I�j
	pcmwf.nSamplesPerSec = 44100;	// �T���v�����O�E���[�g�@44.1kHz
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = 16;		// 16�r�b�g
	lpSPrimary->SetFormat(&pcmwf);

	CoInitialize(NULL);


	return true;
}

void KdDirect3D::Release()
{
	// �o�b�N�o�b�t�@��Z�o�b�t�@���
	KdSafeRelease(m_OrgRenderTarget);
	KdSafeRelease(m_OrgDepthStencil);

	// �f�o�C�X���
	KdSafeRelease(m_lpD3DDev);
	// Direct3D���
	KdSafeRelease(m_lpD3D);
	//�T�E���h�֘A�J��
	KdSafeRelease(lpSPrimary);
	KdSafeRelease(lpDSound);

}

bool KdDirect3D::ChangeFullScreenMode()
{

	// �t���X�N���[�����[�h��
	if (m_d3dpp.Windowed) {
		m_d3dpp.Windowed = FALSE;
		m_d3dpp.FullScreen_RefreshRateInHz = 60;
	}
	// �E�B���h�E���[�h��
	else {
		m_d3dpp.Windowed = TRUE;
		m_d3dpp.BackBufferWidth = 0;
		m_d3dpp.BackBufferHeight = 0;
		m_d3dpp.FullScreen_RefreshRateInHz = 0;
	}

	// �f�B�X�v���C���[�h�ݒ�(FullScreen���̂�)
	D3DDISPLAYMODEEX dm;
	dm.Width = m_d3dpp.BackBufferWidth;
	dm.Height = m_d3dpp.BackBufferHeight;
	dm.Format = m_d3dpp.BackBufferFormat;
	dm.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;
	dm.RefreshRate = m_d3dpp.FullScreen_RefreshRateInHz;
	dm.Size = sizeof(dm);

	// 
	//HRESULT hr = m_lpD3DDev->Reset(&m_d3dpp, m_d3dpp.Windowed ? nullptr : &dm);
	HRESULT hr = m_lpD3DDev->Reset(&m_d3dpp);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//================================================================================
//
// ��{�I���Ȃ��Ǝv�������_�[�X�e�[�g�̐ݒ�
//
//================================================================================
void KdDirect3D::SetDefaultState()
{
	// DirectGraphics�̏ڍאݒ�
	m_lpD3DDev->SetRenderState(D3DRS_ZENABLE,TRUE);					// Z�o�b�t�@�L��
	m_lpD3DDev->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);			// Z�o�b�t�@�ɏ������ݗL��
	m_lpD3DDev->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	
	m_lpD3DDev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );		// �A���t�@�u�����h�L��

	// ���������[�h
	m_lpD3DDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_lpD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_lpD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_lpD3DDev->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);		//���_�@���̎������K��

	m_lpD3DDev->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);	// �O���[�V�F�[�f�B���O
	m_lpD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);		// �J�����O CCW = �E��� = �\�ʂ̂ݕ`��

	// �A���t�@�l�ʌv�Z
	m_lpD3DDev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	m_lpD3DDev->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
	m_lpD3DDev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
	m_lpD3DDev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_INVSRCALPHA);

	// �e�N�X�`���̃��l�̃u�����f�B���O���@�̐ݒ�
	// �e�N�X�`�������������̕��@
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );    // �ȉ��̈����̐�������Z����
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );    // �e�N�X�`���̐F���g�p
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );    // ���_�̐F���g�p
	// �F������������@
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );    // �ȉ��̈����̐�������Z����
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );    // �e�N�X�`���̐F���g�p
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );    // ���_�̐F���g�p

	// �e�N�X�`����Ԃ���`��
	m_lpD3DDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_lpD3DDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_lpD3DDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// �e�N�X�`���A�h���b�V���O���[�h�ݒ�
	m_lpD3DDev->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);	// ���b�v���[�h
	m_lpD3DDev->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);	// ���b�v���[�h

	// �~�b�v�}�b�v�ڍ׃��x����ݒ肷��B
	float fMipBias = 0.0f;
	m_lpD3DDev->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, *((DWORD*)&fMipBias));

	// ���C�gOFF
	m_lpD3DDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �X�y�L�����L��
	m_lpD3DDev->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// �t�H�O(������)
	m_lpD3DDev->SetRenderState(D3DRS_FOGENABLE, FALSE);
}
void KdDirect3D::CreatePointLight(const D3DXVECTOR3& Pos, const D3DXVECTOR4& Diffuse, const D3DXVECTOR4& Ambient)
{
	D3DLIGHT9 tmp = {};
	tmp.Type = D3DLIGHT_POINT;

	tmp.Position = Pos;

	tmp.Diffuse.a = Diffuse.w;
	tmp.Diffuse.r = Diffuse.x;
	tmp.Diffuse.g = Diffuse.y;
	tmp.Diffuse.b = Diffuse.z;

	tmp.Ambient.a = Ambient.w;
	tmp.Ambient.r = Ambient.x;
	tmp.Ambient.g = Ambient.y;
	tmp.Ambient.b = Ambient.z;


	m_Lights.emplace_back(tmp);

	//���C�g�̃Z�b�g
//	m_lpD3DDev->SetLight(&m_Lights.back(), &m_Lights[m_Lights.back()]);

}

void KdDirect3D::CreateDirectionalLight(const D3DXVECTOR3& Dir, const D3DXVECTOR4& Diffuse, const D3DXVECTOR4& Ambient)
{
	D3DLIGHT9 tmp = {};
	tmp.Type = D3DLIGHT_DIRECTIONAL;

	tmp.Diffuse.a = Diffuse.x;
	tmp.Diffuse.r = Diffuse.y;
	tmp.Diffuse.g = Diffuse.z;
	tmp.Diffuse.b = Diffuse.w;

	tmp.Ambient.a = Ambient.x;
	tmp.Ambient.r = Ambient.y;
	tmp.Ambient.g = Ambient.z;
	tmp.Ambient.b = Ambient.w;

	auto dir = Dir;
	D3DXVec3Normalize(&dir, &dir);
	tmp.Direction = dir;

	m_Lights.emplace_back(tmp);

	//���C�g�̃Z�b�g
//	m_lpD3DDev->SetLight(0, &m_Lights.back());
}

void KdDirect3D::DeleteLight()
{
	for (UINT i = 1; i < m_Lights.size(); i++)
	{
		m_lpD3DDev->LightEnable(i, false);
		m_Lights.pop_back();
	}
}

void KdDirect3D::SetLights()
{
	for (UINT i = 0; i < m_Lights.size(); i++)
	{
		m_lpD3DDev->SetLight(i, &m_Lights[i]);
		m_lpD3DDev->LightEnable(i, true);
	}
}


void KdDirect3D::LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string &Path, int W, int H, const D3DCOLOR Color)
{
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(m_lpD3DDev,Path.c_str(),W,H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, nullptr, nullptr, lpTex);
}
void KdDirect3D::LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string &Path, const D3DCOLOR Color)
{
	D3DXCreateTextureFromFileEx(m_lpD3DDev,Path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, nullptr, nullptr, lpTex);
}
void KdDirect3D::LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string &Path)
{
	D3DXCreateTextureFromFileEx(m_lpD3DDev, Path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, nullptr, nullptr, lpTex);
}