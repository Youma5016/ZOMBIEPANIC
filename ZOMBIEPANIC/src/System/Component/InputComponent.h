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
	void SetButtionValue(char Key, float val) {	//���ɓǂݍ��񂾂��ǂ����𒲂ׂ�
		if (m_ButtionMap.find(Key) != m_ButtionMap.end()) {
			//���ɂ�����
			m_ButtionMap[Key] = val;
			//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
			//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
		}  }

	//�{�^���̊Ǘ�
	enum {
		None,//�������Ă��Ȃ����
		Down,//�������u��	
		Keep,//���������Ă�����
		Up,//�������u��
	};
protected:
	std::weak_ptr<GameObject>m_pOwner;

	std::map<char, float> m_ButtionMap;


	//�X�e�B�b�N����
	float m_horizontal = 0;//-1�`1;
	float m_vertical = 0;

	
};

class InputKeyboard :public InputComponent {
public:
	void Update()override;

};

//�L�[�ƃ}�E�X�ɑΉ�����h���N���X

//�Q�[���p�b�h�ɑΉ�����h���N���X

//�G�̓����ɑΉ�����h���N���X