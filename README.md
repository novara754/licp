# Licp

A basic Lisp implemented in C.

Run `make` to compile the project and then run the resulting `licp` executable
to start a REPL which can evaluate some basic arithmetic:

It supports the functions `+` and `-` which both accept up to 5 arguments.

```
$ make && ./licp
> (+ 1 2 3)
6
> (- 5 2)
3
> (+ 1 2 (- 10 3))
10
> asd
invalid input
> 123
123
```

Press `Ctrl+D` or `Ctrl+C` to exit.

## License

Licensed under the [MIT License](./LICENSE).
