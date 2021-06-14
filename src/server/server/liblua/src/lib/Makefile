LUA = ../..

include $(LUA)/config

EXTRA_DEFS = $(POPEN) $(TMPNAM) $(DEGREES) $(LOADLIB)

OBJS = \
	lauxlib.o\
	lbaselib.o\
	ldblib.o\
	liolib.o\
	lmathlib.o\
	ltablib.o\
	lstrlib.o\
	loadlib.o\

SRCS = \
	lauxlib.c\
	lbaselib.c\
	ldblib.c\
	liolib.c\
	lmathlib.c\
	ltablib.c\
	lstrlib.c\
	loadlib.c\

OUTPUT = ../../../../data/lib

TARGET_NAME = liblualib.a
TARGET = $(OUTPUT)/$(TARGET_NAME)

lib: clean_lib $(TARGET)



%.o: %.c
	@echo -e "       [ \033[36mCOMPILING \033[37m]\033[0m" $<
	@$(CC) $(CFLAGS) $(INCDIR) -c $<





$(TARGET): $(OBJS)
	@echo -e "       [ \033[32mGENERATING \033[37m]\033[0m" $(TARGET_NAME)
	@$(AR) $@ $(OBJS)
	@$(RANLIB) $@

clean_lib:
	@rm -f $(TARGET)

clean:
	@rm -f $(OBJS) $(TARGET)

co:
	@co -q -f -M $(SRCS)

klean:	clean
	@rm -f $(SRCS)
