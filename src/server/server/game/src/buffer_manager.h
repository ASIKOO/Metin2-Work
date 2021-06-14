#ifndef __INC_METIN_II_GAME_BUFFER_MANAGER_H__
#define __INC_METIN_II_GAME_BUFFER_MANAGER_H__

class TEMP_BUFFER
{
	public:
		TEMP_BUFFER(int32_t Size = 8192, bool ForceDelete = false );
		~TEMP_BUFFER();

		const void * 	read_peek();
		void		write(const void * data, int32_t size);
		int32_t		size();
		void	reset();

		LPBUFFER	getptr() { return buf; }

	protected:
		LPBUFFER	buf;
		bool		forceDelete;
};

#endif
