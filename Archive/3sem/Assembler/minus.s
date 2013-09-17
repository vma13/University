	.intel_syntax noprefix
	.globl minus
	.type minus, @function
minus:
	push ebx
	push esi
	push ecx
  mov edx, [esp+16] ;/* array a*/
	mov ebx, [esp+20] ;/* array b*/
  mov esi, [esp+24]  ;/* array c */
	mov ecx, [esp+28] ;/* size array a*/
  mov edi, [esp+32] ;/*size array b*/
  clc                 ;/* clear the carry flage */
cycle1:
  mov eax, [ebx+ecx-1]
  neg eax
  mov [esi+ecx-1], eax
  loop cycle1
  
cycle2:	
	mov eax, [edx+ecx-1]
	adc [esi+ecx-1], eax
	loop cycle2

  mov eax, esi
	pop ecx
	pop esi
	pop ebx	
	ret	
  