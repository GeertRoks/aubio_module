PRGRM = AubioWrapper
OBJ = main_aubioWrapper.o onset/aubioOnsetWrapper.o

CXXFLAGS := -Wall -std=c++11
CXXFLAGS += $(patsubst %,-I %, $(MODULES))
LDFLAGS =
LDLIBS = -laubio

all: $(PRGRM)

# link the program
$(PRGRM): $(OBJ)
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS)

# builds given .o files dependend on their corresponding .cpp and .h files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@



# Compile tests of individual segments of the code.
debug: onsetTest pitchTest

onsetTest: onset/main_test_aubioOnset.cpp onset/aubioOnsetWrapper.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS)

pitchTest: pitch/main_test_aubioPitch.cpp pitch/aubioPitchWrapper.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS)


clean:
	rm $(OBJ)
	rm $(PRGRM)

cleandebug:
	rm onsetTest
	rm pitchTest


.PHONY: all clean cleandebug
