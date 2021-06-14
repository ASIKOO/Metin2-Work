#ifndef __INC_METIN_II_GAME_SPEEDSERVER_H__
#define __INC_METIN_II_GAME_SPEEDSERVER_H__

#include "../../common/length.h"
#include <list>

// castle.cpp 에 있는 것을 복붙 하였다
#define EMPIRE_NONE		0	// 아무국가 아님
#define EMPIRE_RED		1	// 신수
#define EMPIRE_YELLOW	2	// 천조
#define EMPIRE_BLUE		3	// 진노

class HME
{
	public :
		int32_t hour;
		int32_t min;
		int32_t exp;

		HME (int32_t h=0, int32_t m=0, int32_t e=0){
			hour =  h; min = m; 
			exp = e;
		}

		HME& operator=(const HME &rhs)
		{
			hour = rhs.hour;
			min = rhs.min;
			exp = rhs.exp;
			return *this;
		}

		bool operator==(const HME &rhs) const
		{
			return hour == rhs.hour
				&& min == rhs.min
				&& exp == rhs.exp;
		}

		bool operator<(const HME &rhs) const
		{
			return (hour<rhs.hour)
				|| (hour==rhs.hour) && (min<rhs.min);
		}
};

class Date
{
	public : 
		int32_t year;
		int32_t mon;
		int32_t day;

		Date (int32_t y = 0, int32_t m = 0, int32_t d = 0)
		{
			year = y; mon = m; day = d;
		}

		bool operator==(const Date &rhs) const
		{
			return year == rhs.year
				&& mon == rhs.mon
				&& day == rhs.day;
		}
		bool operator<(const Date &rhs) const
		{
			return (year<rhs.year)
				|| (year==rhs.year) && (mon<rhs.mon)
				|| (year==rhs.year) && (mon==rhs.mon) && (day<rhs.day);
		}
};

class CSpeedServerEmpireExp
{
	public :
		CSpeedServerEmpireExp();
		~CSpeedServerEmpireExp();

		bool Initialize (uint8_t empire);
		
		std::list <HME>& GetWdayExpTable(int32_t wday);
		void SetWdayExpTable(int32_t wday, HME hme);

		std::list <HME>& GetHolidayExpTable(Date date, bool &is_exist);
		void SetHolidayExpTable(Date date, HME hme);

		void InitWdayExpTable(int32_t wday);
		void InitHolidayExpTable(Date date);
		HME GetCurrentExpPriv (int32_t &duration, bool &is_change);

		bool WriteExpTable();

	private :
		bool LoadExpTable ();
		bool LoadWdayExpTable (int32_t wday, char *str);

		uint8_t empire;
		char file_name [256];
		HME current_hme;
		std::map <Date, std::list <HME> > holiday_map;
		std::list <HME> wday_exp_table[7];
};

class CSpeedServerManager : public singleton<CSpeedServerManager>
{
	public:
		CSpeedServerManager();
		~CSpeedServerManager();

		bool Initialize ();

		std::list <HME>& GetWdayExpTableOfEmpire (uint8_t empire, int32_t wday);
		void SetWdayExpTableOfEmpire (uint8_t empire, int32_t wday, HME hme);
		void InitWdayExpTableOfEmpire (uint8_t empire, int32_t wday);
		
		std::list <HME>& GetHolidayExpTableOfEmpire (uint8_t empire, Date date, bool &is_exist);
		void SetHolidayExpTableOfEmpire (uint8_t empire, Date date, HME hme);
		void InitHolidayExpTableOfEmpire (uint8_t empire, Date date);

		bool WriteExpTableOfEmpire (uint8_t empire);
		
		HME GetCurrentExpPrivOfEmpire (uint8_t empire, int32_t &duration, bool &is_change);

	private:
		CSpeedServerEmpireExp Empire[EMPIRE_MAX_NUM];
		
};

#endif
