	.intel_syntax noprefix
	.globl asm_strncpy
	.type asm_strncpy, @function
asm_strncpy:	
	push ebx
	push ecx
	push esi
	mov eax, [esp+16]
	mov ebx, [esp+20]
	mov ecx, [esp+24]
	mov esi, eax
	push edi
	mov byte ptr dl, 0
cycle:
	cmp ecx, 0
	je end
	cmp [ebx], dl
	jz end
	mov edi, [ebx]
	mov [esi], edi
	inc ebx
	inc esi
	dec ecx
	jmp cycle
end:
	mov [esi], dl	
	pop edi
	pop esi
	pop ecx
	pop ebx
	ret

