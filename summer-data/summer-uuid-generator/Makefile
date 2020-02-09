CC       = g++
CFLAGS   = -Wall -O3 -fPIC    
CXXFLAGS = 
INCLUDE  = -I ./include
TARGET   = libsummeruuidgenerator.so
LIBPATH  = ./lib

OBJS     = uuid-generator.o
SRCS     = src/uuid-generator.cpp
 
$(OBJS):$(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $^
	@$(CC) -shared -fPIC -o $(TARGET) $(OBJS)    
	@mv $(TARGET) $(LIBPATH)
	@rm -f  $(OBJS)
	