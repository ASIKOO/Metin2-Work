CC = clang++-devel

INCDIR =
LIBDIR =
BINDIR = ..
OBJDIR = OBJDIR
OUTPUT = ../../../output

TARGET_NAME = db_debug
TEST_TARGET_NAME = db_stripped

TARGET = $(OUTPUT)/$(TARGET_NAME)
TEST_TARGET = $(OUTPUT)/$(TEST_TARGET_NAME)

FLAGS += -g
FLAGS += -ggdb
FLAGS += -DNDEBUG

FLAGS += -w
FLAGS += -Wall
FLAGS += -O2
FLAGS += -fno-rtti
FLAGS += -pipe
FLAGS += -fno-exceptions
FLAGS += -D_THREAD_SAFE
FLAGS += -march=native
# FLAGS += -std=c++11
FLAGS += -std=c++2a

INCDIR += -I../../../data/boost_1_50_0
INCDIR += -I../../../data/mysql_8_0_20

LIBDIR += -L../../../data/lib
LIBDIR += -L/usr/local/lib/mysql

LIBS += -lmysqlclient
LIBS += -lthecore
LIBS += -lpoly
LIBS += -lz
LIBS += -lsql
LIBS += -lgame
LIBS += -pthread
LIBS += -lm

SRCS = \
	Config.cpp\
	NetBase.cpp\
	Peer.cpp\
	PeerBase.cpp\
	Main.cpp\
	Lock.cpp\
	DBManager.cpp\
	Cache.cpp\
	LoginData.cpp\
	ClientManager.cpp\
	ClientManagerPlayer.cpp\
	ClientManagerLogin.cpp\
	ClientManagerBoot.cpp\
	ClientManagerParty.cpp\
	ClientManagerGuild.cpp\
	GuildManager.cpp\
	HB.cpp\
	PrivManager.cpp\
	MoneyLog.cpp\
	ItemAwardManager.cpp\
	ClientManagerEventFlag.cpp\
	Marriage.cpp\
	Monarch.cpp\
	BlockCountry.cpp\
	ItemIDRangeManager.cpp\
	ClientManagerHorseName.cpp\
	AuctionManager.cpp\
	ProtoReader.cpp\
	CsvReader.cpp\

OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

default:
	@echo -e ""
	@echo -e "\033[0;36m ■\033[0m gmake clean \033[0;36m■\033[0m gmake depend \033[0;36m■\033[0m gmake db \033[0;36m■\033[0m"
	@echo -e ""

db: clean_db $(TARGET) $(TEST_TARGET)
	@strip $(TEST_TARGET) 

$(TARGET): $(OBJS)
	@echo -e "       [ \033[32mGENERATING \033[37m]\033[0m" $(TARGET_NAME)
	@$(CC) $(FLAGS) $(LIBDIR) $(OBJS) $(LIBS) -o $(TARGET)

$(TEST_TARGET): $(OBJS)
	@echo -e "       [ \033[32mGENERATING \033[37m]\033[0m" $(TEST_TARGET_NAME)
	@$(CC) $(FLAGS) $(LIBDIR) $(OBJS) $(LIBS) -o $(TEST_TARGET)

$(OBJDIR)/%.o: %.cpp
	@echo -e "       [ \033[36mCOMPILING \033[37m]\033[0m" $<
	@$(CC) $(FLAGS) $(INCDIR) -c $< -o $@

clean_db:
	@rm -f $(TARGET) $(TEST_TARGET)

clean:
	@rm -f $(OBJS) $(TARGET) $(TEST_TARGET)

depend:
	@touch Depend
	@makedepend -fDepend $(INCDIR) -I/usr/include/c++/3.3 -I/usr/include/c++/4.2 -p$(OBJDIR)/ $(SRCS) 2> /dev/null

sinclude Depend
