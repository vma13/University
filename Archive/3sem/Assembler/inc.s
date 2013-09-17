.intel_syntax noprefix
.globl myinc
.type myinc,@function
myinc:
	mov eax,[esp+4]
	add eax,1
	ret
