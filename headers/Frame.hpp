#ifndef FRAME_HPP
#define FRAME_HPP

#include "BaseType.hpp"
#include "InstanceClass.hpp"
#include "StaticClass.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

using namespace std;

/**
 * @file Frame.hpp
 * @brief Declara a classe Frame, que representa um frame da pilha de execução da JVM.
 */

/**
 * @class Frame
 * @brief Representa um frame da pilha de execução da JVM, armazenando variáveis locais, pilha de operandos e contexto do método.
 */
class Frame {
public:
    /**
     * @brief Construtor para métodos de instância.
     * 
     * @param object Ponteiro para o objeto da instância (`this`).
     * @param class_runtime Classe onde o método foi definido.
     * @param method_name Nome do método.
     * @param method_descriptor Descritor do método (tipo dos parâmetros e retorno).
     * @param arguments Vetor com os argumentos para o método.
     */
    Frame(InstanceClass* object, StaticClass* class_runtime, string method_name, string method_descriptor, vector<Value> arguments);

    /**
     * @brief Construtor para métodos estáticos.
     * 
     * @param class_runtime Classe onde o método foi definido.
     * @param method_name Nome do método.
     * @param method_descriptor Descritor do método.
     * @param arguments Vetor de argumentos (opcional).
     */
    Frame(StaticClass* class_runtime, string method_name, string method_descriptor, vector<Value> arguments = vector<Value>());

    /**
     * @brief Destrutor do Frame.
     */
    ~Frame();

    /**
     * @brief Retorna o pool de constantes da classe onde o método foi definido.
     * @return ConstantPoolInfo** Ponteiro para o pool de constantes.
     */
    ConstantPoolInfo** get_constant_pool();

    /**
     * @brief Obtém o valor de uma variável local pelo índice.
     * @param index Índice da variável.
     * @return Value Valor armazenado.
     */
    Value get_local_variable_value(uint32_t index);

    /**
     * @brief Define o valor de uma variável local pelo índice.
     * @param variableValue Valor a ser definido.
     * @param index Índice da variável.
     */
    void set_local_variable(Value variableValue, uint32_t index);

    /**
     * @brief Empilha um valor na pilha de operandos.
     * @param operand Valor a ser empilhado.
     */
    void push_operand_stack(Value operand);

    /**
     * @brief Remove e retorna o topo da pilha de operandos.
     * @return Value Valor desempilhado.
     */
    Value pop_operand_stack();

    /**
     * @brief Retorna uma cópia da pilha de operandos atual.
     * @return stack<Value> Pilha copiada.
     */
    stack<Value> copy_operand_stack();

    /**
     * @brief Restaura a pilha de operandos a partir de uma pilha de backup.
     * @param backup Pilha de operandos a ser restaurada.
     */
    void load_operand_stack(stack<Value> backup);

    /**
     * @brief Retorna o objeto associado ao frame (caso seja método de instância).
     * @return InstanceClass* Ponteiro para o objeto.
     */
    InstanceClass* get_object();

    /**
     * @brief Retorna ponteiro para o bytecode do método a partir de um endereço.
     * @param address Posição relativa do bytecode.
     * @return u1* Ponteiro para o bytecode.
     */
    u1* get_code(uint32_t address);

    /**
     * @brief Contador de programa (Program Counter), indica a instrução atual do método.
     */
    u4 pc;

    /**
     * @brief Retorna o número de variáveis locais alocadas no método.
     * @return u2 Tamanho do vetor de variáveis locais.
     */
    u2 get_local_variables_vector_size();

    /**
     * @brief Retorna o tamanho total do código (bytecode) do método.
     * @return u4 Tamanho do código em bytes.
     */
    u4 get_code_size();

private:
    /**
     * @brief Busca o método na classe com nome e descritor fornecidos.
     * @param class_runtime Classe onde buscar.
     * @param name Nome do método.
     * @param descriptor Descritor do método.
     * @return MethodInfo* Ponteiro para a estrutura do método.
     */
    MethodInfo* obterMethodNamed(StaticClass* class_runtime, const string& name, const string& descriptor);

    /**
     * @brief Inicializa os atributos `code_attribute` e `exceptions_attribute` do método.
     */
    void encontrarAttributes();

    StaticClass* class_runtime;                /**< Classe onde o método está definido. */
    InstanceClass* object;                     /**< Objeto da instância, se for método de instância. */
    MethodInfo method;                         /**< Informações do método em execução. */
    CodeAttribute* code_attribute;             /**< Atributo que contém o código do método. */
    ExceptionsAttribute* exceptions_attribute; /**< Atributo que contém as exceções do método. */
    map<uint32_t, Value> local_variables;      /**< Mapeamento de índice para variáveis locais. */
    stack<Value> operand_stack;                /**< Pilha de operandos usada durante execução. */
};

#endif // FRAME_HPP