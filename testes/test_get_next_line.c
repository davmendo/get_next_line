#include "get_next_line.h"

void run_tests()
{
    int fd;
    char *line;

    // Teste 1: Arquivo de teste com várias linhas
    fd = open("test_file.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir o arquivo de teste");
        return;
    }
    printf("Teste 1: Lendo linhas do arquivo de teste\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);

    // Teste 2: Arquivo vazio
    fd = open("empty_file.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir o arquivo vazio");
        return;
    }
    printf("\nTeste 2: Lendo de um arquivo vazio\n");
    line = get_next_line(fd);
    if (line == NULL)
        printf("Nenhuma linha lida, como esperado.\n");
    else
    {
        printf("Erro: Linha não deveria ter sido lida.\n");
        free(line);
    }
    close(fd);

    // Teste 3: Arquivo com uma única linha sem quebra de linha
    fd = open("single_line.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir o arquivo de uma linha");
        return;
    }
    printf("\nTeste 3: Lendo um arquivo com uma única linha\n");
    line = get_next_line(fd);
    if (line != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    else
    {
        printf("Erro: Nenhuma linha lida.\n");
    }
    close(fd);

    // Teste 4: Lendo da entrada padrão (stdin)
    printf("\nTeste 4: Digite uma linha para testar a leitura da entrada padrão (stdin):\n");
    line = get_next_line(0);
    if (line != NULL)
    {
        printf("Você digitou: %s", line);
        free(line);
    }
    else
    {
        printf("Erro ao ler da entrada padrão.\n");
    }
}

int main()
{
    run_tests();
    return 0;
}

