OBJDIR := ./obj/
LIBDIR := ./lib/
SRCDIR := ./src/
TESTDIR := ./test/
INCLUDEDIR := ./include/

DEBUG_MODE = debug
RELEASE_MODE = release

SRCS_HELPER := $(wildcard $(SRCDIR)*.c)
SRCS += $(foreach var, $(SRCS_HELPER), $(notdir $(var)))

OBJS_HELPER_DEBUG += $(foreach var, $(SRCS), $(var:%.c=$(DEBUG_MODE)%.o))
OBJS_DEBUG += $(foreach var, $(OBJS_HELPER_DEBUG), $(var:%=$(OBJDIR)%))

OBJS_HELPER_RELEASE += $(foreach var, $(SRCS), $(var:%.c=$(RELEASE_MODE)%.o))
OBJS_RELEASE += $(foreach var, $(OBJS_HELPER_RELEASE), $(var:%=$(OBJDIR)%))

TEST_SRC_HELPER := $(wildcard $(TESTDIR)*.c)

EXE_FILES_HELPER += $(foreach var, $(SRCS), $(var:.c=))
EXE_FILES := $(filter-out task, $(EXE_FILES_HELPER))

CFLAGS_RELEASE := -ansi -pedantic-errors -Wall -Wextra -DNDBUG -O3 -I ./include
CFLAGS_DEBUG = -ansi -pedantic-errors -Wall -Wextra -g -I ./include

LDFLAGS = -L /home/ariel/infinitylabs/git/ds/libs -Wl,-rpath=/home/ariel/infinitylabs/git/ds/libs

DEPDIR := $(OBJDIR)./deps
DEPFILES := $(SRCS:%.c=$(DEPDIR)/%.d)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)$*.d



$(DEPDIR): ; @mkdir -p $@
	
$(DEPFILES):

include $(wildcard $(DEPFILES))
