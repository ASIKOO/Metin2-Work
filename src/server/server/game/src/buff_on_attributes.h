#ifndef __METIN2_BUFF_ON_ATTRIBUTES_H
#define __METIN2_BUFF_ON_ATTRIBUTES_H

class CHARACTER;

class CBuffOnAttributes
{
public:
	CBuffOnAttributes(LPCHARACTER pOwner, uint8_t m_point_type, std::vector <uint8_t>* vec_buff_targets);
	~CBuffOnAttributes();

	// ���� �� �̸鼭, m_p_vec_buff_wear_targets�� �ش��ϴ� �������� ���, �ش� ���������� ���� ���� ȿ���� ����.
	void RemoveBuffFromItem(LPITEM pItem);
	// m_p_vec_buff_wear_targets�� �ش��ϴ� �������� ���, �ش� �������� attribute�� ���� ȿ�� �߰�.
	void AddBuffFromItem(LPITEM pItem);
	// m_bBuffValue�� �ٲٰ�, ������ ���� �ٲ�.
	void ChangeBuffValue(uint8_t bNewValue);
	// CHRACTRE::ComputePoints���� �Ӽ�ġ�� �ʱ�ȭ�ϰ� �ٽ� ����ϹǷ�, 
	// ���� �Ӽ�ġ���� ���������� owner���� ��.
	void GiveAllAttributes();

	// m_p_vec_buff_wear_targets�� �ش��ϴ� ��� �������� attribute�� type���� �ջ��ϰ�,
	// �� attribute���� (m_bBuffValue)% ��ŭ�� ������ ��.
	bool On(uint8_t bValue);
	// ���� ���� ��, �ʱ�ȭ
	void Off();

	void Initialize();
private:
	LPCHARACTER m_pBuffOwner;
	uint8_t m_bPointType;
	uint8_t m_bBuffValue;
	std::vector <uint8_t>* m_p_vec_buff_wear_targets;
	
	// apply_type, apply_value ����� ��
	typedef std::map <uint8_t, int32_t> TMapAttr;
	// m_p_vec_buff_wear_targets�� �ش��ϴ� ��� �������� attribute�� type���� �ջ��Ͽ� ������ ����.
	TMapAttr m_map_additional_attrs;

};

#endif
