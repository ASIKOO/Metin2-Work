#!/bin/sh

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		VERSION_USE=FALSE
		### Kraizy Full Edition = TRUE
		### Kraizy Updated Edition = FALSE

		if [ ${VERSION_USE} == TRUE ]
		then
			VERSION="1.1.0"
			### Kraizy Full Edition
		else
			VERSION="2014.1"
			### Kraizy Updated Edition
		fi

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		ROOT_PATH="/usr/m2_project"

		FLAG="-j3"
		CONFIGURATION="0" # 0 = debug | 1 = release #

		USE_AUTO_START="1" # 0 = false | 1 = true #
		USE_PRE_QC="1" # 0 = false | 1 = true #

		DEFAULT_CORE_COUNT="1" # for auto start option #
		DEFAULT_CORE_MIN="1" # don't touch #
		DEFAULT_CORE_MAX="3" # number of channel max #

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		M2_PATH="${ROOT_PATH}/${VERSION}"
		BACKUP_PATH="${ROOT_PATH}/backups"

		CONFIG_PATH="${M2_PATH}/settings"

		QUEST_PATH="${M2_PATH}/resources/locale/quest"

		if [ ${VERSION_USE} == TRUE ]
		then
			QUEST_PATH="${M2_PATH}/resources/locale/quest"
			### Kraizy Full Edition
		else
			QUEST_PATH="${M2_PATH}/resources/locale/france/quest"
			### Kraizy Updated Edition
		fi

		SRC_PATH="${M2_PATH}/srcs"
		SRC_OUTPUT_PATH="${SRC_PATH}/output"
		SRC_SERVER_PATH="${SRC_PATH}/server"
		SRC_DATA_PATH="${SRC_PATH}/data"

		SRC_GAME_PATH="${SRC_SERVER_PATH}/game/src"
		SRC_DB_PATH="${SRC_SERVER_PATH}/db/src"
		SRC_QC_PATH="${SRC_SERVER_PATH}/qc"

		SRC_LIBGAME_PATH="${SRC_SERVER_PATH}/libgame/src"
		SRC_LIBLUA_PATH="${SRC_SERVER_PATH}/liblua"
		SRC_LIBPOLY_PATH="${SRC_SERVER_PATH}/libpoly"
		SRC_LIBSQL_PATH="${SRC_SERVER_PATH}/libsql"
		SRC_LIBTHECORE_PATH="${SRC_SERVER_PATH}/libthecore/src"
		SRC_LIBCRYPTOPP_PATH="${SRC_DATA_PATH}/cryptopp_8_2_0/cryptopp"

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		m2_start_request()
		{
			clear
			echo -e ""

			if [ ${VERSION_USE} == TRUE ]
			then
				echo -e "\033[37m   [ \033[32mKRAIZY FULL EDITION\033[37m ] [ \033[36m${1} REQUEST\033[37m ]\033[0m"
				### Kraizy Full Edition
			else
				echo -e "\033[37m   [ \033[32mKRAIZY UPDATED EDITION\033[37m ] [ \033[36m${1} REQUEST\033[37m ]\033[0m"
				### Kraizy Updated Edition
			fi

			echo -e ""
			sleep 1
		}

		m2_end_request()
		{
			sleep 1
			echo -e ""

			if [ ${VERSION_USE} == TRUE ]
			then
				echo -e "\033[37m   [ \033[32mKRAIZY FULL EDITION\033[37m ] [ \033[36mCOMPLETED\033[37m ]\033[0m"
				### Kraizy Full Edition
			else
				echo -e "\033[37m   [ \033[32mKRAIZY UPDATED EDITION\033[37m ] [ \033[36mCOMPLETED\033[37m ]\033[0m"
				### Kraizy Updated Edition
			fi

			echo -e ""
		}

		init_db()
		{
			PID_PATH="${M2_PATH}/server/db/pid"

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[31mALREADY STARTED \033[37m]\033[0m"
				else

					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${M2_PATH}/server/db/ && ./db >> syserr_start 2>> syslog_start & sleep 8
				fi
			else

				echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
				cd ${M2_PATH}/server/db/ && ./db >> syserr_start 2>> syslog_start & sleep 8
			fi
		}

		init_auth()
		{
			PID_PATH="${M2_PATH}/server/auth/pid"

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[31mALREADY STARTED \033[37m]\033[0m"
				else

					echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${M2_PATH}/server/auth/ && ./auth >> syserr_start 2>> syslog_start & sleep 0.1
				fi
			else

				echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
				cd ${M2_PATH}/server/auth/ && ./auth >> syserr_start 2>> syslog_start & sleep 0.1
			fi
		}

		init_channel()
		{
			CHANNEL=$1
			echo -e "       \033[37m[ \033[37mCHANNEL ${CHANNEL} \033[37m]\033[0m"
		}

		init_core()
		{
			CHANNEL=$1
			CORE=$2
			PID_PATH="${M2_PATH}/server/channels/${CHANNEL}/cores/${CORE}/pid"

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					echo -e "           \033[37m[ \033[37mCORE ${CORE} \033[37m] \033[37m[ \033[31mALREADY STARTED \033[37m]\033[0m"
				else

					echo -e "           \033[37m[ \033[37mCORE ${CORE} \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${M2_PATH}/server/channels/${CHANNEL}/cores/${CORE}/ && ./game_${CHANNEL}_${CORE} >> syserr_start 2>> syslog_start & sleep 0.1
				fi
			else

				echo -e "           \033[37m[ \033[37mCORE ${CORE} \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
				cd ${M2_PATH}/server/channels/${CHANNEL}/cores/${CORE}/ && ./game_${CHANNEL}_${CORE} >> syserr_start 2>> syslog_start & sleep 0.1
			fi
		}

		kill_db()
		{
			PID_PATH="${M2_PATH}/server/db/pid"

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					kill -9 ${PID_READ} > /dev/null 2> /dev/null & sleep 0.1
				else

					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[31mNOT STARTED \033[37m]\033[0m"
				fi
			else

				echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[31mNOT STARTED \033[37m]\033[0m"
			fi
		}

		kill_auth()
		{
			PID_PATH="${M2_PATH}/server/auth/pid"

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					kill -9 ${PID_READ} > /dev/null 2> /dev/null & sleep 0.1
				else

					echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[31mNOT STARTED \033[37m]\033[0m"
				fi
			else

				echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[31mNOT STARTED \033[37m]\033[0m"
			fi
		}

		kill_core()
		{
			CHANNEL=$1
			CORE=$2
			PID_PATH="${M2_PATH}/server/channels/${CHANNEL}/cores/${CORE}/pid"

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					echo -e "           \033[37m[ \033[37mCORE ${CORE} \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					kill -9 ${PID_READ} > /dev/null 2> /dev/null & sleep 0.1
				else

					echo -e "           \033[37m[ \033[37mCORE ${CORE} \033[37m] \033[31mNOT STARTED \033[37m]\033[0m"
				fi
			else

				echo -e "           \033[37m[ \033[37mCORE ${CORE} \033[37m] \033[31mNOT STARTED \033[37m]\033[0m"
			fi
		}		

		check()
		{
			if [ -e ${2}/${1} ]
			then
				CLR=true
				rm -rf ${2}/${1}
			fi
		}

		check_idle()
		{
			if [ -e $2/$1 ]
			then
				CLR=true
			fi
		}

		check_logs()
		{
			check pid $1
			check syslog_game_1_1 $1
			check syslog_game_1_2 $1
			check syslog_game_1_3 $1
			check syslog_game_1_4 $1
			check syslog_game_1_5 $1
			check syslog_game_2_1 $1
			check syslog_game_2_2 $1
			check syslog_game_2_3 $1
			check syslog_game_2_4 $1
			check syslog_game_2_5 $1
			check syslog_game_3_1 $1
			check syslog_game_3_2 $1
			check syslog_game_3_3 $1
			check syslog_game_3_4 $1
			check syslog_game_3_5 $1
			check syslog_game_99_99 $1
			check pid_game_1_1 $1
			check pid_game_1_2 $1
			check pid_game_1_3 $1
			check pid_game_1_4 $1
			check pid_game_1_5 $1
			check pid_game_2_1 $1
			check pid_game_2_2 $1
			check pid_game_2_3 $1
			check pid_game_2_4 $1
			check pid_game_2_5 $1
			check pid_game_3_1 $1
			check pid_game_3_2 $1
			check pid_game_3_3 $1
			check pid_game_3_4 $1
			check pid_game_3_5 $1
			check pid_game_99_1 $1
			check syserr $1
			check syslog $1 $1
			check packet_info.txt $1
			check p2p_packet_info.txt $1
			check udp_packet_info.txt $1
			check game.core $1
			check db.core $1
			check gdb.core $1
			check VERSION.txt $1
			check mob_data.txt $1
			check stdout $1
			check PTS $1
			check usage.txt $1
			check castle_data.txt $1
			check syslog_start $1
			check syserr_start $1
		}

		check_logs_idle()
		{
			check_idle pid $1
			check_idle syslog_game_1_1 $1
			check_idle syslog_game_1_2 $1
			check_idle syslog_game_1_3 $1
			check_idle syslog_game_1_4 $1
			check_idle syslog_game_1_5 $1
			check_idle syslog_game_2_1 $1
			check_idle syslog_game_2_2 $1
			check_idle syslog_game_2_3 $1
			check_idle syslog_game_2_4 $1
			check_idle syslog_game_2_5 $1
			check_idle syslog_game_3_1 $1
			check_idle syslog_game_3_2 $1
			check_idle syslog_game_3_3 $1
			check_idle syslog_game_3_4 $1
			check_idle syslog_game_3_5 $1
			check_idle syslog_game_99_99 $1
			check_idle pid_game_1_1 $1
			check_idle pid_game_1_2 $1
			check_idle pid_game_1_3 $1
			check_idle pid_game_1_4 $1
			check_idle pid_game_1_5 $1
			check_idle pid_game_2_1 $1
			check_idle pid_game_2_2 $1
			check_idle pid_game_2_3 $1
			check_idle pid_game_2_4 $1
			check_idle pid_game_2_5 $1
			check_idle pid_game_3_1 $1
			check_idle pid_game_3_2 $1
			check_idle pid_game_3_3 $1
			check_idle pid_game_3_4 $1
			check_idle pid_game_3_5 $1
			check_idle pid_game_99_1 $1
			check_idle syserr $1
			check_idle syslog $1 $1
			check_idle packet_info.txt $1
			check_idle p2p_packet_info.txt $1
			check_idle udp_packet_info.txt $1
			check_idle game.core $1
			check_idle db.core $1
			check_idle gdb.core $1
			check_idle VERSION.txt $1
			check_idle mob_data.txt $1
			check_idle stdout $1
			check_idle PTS $1
			check_idle usage.txt $1
			check_idle castle_data.txt $1
			check_idle syslog_start $1
			check_idle syserr_start $1
		}

		clean_db()
		{
			DIR_PATH="${M2_PATH}/server/db"
			PID_PATH="${DIR_PATH}/pid"

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[31mSTARTED \033[37m]\033[0m"
				else

					CLR=false
					check_logs ${DIR_PATH}

					if [ $CLR = true ]
					then

						echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					else

						echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[33mNOT NEEDED \033[37m]\033[0m"
					fi
				fi
			else

				CLR=false
				check_logs ${DIR_PATH}

				if [ $CLR = true ]
				then

					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
				else

					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[33mNOT NEEDED \033[37m]\033[0m"
				fi
			fi
		}

		clean_auth()
		{
			DIR_PATH="${M2_PATH}/server/auth"
			PID_PATH="${DIR_PATH}/pid"

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[31mSTARTED \033[37m]\033[0m"
				else

					CLR=false
					check_logs ${DIR_PATH}

					if [ $CLR = true ]
					then

						echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					else

						echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[33mNOT NEEDED \033[37m]\033[0m"
					fi
				fi
			else

				CLR=false
				check_logs ${DIR_PATH}

				if [ $CLR = true ]
				then

					echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
				else

					echo -e "       \033[37m[ \033[37mAUTH \033[37m] \033[37m[ \033[33mNOT NEEDED \033[37m]\033[0m"
				fi
			fi
		}

		clean_core()
		{
			DIR_PATH="${M2_PATH}/server/channels/${1}/cores/${2}"
			PID_PATH="${DIR_PATH}/pid"

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					echo -e "           \033[37m[ \033[37mCORE ${2} \033[37m] \033[37m[ \033[31mSTARTED \033[37m]\033[0m"
				else

					CLR=false
					check_logs ${DIR_PATH}

					if [ $CLR = true ]
					then

						echo -e "           \033[37m[ \033[37mCORE ${2} \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					else

						echo -e "           \033[37m[ \033[37mCORE ${2} \033[37m] \033[37m[ \033[33mNOT NEEDED \033[37m]\033[0m"
					fi
				fi
			else

				CLR=false
				check_logs ${DIR_PATH}

				if [ $CLR = true ]
				then

					echo -e "           \033[37m[ \033[37mCORE ${2} \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
				else

					echo -e "           \033[37m[ \033[37mCORE ${2} \033[37m] \033[37m[ \033[33mNOT NEEDED \033[37m]\033[0m"
				fi
			fi
		}

		state_db()
		{
			DIR_PATH="${M2_PATH}/server/db"
			CORE_PATH="${DIR_PATH}/db.core"
			PID_PATH="${DIR_PATH}/pid"

			CHECK_STATE=`ps -C | grep -c db`
			STATE_DB=""
			STATE_PID=""

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					STATE_PID="\033[37m[ \033[32mONLINE \033[37m]\033[0m "
				else

					if [ ${CHECK_STATE} -gt 2 ]
					then

						STATE_DB="\033[37m[ \033[35mWARNING RUNNING PROCESS \033[37m]\033[0m "
					else

						CLR=false
						check_logs_idle ${DIR_PATH}

						if [ $CLR = true ]
						then

							STATE_LOGS="\033[37m[ \033[33mNEED CLEAN \033[37m]\033[0m "
						else

							STATE_LOGS=""
						fi

						STATE_PID="\033[37m[ \033[31mOFFLINE \033[37m]\033[0m "
					fi
				fi
			else

				if [ ${CHECK_STATE} -gt 2 ]
				then

					STATE_DB="\033[37m[ \033[35mWARNING RUNNING PROCESS \033[37m]\033[0m "
				else

					CLR=false
					check_logs_idle ${DIR_PATH}

					if [ $CLR = true ]
					then

						STATE_LOGS="\033[37m[ \033[33mNEED CLEAN \033[37m]\033[0m "
					else

						STATE_LOGS=""
					fi

					STATE_PID="\033[37m[ \033[31mOFFLINE \033[37m]\033[0m "
				fi
			fi

			if [ -e ${CORE_PATH} ]
			then

				STATE_CORE="\033[37m[ \033[31mCRASH \033[37m]\033[0m "
			else

				STATE_CORE=""
			fi

			echo -e "       \033[37m[ \033[37mDB \033[37m] ${STATE_DB}${STATE_PID}${STATE_CORE}${STATE_LOGS}"
		}

		state_auth()
		{
			DIR_PATH="${M2_PATH}/server/auth"
			CORE_PATH="${DIR_PATH}/game.core"
			PID_PATH="${DIR_PATH}/pid"

			CHECK_STATE=`ps -C | grep -c auth`
			STATE_GAME=""
			STATE_PID=""

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					STATE_PID="\033[37m[ \033[32mONLINE \033[37m]\033[0m "
				else

					if [ ${CHECK_STATE} -gt 2 ]
					then

						STATE_GAME="\033[37m[ \033[35mWARNING RUNNING PROCESS \033[37m]\033[0m "
					else

						CLR=false
						check_logs_idle ${DIR_PATH}

						if [ $CLR = true ]
						then

							STATE_LOGS="\033[37m[ \033[33mNEED CLEAN \033[37m]\033[0m "
						else

							STATE_LOGS=""
						fi

						STATE_PID="\033[37m[ \033[31mOFFLINE \033[37m]\033[0m "
					fi
				fi
			else

				if [ ${CHECK_STATE} -gt 2 ]
				then

					STATE_GAME="\033[37m[ \033[35mWARNING RUNNING PROCESS \033[37m]\033[0m "
				else

					CLR=false
					check_logs_idle ${DIR_PATH}

					if [ $CLR = true ]
					then

						STATE_LOGS="\033[37m[ \033[33mNEED CLEAN \033[37m]\033[0m "
					else

						STATE_LOGS=""
					fi

					STATE_PID="\033[37m[ \033[31mOFFLINE \033[37m]\033[0m "
				fi
			fi

			if [ -e ${CORE_PATH} ]
			then

				STATE_CORE="\033[37m[ \033[31mCRASH \033[37m]\033[0m "
			else

				STATE_CORE=""
			fi

			echo -e "       \033[37m[ \033[37mAUTH \033[37m] ${STATE_GAME}${STATE_PID}${STATE_CORE}${STATE_LOGS}"
		}

		state_core()
		{
			DIR_PATH="${M2_PATH}/server/channels/${1}/cores/${2}"
			CORE_PATH="${DIR_PATH}/game.core"
			PID_PATH="${DIR_PATH}/pid"

			CHECK_STATE=`ps -C | grep -c game_${CHANNEL}_${CORE}`
			STATE_GAME=""
			STATE_PID=""

			if [ -e ${PID_PATH} ]
			then

				PID_READ=`cat ${PID_PATH}`

				if ps -p ${PID_READ} > /dev/null
				then

					STATE_PID="\033[37m[ \033[32mONLINE \033[37m]\033[0m "
				else

					if [ ${CHECK_STATE} -gt 2 ]
					then

						STATE_GAME="\033[37m[ \033[35mWARNING RUNNING PROCESS \033[37m] \033[37m[ \033[31mPID NOT FOUND \033[37m]\033[0m "
					else

						CLR=false
						check_logs_idle ${DIR_PATH}

						if [ $CLR = true ]
						then

							STATE_LOGS="\033[37m[ \033[33mNEED CLEAN \033[37m]\033[0m "
						else

							STATE_LOGS=""
						fi

						STATE_PID="\033[37m[ \033[31mOFFLINE \033[37m]\033[0m "
					fi
				fi
			else

				if [ ${CHECK_STATE} -gt 2 ]
				then

						STATE_GAME="\033[37m[ \033[35mWARNING RUNNING PROCESS \033[37m] \033[37m[ \033[31mPID NOT FOUND \033[37m]\033[0m "
				else

					CLR=false
					check_logs_idle ${DIR_PATH}

					if [ $CLR = true ]
					then

						STATE_LOGS="\033[37m[ \033[33mNEED CLEAN \033[37m]\033[0m "
					else

						STATE_LOGS=""
					fi

					STATE_PID="\033[37m[ \033[31mOFFLINE \033[37m]\033[0m "
				fi
			fi

			if [ -e ${CORE_PATH} ]
			then

				STATE_CORE="\033[37m[ \033[31mCRASH \033[37m]\033[0m "
			else

				STATE_CORE=""
			fi

			echo -e "           \033[37m[ \033[37mCORE ${2} \033[37m] ${STATE_GAME}${STATE_PID}${STATE_CORE}${STATE_LOGS}"
		}		

		make_quest()
		{
			LOCALE_LIST_PATH="${QUEST_PATH}/new_locale_list"
			OBJECT_PATH="${QUEST_PATH}/object"

			if [ -e ${LOCALE_LIST_PATH} ]
			then

				if [ -r ${LOCALE_LIST_PATH} ]
				then

					if [ ! -e ${OBJECT_PATH} ]
					then

						mkdir ${OBJECT_PATH}
					fi

					echo -e "       \033[37m[ \033[37mQUESTS \033[37m] \033[37m[ \033[32mBUILD \033[37m]\033[0m"
					echo -e ""
					sleep 1

						for LINE in `cat ${LOCALE_LIST_PATH}`
						do
							# cd ${QUEST_PATH} && ./qc ${LINE} > ./log/syslog.${LINE} 2> ./log/syserr.${LINE} & sleep 1
							cd ${QUEST_PATH} && ./qc ${LINE} > ./log/${LINE}.syslog 2> ./log/${LINE}.syserr & sleep 3
							echo -e "           \033[37m[ \033[37mQUEST \033[37m] \033[37m[ \033[33m${LINE} \033[37m]\033[0m"
						done

					sleep 1
					echo -e ""
					echo -e "       \033[37m[ \033[37mQUESTS \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
				else

					echo -e "       \033[37m[ \033[37mQUESTS \033[37m] \033[37m[ \033[31mERROR \033[37m]\033[0m"
				fi
			else

				echo -e "       \033[37m[ \033[37mQUESTS \033[37m] \033[37m[ \033[31mERROR \033[37m]\033[0m"
			fi
		}

		quests_logs()
		{
			# check log/syslog $1
			# check log/syserr $1
			# check log/*.syserr $1
			# check log/*.syslog $1
			check log/* $1
			# check log/syserr.* $1
			# check log/syslog.* $1
			check qc.core $1
		}

		clean_quest()
		{
			CLR=false

			if [ -e ${QUEST_PATH} ]
			then

				rm -rdf ${QUEST_PATH}/object
				mkdir ${QUEST_PATH}/object

				quests_logs ${QUEST_PATH}

				if [ $CLR = true ]
				then

					echo -e "       \033[37m[ \033[37mQUESTS \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
				else

					echo -e "       \033[37m[ \033[37mQUESTS \033[37m] \033[37m[ \033[33mNOT NEEDED \033[37m]\033[0m"
				fi
			else

					echo -e "       \033[37m[ \033[37mQUESTS \033[37m] \033[37m[ \033[31mERROR \033[37m]\033[0m"
			fi
		}

		make_one_quest()
		{
			OBJECT_PATH="${QUEST_PATH}/object"

			if [ -e ${PID_PATH} ]
			then

				if [ -f ${QUEST_PATH}/${1} ]
				then

					if [ ! -e ${OBJECT_PATH} ]
					then

						mkdir ${OBJECT_PATH}
					fi

					echo -e "       \033[37m[ \033[37mQUEST \033[37m] \033[37m[ \033[32mBUILD \033[37m]\033[0m"
					echo -e ""

					sleep 1

					# cd ${QUEST_PATH} && ./qc ${1} > ./log/syslog.${1} 2> ./log/syserr.${1}
					cd ${QUEST_PATH} && ./qc ${1} > ./log/${1}.syslog 2> ./log/${1}.syserr
					echo -e "           \033[37m[ \033[37mQUEST \033[37m] \033[37m[ \033[33m${1} \033[37m]\033[0m"

					sleep 1

					echo -e ""
					echo -e "       \033[37m[ \033[37mQUEST \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
				else

					echo -e "       \033[37m[ \033[37mQUEST \033[37m] \033[37m[ \033[31mINVALID QUEST \033[37m]\033[0m"
				fi
			else

				echo -e "       \033[37m[ \033[37mQUEST \033[37m] \033[37m[ \033[31mINVALID QUEST \033[37m]\033[0m"
			fi
		}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		clear
		echo ""
		echo ""
		echo ""
		echo "	  __  __ ____    ____  ____   ___      _ _____ ____ _____"
		echo "	 |  \/  |___ \  |  _ \|  _ \ / _ \    | | ____/ ___|_   _|"
		echo "	 | |\/| | __) | | |_) | |_) | | | |_  | |  _|| |     | |"
		echo "	 | |  | |/ __/  |  __/|  _ <| |_| | |_| | |__| |___  | |"
		echo "	 |_|  |_|_____| |_|   |_| \_\\\___/ \___/|_____\____| |_|"
		echo ""
		echo ""
		echo ""
		echo -e ""

		if [ ${VERSION_USE} == TRUE ]
		then
			echo -e "   [ \033[32mM2 PROJECT\033[37m ] [ \033[36mKRAIZY FULL EDITION\033[37m ]\033[0m"
			### Kraizy Full Edition
		else
			echo -e "   [ \033[32mM2 PROJECT\033[37m ] [ \033[36mKRAIZY UPDATED EDITION\033[37m ]\033[0m"
			### Kraizy Updated Edition
		fi

		echo -e ""
		echo -e "       [ FILES ]\033[0m"
		echo -e ""

		if [ ${USE_AUTO_START} = "1" ]
		then

			echo -e "           [ \033[33m103\033[37m ] \033[36mSTART \033[0m"
			echo -e "           [ \033[33m104\033[37m ] \033[36mSTOP \033[0m"
			echo -e "           [ \033[33m106\033[37m ] \033[36mCLEAN \033[0m"
		else

			echo -e "           [ \033[33m101\033[37m ] \033[36mSTART\033[37m   \033[37m[ \033[33m102\033[37m ] \033[36mMANUAL   \033[37m[ \033[33m103\033[37m ] \033[36mAUTO \033[0m"
			echo -e "           [ \033[33m104\033[37m ] \033[36mSTOP\033[37m    \033[37m[ \033[33m105\033[37m ] \033[36mFORCE \033[0m"
			echo -e "           [ \033[33m106\033[37m ] \033[36mCLEAN \033[0m"
		fi

		echo -e ""
		echo -e "       [ QUESTS ]\033[0m"
		echo -e ""

		if [ ${USE_PRE_QC} = "1" ]
		then

			echo -e "           [ \033[33m203\033[37m ] \033[36mUPDATE \033[0m"
			echo -e "           [ \033[33m204\033[37m ] \033[36mCLEAN \033[0m"
		else

			# echo -e "           [ \033[33m201\033[37m ] \033[36mUPDATE\033[37m   \033[37m[ \033[33m202\033[37m ] \033[36mMANUAL   \033[37m[ \033[33m203\033[37m ] \033[36mPRE QC \033[0m"
			echo -e "           [ \033[33m201\033[37m ] \033[36mUPDATE\033[0m"
			echo -e "           [ \033[33m204\033[37m ] \033[36mCLEAN \033[0m"
		fi

		echo -e ""
		echo -e "       [ SRCS ]\033[0m"
		echo -e ""
		echo -e "           [ \033[33m301\033[37m ] \033[36mGAME\033[37m        \033[37m[ \033[33m302\033[37m ] \033[36mDB            \033[37m[ \033[33m303\033[37m ] \033[36mQC \033[0m"
		# echo -e ""
		echo -e "           [ \033[33m304\033[37m ] \033[36mLIBGAME\033[37m     \033[37m[ \033[33m305\033[37m ] \033[36mLIBTHECORE    \033[37m[ \033[33m306\033[37m ] \033[36mLIBLUA \033[0m"
		echo -e "           [ \033[33m307\033[37m ] \033[36mLIBPOLY\033[37m     \033[37m[ \033[33m308\033[37m ] \033[36mLIBCRYPTOPP   \033[37m[ \033[33m309\033[37m ] \033[36mLIBSQL \033[0m"
		# echo -e ""
		echo -e "           [ \033[33m310\033[37m ] \033[36mCLEAN ALL\033[37m   \033[37m[ \033[33m311\033[37m ] \033[36mCLEAN MAIN    \033[37m[ \033[33m312\033[37m ] \033[36mCLEAN SUB \033[0m"
		echo -e ""
		echo -e "       [ MISCELLANEOUS ]\033[0m"
		echo -e ""
		echo -e "           [ \033[33m401\033[37m ] \033[36mSYMBOLIC LINKS\033[37m    \033[37m[ \033[33m402\033[37m ] \033[36mSTATE \033[0m"
		echo -e "           [ \033[33m403\033[37m ] \033[36mCHECK INTEGRITY\033[37m   \033[37m[ \033[33m405\033[37m ] \033[36mBACKUP \033[0m"
		echo -e ""

		if [ ${VERSION_USE} == TRUE ]
		then
			echo -e "   [ \033[32mM2 PROJECT\033[37m ] [ \033[36mKRAIZY FULL EDITION\033[37m ]\033[0m"
			### Kraizy Full Edition
		else
			echo -e "   [ \033[32mM2 PROJECT\033[37m ] [ \033[36mKRAIZY UPDATED EDITION\033[37m ]\033[0m"
			### Kraizy Updated Edition
		fi

		echo -e ""
		read m2sh

		case ${m2sh} in

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		101*)
			m2_start_request "START"

				for CHANNEL in `seq ${DEFAULT_CORE_MIN} ${DEFAULT_CORE_MAX}`
				do

					if [ ${CHANNEL} = 1 ]
					then

						echo -e "       [ \033[33m${CHANNEL}\033[37m ] \033[36mCHANNEL \033[0m"
					else

						echo -e "       [ \033[33m${CHANNEL}\033[37m ] \033[36mCHANNELS \033[0m"
					fi
				done

				echo -e ""
				read M2SH_START
				DEFAULT_CORE_COUNT=${M2SH_START}

				if [ -z ${DEFAULT_CORE_COUNT} ]
				then

					DEFAULT_CORE_COUNT=${DEFAULT_CORE_MIN}
				else

					if [ ${DEFAULT_CORE_COUNT} -ge ${DEFAULT_CORE_MIN} ] || [ ${DEFAULT_CORE_COUNT} -le ${DEFAULT_CORE_MAX} ]
					then

						if [ ${DEFAULT_CORE_COUNT} -gt ${DEFAULT_CORE_MAX} ]
						then

							DEFAULT_CORE_COUNT=${DEFAULT_CORE_MAX}
						elif [ ${DEFAULT_CORE_COUNT} -lt ${DEFAULT_CORE_MIN} ]
						then

							DEFAULT_CORE_COUNT=${DEFAULT_CORE_MIN}
						else

							DEFAULT_CORE_COUNT=${M2SH_START}
						fi
					else

						DEFAULT_CORE_COUNT=${DEFAULT_CORE_MIN}
					fi
				fi

			m2_start_request "START"

				init_db
				init_auth

				for CHANNEL in `seq ${DEFAULT_CORE_MIN} ${DEFAULT_CORE_COUNT}`
				do

					init_channel ${CHANNEL}
					init_core ${CHANNEL} 1
					init_core ${CHANNEL} 2
					init_core ${CHANNEL} 3
					init_core ${CHANNEL} 4
					init_core ${CHANNEL} 5
				done

				init_channel 99
				init_core 99 1

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		102*)
			clear
			echo -e ""
			echo -e "   [ \033[32mM2 PROJECT\033[37m ] [ \033[36mSTART REQUEST\033[37m ]\033[0m"
			echo -e ""
			echo -e "       [\033[33m 001 \033[37m] \033[36mDB \033[0m"
			echo -e "       [\033[33m 002 \033[37m] \033[36mAUTH \033[0m"
			echo -e ""
			echo -e "       [\033[33m 100 \033[37m] \033[36mCHANNEL 1 \033[0m"
			echo -e ""
			echo -e "           [\033[33m 101 \033[37m] \033[36mCHANNEL 1 \033[37m/\033[36m 1 \033[0m"
			echo -e "           [\033[33m 102 \033[37m] \033[36mCHANNEL 1 \033[37m/\033[36m 2 \033[0m"
			echo -e "           [\033[33m 103 \033[37m] \033[36mCHANNEL 1 \033[37m/\033[36m 3 \033[0m"
			echo -e "           [\033[33m 104 \033[37m] \033[36mCHANNEL 1 \033[37m/\033[36m 4 \033[0m"
			echo -e "           [\033[33m 105 \033[37m] \033[36mCHANNEL 1 \033[37m/\033[36m 5 \033[0m"
			echo -e ""
			echo -e "       [\033[33m 200 \033[37m] \033[36mCHANNEL 2 \033[0m"
			echo -e ""
			echo -e "           [\033[33m 201 \033[37m] \033[36mCHANNEL 2 \033[37m/\033[36m 1 \033[0m"
			echo -e "           [\033[33m 202 \033[37m] \033[36mCHANNEL 2 \033[37m/\033[36m 2 \033[0m"
			echo -e "           [\033[33m 203 \033[37m] \033[36mCHANNEL 2 \033[37m/\033[36m 3 \033[0m"
			echo -e "           [\033[33m 204 \033[37m] \033[36mCHANNEL 2 \033[37m/\033[36m 4 \033[0m"
			echo -e "           [\033[33m 205 \033[37m] \033[36mCHANNEL 2 \033[37m/\033[36m 5 \033[0m"
			echo -e ""
			echo -e "       [\033[33m 300 \033[37m] \033[36mCHANNEL 3 \033[0m"
			echo -e ""
			echo -e "           [\033[33m 301 \033[37m] \033[36mCHANNEL 3 \033[37m/\033[36m 1 \033[0m"
			echo -e "           [\033[33m 302 \033[37m] \033[36mCHANNEL 3 \033[37m/\033[36m 2 \033[0m"
			echo -e "           [\033[33m 303 \033[37m] \033[36mCHANNEL 3 \033[37m/\033[36m 3 \033[0m"
			echo -e "           [\033[33m 304 \033[37m] \033[36mCHANNEL 3 \033[37m/\033[36m 4 \033[0m"
			echo -e "           [\033[33m 305 \033[37m] \033[36mCHANNEL 3 \033[37m/\033[36m 5 \033[0m"
			echo -e ""
			echo -e "       [\033[33m 990 \033[37m] \033[36mCHANNEL 99 \033[0m"
			echo -e ""
			echo -e "           [\033[33m 991 \033[37m] \033[36mCHANNEL 99 \033[37m/\033[36m 1 \033[0m"
			echo -e ""

			if [ ${VERSION_USE} == TRUE ]
			then
				echo -e "   [ \033[32mM2 PROJECT\033[37m ] [ \033[36mKRAIZY FULL EDITION\033[37m ]\033[0m"
				### Kraizy Full Edition
			else
				echo -e "   [ \033[32mM2 PROJECT\033[37m ] [ \033[36mKRAIZY UPDATED EDITION\033[37m ]\033[0m"
				### Kraizy Updated Edition
			fi

			echo -e ""
			read m2sh_manual_start

			case ${m2sh_manual_start} in

				001*)
					m2_start_request "START"
					
						init_db
						
					m2_end_request
				;;
				
				002*)
					m2_start_request "START"
					
						init_auth
					
					m2_end_request
				;;
				
				100*)
					m2_start_request "START"

						init_channel 1
						init_core 1 1
						init_core 1 2
						init_core 1 3
						init_core 1 4
						init_core 1 5

					m2_end_request
				;;
				
				101*)
					m2_start_request "START"

						init_channel 1
						init_core 1 1

					m2_end_request
				;;
				
				102*)
					m2_start_request "START"

						init_channel 1
						init_core 1 2

					m2_end_request
				;;
				
				103*)
					m2_start_request "START"

						init_channel 1
						init_core 1 3

					m2_end_request
				;;
				
				104*)
					m2_start_request "START"

						init_channel 1
						init_core 1 4

					m2_end_request
				;;
				
				105*)
					m2_start_request "START"

						init_channel 1
						init_core 1 5

					m2_end_request
				;;
				
				200*)
					m2_start_request "START"

						init_channel 2
						init_core 2 1
						init_core 2 2
						init_core 2 3
						init_core 2 4
						init_core 2 5

					m2_end_request
				;;
				
				201*)
					m2_start_request "START"

						init_channel 2
						init_core 2 1

					m2_end_request
				;;
				
				202*)
					m2_start_request "START"

						init_channel 2
						init_core 2 2

					m2_end_request
				;;
				
				203*)
					m2_start_request "START"

						init_channel 2
						init_core 2 3

					m2_end_request
				;;
				
				204*)
					m2_start_request "START"

						init_channel 2
						init_core 2 4

					m2_end_request
				;;
				
				205*)
					m2_start_request "START"

						init_channel 2
						init_core 2 5

					m2_end_request
				;;
				
				300*)
					m2_start_request "START"

						init_channel 3
						init_core 3 1
						init_core 3 2
						init_core 3 3
						init_core 3 4
						init_core 3 5

					m2_end_request
				;;
				
				301*)
					m2_start_request "START"

						init_channel 3
						init_core 3 1

					m2_end_request
				;;
				
				302*)
					m2_start_request "START"

						init_channel 3
						init_core 3 2

					m2_end_request
				;;
				
				303*)
					m2_start_request "START"

						init_channel 3
						init_core 3 3

					m2_end_request
				;;
				
				304*)
					m2_start_request "START"

						init_channel 3
						init_core 3 4

					m2_end_request
				;;
				
				305*)
					m2_start_request "START"

						init_channel 3
						init_core 3 5

					m2_end_request
				;;

				990*)
					m2_start_request "START"

						init_channel 99
						init_core 99 1

					m2_end_request
				;;

				991*)
					m2_start_request "START"

						init_channel 99
						init_core 99 1

					m2_end_request
				;;

			esac
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		103*)
			m2_start_request "AUTO"

				CHECK_STATE_DB=`ps -c | grep -c db`
				CHECK_STATE_GAME=`ps -c | grep -c game`
		
				if [ ${CHECK_STATE_DB} -gt 0 ] || [ ${CHECK_STATE_GAME} -gt 0 ]
				then

					m2_start_request "SHUTDOWN"

						for CHANNEL in `seq ${DEFAULT_CORE_MIN} ${DEFAULT_CORE_MAX}`
						do

							init_channel ${CHANNEL}
							kill_core ${CHANNEL} 1
							kill_core ${CHANNEL} 2
							kill_core ${CHANNEL} 3
							kill_core ${CHANNEL} 4
							kill_core ${CHANNEL} 5
						done

						init_channel 99
						kill_core 99 1

						kill_auth
						kill_db

					m2_end_request
				fi

			m2_start_request "CLEAN"

				clean_db
				clean_auth

				for CHANNEL in `seq ${DEFAULT_CORE_MIN} ${DEFAULT_CORE_MAX}`
				do

					init_channel ${CHANNEL}
					clean_core ${CHANNEL} 1
					clean_core ${CHANNEL} 2
					clean_core ${CHANNEL} 3
					clean_core ${CHANNEL} 4
					clean_core ${CHANNEL} 5
				done

				init_channel 99
				clean_core 99 1

			m2_end_request
			m2_start_request "START"

				init_db
				init_auth

				for CHANNEL in `seq ${DEFAULT_CORE_MIN} ${DEFAULT_CORE_COUNT}`
				do

					init_channel ${CHANNEL}
					init_core ${CHANNEL} 1
					init_core ${CHANNEL} 2
					init_core ${CHANNEL} 3
					init_core ${CHANNEL} 4
					init_core ${CHANNEL} 5
				done

				init_channel 99
				init_core 99 1

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		104*)
			m2_start_request "SHUTDOWN"

				for CHANNEL in `seq ${DEFAULT_CORE_MIN} ${DEFAULT_CORE_MAX}`
				do

					init_channel ${CHANNEL}
					kill_core ${CHANNEL} 1
					kill_core ${CHANNEL} 2
					kill_core ${CHANNEL} 3
					kill_core ${CHANNEL} 4
					kill_core ${CHANNEL} 5
				done

				init_channel 99
				kill_core 99 1

				kill_auth
				kill_db

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		105*)
			m2_start_request "SHUTDOWN"

				CHECK_STATE_DB=`ps -c | grep -c db`
				CHECK_STATE_GAME=`ps -c | grep -c game`
		
				if [ ${CHECK_STATE_GAME} -gt 0 ]
				then

					echo -e "       \033[37m[ \033[37mGAME \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					killall -9 game >/dev/null 2>/dev/null
				else
					echo -e "       \033[37m[ \033[37mGAME \033[37m] \033[37m[ \033[33mNOT NEEDED \033[37m]\033[0m"
				fi

					sleep 1

				if [ ${CHECK_STATE_DB} -gt 0 ]
				then

					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					killall -9 db >/dev/null 2>/dev/null
				else
					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[33mNOT NEEDED \033[37m]\033[0m"
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		106*)
			m2_start_request "CLEAN"

				clean_db
				clean_auth

				for CHANNEL in `seq ${DEFAULT_CORE_MIN} ${DEFAULT_CORE_MAX}`
				do

					init_channel ${CHANNEL}
					clean_core ${CHANNEL} 1
					clean_core ${CHANNEL} 2
					clean_core ${CHANNEL} 3
					clean_core ${CHANNEL} 4
					clean_core ${CHANNEL} 5
				done

				init_channel 99
				clean_core 99 1

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		201*)
			m2_start_request "QUESTS"

				make_quest

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		202*)
			m2_start_request "QUESTS"

				echo -e "       \033[37m[ \033[37mPlease enter the name of the quest with its extension \033[37m]\033[0m"
				echo -e ""

				read quest_name
				echo -e ""

				make_one_quest ${quest_name}

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		203*)
			m2_start_request "QUESTS"

				cd ${QUEST_PATH}
				python2.7 pre_qc.py -ac

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		204*)
			m2_start_request "CLEAN"

				clean_quest

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		301*)
			m2_start_request "GAME"

				CHECK_STATE=`ps -c | grep -c game`
				GAME_DEBUG_PATH="${SRC_OUTPUT_PATH}/game_debug"
				GAME_STRIPPED_PATH="${SRC_OUTPUT_PATH}/game_stripped"

				if [ ${CHECK_STATE} -gt 0 ]
				then

					echo -e "       [ \033[35mGAME PROCESS IS RUNNING \033[37m]\033[0m "
					echo -e "       [ \033[35mPLEASE STOP IT \033[37m]\033[0m "
				else

					cd ${SRC_GAME_PATH} && gmake clean_game
					cd ${SRC_GAME_PATH} && gmake game ${FLAG}
					
					sleep 1

					if [ -e ${GAME_DEBUG_PATH} ] || [ -e ${GAME_STRIPPED_PATH}} ]
					then

						if [ ${CONFIGURATION} -eq 0 ]
						then

							cp ${GAME_DEBUG_PATH} ${M2_PATH}/resources/game
							echo -e "       \033[37m[ \033[37mGAME \033[37m] \033[37m[ \033[32mDEBUG GAME REQUEST SUCCESS \033[37m]\033[0m"
						else

							cp ${GAME_STRIPPED_PATH} ${M2_PATH}/resources/game
							echo -e "       \033[37m[ \033[37mGAME \033[37m] \033[37m[ \033[32mRELEASE GAME REQUEST SUCCESS \033[37m]\033[0m"
						fi
					else

						echo -e "       \033[37m[ \033[37mGAME \033[37m] \033[37m[ \033[31mGAME REQUEST FAILED \033[37m]\033[0m"
					fi
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		302*)
			m2_start_request "DB"

				CHECK_STATE=`ps -c | grep -c db`
				DB_DEBUG_PATH="${SRC_OUTPUT_PATH}/db_debug"
				DB_STRIPPED_PATH="${SRC_OUTPUT_PATH}/db_stripped"

				if [ ${CHECK_STATE} -gt 0 ]
				then

					echo -e "       [ \033[35mDB PROCESS IS RUNNING \033[37m]\033[0m "
					echo -e "       [ \033[35mPLEASE STOP IT \033[37m]\033[0m "
				else

					cd ${SRC_DB_PATH} && gmake clean_db
					cd ${SRC_DB_PATH} && gmake db ${FLAG}
					
					sleep 1

					if [ -e ${DB_DEBUG_PATH} ] || [ -e ${DB_STRIPPED_PATH}} ]
					then

						if [ ${CONFIGURATION} -eq 0 ]
						then

							cp ${DB_DEBUG_PATH} ${M2_PATH}/resources/db
							echo -e "       \033[37m[ \033[37mGAME \033[37m] \033[37m[ \033[32mDEBUG DB REQUEST SUCCESS \033[37m]\033[0m"
						else

							cp ${DB_STRIPPED_PATH} ${M2_PATH}/resources/db
							echo -e "       \033[37m[ \033[37mGAME \033[37m] \033[37m[ \033[32mRELEASE DB REQUEST SUCCESS \033[37m]\033[0m"
						fi
					else

						echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[31mDB REQUEST FAILED \033[37m]\033[0m"
					fi
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		303*)
			m2_start_request "QC"

				CHECK_STATE=`ps -c | grep -c qc`
				QC_DEBUG_PATH="${SRC_OUTPUT_PATH}/qc"

				if [ ${CHECK_STATE} -gt 0 ]
				then

					echo -e "       [ \033[35mDB PROCESS IS RUNNING \033[37m]\033[0m "
					echo -e "       [ \033[35mPLEASE STOP IT \033[37m]\033[0m "
				else

					cd ${SRC_QC_PATH} && gmake clean_qc
					cd ${SRC_QC_PATH} && gmake qc ${FLAG}
					
					sleep 1

					if [ -e ${QC_DEBUG_PATH} ]
					then

						if [ ${VERSION_USE} == TRUE ]
						then
							cp ${QC_DEBUG_PATH} ${M2_PATH}/resources/locale/quest/qc
							### Kraizy Full Edition
						else
							cp ${QC_DEBUG_PATH} ${M2_PATH}/resources/locale/france/quest/qc
							### Kraizy Updated Edition
						fi

						echo -e "       \033[37m[ \033[37mQC \033[37m] \033[37m[ \033[32mQC REQUEST SUCCESS \033[37m]\033[0m"
					else

						echo -e "       \033[37m[ \033[37mQC \033[37m] \033[37m[ \033[31mQC REQUEST FAILED \033[37m]\033[0m"
					fi
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		304*)
			m2_start_request "LIBGAME"

				if [ -e ${SRC_PATH} ]
				then

					cd ${SRC_LIBGAME_PATH} && gmake clean_lib
					cd ${SRC_LIBGAME_PATH} && gmake lib ${FLAG}
				else

					echo -e "       \033[37m[ \033[37mM2 SRC SF \033[37m] \033[37m[ \033[31mDOESN'T EXIST OR HASN'T BEEN INSTALLED \033[37m]\033[0m"
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		305*)
			m2_start_request "LIBTHECORE"

				if [ -e ${SRC_PATH} ]
				then

					cd ${SRC_LIBTHECORE_PATH} && gmake clean_lib
					cd ${SRC_LIBTHECORE_PATH} && gmake lib ${FLAG}
				else

					echo -e "       \033[37m[ \033[37mM2 SRC SF \033[37m] \033[37m[ \033[31mDOESN'T EXIST OR HASN'T BEEN INSTALLED \033[37m]\033[0m"
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		306*)
			m2_start_request "LIBLUA"

				if [ -e ${SRC_PATH} ]
				then

					cd ${SRC_LIBLUA_PATH} && gmake clean_lib
					cd ${SRC_LIBLUA_PATH} && gmake lib ${FLAG}
				else

					echo -e "       \033[37m[ \033[37mM2 SRC SF \033[37m] \033[37m[ \033[31mDOESN'T EXIST OR HASN'T BEEN INSTALLED \033[37m]\033[0m"
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		307*)
			m2_start_request "LIBPOLY"

				if [ -e ${SRC_PATH} ]
				then

					cd ${SRC_LIBPOLY_PATH} && gmake clean_lib
					cd ${SRC_LIBPOLY_PATH} && gmake lib ${FLAG}
				else

					echo -e "       \033[37m[ \033[37mM2 SRC SF \033[37m] \033[37m[ \033[31mDOESN'T EXIST OR HASN'T BEEN INSTALLED \033[37m]\033[0m"
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		308*)
			m2_start_request "LIBCRYPTOPP"

				if [ -e ${SRC_PATH} ]
				then

					cd ${SRC_LIBCRYPTOPP_PATH} && gmake clean_lib
					cd ${SRC_LIBCRYPTOPP_PATH} && gmake lib ${FLAG}
				else

					echo -e "       \033[37m[ \033[37mM2 SRC SF \033[37m] \033[37m[ \033[31mDOESN'T EXIST OR HASN'T BEEN INSTALLED \033[37m]\033[0m"
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		309*)
			m2_start_request "LIBSQL"

				if [ -e ${SRC_PATH} ]
				then

					cd ${SRC_LIBSQL_PATH} && gmake clean_lib
					cd ${SRC_LIBSQL_PATH} && gmake lib ${FLAG}
				else

					echo -e "       \033[37m[ \033[37mM2 SRC SF \033[37m] \033[37m[ \033[31mDOESN'T EXIST OR HASN'T BEEN INSTALLED \033[37m]\033[0m"
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		310*)
			m2_start_request "CLEAN"

				if [ -e ${SRC_PATH} ]
				then

					echo -e "       \033[37m[ \033[37mGAME \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_GAME_PATH} && gmake clean
					cd ${SRC_GAME_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_DB_PATH} && gmake clean
					cd ${SRC_DB_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mQC \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_QC_PATH} && gmake clean

					echo -e ""
					echo -e "       \033[37m[ \033[37mLIBGAME \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBGAME_PATH} && gmake clean
					cd ${SRC_LIBGAME_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mLIBLUA \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBLUA_PATH} && gmake clean

					echo -e "       \033[37m[ \033[37mLIBPOLY \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBPOLY_PATH} && gmake clean
					cd ${SRC_LIBPOLY_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mLIBSQL \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBSQL_PATH} && gmake clean
					cd ${SRC_LIBSQL_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mLIBTHECORE \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBTHECORE_PATH} && gmake clean
					cd ${SRC_LIBTHECORE_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mLIBCRYPTOPP \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBCRYPTOPP_PATH} && gmake clean
					cd ${SRC_LIBCRYPTOPP_PATH} && gmake depend
				else

					echo -e "       \033[37m[ \033[37mM2 SRC SF \033[37m] \033[37m[ \033[31mDOESN'T EXIST OR HASN'T BEEN INSTALLED \033[37m]\033[0m"
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		311*)
			m2_start_request "CLEAN"

				if [ -e ${SRC_PATH} ]
				then

					echo -e "       \033[37m[ \033[37mGAME \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_GAME_PATH} && gmake clean
					cd ${SRC_GAME_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mDB \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_DB_PATH} && gmake clean
					cd ${SRC_DB_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mQC \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_QC_PATH} && gmake clean
				else

					echo -e "       \033[37m[ \033[37mM2 SRC SF \033[37m] \033[37m[ \033[31mDOESN'T EXIST OR HASN'T BEEN INSTALLED \033[37m]\033[0m"
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		312*)
			m2_start_request "CLEAN"

				if [ -e ${SRC_PATH} ]
				then

					echo -e "       \033[37m[ \033[37mLIBGAME \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBGAME_PATH} && gmake clean
					cd ${SRC_LIBGAME_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mLIBLUA \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBLUA_PATH} && gmake clean

					echo -e "       \033[37m[ \033[37mLIBPOLY \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBPOLY_PATH} && gmake clean
					cd ${SRC_LIBPOLY_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mLIBSQL \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBSQL_PATH} && gmake clean
					cd ${SRC_LIBSQL_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mLIBTHECORE \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBTHECORE_PATH} && gmake clean
					cd ${SRC_LIBTHECORE_PATH} && gmake depend

					echo -e "       \033[37m[ \033[37mLIBCRYPTOPP \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
					cd ${SRC_LIBCRYPTOPP_PATH} && gmake clean
					cd ${SRC_LIBCRYPTOPP_PATH} && gmake depend
				else

					echo -e "       \033[37m[ \033[37mM2 SRC SF \033[37m] \033[37m[ \033[31mDOESN'T EXIST OR HASN'T BEEN INSTALLED \033[37m]\033[0m"
				fi

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		401*)

			m2_start_request "SYMBOLIC LINKS"
			
				echo -e "       \033[31mComing Soon\033[0m"
			
			m2_end_request

		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		402*)
			m2_start_request "STATE"

				state_db
				state_auth

				for CHANNEL in `seq ${DEFAULT_CORE_MIN} ${DEFAULT_CORE_MAX}`
				do

					init_channel ${CHANNEL}
					state_core ${CHANNEL} 1
					state_core ${CHANNEL} 2
					state_core ${CHANNEL} 3
					state_core ${CHANNEL} 4
					state_core ${CHANNEL} 5
				done

				init_channel 99
				state_core 99 1

			m2_end_request
		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		403*)

			m2_start_request "CHECK INTEGRITY"
			
				echo -e "       \033[31mComing Soon\033[0m"
			
			m2_end_request

		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		404*)

			m2_start_request "KIJARU"
			
				echo -e "       \033[31mI Miss You... <3\033[0m"
			
			m2_end_request

		;;

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

		405*)
			m2_start_request "BACKUP"

				QC_STATE=`ps -c | grep -c qc`
				DB_STATE=`ps -c | grep -c db`
				GAME_STATE=`ps -c | grep -c game`

				if [ ${QC_STATE} -gt 1 ] || [ ${DB_STATE} -gt 1 ] || [ ${GAME_STATE} -gt 1 ]
				then

					echo -e "       [ \033[35mSERVER PROCESS IS RUNNING \033[37m]\033[0m "
					echo -e "       [ \033[35mPLEASE STOP IT \033[37m]\033[0m "
				else

					if [ ! -e ${BACKUP_PATH} ]
					then

						mkdir ${BACKUP_PATH}
					fi

					echo -e "       \033[37m[ \033[37mBACKUP \033[37m] \033[37m[ \033[32mBUILD \033[37m]\033[0m"
					echo -e ""

					FILENAME="$(date +%Y_%m_%d_%H_%M_%S)"
					mkdir ${BACKUP_PATH}/${FILENAME}

					if [ ${VERSION_USE} == TRUE ]
					then
						mysqldump --defaults-extra-file="${CONFIG_PATH}/mysqldump" --default-character-set="UTF8" --set-gtid-purged="OFF" metin2 > "${BACKUP_PATH}/${FILENAME}/M2SQL.sql"
						### Kraizy Full Edition
					else
						mysqldump --defaults-extra-file="${CONFIG_PATH}/mysqldump" --default-character-set="UTF8" --set-gtid-purged="OFF" account > "${BACKUP_PATH}/${FILENAME}/account.sql"
						mysqldump --defaults-extra-file="${CONFIG_PATH}/mysqldump" --default-character-set="UTF8" --set-gtid-purged="OFF" common > "${BACKUP_PATH}/${FILENAME}/common.sql"
						mysqldump --defaults-extra-file="${CONFIG_PATH}/mysqldump" --default-character-set="UTF8" --set-gtid-purged="OFF" player > "${BACKUP_PATH}/${FILENAME}/player.sql"
						mysqldump --defaults-extra-file="${CONFIG_PATH}/mysqldump" --default-character-set="UTF8" --set-gtid-purged="OFF" log > "${BACKUP_PATH}/${FILENAME}/log.sql"
						mysqldump --defaults-extra-file="${CONFIG_PATH}/mysqldump" --default-character-set="UTF8" --set-gtid-purged="OFF" hotbackup > "${BACKUP_PATH}/${FILENAME}/hotbackup.sql"
						### Kraizy Updated Edition
					fi
					
					echo -e "           \033[37m[ \033[37mM2 SQL \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"

					tar cf "${BACKUP_PATH}/${FILENAME}/M2SF_M2SRCSF.tar" "${VERSION}"
					tar uf "${BACKUP_PATH}/${FILENAME}/M2SF_M2SRCSF.tar" "m2sh.sh"

					echo -e "           \033[37m[ \033[37mM2 SF + M2 SRC SF \033[37m] \033[37m[ \033[32mDONE \033[37m]\033[0m"
				fi

			m2_end_request
		;;

		esac

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################
