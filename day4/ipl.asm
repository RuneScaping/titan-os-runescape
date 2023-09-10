; hello-os

CYLS   EQU   10               ; 读取的柱面数量（CYLS = cylinders）

  ORG   0x7c00            ; 指明程序的装载地址

; 用于标准FAT12格式的软盘
  JMP   entry             ; 跳转指令
  NOP                     ; NOP指令
  DB    "TTIPL   "        ; OEM标识符（8字节）
  DW    512               ; 每个扇区（sector）的字节数（必须为512字节）
  DB    1                 ; 每个簇（cluster）的扇区数（必须为1个扇区）