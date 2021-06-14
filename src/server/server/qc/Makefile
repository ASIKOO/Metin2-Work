MAKE = clang++-devel

LIBS =
FLAGS =
INCDIR =
LIBDIR =
BINDIR = ..
OUTPUT = ../../output
OBJDIR = OBJDIR

FLAGS += -g
FLAGS += -ggdb
FLAGS += -DNDEBUG

FLAGS += -w

INCDIR += -I../liblua/include
INCDIR += -I../liblua/src

LIBDIR += -L../../data/lib

LIBS += -llua
LIBS += -llualib

TARGET_NAME = qc
TARGET = $(OUTPUT)/$(TARGET_NAME)

default:
	@echo -e ""
	@echo -e "\033[0;36m ■\033[0m gmake clean \033[0;36m■\033[0m gmake depend \033[0;36m■\033[0m gmake qc \033[0;36m■\033[0m"
	@echo -e ""

qc: clean_qc qc.cc qc.o crc32.o
	@echo -e "       [ \033[32mGENERATING \033[37m]\033[0m" $(TARGET_NAME)
	@$(MAKE) -g -o $(TARGET) $(INCDIR) $(LIBDIR) qc.o crc32.o $(LIBS)

%.o: %.cc
	@echo -e "       [ \033[36mCOMPILING \033[37m]\033[0m" $<
	@$(MAKE) $(FLAGS) -c $< $(INCDIR) $(LIBDIR)

clean_qc:
	@rm -f $(TARGET)

clean:
	@rm -f qc.o crc32.o $(TARGET)
