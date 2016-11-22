CC=g++

ifeq ($(dbg),1)
	LOG=1
endif

all: test


ifdef LOG
test:
	@echo LOG=1
else
test:
	@echo LOG=0
endif

