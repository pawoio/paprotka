	; SPIS REJESTROW

	; rdi	ilość wowołan
	; rsi	p1
	; rdx	p12
	; rcx	p123
	; rbp	wskaznik ramki
	; rsp	wskaznik stosu
	; rax	uzywane w div i potem przy mul
	; rbx   uzywane w div
    ; r8 p1
    ; r9  p12
    ; r10 p123


	; xmm0	x0
	; xmm1	x1
	; xmm2	y0
	; xmm3	y1


section .text
    extern glVertex2d

	global fern
    extern putPixel
default rel
section .data
	const0_0:	dq	0.0
	const0_85:	dq	0.85
	const0_04:	dq	0.04
	constmin0_04:	dq	-0.04
	const1_6:	dq	1.6
	constmin0_15:	dq	-0.15
	const0_28:	dq	0.28
	const0_26:	dq	0.26
	constmin0_26: dq -0.26
	const0_24:	dq	0.24
	const0_44:	dq	0.44
	const0_2:	dq	0.2
	const0_23:	dq	0.23
	const0_22:	dq	0.22
	const0_16:	dq	0.16
	const3_0:	dq	3.0
	const5_0:   dq  5.0
	const1_0:   dq  1.0


fern:
	push rbp
	mov rbp, rsp

    mov r8, rsi
    mov r9, rdx
    mov r10, rcx
    mov rcx, rdi
	cmp rcx, 0
	jz exit


	movsd xmm4, [const0_0]
	movsd xmm0, xmm4		; x=0
	movsd xmm2, xmm0		; y=0
	;mov r11, rdx			; p12 -> r11


whileIteration:

	; ALGORYTM
	; (x,y) = (0.85x + 0.04y, -0.04x + 0.85y +1.6)
	; (x,y) = (-0.15x + 0.28y, 0.26x + 0.24y + 0.44)
	; (x,y) = (0.20x - 0.26y, 0.23x + 0.22y + 1.6)
	; (x,y) = (0, 0.16y)
	; proporcje 85 : 7 : 7 : 1

	rdrand rax
	mov rdx,0
	mov rbx, 100
	div rbx				; dzieli rdx:rax przez to co po div (rbx), wynik (calosci) w rax, reszta w rdx

	cmp rdx, r8			; if (rand < p1) (x,y) = (0.85x + 0.04y, -0.04x + 0.85y +1.6)
	jge else1

	movsd xmm1, xmm0
	movsd xmm4, [const0_85]
	mulsd xmm1, xmm4		; 0.85x
	movsd xmm5, xmm2
	movsd xmm4, [const0_04]
	mulsd xmm5, xmm4
	addsd xmm1, xmm5		; x = 0.85x + 0.04y

	movsd xmm3, xmm0
	movsd xmm4, [constmin0_04]
	mulsd xmm3, xmm4		; -0.04x
	movsd xmm5, xmm2
	movsd xmm4, [const0_85]
	mulsd xmm5, xmm4		; 0.85y
	addsd xmm3, xmm5		; -0.04x + 0.85y
	movsd xmm4, [const1_6]
	addsd xmm3, xmm4		; y = -0.04x + 0.85y +1.6

	jmp paint


else1:
	; if(rand >= p1 && rand < p12) (x,y) = (-0.15x + 0.28y, 0.26x + 0.24y + 0.44)
	cmp rdx, r9
	jge else2

	movsd xmm1, xmm0
	movsd xmm4, [constmin0_15]	; -0.15x
	mulsd xmm1, xmm4
	movsd xmm5, xmm2
	movsd xmm4, [const0_28]
	mulsd xmm5, xmm4		; 0.28y
	addsd xmm1, xmm5		; x = -0.15x + 0.28y

	movsd xmm3, xmm0
	movsd xmm4, [const0_26]
	mulsd xmm3, xmm4		; 0.26x
	movsd xmm5, xmm2
	movsd xmm4, [const0_24]
	mulsd xmm5, xmm4		; 0.24y
	addsd xmm3, xmm5		; 0.26x + 0.24y
	movsd xmm4, [const0_44]
	addsd xmm3, xmm4		; y = 0.26x + 0.24y + 0.44

	jmp paint

else2:
	; if (rand >= p12 && rand < p123) (x,y) = (0.20x - 0.26y, 0.23x + 0.22y + 1.6)
	cmp rdx, r10
	jge else3

	movsd xmm1, xmm0
	movsd xmm4, [const0_2]
	mulsd xmm1, xmm4		; 0.20x
	movsd xmm5, xmm2
	movsd xmm4, [const0_26]
	mulsd xmm5, xmm4		; 0.26y
	subsd xmm1, xmm5		; x = 0.20x - 0.26y

	movsd xmm3, xmm0
	movsd xmm4, [const0_23]
	mulsd xmm3, xmm4		; 0.23x
	movsd xmm5, xmm2
	movsd xmm4, [const0_22]
	mulsd xmm5, xmm4		; 0.22y
	addsd xmm3, xmm5		; 0.23x + 0.22y
	movsd xmm4, [const1_6]
	addsd xmm3, xmm4		; y = 0.23x + 0.22y + 1.6

	jmp paint

else3:
	; if (rand>= p1+p2+p3) (x,y) = (0, 0.16y)

	movsd xmm1, [const0_0]		; x = 0
	movsd xmm4, [const0_16]
	movsd xmm3, xmm2
	mulsd xmm3, xmm4		; y = 0.16y

paint:
    movsd xmm6, xmm0
    movsd xmm7, xmm1

	movsd xmm0, xmm1
    movsd xmm1, xmm3
    movsd xmm8, [const3_0]
    divsd xmm0, xmm8
    movsd xmm8, [const5_0]
    divsd xmm1, xmm8
    movsd xmm8, [const1_0]
    subsd xmm1, xmm8

    movsd xmm1, [const0_22]
    movsd xmm0, [const0_16]
    call putPixel
    movsd xmm0, xmm6
    movsd xmm1, xmm7



endWhile:
	movsd xmm0, xmm1		; x0 = x1
	movsd xmm2, xmm3		; y0 = y1

	dec rcx				; pozostale iteracje -= 1

	;cmp rcx, 0
	;jg whileIteration

exit:
	mov rsp, rbp
	pop rbp
	ret
