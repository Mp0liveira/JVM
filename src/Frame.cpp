#include "Frame.hpp"
#include "ClassFileViewer.hpp"
#include "MethodArea.hpp"
#include "ClassFileUtils.hpp"

// Construtor para método de instância
Frame::Frame(InstanceClass *object, StaticClass *classRuntime, string methodName, string methodDescriptor, vector<Value> arguments) :
    pc(0), object(object)
{
  // Copia os argumentos para as variáveis locais
  for (int i = 0; i < (signed) arguments.size(); i++) {
    local_variables[i] = arguments[i];
  }

  // Localiza o método pelo nome e descritor
  MethodInfo *_method = obterMethodNamed(classRuntime, methodName, methodDescriptor);
  assert(_method != NULL);
  method = *_method;

  // Garante que não é um método estático
  assert((method.access_flags & 0x0008) == 0);

  // Carrega atributos do método (Code, Exceptions)
  encontrarAttributes();
}

// Construtor para método estático
Frame::Frame(StaticClass *classRuntime, string methodName, string methodDescriptor, vector<Value> arguments) :
    pc(0), object(NULL)
{
  // Copia os argumentos para as variáveis locais
  for (int i = 0; i < (signed) arguments.size(); i++) {
    local_variables[i] = arguments[i];
  }

  // Localiza o método pelo nome e descritor
  MethodInfo *_method = obterMethodNamed(classRuntime, methodName, methodDescriptor);
  assert(_method != NULL);
  method = *_method;

  // Garante que o método é estático
  assert((method.access_flags & 0x0008) != 0);

  // Carrega atributos do método (Code, Exceptions)
  encontrarAttributes();
}

// Destrutor (vazio)
Frame::~Frame()
{
}

// Retorna ponteiro para a constant pool da classe
ConstantPoolInfo** Frame::get_constant_pool()
{
  return &(class_runtime->get_class_file()->constant_pool);
}

// Retorna valor de uma variável local por índice
Value Frame::get_local_variable_value(uint32_t index)
{
  if (index >= code_attribute->max_locals) {
    cerr << "Trying to get inexistent local variable" << endl;
    exit(1);
  }
  return local_variables[index];
}

// Define valor de variável local
void Frame::set_local_variable(Value variableValue, uint32_t index)
{
  if (index >= code_attribute->max_locals) {
    cerr << "Trying to set inexistent local variable" << endl;
    exit(1);
  }
  local_variables[index] = variableValue;
}

// Empilha valor na pilha de operandos
void Frame::push_operand_stack(Value operand)
{
  operand_stack.push(operand);
}

// Desempilha e retorna o topo da pilha de operandos
Value Frame::pop_operand_stack()
{
  if (operand_stack.size() == 0) {
    cerr << "IndexOutOfBoundsException" << endl;
    exit(1);
  }

  Value top = operand_stack.top();
  operand_stack.pop();
  return top;
}

// Retorna uma cópia da pilha de operandos
stack<Value> Frame::copy_operand_stack()
{
  return operand_stack;
}

// Substitui a pilha de operandos por uma cópia fornecida
void Frame::load_operand_stack(stack<Value> backup)
{
  operand_stack = backup;
}

// Retorna ponteiro para instrução no endereço especificado
u1* Frame::get_code(uint32_t address)
{
  return code_attribute->code + address;
}

// Busca método na classe ou na hierarquia por nome e descritor
MethodInfo* Frame::obterMethodNamed(StaticClass *classRuntime, const string& name, const string& descriptor)
{
  MethodArea &methodArea = MethodArea::get_instance();
  StaticClass *currClass = classRuntime;
  MethodInfo *method;

  while (currClass != NULL) {
    ClassFile *classFile = currClass->get_class_file();

    for (int i = 0; i < classFile->methods_count; i++) {
      method = &(classFile->methods[i]);
      string methodName = get_formatted_constant(classFile->constant_pool, method->name_index);
      string methodDesc = get_formatted_constant(classFile->constant_pool, method->descriptor_index);

      if (methodName == name && methodDesc == descriptor) {
        class_runtime = currClass;
        return method;
      }
    }

    // Se não houver superclasse, termina
    if (classFile->super_class == 0) {
      currClass = NULL;
    } else {
      // Continua busca na superclasse
      string superClassName = get_formatted_constant(classFile->constant_pool, classFile->super_class);
      currClass = methodArea.get_class(superClassName);
    }
  }

  return NULL;
}

// Localiza atributos Code e Exceptions do método
void Frame::encontrarAttributes()
{
  ConstantPoolInfo *constantPool = *get_constant_pool();
  code_attribute = NULL;
  exceptions_attribute = NULL;

  for (int i = 0; i < method.attributes_count; i++) {
    AttributeInfo *attr = &(method.attributes[i]);
    ConstUtf8Info attrName = constantPool[attr->attribute_name_index - 1].info.utf8_info;

    if (ClassFileUtils::compare_utf8_str(attrName, "Code")) {
      code_attribute = &(attr->info.code_info);
      if (exceptions_attribute != NULL)
        break;
    } else if (ClassFileUtils::compare_utf8_str(attrName, "Exceptions")) {
      exceptions_attribute = &(attr->info.exceptions_info);
      if (code_attribute != NULL)
        break;
    }
  }
}

// Retorna o número de variáveis locais permitido no método
u2 Frame::get_local_variables_vector_size()
{
  return code_attribute->max_locals;
}

// Retorna o tamanho do código do método
u4 Frame::get_code_size()
{
  return code_attribute->code_length;
}