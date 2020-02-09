CC       = g++
CFLAGS   = -Wall -O3 -fPIC    
CXXFLAGS = 
INCLUDE  = -I ./include
TARGET   = libsummerdatakeyvalue.so
LIBPATH  = ./lib

OBJS     = keyvalue.o
SRCS     = src/keyvalue.cpp
 
$(OBJS):$(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $^
	@$(CC) -shared -fPIC -o $(TARGET) $(OBJS)    
	@mv $(TARGET) $(LIBPATH)
	@rm -f  $(OBJS)
	