#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int qbsp_main(int argc, const char **argv);
int light_main(int argc, const char **argv);
int vis_main(int argc, const char **argv);
int bspinfo_main(int argc, const char **argv);
int bsputil_main(int argc, const char **argv);

static int is_eq(const char *a, const char *b)
{
#ifdef _WIN32
    return _stricmp(a, b) == 0;
#else
    return strcmp(a, b) == 0;
#endif
}

static void print_help(void)
{
    puts(
"csmap - ericw tools in einer Exe\n"
"\n"
"Verwendung:\n"
"  csmap qbsp    <args...>\n"
"  csmap light   <args...>\n"
"  csmap vis     <args...>\n"
"  csmap bspinfo <args...>\n"
"  csmap bsputil <args...>\n"
"\n"
"Pipeline:\n"
"  csmap qbsp <...> -- light <...> -- vis <...>\n"
"\n"
"Hinweis: Argumente werden unverändert an die Original-Parser übergeben.\n"
    );
}

int main(int argc, char **argv)
{
    if (argc <= 1) {
        print_help();
        return 0;
    }

    int start = 1;
    for (int i = 1; i <= argc; ++i) {
        if (i == argc || is_eq(argv[i], "--")) {
            int len = i - start;
            if (len > 0) {
                char **seg = argv + start;
                char *saved = NULL;
                if (i < argc) {
                    saved = argv[i];
                    argv[i] = NULL;
                }

                int rc = 0;
                if (is_eq(seg[0], "qbsp")) {
                    rc = qbsp_main(len, (const char *const *)seg);
                } else if (is_eq(seg[0], "light")) {
                    rc = light_main(len, (const char *const *)seg);
                } else if (is_eq(seg[0], "vis")) {
                    rc = vis_main(len, (const char *const *)seg);
                } else if (is_eq(seg[0], "bspinfo")) {
                    rc = bspinfo_main(len, (const char *const *)seg);
                } else if (is_eq(seg[0], "bsputil")) {
                    rc = bsputil_main(len, (const char *const *)seg);
                } else {
                    fprintf(stderr, "Unbekanntes Subcommand: %s\n", seg[0]);
                    rc = 2;
                }

                if (i < argc) {
                    argv[i] = saved;
                }

                if (rc) {
                    return rc;
                }
            }
            start = i + 1;
        }
    }

    return 0;
}
