CC       = g++
CFLAGS   = -Wall -O2   
CXXFLAGS = 
INCLUDE  = -I ./include
TARGET   = out/summer
#LIBPATH  = ./lib

OBJS     = *.o
SRCS     = ./src/*.cpp
 
$(OBJS):$(SRCS)
	@echo "Building Summer CLI..."
	@$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o $(TARGET)
	@echo "Complete."