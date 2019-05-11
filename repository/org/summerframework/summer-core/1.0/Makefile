CC       = g++
CFLAGS   = -Wall -O3 -fPIC    
CXXFLAGS = 
INCLUDE  = -I ./include
TARGET   = libsummercore.so
LIBPATH  = ./lib

OBJS     = summer.o
SRCS     = src/summer.cpp
 
$(OBJS):$(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $^
	@$(CC) -shared -fPIC -o $(TARGET) $(OBJS)    
	@mv $(TARGET) $(LIBPATH)
	@rm -f  $(OBJS)