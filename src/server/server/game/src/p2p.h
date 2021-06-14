
#ifndef P2P_MANAGER_H_
#define P2P_MANAGER_H_

#include <boost/unordered_map.hpp>

#include "input.h"
#include "../../common/stl.h"

typedef struct _CCI
{
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
	uint32_t	dwPID;
	uint8_t	bEmpire;
	int32_t	lMapIndex;
	uint8_t	bChannel;

	LPDESC	pkDesc;
} CCI;

class P2P_MANAGER : public singleton<P2P_MANAGER>
{
	public:
		P2P_MANAGER();
		~P2P_MANAGER();

		// �Ʒ� Register* Unregister* pair���� ���������� ��� ���� ��ƾ�� ����Ѵ�.
		// ���� ��������� ǥ���ϱ� ���� ��
		void			RegisterAcceptor(LPDESC d);
		void			UnregisterAcceptor(LPDESC d);

		void			RegisterConnector(LPDESC d);
		void			UnregisterConnector(LPDESC d);

		void			EraseUserByDesc(LPDESC d);	// �ش� desc�� �ִ� �������� �����.

		void			FlushOutput();

		void			Boot(LPDESC d);	// p2p ó���� �ʿ��� ������ �����ش�. (�� ĳ������ �α��� ���� ��)

		void			Send(const void * c_pvData, int32_t iSize, LPDESC except = NULL);

		void			Login(LPDESC d, const TPacketGGLogin * p);
		void			Logout(const char * c_pszName);

		CCI *			Find(const char * c_pszName);
		CCI *			FindByPID(uint32_t pid);

		int32_t				GetCount();
		int32_t				GetEmpireUserCount(int32_t idx);
		int32_t				GetDescCount();
		void			GetP2PHostNames(std::string& hostNames);

	private:
		void			Logout(CCI * pkCCI);

		CInputProcessor *	m_pkInputProcessor;
		int32_t			m_iHandleCount;

		typedef boost::unordered_map<std::string, CCI *, stringhash> TCCIMap;
		typedef boost::unordered_map<uint32_t, CCI*> TPIDCCIMap;

		std::unordered_set<LPDESC> m_set_pkPeers;
		TCCIMap			m_map_pkCCI;
		TPIDCCIMap		m_map_dwPID_pkCCI;
		int32_t			m_aiEmpireUserCount[EMPIRE_MAX_NUM];
};

#endif /* P2P_MANAGER_H_ */

