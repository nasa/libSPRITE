BASEDIR=$(SP)
PREFIX=/usr/local
INCLUDEDIR=$(PREFIX)/include/SPRITE
INCLUDEINSTALLDIR:=$(INCLUDEDIR)/$(NAMESPACE)
LIBDIR=$(PREFIX)/lib/SPRITE
BINDIR=$(PREFIX)/bin

CC:=gcc
CPP:=g++
LD:=g++
AR:=ar

CFLAGS+=-Wall -Wextra -Wparentheses -Wuninitialized -Wcomment -Wformat -Weffc++ -fPIC -I$(BASEDIR) $(USER_CFLAGS)
CPPFLAGS+=$(CFLAGS) $(USER_CPPFLAGS)
LDFLAGS+=-L$(LIBDIR) $(USER_LDFLAGS)

SYSTEM:=$(shell uname)
ARCH:=$(shell uname -m)

HEADERS:=$(shell ls *\.h 2>/dev/null | grep -s -v _ut\.h)
HEADERS+=$(shell ls *\.hpp 2>/dev/null)

OBJS:=$(patsubst %.cpp, %.o, $(SRC))
DEPS:=$(patsubst %.cpp, %.d, $(SRC))
OBJS:=$(OBJS:%.c=%.o)
DEPS:=$(DEPS:%.c=%.d)

TEST_OBJS:=$(patsubst %.cpp, %.o, $(TEST_SRC))
TEST_DEPS+=$(patsubst %.cpp, %.d, $(TEST_SRC))

ifeq ($(TGTTYPE), static_lib)
TGT:=lib$(TGT).a
TGTINSTALLDIR:=$(LIBDIR)
endif

ifeq ($(TGTTYPE), application)
LDFLAGS+=-ldl -lpthread
TGTINSTALLDIR:=$(BINDIR)
endif

.PHONY:all test install uninstall clean $(SUBDIRS)

all: TARGET:=all
all: $(SUBDIRS) $(OBJS) $(TGT)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

%.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

%.d:%.cpp
	$(CPP) -MM $(CPPFLAGS) -MT $*.o $< -o $@

TEST_DRIVER:=run_test
test: TARGET:=test
test: CPPFLAGS+=-DASSERT_THROWS_EXCEPTION
test: $(SUBDIRS) $(TEST_OBJS) $(TEST_DRIVER)

$(TEST_DRIVER): $(BASEDIR)test_harness.cpp $(TEST_OBJS) $(OBJS)
ifdef TEST_OBJS
	$(CPP) $< -o $@ $(CPPFLAGS) $(TEST_OBJS) $(OBJS) $(TESTDEPS) $(LDFLAGS) \
              -lcppunit
endif

install: all
	-mkdir -p $(INCLUDEINSTALLDIR)
ifneq (, $(strip $(HEADERS)))
	-install $(HEADERS) $(INCLUDEINSTALLDIR)
else
	@echo "No headers to install in this directory"
endif
ifdef TGTINSTALLDIR
	-mkdir -p $(TGTINSTALLDIR)
	-install $(TGT) $(TGTINSTALLDIR)
	-$(foreach lib,$(EXTRA_LIB), install $(lib) $(TGTINSTALLDIR);)
endif

uninstall: $(SUBDIRS)
	-rm -rf $(INCLUDEINSTALLDIR)
ifdef TGTINSTALLDIR
	-rm -f $(TGTINSTALLDIR)/$(TGT)
	-$(foreach lib,$(EXTRA_LIB), rm -f $(TGTINSTALLDIR)/$(lib);)
endif

clean: TARGET:=clean
clean: $(SUBDIRS)
	rm -f $(OBJS) $(DEPS) $(TEST_OBJS) $(TEST_DEPS) $(TGT) $(TEST_DRIVER) \
          $(EXTRA_CLEAN) *.stackdump *~

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
-include $(TEST_DEPS)
endif
