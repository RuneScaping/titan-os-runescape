#include "desctbl.h"
#include "int.h"

void init_gdtidt(void) {
  struct SegmentDescriptor *gdt = (struct SegmentDescriptor *)ADR_GDT;
  struct Ga