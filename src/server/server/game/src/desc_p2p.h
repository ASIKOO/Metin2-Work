#include "desc.h"

class DESC_P2P : public DESC
{
	public:
		virtual ~DESC_P2P();

		virtual void	Destroy();
		virtual void	SetPhase(int32_t iPhase);
		bool		Setup(LPFDWATCH _fdw, socket_t fd, const char * host, uint16_t wPort);
};

