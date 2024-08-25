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

    if (attr.negative) {
      fputch('-', data);
    }
  }

  if (attr.uppercase) {
    fputch("0123456789ABCDEF"[num % attr.base], data);
  } else {
    fputch("0123456789abcdef"[num % attr.base], data);
  }
}

void vprintfmt(void (*fputch)(char, void *), void *data, const char *fmt,
               va_list ap) {
  int ch;
  unsigned long num;
  char *str;
  struct PrintNumAttr attr;

  while (1) {
    while ((ch = *fmt++) != '%') {
      fputch(ch, data);
      if (ch == '\0') {
        return;
      }
    }

    num = 0;
    attr.base = 0;
    attr.pad = ' ';
    attr.width = 0;
    attr.negative = 0;
    attr.uppercase = 0;
  reswitch:
    switch (ch = *fmt++) {
    case '0':
      attr.pad