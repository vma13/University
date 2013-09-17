.intel_syntax noprefix
.globl longadd
.type longadd; @function
longadd:
  push ebx
  push esi
  push ecx
  mov ebx,[esp+20]
  mov esi,[esp+24]
  mov edx,[esp+16]
  mov ecx,[esp+28]
  clc
cycle:
  mov eax,[edx+4*ecx-4]
  adc eax,[ebx+4*ecx-4]
  mov [esi+4*ecx-4], eax
  loop cycle
  mov eax,esi
  pop ecx
  pop esi
  pop ebx
ret