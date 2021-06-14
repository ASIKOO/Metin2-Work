#ifndef __INC_METIN_II_GAME_ENTITY_H__
#define __INC_METIN_II_GAME_ENTITY_H__

class SECTREE;

class CEntity
{
	public:
		typedef std::unordered_map<LPENTITY, int32_t> ENTITY_MAP;

	public:
		CEntity();
		virtual	~CEntity();

		virtual void	EncodeInsertPacket(LPENTITY entity) = 0;
		virtual	void	EncodeRemovePacket(LPENTITY entity) = 0;

	protected:
		void			Initialize(int32_t type = -1);
		void			Destroy();


	public:
		void			SetType(int32_t type);
		int32_t				GetType() const;
		bool			IsType(int32_t type) const;

		void			ViewCleanup();
		void			ViewInsert(LPENTITY entity, bool recursive = true);
		void			ViewRemove(LPENTITY entity, bool recursive = true);
		void			ViewReencode();	// 주위 Entity에 패킷을 다시 보낸다.

		int32_t				GetViewAge() const	{ return m_iViewAge;	}

		int32_t			GetX() const		{ return m_pos.x; }
		int32_t			GetY() const		{ return m_pos.y; }
		int32_t			GetZ() const		{ return m_pos.z; }
		const PIXEL_POSITION &	GetXYZ() const		{ return m_pos; }

		void			SetXYZ(int32_t x, int32_t y, int32_t z)		{ m_pos.x = x, m_pos.y = y, m_pos.z = z; }
		void			SetXYZ(const PIXEL_POSITION & pos)	{ m_pos = pos; }

		LPSECTREE		GetSectree() const			{ return m_pSectree;	}
		void			SetSectree(LPSECTREE tree)	{ m_pSectree = tree;	}

		void			UpdateSectree();
		void			PacketAround(const void * data, int32_t bytes, LPENTITY except = NULL);
		void			PacketView(const void * data, int32_t bytes, LPENTITY except = NULL);

		void			BindDesc(LPDESC _d)     { m_lpDesc = _d; }
		LPDESC			GetDesc() const			{ return m_lpDesc; }

		void			SetMapIndex(int32_t l)	{ m_lMapIndex = l; }
		int32_t			GetMapIndex() const	{ return m_lMapIndex; }

		void			SetObserverMode(bool bFlag);
		bool			IsObserverMode() const	{ return m_bIsObserver; }

	protected:
		bool			m_bIsObserver;
		bool			m_bObserverModeChange;
		ENTITY_MAP		m_map_view;
		int32_t			m_lMapIndex;

	private:
		LPDESC			m_lpDesc;

		int32_t			m_iType;
		bool			m_bIsDestroyed;

		PIXEL_POSITION		m_pos;

		int32_t			m_iViewAge;

		LPSECTREE		m_pSectree;
};

#endif
