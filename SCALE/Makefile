NAMESPACE:=SCALE

LUA_INCLUDE:=/usr/local/include
LUA_LIB:=lua

SRC:=Scale_if.cpp \
     Nest.cpp

TEST_SRC:=Scale_if_ut.cpp \
          Test_task.cpp

TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

CFLAGS=-O2 -I$(LUA_INCLUDE) #-DXPRINT_LOCATION -DPRINT_DEBUG
LDFLAGS+=-lSPRITE_SRTX -lSPRITE_units -lrt -lpthread -l$(LUA_LIB) -ldl

EXTRA_LIB:=scheduler.lua

SP:=../
include $(SP)rules.mk
