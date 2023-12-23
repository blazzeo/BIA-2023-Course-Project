.586
    .model flat, stdcall
    includelib kernel32.lib
    includelib libucrt.lib
    includelib C:\StaticLib1.lib
    convertToNum PROTO : byte
    Strlen PROTO : byte
    printInt PROTO : dword
    printStr PROTO : byte
    printBool PROTO : byte
    ExitProcess PROTO : DWORD


.STACK 4096

.CONST
	l0	DWORD	15
	l1	DWORD	2
	l2	DWORD	20
	l3	DWORD	10
	l4	DWORD	1
	l5	DWORD	4
	l6	DWORD	10
	l7	DB	'54321', 0
	l8	DWORD	0
	l9	DWORD	10
	l10	DB	'length is less than 10', 0

.DATA

.CODE
square	PROC
	push	ebp
	mov	ebp, esp
	sub	esp, 0
;	EXPRESSION	2
	push	dword ptr[ebp+8]	; x
	push	dword ptr[ebp+12]	; y
;	multiply
	pop	eax
	pop	ebx
	mul	ebx
	push	eax
;	multiply
	push	dword ptr[ebp+16]	; z
;	multiply
	pop	eax
	pop	ebx
	mul	ebx
	push	eax
;	multiply
	pop	eax
	add	esp,	0
	pop	ebp
	ret 12
square	ENDP

main	PROC
	push	ebp
	mov	ebp, esp
	sub	esp, 24
;	EXPRESSION	7
	push	l0
	pop	eax
	mov	dword ptr [ebp-4], eax	; y
;	EXPRESSION	9
	push	l1
	push	l2
	push	l3
	push	l4
	call	square
	push	eax
	push	l5
;	plus
	pop	eax
	pop	ebx
	add	eax, ebx
	push	eax
;	plus
;	multiply
	pop	eax
	pop	ebx
	mul	ebx
	push	eax
;	multiply
	pop	eax
	mov	dword ptr [ebp-8], eax	; x
;	EXPRESSION	10
	push	dword ptr[ebp-8]	; x
	call	printInt
;	EXPRESSION	12
	push	offset l7
	pop	eax
	mov	dword ptr [ebp-12], eax	; str1
;	EXPRESSION	14
	push	1
	pop	eax
	mov	dword ptr [ebp+8], eax	; z
; IF
	mov	eax, dword ptr [ebp+8]	; z
	test	eax, eax
	jz	skip_if_0
;	EXPRESSION	16
	push	dword ptr[ebp-12]	; str1
	call	Strlen
	push	eax
	pop	eax
	mov	dword ptr [ebp+8], eax	; len
; IF
	push	dword ptr [ebp+8] ;	len0
	push	l9
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jne	skip_if_1
;	EXPRESSION	18
	push	dword ptr[ebp+8]	; len
	call	printInt
skip_if_1:
;	EXPRESSION	20
	push	offset l10
	call	printStr
skip_if_0:
;	EXPRESSION	23
	push	dword ptr[ebp-12]	; str1
	call	convertToNum
	push	eax
	pop	eax
	mov	dword ptr [ebp-24], eax	; num
;	EXPRESSION	24
	push	dword ptr[ebp-24]	; num
	call	printInt
;	EXPRESSION	25
	push	l8
	pop	eax
	add	esp,	24
	pop	ebp
	push	0
	call	ExitProcess
main	ENDP

end main
