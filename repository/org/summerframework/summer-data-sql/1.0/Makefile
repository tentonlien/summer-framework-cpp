CC       = g++
CFLAGS   = -Wall -O3 -fPIC    
CXXFLAGS = 
INCLUDE  = -I ./include -I ./../../../../mysql/mysql-connector-c/8.0/include
TARGET   = libsummerdatasql.so
LIBPATH  = ./lib

OBJS     = SqlQueryResult.o MysqlConnector.o
SRCS     = src/SqlQueryResult.cpp src/MysqlConnector.cpp
 
$(OBJS):$(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $^
	@$(CC) -shared -fPIC -o $(TARGET) $(OBJS)    
	@mv $(TARGET) $(LIBPATH)
	@rm -f  $(OBJS)