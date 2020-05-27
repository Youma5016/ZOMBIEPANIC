#include"../KdLibrary/KdLibrary.h"
#include"InputComponent.h"
//�R���|�\�l���g
//111111
void InputKeyboard::Update()
{

	for (auto itr = m_ButtionMap.begin(); itr != m_ButtionMap.end(); itr++) {
		{

			if (GetAsyncKeyState(itr->first)) {
				if (m_ButtionMap[itr->first] == None) {
					m_ButtionMap[itr->first] = Down;

				}
				else { m_ButtionMap[itr->first] = Keep; }
			}
			else {
				if (m_ButtionMap[itr->first] == Keep || m_ButtionMap[itr->first] == Down) {
					m_ButtionMap[itr->first] = Up;
				}
				else { m_ButtionMap[itr->first] = None; }
			}
		}




		m_horizontal = 0;
		m_vertical = 0;


		if (GetAsyncKeyState(VK_UP)) { m_vertical = 1.0f; }
		if (GetAsyncKeyState(VK_DOWN)) { m_vertical = -1.0f; }
		if (GetAsyncKeyState(VK_RIGHT)) { m_horizontal = -1.0f; }
		if (GetAsyncKeyState(VK_LEFT)) { m_horizontal = 1.0f; }


	}
}
const float& InputComponent::GetControlValue(char Key)
{
	//���ɓǂݍ��񂾂��ǂ����𒲂ׂ�
	if (m_ButtionMap.find(Key) != m_ButtionMap.end()) {
		//���ɂ�����
		return m_ButtionMap[Key];
		//���w�肵���L�[�ɂȂ����Ă���v�f�ɃA�N�Z�X
		//���݂��Ȃ��L�[���g�����ꍇ�A�����ǉ����Ă��܂�
	}

	return m_ButtionMap[Key] = 0.0f;

}