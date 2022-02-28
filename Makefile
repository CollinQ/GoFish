CXX = g++
#CXX = clang++

CXXFLAGS = -Wall -Wno-uninitialized

BINARIES= tests game

COMMON_OBJECT_FILES = cards.o utility.o

all: ${BINARIES}

tests: tests.o ${COMMON_OBJECT_FILES}
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

game: main.o ${COMMON_OBJECT_FILES}
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o
