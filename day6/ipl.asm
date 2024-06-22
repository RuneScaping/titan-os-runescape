; hello-os

CYLS   EQU   10               ; 读取的柱面数量（CYLS = cylinders）

  ORG   0x7c00            ; 指明程序的装载地址

; 用于标准FAT12格式的软盘
  JMP   entry             ; 跳转指令
  NOP                     ; NOP指令
  DB    "