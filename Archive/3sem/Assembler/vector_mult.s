.intel_syntax noprefix
.global vector_mult
.type vector_mult, @function
vector_mult:
		push ebx 		
		push edi
    		push esi
		push ecx
		mov ebx, [esp+20] 	
   		mov edi, [esp+24] 	
   		mov esi, [esp+28] 	
		
		mov ax, [ebx+2]		
		mov cx, [edi+4]		
		mul cx			
		mov [esi], ax 		
		mov ax, [ebx+4] 	
		mov cx, [edi+2]		
		mul cx			
		sub [esi], ax 		

		mov ax, [ebx+4]		
		mov cx, [edi] 		
		mul cx			
		mov [esi+2], ax				
		mov ax, [ebx] 		
		mov cx, [edi+4] 	
		mul cx			
		sub [esi+2], ax		

 		mov ax, [ebx]		
		mov cx, [edi+2]		
		mul cx			
		mov [esi+4], ax		
		mov ax, [ebx+2]		
		mov cx, [edi]		
		mul cx			
		sub [esi+4],ax     
		mov eax,esi		

		pop ebx 		
		pop edi
    pop esi
		pop ecx
		ret			
