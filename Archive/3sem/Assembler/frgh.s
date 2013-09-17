.intel_syntax no prefix
.globl myarif
.type myarif, @function
  averege
push ebx
mov eax, [esp+8]
add eax,[esp+12]
mov ebx, 2
cltd
div ebx	
pop ebx
ret