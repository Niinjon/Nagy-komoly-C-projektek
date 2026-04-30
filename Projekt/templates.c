#include <string.h>
#include <stddef.h>
#include <stdlib.h>

/* ===== TEMPLATE STRUCT ===== */
typedef struct {
    const char *name;
    const char *filename;
    const char *content;
} Template;

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

/* ===== LOOKUP FUNCTION ===== */
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