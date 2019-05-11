CC       = g++
CFLAGS   = -Wall -O2   
CXXFLAGS = 
INCLUDE  = -I repository/tinyxml2/7.0.1 -I ./repository/org/summerframework/summer-core/1.0/include
TARGET   = summer
#LIBPATH  = ./lib

OBJS     = SummerCLI.o tinyxml2.o summer.o
SRCS     = ./cli-tool/SummerCLI.cpp ./repository/tinyxml2/7.0.1/tinyxml2.cpp ./repository/org/summerframework/summer-core/1.0/src/summer.cpp
 
$(OBJS):$(SRCS)
	@echo "Building Summer CLI..."
	@$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o $(TARGET)
	@echo "Complete."