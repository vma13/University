.intel_syntax noprefix
.globl maxdig
.type maxdig, @function
maxdig:
   finit
   fld qword ptr, [esp+4]
   fld qword ptr, [esp+12]
   fcomi st(1),st(0)
   jc second
   ffree st(1)
second:
   fxch
   ffree st(1)
   ret
 