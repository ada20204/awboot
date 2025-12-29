
BUILD_DIR=build

MKSUNXI = mksunxi
MKSUNXI_NUTTX = mksunxi-nuttx

CSRC    = mksunxi.c
CSRC_NUTTX = mksunxi-nuttx.c
CXXSRC  =

COBJS   = $(addprefix $(BUILD_DIR)/,$(CSRC:.c=.o))
COBJS_NUTTX = $(addprefix $(BUILD_DIR)/,$(CSRC_NUTTX:.c=.o))
CXXOBJS = $(addprefix $(BUILD_DIR)/,$(CXXSRC:.cpp=.opp))

INCLUDES = -I includes -I ../lib
CFLAGS   = -O2 -std=gnu99 $(INCLUDES)
CXXFLAGS = -O2 -std=gnu++11 $(INCLUDES)

CC  ?= gcc
CXX ?= g++

all: tools
tools: $(MKSUNXI) $(MKSUNXI_NUTTX)

.PHONY: all tools clean
.SILENT:

clean:
	rm -rf build
	rm -f $(MKSUNXI)
	rm -f $(MKSUNXI_NUTTX)

$(BUILD_DIR)/%.o : %.c
	echo "  CC    $@"
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.opp : %.cpp
	echo "  CXX   $@"
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MKSUNXI): $(COBJS)
	echo "  LD    $@"
	$(CC) $(CFLAGS) $(COBJS) -o $(MKSUNXI)

$(MKSUNXI_NUTTX): $(COBJS_NUTTX)
	echo "  LD    $@"
	$(CC) $(CFLAGS) $(COBJS_NUTTX) -o $(MKSUNXI_NUTTX)
