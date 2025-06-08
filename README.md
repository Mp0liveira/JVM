# How to compile and run?

```bash
make
```

For executing the JVM:
```bash
./bin -e=examples/<some-example>.class
```

For executing the Bytecode Viwer:
```bash
./bin -r=examples/<some-example>.class -o=out.txt
```

# How to test?

To test the JVM:
```bash
t.sh
```

To test the Bytecode Viwer:
```bash
run_tests.sh
```

The results will be stored in the `output` folder.
