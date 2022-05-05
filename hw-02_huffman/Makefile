CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -I include
LDFLAGS = 

EXE = hw-02_huffman
SRCDIR = src
OBJDIR = obj

EXE_TEST = hw-02_huffman_test
SRCDIR_TEST = tests/test_src
OBJDIR_TEST = obj_test

INCLUDE = include

INCLUDE_TEST = tests/test_include
SRCDIR_TEST = tests/test_src


OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)


test: $(EXE_TEST) 

$(EXE_TEST): $(OBJDIR_TEST)/arg_utils.o $(OBJDIR_TEST)/bitio.o $(OBJDIR_TEST)/huffman_archiver.o $(OBJDIR_TEST)/huffman_dearchiver.o $(OBJDIR_TEST)/hufftree.o $(OBJDIR_TEST)/test.o
	$(CXX) -o $(EXE_TEST) $(OBJDIR_TEST)/arg_utils.o $(OBJDIR_TEST)/bitio.o $(OBJDIR_TEST)/huffman_archiver.o $(OBJDIR_TEST)/huffman_dearchiver.o $(OBJDIR_TEST)/hufftree.o $(OBJDIR_TEST)/test.o $(LDFLAGS)
	
$(OBJDIR_TEST)/arg_utils.o: $(SRCDIR)/arg_utils.cpp  $(INCLUDE)/arg_utils.h| $(OBJDIR_TEST)
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/arg_utils.cpp -o $(OBJDIR_TEST)/arg_utils.o


$(OBJDIR_TEST)/bitio.o: $(SRCDIR)/bitio.cpp  $(INCLUDE)/bitio.h| $(OBJDIR_TEST)
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/bitio.cpp -o $(OBJDIR_TEST)/bitio.o


$(OBJDIR_TEST)/huffman_archiver.o: $(SRCDIR)/huffman_archiver.cpp  $(INCLUDE)/huffman_archiver.h| $(OBJDIR_TEST)
	$(CXX) $(CXXFLAGS) -c  $(SRCDIR)/huffman_archiver.cpp -o $(OBJDIR_TEST)/huffman_archiver.o


$(OBJDIR_TEST)/huffman_dearchiver.o: $(SRCDIR)/huffman_dearchiver.cpp  $(INCLUDE)/huffman_dearchiver.h| $(OBJDIR_TEST)
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/huffman_dearchiver.cpp -o $(OBJDIR_TEST)/huffman_dearchiver.o


$(OBJDIR_TEST)/hufftree.o: $(SRCDIR)/hufftree.cpp  $(INCLUDE)/hufftree.h $(INCLUDE)/huffman_util.h | $(OBJDIR_TEST)
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/hufftree.cpp -o $(OBJDIR_TEST)/hufftree.o


$(OBJDIR_TEST)/test.o: $(SRCDIR_TEST)/test.cpp $(INCLUDE_TEST)/doctest.h $(INCLUDE)/arg_utils.h  $(INCLUDE)/bitio.h  $(INCLUDE)/huffman_archiver.h $(INCLUDE)/huffman_dearchiver.h $(INCLUDE)/hufftree.h| $(OBJDIR_TEST)
	$(CXX) $(CXXFLAGS) -c $(SRCDIR_TEST)/test.cpp -o $(OBJDIR_TEST)/test.o





$(OBJDIR):
	mkdir -p $(OBJDIR)


$(OBJDIR_TEST):
	mkdir -p $(OBJDIR_TEST)



clean:
	rm -rf $(OBJDIR) $(EXE)

clean_test:
	rm -rf $(OBJDIR_TEST) $(EXE_TEST)

.PHONY: clean all test clean_test
