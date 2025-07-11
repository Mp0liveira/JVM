#include <string>
#include "StaticClass.hpp"
#include "ClassFileViewer.hpp"

StaticClass::StaticClass(ClassFile* class_file)
{
  this->class_file = class_file;
  for (int i=0;i<class_file->fields_count;i++) {
      FieldInfo finfo = class_file->fields[i];

      if (finfo.access_flags & FIELD_FLAG_ACC_STATIC) {
          std::string fieldName = get_formatted_constant(class_file->constant_pool, finfo.name_index);
          std::string fieldDescriptor = get_formatted_constant(class_file->constant_pool, finfo.descriptor_index);

          char fieldType = fieldDescriptor[0];
          Value value;

          switch (fieldType) {
          case 'B':
              value.print_type = ValueType::BYTE;
              value.type = ValueType::BYTE;
              value.data.byte_value = 0;
              break;
          case 'C':
              value.print_type = ValueType::CHAR;
              value.type = ValueType::CHAR;
              value.data.char_value = 0;
              break;
          case 'D':
              value.print_type = ValueType::DOUBLE;
              value.type = ValueType::DOUBLE;
              value.data.double_value = 0;
              break;
          case 'F':
              value.print_type = ValueType::FLOAT;
              value.type = ValueType::FLOAT;
              value.data.float_value = 0;
              break;
          case 'I':
              value.print_type = ValueType::INT;
              value.type = ValueType::INT;
              value.data.int_value = 0;
              break;
          case 'J':
              value.print_type= ValueType::LONG;
              value.type = ValueType::LONG;
              value.data.long_value = 0;
              break;
          case 'S':
              value.print_type= ValueType::SHORT;
              value.type = ValueType::SHORT;
              value.data.short_value = 0;
              break;
          case 'Z':
              value.print_type = ValueType::BOOLEAN;
              value.type = ValueType::BOOLEAN;
              value.data.char_value = false;
              break;
          default:
              value.print_type = ValueType::REFERENCE;
              value.type = ValueType::REFERENCE;
              value.data.object = 0;
          }

          insert_value(value, fieldName);
      }
  }
}



ClassFile* StaticClass::get_class_file()
{
  return this->class_file;
}

void StaticClass::insert_value(const Value& value, const string& fieldName)
{
  static_fields[fieldName] = value;
}

Value StaticClass::get_value(const std::string& fieldName) 
{
    auto it = this->static_fields.find(fieldName);

    if (it == this->static_fields.end()) {
        cerr << "NoSuchFieldError: " << fieldName << endl;
        exit(1);
    }

    return it->second;
}

bool StaticClass::check_field(const std::string& fieldName)
{
  return this->static_fields.count(fieldName) > 0;
}

/* Função que vai abrir o arquivo dado */
std::string StaticClass::initialize_file(char *argv[])
{
  std::string str(argv[2]);
  std::string nome = str.substr(0, str.length() - 6);
  return nome;
}

