// vim:ts=8 sw=4
#ifndef __INC_METIN_II_PLAYERHB_H__
#define __INC_METIN_II_PLAYERHB_H__

class PlayerHB : public singleton<PlayerHB>
{
    public:
	PlayerHB();
	virtual ~PlayerHB();

	bool	Initialize();

	void	Put(uint32_t id);

    private:
	bool	Query(uint32_t id);

	std::map<uint32_t, int32_t> m_map_data;
	std::string		m_stCreateTableQuery;
	std::string		m_stTableName;
	int32_t			m_iExpireTime;
};

#endif
