# Instruções

## Compilação

Para compilar, devem ser seguidos os seguintes passos:

1. Crie um diretório chamado `build` a partir desse comando:

    ```shell
    mkdir build
    ```

2. Entre no diretório e execute o seguinte comando:

    ```shell
    cmake .. && make
    ```

Dessa forma o projeto será compilado e um arquivo chamado Eu_Carrinho será criado.

## Execução

Para executar, basta rodar o seguinte comando dentro da pasta build:

```shell
./Eu_Carrinho arquivo.ppm
```

Lembrando que `arquivo.ppm` deve ser substituído pelo caminho e nome do arquivo ppm com os dados do terreno.
