#include "lazy.h"

/* ===== MAIN ===== */



int main(int argc, char *argv[])
{
    Config cfg = {0};

    if (!parse_args(argc, argv, &cfg))
    {    
        return 1;
    }

    /* ===== ARGUMENTUMOK NÉLKÜL ===== */
    if (argc == 1)
    {
        WINDOWS_MODE ? print_help() : print_design_full();
        return 0;
    }
    
    /* ===== CONTROL FLAG-EK ===== */
    if (cfg.help)
    {
        WINDOWS_MODE ? print_help() : print_design_help();
        return 0;
    }

    if (cfg.version)
    {
        WINDOWS_MODE ? print_version() : print_design_version();
        return 0;
    }

    if (cfg.usage)
    {
        WINDOWS_MODE ? print_usage() : print_design_usage();
        return 0;
    }
    
    /* ===== TEMPLETEK ===== */
    if (!cfg.template_name)
    {
        printf("No template specified!\n");
        return 1;
    }

    /* ===== TEMPLATE KERESÉS ===== */

    Template *tpl = find_template(cfg.template_name);

    if (!tpl)
    {
        printf("Unknown template!\n");
        return 1;
    }

    /* ===== STDOUT ===== */

    if (cfg.stdout_flag)
    {
        printf("%s", tpl->content);
        return 0;
    }

    /* ===== FÁJL ELLENŐRZÉS ===== */

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