.intel_syntax noprefix
.globl mystrlen
.type mystrlen; @function
mystrcmp:
  mov edx, [esp+8]
  push ebx
  mov ebx, [esp+8]
cycle:
  mov byte ptr al, [ebx]
  cmp byte ptr al, [edx]
  jnz end
  cmp byte ptr al, 0
  inc ebx
  inc edx
  jmp cycle
end:
  sub byte ptr al, [edx]
  cbw
  cwde
  pop edx
ret