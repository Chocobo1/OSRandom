# compiler options
CXX       += -fsanitize=undefined
CXXFLAGS   = -std=c++11 -pipe -Wall -Wextra -Wpedantic -fmax-errors=2 -fdiagnostics-color=auto -O2 -g
#LDFLAGS   = -s
SRC_NAME   = test
EXECUTABLE = run_tests
SRC_EXT    = cpp


# targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(patsubst %,%.o,$(SRC_NAME))
	$(CXX) $(LDFLAGS) $(patsubst %,%.o,$(SRC_NAME)) -o $(EXECUTABLE)
	@echo

$(patsubst %,%.o,$(SRC_NAME)): %.o : %.$(SRC_EXT)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(patsubst %,./%.o,$(SRC_NAME)) ./$(EXECUTABLE)
