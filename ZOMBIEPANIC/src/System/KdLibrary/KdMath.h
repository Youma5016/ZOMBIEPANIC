#pragma once

class KdMatrix;

//ラッピング:ライブラリや他人の作ったプログラムを
//使いやすいように自作のクラスや関数に収めること
class KdVec3 :public D3DXVECTOR3{

public:
	KdVec3(){ x = y = z = 0; }
	KdVec3(float ix, float iy, float iz){ 
		x = ix;y = iy;z = iz;
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
	void SetLength(float len){
		Normalize();
		*this *= len;
	}
	void TransCoord(const KdMatrix& mat);
	void TransNormal(const KdMatrix& mat);

	//ベクトルの長さを取得
	float Length()const { return D3DXVec3Length(this); }

	float LengthToTarget(const KdVec3& v) const{
		KdVec3 vv = v- (*this) ;
		return D3DXVec3Length(&vv);
	}

	//自分を書き換えず逆行列化
	void  Inverse(KdVec3& v) const{v= (*this)*-1; }
	//自分を書き換えて逆行列化
	const void Inverse() { *this *= -1; }
};

//マトリックス関係ラップ
class KdMatrix :public D3DXMATRIX {

	//メンバ変数の追加禁止
public:
	
	KdMatrix(){ D3DXMatrixIdentity(this); }
	
	KdMatrix(const D3DXMATRIX& m) { 
		*(D3DXMATRIX*)this = m;
	}

	const D3DXMATRIX& operator=(const D3DXMATRIX& m)
	{
		*(D3DXMATRIX*)this = m;
		return *this;
	}


	//移動
	void CreateTrans(float x, float y, float z) {
		D3DXMatrixTranslation(this, x, y, z);
	}
	void CreateTrans(const KdVec3& v) {
		D3DXMatrixTranslation(this, v.x, v.y,v.z);
	}

	//回転
	void CreateRotationX(const float rad) {
		D3DXMatrixRotationX(this, rad);
	}
	void CreateRotationY(const float rad) {
		D3DXMatrixRotationY(this, rad);
	}
	void CreateRotationZ(const float rad) {
		D3DXMatrixRotationZ(this, rad);
	}
	void CreateRotation(float radx, float rady, float radz) {
		D3DXMatrixRotationYawPitchRoll(this,rady,radx, radz);
	}

	//拡大行列
	void CreateScale(float x, float y, float z) {
		D3DXMatrixScaling(this, x, y, z);
	}

	//操作系--------------------------->
	//東西南北天地に進めfloat
	void MoveWorld(float x, float y, float z) {
		KdMatrix m;
		m.CreateTrans(x, y, z);
		*this = (*this)*m;
	}

	//東西南北天地に進め
	void MoveWorld(const KdVec3& v) {
		KdMatrix m;
		m.CreateTrans(v.x, v.y, v.z);
		*this = (*this)*m;
	}

	//上下左右に動けfloat
	void MoveLocal(float x, float y, float z) {
		KdMatrix m;
		m.CreateTrans(x, y, z);
		*this = m * (*this);
	}


	//上下左右に動け
	void MoveLocal(const KdVec3& v) {
		KdMatrix m;
		m.CreateTrans(v.x, v.y, v.z);
		*this = m * (*this);
	}
	
	//世界座標回転
	void RotateXWorld(float rad) {
		KdMatrix m;
		m.CreateRotationX(rad);
		*this = (*this)*m;
	}
	void RotateYWorld(float rad) {
		KdMatrix m;
		m.CreateRotationY(rad);
		*this = (*this)*m;
	}
	void RotateZWorld(float rad) {
		KdMatrix m;
		m.CreateRotationZ(rad);
		*this = (*this)*m;
	}
	void RotateWorld(float radx, float rady, float radz ) {
		KdMatrix m;
		m.CreateRotation(radx,rady,radz);
		*this = (*this)*m;
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
		m.CreateRotation(radx, rady, radz);
		*this = m * (*this);
	}
	void Scaling(float x, float y, float z) {
		KdMatrix m;
		m.CreateScale(x, y, z);
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
	const KdVec3&GetXAxis()const {
		return*(KdVec3*)&_11;
	}
	//上方向のベクトル
	const KdVec3&GetYAxis()const {
		return*(KdVec3*)&_21;
	}
	//前方向のベクトル
	const KdVec3&GetZAxis()const {
		return*(KdVec3*)&_31;
	}

	//拡大率=長さ
	float GetScaleX()const {
		return GetXAxis().Length();
	}
	float GetScaleY()const {
		return GetXAxis().Length();
	}
	float GetScaleZ()const {
		return GetXAxis().Length();
	}

	//////自分の傾きrad角
	//float GetXDegRot() {
	//	KdVec3 v = GetYAxis();

	//	v.Normalize();
	//	v.x = 0;

	//	float ToRot = D3DXVec3Dot(&D3DXVECTOR3(0, 1, 0), &v);

	//	//======================================

	//	//角度変換
	//	ToRot = D3DXToDegree(acos(ToRot));
	//	//補正
	//	if (v.x < 0) {
	//		ToRot *= -1;
	//	}
	//	return ToRot;
	//}



	//////自分の傾きrad角
	//float GetYDegRot(){
	//	KdVec3 v = GetXAxis();

	//	v.Normalize();
	//	v.y = 0;

	//	float ToRot = D3DXVec3Dot(&D3DXVECTOR3(1, 0, 0), &v);

	//	//======================================

	//	//角度変換
	//	ToRot = D3DXToDegree(acos(ToRot));
	//	//補正
	//	if (v.y < 0) {
	//		ToRot *= -1;
	//	}
	//	return ToRot;
	//}
	////自分の傾きrad角
	//float GetZDegRot() {
	//	KdVec3 v = GetXAxis();

	//	v.Normalize();
	//	//v.Inverse();
	//	v.z = 0;

	//	float ToRot = D3DXVec3Dot(&D3DXVECTOR3(1, 0, 0), &v);

	//	//======================================

	//	//角度変換
	//	ToRot = D3DXToDegree(acos(ToRot));
	//	//補正
	//	if (v.x < 0) {
	//		ToRot *= -1;
	//	}
	//	ToRot *= -1;
	//	return ToRot;

	//}
	
};