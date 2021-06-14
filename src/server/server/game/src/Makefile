CC = clang++-devel

LIBS =
FLAGS =
INCDIR =
LIBDIR =
BINDIR = ..
OBJDIR = OBJDIR
OUTPUT = ../../../output
USE_STACKTRACE = 0

TARGET_NAME = game_debug
TEST_TARGET_NAME = game_stripped
TARGET = $(OUTPUT)/$(TARGET_NAME)
TEST_TARGET = $(OUTPUT)/$(TEST_TARGET_NAME)

FLAGS += -g
FLAGS += -ggdb
FLAGS += -DNDEBUG
FLAGS += -w
FLAGS += -Wall
#FLAGS += -O2
FLAGS += -pipe
FLAGS += -fexceptions
FLAGS += -D_THREAD_SAFE
FLAGS += -march=native
FLAGS += -fstack-protector-all
FLAGS += -std=c++14
FLAGS += -DBOOST_ERROR_CODE_HEADER_ONLY
FLAGS += -ferror-limit=1

INCDIR += -I../../../data/boost_1_50_0
INCDIR += -I../../../data/libdevil_1_7_8
INCDIR += -I../../../data/mysql_8_0_20
INCDIR += -I../../../data/cryptopp_8_2_0
INCDIR += -I../../liblua/include
INCDIR += -I/usr/local/include
# INCDIR += -L/usr/local/lib/mysql

# LIBDIR += -L../../../data/libdevil_1_7_8
LIBDIR += -L../../../data/lib
LIBDIR += -L/usr/local/lib/mysql
LIBDIR += -L/usr/local/lib

LIBS += -pthread
LIBS += -lm
LIBS += -lmd
LIBS += -lIL
LIBS += -lpng
LIBS += -ltiff
LIBS += -lmng
LIBS += -llcms
LIBS += -ljpeg
LIBS += -lmysqlclient
LIBS += -lz
LIBS += -lcryptopp
LIBS += -lthecore
LIBS += -lpoly
LIBS += -llua
LIBS += -llualib
LIBS += -lsql
LIBS += -lgame

ifeq ($(USE_STACKTRACE), 1)
LIBS += /usr/local/lib/libexecinfo.a
endif

CFILE = \
	minilzo.c\

CPPFILE = \
	BattleArena.cpp\
	FSM.cpp\
	MarkConvert.cpp\
	MarkImage.cpp\
	MarkManager.cpp\
	OXEvent.cpp\
	TrafficProfiler.cpp\
	ani.cpp\
	arena.cpp\
	banword.cpp\
	battle.cpp\
	blend_item.cpp\
	block_country.cpp\
	buffer_manager.cpp\
	building.cpp\
	castle.cpp\
	char.cpp\
	char_affect.cpp\
	char_battle.cpp\
	char_change_empire.cpp\
	char_horse.cpp\
	char_item.cpp\
	char_manager.cpp\
	char_quickslot.cpp\
	char_resist.cpp\
	char_skill.cpp\
	char_state.cpp\
	PetSystem.cpp\
	cmd.cpp\
	cmd_emotion.cpp\
	cmd_general.cpp\
	cmd_gm.cpp\
	cmd_oxevent.cpp\
	config.cpp\
	constants.cpp\
	crc32.cpp\
	cube.cpp\
	db.cpp\
	desc.cpp\
	desc_client.cpp\
	desc_manager.cpp\
	desc_p2p.cpp\
	dev_log.cpp\
	dungeon.cpp\
	empire_text_convert.cpp\
	entity.cpp\
	entity_view.cpp\
	event.cpp\
	event_queue.cpp\
	exchange.cpp\
	file_loader.cpp\
	fishing.cpp\
	gm.cpp\
	guild.cpp\
	guild_manager.cpp\
	guild_war.cpp\
	horse_rider.cpp\
	horsename_manager.cpp\
	input.cpp\
	input_auth.cpp\
	input_db.cpp\
	input_login.cpp\
	input_main.cpp\
	input_p2p.cpp\
	input_teen.cpp\
	input_udp.cpp\
	ip_ban.cpp\
	item.cpp\
	item_addon.cpp\
	item_attribute.cpp\
	item_manager.cpp\
	item_manager_idrange.cpp\
	locale.cpp\
	locale_service.cpp\
	log.cpp\
	login_data.cpp\
	lzo_manager.cpp\
	marriage.cpp\
	matrix_card.cpp\
	messenger_manager.cpp\
	mining.cpp\
	mob_manager.cpp\
	monarch.cpp\
	motion.cpp\
	over9refine.cpp\
	p2p.cpp\
	packet_info.cpp\
	party.cpp\
	passpod.cpp\
	pcbang.cpp\
	polymorph.cpp\
	priv_manager.cpp\
	pvp.cpp\
	questevent.cpp\
	questlua.cpp\
	questlua_affect.cpp\
	questlua_arena.cpp\
	questlua_ba.cpp\
	questlua_building.cpp\
	questlua_danceevent.cpp\
	questlua_dungeon.cpp\
	questlua_forked.cpp\
	questlua_game.cpp\
	questlua_global.cpp\
	questlua_guild.cpp\
	questlua_horse.cpp\
	questlua_pet.cpp\
	questlua_item.cpp\
	questlua_marriage.cpp\
	questlua_mgmt.cpp\
	questlua_monarch.cpp\
	questlua_npc.cpp\
	questlua_oxevent.cpp\
	questlua_party.cpp\
	questlua_pc.cpp\
	questlua_quest.cpp\
	questlua_target.cpp\
	questmanager.cpp\
	questnpc.cpp\
	questpc.cpp\
	refine.cpp\
	regen.cpp\
	safebox.cpp\
	sectree.cpp\
	sectree_manager.cpp\
	sequence.cpp\
	shop.cpp\
	skill.cpp\
	start_position.cpp\
	target.cpp\
	text_file_loader.cpp\
	trigger.cpp\
	utils.cpp\
	vector.cpp\
	war_map.cpp\
	wedding.cpp\
	xmas_event.cpp\
	panama.cpp\
	threeway_war.cpp\
	map_location.cpp\
	auth_brazil.cpp\
	BlueDragon.cpp\
	BlueDragon_Binder.cpp\
	DragonLair.cpp\
	questlua_dragonlair.cpp\
	skill_power.cpp\
	affect.cpp\
	SpeedServer.cpp\
	questlua_speedserver.cpp\
	auction_manager.cpp\
	FileMonitor_FreeBSD.cpp\
	ClientPackageCryptInfo.cpp\
	cipher.cpp\
	buff_on_attributes.cpp\
	dragon_soul_table.cpp\
	DragonSoul.cpp\
	group_text_parse_tree.cpp\
	char_dragonsoul.cpp\
	questlua_dragonsoul.cpp\
	shop_manager.cpp\
	shopEx.cpp\
	item_manager_read_tables.cpp\

