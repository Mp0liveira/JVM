#ifndef STATICCLASS
#define STATICCLASS

#include "ClassFile.hpp"
#include "ClassFileReader.hpp"
#include <map>
#include <string>

using namespace std;

/**
 * @file StaticClass.hpp
 * @brief Representa uma classe carregada na JVM, com suporte a campos estáticos.
 */

 /**
 * @class StaticClass.hpp
 * @brief Armazena e gerencia os dados de uma classe Java carregada, incluindo o acesso
 * aos seus campos estáticos e à estrutura `ClassFile` correspondente.
 */
class StaticClass {
public:
    /**
     * @brief Construtor que inicializa a StaticClass com um ponteiro para ClassFile.
     * @param class_file Ponteiro para a estrutura ClassFile carregada.
     */
    StaticClass(ClassFile* class_file);

    /**
     * @brief Retorna o ponteiro para o ClassFile associado.
     * @return Ponteiro para a estrutura ClassFile.
     */
    ClassFile* get_class_file();

    /**
     * @brief Insere ou atualiza o valor de um campo estático.
     * @param value Valor a ser armazenado.
     * @param field_name Nome do campo estático.
     */
    void insert_value(const Value& value, const string& field_name);

    /**
     * @brief Retorna o valor associado a um campo estático.
     * @param field_name Nome do campo.
     * @return Valor armazenado.
     */
    Value get_value(const string& field_name);

    /**
     * @brief Verifica se um campo estático com o nome especificado existe.
     * @param field_name Nome do campo.
     * @return true se o campo existir, false caso contrário.
     */
    bool check_field(const string& field_name);

    /**
     * @brief Inicializa o bloco `<clinit>` da classe, se existir.
     * @param argv Argumentos da linha de comando (opcionalmente usados).
     * @return Nome do método `<clinit>` executado, ou string vazia se não houver.
     */
    string initialize_file(char* argv[]);

private:
    /// Ponteiro para a estrutura ClassFile que representa esta classe.
    ClassFile* class_file;

    /// Mapa que armazena os valores dos campos estáticos (por nome).
    map<string, Value> static_fields;
};

#endif
