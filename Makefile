PRGRM = aubio_module
TRGT = aubio_module.o aubio_onset.o aubio_pitch.o hopbuffer.o
OBJ = $(addprefix src/, $(TRGT))

CXXFLAGS := -Wall -std=c++11
CXXFLAGS += $(patsubst %,-I %, $(MODULES))
LDFLAGS =
LDLIBS = -laubio

all: $(PRGRM)

# link the program
$(PRGRM): main.cpp $(OBJ)
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS)

# builds given .o files dependend on their corresponding .cpp and .h files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@


# Compile tests of individual segments of the code.
debug: onset_test pitch_test

onset_test: src/aubio_onset_test.cpp src/aubio_onset.o src/aubio_module.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS)

pitch_test: src/aubio_pitch_test.cpp src/aubio_pitch.o src/aubio_module.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS)

clean:
	rm $(OBJ)
	rm $(PRGRM)

cleandebug:
	rm onset_test
	rm pitch_test


.PHONY: all clean cleandebug
