	.intel_syntax noprefix
	.globl strcat
	.type strcat, @function
strcat:	
	push ebx
	push esi
	mov eax, [esp+12]
	mov ebx, [esp+16]
	mov esi, eax
	push edi
	mov byte ptr dl, 0
cycle:
	cmp [esi], dl
	jz cycle2
	inc esi
	jmp cycle
cycle2:
	cmp [ebx], dl
	jz end
	mov edi, [ebx]
	mov [esi], edi
	inc ebx
	inc esi
	loop cycle2
end:
	mov edi, [ebx]
	mov [esi], edi
	pop edi
	pop esi
	pop ebx
	ret


