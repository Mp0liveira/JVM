#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "Array.hpp"
#include "BaseType.hpp"
#include "ClassFileViewer.hpp"
#include "Frame.hpp"
#include "InstanceClass.hpp"
#include "MethodArea.hpp"
#include "Stack.hpp"
#include "StaticClass.hpp"
#include "StrObject.hpp"

#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

// Declaração antecipada da classe Operations
class Operations;

// Define ponteiro para função membro da classe Operations
typedef void (Operations::*generic_function)();

// Classe que executa instruções da JVM (padrão singleton)
class Operations {
public:
    // Retorna instância única da classe
    static Operations& get_instance()
    {
        static Operations instance;
        return instance;
    }

    // Destrutor
    ~Operations();

    // Executa métodos estáticos de uma classe
    void executeMethods(StaticClass* class_runtime);

    // Verifica se um método existe em uma classe
    bool verifyMethod(StaticClass* class_runtime, const string& name, const string& descriptor);

    // Preenche array multidimensional com base nas dimensões
    void populateMultiarray(Array* array, ValueType value, stack<int> count);

private:
    // Construtor privado (singleton)
    Operations();

    // Construtor de cópia desativado
    Operations(Operations const&);

    // Operador de atribuição desativado
    void operator=(Operations const&);

    // Array de ponteiros para funções que implementam instruções da JVM
    generic_function generic_functions_arr[202];

    // Indica se a instrução atual está em modo "wide"
    bool is_wide;

    // Implementações das instruções da JVM (ex: nop, iconst_0, etc.)
    void nop();
    void aconst_null();
    void iconst_m1();
    void iconst_0();
    void iconst_1();
    void iconst_2();
    void iconst_3();
    void iconst_4();
    void iconst_5();
    void lconst_0();
    void lconst_1();
    void fconst_0();
    void fconst_1();
    void fconst_2();
    void dconst_0();
    void dconst_1();
    void bipush();
    void sipush();
    void ldc();
    void ldc_w();
    void ldc2_w();
    void iload();
    void lload();
    void fload();
    void dload();
    void aload();
    void iload_0();
    void iload_1();
    void iload_2();
    void iload_3();
    void lload_0();
    void lload_1();
    void lload_2();
    void lload_3();
    void fload_0();
    void fload_1();
    void fload_2();
    void fload_3();
    void dload_0();
    void dload_1();
    void dload_2();
    void dload_3();
    void aload_0();
    void aload_1();
    void aload_2();
    void aload_3();
    void iaload();
    void laload();
    void faload();
    void daload();
    void aaload();
    void baload();
    void caload();
    void saload();
    void istore();
    void lstore();
    void fstore();
    void dstore();
    void astore();
    void istore_0();
    void istore_1();
    void istore_2();
    void istore_3();
    void lstore_0();
    void lstore_1();
    void lstore_2();
    void lstore_3();
    void fstore_0();
    void fstore_1();
    void fstore_2();
    void fstore_3();
    void dstore_0();
    void dstore_1();
    void dstore_2();
    void dstore_3();
    void astore_0();
    void astore_1();
    void astore_2();
    void astore_3();
    void iastore();
    void lastore();
    void fastore();
    void dastore();
    void aastore();
    void bastore();
    void castore();
    void sastore();
    void pop();
    void pop2();
    void dup();
    void dup_x1();
    void dup_x2();
    void dup2();
    void dup2_x1();
    void dup2_x2();
    void swap();
    void iadd();
    void ladd();
    void fadd();
    void dadd();
    void isub();
    void lsub();
    void fsub();
    void dsub();
    void imul();
    void lmul();
    void fmul();
    void dmul();
    void idiv();
    void ldiv();
    void fdiv();
    void ddiv();
    void irem();
    void lrem();
    void frem();
    void drem();
    void ineg();
    void lneg();
    void fneg();
    void dneg();
    void ishl();
    void lshl();
    void ishr();
    void lshr();
    void iushr();
    void lushr();
    void iand();
    void land();
    void ior();
    void lor();
    void ixor();
    void lxor();
    void iinc();
    void i2l();
    void i2f();
    void i2d();
    void l2i();
    void l2f();
    void l2d();
    void f2i();
    void f2l();
    void f2d();
    void d2i();
    void d2l();
    void d2f();
    void i2b();
    void i2c();
    void i2s();
    void lcmp();
    void fcmpl();
    void fcmpg();
    void dcmpl();
    void dcmpg();
    void ifeq();
    void ifne();
    void iflt();
    void ifge();
    void ifgt();
    void ifle();
    void if_icmpeq();
    void if_icmpne();
    void if_icmplt();
    void if_icmpge();
    void if_icmpgt();
    void if_icmple();
    void if_acmpeq();
    void if_acmpne();
    void func_goto();
    void jsr();
    void ret();
    void tableswitch();
    void lookupswitch();
    void ireturn();
    void lreturn();
    void freturn();
    void dreturn();
    void areturn();
    void func_return();
    void getstatic();
    void putstatic();
    void getfield();
    void putfield();
    void invokevirtual();
    void invokespecial();
    void invokestatic();
    void invokeinterface();
    void func_new();
    void newarray();
    void anewarray();
    void arraylength();
    void athrow();
    void checkcast();
    void instanceof();
    void monitorenter();
    void monitorexit();
    void wide();
    void multianewarray();
    void ifnull();
    void ifnonnull();
    void goto_w();
    void jsr_w();

    // Inicializa o array de instruções
    void initInstructions();
};

#endif