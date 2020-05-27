#include"../KdLibrary/MyLibrary.h"
#include"GameObject.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Init()
{
	D3DXMatrixIdentity(&m_world);
}

void GameObject::Draw2D()
{
}

void GameObject::Draw3D()
{
}
