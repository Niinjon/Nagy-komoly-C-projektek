#include <stdio.h>

#define BOLD  "\033[1m"
#define RESET "\033[0m"
#define PAD   "  "

int get_template_count();

typedef struct {
    const char *name;
    const char *filename;
    const char *content;
} Template;

Template *get_templates();


static const char *LOGO_ART[] = {
    " _                      ____      _   ",
    "| |    __ _ _____  _   / ___|__ _| |_ ",
    "| |   / _` |_  / || | | |   / _` | __|",
    "| |__| (_| |/ /| || | | |__| (_| | |_ ",
    "|_____\\__,_/___|\\_, |  \\____\\__,_|\\__|",
    "                |__/                  ",
    NULL
};

static const char *CAT_ART[] = {
    "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x5a",
    "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x5a",
    "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7a",
    "\x20\x20\x20\x20\x20\x20\xef\xbc\x8f\xef\xbc\x9e\x20\x20\x20\x20\xe3\x83\x95",
    "\x20\x20\x20\x20\x20\x20\x7c\x20\xe3\x80\x80\x5f\x20\x20\x5f\x7c",
    "\x20\x20\x20\x20\x20\xef\xbc\x8f\x60\xe3\x83\x9f\x5f\x78\x5f\xe3\x83\x8e",
    "\x20\x20\x20\x20\x20\x2f\xe3\x80\x80\xe3\x80\x80\xe3\x80\x80\x20\x7c",
    "\x20\x20\x20\x20\x2f\xe3\x80\x80\x20\xe3\x83\xbd\xe3\x80\x80\x20\xef\xbe\x89",
    "\x20\x20\x20\xe2\x94\x82\xe3\x80\x80\xe3\x80\x80\x7c\x20\x7c\x20\x7c",
    "\xef\xbc\x8f\xef\xbf\xa3\x7c\xe3\x80\x80\x20\x7c\x20\x7c\x20\x7c",
    "\x7c\x28\xef\xbf\xa3\xe3\x83\xbd\x5f\x5f\xe3\x83\xbd\x5f\x29\x5f\x29",
    "\xef\xbc\xbc\xe4\xba\x8c\xe3\x81\xa4",
    NULL
};

void print_design_full() {

    printf("\n");

    /* Logo - pad=6 */
    for (int i = 0; LOGO_ART[i]; i++)
        printf(PAD "      " BOLD "%s" RESET "\n", LOGO_ART[i]);

    printf("\n");

    /* Cat - pad=17 */
    for (int i = 0; CAT_ART[i]; i++)
        printf(PAD "                 %s\n", CAT_ART[i]);

    /* Tagline - pad=10 */
    printf("\n");
    printf(PAD "                template generator\n\n");

    /* Separator */
    printf(PAD "---------------------------------------------------\n\n");

    /* ---- USAGE ---- */
    printf(PAD "+-------------------------------------------------+\n");
    printf(PAD "| " BOLD "\xf0\x9f\x93\x8b USAGE" RESET "                                        |\n");
    printf(PAD "|                                                 |\n");
    printf(PAD "|   LazyCat <template> [options]                  |\n");
    printf(PAD "|                                                 |\n");
    printf(PAD "+-------------------------------------------------+\n\n");

    /* ---- TEMPLATES ---- */
    printf(PAD "+-------------------------------------------------+\n");
    printf(PAD "| " BOLD "\xf0\x9f\x93\x81 TEMPLATES" RESET "                                    |\n");
    printf(PAD "|                                                 |\n");

    Template *t = get_templates();
    int count = get_template_count();
    for (int i = 0; i < count; i += 2) {
        if (i + 1 < count)
            printf(PAD "|   \xe2\x96\xb8 %-14s  \xe2\x96\xb8 %-14s            |\n",
                   t[i].name, t[i+1].name);
        else
            printf(PAD "|   \xe2\x96\xb8 %-14s                              |\n",
                   t[i].name);
    }

    printf(PAD "|                                                 |\n");
    printf(PAD "+-------------------------------------------------+\n\n");

    /* ---- OPTIONS ---- */
    printf(PAD "+-------------------------------------------------+\n");
    printf(PAD "| " BOLD "\xe2\x9a\x99\xef\xb8\x8f OPTIONS" RESET "                                      |\n");
    printf(PAD "|                                                 |\n");
    printf(PAD "|   -h, --help     Show this help message         |\n");
    printf(PAD "|   -v, --version  Show version information       |\n");
    printf(PAD "|   -u             Show usage information         |\n");
    printf(PAD "|   --stdout       Show templates content         |\n");
    printf(PAD "|                                                 |\n");
    printf(PAD "+-------------------------------------------------+\n\n");

    printf(PAD "---------------------------------------------------\n");
    printf(PAD "   LazyCat v1.1.162  *  simple. fast. lazy.\n");
    printf(PAD "---------------------------------------------------\n\n");
}


