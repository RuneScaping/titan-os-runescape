  [BITS 32]

  GLOBAL asm_int_handler21, asm_int_handler27, asm_int_handler2c

  EXTERN int_handler21, int_handler27, int_handler2c

asm_int_handler21:
  PUSH    ES
  PUSH    DS
  PUSHA