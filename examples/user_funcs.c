#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../maple.h"

char*
triple(char *s)
{
    int converted = atoi(s);
    int result = converted * 3;

    memset(s, 0, strlen(s)+1);
    sprintf(s, "%d", result);
    return s;
}

int
main(void)
{
    mp_context_t *ctx = mp_init();
    mp_register_func(ctx, "triple", triple);

    mp_set_var(ctx, "x", "5");

    const char *tmpl =
        "Here is a user defined function called: triple.\n"
        "It takes a number and triples it.\n"
        "Number x, tripled is {{ triple x }}\n";

    mp_render(ctx, stdout, tmpl, NULL, ".");

    mp_free(ctx);

    return 0;
}
