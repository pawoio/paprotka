
	; rdi	pierwszy piksel
	; rsi	szerokosc bitmapy
	; rdx	wysokosc bitmapy
	; rcx	iteracje

	; r8	 p1
	; r9	 p12
	; r10	 p123
	; r11	wysokosc bitmapy

	; xmm0	x0
	; xmm1	x1
	; xmm2	y0
	; xmm3	y1


section .text
	global fern

default rel
section .data
	c0_0:	dq	0.0
	c0_85:	dq	0.85
	c0_04:	dq	0.04
	cmin0_04:	dq	-0.04
	c1_6:	dq	1.6
	cmin0_15:	dq	-0.15
	c0_28:	dq	0.28
	c0_26:	dq	0.26
	c0_24:	dq	0.24
	c0_44:	dq	0.44
	c0_2:	dq	0.2
	c0_23:	dq	0.23
	c0_22:	dq	0.22
	c0_16:	dq	0.16
	c3_0:	dq	3.0
	X:		dq	6.0
	Y:		dq	11.0

fern:
	push rbp
	mov rbp, rsp

	cmp rcx, 0
	jz exit

	movsd xmm4, [c0_0]
	movsd xmm0, xmm4		; x=0
	movsd xmm2, xmm0		; y=0
	mov r11, rdx			; wysokosc -> r11
	mov r10, [rbp+16]		; p123 -> r10				

loop:

	rdrand rax
	mov rdx,0
	mov rbx, 100
	div rbx

	cmp rdx, r8			;0.85x + 0.04y, -0.04x + 0.85y +1.6
	jge cond1

	movsd xmm1, xmm0
	movsd xmm4, [c0_85]
	mulsd xmm1, xmm4
	movsd xmm5, xmm2
	movsd xmm4, [c0_04]
	mulsd xmm5, xmm4
	addsd xmm1, xmm5

	movsd xmm3, xmm0
	movsd xmm4, [cmin0_04]
	mulsd xmm3, xmm4
	movsd xmm5, xmm2
	movsd xmm4, [c0_85]
	mulsd xmm5, xmm4
	addsd xmm3, xmm5
	movsd xmm4, [c1_6]
	addsd xmm3, xmm4

	jmp paint


cond1:
	; -0.15x + 0.28y, 0.26x + 0.24y + 0.44
	cmp rdx, r9
	jge cond2

	movsd xmm1, xmm0
	movsd xmm4, [cmin0_15]
	mulsd xmm1, xmm4
	movsd xmm5, xmm2
	movsd xmm4, [c0_28]
	mulsd xmm5, xmm4
	addsd xmm1, xmm5
	
	movsd xmm3, xmm0
	movsd xmm4, [c0_26]
	mulsd xmm3, xmm4
	movsd xmm5, xmm2
	movsd xmm4, [c0_24]
	mulsd xmm5, xmm4
	addsd xmm3, xmm5
	movsd xmm4, [c0_44]
	addsd xmm3, xmm4
		
	jmp paint

cond2:
	; 0.20x - 0.26y, 0.23x + 0.22y + 1.6
	cmp rdx, r10
	jge cond3

	movsd xmm1, xmm0
	movsd xmm4, [c0_2]
	mulsd xmm1, xmm4
	movsd xmm5, xmm2
	movsd xmm4, [c0_26]
	mulsd xmm5, xmm4
	subsd xmm1, xmm5
	
	movsd xmm3, xmm0
	movsd xmm4, [c0_23]
	mulsd xmm3, xmm4
	movsd xmm5, xmm2
	movsd xmm4, [c0_22]
	mulsd xmm5, xmm4
	addsd xmm3, xmm5
	movsd xmm4, [c1_6]
	addsd xmm3, xmm4		; y = 0.23x + 0.22y + 1.6

	jmp paint	

cond3:
	; if (rand>= p1+p2+p3) (x,y) = (0, 0.16y)

	movsd xmm1, [c0_0]
	movsd xmm4, [c0_16]
	movsd xmm3, xmm2
	mulsd xmm3, xmm4

paint:
	movsd xmm6, xmm1
	movsd xmm4, [c3_0]
	addsd xmm6, xmm4
	movsd xmm4, [X]
	divsd xmm6, xmm4
	cvtsi2sd xmm4, rsi
	mulsd xmm6, xmm4
	cvtsd2si rax, xmm6
	mov r12, 3
	mul r12
	mov r13, [rdi]
	add r13, rax

	movsd xmm7, xmm3
	movsd xmm4, [Y]
	subsd xmm4, xmm7
	movsd xmm7, xmm4
	movsd xmm4, [Y]
	divsd xmm7, xmm4
	cvtsi2sd xmm4, r11
	mulsd xmm7, xmm4
	mov rax, rsi
	mov r12, 3
	mul r12

	cvtsd2si r12, xmm7
	mul r12

	add r13, rax

	mov r12b, 0
	mov [r13], r12b
	inc r13
	mov r12b, 128
	mov [r13], r12b
	inc r13
	mov r12b, 0
	mov [r13], r12b

endWhile:
	movsd xmm0, xmm1
	movsd xmm2, xmm3

	dec rcx
	
	cmp rcx, 0
	jg loop

exit:	
	mov rsp, rbp	
	pop rbp
	ret

