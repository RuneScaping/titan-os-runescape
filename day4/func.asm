  ; [FORMAT "WCOFF"]
  [BITS 32]

  ; 程序中包含函数名
  GLOBAL io_hlt, io_cli, io_sti, io_stihlt
  GLOBAL io_in8, io_in16, io_in32
  GLOBAL io_out8, io_out16, io_out32
  GLOBAL io_load_eflags, io_store_eflags
  ; GLOBAL write_mem8

  [SECTION .text]
io_hlt:                 ; void io_hlt(void);
  HLT
  RET

io_cli:                 ; void io_cli(void);
  CLI
  RET

io_sti:                 ; void io_sti(void);
  STI
  RET

io_stihlt:              ; void io_stihlt(void);
  STI
  HLT
  RET

io_in8:                 ; int io_in8(int port);
