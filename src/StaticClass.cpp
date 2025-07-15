#include <string>
#include "StaticClass.hpp"
#include "ClassFileViewer.hpp"

// Construtor: inicializa campos estáticos da classe com valores padrão
StaticClass::StaticClass(ClassFile* class_file)
{
  this->class_file = class_file;

  for (int i = 0; i < class_file->fields_count; i++) {
    FieldInfo finfo = class_file->fields[i];

    // Verifica se o campo é estático
    if (finfo.access_flags & FIELD_FLAG_ACC_STATIC) {
      std::string fieldName = get_formatted_constant(class_file->constant_pool, finfo.name_index);
      std::string fieldDescriptor = get_formatted_constant(class_file->constant_pool, finfo.descriptor_index);

      char fieldType = fieldDescriptor[0];
      Value value;

      // Inicializa o campo conforme seu tipo
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
      default: // referência (classe ou array)
        value.print_type = ValueType::REFERENCE;
        value.type = ValueType::REFERENCE;
        value.data.object = 0;
      }

      // Insere o campo inicializado no mapa de campos estáticos
      insert_value(value, fieldName);
    }
  }
}

// Retorna ponteiro para o ClassFile da classe
ClassFile* StaticClass::get_class_file()
{
  return this->class_file;
}

// Insere/atualiza valor de um campo estático
void StaticClass::insert_value(const Value& value, const string& fieldName)
{
  static_fields[fieldName] = value;
}

// Retorna valor de um campo estático; erro se não existir
Value StaticClass::get_value(const std::string& fieldName) 
{
  auto it = this->static_fields.find(fieldName);

  if (it == this->static_fields.end()) {
    cerr << "NoSuchFieldError: " << fieldName << endl;
    exit(1);
  }

  return it->second;
}

// Verifica se o campo estático existe
bool StaticClass::check_field(const std::string& fieldName)
{
  return this->static_fields.count(fieldName) > 0;
}

// Retorna nome do arquivo sem a extensão ".class"
std::string StaticClass::initialize_file(char *argv[])
{
  std::string str(argv[2]);
  std::string nome = str.substr(0, str.length() - 6);
  return nome;
}
