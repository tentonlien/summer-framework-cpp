CC       = g++
CFLAGS   = -Wall -O3 -fPIC    
CXXFLAGS = 
INCLUDE  = -I ./include
TARGET   = libsummerjsonwrapper.so
LIBPATH  = ./lib

OBJS     = JsonParser.o
SRCS     = src/JsonParser.cpp
 
$(OBJS):$(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $^
	@$(CC) -shared -fPIC -o $(TARGET) $(OBJS)    
	@mv $(TARGET) $(LIBPATH)
	@rm -f  $(OBJS)
	