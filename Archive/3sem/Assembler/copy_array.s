.intel_syntax noprefix
.globl copy_array
.type copy_array,@function
copy_array:
push ecx
push ebx
push esi
mov edx,[esp+16]
mov eax,[esp+20]
mov ebx,[esp+24]
mov ecx,1
cycle:
mov esi,[edx+2*ecx]
mov [edx+ecx],esi
shl esi,1
cmp esi,ebx
js cycle
pop esi
pop ebx
pop ecx
ret