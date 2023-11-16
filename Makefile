CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = choiceGame

# SFML Configuration
SFML_INCLUDE = -I/path/to/sfml/include
SFML_LIBS = -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

# Find all source and header files
SRC := $(wildcard $(SRCDIR)/*.cpp)
HDR := $(wildcard $(INCDIR)/*.hpp)

# Create a list of object files
OBJ := $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HDR)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -I$(INCDIR) -c $< -o $@

clean:
	rm -r $(BUILDDIR)
	rm -f $(TARGET)
