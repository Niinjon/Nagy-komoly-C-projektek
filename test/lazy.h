#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* ===== VERSION ===== */

#define VERSION "1.1.168"

/* ===== OS DETECT ===== */

#if defined(_WIN32) || defined(_WIN64)
    #define LAZYCAT_OS_WINDOWS 1
    #define LAZYCAT_OS_NAME "Windows"
#else
    #define LAZYCAT_OS_WINDOWS 0
    #define LAZYCAT_OS_NAME "Unix-like"
#endif

#define WINDOWS_MODE LAZYCAT_OS_WINDOWS

/* ===== CONFIG ===== */

typedef struct {
    int help;
    int version;
    int usage;
    int stdout_flag;
    const char *template_name;
} Config;

/* ===== TEMPLATE ===== */

typedef struct {
    const char *name;
    const char *filename;
    const char *content;
} Template;

/* ===== CLI ===== */

int parse_args(int argc, char *argv[], Config *cfg);

void print_help();
void print_version();
void print_usage();

/* ===== DESIGN ===== */

void print_design_full();
void print_design_help();
void print_design_usage();
void print_design_version();

/* ===== TEMPLATE ===== */

Template *find_template(const char *name);

Template *get_templates();
int get_template_count();

/* ===== IO ===== */

int file_exists(const char *filename);
int write_file(const char *filename, const char *content);

#endif