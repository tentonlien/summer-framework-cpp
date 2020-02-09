# CC       = g++
# CFLAGS   = -Wall -O2
# CXXFLAGS = 
# # INCLUDE  = -I ./include
# TARGET   = DemoApplication
# LIBPATH  = ./out

# OBJS     = DemoApplication.o
# SRCS     = DemoApplication.cpp
 
# $(OBJS):$(SRCS)
# 	@$(CC) $(CFLAGS) $(INCLUDE) -c $^
# 	@$(CC) -shared -fPIC -pthread -o $(TARGET) $(OBJS)    
# 	@mv $(TARGET) $(LIBPATH)
# 	@rm -f  $(OBJS)

CC       = g++
CFLAGS   = -Wall -O2 -std=c++17
CXXFLAGS = 
# INCLUDE  = -I repository/tinyxml2/7.0.1 -I ./repository/org/summerframework/summer-core/1.0/include
TARGET   = ./out/DemoApplication
OUTPUT_PATH  = ./out

OBJS     = DemoApplication.o
SRCS     = ./src/cpp/DemoApplication.cpp ./gen/*.cpp ./src/cpp/controller/*.cpp ./src/cpp/model/*.cpp

$(OBJS):$(SRCS)
	@echo "Building DemoApplication..."
	@if [ ! -d "./lib" ]; then mkdir lib; fi
	@$(CC) $(CFLAGS) $(SRCS) -L ./out/lib -l summercore -L ./out/lib -l summerweb -o $(TARGET) -pthread -Wl,-rpath ./lib
	#@mv $(TARGET) $(OUTPUT_PATH)
	@rm -r lib
	@echo "Complete."
	@cd out && ./DemoApplication