#pragma once
#ifndef Z80_
#define Z80_

typedef struct s_clock {
  int _m;
  int _t;
} t_clock;

typedef struct s_registry {
  unsigned char _a;
  unsigned char _b;
  unsigned char _c;
  unsigned char _d;
  unsigned char _e;
  unsigned char _f;
  unsigned char _l;
  unsigned char _h;
  unsigned char flags;
  unsigned short sp;
  unsigned short pc;
} t_registry;

typedef struct Z80 {
  t_clock clock;
  t_registry reg;

  void (*ADD_e)();
};

struct op_s {
  char *mnemo;
  char *byte_value;
  char *comment;
  void (*func)(void *);
};

typedef struct op_s op_t;

#endif
