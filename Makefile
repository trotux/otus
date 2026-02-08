export TOPDIR := $(CURDIR)
export BUILD_DIR := $(TOPDIR)/build

ifneq ("$(origin V)", "command line")
V := 0
endif

ifneq ("$(origin BuildType)", "command line")
BuildType := Debug
endif

MAKE_JOB := $(shell nproc)

CMAKE_CONF_OPTS := -H. -B$(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=YES

ifeq ($(BuildType),Release)
CMAKE_CONF_OPTS += -DCMAKE_BUILD_TYPE=Release
else
CMAKE_CONF_OPTS += -DCMAKE_BUILD_TYPE=Debug
endif

ifeq ($(V),1)
CMAKE_CONF_OPTS += -DCMAKE_VERBOSE_MAKEFILE=YES
endif

.PHONY: all distclean clean docker docker-run

all: build-main

build-main:
	cmake $(CMAKE_CONF_OPTS)
	cmake --build $(BUILD_DIR) --parallel $(MAKE_JOB)
	ln -sf build/compile_commands.json

distclean: clean

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(TOPDIR)/compile_commands.json

run-tests:
	@echo "=== Running tests ==="
	@ctest --verbose --test-dir ./build/
