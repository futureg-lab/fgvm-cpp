# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  fgvm_core_config = debug
  fgvm_examples_config = debug
  sandbox_config = debug
endif
ifeq ($(config),release)
  fgvm_core_config = release
  fgvm_examples_config = release
  sandbox_config = release
endif

PROJECTS := fgvm-core fgvm-examples sandbox

.PHONY: all clean help $(PROJECTS) Lib

all: $(PROJECTS)

Lib: fgvm-core fgvm-examples

fgvm-core:
ifneq (,$(fgvm_core_config))
	@echo "==== Building fgvm-core ($(fgvm_core_config)) ===="
	@${MAKE} --no-print-directory -C includes/fgvm/core -f Makefile config=$(fgvm_core_config)
endif

fgvm-examples:
ifneq (,$(fgvm_examples_config))
	@echo "==== Building fgvm-examples ($(fgvm_examples_config)) ===="
	@${MAKE} --no-print-directory -C includes/fgvm/examples -f Makefile config=$(fgvm_examples_config)
endif

sandbox: fgvm-core fgvm-examples
ifneq (,$(sandbox_config))
	@echo "==== Building sandbox ($(sandbox_config)) ===="
	@${MAKE} --no-print-directory -C . -f sandbox.make config=$(sandbox_config)
endif

clean:
	@${MAKE} --no-print-directory -C includes/fgvm/core -f Makefile clean
	@${MAKE} --no-print-directory -C includes/fgvm/examples -f Makefile clean
	@${MAKE} --no-print-directory -C . -f sandbox.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   fgvm-core"
	@echo "   fgvm-examples"
	@echo "   sandbox"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"