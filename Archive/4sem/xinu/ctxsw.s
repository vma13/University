.intel_syntax noprefix
.globl _ctxsw 
.type _ctxsw, @function
	
_ctxsw:	
		mov [esp - 4], eax  //old eax, чтобы его портить
		mov eax, [esp + 4]  //еах - указатель н амассив оld
		mov [eax + 4], ebx  //old ebx
		mov ebx, [esp - 4]  //в ebx положили старый еах
		mov [eax], ebx      //eax -> ebx
		mov [eax + 8], ecx  //кладем регистры old
		mov [eax + 12], edx 
		mov [eax + 16], esi 
		mov [eax + 20], edi 
		mov [eax + 24], ebp 
		mov [eax + 28], esp
	        pushf               //сохранить состояние процессора в esp
		mov ebx, [esp]      //то что в esp положить в ebx
		mov [eax + 32], ebx //сохраяем флаги в eax+32
	        add esp, 4          //добавить 4 к esp(вернуть в esp)
		mov ebx, [esp]      //положить адрес возврата в ebx
		mov [eax + 36], ebx //кладем адрес возврата в eax+36
		mov eax, [esp + 8]  //eax - указатель на массив new
		mov ecx, [eax + 8]  //кладем регистр ecx в eax+8 и т.д.
		mov edx, [eax + 12] 
		mov esi, [eax + 16] 
		mov edi, [eax + 20] 
		mov ebp, [eax + 24] 
		mov esp, [eax + 28] 
		mov ebx, [eax + 32] //eax+32 положить в ebx(флаги)
		push ebx            //в стэк запихиваем флаги(в новом стэке(new))
		mov ebx, [eax + 36] //eax+36(адрес возврата нового процесса) положить в ebx
		push ebx	    //в стэк запихиваем адрес возврата нового процесса(в новом стэке(new))
		mov ebx, [eax + 4]  //еах+4 кладем в ebx
		mov eax, [eax]      //eax -> eax
		iret                //возврат из прерывания(восстанавливаем флаги)
	
