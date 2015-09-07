
NAMESPACE:=util

SRC:=Serial_buffer.cpp \
     Smooth.cpp

TEST_SRC:=Linked_list_ut.cpp \
          Sample_set_ut.cpp \
          Serial_buffer_ut.cpp \
          Smooth_ut.cpp

TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

SP:=../
CFLAGS+=-I./

#Only one of the two options below should be enabled
CFLAGS+=-O2   # Standard compile
#CFLAGS+=-fprofile-arcs -ftest-coverage    # Compile for code coverage

CPPFLAGS+=-DXPRINT_LOCATION #-DPRINT_DEBUG
LDFLAGS+=-ldl

include $(SP)rules.mk
