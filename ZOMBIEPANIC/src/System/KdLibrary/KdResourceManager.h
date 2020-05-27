#pragma once

class KdModel;
class SoundBase;
class KdResourcemanager {
public:
	std::shared_ptr<KdModel>GetModel(const std::string&Filename);//リソースの管理
	void clear(void) { m_models.clear(); m_texture.clear(); }



	std::shared_ptr <LPDIRECT3DTEXTURE9> GetTexture(const std::string& Path, int W, int H, const D3DCOLOR Color);
	std::shared_ptr <LPDIRECT3DTEXTURE9> GetTexture(const std::string& Path, const D3DCOLOR Color);
	std::shared_ptr <LPDIRECT3DTEXTURE9> GetTexture(const std::string& Path);
	std::shared_ptr<SoundBase>GetSound(const char* Path);
private:

	//モデルデータ
	std::map<std::string, std::shared_ptr<KdModel>>m_models;
	//テクスチャ
	std::map<std::string, std::shared_ptr<LPDIRECT3DTEXTURE9>>m_texture;
	//サウンド
	std::map<std::string, std::shared_ptr<SoundBase>> m_sounds;
private:
	KdResourcemanager() {} // ← コンストラクタ
	~KdResourcemanager() {} // ←デストラクタ

public:
	static KdResourcemanager& GetInstance()
	{
		static KdResourcemanager instance;
		return instance;

	}
};
#define RESOURCE_MNG KdResourcemanager::GetInstance()