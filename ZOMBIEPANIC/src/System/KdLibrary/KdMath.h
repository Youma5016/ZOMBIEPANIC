#pragma once

class KdMatrix;

//���b�s���O:���C�u�����⑼�l�̍�����v���O������
//�g���₷���悤�Ɏ���̃N���X��֐��Ɏ��߂邱��
class KdVec3 :public D3DXVECTOR3 {

public:
	KdVec3() { x = y = z = 0; }
	KdVec3(float ix, float iy, float iz) {
		x = ix; y = iy; z = iz;
	}
	KdVec3(const D3DXVECTOR3& v) {
		x = v.x; y = v.y; z = v.z;
	}

	//�u=�v���Z�q���g��ꂽ��g�p�����֐�
	const D3DXVECTOR3& operator=(const D3DXVECTOR3& v) {
		x = v.x; y = v.y; z = v.z;
		return *this;//=�̐���Ȃ��Ɏg����
	}



	//�ݒ�
	void Set(float ix, float iy, float iz) {
		x = ix; y = iy; z = iz;
	}
	//�P�ʍs��
	void Normalize() {
		D3DXVec3Normalize(this, this);
	}

	//�w��̒����Ƀx�N�g���𑵂���(�����͂��̂܂�)
	void SetLength(float len) {
		Normalize();
		*this *= len;
	}
	void TransCoord(const KdMatrix& mat);
	void TransNormal(const KdMatrix& mat);

	//�x�N�g���̒������擾
	float Length()const { return D3DXVec3Length(this); }

	float LengthToTarget(const KdVec3& v) const {
		KdVec3 vv = v - (*this);
		return D3DXVec3Length(&vv);
	}

	//�����������������t�s��
	void  Inverse(KdVec3& v) const { v = (*this) * -1; }
	//���������������ċt�s��
	const void Inverse() { *this *= -1; }
};

//�}�g���b�N�X�֌W���b�v
class KdMatrix :public D3DXMATRIX {

	//�����o�ϐ��̒ǉ��֎~
public:

	KdMatrix() { D3DXMatrixIdentity(this); }

	KdMatrix(const D3DXMATRIX& m) {
		*(D3DXMATRIX*)this = m;
	}

	const D3DXMATRIX& operator=(const D3DXMATRIX& m)
	{
		*(D3DXMATRIX*)this = m;
		return *this;
	}


	//�ړ�
	void SetTrans(float x, float y, float z) {
		(*this)._41 = x;
		(*this)._42 = y;
		(*this)._43 = z;
	}
	void SetTrans(const KdVec3& v) {
		(*this)._41 = v.x;
		(*this)._42 = v.y;
		(*this)._43 = v.z;
	}
	void CreateTrans(float x, float y, float z) {
		D3DXMatrixTranslation(this, x, y, z);
	}
	void CreateTrans(const KdVec3& v) {
		D3DXMatrixTranslation(this, v.x, v.y, v.z);
	}
	//��]
	void CreateRotationX(const float rad) {
		D3DXMatrixRotationX(this, rad);
	}
	void CreateRotationY(const float rad) {
		D3DXMatrixRotationY
		(this, rad);
	}
	void CreateRotationZ(const float rad) {

		D3DXMatrixRotationZ(this, rad);

	}
	void SetRotation(float radx, float rady, float radz) {
		KdVec3 pos, scl;
		KdMatrix  rM, sM, Mat;

		//�ړ��s��̎��o��
		Mat.SetTrans((*this)._41, (*this)._42, (*this)._43);
		//�g��s��̎��o��
		sM.MoveScal((*this).GetXAxis().Length(), (*this).GetYAxis().Length(), (*this).GetZAxis().Length());
		//��]�s��̎��o��
		rM.RotateXLocal(radx);
		rM.RotateYLocal(rady);
		rM.RotateZLocal(radz);
		(*this) = sM * rM * Mat;
	}
	void CreateRotation(float radx, float rady, float radz) {
		D3DXMatrixRotationYawPitchRoll(this, rady, radx, radz);
	}


