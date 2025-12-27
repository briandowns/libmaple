# libmaple

[![Build and Deploy](https://github.com/briandowns/libmaple/actions/workflows/main.yml/badge.svg)](https://github.com/briandowns/libmaple/actions/workflows/main.yml/badge.svg)

**Maple** is a lightweight, embeddable template engine written in pure C. It provides variables, conditional logic, loops, arithmetic, comparisons, functions, file includes, and caching, with no dependencies.

Inspired by Go’s `text/template` — but built for C developers who want speed, simplicity, and full control.

For a quick look at functionality, run: `make example && ./example`. More detailed examples can found in the `examples` directory.

## Build

To build a shared object for your system, run:

```sh
make
```

When linking, make sure to include the math library with `-lm`.

## Features

### Core

- **Variable substitution**:  
  `{{ name }}`
  
  A single symbol between the double curly braces indicates a variable. If that variable has been set on the context, this will be rendered with whitespace trimmed.

- **Function calls**:  
  Call built‑in or custom C functions
  
  * `{{ lower name }}`
  * `{{ upper name }}`
  * `{{ title name }}`
  * `{{ reverse name }}`

- **Whitespace trimming**:  
  Surrounding whitespace inside tags is automatically removed.

### Expression & Logic Support

- **Arithmetic expressions**:

  Handles `+`, `-`, `*`, `/`, `()` with correct operator precedence.
  All numbers are handled as doubles. If the value is a whole number the decimal point and trailing 0's will not be displayed.
  Supports 2 points of precision

- **Comparison operators**:

  `<`, `>`, `<=`, `>=`, `==`, `!=`

- **Boolean logic**:

  Supports `&&`, `||`, `!`.

- **Unified numeric/logical evaluation**:

  Same syntax usable anywhere, even inside `if` or template output.

### Includes

Additional template files can be loaded from within other templates with the following syntax:

```js
{{ include "another_template.tmpl" }}
```

---

### Control Flow

```js
{{ if (x + y) >= 10 && age <>; 30 }}
Condition is true
{{ else }}
Condition is false
{{ end }}
```

### HTML 

All values are HTML escaped by default.

If a value contains HTML or characters that could be replaced by the escaping process, use the `safe` keyword.

```js
{{ safe var_containing_known_good_html }}
```

### Error Handling

Functions that can error will return a `uint8_t` value starting at 1. A lookup function is provided to get the corresponding error string.

```c
uint8_t ret = mp_render_segment(ctx, tpl, NULL, ".");
if (ret != 0) {
    printf("%s\n", mp_err_lookup(ret));
    return 1;
}
```

This pattern should be used when extending functionality.

## Tests

All tests can be found in the `tests/` directory and are easily extended.

To run:

```sh
make test
```

Tests are compiled with debug symbols.

## Contributing

Please feel free to open a PR!

## Contact

Brian Downs [@bdowns328](http://twitter.com/bdowns328)

## License

BSD 2 Clause [License](/LICENSE).
