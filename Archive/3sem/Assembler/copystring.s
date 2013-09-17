.intel_syntax noprefix
.globl copystring
.type copystring, @function

copystring: 
push ebx
push ecx
push esi
mov edx,[esp+12]
xor ecx,ecx

cycle:
mov byte ptr bl,[esi+ecx]
cmp byte ptr bl, 0 
jz end
inc ecx
jmp cycle

end:
inc ecx
push ecx
call malloc
pop ecx

copycycle:
mov byte ptr bl,[esi+ecx-1]
mov byte ptr [eax+ecx-1],bl
loop copycycle 
pop ebx
ret
