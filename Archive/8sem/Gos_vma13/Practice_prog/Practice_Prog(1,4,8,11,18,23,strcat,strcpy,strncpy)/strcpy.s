	.intel_syntax noprefix
	.globl strcpy
	.type strcpy, @function
strcpy:	
	push ebx
	push esi
	mov eax, [esp+12]
	mov ebx, [esp+16]
	mov esi, eax
	push edi
	mov byte ptr dl, 0
cycle:
	cmp [ebx], dl
	jz end
	mov edi, [ebx]
	mov [esi], edi
	inc ebx
	inc esi
	loop cycle
end:
	mov edi, [ebx]
	mov [esi], edi
	pop edi
	pop esi
	pop ebx
	ret

