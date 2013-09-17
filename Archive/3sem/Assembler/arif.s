.intel_syntax noprefix
.globl arif 
.type arif; @function
arif:
  push ebx
  push eax
  mov edx,[esp+20]
  mov ecx,[esp+16]
  mov edx,[esp+12]
  imul 2
  mov ecx,ebx
  sub ecx,1
  xchg ecx,eax 
  imul edx
  add eax,ecx
  imul ebx
  cltd
  idiv 2
  pop ecx
  pop ebx
  ret
  