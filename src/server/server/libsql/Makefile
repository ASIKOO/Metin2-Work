CC = clang++-devel

LIBS =
FLAGS =
INCDIR =
LIBDIR =
BINDIR = ..
OBJDIR = OBJDIR
OUTPUT = ../../data/lib

TARGET_NAME = libsql.a
TARGET = $(OUTPUT)/$(TARGET_NAME)

INCDIR += -I../../data/mysql_8_0_20

# FLAGS += -g
FLAGS += -w
FLAGS += -Wall
FLAGS += -O2
# FLAGS += -m32
FLAGS += -pipe
# FLAGS += -fexceptions
FLAGS += -D_GLIBCXX_USE_CXX11_ABI=1
FLAGS += -fno-exceptions
FLAGS += -D_THREAD_SAFE
# FLAGS += -mcpu=i686
FLAGS += -march=native
# FLAGS += -DNDEBUG
# FLAGS += -fstack-protector-all
# FLAGS += -std=c++11

OBJFILES = AsyncSQL.o Semaphore.o Tellwait.o Statement.o

default:
	@echo -e ""
	@echo -e "\033[0;36m ■\033[0m gmake clean \033[0;36m■\033[0m gmake depend \033[0;36m■\033[0m gmake lib \033[0;36m■\033[0m"
	@echo -e ""

lib: clean_lib
	@$(MAKE) -s $(TARGET)

$(TARGET): $(OBJFILES)
	@echo -e "       [ \033[32mGENERATING \033[37m]\033[0m" $(TARGET_NAME)
	@ar cru $(TARGET) $(OBJFILES) $(LIBS)
	@ranlib $(TARGET)
	@chmod 700 $(TARGET)

clean_lib:
	@rm -f $(TARGET)

clean:
	@rm -f *.o $(TARGET)

depend:
	@touch Depend
	@$(CC) $(FLAGS) $(INCDIR) -MM *.cpp > Depend

$(OBJFILES):
	@echo -e "       [ \033[36mCOMPILING \033[37m]\033[0m" $<
	@$(CC) $(FLAGS) $(INCDIR) -c $<

include Depend
