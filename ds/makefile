OBJ_DIR := ./obj/
LIB_DIR := ./lib/
SRC_DIR := ./src/
TEST_DIR := ./test/
INCLUDE_DIR := ./include/
DEPS_DIR := $(OBJ_DIR).deps/
#distinguish between debug and release
DEBUG_MODE = debug
RELEASE_MODE = release
# helper and dependencies variables
SRCS_HELPER := $(wildcard $(SRC_DIR)*.c)
SRCS += $(foreach var, $(SRCS_HELPER), $(notdir $(var)))

OBJS_HELPER_DEBUG += $(foreach var, $(SRCS), $(var:%.c=$(DEBUG_MODE)%.o))
OBJS_DEBUG += $(foreach var, $(OBJS_HELPER_DEBUG), $(var:%=$(OBJ_DIR)%))

OBJS_HELPER_RELEASE += $(foreach var, $(SRCS), $(var:%.c=$(RELEASE_MODE)%.o))
OBJS_RELEASE += $(foreach var, $(OBJS_HELPER_RELEASE), $(var:%=$(OBJ_DIR)%))

TEST_SRC_HELPER := $(wildcard $(TEST_DIR)*.c)
TEST_SRCS += $(foreach var, $(TEST_SRC_HELPER), $(notdir $(var)))

EXE_FILES += $(foreach var, $(TEST_SRCS), $(var:%.c=%.out))

#compilation flags
CFLAGS_RELEASE := -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3  -I ./include
CFLAGS_DEBUG = -ansi -pedantic-errors -Wall -Wextra -g -I ./include
#preproccessor flags - to generate the dependencies files
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.d  
#linker flags 
LDFLAGS := -L /home/ariel/infinitylabs/git/ds/lib -Wl,-rpath=/home/ariel/infinitylabs/git/ds/lib

#for makefile debugging purposes - see variables
.PHONY:print
print: ;@echo $($(NAME))

# create release and debug shared objects
.PHONY: all
all: debug release
#create executable with the debug shared object
.PHONY: test
test: $(EXE_FILES)

%.out: $(OBJ_DIR)%.o $(DEPS_DIR)%.d $(LIB_DIR)libdebug.so | $(DEPS_DIR)
	$(CC) $(LDFLAGS) -o $@ $< -ldebug

$(OBJ_DIR)%.o : $(TEST_DIR)%.c $(DEPS_DIR)%.d | $(DEPS_DIR)
	$(CC) $(CFLAGS_DEBUG) $(DEPFLAGS) -c $< -o $@
# create debug shared object
.PHONY: debug
debug: $(LIB_DIR)libdebug.so

$(LIB_DIR)libdebug.so: $(OBJS_DEBUG)
	$(CC) -shared -o $@ $(OBJS_DEBUG)

$(OBJ_DIR)$(DEBUG_MODE)%.o : $(SRC_DIR)%.c $(DEPS_DIR)%.d | $(DEPS_DIR)
	$(CC) $(CFLAGS_DEBUG) -fPIC $(DEPFLAGS) -c $< -o $@
# create release shared object
.PHONY: release
release: $(LIB_DIR)librelease.so

$(LIB_DIR)librelease.so: $(OBJS_RELEASE)
	$(CC) -shared -o $@ $(OBJS_RELEASE)

$(OBJ_DIR)$(RELEASE_MODE)%.o : $(SRC_DIR)%.c $(DEPS_DIR)%.d | $(DEPS_DIR)
	$(CC) $(CFLAGS_RELEASE) -fPIC $(DEPFLAGS) -c $< -o $@

#create dependencies directory if necessary. 
$(DEPS_DIR): ; @mkdir -p $@
DEPFILES := $(SRCS:%.c=$(DEPS_DIR)%.d)
TEST_DEPFILES := $(TEST_SRCS:%.c=$(DEPS_DIR)%.d)
#note - the empty depfiles rule purpose is to let 
#the make know depfiles exist, so it can be included later. 
$(DEPFILES):

include $(wildcard $(DEPFILES))

$(TEST_DEPFILES):
# the include appends the depfiles so they will be part of the makefile
include $(wildcard $(TEST_DEPFILES))

# Clean all files
.PHONY: clean 
clean: 
	$(RM) $(LIB_DIR)*.so $(OBJ_DIR)*.o $(DEPS_DIR)*.d ./*.out

