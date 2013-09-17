.intel_syntax noprefix 
.globl sum
.type sum, @function
  
sum:
push ecx 
push ebx
push esi 
push edi

mov ecx, 7
mov ebx, 22
mov edi, 121
xor esi, esi

cmp esi, ecx
je end
cmp esi, ebx
ja end
cmp esi,  11
ja sum2_if
je sum3_else

sum2_if:
mov esi,  [esi + 2]
loop sum2_if

sum3_else:
mov esi, ebx
div ebx
mov edi, esi
loop sum3_else

end:
pop ecx
pop ebx
pop esi
pop edi

ret
