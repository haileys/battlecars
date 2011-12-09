# GNU Make project makefile autogenerated by Premake
ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),release)
  OBJDIR     = obj/Release/Sample-Allegro
  TARGETDIR  = ../../../bin/AllegroSample.app/Contents/MacOS
  TARGET     = $(TARGETDIR)/AllegroSample
  DEFINES   += -DNDEBUG
  INCLUDES  += -I../../../include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -O2 -ffast-math
  CXXFLAGS  += $(CFLAGS) -fno-rtti
  LDFLAGS   += -L../../../lib -L../../../lib/macosx
  LIBS      += ../../../lib/macosx/libGWEN-Renderer-Allegro.a ../../../lib/macosx/libgwen_static.a ../../../lib/macosx/libunittest.a -lalleg
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += ../../../lib/macosx/libGWEN-Renderer-Allegro.a ../../../lib/macosx/libgwen_static.a ../../../lib/macosx/libunittest.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = obj/Debug/Sample-Allegro
  TARGETDIR  = ../../../bin/AllegroSample_D.app/Contents/MacOS
  TARGET     = $(TARGETDIR)/AllegroSample_D
  DEFINES   += -D_DEBUG
  INCLUDES  += -I../../../include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g
  CXXFLAGS  += $(CFLAGS) -fno-rtti
  LDFLAGS   += -L../../../lib -L../../../lib/macosx
  LIBS      += ../../../lib/macosx/libGWEN-Renderer-Allegro.a ../../../lib/macosx/libgwend_static.a ../../../lib/macosx/libunittestd.a -lalleg
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += ../../../lib/macosx/libGWEN-Renderer-Allegro.a ../../../lib/macosx/libgwend_static.a ../../../lib/macosx/libunittestd.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/AllegroSample.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET) $(dir $(TARGETDIR))PkgInfo $(dir $(TARGETDIR))Info.plist
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking Sample-Allegro
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

$(dir $(TARGETDIR))PkgInfo:
$(dir $(TARGETDIR))Info.plist:

clean:
	@echo Cleaning Sample-Allegro
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/AllegroSample.o: ../../../Samples/Allegro/AllegroSample.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
