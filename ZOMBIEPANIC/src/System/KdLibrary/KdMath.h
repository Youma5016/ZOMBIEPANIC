#pragma once

class KdMatrix;

//ラッピング:ライブラリや他人の作ったプログラムを
//使いやすいように自作のクラスや関数に収めること
class KdVec3 :public D3DXVECTOR3 {

public:
	KdVec3() { x = y = z = 0; }
	KdVec3(float ix, float iy, float iz) {
		x = ix; y = iy; z = iz;
	}
	KdVec3(const D3DXVECTOR3& v) {
		x = v.x; y = v.y; z = v.z;
	}

	//「=」演算子が使われたら使用される関数
	const D3DXVECTOR3& operator=(const D3DXVECTOR3& v) {
		x = v.x; y = v.y; z = v.z;
		return *this;//=の数珠つなぎに使える
	}



	//設定
	void Set(float ix, float iy, float iz) {
		x = ix; y = iy; z = iz;
	}
	//単位行列化
	void Normalize() {
		D3DXVec3Normalize(this, this);
	}

	//指定の長さにベクトルを揃える(向きはそのまま)
	void SetLength(float len) {
		Normalize();
		*this *= len;
	}
	void TransCoord(const KdMatrix& mat);
	void TransNormal(const KdMatrix& mat);

	//ベクトルの長さを取得
	float Length()const { return D3DXVec3Length(this); }

	float LengthToTarget(const KdVec3& v) const {
		KdVec3 vv = v - (*this);
		return D3DXVec3Length(&vv);
	}

	//自分を書き換えず逆行列化
	void  Inverse(KdVec3& v) const { v = (*this) * -1; }
	//自分を書き換えて逆行列化
	const void Inverse() { *this *= -1; }
};

//マトリックス関係ラップ
class KdMatrix :public D3DXMATRIX {

	//メンバ変数の追加禁止
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


	//移動
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
	//回転
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

		//移動行列の取り出し
		Mat.SetTrans((*this)._41, (*this)._42, (*this)._43);
		//拡大行列の取り出し
		sM.MoveScal((*this).GetXAxis().Length(), (*this).GetYAxis().Length(), (*this).GetZAxis().Length());
		//回転行列の取り出し
		rM.RotateXLocal(radx);
		rM.RotateYLocal(rady);
		rM.RotateZLocal(radz);
		(*this) = sM * rM * Mat;
	}
	void CreateRotation(float radx, float rady, float radz) {
		D3DXMatrixRotationYawPitchRoll(this, rady, radx, radz);
	}


	//拡大行列
	inline void SetScale(float x, float y, float z) {


		if ((*this).GetScaleX() != 0)
		{
			//スケールｘの単位化
			(KdVec3&)_11 /= (*this).GetScaleX();

		}
		else {
			_11 = 1;
			_12 = 1;
			_13 = 1;
		}

		//スケールｘ
		(KdVec3&)_11 *= x;

		//スケールｙの単位化
		if ((*this).GetScaleY() != 0)
		{
			//スケールyの単位化
			(KdVec3&)_21 /= (*this).GetScaleY();

		}
		else {
			_21 = 1;
			_22 = 1;
			_23 = 1;
		}
		//スケールｙ*
		(KdVec3&)_21 *= y;

		//スケールzの単位化
		if ((*this).GetScaleZ() != 0)
		{
			//スケールzの単位化
			(KdVec3&)_31 /= (*this).GetScaleZ();

		}
		else {
			_31 = 1;
			_32 = 1;
			_33 = 1;
		}

		//スケールz	*
		(KdVec3&)_31 *= z;




	}
	//拡大行列
	void CreateScale(float x, float y, float z) {
		D3DXMatrixScaling(this, x, y, z);
	}

	void MoveScal(float x, float y, float z) {
		KdMatrix s;
		D3DXMatrixScaling(&s, x, y, z);
		(*this) = s * (*this);
	}

	//操作系--------------------------->
	//東西南北天地に進めfloat
	void MoveWorld(float x, float y, float z) {
		KdMatrix m;
		m.SetTrans(x, y, z);
		*this = (*this) * m;
	}

	//東西南北天地に進め
	void MoveWorld(const KdVec3& v) {
		KdMatrix m;
		m.SetTrans(v.x, v.y, v.z);
		*this = (*this) * m;
	}

	//上下左右に動けfloat
	void MoveLocal(float x, float y, float z) {
		KdMatrix m;
		m.SetTrans(x, y, z);
		*this = m * (*this);
	}


	//上下左右に動け
	void MoveLocal(const KdVec3& v) {
		KdMatrix m;
		m.SetTrans(v.x, v.y, v.z);
		*this = m * (*this);
	}

	//世界座標回転
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
	//自分座標回転
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

	//逆行列
	void Inverse() {
		D3DXMatrixInverse(this, NULL, this);
	}


	const KdVec3& GetPos()const {
		return *(KdVec3*)&_41;//float型をvec3ポインタにキャストした参照のアドレス
	}

	//左方向のベクトル
	const KdVec3& GetXAxis()const {
		return*(KdVec3*)&_11;
	}
	//上方向のベクトル
	const KdVec3& GetYAxis()const {
		return*(KdVec3*)&_21;
	}
	//前方向のベクトル
	const KdVec3& GetZAxis()const {
		return*(KdVec3*)&_31;
	}

	//拡大率=長さ
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