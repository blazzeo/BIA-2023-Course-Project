.586
    .model flat, stdcall
    includelib kernel32.lib
    includelib libucrt.lib
    includelib StaticLib.lib
    EXTRN convertToNum: PROC
    EXTRN Strlen: PROC
    EXTRN printInt: PROC
    EXTRN printStr: PROC
    EXTRN printBool: PROC
    ExitProcess PROTO : DWORD


.STACK 4096

.CONST
	l0	DWORD	15
	l1	DWORD	20
	l2	DWORD	4
	l3	DWORD	10
	l4	DB	'54321', 0
	l5	DWORD	0
	l6	DWORD	10
	l7	DB	'length is less than 10', 0

.DATA

.CODE
square	PROC
	push	ebp
	mov	ebp, esp
	sub	esp, 0
;	EXPRESSION
	push	dword ptr[ebp+12]
	push	dword ptr[ebp+12]
;	multiply
	pop	eax
	pop	ebx
	mul	ebx
	push	eax
;	multiply
	pop	eax
	add	esp,	0
	pop	ebp
	add	esp,	8
	ret
square	ENDP

main	PROC
	push	ebp
	mov	ebp, esp
	sub	esp, 28
;	EXPRESSION
	push	offset l0
	mov	dword ptr [ebp-4], eax	;7
;	EXPRESSION
	push	offset l1
	call	square
	push	eax
	push	offset l2
;	plus
	pop	eax
	pop	ebx
	add	eax, ebx
	push	eax
;	plus
	mov	dword ptr [ebp-8], eax	;9
;	EXPRESSION
	push	dword ptr[ebp-8]
	call	printInt	;10
;	EXPRESSION
	push	offset l4
	mov	dword ptr [ebp-19], eax	;12
;	EXPRESSION
	mov	dword ptr [ebp+9], eax	;14
	mov	eax, dword ptr [ebp+0]
	test	eax, eax
	jz	skip_if_0
;	EXPRESSION
	push	dword ptr[ebp-19]
	call	Strlen
	push	eax
	mov	dword ptr [ebp+12], eax	;16
	push	dword ptr [ebp+0]
	push	offset l6
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jne	skip_if_1
;	EXPRESSION
	push	dword ptr[ebp+12]
	call	printInt	;18
skip_if_1:
;	EXPRESSION
	push	offset l7
	call	printStr
skip_if_0:
;	EXPRESSION
	push	dword ptr[ebp-19]
	call	convertToNum
	push	eax
	mov	dword ptr [ebp-28], eax	;23
;	EXPRESSION
	push	dword ptr[ebp-28]
	call	printInt	;24
;	EXPRESSION
	push	offset l5
	pop	eax
	add	esp,	28
	pop	ebp
	call	ExitProcess
main	ENDP

end main
