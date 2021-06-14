#ifndef __INC_METIN_II_GAME_PVP_H__
#define __INC_METIN_II_GAME_PVP_H__

class CHARACTER;

// CPVP���� uint32_t ���̵� �ΰ��� �޾Ƽ� m_dwCRC�� ���� ������ �ִ´�.
// CPVPManager���� �̷��� ���� CRC�� ���� �˻��Ѵ�.
class CPVP
{
	public:
		friend class CPVPManager;

		typedef struct _player
		{
			uint32_t	dwPID;
			uint32_t	dwVID;
			bool	bAgree;
			bool	bCanRevenge;

			_player() : dwPID(0), dwVID(0), bAgree(false), bCanRevenge(false)
			{
			}
		} TPlayer;

		CPVP(uint32_t dwID1, uint32_t dwID2);
		CPVP(CPVP & v);
		~CPVP();

		void	Win(uint32_t dwPID); // dwPID�� �̰��!
		bool	CanRevenge(uint32_t dwPID); // dwPID�� ������ �� �־�?
		bool	IsFight();
		bool	Agree(uint32_t dwPID);

		void	SetVID(uint32_t dwPID, uint32_t dwVID);
		void	Packet(bool bDelete = false);

		void	SetLastFightTime();
		uint32_t	GetLastFightTime();

		uint32_t 	GetCRC() { return m_dwCRC; }

	protected:
		TPlayer	m_players[2];
		uint32_t	m_dwCRC;
		bool	m_bRevenge;

		uint32_t   m_dwLastFightTime;
};

class CPVPManager : public singleton<CPVPManager>
{
	typedef std::map<uint32_t, std::unordered_set<CPVP*> > CPVPSetMap;

	public:
	CPVPManager();
	virtual ~CPVPManager();

	void			Insert(LPCHARACTER pkChr, LPCHARACTER pkVictim);
	bool			CanAttack(LPCHARACTER pkChr, LPCHARACTER pkVictim);
	bool			Dead(LPCHARACTER pkChr, uint32_t dwKillerPID);	// PVP�� �־��� �������� ����
	void			GiveUp(LPCHARACTER pkChr, uint32_t dwKillerPID);
	void			Connect(LPCHARACTER pkChr);
	void			Disconnect(LPCHARACTER pkChr);

	void			SendList(LPDESC d);
	void			Delete(CPVP * pkPVP);

	void			Process();

	public:
	CPVP *			Find(uint32_t dwCRC);
	protected:
	void			ConnectEx(LPCHARACTER pkChr, bool bDisconnect);

	std::map<uint32_t, CPVP *>	m_map_pkPVP;
	CPVPSetMap		m_map_pkPVPSetByID;
};

#endif
