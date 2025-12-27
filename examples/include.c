#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../maple.h"

int
main(void)
{
    mp_context_t *ctx = mp_init(stdout);

    const char *tmpl =
        "<html><title>{{ site_name }}</title>"
        "<body>lots 'o content...</body>"
        "{{ include \"footer.html.tmpl\" }}"
        "</html>\n\n";

    mp_set_var(ctx, "site_name", "Sky Island");
    mp_set_var(ctx, "footer", "© 2025");

    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    if (ret != 0) {
        printf("%s\n", mp_err_lookup(ret));
        return 1;
    }

    mp_free(ctx);

    return 0;
}
