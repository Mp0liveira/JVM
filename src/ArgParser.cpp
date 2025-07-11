#include "ArgParser.hpp"
#include <iostream>

using namespace std;

// Função responsável por analisar os argumentos da linha de comando
const Parameters parse_args(int argc, char* argv[])
{
    Parameters params = { NULL, NULL };  // Inicializa os campos com NULL

    // Loop para percorrer todos os argumentos
    for (int i = 1; i < argc; i++) {
        // Modo leitura: -r=caminho/do/arquivo.class
        if (strncmp(argv[i], "-r=", 3) == 0) {
            params.execute = false; // Não vai executar, apenas ler
            params.class_file_path = argv[i] + 3; // Pega o caminho após "-r="
        }
        // Arquivo de saída: -o=saida.txt
        else if (strncmp(argv[i], "-o=", 3) == 0)
            params.output_file_path = argv[i] + 3;
        // Modo execução: -e=caminho/do/arquivo.class
        else if (strncmp(argv[i], "-e=", 3) == 0) {
            params.execute = true; // Vai executar
            params.class_file_path = argv[i] + 3; // Pega o caminho após "-e="
        }
    }

    return params; // Retorna a estrutura preenchida
}

// Função para validar se os parâmetros fornecidos são válidos
bool validate_parameters(const Parameters* params)
{
    // Verifica se o caminho do .class foi fornecido,
    // e se no modo leitura também foi fornecido o caminho de saída
    if (!params->class_file_path || (!params->execute && !params->output_file_path)) {
        // Mensagem de erro explicativa para o usuário
        cerr << "Você precisa executar este binário passando um arquivo para leitura ou execução\n";
        cerr << "Modo leitura:\n\t./bin -r=caminho/arquivo.class -o=saida.txt\n";
        cerr << "Modo execução:\n\t./bin -e=caminho/arquivo.class\n";
        return false;
    }
    return true; // Parâmetros válidos
}
