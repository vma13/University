.intel_syntax noprefix
.globl mystrlen
.type mystrlen, @function
mystrlen:
	mov eax, 0
	mov edx, [esp+4]
	push ebx
	mov byte ptr bl, 0
	cycle: 
	cmp byte ptr bl,[edx]
	jz end
	add edx, 1
	add eax,1 //ploho
	jmp cycle //ploho
	end:
	pop ebx
	ret