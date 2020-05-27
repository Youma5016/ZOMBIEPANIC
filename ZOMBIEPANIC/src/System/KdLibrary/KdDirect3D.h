#pragma once

//==========================================================================================================
//
// 簡易Direct3D操作クラス
//	Direct3D9に必要な変数や、よく行う操作をまとめている。
//
//==========================================================================================================
class KdDirect3D {
public:
	//=============================================
	//
	// 取得系
	//
	//=============================================
	// D3Dオブジェクト取得
	LPDIRECT3D9EX			GetD3D(){ return m_lpD3D; }
	// D3Dデバイス取得
	LPDIRECT3DDEVICE9	GetDev(){ return m_lpD3DDev;}
	// D3Dパラメータ取得
	D3DPRESENT_PARAMETERS*	GetD3DPP(){return &m_d3dpp;}

	// デバイス情報取得
	D3DCAPS9*				GetCaps(){return &m_Caps;}

	// X解像度取得(画面の幅)
	int						GetRezoW() const {return m_d3dpp.BackBufferWidth;}
	// Y解像度取得(画面の高)
	int						GetRezoH() const {return m_d3dpp.BackBufferHeight;}
	//サウンド関連のデバイス制御変数
	LPDIRECTSOUND8 lpDSound;
	LPDIRECTSOUNDBUFFER lpSPrimary;

	LPD3DXSPRITE& GetSprite() { return mpSprite; } 	// スプライト
	LPD3DXFONT& GetFont() { return mpFont; }		// フォント
	LPDIRECTSOUND8& GetlpDSound() { return lpDSound; }

	void LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string &Path, int W, int H, const D3DCOLOR Color);
	void LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string &Path, const D3DCOLOR Color);
	void LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string &Path);

	//=============================================
	// 初期化
	//=============================================
	bool Init(HWND hWnd, int width, int height, bool fullscreen, std::string& errorMsg);


	//=============================================
	// 解放
	//=============================================
	void Release();

	//=============================================
	// ウィンドウ/フルスクリーン切り替え
	//=============================================
	bool ChangeFullScreenMode();

	//=============================================
	// ステート設定
	//=============================================
	// 基本的なレンダーステート等の設定
	void SetDefaultState();

	//=============================================
	// 行列セット
	//=============================================
	// ワールド変換行列をセット
	void SetWorldMatrix(const D3DXMATRIX* m) {
		m_lpD3DDev->SetTransform(D3DTS_WORLD, m);
	}
	// 
	~KdDirect3D() {
		Release();
	}

private:
	D3DLIGHT9					m_Light = {};//<-構造体の中身０クリアに



	LPDIRECT3D9EX				m_lpD3D = nullptr;				// D3Dオブジェクト
	LPDIRECT3DDEVICE9			m_lpD3DDev = nullptr;			// D3Dデバイス
	D3DPRESENT_PARAMETERS		m_d3dpp;						// 詳細設定
	D3DCAPS9					m_Caps;							// デバイスの情報

	LPDIRECT3DSURFACE9			m_OrgRenderTarget = nullptr;	// デフォルトのバックバッファ
	LPDIRECT3DSURFACE9			m_OrgDepthStencil = nullptr;	// デフォルトの深度(Z)バッファ



	//スプライト関係
	LPD3DXSPRITE	mpSprite = nullptr;	// スプライト
	LPD3DXFONT		mpFont = nullptr;		// フォント




//-------------------------------
// シングルトン用
//-------------------------------
private:

	KdDirect3D(){
	}

public:
	static KdDirect3D &GetInstance(){
		static KdDirect3D Instance;
		return Instance;
	}
	struct a {
		int a;
	};

};

// 簡単にアクセスできるようにするためのマクロ
#define KD3D KdDirect3D::GetInstance()
#define D3DEV  KdDirect3D::GetInstance().GetDev()
#define FONT KdDirect3D::GetInstance().GetFont()
#define SPRITE KdDirect3D::GetInstance().GetSprite()