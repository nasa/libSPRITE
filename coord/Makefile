NAMESPACE:=coord
SRC:=GST_angle.cpp

TEST_SRC:=ECI_ut.cpp \

TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

SP:=../
CFLAGS+=-I./

#Only one of the two options below should be enabled
CFLAGS+=-O2   # Standard compile
#CFLAGS+=-fprofile-arcs -ftest-coverage    # Compile for code coverage

CPPFLAGS+=-DXPRINT_LOCATION #-DPRINT_DEBUG
LDFLAGS+=-lSPRITE_math -lSPRITE_units -ldl

include $(SP)rules.mk
