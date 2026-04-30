#include <stdio.h>
#include <stdlib.h>

/* ===== STRUCTOK ===== */

typedef struct {
    int help;
    int version;
    int usage;
    int stdout_flag;
    const char *template_name;
} Config;

typedef struct {
    const char *name;
    const char *filename;
    const char *content;
} Template;

/* ===== FORWARD DECLARATION ===== */

int parse_args(int argc, char *argv[], Config *cfg);

/* design.c */
void print_design_help();
void print_design_full();
void print_design_usage();
void print_design_version();

/* cli.c */
void print_version();
void print_usage();

Template *find_template(const char *name);

int file_exists(const char *filename);
int write_file(const char *filename, const char *content);

/* ===== MAIN ===== */

int main(int argc, char *argv[])
{
    Config cfg = {0};print_design_help;

    if (!parse_args(argc, argv, &cfg))
    {    
        return 1;
    }
    /* Argumentum nélkül: teljes design help */
    if (argc == 1)
    {
        print_design_full();
        return 0;
    }
    
    /* control flag-ek */
    if (cfg.help)
    {
        print_design_help();
        return 0;
    }

    if (cfg.version)
    {
        print_design_version();
        return 0;
    }

    if (cfg.usage)
    {
        print_design_usage();
        return 0;
    }

    /* innentől kell template */
    if (!cfg.template_name)
    {
        printf("No template specified!\n");
        return 1;
    }

    Template *tpl = find_template(cfg.template_name);

    if (!tpl)
    {
        printf("Unknown template!\n");
        return 1;
    }

    if (cfg.stdout_flag)
    {
        printf("%s", tpl->content);
        return 0;
    }

    if (file_exists(tpl->filename))
    {
        printf("File already exists: %s\n", tpl->filename);
        return 1;
    }

    if (!write_file(tpl->filename, tpl->content))
    {
        return 1;
    }
    printf("Created %s\n", tpl->filename);
    return 0;
}