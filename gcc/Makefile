OUTDIR = bin
TMPDIR = tmp
TARGET = AddInNative.so

SOURCES = AddInNative.cpp \
	dllmain.cpp \
	stdafx.cpp \
	Interface.cpp \
	NiceHooker.cpp \
	Substitute.cpp \
	Generated.cpp

LIBS     = pthread
OBJECTS  = $(SOURCES:.cpp=.o)
INCLUDES = -I../include
CXXLAGS  = $(CXXFLAGS) $(INCLUDES) -m32 -finput-charset=WINDOWS-1251 -fPIC

all: $(TARGET)
-include $(OBJECTS:.o=.d)

%.o: %.cpp
	mkdir -p $(TMPDIR)
	g++ -c  $(CXXLAGS) $*.cpp -o $(TMPDIR)/$*.o
	g++ -MM $(CXXLAGS) $*.cpp >  $(TMPDIR)/$*.d
	@mv -f $(TMPDIR)/$*.d $(TMPDIR)/$*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $(TMPDIR)/$*.d.tmp > $(TMPDIR)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(TMPDIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(TMPDIR)/$*.d
	@rm -f $(TMPDIR)/$*.d.tmp

$(TARGET): $(OBJECTS) Makefile
	mkdir -p $(OUTDIR)
	g++ $(CXXLAGS) -shared $(addprefix $(TMPDIR)/, $(OBJECTS)) -o $(OUTDIR)/$(TARGET) $(addprefix -l, $(LIBS))

clean:
#	-rm $(OUTDIR)/$(TARGET) $(TMPDIR)/*.o $(TMPDIR)/*.d
	-rm -fr $(OUTDIR) $(TMPDIR)
