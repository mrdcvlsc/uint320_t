CC := g++
TESTFLAGS := -g -Og -D_HIDE_WARNING
CXXFLAGS := -std=c++11 -Wall -Wextra

OS := $(shell uname)

ifeq ($(OS), Linux)
TESTFLAGS += -fsanitize=address
endif

SRC := tests
SRC_FILES := $(wildcard $(SRC)/*.cpp)
OBJ := $(patsubst $(SRC)/%.cpp,$(SRC)/%.out,$(SRC_FILES))

# -------------------------- run test programs ---------------------------

header_test: $(OBJ)
	@echo "----------------------------------------------------"
	@./$(SRC)/constructor.out
	@./$(SRC)/comparison.out
	@./$(SRC)/leftshifts.out
	@./$(SRC)/rightshifts.out
	@./$(SRC)/addition.out
	@./$(SRC)/subtraction.out
	@./$(SRC)/multiplication.out
	@./$(SRC)/division.out
	@./$(SRC)/base10-output.out

# -------------------------- test program compilation ---------------------------

$(SRC)/%.out: $(SRC)/%.cpp
	@echo "compiling test program - compiler : $(CC)"
	@$(CC) $(TESTFLAGS) $(CXXFLAGS) -o $@ $<

clean:
ifeq ($(OS), Linux)
	@echo "deleting compiled test programs"
	@rm ./$(SRC)/*.out
else
	@echo "deleting compiled test programs"
	del tests\*.out
endif