NAMESPACE:=SCALE

LUAINCPATH:=/usr/local/include
LUALIB:=lua

SRC:=Scale_if.cpp \
     Nest.cpp

TEST_SRC:=Scale_if_ut.cpp \
          Test_task.cpp

TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

CFLAGS=-O2 -I$(LUAINCPATH) #-DXPRINT_LOCATION -DPRINT_DEBUG
LDFLAGS+=-lSPRITE_SRTX -lSPRITE_units -lrt -lpthread -l$(LUALIB) -ldl

EXTRA_LIB:=scheduler.lua

SP:=../
include $(SP)rules.mk
