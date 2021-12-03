## Tests

Run
```console
$ make
```
to compile all tests.

### `example`

Demonstrates that the compiler succesfully instruments functions, while excluding
"safe" functions.

Running:
```console
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

### `overflow`

Demonstrates that the shellcode successfully launches a shell when ran without stack protection.

Running:
```console
$ ./overflow
```

### `overflow-protect`

Demonstrates that KGuard, when it puts the compiler instrumentation and the kernel
together, successfully prevents the shellcode attack.

Running:
```console
$ ./daemon overflow-protect
```

### `test1`-`test5`

These are various tests of KGuard's kernel-side implementation. `test1` makes
sure that KGuard performs a successful push/pop. `test2` tests that KGuard will
terminate the process on return address mismatch. `test3` is a variation of
`test1`, with many pushes and pops. Similarly, `test4` is a variation of `test2`.
`test5` ensures that KGuard is inherited over newly created processes -- if a
process with KGuard protection forks, the child will also have KGuard protection.

Running:
```console
$ ./daemon testN
```
where you should replace `N` with the test number.

### `setjmp_example`

This test demonstrates that the `setjmp`/`longjmp` side of KGuard is working as
intended. That is, uncanonical stack modifications are supported by KGuard.
Moreover, KGuard ensures that control flow cannot be hijacked via
`setjmp`/`longjmp`.

