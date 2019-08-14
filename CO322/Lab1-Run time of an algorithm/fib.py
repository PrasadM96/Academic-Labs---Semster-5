#!/usr/bin/python
import time

def fib_r(x) :
    if (x <= 2):
        return 1
    return fib_r(x-1) + fib_r(x-2)


def fib_i(x) :
    a = 1
    b = 1
    fib = 1
    i = 2
    while i < x:
        fib = a +b
        a = b
        b = fib
        i+=1
        
    return fib





#for i in range(1,41):
#	startTime=time.time();
#	val=fib_i(i);
#	endTime=time.time();
	
#	print(str((endTime-startTime)*1000000))

for i in range(1,41):
	startTime=time.time();
	val=fib_r(i);
	endTime=time.time();
	
	print('{:.2f}'.format((endTime-startTime)*1000000))








