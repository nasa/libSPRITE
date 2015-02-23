NAMESPACE:=SCALE
SRC:=Scale_if.cpp \
     Nest.cpp

TEST_SRC:=Scale_if_ut.cpp \
          Test_task.cpp

TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

CFLAGS=-O2 -I/usr/include/lua5.2 #-DXPRINT_LOCATION -DPRINT_DEBUG
LDFLAGS+=-lSPRITE_SRTX -lSPRITE_units -lrt -lpthread -llua5.2 -ldl

EXTRA_LIB:=scheduler.lua

SP:=../
include $(SP)rules.mk
