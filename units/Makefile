NAMESPACE:=units

SRC:=Centimeters.cpp \
     Days.cpp \
     Degrees.cpp \
     Feet.cpp \
     Feetpersecond.cpp \
     Feetpersecondpersecond.cpp \
     Gallons.cpp \
     GPS_time.cpp \
     J2000_time.cpp \
     J2010_time.cpp \
     Kilometers.cpp \
     Kilometersperhour.cpp \
     Liters.cpp \
     Meters.cpp \
     Meterspersecond.cpp \
     Meterspersecondpersecond.cpp \
     Miles.cpp \
     Milesperhour.cpp \
     Nanoseconds.cpp \
     Radians.cpp \
     Seconds.cpp \
     Yards.cpp


TEST_SRC:=Centimeters_ut.cpp \
          Degrees_ut.cpp \
          Feetpersecondpersecond_ut.cpp \
          Feetpersecond_ut.cpp \
          Feet_ut.cpp \
          Gallons_ut.cpp \
          GPS_time_ut.cpp \
          J2010_time_ut.cpp \
          Kilometersperhour_ut.cpp \
          Kilometers_ut.cpp \
          Liters_ut.cpp \
          Meterspersecondpersecond_ut.cpp \
          Meterspersecond_ut.cpp \
          Meters_ut.cpp \
          Milesperhour_ut.cpp \
          Miles_ut.cpp \
          Nanoseconds_ut.cpp \
          Radians_ut.cpp \
          Seconds_ut.cpp \
          Yards_ut.cpp


TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

CPPFLAGS+=-DXPRINT_LOCATION #-DPRINT_DEBUG

SP:=../
include $(SP)rules.mk
