CC       = g++
CFLAGS   = -Wall -O2 -fPIC    
CXXFLAGS = 
INCLUDE  = -I ./include
TARGET   = libsummerweb.so
LIBPATH  = ./lib

OBJS     = Controller.o HttpRequest.o HttpResponse.o HttpServer.o LogManager.o
SRCS     = src/Controller.cpp src/HttpRequest.cpp src/HttpResponse.cpp src/HttpServer.cpp src/LogManager.cpp
 
$(OBJS):$(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $^
	@$(CC) -shared -fPIC -o $(TARGET) $(OBJS)    
	@mv $(TARGET) $(LIBPATH)
	@rm -f  $(OBJS)