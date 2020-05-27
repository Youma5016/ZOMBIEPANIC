#pragma once

class GameObject
{
public:
	GameObject();

	~GameObject();
	virtual void Init();		//���z�֐�
	virtual void Update() = 0;	//�������z�֐�
	virtual void Draw2D();
	virtual void Draw3D();
	virtual void End() = 0;
protected:
	KdMatrix m_world;
	std::shared_ptr<KdModel> m_pModel = nullptr;

};