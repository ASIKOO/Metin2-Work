
	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

import app
app.ServerName = None

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

SRV_LOCALHOST = {
	'name':'LOCALHOST',
	'host':'127.0.0.1',
	'auth':11002,
	'c1':13001,
	'ids':'10',
}

SRV_LAN = {
	'name':'LAN',
	'host':'192.168.0.26',
	'auth':11002,
	'c1':13001,
	'ids':'20',
}

SRV_WAN = {
	'name':'WAN',
	'host':'82.64.248.79',
	'auth':11002,
	'c1':13001,
	'ids':'30',
}

SRV_KIMSUFI = {
	'name':'KIMSUFI',
	'host':'37.187.100.211',
	'auth':11002,
	'c1':13001,
	'ids':'40',
}

SRV_ONLINE = {
	'name':'ONLINE',
	'host':'51.159.70.28',
	'auth':11002,
	'c1':13001,
	'ids':'50',
}

SRV_METIN2 = {
	'name':'M2 PROJECT',
	'host':'51.159.70.28',
	'auth':11002,
	'c1':13001,
	'c2':13011,
	'c3':13021,
	'ids':'60',
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

SRV_C = {
	'c1':'C1   ',
	'c2':'C2   ',
	'c3':'C3   ',
	'c4':'C4   ',
	'c5':'C5   ',
	'c6':'C6   ',
	'c7':'C7   ',
	'c8':'C8   ',
	'c9':'C9   ',
	'cs':'CS   ',
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

# STATE_NONE = '|cFFBE4520?!'
STATE_NONE = '|cFFC7C7C7?!|r'

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

STATE_DICT = {
	# 0:'|cFFBE4520?!|r',
	0:'|cFFC7C7C7?!|r',
	1:'|cFF8CBE20NORM|r',
	2:'|cFFBE6D20BUSY|r',
	3:'|cFFBE4520FULL|r'
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

SERVER_LOCALHOST_CHANNEL_DICT = {
	1:{
		'key':11,
		'name':SRV_C['c1'],
		'ip':SRV_LOCALHOST['host'],
		'tcp_port':SRV_LOCALHOST['c1'],
		'udp_port':SRV_LOCALHOST['c1'],
		'state':STATE_NONE,
		'count':0
	}
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

SERVER_LAN_CHANNEL_DICT = {
	1:{
		'key':11,
		'name':SRV_C['c1'],
		'ip':SRV_LAN['host'],
		'tcp_port':SRV_LAN['c1'],
		'udp_port':SRV_LAN['c1'],
		'state':STATE_NONE,
		'count':0
	}
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

SERVER_WAN_CHANNEL_DICT = {
	1:{
		'key':21,
		'name':SRV_C['c1'],
		'ip':SRV_WAN['host'],
		'tcp_port':SRV_WAN['c1'],
		'udp_port':SRV_WAN['c1'],
		'state':STATE_NONE,
		'count':0
	}
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

SERVER_KIMSUFI_CHANNEL_DICT = {
	1:{
		'key':31,
		'name':SRV_C['c1'],
		'ip':SRV_KIMSUFI['host'],
		'tcp_port':SRV_KIMSUFI['c1'],
		'udp_port':SRV_KIMSUFI['c1'],
		'state':STATE_NONE,
		'count':0
	}
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

SERVER_ONLINE_CHANNEL_DICT = {
	1:{
		'key':41,
		'name':SRV_C['c1'],
		'ip':SRV_ONLINE['host'],
		'tcp_port':SRV_ONLINE['c1'],
		'udp_port':SRV_ONLINE['c1'],
		'state':STATE_NONE,
		'count':0
	}
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

SERVER_METIN2_CHANNEL_DICT = {
	1:{
		'key':51,
		'name':SRV_C['c1'],
		'ip':SRV_METIN2['host'],
		'tcp_port':SRV_METIN2['c1'],
		'udp_port':SRV_METIN2['c1'],
		'state':STATE_NONE,
		'count':0
	},
	2:{
		'key':52,
		'name':SRV_C['c2'],
		'ip':SRV_METIN2['host'],
		'tcp_port':SRV_METIN2['c2'],
		'udp_port':SRV_METIN2['c2'],
		'state':STATE_NONE,
		'count':0
	},
	3:{
		'key':53,
		'name':SRV_C['c3'],
		'ip':SRV_METIN2['host'],
		'tcp_port':SRV_METIN2['c3'],
		'udp_port':SRV_METIN2['c3'],
		'state':STATE_NONE,
		'count':0
	}
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

REGION_NAME_DICT = {
	0:'TAIWAN'
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

REGION_AUTH_SERVER_DICT = {
	0:{
		1:{
			'ip':SRV_LOCALHOST['host'],
			'port':SRV_LOCALHOST['auth']
		},
		2:{
			'ip':SRV_LAN['host'],
			'port':SRV_LAN['auth']
		},
		3:{
			'ip':SRV_WAN['host'],
			'port':SRV_WAN['auth']
		},
		4:{
			'ip':SRV_KIMSUFI['host'],
			'port':SRV_KIMSUFI['auth']
		},
		5:{
			'ip':SRV_ONLINE['host'],
			'port':SRV_ONLINE['auth']
		},
		6:{
			'ip':SRV_METIN2['host'],
			'port':SRV_METIN2['auth']
		}
	}
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

REGION_DICT = {
	0:{
		1:{
			'name':SRV_LOCALHOST['name'],
			'channel':SERVER_LOCALHOST_CHANNEL_DICT
		},
		2:{
			'name':SRV_LAN['name'],
			'channel':SERVER_LAN_CHANNEL_DICT
		},
		3:{
			'name':SRV_WAN['name'],
			'channel':SERVER_WAN_CHANNEL_DICT
		},
		4:{
			'name':SRV_KIMSUFI['name'],
			'channel':SERVER_KIMSUFI_CHANNEL_DICT
		},
		5:{
			'name':SRV_ONLINE['name'],
			'channel':SERVER_ONLINE_CHANNEL_DICT
		},
		6:{
			'name':SRV_METIN2['name'],
			'channel':SERVER_METIN2_CHANNEL_DICT
		}
	}
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################

MARKADDR_DICT = {
	10:{
		'ip':SRV_LOCALHOST['host'],
		'tcp_port':SRV_LOCALHOST['c1'],
		'mark':SRV_LOCALHOST['ids'] + '.tga',
		'symbol_path':SRV_LOCALHOST['ids']
	},
	20:{
		'ip':SRV_LAN['host'],
		'tcp_port':SRV_LAN['c1'],
		'mark':SRV_LAN['ids'] + '.tga',
		'symbol_path':SRV_LAN['ids']
	},
	30:{
		'ip':SRV_WAN['host'],
		'tcp_port':SRV_WAN['c1'],
		'mark':SRV_WAN['ids'] + '.tga',
		'symbol_path':SRV_WAN['ids']
	},
	40:{
		'ip':SRV_KIMSUFI['host'],
		'tcp_port':SRV_KIMSUFI['c1'],
		'mark':SRV_KIMSUFI['ids'] + '.tga',
		'symbol_path':SRV_KIMSUFI['ids']
	},
	50:{
		'ip':SRV_ONLINE['host'],
		'tcp_port':SRV_ONLINE['c1'],
		'mark':SRV_ONLINE['ids'] + '.tga',
		'symbol_path':SRV_ONLINE['ids']
	},
	60:{
		'ip':SRV_METIN2['host'],
		'tcp_port':SRV_METIN2['c1'],
		'mark':SRV_METIN2['ids'] + '.tga',
		'symbol_path':SRV_METIN2['ids']
	}
}

	################################################################################
	##	 																		  ##
	##	 8b    d8 oP"Yb.     88""Yb 88""Yb  dP"Yb   88888 888888  dP""b8 888888	  ##
	##	 88b  d88 "' dP'     88__dP 88__dP dP   Yb     88 88__   dP   `"   88	  ##
	##	 88YbdP88   dP'      88"""  88"Yb  Yb   dP o.  88 88""   Yb        88	  ##
	##	 88 YY 88 .d8888     88     88  Yb  YbodP  "bodP' 888888  YboodP   88	  ##
	##	 																		  ##
	################################################################################
