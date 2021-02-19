CXX = g++
CFLAGS = -std=c++14 -Wall -g

TARGET = server
OBJS = code/Vagrant/algorithm/*.cpp \
	code/Vagrant/config/*.cpp \
	code/Vagrant/file/*.cpp \
	code/Vagrant/http/*.cpp \
       code/Vagrant/sql/*.cpp \
       code/Vagrant/server/*.cpp \
       code/Classes/*.cpp \
       code/main.cpp

all: $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o bin/$(TARGET)  -pthread -lmysqlclient

clean:
	rm -rf bin/$(OBJS) $(TARGET)




