# Makefile autogenerated by premake
# Don't edit this file! Instead edit `premake.lua` then rerun `make`
# Options:
#   CONFIG=[Debug|Release]

ifndef CONFIG
  CONFIG=Debug
endif

export CONFIG

.PHONY: all clean RetroMessenger

all: RetroMessenger

Makefile: premake.lua retromessenger.lua
	@echo ==== Regenerating Makefiles ====
	@premake --file $^ --target gnu --unicode

RetroMessenger:
	@echo ==== Building RetroMessenger ====
	@$(MAKE) --no-print-directory -C . -f RetroMessenger.make

clean:
	@$(MAKE) --no-print-directory -C . -f RetroMessenger.make clean
