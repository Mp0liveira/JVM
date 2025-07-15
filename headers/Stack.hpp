#ifndef STACK_HPP
#define STACK_HPP

#include "Frame.hpp"
#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;

// Define o número máximo de frames permitido na pilha (limitado na implementação)
#define FRAME_MAX_SIZE 50

// Classe Singleton que representa a pilha de chamadas da JVM
class Stack {
public:
    // Retorna a instância única da Stack (Singleton)
    static Stack& get_instance()
    {
        static Stack instance;
        return instance;
    }

    // Destrutor: limpa recursos da pilha
    ~Stack();

    // Empilha um novo frame na pilha de chamadas
    void push_frame(Frame* frame);

    // Retorna o frame no topo da pilha (frame atual)
    Frame* get_top_frame();

    // Remove o frame do topo da pilha e retorna se a operação foi bem-sucedida
    bool pop_frame();

    // Retorna o número atual de frames na pilha
    uint32_t size();

private:
    // Construtor privado para implementar o padrão Singleton
    Stack();

    // Construtor de cópia desativado
    Stack(Stack const&);

    // Operador de atribuição desativado
    void operator=(Stack const&);

    // Container que armazena os ponteiros dos Frames da pilha
    stack<Frame*> frame_stack;
};