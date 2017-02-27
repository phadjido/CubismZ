all: spdp libspdp.a mytest_spdp

spdp: SPDP_10.c
	gcc -O3 SPDP_10.c -o spdp


libspdp.a: spdp_10.c
#	gcc -O3 -c spdp_10.c
	gcc -O0 -g -ggdb -c spdp_10.c
	ar rs libspdp.a spdp_10.o
	ranlib libspdp.a

#mytest_spdp: mytest.c
#	gcc -fopenmp -O3 -o mytest_spdp mytest.c spdp_10.c -lm

mytest_spdp: mytest.cpp myspdp.h
	gcc -fopenmp -g -ggdb -O0 -o mytest_spdp mytest.cpp -L. -lspdp -lm
#	gcc -fopenmp -O3 -o mytest_spdp mytest.cpp -L. -lspdp -lm

clean:
	rm -f spdp mytest_spdp *.o *.a
