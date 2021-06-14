#ifndef __PRIV_MANAGER_H
#define __PRIV_MANAGER_H

/**
 * @version 05/06/08	Bang2ni - Guild privilege ���� �Լ� ���� �ð� �߰�
 * 			          RequestGiveGuildPriv, GiveGuildPriv �Լ� ������Ÿ�� ����
 * 			          m_aPrivGuild Ÿ�� ����
 * 			          ����ü SPrivGuildData, ��� �Լ� GetPrivByGuildEx �߰�
 */
class CPrivManager : public singleton<CPrivManager>
{
	public:
		CPrivManager();

		void RequestGiveGuildPriv(uint32_t guild_id, uint8_t type, int32_t value, int32_t dur_time_sec);
		void RequestGiveEmpirePriv(uint8_t empire, uint8_t type, int32_t value, int32_t dur_time_sec);
		void RequestGiveCharacterPriv(uint32_t pid, uint8_t type, int32_t value);

		void GiveGuildPriv(uint32_t guild_id, uint8_t type, int32_t value, uint8_t bLog, int32_t end_time_sec);
		void GiveEmpirePriv(uint8_t empire, uint8_t type, int32_t value, uint8_t bLog, int32_t end_time_sec);
		void GiveCharacterPriv(uint32_t pid, uint8_t type, int32_t value, uint8_t bLog);

		void RemoveGuildPriv(uint32_t guild_id, uint8_t type);
		void RemoveEmpirePriv(uint8_t empire, uint8_t type);
		void RemoveCharacterPriv(uint32_t pid, uint8_t type);

		int32_t GetPriv(LPCHARACTER ch, uint8_t type);
		int32_t GetPrivByEmpire(uint8_t bEmpire, uint8_t type);
		int32_t GetPrivByGuild(uint32_t guild_id, uint8_t type);
		int32_t GetPrivByCharacter(uint32_t pid, uint8_t type);

	public:
		struct SPrivEmpireData
		{
			int32_t m_value;
			int32_t m_end_time_sec;
		};

		SPrivEmpireData* GetPrivByEmpireEx(uint8_t bEmpire, uint8_t type);

		/// ��� ���ʽ� ������
		struct SPrivGuildData
		{
			int32_t		value;		///< ���ʽ� ��ġ
			int32_t	end_time_sec;	///< ���� �ð�
		};

		/// ��� ���ʽ� �����͸� ���´�.
		/**
		 * @param [in]	dwGuildID ���� ����� ID
		 * @param [in]	byType ���ʽ� Ÿ��
		 * @return	��� ����� ��� ���ʽ� �������� ������, �ش��ϴ� ���ʽ� Ÿ�ٰ� ����� ID �� ���� ���ʽ� �����Ͱ� ���� ��� NULL
		 */
		const SPrivGuildData*	GetPrivByGuildEx( uint32_t dwGuildID, uint8_t byType ) const;

	private:
		SPrivEmpireData m_aakPrivEmpireData[MAX_PRIV_NUM][EMPIRE_MAX_NUM];
		std::map<uint32_t, SPrivGuildData> m_aPrivGuild[MAX_PRIV_NUM];
		std::map<uint32_t, int32_t> m_aPrivChar[MAX_PRIV_NUM];
};
#endif
