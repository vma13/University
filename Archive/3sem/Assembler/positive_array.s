.intel_syntax noprefix
.globl positive_array
.type positive_array, @function

positive_array:
  push ebx
  push edx
  mov edx,[esp+12]
  mov ebx,[esp+16]
  mov ecx,[esp+20]
  push esi
  push edi
  xor esi,esi
  
cycle:
  cmp [edx],esi
  js neg
  mov edi,[edx]
  mov [ebx+4*eax],edi
  inc eax
  
neg:
  add edx,4
  dec ecx
  cmp ecx,0
  jz end
  jmp cycle
  pop edi
  pop esi
  pop ecx
  pop ebx
  ret