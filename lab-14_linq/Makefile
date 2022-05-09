CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude
LDFLAGS = 

EXE = lab-14_linq
SRCDIR = src
OBJDIR = obj

TEST_DIR = tests
TEST_EXE = smoke_test

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE)

clean_test:
	rm -rf $(OBJDIR) $(TEST_EXE)

test: $(TEST_EXE)

$(TEST_EXE): obj/smoke_test.o
	$(CXX)	obj/smoke_test.o -o $(TEST_EXE)

obj/smoke_test.o: tests/smoke_test.cpp include/linq.hpp | obj
	$(CXX) $(CXXFLAGS) -c tests/smoke_test.cpp -o obj/smoke_test.o



.PHONY: clean all
