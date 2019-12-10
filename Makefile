PRGRM = AubioWrapper
OBJ = main_aubioWrapper.o onset/aubioOnsetWrapper.o

CXXFLAGS := -Wall -std=c++11
CXXFLAGS += $(patsubst %,-I %, $(MODULES))
LDFLAGS =
LDLIBS = -laubio

all: $(PRGRM)

# link the program
$(PRGRM): $(OBJ)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJ) $(LDFLAGS) $(LDLIBS)

# builds given .o files dependend on their corresponding .cpp and .h files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm $(OBJ)
	rm $(PRGRM)

.PHONY: all clean
