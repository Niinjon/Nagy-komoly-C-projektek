#include "lazy.h"

/* ===== DESIGN MACROS ===== */

#define PAD "  "
#define BOLD "\033[1m"
#define RESET "\033[0m"

/* ===== ASCII LOGÓ ===== */

const char *LOGO_ART[] = {
    " _                      ____      _   ",
    "| |    __ _ _____  _   / ___|__ _| |_ ",
    "| |   / _` |_  / || | | |   / _` | __|",
    "| |__| (_| |/ /| || | | |__| (_| | |_ ",
    "|_____\\__,_/___|\\_, |  \\____\\__,_|\\__|",
    "                |__/                  ",
    NULL
};

/* ===== SZISZA!!! ===== */

const char *CAT_ART[] = {
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


/* ===== TEMPLATE DATA ===== */

static Template templates[] = {
    {
        "c",
        "main.c",
        "#include <stdio.h>\n\n"
        "int main() \n{\n"
        "    printf(\"Hello, World!\\n\");\n"
        "    return 0;\n"
        "}\n"
    },
    {
        "py",
        "main.py",
        "class App:\n"
        "    def run(self):\n"
        "        print(\"Hello, World!\")\n\n"
        "if __name__ == \"__main__\":\n"
        "    app = App()\n"
        "    app.run()\n"
    },
    {
        "java",
        "Main.java",
        "public class Main {\n"
        "    public static void main(String[] args) {\n"
        "        App app = new App();\n"
        "        app.run();\n"
        "    }\n"
        "}\n\n"
        "class App {\n"
        "    public void run() {\n"
        "        System.out.println(\"Hello, World!\");\n"
        "    }\n"
        "}\n"
    },
    {
        "bash",
        "main.sh",
        "#!/usr/bin/env bash\n\n"
        "main() {\n"
        "    echo \"Hello, World!\"\n"
        "}\n\n"
        "main \"$@\"\n"
    }
};

#define TEMPLATE_COUNT (sizeof(templates) / sizeof(templates[0]))

/* ===== TEMPLATE FUNCTIONS ===== */

Template *find_template(const char *name) {

    for (int i = 0; i < TEMPLATE_COUNT; i++) {
        if (strcmp(name, templates[i].name) == 0) {
            return &templates[i];
        }
    }

    return NULL;
}

int get_template_count()
{
    return TEMPLATE_COUNT;
}

Template *get_templates()
{
    return templates;
}

/* ===== CLI ===== */

int parse_args(int argc, char *argv[], Config *cfg)
{

    for (int i = 1; i < argc; i++)
    {

        if (cfg->template_name)
        {
            if (!strcmp(argv[i], "--stdout"))
            {
                cfg->stdout_flag = 1;
            }

            continue;
        }

        
        if (argv[i][0] == '-')
        {

            if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
            {
                cfg->help = 1;
            }
            else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version"))
            {
                cfg->version = 1;
            }
            else if (!strcmp(argv[i], "-u"))
            {
                cfg->usage = 1;
            }
            else if (!strcmp(argv[i], "--stdout"))
            { 
                cfg->stdout_flag = 1;
            }    
            else
            {
                printf("Unknown option: %s\n", argv[i]);
                return 0;
            }

        }
        
        else
        {
            if (!cfg->template_name)
            {
                cfg->template_name = argv[i];
            }

            else
            {
                printf("Too many arguments\n");
                return 0;
            }
        }
    }

    return 1;
}

/* ===== SIMPLE CLI ===== */

void print_help()
{
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

void print_version()
{
    printf("LazyCat version %s\n", VERSION);
}

void print_usage()
{
    printf("Usage: LazyCat <template> [options]\n");
}

/* ===== IO ===== */

int file_exists(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f) 
    {
        fclose(f);
        return 1;
    }
    return 0;
}

int write_file(const char *filename, const char *content)
{

    FILE *f = fopen(filename, "w");
    if (!f)
    {
        perror("fopen");
        return 0;
    }

    fputs(content, f);
    fclose(f);
    return 1;
}

/* ===== DESIGN ===== */

void print_header_NRY()
{
        printf("\n");

    /* Logo - pad=6 */
    for (int i = 0; LOGO_ART[i]; i++)
    {
        printf(PAD "      " BOLD "%s" RESET "\n", LOGO_ART[i]);
    }
    printf("\n");

    /* Cat - pad=17 */
    for (int i = 0; CAT_ART[i]; i++)
    {
        printf(PAD "                 %s\n", CAT_ART[i]);
    }

    /* Tagline - pad=10 */
    printf("\n");
    printf(PAD "                template generator\n\n");

    /* Separator */
    printf(PAD "---------------------------------------------------\n\n");
}

void print_design_full()
{

    print_header_NRY();

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

    for (int i = 0; i < count; i += 2)
    {
        if (i + 1 < count)
        {
            printf(PAD "|   \xe2\x96\xb8 %-14s  \xe2\x96\xb8 %-14s            |\n",
                   t[i].name, t[i+1].name);
        }
        
        else
        {
            printf(PAD "|   \xe2\x96\xb8 %-14s                              |\n",
                   t[i].name);
        }
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
    printf(PAD "   LazyCat v%s  *  simple. fast. lazy.\n", VERSION);
    printf(PAD "---------------------------------------------------\n\n");
}


void print_design_help()
{

    print_header_NRY();

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

    for (int i = 0; i < count; i += 2)
    {
        if (i + 1 < count)
        {
            printf(PAD "|   \xe2\x96\xb8 %-14s  \xe2\x96\xb8 %-14s            |\n",
                   t[i].name, t[i+1].name);
        }

        else
        {
            printf(PAD "|   \xe2\x96\xb8 %-14s                              |\n",
                   t[i].name);
        }
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
    print_header_NRY();

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
    
    print_header_NRY();
    
    
    printf(PAD "---------------------------------------------------\n");
    printf(PAD "   LazyCat v%s  *  simple. fast. lazy.\n", VERSION);
    printf(PAD "---------------------------------------------------\n\n");
}
