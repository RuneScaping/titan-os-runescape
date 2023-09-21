
#include <stdio.h>

#include "io.h"
#include "pm.h"

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void box_fill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0,
               int x1, int y1);
void init_screen(unsigned char *vram, int x, int y);
void put_font8(unsigned char *vram, int xsize, int x, int y, char c,
               char *font);
void put_fonts8_asc(unsigned char *vram, int xsize, int x, int y, char c,
                    char *s);
void init_mouse_cursor8(char *mouse, char bc);
void put_block8_8(unsigned char *vram, int vxsize, int pxsize, int pysize,
                  int px0, int py0, char *buf, int bxsize);

#define COL8_000000 0
#define COL8_FF0000 1
#define COL8_00FF00 2
#define COL8_FFFF00 3
#define COL8_0000FF 4
#define COL8_FF00FF 5
#define COL8_00FFFF 6
#define COL8_FFFFFF 7
#define COL8_C6C6C6 8
#define COL8_840000 9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

struct BootInfo { // 12 Bytes
  char cyls, leds, vmode, reserve;// ff0 ff1 ff2 vmode:颜色数目信息    ff3
  short scrnx, scrny;//屏幕分辨率(行列像素) 0x0ff4 0x0ff6
  unsigned char *vram;//显存缓冲区 0x0ff8
};

struct SegmentDescriptor {
  short limit_low, base_low; // 段大小限制低位， 基址低位
  char base_mid, access_right; // 基址中位，访问权限
  char limit_high, base_high; // 段大小限制高位，基址高位
};

struct GateDescriptor {
  short offset_low, selector;
  char dw_count, access_right;
  short offset_high;
};

void init_gdtidt(void);
void set_segmdesc(struct SegmentDescriptor *sd, unsigned int limit, int base,
                  int ar);
void set_gatedesc(struct GateDescriptor *gd, int offset, int selector, int ar);

int main(void) {
  struct BootInfo *binfo = (struct BootInfo *)0x0ff0;//对齐启动区
  char s[40], mcursor[256];

  init_gdtidt();
  init_palette();

  init_screen(binfo->vram, binfo->scrnx, binfo->scrny);

  int mx = (binfo->scrnx - 16) / 2;
  int my = (binfo->scrny - 28 - 16) / 2;
  init_mouse_cursor8(mcursor, COL8_840084);
  put_block8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);

  put_fonts8_asc(binfo->vram, binfo->scrnx, 8, 8, COL8_FFFFFF, "Hello, welcome to titanic OS.");
  put_fonts8_asc(binfo->vram, binfo->scrnx, 31, 31, COL8_000000,
                 "titanic OS.");
  put_fonts8_asc(binfo->vram, binfo->scrnx, 30, 30, COL8_FFFFFF,
                 "titanic OS.");

  sprintf(s, "print variable `scrnx` = %d", binfo->scrnx);
  put_fonts8_asc(binfo->vram, binfo->scrnx, 16, 64, COL8_FFFFFF, s);

  for (;;) {
    io_hlt();
  }

  return 0;
}

void init_palette(void) {
  static unsigned char table_rgb[16 * 3] = {
      0x00, 0x00, 0x00, // 黑色
      0xff, 0x00, 0x00, // 亮红色
      0x00, 0xff, 0x00, // 亮绿色
      0xff, 0xff, 0x00, // 亮黄色
      0x00, 0x00, 0xff, // 亮蓝色
      0xff, 0x00, 0xff, // 亮紫色
      0x00, 0xff, 0xff, // 浅亮蓝色
      0xff, 0xff, 0xff, // 白色
      0xc6, 0xc6, 0xc6, // 亮灰色
      0x84, 0x00, 0x00, // 暗红色
      0x00, 0x84, 0x00, // 暗绿色
      0x84, 0x84, 0x00, // 暗黄色
      0x00, 0x00, 0x84, // 暗蓝色
      0x84, 0x00, 0x84, // 暗紫色
      0x00, 0x84, 0x84, // 浅暗蓝色
      0x84, 0x84, 0x84  // 暗灰色
  };

  set_palette(0, 15, table_rgb);
}

void set_palette(int start, int end, unsigned char *rgb) {
  int eflags = io_load_eflags(); // 记录标志

  io_cli(); // 禁止中断

  io_out8(0x03c8, start);
  for (int i = start; i <= end; i++) {
    io_out8(0x03c9, rgb[0] / 4);
    io_out8(0x03c9, rgb[1] / 4);
    io_out8(0x03c9, rgb[2] / 4);
    rgb += 3;
  }

  io_store_eflags(eflags);
}

void box_fill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0,
               int x1, int y1) {
  for (int y = y0; y <= y1; y++) {