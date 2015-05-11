CXX = g++
CFLAGS = -ansi -Wall -g -std=c++11

SOURCES_DIR = src
OBJECTS_DIR = obj
INCLUDES_DIR = include

SOURCES = $(wildcard $(SOURCES_DIR)/*.cpp)
OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(notdir $(SOURCES:.cpp=.o)))
HEADERS = $(addprefix $(INCLUDES_DIR)/,$(notdir $(SOURCES:.cpp=.h)))
EXECUTABLES = Main

INC = -I./$(INCLUDES_DIR) -I/usr/include/SDL2
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

.PHONY: all
all: $(SOURCES) $(EXECUTABLES)

# Create executable file
$(EXECUTABLES): $(OBJECTS)
	$(CXX) -O2 $^ -o $@ $(LIBS)

# Create object files
$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	$(CXX) $(CFLAGS) $(INC) -c $< -o $@

.PHONY: print
print:
	@echo Sources: $(SOURCES)
	@echo Objects: $(OBJECTS)
	@echo Headers: $(HEADERS)
	@echo Executable: $(EXECUTABLES)

.PHONY: clean
clean:
	-rm -f $(EXECUTABLES) $(OBJECTS_DIR)/*.o
