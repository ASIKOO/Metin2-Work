/**
 *
 * @file	TrafficProfiler.h
 * @brief	TrafficProfiler class definition file
 * @author	Bang2ni
 * @version	05/07/07 Bang2ni - First release.
 * 
 */

#ifndef _METIN_II_TRAFFICPROFILER_H_
#define _METIN_II_TRAFFICPROFILER_H_

/**
 * @class	TrafficProfiler
 * @brief	Network I/O traffic �� ��Ŷ ������ �����ϴ� profiler.
 * @author	Bang2ni
 * @version	05/07/07 Bang2ni - First release.
 *
 * �ð��� ���� Network I/O �� traffic �� ��Ŷ ������ �����ϰ�, Text file ���·� ������ �ۼ��Ѵ�.
 */
class TrafficProfiler : public singleton< TrafficProfiler >
{
	public:

		/// I/O ����
		enum IODirection {
			IODIR_INPUT	= 0,	///< Input
			IODIR_OUTPUT,	///< Output
			IODIR_MAX
		};

	public:

		/// Constructor
		TrafficProfiler( void );

		/// Destructor
		~TrafficProfiler( void );

		/// Profiling �� �ʿ��� �ʱ�ȭ�� �Ѵ�.
		/**
		 * @param [in]	dwFlushCycle Flush �ֱ�. �� �����̴�.
		 * @param [in]	pszLogFileName Profiling log file �� �̸�
		 * @return	false �� ��� profiling log file �� open ���� ���ߴ�.
		 *
		 * profiling log file �� open(����) �Ѵ�.
		 */
		bool	Initialize( uint32_t dwFlushCycle, const char* pszLogFileName );

		/// Profiling �� ���� ���۵ưų� ���� �� Packet �� Report �Ѵ�.
		/**
		 * @param [in]	dir Profiling �� Packet �� ����
		 * @param [in]	byHeader Packet ���
		 * @param [in]	dwSize Packet �� �� size
		 * @return	Initialize ���� �ʾҴٸ� false �� ��ȯ�Ѵ�.
		 *
		 * Packet �� �ش��ϴ� size �� ������Ų��.
		 * Initialize ���ĳ� �ֱ� Flush �� ���Ŀ� Flush �ֱ� ��ŭ �ð��� �帥 �� ȣ��ȴٸ� Report ���� Flush �Ѵ�.
		 */
		bool	Report( IODirection dir, uint8_t byHeader, uint32_t dwSize )
		{
			ComputeTraffic( dir, byHeader, dwSize );
			if ( (uint32_t)(time( NULL ) - m_tmProfileStartTime) >= m_dwFlushCycle )
				return Flush();
			return true;
		}

		/// ������� Report �� ������ ���Ͽ� ����.
		/**
		 * @return	Initialize ���� �ʾҴ�.
		 */
		bool	Flush( void );

	private:

		/// Profling �� ���õ� variables �� �ʱ�ȭ �Ѵ�.
		void	InitializeProfiling( void );

		/// Report �� Packet �� traffic �� ����Ѵ�.
		/**
		 * @param [in]	dir Profiling �� Packet �� ����
		 * @param [in]	byHeader Packet ���
		 * @param [in]	dwSize Packet �� �� size
		 */
		void	ComputeTraffic( IODirection dir, uint8_t byHeader, uint32_t dwSize )
		{

			TrafficInfo& rTrafficInfo = m_aTrafficVec[ dir ][ byHeader ];

			m_dwTotalTraffic += dwSize;
			m_dwTotalPacket += !rTrafficInfo.second;

			rTrafficInfo.first += dwSize;
			rTrafficInfo.second++;
		}

		/// Traffic info type.
		/**
		 * first: ������ �� size
		 * second: �� packet �� ���۵� Ƚ��
		 */
		typedef std::pair< uint32_t, uint32_t >	TrafficInfo;

		/// Traffic info vector.
		typedef std::vector< TrafficInfo >	TrafficVec;

		FILE*		m_pfProfileLogFile;	///< Profile log file pointer
		uint32_t		m_dwFlushCycle;		///< Flush �ֱ�
		time_t		m_tmProfileStartTime;	///< ���������� ������ �ð�. Flush �� ������ Update �ȴ�.
		uint32_t		m_dwTotalTraffic;	///< Report �� �� Traffic �뷮
		uint32_t		m_dwTotalPacket;	///< Report �� �� Packet ��
		TrafficVec	m_aTrafficVec[ IODIR_MAX ];	///< Report �� Traffic �� ������ vector�� �迭. �� ���⸶�� vector �� ������.
};

#endif // _METIN_II_TRAFFICPROFILER_H_
