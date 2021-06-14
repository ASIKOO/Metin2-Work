CC = clang++-devel

LIBS =
FLAGS =
INCDIR =
LIBDIR =
BINDIR = ..
OBJDIR = OBJDIR
OUTPUT = ../../data/lib

TARGET_NAME = libpoly.a
TARGET = $(OUTPUT)/$(TARGET_NAME)

# FLAGS += -g
FLAGS += -w
FLAGS += -Wall
FLAGS += -O2
# FLAGS += -m32
FLAGS += -pipe
# FLAGS += -fexceptions
FLAGS += -fno-exceptions
# FLAGS += -D_THREAD_SAFE
# FLAGS += -mcpu=i686
FLAGS += -march=native
FLAGS += -D_GLIBCXX_USE_CXX11_ABI=1
# FLAGS += -DNDEBUG
# FLAGS += -fstack-protector-all
# FLAGS += -std=c++11
FLAGS += -fno-rtti

OBJFILES = Base.o Poly.o SymTable.o Symbol.o

default:
	@echo -e ""
	@echo -e "\033[0;36m ■\033[0m gmake clean \033[0;36m■\033[0m gmake depend \033[0;36m■\033[0m gmake lib \033[0;36m■\033[0m"
	@echo -e ""

lib: clean_lib $(TARGET)

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
	@$(CC) $(FLAGS) -MM *.cc > Depend

$(OBJFILES):
	@echo -e "       [ \033[36mCOMPILING \033[37m]\033[0m" $<
	@$(CC) $(FLAGS) -c $<

include Depend

