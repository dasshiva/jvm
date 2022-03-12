/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#define LOG_VERSION "0.1.0"

typedef struct {
  va_list ap;
  const char *fmt;
  const char *file;
  struct tm *time;
  void *udata;
  int line;
  int level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

enum { TRACE, DEBUG, INFO, WARN, ERROR, FATAL };

void log_stderr(int level, const char *fmt, ...);
void log_f(FILE* fptr, int level, const char* file , int line, const char* fmt,...);

#define log_file(...) log_f(fptr,level,__FILE__,__LINE__,__VA_ARGS__)

#endif
