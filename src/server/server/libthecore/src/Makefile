CC = clang++-devel

LIBS =
FLAGS =
INCDIR =
OUTPUT = ../../../data/lib

TARGET_NAME = libthecore.a
TARGET = $(OUTPUT)/$(TARGET_NAME)

INCDIR = -I../include

# FLAGS += -g
FLAGS += -w
FLAGS += -Wall
FLAGS += -O2
# FLAGS += -m32
FLAGS += -pipe
# FLAGS += -fexceptions
# FLAGS += -D_THREAD_SAFE
# FLAGS += -mcpu=i686
FLAGS += -march=native
# FLAGS += -DNDEBUG
# FLAGS += -fstack-protector-all
# FLAGS += -std=c++11

OBJFILES = socket.o fdwatch.o buffer.o signal.o log.o utils.o kstbl.o hangul.o heart.o main.o tea.o des.o gost.o memcpy.o

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
	@$(CC) $(FLAGS) $(INCDIR)  -MM *.c > Depend

$(OBJFILES):
	@echo -e "       [ \033[36mCOMPILING \033[37m]\033[0m" $<
	@$(CC) $(FLAGS) $(INCDIR) -c $<

memcpy: memcpy.o utils.o log.o
	@$(CC) $(FLAGS) $(INCDIR) -c -D__MAIN__ memcpy.c
	@$(CC) $(FLAGS) $(INCDIR) -o memcpy memcpy.o utils.o log.o

include Depend
