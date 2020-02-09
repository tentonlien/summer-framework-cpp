CC       = g++
CFLAGS   = -Wall -O2   
CXXFLAGS = 
TARGET   = ./out/{{projectName}}
OUTPUT_PATH  = ./out

OBJS     = *.o
SRCS     = ./src/cpp/{{programEntryFileName}}Application.cpp ./gen/*.cpp

$(OBJS):$(SRCS)
	@echo "Building {{programEntryFileName2}}Application..."
	@if [ ! -d "./lib" ]; then mkdir lib; fi
	@$(CC) $(CFLAGS) $(SRCS) -L ./out/lib -l summercore -L ./out/lib -l summerweb -o $(TARGET) -pthread -Wl,-rpath ./lib
	@rm -r lib
	@echo "Complete."