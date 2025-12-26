#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "crosscheck.h"
#include "../maple.h"

#define OUTPUT_BUF_SIZE 1024

static mp_context_t *ctx = {0};
static char output[OUTPUT_BUF_SIZE] = {0};
static FILE *ret_buffer = {0};

void
cc_setup()
{
    ret_buffer = fmemopen(output, OUTPUT_BUF_SIZE, "w");
    ctx = mp_init(ret_buffer);
}

void
cc_tear_down()
{
    memset(output, 0, OUTPUT_BUF_SIZE);
    mp_free(ctx);
}

cc_result_t
test_internal_func_lower()
{
    const char *tmpl = "{{ lower name }}";

    mp_set_var(ctx, "name", "MAPLE");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "maple");

    CC_SUCCESS;
}

cc_result_t
test_internal_func_upper()
{
    const char *tmpl = "{{ upper name }}";

    mp_set_var(ctx, "name", "maple");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "MAPLE");

    CC_SUCCESS;
}

cc_result_t
test_internal_func_title()
{
    const char *tmpl = "{{ title name }}";

    mp_set_var(ctx, "name", "maple downs");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "Maple Downs");

    CC_SUCCESS;
}

cc_result_t
test_internal_func_reverse()
{
    const char *tmpl = "{{ reverse name }}";

    mp_set_var(ctx, "name", "maple");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "elpam");

    CC_SUCCESS;
}

cc_result_t
test_arithmetic_order_of_ops_int()
{
    const char *tmpl = "{{ 5 + 2 * 3 }}";
    mp_set_var(ctx, "name", "maple downs");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "11");

    CC_SUCCESS;
}

cc_result_t
test_arithmetic_order_of_ops_double()
{
    const char *tmpl = "{{ 5.8 + 6 / 3 }}";
    mp_set_var(ctx, "name", "maple downs");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "7.80");

    CC_SUCCESS;
}

cc_result_t
test_comp_equals()
{
    const char *tmpl = "{{ if x == y }}true{{ else }}false{{ end }}";
    mp_set_var(ctx, "x", "10");
    mp_set_var(ctx, "y", "20");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "false");

    CC_SUCCESS;
}

cc_result_t
test_comp_not_equals()
{
    const char *tmpl = "{{ if x != y }}true{{ else }}false{{ end }}";
    mp_set_var(ctx, "x", "10");
    mp_set_var(ctx, "y", "20");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "true");

    CC_SUCCESS;
}

cc_result_t
test_comp_gt()
{
    const char *tmpl = "{{ if x > y }}true{{ else }}false{{ end }}";
    mp_set_var(ctx, "x", "10");
    mp_set_var(ctx, "y", "20");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "false");

    CC_SUCCESS;
}

cc_result_t
test_comp_lt()
{
    const char *tmpl = "{{ if x < y }}true{{ else }}false{{ end }}";
    mp_set_var(ctx, "x", "10");
    mp_set_var(ctx, "y", "20");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "true");

    CC_SUCCESS;
}

cc_result_t
test_comp_gt_eq()
{
    const char *tmpl = "{{ if x >= y }}true{{ else }}false{{ end }}";
    mp_set_var(ctx, "x", "10");
    mp_set_var(ctx, "y", "10");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "true");

    CC_SUCCESS;
}

cc_result_t
test_comp_lt_eq()
{
    const char *tmpl = "{{ if x <= y }}true{{ else }}false{{ end }}";
    mp_set_var(ctx, "x", "10");
    mp_set_var(ctx, "y", "10");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "true");

    CC_SUCCESS;
}

cc_result_t
test_boolean_and()
{
    const char *tmpl = "{{ if x == y && z == (y*2) }}true{{ else }}false{{ end }}";
    mp_set_var(ctx, "x", "10");
    mp_set_var(ctx, "y", "10");
    mp_set_var(ctx, "z", "20");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "true");

    CC_SUCCESS;
}

cc_result_t
test_boolean_or()
{
    const char *tmpl = "{{ if x != y || z == (y * 2) }}true{{ else }}false{{ end }}";
    mp_set_var(ctx, "x", "10");
    mp_set_var(ctx, "y", "10");
    mp_set_var(ctx, "z", "20");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, 0);

    fclose(ret_buffer);

    CC_ASSERT_STRING_EQUAL(output, "true");

    CC_SUCCESS;
}

cc_result_t
test_error_missing_end()
{
    const char *tmpl = "{{ if x != y || z == (y * 2) }}true";
    mp_set_var(ctx, "x", "10");
    mp_set_var(ctx, "y", "10");
    mp_set_var(ctx, "z", "20");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_UINT8_EQUAL(ret, MP_ERR_MISSING_END_TAG);

    fclose(ret_buffer);

    CC_SUCCESS;
}

cc_result_t
test_error_missing_end_string()
{
    const char *tmpl = "{{ if x != y || z == (y * 2) }}true";
    mp_set_var(ctx, "x", "10");
    mp_set_var(ctx, "y", "10");
    mp_set_var(ctx, "z", "20");
    uint8_t ret = mp_render_segment(ctx, tmpl, NULL, ".");
    CC_ASSERT_STRING_EQUAL(mp_err_lookup(ret), "missing end tag");

    fclose(ret_buffer);

    CC_SUCCESS;
}

int
main(void)
{
    srand(time(NULL));

    CC_INIT;
 
    CC_RUN(test_internal_func_lower);
    CC_RUN(test_internal_func_upper);
    CC_RUN(test_internal_func_title);
    CC_RUN(test_internal_func_reverse);
    CC_RUN(test_arithmetic_order_of_ops_int);
    CC_RUN(test_arithmetic_order_of_ops_double);
    CC_RUN(test_comp_equals);
    CC_RUN(test_comp_not_equals);
    CC_RUN(test_comp_gt);
    CC_RUN(test_comp_lt);
    CC_RUN(test_comp_gt_eq);
    CC_RUN(test_comp_lt_eq);
    CC_RUN(test_boolean_and);
    CC_RUN(test_boolean_or);
    CC_RUN(test_error_missing_end);
    CC_RUN(test_error_missing_end_string);

    CC_COMPLETE;
}
