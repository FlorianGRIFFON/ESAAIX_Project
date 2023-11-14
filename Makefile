CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = choiceGame

# Find all source and header files
SRC := $(wildcard $(SRCDIR)/*.cpp)
HDR := $(wildcard $(INCDIR)/*.hpp)

# Create a list of object files
OBJ := $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HDR)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -r $(BUILDDIR)
	rm -f $(TARGET)
