#ifndef STACK_HPP
#define STACK_HPP

#include "Frame.hpp"
#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;

/**
 * @file Stack.hpp
 * @brief Declara a classe Stack, que representa a pilha de chamadas da JVM.
 */

/**
 * @def FRAME_MAX_SIZE
 * @brief Define o número máximo de frames permitido na pilha de chamadas.
 * 
 * Este valor é fixado na implementação como uma limitação prática.
 */
#define FRAME_MAX_SIZE 50

/**
 * @class Stack
 * @brief Representa a pilha de chamadas da JVM como uma classe Singleton.
 * 
 * A pilha armazena os frames de execução (um para cada chamada de método).
 * Cada frame mantém suas próprias variáveis locais e pilha de operandos.
 */
class Stack {
public:
    /**
     * @brief Retorna a instância única da pilha (Singleton).
     * @return Stack& Referência para a instância da pilha.
     */
    static Stack& get_instance()
    {
        static Stack instance;
        return instance;
    }

    /**
     * @brief Destrutor da pilha.
     * 
     * Libera os recursos (frames) alocados dinamicamente.
     */
    ~Stack();

    /**
     * @brief Empilha um novo frame na pilha de chamadas.
     * @param frame Ponteiro para o frame a ser empilhado.
     */
    void push_frame(Frame* frame);

    /**
     * @brief Retorna o frame no topo da pilha (frame atual).
     * @return Frame* Ponteiro para o frame atual.
     */
    Frame* get_top_frame();

    /**
     * @brief Remove o frame do topo da pilha.
     * @return true Se a operação foi bem-sucedida.
     * @return false Se a pilha já estiver vazia.
     */
    bool pop_frame();

    /**
     * @brief Retorna o número atual de frames na pilha.
     * @return uint32_t Quantidade de frames.
     */
    uint32_t size();

private:
    /**
     * @brief Construtor privado (Singleton).
     */
    Stack();

    /**
     * @brief Construtor de cópia desativado (Singleton).
     */
    Stack(Stack const&);

    /**
     * @brief Operador de atribuição desativado (Singleton).
     */
    void operator=(Stack const&);

    /**
     * @brief Container que armazena os ponteiros dos frames da pilha.
     */
    stack<Frame*> frame_stack;
};

#endif // STACK_HPP