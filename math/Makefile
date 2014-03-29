NAMESPACE:=math
SRC:=DCM.cpp \
     Euler.cpp \
     Matrix3.cpp \
     Quaternion.cpp \
     trig.cpp \
     Vec3.cpp

TEST_SRC:=DCM_ut.cpp \
          Euler_ut.cpp \
          Matrix3_ut.cpp \
          Quaternion_ut.cpp \
          trig_ut.cpp \
          Vec3_ut.cpp


TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

SP:=../
CPPFLAGS+=-DXPRINT_LOCATION #-DPRINT_DEBUG
LDFLAGS+=-lSPRITE_units -ldl

include $(SP)rules.mk
