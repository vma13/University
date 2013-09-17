.intel_syntax noprefix
.globl mystrcmp
.type mystrcmp, @function
mystrcmp:
	mov esi, [esp+4]
	mov edi, [esp+8]

main_loop:
	mov cl, [esi]
        mov dl, [edi]
        cmp cl, '$'
        je end_of_line
        cmp cl, dl
        jb below
        ja above
        inc esi
        inc edi
        jmp main_loop
	
end_of_line:                                                        
	cmp dl, '$'
	je match
	jmp below
	
below:
	mov eax, -1
	ret
	
above:
	mov eax, 1
	ret
	
match:
	mov eax, 0
	ret
	

