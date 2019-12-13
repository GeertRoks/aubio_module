PRGRM = AubioWrapper
TRGT = aubioWrapper.o aubioOnsetWrapper.o aubioPitchWrapper.o hopbuffer.o
OBJ = $(addprefix src/, $(TRGT))

CXXFLAGS := -Wall -std=c++11
CXXFLAGS += $(patsubst %,-I %, $(MODULES))
LDFLAGS =
LDLIBS = -laubio

all: $(PRGRM)

# link the program
$(PRGRM): main_aubioWrapper.cpp $(OBJ)
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS)

# builds given .o files dependend on their corresponding .cpp and .h files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@



# Compile tests of individual segments of the code.
debug: OnsetTest PitchTest

OnsetTest: src/main_test_aubioOnset.cpp src/aubioOnsetWrapper.o src/aubioWrapper.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS)

PitchTest: src/main_test_aubioPitch.cpp src/aubioPitchWrapper.o src/aubioWrapper.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS)


clean:
	rm $(OBJ)
	rm $(PRGRM)

cleandebug:
	rm OnsetTest
	rm PitchTest


.PHONY: all clean cleandebug
