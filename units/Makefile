NAMESPACE:=units

SRC:=Days.cpp \
     Degrees.cpp \
     Kilometers.cpp \
     Meters.cpp \
     Millimeters.cpp \
     Nanoseconds.cpp \
     Radians.cpp \
     Seconds.cpp


TEST_SRC:=Celsius_ut.cpp \
          Degrees_ut.cpp \
          GPS_time_ut.cpp \
          Kilometers_ut.cpp \
          Liters_ut.cpp \
          Meterspersecondpersecond_ut.cpp \
          Meterspersecond_ut.cpp \
          Meters_ut.cpp \
          Millimeters_ut.cpp \
          Nanoseconds_ut.cpp \
          Pascal_ut.cpp \
          Radians_ut.cpp \
          Seconds_ut.cpp


TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

CPPFLAGS+=-DXPRINT_LOCATION #-DPRINT_DEBUG

SP:=../
include $(SP)rules.mk
