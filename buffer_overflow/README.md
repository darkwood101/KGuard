Running

```console
$ make overflow
$ ./overflow
```

should successfully launch a shell since `make overflow` performs the compilation without KGuard protections. Running

```console
$ make overflow-protect
$ ./overflow
```

should not launch a shell since `make overflow-protect` performs the compilation with KGuard protections.
