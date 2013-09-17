.intel_syntax noprefix
.globl arif2 
.type arif2; @function
arif2:
  push ebx
  push esi
  mov edx,[esp+20]
  mov ecx,[esp+16]
  mov ebx,[esp+12]
  add edx,ebx
  imul edx
  shr eax.1
  pop ecx
  pop esi
  ret