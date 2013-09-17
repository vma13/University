intel_syntax noprefix
.globl array_to_digit
.type array_to_digit,@function

array_to_digit:
push edx
push ecx
mov edx,[esp+12]
mov ecx,[esp+16]
cmp ecx,0
jz end
mov edi,0

cycle:

mov bl,[edx+ecx-1]
add edi,bl
loop cycle
mov ebx,100
sub ebx,edi


end:
pop ecx
pop edx
ret

