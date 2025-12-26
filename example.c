#include <sys/stat.h>
#include <unistd.h>

#include "maple.h"

int
main(void)
{
    mp_context_t *ctx = mp_init(stdout);

    mp_set_var(ctx, "name", "Maple downs");
    mp_set_var(ctx, "x", "5");
    mp_set_var(ctx, "y", "10");
    mp_set_var(ctx, "age", "25");
    mp_set_var(ctx, "items", "A, B, C");

    const char *tpl =
        "Hello, {{ lower name }}!\n"
        "Arithmetic: {{ 5 + 2 * 3 }}\n"
        "Comparison: {{ (x + 3) < y }}\n"
        "{{ if (x + y) >= 15 && age < 30 }}Condition True{{ else }}Condition False{{ end }}\n"
        "Loop:\n{{ range items }}- {{ . }}\n{{ end }}\n";

    mp_render_segment(ctx, tpl, NULL, ".");

    mp_free(ctx);

    return 0;
}
