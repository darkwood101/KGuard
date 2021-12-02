Running

```console
$ make example
$ ./example
```

should print

```console
fn entry: ret addr 0x7fe2610c40b3
fn entry: ret addr 0x562e04e3e2d2
fn exit: ret addr 0x562e04e3e2d2
factorial of 5 is 120
entered safe function (not protected by kguard)
fn exit: ret addr 0x7fe2610c40b3
```

to the console (the actual address values will be different). KGuard is applied to functions `main` and `fact`. Function `safe_fn` is manually excluded from KGuard's protection (see the Makefile).
