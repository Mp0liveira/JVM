#ifndef FRAME_HPP
#define FRAME_HPP

#include "BasicTypes.hpp"
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

// Classe que representa um frame da pilha de execução da JVM
class Frame {
public:
    // Construtores para métodos de instância
    Frame(InstanceClass* object, StaticClass* class_runtime, string method_name, string method_descriptor, vector<Value> arguments);

    // Construtor para métodos estáticos
    Frame(StaticClass* class_runtime, string method_name, string method_descriptor, vector<Value> arguments = vector<Value>());

    // Destrutor
    ~Frame();

    // Retorna a constant pool da classe
    ConstantPoolInfo** get_constant_pool();

    // Obtém variável local por índice
    Value get_local_variable_value(uint32_t index);

    // Define valor de variável local por índice
    void set_local_variable(Value variableValue, uint32_t index);

    // Empilha um valor na pilha de operandos
    void push_operand_stack(Value operand);

    // Remove e retorna o topo da pilha de operandos
    Value pop_operand_stack();

    // Retorna uma cópia da pilha de operandos
    stack<Value> copy_operand_stack();

    // Restaura a pilha de operandos a partir de backup
    void load_operand_stack(stack<Value> backup);

    // Retorna o objeto associado ao frame (se houver)
    InstanceClass* get_object();

    // Retorna ponteiro para instrução de bytecode no endereço dado
    u1* get_code(uint32_t address);

    // Contador de programa (posição da instrução atual)
    u4 pc;

    // Retorna o tamanho do vetor de variáveis locais
    u2 get_local_variables_vector_size();

    // Retorna o tamanho total do código do método
    u4 get_code_size();

private:
    // Busca o método com nome e descritor na classe
    MethodInfo* obterMethodNamed(StaticClass* class_runtime, const string& name, const string& descriptor);

    // Localiza e inicializa atributos do método
    void encontrarAttributes();

    StaticClass* class_runtime;           // Ponteiro para a classe estática
    InstanceClass* object;                // Ponteiro para o objeto da instância (se aplicável)
    MethodInfo method;                    // Informações do método
    CodeAttribute* code_attribute;        // Atributo de código do método
    ExceptionsAttribute* exceptions_attribute; // Atributo de exceções do método
    map<uint32_t, Value> local_variables; // Variáveis locais (índice → valor)
    stack<Value> operand_stack;           // Pilha de operandos do frame
};

#endif // FRAME_HPP