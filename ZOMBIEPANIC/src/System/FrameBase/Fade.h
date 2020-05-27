#pragma once

class CFade
{
private:
	CFade();
	~CFade();



public:
	bool GetLoadOKFlg() { return ok; };
   void Update();
	void Draw();
	
	void Start(const float& speed) {
		if ((speed<0.01 && speed>-0.01))return;

		startflg = true;
		accel = (255/(speed*60))*2;
		ok = false;
	};


	void LoadCheck() {

		Draw();
	}
private:
	bool startflg;

	bool ok;

	std::shared_ptr<LPDIRECT3DTEXTURE9> vTex;
	KdMatrix vMat;
	float alpha;
	float accel;
public:
	static CFade& GetInstance()
	{
		static CFade instance;
		return instance;
	}
};
#define FADE CFade::GetInstance()