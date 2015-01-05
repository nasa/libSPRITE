NAMESPACE:=DEM
SRC:=DEM.cpp

TEST_SRC:=DEM_timestamp_ut.cpp \
          DEM_header_ut.cpp \
          DEM_ut.cpp


TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

CPPFLAGS+=-DXPRINT_LOCATION #-DPRINT_DEBUG
LDFLAGS+=-lSPRITE_units

SP:=../
include $(SP)rules.mk