	//�g��s��
	inline void SetScale(float x, float y, float z) {


		if ((*this).GetScaleX() != 0)
		{
			//�X�P�[�����̒P�ʉ�
			(KdVec3&)_11 /= (*this).GetScaleX();

		}
		else {
			_11 = 1;
			_12 = 1;
			_13 = 1;
		}

		//�X�P�[����
		(KdVec3&)_11 *= x;

		//�X�P�[�����̒P�ʉ�
		if ((*this).GetScaleY() != 0)
		{
			//�X�P�[��y�̒P�ʉ�
			(KdVec3&)_21 /= (*this).GetScaleY();

		}
		else {
			_21 = 1;
			_22 = 1;
			_23 = 1;
		}
		//�X�P�[����*
		(KdVec3&)_21 *= y;

		//�X�P�[��z�̒P�ʉ�
		if ((*this).GetScaleZ() != 0)
		{
			//�X�P�[��z�̒P�ʉ�
			(KdVec3&)_31 /= (*this).GetScaleZ();

		}
		else {
			_31 = 1;
			_32 = 1;
			_33 = 1;
		}

		//�X�P�[��z	*
		(KdVec3&)_31 *= z;




	}
	//�g��s��
	void CreateScale(float x, float y, float z) {
		D3DXMatrixScaling(this, x, y, z);
	}

	void MoveScal(float x, float y, float z) {
		KdMatrix s;
		D3DXMatrixScaling(&s, x, y, z);
		(*this) = s * (*this);
	}

	//����n--------------------------->
	//������k�V�n�ɐi��float
	void MoveWorld(float x, float y, float z) {
		KdMatrix m;
		m.SetTrans(x, y, z);
		*this = (*this) * m;
	}

	//������k�V�n�ɐi��
	void MoveWorld(const KdVec3& v) {
		KdMatrix m;
		m.SetTrans(v.x, v.y, v.z);
		*this = (*this) * m;
	}

	//�㉺���E�ɓ���float
	void MoveLocal(float x, float y, float z) {
		KdMatrix m;
		m.SetTrans(x, y, z);
		*this = m * (*this);
	}


	//�㉺���E�ɓ���
	void MoveLocal(const KdVec3& v) {
		KdMatrix m;
		m.SetTrans(v.x, v.y, v.z);
		*this = m * (*this);
	}

	//���E���W��]
	void RotateXWorld(float rad) {
		KdMatrix m;
		m.CreateRotationX(rad);
		*this = (*this) * m;
	}
	void RotateYWorld(float rad) {
		KdMatrix m;
		m.CreateRotationY(rad);
		*this = (*this) * m;
	}
	void RotateZWorld(float rad) {
		KdMatrix m;
		m.CreateRotationZ(rad);
		*this = (*this) * m;
	}
	void RotateWorld(float radx, float rady, float radz) {
		KdMatrix m;
		m.SetRotation(radx, rady, radz);
		*this = (*this) * m;
	}
	//�������W��]
	void RotateXLocal(float rad) {
		KdMatrix m;
		m.CreateRotationX(rad);
		*this = m * (*this);
	}
	void RotateYLocal(float rad) {
		KdMatrix m;
		m.CreateRotationY(rad);
		*this = m * (*this);
	}void RotateZLocal(float rad) {
		KdMatrix m;
		m.CreateRotationZ(rad);
		*this = m * (*this);
	}
	void RotateLocal(float radx, float rady, float radz) {
		KdMatrix m;
		m.SetRotation(radx, rady, radz);
		*this = m * (*this);
	}
	void Scaling(float x, float y, float z) {
		KdMatrix m;
		m.SetScale(x, y, z);
		*this = m * (*this);
	}

	//�t�s��
	void Inverse() {
		D3DXMatrixInverse(this, NULL, this);
	}


	const KdVec3& GetPos()const {
		return *(KdVec3*)&_41;//float�^��vec3�|�C���^�ɃL���X�g�����Q�Ƃ̃A�h���X
	}

	//�������̃x�N�g��
	const KdVec3& GetXAxis()const {
		return*(KdVec3*)&_11;
	}
	//������̃x�N�g��
	const KdVec3& GetYAxis()const {
		return*(KdVec3*)&_21;
	}
	//�O�����̃x�N�g��
	const KdVec3& GetZAxis()const {
		return*(KdVec3*)&_31;
	}

	//�g�嗦=����
	float GetScaleX()const {
		return GetXAxis().Length();
	}
	float GetScaleY()const {
		return GetYAxis().Length();
	}
	float GetScaleZ()const {
		return GetZAxis().Length();
	}



};