CC       = g++
CFLAGS   = -Wall -O2 -fPIC -std=c++17
CXXFLAGS = 
INCLUDE  = -I ./include
TARGET   = libsummercore.so
LIBPATH  = ./lib

OBJS     = *.o # HttpRequest.o HttpResponse.o HttpServer.o LogManager.o
SRCS     = src/*.cpp #src/HttpRequest.cpp src/HttpResponse.cpp src/HttpServer.cpp src/LogManager.cpp
 
$(OBJS):$(SRCS)
	@echo "Building..."
	@$(CC) $(CFLAGS) $(INCLUDE) -c $^
	@$(CC) -shared -fPIC -pthread -o $(TARGET) $(OBJS)
	@mv $(TARGET) $(LIBPATH)
	@rm -f  $(OBJS)

	@echo "Updating /usr/include and /usr/lib ..."
	@if [ ! -d "/usr/include/org" ]; then mkdir /usr/include/org; fi
	@if [ ! -d "/usr/include/org/summerframework" ]; then mkdir /usr/include/org/summerframework; fi
	@cp -r ./include/. /usr/include/org/summerframework
	@cp -r ./lib/. /usr/lib/Summer

	@echo "Complete"