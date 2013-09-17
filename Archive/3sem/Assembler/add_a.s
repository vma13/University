.intel_syntax noprefix
.globl add_a
.type add_a, @function

add_a:
  push ebx
  mov ebx,[esp+8]
  push ebx
  call strlen
  pop ebx
  mov dl, 'a'
  mov [ebx+eax],dl
  mov dl,0
  mov [ebx+eax+1],dl
  mov eax,ebx
  pop ebx
  ret
  