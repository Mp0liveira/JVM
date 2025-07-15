#include "InstanceClass.hpp"
#include "ClassFileViewer.hpp"
#include <string>

// Construtor da classe de instância, inicializa campos de instância com valores padrão
InstanceClass::InstanceClass(StaticClass *class_runtime) :
    class_runtime(class_runtime)
{
  ClassFile *classFile = class_runtime->get_class_file();
  FieldInfo *fields = classFile->fields;
  u2 abstractFlag = 0x0400; // Flag para classe abstrata

  // Verifica se é uma classe abstrata (não pode ser instanciada)
  if ((classFile->access_flags & abstractFlag) != 0) {
    cerr << "InstantiationError" << endl;
    exit(1);
  }

  // Itera sobre todos os campos da classe
  for (int i = 0; i < classFile->fields_count; i++) {
    FieldInfo field = fields[i];
    u2 staticAndFinalFlag = 0x0008 | 0x0010; // Flags para campos static e final

    // Considera apenas campos de instância (não static ou final)
    if ((field.access_flags & staticAndFinalFlag) == 0) {
      string fieldName = get_formatted_constant(classFile->constant_pool, field.name_index);
      string fieldDescriptor = get_formatted_constant(classFile->constant_pool, field.descriptor_index);

      char fieldType = fieldDescriptor[0]; // Primeiro caractere indica o tipo
      Value value;

      // Inicializa o campo com valor padrão conforme o tipo
      switch (fieldType) {
      case 'B': // byte
        value.print_type = ValueType::BYTE;
        value.type = ValueType::BYTE;
        value.data.byte_value = 0;
        break;
      case 'C': // char
        value.print_type = ValueType::CHAR;
        value.type = ValueType::CHAR;
        value.data.char_value = 0;
        break;
      case 'D': // double
        value.print_type = ValueType::DOUBLE;
        value.type = ValueType::DOUBLE;
        value.data.double_value = 0;
        break;
      case 'F': // float
        value.print_type = ValueType::FLOAT;
        value.type = ValueType::FLOAT;
        value.data.float_value = 0;
        break;
      case 'I': // int
        value.print_type = ValueType::INT;
        value.type = ValueType::INT;
        value.data.int_value = 0;
        break;
      case 'J': // long
        value.print_type = ValueType::LONG;
        value.type = ValueType::LONG;
        value.data.long_value = 0;
        break;
      case 'S': // short
        value.print_type = ValueType::SHORT;
        value.type = ValueType::SHORT;
        value.data.short_value = 0;
        break;
      case 'Z': // boolean
        value.print_type = ValueType::BOOLEAN;
        value.type = ValueType::BOOLEAN;
        value.data.char_value = false;
        break;
      default: // referência para objeto (classe ou array)
        value.print_type = ValueType::REFERENCE;
        value.type = ValueType::REFERENCE;
        value.data.object = NULL;
      }

      // Armazena o valor inicial no mapa de campos
      insert_value_into_field(value, fieldName);
    }
  }
}

// Destrutor (vazio)
InstanceClass::~InstanceClass()
{
}

// Retorna o tipo do objeto (instância de classe)
ObjectType InstanceClass::object_type()
{
  return ObjectType::CLASS_INSTANCE;
}

// Retorna ponteiro para a representação da classe estática
StaticClass* InstanceClass::get_class_runtime()
{
  return class_runtime;
}

// Insere valor em um campo da instância
void InstanceClass::insert_value_into_field(Value value, const string& fieldName)
{
  class_fields[fieldName] = value;
}

// Recupera valor de um campo; erro se não existir
Value InstanceClass::get_value_from_field(const string& fieldName)
{
  if (class_fields.count(fieldName) == 0) {
    cerr << "NoSuchFieldError" << endl;
    exit(1);
  }

  return class_fields[fieldName];
}

// Verifica se o campo existe na instância
bool InstanceClass::field_exists(const string& fieldName)
{
  return class_fields.count(fieldName) > 0;
}