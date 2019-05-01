CC       = g++
CFLAGS   = -Wall -O3   
CXXFLAGS = 
INCLUDE  = -I repository/tinyxml2/7.0.1
TARGET   = summer
#LIBPATH  = ./lib

OBJS     = summercli.o tinyxml2.o
SRCS     = ./cli-tool/summer-cli.cpp ./repository/tinyxml2/7.0.1/tinyxml2.cpp
 
$(OBJS):$(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o $(TARGET)
# $(CC) -shared -fPIC -o $(TARGET) $(OBJS)    
# mv $(TARGET) $(LIBPATH)
# rm -f  $(OBJS)