.intel_syntax noprefix
.globl array_to_digit
.type array_to_digit,@function
array_to_digit:
                  push edx
                  push ecx
                  mov edx,[esp+12]
                  mov ecx,[esp+16]
                  mov edi, 0
                  cmp ecx,0
                  jz end
cycle:
                  mov esi,[edx+2*ecx-2]
                  add edi,esi
                  loop cycle          
                  
                  mov eax,edi
                  mov esi,2
                  xor edx,edx
                  div esi
                  cmp edx,0
                  jz one
                  mov eax,0
                  pop ecx
                  pop edx
                  ret
one:
                  mov eax, 1 
                  pop ecx
                  pop edx
                  ret
end:
                 mov eax,0
                  pop ecx
                  pop edx
                  ret
                      
