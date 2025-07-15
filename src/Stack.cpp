#include "Stack.hpp"

// Construtor (inicialização feita implicitamente)
Stack::Stack()
{
}

// Destrutor (libera todos os frames restantes)
Stack::~Stack()
{
  while (!frame_stack.empty()) {
    delete frame_stack.top();
    frame_stack.pop();
  }
}

// Empilha um novo frame na pilha de execução
void Stack::push_frame(Frame *frame)
{
    
  // Verifica se a stack está cheia
//    if (frame_stack.size() >= FRAME_MAX_SIZE) {
//        cerr << "StackOverflowError" << endl;
//        exit(1);
//    }

  frame_stack.push(frame);
}

// Retorna o frame do topo da pilha (ou NULL se vazia)
Frame* Stack::get_top_frame()
{
  if (frame_stack.size() == 0) {
    return NULL;
  }

  return frame_stack.top();
}

// Remove e destrói o frame do topo da pilha
bool Stack::pop_frame()
{
  if (frame_stack.size() == 0) {
    return false;
  }

  Frame *frame = frame_stack.top();
  frame_stack.pop();
  delete frame;

  return true;
}

// Retorna a quantidade de frames atualmente na pilha
uint32_t Stack::size()
{
  return frame_stack.size();
}
