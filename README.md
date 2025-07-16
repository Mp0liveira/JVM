/**
 * @mainpage JVM
*/
# Como compilar e rodar o programa?

Primeiramente, tenha o make instalado. Em seguida utilize o comando abaixo em seu terminal dentro do diretório da jvm:

```bash
make
```

Após isso, suas dependências devem estar instaladas.

# Como testar um único arquivo??

Para executar a jvm em um arquivo especifico:

```bash
./bin -e=examples/<arquivo_exemplo>.class
```

Para executar o bytecode viewer:
```bash
./bin -r=examples/<arquivo_exemplo>.class -o=out.txt
```

# Como testar todos os arquivos?

Para testar a jvm:

```bash
testarJVM.sh
```

A saída estará no arquivo out.txt

Para testar o bytecode viewer:
```bash
testarBYTECODE.sh
```

As saídas estarão na pasta output.
