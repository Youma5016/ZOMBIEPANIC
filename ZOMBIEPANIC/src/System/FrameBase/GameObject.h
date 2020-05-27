#pragma once

class GameObject
{
public:
	GameObject();

	~GameObject();
	virtual void Init();		//‰¼‘zŠÖ”
	virtual void Update() = 0;	//ƒˆ‰¼‘zŠÖ”
	virtual void Draw2D();
	virtual void Draw3D();
	virtual void End() = 0;
protected:
	KdMatrix m_world;
	std::shared_ptr<KdModel> m_pModel = nullptr;

};