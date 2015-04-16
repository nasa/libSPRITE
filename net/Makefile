NAMESPACE:=net
SRC:=Socket.cpp \
     UDP_connection.cpp \
     UDP_client.cpp \
     UDP_server.cpp

TEST_SRC:=UDP_client_ut.cpp \
          UDP_server_ut.cpp

#TEST_SRC:=UDP_server_ut.cpp

TGT:=SPRITE_$(NAMESPACE)
TGTTYPE:=static_lib

SP:=../
CPPFLAGS+=-DXPRINT_LOCATION #-DPRINT_DEBUG
LDFLAGS+=-lpthread

UDP_connection.o: CPPFLAGS+=-DPRINT_DEBUG

include $(SP)rules.mk