COBJS = $(CFILE:%.c=$(OBJDIR)/%.o)
CPPOBJS = $(CPPFILE:%.cpp=$(OBJDIR)/%.o)

MAINOBJ = $(OBJDIR)/main.o
MAINCPP = main.cpp

default:
	@echo -e ""
	@echo -e "\033[0;36m ■\033[0m gmake clean \033[0;36m■\033[0m gmake depend \033[0;36m■\033[0m gmake game \033[0;36m■\033[0m"
	@echo -e ""

game: clean_game $(TARGET) $(TEST_TARGET)
	@strip $(TEST_TARGET)

$(OBJDIR)/minilzo.o: minilzo.c
	@$(CC) $(FLAGS) $(INCDIR) -c $< -o $@
	@echo -e "       [ \033[36mCOMPILING \033[37m]\033[0m" $<

$(OBJDIR)/%.o: %.cpp
	@echo -e "       [ \033[36mCOMPILING \033[37m]\033[0m" $<
	@$(CC) $(FLAGS) $(INCDIR) -c $< -o $@

$(TARGET): $(CPPOBJS) $(COBJS) $(MAINOBJ)
	@echo -e "       [ \033[32mGENERATING \033[37m]\033[0m" $(TARGET_NAME)
	@$(CC) $(FLAGS) $(LIBDIR) $(COBJS) $(CPPOBJS) $(MAINOBJ) $(LIBS) -o $(TARGET) -g

$(TEST_TARGET): $(CPPOBJS) $(COBJS) $(MAINOBJ)
	@echo -e "       [ \033[32mGENERATING \033[37m]\033[0m" $(TEST_TARGET_NAME)
	@$(CC) $(FLAGS) -Wl, -s $(LIBDIR) $(COBJS) $(CPPOBJS) $(MAINOBJ) $(LIBS) -o $(TEST_TARGET)

clean_game:
	@rm -f $(TARGET) $(TEST_TARGET)

clean:
	@rm -f $(COBJS) $(CPPOBJS) $(MAINOBJ) $(TARGET) $(TEST_TARGET)

depend:
	@makedepend -f Depend $(INCDIR) -I/usr/include/c++/3.3 -I/usr/include/c++/4.2 -p$(OBJDIR)/ $(CPPFILE) $(CFILE) $(MAINCPP) $(TESTCPP) 2> /dev/null > Depend

sinclude Depend
