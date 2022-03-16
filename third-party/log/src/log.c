/*
 * Copyright (c) 2020 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/* Modifications :
 * 12.3.22 (Shivashish Das) - Modified the file to remove some features and add some more so that log.c's functions can easily be used by the JVM to report errors and record traces */

#include "log.h"

#include <cmdparser.h>
void exit(int status);


static FILE* log_file = 0;
static const char *level_strings[] = {
  "VM Trace :", "Info :", "VM Warning : ","Fatal VM Error :"
};


static void stdout_callback(log_Event *ev) {
	fprintf(stderr, "%s ", level_strings[ev->level]);
	vfprintf(stderr, ev->fmt, ev->ap);
	fprintf(stderr, "\n");
	fflush(stderr);
}


static void file_callback(log_Event *ev) {
	char buf[64];
	buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ev->time)] = '\0';
	fprintf(log_file, "%s %-5s %s:%d: ", buf, level_strings[ev->level], ev->file, ev->line);
	vfprintf(log_file, ev->fmt, ev->ap);
	fprintf(log_file, "\n");
	fflush(log_file);
}



static void init_event(log_Event *ev) {
	if (!ev->time) {
		time_t t = time(NULL);
		ev->time = localtime(&t);
	}
}

void set_file_target(FILE* fptr) {
	log_file = fptr;
}

void log_log (int level, const char* file , int line, const char* fmt,...) {
	log_Event ev = {                                             
		.fmt   = fmt,
		.file  = file,
		.line  = line,
		.level = level,
	};

	init_event(&ev);
	va_start(ev.ap, fmt);
	/* Shivashish Das 13.3.22 :
         * Don't log traces unless we are running on verbose mode */
	if ((level == TRACE && is_verbose()) || level !=TRACE)
		stdout_callback(&ev);
	if (log_file)
		file_callback(&ev);
	va_end(ev.ap);

	if (level == FATAL)
		exit(1);
}
