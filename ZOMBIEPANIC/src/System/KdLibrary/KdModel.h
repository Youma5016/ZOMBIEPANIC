#pragma once

class KdModel {
public:
	// Xファイル読み込み
	// ・filename	: ファイル名
	// 戻り値		: true … 成功 false … 失敗
	bool LoadXFile(const std::string& filename);

	// 解放
	void Release();

	// 描画
	void Draw();
	//テクスチャの変更
	void ChangeTexture(int& matNum, const std::string& filename);

	// デストラクタ(このクラスが消えるときに、自動で実行される関数です)
	~KdModel() {
		Release();
	}
	LPD3DXMESH& GetMesh(void) { return m_pMesh; }
	
private:
	// メッシュ
	LPD3DXMESH	m_pMesh = nullptr;

	// マテリアル構造体
	struct Material {
		D3DMATERIAL9 matD3D;		// 材質
		LPDIRECT3DTEXTURE9 pTex;	// 画像
	};

	std::vector<Material>	m_materials;

	// ファイル名 記憶用
	std::string		m_fileName;
};
