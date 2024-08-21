#include <stdarg.h>
#include <stdio.h>

struct SprintBuf {
  char *buf;
  int count;
};

struct PrintNumAttr {
  int base;
  int width;
  int pad;
  int uppercase;
  int negative;
};

void printnum(void (*fputch)(char, void *), void *data, unsigned long num,
              struct PrintNumAttr attr) {
  if (num >= attr.base) {
    attr.width -= 1;
    printnum(fputch, data, num / attr.base, attr);
  } else {
    while (--attr.width > attr.negative) {
      fputch(attr.pad, data);
    }
