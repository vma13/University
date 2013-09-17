.intel_syntax no prefix
.globl square
.type square, @function
qq: .double 0.5
square:
 finit
 fld qword ptr, [esp+4]
 fld qword ptr, [esp+8]
 fmul st(0), st(1)
 fld qword ptr qq
 fmul st(0), st(1)
ret



