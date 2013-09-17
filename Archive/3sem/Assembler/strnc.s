.intel_syntax noprefix
.globl strnc
.type srtnc; @function
strnc:
 push ebx
 push ecx
 mov eax,[esp+12]
 mov ebx,[esp+16]
 mov ecx,[esp+20]
 push esi
 mov esi,eax
 push ebx
 mov byte ptr b1,0
 c1:
 cmp[esi],d1
 jz next
 inc esi
 jmp c1
 next:
 dec ecx
 cycle:
 cmp [edi],d1
 jnz true
 jmp end
 true:
 mov byte ptr b1,[edi]
 mov [esi],b1
 inc esi
 inc edi
 loop cycle
 end:
 mov byte ptr b1,[edi]
 mov [esi],b1
 pop ebx
 pop esi
 pop ecx
 pop edi
 ret
 