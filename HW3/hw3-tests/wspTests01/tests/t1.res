---begin global scope---
print (STRING) -> VOID
printi (INT) -> VOID
main () -> VOID
printOk (BOOL) -> VOID
  ---begin scope---
  x INT 0
  y BYTE 1
  z INT 2
  ---end scope---
  ---begin scope---
  isOk BOOL -1
  i INT 0
    ---begin scope---
      ---begin scope---
      ---end scope---
    ---end scope---
    ---begin scope---
      ---begin scope---
      x INT 1
      ---end scope---
    ---end scope---
    ---begin scope---
    ---end scope---
  ---end scope---
---end global scope---
