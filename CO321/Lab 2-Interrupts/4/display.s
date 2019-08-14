	.file	"display.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r24,0
	ldi r25,0
	ldi r22,lo8(1)
	ldi r23,0
.L2:
	in r20,0x4
	movw r18,r22
	mov r0,r24
	rjmp 2f
	1:
	lsl r18
	2:
	dec r0
	brpl 1b
	or r18,r20
	out 0x4,r18
	adiw r24,1
	cpi r24,6
	cpc r25,__zero_reg__
	brne .L2
	cbi 0xa,2
	lds r24,105
	ori r24,lo8(2)
	sts 105,r24
	lds r24,105
	ori r24,lo8(1)
	sts 105,r24
/* #APP */
 ;  22 "display.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
	sbi 0x1d,0
	cbi 0xa,3
	lds r24,105
	ori r24,lo8(8)
	sts 105,r24
	lds r24,105
	ori r24,lo8(4)
	sts 105,r24
/* #APP */
 ;  32 "display.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
	sbi 0x1d,1
	out 0x5,__zero_reg__
.L3:
	rjmp .L3
	.size	main, .-main
	.text
.global	__vector_1
	.type	__vector_1, @function
__vector_1:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
	push r24
	push r25
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 6 */
.L__stack_usage = 6
	lds r24,count
	lds r25,count+1
	adiw r24,1
	sts count+1,r25
	sts count,r24
	sbiw r24,7
	brlt .L7
	out 0x5,__zero_reg__
	sts count+1,__zero_reg__
	sts count,__zero_reg__
.L7:
	ldi r18,lo8(3199999)
	ldi r24,hi8(3199999)
	ldi r25,hlo8(3199999)
1:	subi r18,1
	sbci r24,0
	sbci r25,0
	brne 1b
	rjmp .
	nop
	in r24,0x5
	lsl r24
	out 0x5,r24
	sbi 0x5,0
/* epilogue start */
	pop r25
	pop r24
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_1, .-__vector_1
.global	__vector_2
	.type	__vector_2, @function
__vector_2:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
	push r24
	push r25
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 6 */
.L__stack_usage = 6
	lds r24,count
	lds r25,count+1
	adiw r24,1
	sts count+1,r25
	sts count,r24
	sbiw r24,7
	brlt .L9
	out 0x5,__zero_reg__
	sts count+1,__zero_reg__
	sts count,__zero_reg__
.L9:
	ldi r18,lo8(3199999)
	ldi r24,hi8(3199999)
	ldi r25,hlo8(3199999)
1:	subi r18,1
	sbci r24,0
	sbci r25,0
	brne 1b
	rjmp .
	nop
	in r24,0x5
	lsl r24
	out 0x5,r24
/* epilogue start */
	pop r25
	pop r24
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_2, .-__vector_2
.global	count
	.data
	.type	count, @object
	.size	count, 2
count:
	.word	-1
	.ident	"GCC: (GNU) 4.9.2"
.global __do_copy_data
