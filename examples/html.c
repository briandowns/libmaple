#include <stdio.h>

#include "../maple.h"

static const char *tmpl =
"<html>"
"  <body>"
"    <h1>{{ title }}</h1>"
"    {{ if logged_in }}"
"      <p>Welcome, {{ title name }}!</p>"
"      <ul>"
"        {{ range items }}"
"          <li>{{ . }}</li>"
"        {{ end }}"
"      </ul>"
"    {{ else }}"
"      <a href=\"/login\">Login</a>"
"    {{ end }}"
"    <div>{{ safe raw_html }}</div>"
"  </body>"
"</html>";

int
main(void)
{
    mp_context_t *ctx = mp_init(stdout);

    mp_set_var(ctx, "site_title", "Pet Favs");
    mp_set_var(ctx, "name", "maple downs");
    mp_set_var(ctx, "logged_in", "1");
    mp_set_var(ctx, "items", "Pets, Zoomies, Walks, Ice Cubes");
    mp_set_var(ctx, "raw_html", "<strong>Footer Area</strong>");

    mp_render_segment(ctx, tmpl, NULL, ".");

    mp_free(ctx);

    return 0;
}