void print_design_help() {

    printf("\n");

    /* Logo - pad=6 */
    for (int i = 0; LOGO_ART[i]; i++)
        printf(PAD "      " BOLD "%s" RESET "\n", LOGO_ART[i]);

    printf("\n");

    /* Cat - pad=17 */
    for (int i = 0; CAT_ART[i]; i++)
        printf(PAD "                 %s\n", CAT_ART[i]);

    /* Tagline - pad=10 */
    printf("\n");
    printf(PAD "                template generator\n\n");

    /* Separator */
    printf(PAD "---------------------------------------------------\n\n");

    /* ---- USAGE ---- */
    printf(PAD "+-------------------------------------------------+\n");
    printf(PAD "| " BOLD "\xf0\x9f\x93\x8b USAGE" RESET "                                        |\n");
    printf(PAD "|                                                 |\n");
    printf(PAD "|   LazyCat <template> [options]                  |\n");
    printf(PAD "|                                                 |\n");
    printf(PAD "+-------------------------------------------------+\n\n");

    /* ---- TEMPLATES ---- */
    printf(PAD "+-------------------------------------------------+\n");
    printf(PAD "| " BOLD "\xf0\x9f\x93\x81 TEMPLATES" RESET "                                    |\n");
    printf(PAD "|                                                 |\n");

    Template *t = get_templates();
    int count = get_template_count();
    for (int i = 0; i < count; i += 2) {
        if (i + 1 < count)
            printf(PAD "|   \xe2\x96\xb8 %-14s  \xe2\x96\xb8 %-14s            |\n",
                   t[i].name, t[i+1].name);
        else
            printf(PAD "|   \xe2\x96\xb8 %-14s                              |\n",
                   t[i].name);
    }

    printf(PAD "|                                                 |\n");
    printf(PAD "+-------------------------------------------------+\n\n");

    /* ---- OPTIONS ---- */
    printf(PAD "+-------------------------------------------------+\n");
    printf(PAD "| " BOLD "\xe2\x9a\x99\xef\xb8\x8f OPTIONS" RESET "                                      |\n");
    printf(PAD "|                                                 |\n");
    printf(PAD "|   -h, --help     Show this help message         |\n");
    printf(PAD "|   -v, --version  Show version information       |\n");
    printf(PAD "|   -u             Show usage information         |\n");
    printf(PAD "|   --stdout       Show templates content         |\n");
    printf(PAD "|                                                 |\n");
    printf(PAD "+-------------------------------------------------+\n\n");

}


void print_design_usage() 
{
    printf("\n");

    /* Logo - pad=6 */
    for (int i = 0; LOGO_ART[i]; i++)
        printf(PAD "      " BOLD "%s" RESET "\n", LOGO_ART[i]);

    printf("\n");

    /* Cat - pad=17 */
    for (int i = 0; CAT_ART[i]; i++)
        printf(PAD "                 %s\n", CAT_ART[i]);

    /* Tagline - pad=10 */
    printf("\n");
    printf(PAD "                template generator\n\n");

    /* Separator */
    printf(PAD "---------------------------------------------------\n\n");

    /* ---- USAGE ---- */
    printf(PAD "+-------------------------------------------------+\n");
    printf(PAD "| " BOLD "\xf0\x9f\x93\x8b USAGE" RESET "                                        |\n");
    printf(PAD "|                                                 |\n");
    printf(PAD "|   LazyCat <template> [options]                  |\n");
    printf(PAD "|                                                 |\n");
    printf(PAD "+-------------------------------------------------+\n\n");
}


void print_design_version()
{
    
    printf("\n");

    /* Logo - pad=6 */
    for (int i = 0; LOGO_ART[i]; i++)
        printf(PAD "      " BOLD "%s" RESET "\n", LOGO_ART[i]);

    printf("\n");

    /* Cat - pad=17 */
    for (int i = 0; CAT_ART[i]; i++)
        printf(PAD "                 %s\n", CAT_ART[i]);

    /* Tagline - pad=10 */
    printf("\n");
    printf(PAD "                template generator\n\n");

    /* Separator */
    printf(PAD "---------------------------------------------------\n\n");
    
    
    printf(PAD "---------------------------------------------------\n");
    printf(PAD "   LazyCat v1.1.162  *  simple. fast. lazy.\n");
    printf(PAD "---------------------------------------------------\n\n");
}
