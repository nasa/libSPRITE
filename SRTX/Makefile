NAMESPACE:=SRTX
SRC:=Base_double_buffer.cpp \
     Base_ring_buffer.cpp \
     Buffer.cpp \
     Container.cpp \
     End_of_frame.cpp \
     Mutex.cpp \
     Syncpoint.cpp \
     Data_router.cpp \
     Task.cpp \
     Reference_time.cpp \
     RTC.cpp \
     Scheduler.cpp \

#TEST_SRC:= \
          External_trigger_ut.cpp

TEST_SRC:=Double_buffer_ut.cpp \
          Ring_buffer_ut.cpp \
          Mutex_ut.cpp \
          Symbol_table_ut.cpp \
          Task_properties_ut.cpp \
          RTC_ut.cpp \
          Scheduler_ut.cpp \
          Message_ut.cpp \
          External_trigger_ut.cpp

# Running the reference time test fouls up the clock for the scheduler.
          #Reference_time_ut.cpp \

TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

CFLAGS+=-I./

#Only one of the two options below should be enabled
CFLAGS+=-O2   # Standard compile
#CFLAGS+=-fprofile-arcs -ftest-coverage    # Compile for code coverage

CPPFLAGS+=-DXPRINT_LOCATION #-DPRINT_DEBUG
LDFLAGS+=-lSPRITE_units -lrt -ldl -lpthread

#Data_router.o: CPPFLAGS+=-DPRINT_DEBUG
#End_of_frame.o: CPPFLAGS+=-DPRINT_DEBUG
#Scheduler.o: CPPFLAGS+=-DPRINT_DEBUG
#Task.o: CPPFLAGS+=-DPRINT_DEBUG
#Mutex.o: CPPFLAGS+=-DPRINT_DEBUG
#Scheduler_ut.o: CPPFLAGS+=-DPRINT_DEBUG
#Message_ut.o: CPPFLAGS+=-DPRINT_DEBUG

SP:=../
include $(SP)rules.mk
