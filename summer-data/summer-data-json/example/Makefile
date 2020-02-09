CC       = g++
CFLAGS   = -Wall 
CXXFLAGS = 
INCLUDE  = -I ./../include/
LIB      = -L ./../lib/ -l summerjsonwrapper
LPATH    = -Wl,-rpath ./../lib
TARGET   = example

OBJS     = example.o
SRCS     = example.cpp
 
$(OBJS):$(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(INCLUDE) $(LIB) $(LPATH)

run:
	@./example

clean:
	@rm -f example