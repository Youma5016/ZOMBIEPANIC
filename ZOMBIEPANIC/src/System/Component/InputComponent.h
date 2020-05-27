#pragma once
class GameObject;
class InputComponent{

public:
	virtual void Update() {}
	void SetOwner(std::shared_ptr<GameObject>p) {
		m_pOwner = p;
	}
	//int buttions(int idx) { return m_buttions[idx]; }
	float Horizontal() { return m_horizontal; }
	float Vartical() { return m_vertical; }

	const float& GetControlValue(char Key);
	void SetButtionValue(char Key, float val) {	//既に読み込んだかどうかを調べる
		if (m_ButtionMap.find(Key) != m_ButtionMap.end()) {
			//既にあった
			m_ButtionMap[Key] = val;
			//↑指定したキーにつながっている要素にアクセス
			//存在しないキーを使った場合、自動追加してしまう
		}  }

	//ボタンの管理
	enum {
		None,//何もしていない状態
		Down,//押した瞬間	
		Keep,//押し続けている状態
		Up,//離した瞬間
	};
protected:
	std::weak_ptr<GameObject>m_pOwner;

	std::map<char, float> m_ButtionMap;


	//スティック入力
	float m_horizontal = 0;//-1～1;
	float m_vertical = 0;

	
};

class InputKeyboard :public InputComponent {
public:
	void Update()override;

};

//キーとマウスに対応する派生クラス

//ゲームパッドに対応する派生クラス

//敵の動きに対応する派生クラス