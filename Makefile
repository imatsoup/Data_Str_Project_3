SRC_FILES := $(wildcard *cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))
HEADER_FILES := $(wildcard *.h)
LDLFLAGS := -g -ggdb
CPPFLAGS := -g -ggdb

testHarness.exe: $(OBJ_FILES)
	g++ $(LDLFLAGS) -o $@ $^

%.o: %.cpp $(HEADER_FILES)
	g++ $(CPPFLAGS) -c -o $@ $<