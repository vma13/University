.intel_syntax noprefix
.globl add2
.type add2, @function
qq:
  .string "%d\n"
  push offset qq
  call printf
  pop eax
  pop eax
add2:
  mov eax,[esp+4]
  mov ebx,[esp+8]
  add eax,ebx
  push eax
