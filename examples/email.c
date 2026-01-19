#include "../maple.h"

static const char *tmpl = 
"Hello {{ title name }},\n"
"{{ if is_subscribed == 1 }}\n"
"Thank you for being a loyal subscriber.\n\n"
"Here is your weekly update:\n"
"{{ range product_list }}\n"
"- {{ . }}"
"{{ end }}"
"{{ else }}"
"\nWe miss you! Consider subscribing for exclusive updates.\n\n"
"{{ end }}"
"Best regards,\n\n"
"The Team\n";

int
main(void)
{
    mp_context_t *ctx = mp_init();

    mp_set_var(ctx, "name", "maple downs");
    mp_set_var(ctx, "is_subscribed", "1");
    mp_set_var(ctx, "product_list", "Pets, Zoomies, Walks, Ice Cubes");

    mp_render(ctx, stdout, tmpl, NULL, ".");

    mp_free(ctx);

    return 0;
}
