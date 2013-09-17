.intel_syntax noprefix
.globl mysquare
.type mysquare, @function
qq: .double 0.5
mysquare:
 finit
 fld qword ptr, [esp+4]
 fmul st(0),  st(0)
 fld qword ptr qq
 fmul st(1), st(0)
ret

