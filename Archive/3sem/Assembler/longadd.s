.intel_syntax noprefix
.globl longadd
.type longadd, @function
//int longadd(int *a, int *b, int *c, n);

longadd:
	push ebx
	push esi
	push ecx
	mov ebx,[esp+20]
	mov esi,[esp+24]
	mov edx,[esp+16]
	mov ecx,[esp+28]

	clc //Clear Carry

cycle: 

// edx+(ecx-1)*4 = [edx +4*ecx-4]

	mov eax, [edx+4*ecx-4]
	adc eax, [edx+4-ecx-4]
	mov [esi+4*ecx-4],eax
	// lea ecx,[ecx-1] вычитание не арифметическое
	loop cycle
	
	mov eax,esi
	pop ecx
	pop esi
	pop ebx
	ret
