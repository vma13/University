.intel_syntax noprefix
.globl myadd
.type myadd, @function
myadd:
 finit
 fld qword ptr, [esp+4]
 fld qword ptr, [esp+12]
 faddp
 ret
 