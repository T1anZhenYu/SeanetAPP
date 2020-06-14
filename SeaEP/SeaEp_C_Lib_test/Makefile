CROSS_COMPILE=
STAGING_DIR=
CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++
STRIP=$(CROSS_COMPILE)strip

DEBUG_FLAG=-g

INCLUDE=-I./ 
CXXFLAG+=  -fPIC -Wall $(EXTRA_LDFLAGS) --sysroot=$(STAGING_DIR) ${PREDEFINE}

all: main_test 

###	go	###

	
main_test:main_test.o 
	${CC} ${CXXFLAG} ${INCLUDE} ${L_PATH}   -o $@ main_test.o -lpthread -L. -lseaep_jni
	$(STRIP) $@

%.o:%.c
	${CC} ${CXXFLAG} ${INCLUDE} -c $< -o $@

%.o:%.cpp
	${CXX} ${CXXFLAG} ${INCLUDE} -c $< -o $@

clean_go:
	@rm -f main_test *.o
clean: clean_go
