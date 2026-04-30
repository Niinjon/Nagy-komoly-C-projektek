#include <stdio.h>
#include <string.h>

#define VERSION "1.1.62"

typedef struct {
    int help;
    int version;
    int usage;
    int stdout_flag;
    const char *template_name;
} Config;

typedef struct 
{
    const char *name;
    const char *filename;
    const char *content;
} Template;

int get_template_count();
Template *get_templates();


int parse_args(int argc, char *argv[], Config *cfg) {

    for (int i = 1; i < argc; i++) {

        if (argv[i][0] == '-') {

            if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
                cfg->help = 1;

            else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version"))
                cfg->version = 1;

            else if (!strcmp(argv[i], "-u"))
                cfg->usage = 1;

            else if (!strcmp(argv[i], "--stdout"))
                cfg->stdout_flag = 1;

            else {
                printf("Unknown option: %s\n", argv[i]);
                return 0;
            }

        } else {
            if (!cfg->template_name)
                cfg->template_name = argv[i];
            else {
                printf("Too many arguments\n");
                return 0;
            }
        }
    }

    return 1;
}

void print_help() {
    printf("LazyCat - template generator\n\n");
    printf("Usage: LazyCat <template> [options]\n\n");


    printf("Templates: ");

    Template *t = get_templates();
    int count = get_template_count();

    for (int i = 0; i < count; ++i)
    {
        printf("%s", t[i].name);
        if (i < count - 1)
        {
            printf(", ");
        }
        
    }
    
    printf("\n\n");


    printf("Options:\n");
    printf("  -h, --help\n");
    printf("  -v, --version\n");
    printf("  -u\n");
    printf("  --stdout\n");
}

void print_version() {
    printf("LazyCat version %s\n", VERSION);
}

void print_usage() {
    printf("Usage: LazyCat <template> [options]\n");
}