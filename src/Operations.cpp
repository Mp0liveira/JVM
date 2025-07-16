#include "Operations.hpp"

Operations::Operations()
    : is_wide(false)
{
    initInstructions();
}

Operations::~Operations()
{
}

void Operations::executeMethods(StaticClass* class_runtime)
{
    Stack& Stack = Stack::get_instance();
    vector<Value> arguments;
    Value commandLineArgs = {
        .type = ValueType::REFERENCE,
        .data = { .object = new Array(ValueType::REFERENCE) }
    };
    arguments.push_back(commandLineArgs);
    Stack.push_frame(new Frame(class_runtime, "main", "([Ljava/lang/String;)V", arguments));
    if (verifyMethod(class_runtime, "<clinit>", "()V")) {
        Stack.push_frame(new Frame(class_runtime, "<clinit>", "()V", arguments));
    }
    while (Stack.size() > 0) {
        Frame* top_frame = Stack.get_top_frame();
        u1* code = top_frame->get_code(top_frame->pc);

        (*this.*generic_functions_arr[code[0]])();
    }
}

bool Operations::verifyMethod(StaticClass* class_runtime, const string& name, const string& descriptor)
{
    ClassFile* class_file = class_runtime->get_class_file();
    bool found = false;
    MethodInfo method;
    for (int i = 0; i < class_file->methods_count; i++) {
        method = class_file->methods[i];
        string method_name = get_formatted_constant(class_file->constant_pool, method.name_index);
        string method_desc = get_formatted_constant(class_file->constant_pool, method.descriptor_index);
        if (method_name == name && method_desc == descriptor) {
            found = true;
            break;
        }
    }
    return found;
}

void Operations::populateMultiarray(Array* array, ValueType value_type, stack<int> count)
{
    int curr_count = count.top();
    count.pop();
    ValueType array_type = (count.size() > 1) ? ValueType::REFERENCE : value_type;
    if (count.size() == 0) {
        for (int i = 0; i < curr_count; i++) {
            Value sub_array_value = {
                .print_type = value_type,
                .type = value_type,
                .data = { .long_value = 0 }
            };
            array->push_value(sub_array_value);
        }
    } else {
        for (int i = 0; i < curr_count; i++) {
            Array* subarray = new Array(array_type);
            populateMultiarray(subarray, value_type, count);
            Value sub_array_value = { 
                .print_type = ValueType::REFERENCE,
                .type = ValueType::REFERENCE, 
                .data = { .object = subarray } };
            array->push_value(sub_array_value);
        }
    }
}

void Operations::nop()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    top_frame->pc++;
}

void Operations::aconst_null()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = { 
        .print_type = ValueType::REFERENCE, 
        .type = ValueType::REFERENCE, 
        .data = { .object = NULL } };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iconst_m1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = -1 }
    };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iconst_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = 0 }
    };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iconst_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = 1 }
    };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iconst_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = 2 }
    };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iconst_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = 3 }
    };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iconst_4()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = 4 }
    };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iconst_5()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = 5 }
    };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::lconst_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    Value value = {
        .print_type = ValueType::LONG,
        value.type = ValueType::LONG,
        value.data = { .long_value = 0 }
    };
    top_frame->push_operand_stack(padding);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::lconst_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    Value value = {
        .print_type = ValueType::LONG,
        value.type = ValueType::LONG,
        value.data = { .long_value = 1 }
    };
    top_frame->push_operand_stack(padding);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::fconst_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = {
        value.print_type = ValueType::FLOAT,
        value.type = ValueType::FLOAT,
        value.data = { .float_value = 0 } 
    };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::fconst_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = {
        value.print_type = ValueType::FLOAT,
        value.type = ValueType::FLOAT,
        value.data = { .float_value = 1 } 
    };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::fconst_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = {
        value.print_type = ValueType::FLOAT,
        value.type = ValueType::FLOAT,
        value.data = { .float_value = 2 } 
    };
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::dconst_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    Value value = { 
        value.print_type = ValueType::DOUBLE,
        value.type = ValueType::DOUBLE,
        value.data = { .double_value = 0 }
    };
    top_frame->push_operand_stack(padding);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::dconst_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    Value value = {
        .print_type = ValueType::DOUBLE,
        .type = ValueType::DOUBLE,
        .data =  { .double_value = 1 }
    };
    top_frame->push_operand_stack(padding);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::bipush()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte = code[1];
    Value value = {
        .print_type = ValueType::BYTE,
        .type = ValueType::INT,
        .data = { .int_value = (int32_t)(int8_t)byte }
    };
    top_frame->push_operand_stack(value);
    top_frame->pc += 2;
}

void Operations::sipush()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t short_value = (byte1 << 8) | byte2;
    Value value = {
        .print_type = ValueType::SHORT,
        .type = ValueType::INT,
        .data = { .int_value = (int32_t)(int16_t)short_value }
    };
    top_frame->push_operand_stack(value);
    top_frame->pc += 3;
}

void Operations::ldc()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 index = code[1];
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    ConstantPoolInfo entry = constant_pool[index - 1];
    Value value;
    if (entry.tag == ConstStr) {
        ConstantPoolInfo utf8_entry = constant_pool[entry.info.str_info.string_index - 1];
        assert(utf8_entry.tag == ConstUtf8);
        u1* bytes = utf8_entry.info.utf8_info.bytes;
        char utf8_str[utf8_entry.info.utf8_info.length + 1];
        int i;
        for (i = 0; i < utf8_entry.info.utf8_info.length; i++) {
            utf8_str[i] = bytes[i];
        }
        utf8_str[i] = '\0';
        value = {
            .print_type = ValueType::REFERENCE,
            .type = ValueType::REFERENCE,
            .data = { .object = new StrObject(utf8_str) }
        };
    } else if (entry.tag == ConstInt) {
        value = {
            .print_type = ValueType::INT,
            .type = ValueType::INT,
            .data = { .int_value = (int32_t)entry.info.int_info.bytes }
        };
    } else if (entry.tag == ConstFloat) {
        u4 floatBytes = entry.info.float_info.bytes;
        int s = ((floatBytes >> 31) == 0) ? 1 : -1;
        int e = ((floatBytes >> 23) & 0xff);
        int m = (e == 0) ? (floatBytes & 0x7fffff) << 1 : (floatBytes & 0x7fffff) | 0x800000;
        float number = s * m * pow(2, e - 150);
        value = { 
            .print_type = ValueType::FLOAT,
            .type = ValueType::FLOAT,
            .data = { .float_value = number }
        };
    } else {
        
        cerr << "ldc trying to access invalid constant pool element " << entry.tag << endl;
        exit(1);
    }
    top_frame->push_operand_stack(value);
    top_frame->pc += 2;
}

void Operations::ldc_w()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    u2 index = (byte1 << 8) | byte2;
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    ConstantPoolInfo entry = constant_pool[index - 1];
    Value value;
    if (entry.tag == ConstStr) {
        ConstantPoolInfo utf8_entry = constant_pool[entry.info.str_info.string_index - 1];
        assert(utf8_entry.tag == ConstUtf8);
        u1* bytes = utf8_entry.info.utf8_info.bytes;
        char utf8_str[utf8_entry.info.utf8_info.length + 1];
        int i;
        for (i = 0; i < utf8_entry.info.utf8_info.length; i++) {
            utf8_str[i] = bytes[i];
        }
        utf8_str[i] = '\0';
        value = {
            .print_type = ValueType::REFERENCE,
            .type = ValueType::REFERENCE,
            .data = { .object = new StrObject(utf8_str) }
        };
    } else if (entry.tag == ConstInt) {
        value = {
            .print_type = ValueType::INT,
            .type = ValueType::INT,
            .data = { .int_value = (int)entry.info.int_info.bytes }
        };
    } else if (entry.tag == ConstFloat) {
        u4 floatBytes = entry.info.float_info.bytes;
        int s = ((floatBytes >> 31) == 0) ? 1 : -1;
        int e = ((floatBytes >> 23) & 0xff);
        int m = (e == 0) ? (floatBytes & 0x7fffff) << 1 : (floatBytes & 0x7fffff) | 0x800000;
        float number = s * m * pow(2, e - 150);
        value = {
            .print_type = ValueType::FLOAT,
            .type = ValueType::FLOAT,
            .data = { .float_value = number }
        };
    } else {
        cerr << "ldc_w trying to access invalid constant pool element " << entry.tag << endl;
        exit(1);
    }
    top_frame->push_operand_stack(value);
    top_frame->pc += 3;
}

void Operations::ldc2_w()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    u2 index = (byte1 << 8) | byte2;
    ConstantPoolInfo* class_file = *(top_frame->get_constant_pool());
    ConstantPoolInfo entry = class_file[index - 1];
    Value value;
    if (entry.tag == ConstLong) {
        u4 highBytes = entry.info.long_info.high_bytes;
        u4 lowBytes = entry.info.long_info.low_bytes;
        int64_t longNumber = ((int64_t)highBytes << 32) + lowBytes;
        value = {
            .print_type = ValueType::LONG,
            .type = ValueType::LONG,
            .data = { .long_value = longNumber }
        };
        Value padding = {
            .print_type = ValueType::PADDING,
            .type = ValueType::PADDING
        };
        top_frame->push_operand_stack(padding);
    } else if (entry.tag == ConstDouble) {
        u4 highBytes = entry.info.double_info.high_bytes;
        u4 lowBytes = entry.info.double_info.low_bytes;
        int64_t longNumber = ((int64_t)highBytes << 32) + lowBytes;
        int32_t s = ((longNumber >> 63) == 0) ? 1 : -1;
        int32_t e = (int32_t)((longNumber >> 52) & 0x7ffL);
        int64_t m = (e == 0) ? (longNumber & 0xfffffffffffffL) << 1 : (longNumber & 0xfffffffffffffL) | 0x10000000000000L;
        double doubleNumber = s * m * pow(2, e - 1075);
        value = {
            .print_type = ValueType::DOUBLE,
            .type = ValueType::DOUBLE,
            .data = { .double_value = doubleNumber }
        };
        Value padding = {
            .print_type = ValueType::PADDING,
            .type = ValueType::PADDING
        };
        top_frame->push_operand_stack(padding);
    } else {
        cerr << "ldc2_w trying to access invalid constant pool element " << entry.tag << endl;
        exit(1);
    }
    top_frame->push_operand_stack(value);
    top_frame->pc += 3;
}

void Operations::iload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    int16_t index = (int16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
        top_frame->pc += 3;
        is_wide = false;
    } else {
        top_frame->pc += 2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > index));
    Value value = top_frame->get_local_variable_value(index);
    assert(value.type == ValueType::INT);
    top_frame->push_operand_stack(value);
}

void Operations::lload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    int16_t index = (int16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
        top_frame->pc += 3;
        is_wide = false;
    } else {
        top_frame->pc += 2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > (index + 1)));
    Value value = top_frame->get_local_variable_value(index);
    assert(value.type == ValueType::LONG);
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    top_frame->push_operand_stack(padding);
    top_frame->push_operand_stack(value);
}

void Operations::fload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    int16_t index = (int16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
        top_frame->pc += 3;
        is_wide = false;
    } else {
        top_frame->pc += 2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > index));
    Value value = top_frame->get_local_variable_value(index);
    assert(value.type == ValueType::FLOAT);
    top_frame->push_operand_stack(value);
}

void Operations::dload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    int16_t index = (int16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
        top_frame->pc += 3;
        is_wide = false;
    } else {
        top_frame->pc += 2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > (index + 1)));
    Value value = top_frame->get_local_variable_value(index);
    assert(value.type == ValueType::DOUBLE);
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    top_frame->push_operand_stack(padding);
    top_frame->push_operand_stack(value);
}

void Operations::aload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    int16_t index = (int16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
        top_frame->pc += 3;
        is_wide = false;
    } else {
        top_frame->pc += 2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > index));
    Value value = top_frame->get_local_variable_value(index);
    assert(value.type == ValueType::REFERENCE);
    top_frame->push_operand_stack(value);
}

void Operations::iload_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(0);
    assert(value.type == ValueType::INT);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iload_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(1);
    assert(value.type == ValueType::INT);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iload_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(2);
    assert(value.type == ValueType::INT);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iload_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(3);
    assert(value.type == ValueType::INT);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::lload_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value;
    value = top_frame->get_local_variable_value(1);
    assert(value.type == ValueType::PADDING);
    top_frame->push_operand_stack(value);
    value = top_frame->get_local_variable_value(0);
    assert(value.type == ValueType::LONG);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::lload_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value;
    value = top_frame->get_local_variable_value(2);
    assert(value.type == ValueType::PADDING);
    top_frame->push_operand_stack(value);
    value = top_frame->get_local_variable_value(1);
    assert(value.type == ValueType::LONG);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::lload_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value;
    value = top_frame->get_local_variable_value(3);
    assert(value.type == ValueType::PADDING);
    top_frame->push_operand_stack(value);
    value = top_frame->get_local_variable_value(2);
    assert(value.type == ValueType::LONG);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::lload_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value;
    value = top_frame->get_local_variable_value(4);
    assert(value.type == ValueType::PADDING);
    top_frame->push_operand_stack(value);
    value = top_frame->get_local_variable_value(3);
    assert(value.type == ValueType::LONG);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::fload_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(0);
    assert(value.type == ValueType::FLOAT);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::fload_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(1);
    assert(value.type == ValueType::FLOAT);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::fload_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(2);
    assert(value.type == ValueType::FLOAT);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::fload_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(3);
    assert(value.type == ValueType::FLOAT);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::dload_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value;
    value = top_frame->get_local_variable_value(1);
    assert(value.type == ValueType::PADDING);
    top_frame->push_operand_stack(value);
    value = top_frame->get_local_variable_value(0);
    assert(value.type == ValueType::DOUBLE);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::dload_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value;
    value = top_frame->get_local_variable_value(2);
    assert(value.type == ValueType::PADDING);
    top_frame->push_operand_stack(value);
    value = top_frame->get_local_variable_value(1);
    assert(value.type == ValueType::DOUBLE);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::dload_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value;
    value = top_frame->get_local_variable_value(3);
    assert(value.type == ValueType::PADDING);
    top_frame->push_operand_stack(value);
    value = top_frame->get_local_variable_value(2);
    assert(value.type == ValueType::DOUBLE);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::dload_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value;
    value = top_frame->get_local_variable_value(4);
    assert(value.type == ValueType::PADDING);
    top_frame->push_operand_stack(value);
    value = top_frame->get_local_variable_value(3);
    assert(value.type == ValueType::DOUBLE);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::aload_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(0);
    assert(value.type == ValueType::REFERENCE);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::aload_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(1);
    assert(value.type == ValueType::REFERENCE);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::aload_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(2);
    assert(value.type == ValueType::REFERENCE);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::aload_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->get_local_variable_value(3);
    assert(value.type == ValueType::REFERENCE);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::iaload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    top_frame->push_operand_stack(array->get_value(index.data.int_value));
    top_frame->pc++;
}

void Operations::laload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if ((signed)index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    top_frame->push_operand_stack(padding);
    top_frame->push_operand_stack(array->get_value(index.data.int_value));
    top_frame->pc++;
}

void Operations::faload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    top_frame->push_operand_stack(array->get_value(index.data.int_value));
    top_frame->pc++;
}

void Operations::daload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    top_frame->push_operand_stack(padding);
    top_frame->push_operand_stack(array->get_value(index.data.int_value));
    top_frame->pc++;
}

void Operations::aaload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    top_frame->push_operand_stack(array->get_value(index.data.int_value));
    top_frame->pc++;
}

void Operations::baload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    Value value = array->get_value(index.data.int_value);
    assert(value.type == ValueType::BOOLEAN || value.type == ValueType::BYTE);
    if (value.type == ValueType::BOOLEAN) {
        value = {
            .print_type = ValueType::BOOLEAN,
            .type = ValueType::INT,
            .data = { .int_value = value.data.boolean_value }
        };
    } else {
        value = {
            .print_type = ValueType::BYTE,
            .type = ValueType::INT,
            .data = { .int_value = (int32_t)value.data.byte_value }
        };
    }
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::caload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    Value char_value = array->get_value(index.data.int_value);
    char_value = {
        .print_type = ValueType::CHAR,
        .type = ValueType::INT,
        .data = { .int_value = char_value.data.char_value }
    };
    top_frame->push_operand_stack(char_value);
    top_frame->pc++;
}

void Operations::saload()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    Value short_value = array->get_value(index.data.int_value);
    short_value = {
        .print_type = ValueType::SHORT,
        .type = ValueType::INT,
        .data = { .int_value = (int32_t)short_value.data.short_value }
    };
    top_frame->push_operand_stack(short_value);
    top_frame->pc++;
}

void Operations::istore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    int16_t index = (int16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
        top_frame->pc += 3;
        is_wide = false;
    } else {
        top_frame->pc += 2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > index));
    top_frame->set_local_variable(value, index);
}

void Operations::lstore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::LONG);
    top_frame->pop_operand_stack();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    int16_t index = (int16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
        top_frame->pc += 3;
        is_wide = false;
    } else {
        top_frame->pc += 2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > (index + 1)));
    top_frame->set_local_variable(value, index);
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    top_frame->set_local_variable(padding, index + 1);
}

void Operations::fstore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::FLOAT);
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    int16_t index = (int16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
        top_frame->pc += 3;
        is_wide = false;
    } else {
        top_frame->pc += 2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > index));
    top_frame->set_local_variable(value, index);
}

void Operations::dstore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::DOUBLE);
    top_frame->pop_operand_stack();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    int16_t index = (int16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
        top_frame->pc += 3;
        is_wide = false;
    } else {
        top_frame->pc += 2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > (index + 1)));
    top_frame->set_local_variable(value, index);
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    top_frame->set_local_variable(padding, index + 1);
}

void Operations::astore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::REFERENCE);
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    int16_t index = (int16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
        top_frame->pc += 3;
        is_wide = false;
    } else {
        top_frame->pc += 2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > index));
    top_frame->set_local_variable(value, index);
}

void Operations::istore_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    top_frame->set_local_variable(value, 0);
    top_frame->pc++;
}

void Operations::istore_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    top_frame->set_local_variable(value, 1);
    top_frame->pc++;
}

void Operations::istore_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    top_frame->set_local_variable(value, 2);
    top_frame->pc++;
}

void Operations::istore_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    top_frame->set_local_variable(value, 3);
    top_frame->pc++;
}

void Operations::lstore_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::LONG);
    top_frame->set_local_variable(value, 0);
    value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::PADDING);
    top_frame->set_local_variable(value, 1);
    top_frame->pc++;
}

void Operations::lstore_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::LONG);
    top_frame->set_local_variable(value, 1);
    value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::PADDING);
    top_frame->set_local_variable(value, 2);
    top_frame->pc++;
}

void Operations::lstore_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::LONG);
    top_frame->set_local_variable(value, 2);
    value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::PADDING);
    top_frame->set_local_variable(value, 3);
    top_frame->pc++;
}

void Operations::lstore_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::LONG);
    top_frame->set_local_variable(value, 3);
    value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::PADDING);
    top_frame->set_local_variable(value, 4);
    top_frame->pc++;
}

void Operations::fstore_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::FLOAT);
    top_frame->set_local_variable(value, 0);
    top_frame->pc++;
}

void Operations::fstore_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::FLOAT);
    top_frame->set_local_variable(value, 1);
    top_frame->pc++;
}

void Operations::fstore_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::FLOAT);
    top_frame->set_local_variable(value, 2);
    top_frame->pc++;
}

void Operations::fstore_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::FLOAT);
    top_frame->set_local_variable(value, 3);
    top_frame->pc++;
}

void Operations::dstore_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::DOUBLE);
    top_frame->set_local_variable(value, 0);
    value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::PADDING);
    top_frame->set_local_variable(value, 1);
    top_frame->pc++;
}

void Operations::dstore_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::DOUBLE);
    top_frame->set_local_variable(value, 1);
    value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::PADDING);
    top_frame->set_local_variable(value, 2);
    top_frame->pc++;
}

void Operations::dstore_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::DOUBLE);
    top_frame->set_local_variable(value, 2);
    value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::PADDING);
    top_frame->set_local_variable(value, 3);
    top_frame->pc++;
}

void Operations::dstore_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::DOUBLE);
    top_frame->set_local_variable(value, 3);
    value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::PADDING);
    top_frame->set_local_variable(value, 4);
    top_frame->pc++;
}

void Operations::astore_0()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::REFERENCE);
    top_frame->set_local_variable(value, 0);
    top_frame->pc++;
}

void Operations::astore_1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::REFERENCE);
    top_frame->set_local_variable(value, 1);
    top_frame->pc++;
}

void Operations::astore_2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::REFERENCE);
    top_frame->set_local_variable(value, 2);
    top_frame->pc++;
}

void Operations::astore_3()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::REFERENCE);
    top_frame->set_local_variable(value, 3);
    top_frame->pc++;
}

void Operations::iastore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value >= (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    value.print_type = ValueType::INT;
    assert(value.type == array->array_content_type());
    array->change_value(index.data.int_value, value);
    top_frame->pc++;
}

void Operations::lastore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::LONG);
    Value padding = top_frame->pop_operand_stack();
    assert(padding.type == ValueType::PADDING);
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value >= (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    assert(value.type == array->array_content_type());
    array->change_value(index.data.int_value, value);
    top_frame->pc++;
}

void Operations::fastore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::FLOAT);
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value >= (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    assert(value.type == array->array_content_type());
    array->change_value(index.data.int_value, value);
    top_frame->pc++;
}

void Operations::dastore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::DOUBLE);
    Value padding = top_frame->pop_operand_stack();
    assert(padding.type == ValueType::PADDING);
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value >= (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    assert(value.type == array->array_content_type());
    array->change_value(index.data.int_value, value);
    top_frame->pc++;
}

void Operations::aastore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::REFERENCE);
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value >= (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    array->change_value(index.data.int_value, value);
    top_frame->pc++;
}

void Operations::bastore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    assert(array->array_content_type() == ValueType::BOOLEAN || array->array_content_type() == ValueType::BYTE);
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    if (array->array_content_type() == ValueType::BOOLEAN) {
        value = {
            .print_type = ValueType::BOOLEAN,
            .type = ValueType::BOOLEAN,
            .data = { .boolean_value = (value.data.int_value != 0) ? true : false }
        };
    } else {
        value = {
            .print_type = ValueType::BYTE,
            .type = ValueType::BYTE,
            .data = { .byte_value = (int8_t)value.data.int_value }
        };
    }
    array->change_value(index.data.int_value, value);
    top_frame->pc++;
}

void Operations::castore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    value = {
        .print_type = ValueType::CHAR,
        .type = ValueType::CHAR,
        .data = { .char_value = (uint8_t)value.data.int_value }
    };
    array->change_value(index.data.int_value, value);
    top_frame->pc++;
}

void Operations::sastore()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Array* array;
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    Value index = top_frame->pop_operand_stack();
    assert(index.type == ValueType::INT);
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->object_type() == ObjectType::ARRAY);
    array = (Array*)arrayref.data.object;
    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > (signed)array->get_size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    value = {
        .print_type = ValueType::SHORT,
        .type = ValueType::SHORT,
        .data = { .short_value = (int16_t)value.data.int_value }
    };
    array->change_value(index.data.int_value, value);
    top_frame->pc++;
}

void Operations::pop()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type != ValueType::LONG);
    assert(value.type != ValueType::DOUBLE);
    top_frame->pc++;
}

void Operations::pop2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    top_frame->pc++;
}

void Operations::dup()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type != ValueType::LONG);
    assert(value.type != ValueType::DOUBLE);
    top_frame->push_operand_stack(value);
    top_frame->push_operand_stack(value);
    top_frame->pc++;
}

void Operations::dup_x1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type != ValueType::LONG);
    assert(value_1.type != ValueType::DOUBLE);
    Value value_2 = top_frame->pop_operand_stack();
    assert(value_2.type != ValueType::LONG);
    assert(value_2.type != ValueType::DOUBLE);
    top_frame->push_operand_stack(value_1);
    top_frame->push_operand_stack(value_2);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::dup_x2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_3 = top_frame->pop_operand_stack();
    assert(value_1.type != ValueType::LONG);
    assert(value_1.type != ValueType::DOUBLE);
    assert(value_3.type != ValueType::LONG);
    assert(value_3.type != ValueType::DOUBLE);
    top_frame->push_operand_stack(value_1);
    top_frame->push_operand_stack(value_3);
    top_frame->push_operand_stack(value_2);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::dup2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    Value value_2 = top_frame->pop_operand_stack();
    assert(value_2.type != ValueType::LONG);
    assert(value_2.type != ValueType::DOUBLE);
    top_frame->push_operand_stack(value_2);
    top_frame->push_operand_stack(value_1);
    top_frame->push_operand_stack(value_2);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::dup2_x1()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_3 = top_frame->pop_operand_stack();
    assert(value_2.type != ValueType::LONG);
    assert(value_2.type != ValueType::DOUBLE);
    assert(value_3.type != ValueType::LONG);
    assert(value_3.type != ValueType::DOUBLE);
    top_frame->push_operand_stack(value_2);
    top_frame->push_operand_stack(value_1);
    top_frame->push_operand_stack(value_3);
    top_frame->push_operand_stack(value_2);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::dup2_x2()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_3 = top_frame->pop_operand_stack();
    Value value_4 = top_frame->pop_operand_stack();
    assert(value_2.type != ValueType::LONG);
    assert(value_2.type != ValueType::DOUBLE);
    assert(value_4.type != ValueType::LONG);
    assert(value_4.type != ValueType::DOUBLE);
    top_frame->push_operand_stack(value_2);
    top_frame->push_operand_stack(value_1);
    top_frame->push_operand_stack(value_4);
    top_frame->push_operand_stack(value_3);
    top_frame->push_operand_stack(value_2);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::swap()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    Value value_2 = top_frame->pop_operand_stack();
    assert(value_1.type != ValueType::LONG);
    assert(value_1.type != ValueType::DOUBLE);
    assert(value_2.type != ValueType::LONG);
    assert(value_2.type != ValueType::DOUBLE);
    top_frame->push_operand_stack(value_1);
    top_frame->push_operand_stack(value_2);
    top_frame->pc++;
}

void Operations::iadd()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);
    value_1.data.int_value = value_1.data.int_value + (value_2.data.int_value);
    value_1.print_type = ValueType::INT;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::ladd()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::LONG);
    assert(value_1.type == ValueType::LONG);
    value_1.data.long_value = value_1.data.long_value + (value_2.data.long_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::fadd()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::FLOAT);
    assert(value_1.type == ValueType::FLOAT);
    value_1.data.float_value = value_1.data.float_value + (value_2.data.float_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::dadd()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::DOUBLE);
    assert(value_1.type == ValueType::DOUBLE);
    value_1.data.double_value = value_1.data.double_value + (value_2.data.double_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::isub()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);
    value_1.print_type = ValueType::INT;
    value_1.data.int_value = value_1.data.int_value - (value_2.data.int_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::lsub()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::LONG);
    assert(value_1.type == ValueType::LONG);
    value_1.data.long_value = value_1.data.long_value - (value_2.data.long_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::fsub()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::FLOAT);
    assert(value_1.type == ValueType::FLOAT);
    value_1.data.float_value = value_1.data.float_value - (value_2.data.float_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::dsub()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::DOUBLE);
    assert(value_1.type == ValueType::DOUBLE);
    value_1.data.double_value = value_1.data.double_value - (value_2.data.double_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::imul()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);
    value_1.print_type = ValueType::INT;
    value_1.data.int_value = value_1.data.int_value * (value_2.data.int_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::lmul()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::LONG);
    assert(value_1.type == ValueType::LONG);
    value_1.data.long_value = value_1.data.long_value * (value_2.data.long_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::fmul()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::FLOAT);
    assert(value_1.type == ValueType::FLOAT);
    value_1.data.float_value = value_1.data.float_value * (value_2.data.float_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::dmul()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::DOUBLE);
    assert(value_1.type == ValueType::DOUBLE);
    value_1.data.double_value = value_1.data.double_value * (value_2.data.double_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::idiv()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);
    if (value_2.data.int_value == 0) {
        cerr << "ArithmeticException" << endl;
        exit(2);
    }
    value_1.print_type = ValueType::INT;
    value_1.data.int_value = value_1.data.int_value / (value_2.data.int_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::ldiv()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::LONG);
    assert(value_1.type == ValueType::LONG);
    if (value_2.data.long_value == 0) {
        cerr << "ArithmeticException" << endl;
        exit(2);
    }
    value_1.data.long_value = value_1.data.long_value / (value_2.data.long_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::fdiv()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::FLOAT);
    assert(value_1.type == ValueType::FLOAT);
    if (value_2.data.float_value == 0) {
        cerr << "ArithmeticException" << endl;
        exit(2);
    }
    value_1.data.float_value = value_1.data.float_value / (value_2.data.float_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::ddiv()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::DOUBLE);
    assert(value_1.type == ValueType::DOUBLE);
    if (value_2.data.double_value == 0) {
        cerr << "ArithmeticException" << endl;
        exit(2);
    }
    value_1.data.double_value = value_1.data.double_value / (value_2.data.double_value);
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::irem()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);
    if (value_2.data.int_value == 0) {
        cerr << "ArithmeticException" << endl;
        exit(2);
    }
    value_1.print_type = ValueType::INT;
    value_1.data.int_value = value_1.data.int_value - (value_1.data.int_value / value_2.data.int_value) * value_2.data.int_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::lrem()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();

    assert(value_2.type == ValueType::LONG);
    assert(value_1.type == ValueType::LONG);
    if (value_2.data.long_value == 0) {
        cerr << "ArithmeticException" << endl;
        exit(2);
    }

    value_1.data.long_value = value_1.data.long_value - (value_1.data.long_value / value_2.data.long_value) * value_2.data.long_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::frem()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::FLOAT);
    assert(value_1.type == ValueType::FLOAT);
    if (value_2.data.float_value == 0) {
        cerr << "ArithmeticException" << endl;
        exit(2);
    }

    value_1.data.float_value = value_1.data.float_value
        - ((uint32_t)(value_1.data.float_value / value_2.data.float_value)) * value_2.data.float_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::drem()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();

    assert(value_2.type == ValueType::DOUBLE);
    assert(value_1.type == ValueType::DOUBLE);
    if (value_2.data.double_value == 0) {
        cerr << "ArithmeticException" << endl;
        exit(2);
    }

    value_1.data.double_value = value_1.data.double_value
        - ((uint64_t)(value_1.data.double_value / value_2.data.double_value)) * value_2.data.double_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::ineg()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::INT);
    value_1.print_type = ValueType::INT;
    value_1.data.int_value = -value_1.data.int_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::lneg()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();

    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::LONG);
    value_1.data.long_value = -value_1.data.long_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::fneg()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::FLOAT);
    value_1.data.float_value = -value_1.data.float_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::dneg()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();

    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::DOUBLE);
    value_1.data.double_value = -value_1.data.double_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::ishl()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);

    value_2.data.int_value = 0x1f & value_2.data.int_value;
    value_1.data.int_value = value_1.data.int_value << value_2.data.int_value;
    value_1.print_type = ValueType::INT;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::lshl()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();

    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::LONG);
    value_2.data.long_value = 0x3f & value_2.data.long_value;
    value_1.data.long_value = (value_1.data.long_value) << value_2.data.int_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::ishr()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);

    value_2.data.int_value = 0x1f & value_2.data.int_value;
    value_1.data.int_value = value_1.data.int_value >> value_2.data.int_value;
    value_1.print_type = ValueType::INT;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::lshr()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();

    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::LONG);

    value_2.data.long_value = 0x3f & value_2.data.long_value;
    value_1.data.long_value = value_1.data.long_value >> value_2.data.long_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::iushr()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);
    value_2.data.int_value = 0x1f & value_2.data.int_value;
    value_1.data.int_value = value_1.data.int_value >> value_2.data.int_value;
    if (value_1.data.int_value < 0) {
        value_1.data.int_value = value_1.data.int_value + (2 << ~(value_2.data.int_value));
    }
    value_1.print_type = ValueType::INT;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::lushr()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::LONG);
    value_2.data.int_value = 0x3f & value_2.data.int_value;
    value_1.data.long_value = value_1.data.long_value >> value_2.data.int_value;
    if (value_1.data.long_value < 0) {
        value_1.data.long_value = value_1.data.long_value + ((int64_t)2 << ~(value_2.data.int_value));
    }
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::iand()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);
    value_1.print_type = ValueType::INT;
    value_1.data.int_value = value_1.data.int_value & value_2.data.int_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::land()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();

    assert(value_2.type == ValueType::LONG);
    assert(value_1.type == ValueType::LONG);

    value_1.data.long_value = value_1.data.long_value & value_2.data.long_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::ior()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);
    value_1.print_type = ValueType::INT;
    value_1.data.int_value = value_1.data.int_value | value_2.data.int_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::lor()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();

    assert(value_2.type == ValueType::LONG);
    assert(value_1.type == ValueType::LONG);
    value_1.data.long_value = value_1.data.long_value | value_2.data.long_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::ixor()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);
    value_1.print_type = ValueType::INT;
    value_1.data.int_value = value_1.data.int_value ^ value_2.data.int_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::lxor()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();

    assert(value_2.type == ValueType::LONG);
    assert(value_1.type == ValueType::LONG);
    value_1.data.long_value = value_1.data.long_value ^ value_2.data.long_value;
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::iinc()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u2 index = 0;
    if (is_wide) {
        index = (code[1] << 8) | code[2];
    } else {
        index += code[1];
    }
    Value localVariable = top_frame->get_local_variable_value(index);
    assert(localVariable.type == ValueType::INT);
    int32_t inc;
    if (is_wide) {
        uint16_t constant = (code[3] << 8) | code[4];
        inc = (int32_t)(int16_t)constant;
    } else {
        inc = (int32_t)(int8_t)code[2];
    }
    localVariable.data.int_value += inc;
    top_frame->set_local_variable(localVariable, index);
    top_frame->pc += is_wide ? 5 : 3;
    is_wide = false;
}

void Operations::i2l()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::INT);
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    top_frame->push_operand_stack(padding);
    value_1 = {
        .print_type = ValueType::LONG,
        .type = ValueType::LONG,
        .data = { .long_value = (int64_t)value_1.data.int_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::i2f()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::INT);
    value_1 = {
        .print_type = ValueType::FLOAT,
        .type = ValueType::FLOAT,
        .data = { .float_value = (float)value_1.data.int_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::i2d()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::INT);
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    top_frame->push_operand_stack(padding);
    value_1 = {
        .print_type = ValueType::DOUBLE,
        .type = ValueType::DOUBLE,
        .data = { .double_value = (double)value_1.data.int_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::l2i()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::LONG);
    value_1 = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = (int32_t)value_1.data.int_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::l2f()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::LONG);
    value_1 = {
        .print_type = ValueType::FLOAT,
        .type = ValueType::FLOAT,
        .data = { .float_value = (float)value_1.data.long_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::l2d()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();

    assert(value_1.type == ValueType::LONG);
    value_1 = {
        .print_type = ValueType::DOUBLE,
        .type = ValueType::DOUBLE,
        .data = { .double_value = (double)value_1.data.long_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::f2i()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::FLOAT);
    value_1 = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = (int32_t)value_1.data.float_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::f2l()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::FLOAT);
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    top_frame->push_operand_stack(padding);
    value_1 = {
        .print_type = ValueType::LONG,
        .type = ValueType::LONG,
        .data = { .long_value = (int64_t)value_1.data.float_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::f2d()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::FLOAT);
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    top_frame->push_operand_stack(padding);
    value_1 = {
        .print_type = ValueType::DOUBLE,
        .type = ValueType::DOUBLE,
        .data = { .double_value = (double)value_1.data.float_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::d2i()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::DOUBLE);
    value_1 = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = (int32_t)value_1.data.double_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::d2l()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();

    assert(value_1.type == ValueType::DOUBLE);
    value_1 = {
        .print_type = ValueType::LONG,
        .type = ValueType::LONG,
        .data = { .long_value = (int64_t)value_1.data.double_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::d2f()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::DOUBLE);
    value_1 = {
        .print_type = ValueType::FLOAT,
        .type = ValueType::FLOAT,
        .data = { .float_value = (float)value_1.data.double_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::i2b()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::INT);
    value_1 = {
        .print_type = ValueType::BYTE,
        .type = ValueType::INT,
        .data = { .int_value = (int32_t)(int8_t)value_1.data.int_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::i2c()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::INT);
    value_1 = {
        .print_type = ValueType::CHAR,
        .type = ValueType::INT,
        .data = { .char_value = (uint8_t)value_1.data.int_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::i2s()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_1 = top_frame->pop_operand_stack();
    assert(value_1.type == ValueType::INT);
    value_1 = {
        .print_type = ValueType::SHORT,
        .type = ValueType::INT,
        .data = { .short_value = (int16_t)value_1.data.int_value }
    };
    top_frame->push_operand_stack(value_1);
    top_frame->pc++;
}

void Operations::lcmp()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value result = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
    };
    assert(value_2.type == ValueType::LONG);
    assert(value_1.type == ValueType::LONG);
    if (value_1.data.long_value > value_2.data.long_value) {
        result.data.int_value = 1;
    } else if (value_1.data.long_value == value_2.data.long_value) {
        result.data.int_value = 0;
    } else {
        result.data.int_value = -1;
    }
    top_frame->push_operand_stack(result);
    top_frame->pc++;
}

void Operations::fcmpl()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    Value result = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
    };
    assert(value_2.type == ValueType::FLOAT);
    assert(value_1.type == ValueType::FLOAT);
    if (isnan(value_1.data.float_value) || isnan(value_2.data.float_value)) {
        result.data.int_value = -1;
    } else if (value_1.data.float_value > value_2.data.float_value) {
        result.data.int_value = 1;
    } else if (value_1.data.float_value == value_2.data.float_value) {
        result.data.int_value = 0;
    } else {
        result.data.int_value = -1;
    }
    top_frame->push_operand_stack(result);
    top_frame->pc++;
}

void Operations::fcmpg()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    Value result = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
    };
    assert(value_2.type == ValueType::FLOAT);
    assert(value_1.type == ValueType::FLOAT);
    if (isnan(value_1.data.float_value) || isnan(value_2.data.float_value)) {
        result.data.int_value = 1;
    } else if (value_1.data.float_value > value_2.data.float_value) {
        result.data.int_value = 1;
    } else if (value_1.data.float_value == value_2.data.float_value) {
        result.data.int_value = 0;
    } else {
        result.data.int_value = -1;
    }
    top_frame->push_operand_stack(result);
    top_frame->pc++;
}

void Operations::dcmpl()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value result = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
    };
    assert(value_2.type == ValueType::DOUBLE);
    assert(value_1.type == ValueType::DOUBLE);
    if (isnan(value_1.data.double_value) || isnan(value_2.data.double_value)) {
        result.data.int_value = -1;
    } else if (value_1.data.double_value > value_2.data.double_value) {
        result.data.int_value = 1;
    } else if (value_1.data.double_value == value_2.data.double_value) {
        result.data.int_value = 0;
    } else {
        result.data.int_value = -1;
    }
    top_frame->push_operand_stack(result);
    top_frame->pc++;
}

void Operations::dcmpg()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value_2 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value value_1 = top_frame->pop_operand_stack();
    top_frame->pop_operand_stack();
    Value result = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
    };
    assert(value_2.type == ValueType::DOUBLE);
    assert(value_1.type == ValueType::DOUBLE);
    if (isnan(value_1.data.double_value) || isnan(value_2.data.double_value)) {
        result.data.int_value = 1;
    } else if (value_1.data.double_value > value_2.data.double_value) {
        result.data.int_value = 1;
    } else if (value_1.data.double_value == value_2.data.double_value) {
        result.data.int_value = 0;
    } else {
        result.data.int_value = -1;
    }
    top_frame->push_operand_stack(result);
    top_frame->pc++;
}

void Operations::ifeq()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    if (value.data.int_value == 0) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::ifne()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    if (value.data.int_value != 0) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::iflt()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    if (value.data.int_value < 0) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::ifge()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    if (value.data.int_value >= 0) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::ifgt()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    if (value.data.int_value > 0) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::ifle()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value = top_frame->pop_operand_stack();
    assert(value.type == ValueType::INT);
    if (value.data.int_value <= 0) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::if_icmpeq()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value2 = top_frame->pop_operand_stack();
    Value value1 = top_frame->pop_operand_stack();
    assert(value1.type == ValueType::INT);
    assert(value2.type == ValueType::INT);
    if (value1.data.int_value == value2.data.int_value) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::if_icmpne()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value2 = top_frame->pop_operand_stack();
    Value value1 = top_frame->pop_operand_stack();
    assert(value1.type == ValueType::INT);
    assert(value2.type == ValueType::INT);
    if (value1.data.int_value != value2.data.int_value) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::if_icmplt()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value2 = top_frame->pop_operand_stack();
    Value value1 = top_frame->pop_operand_stack();
    assert(value1.type == ValueType::INT);
    assert(value2.type == ValueType::INT);
    if (value1.data.int_value < value2.data.int_value) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::if_icmpge()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value2 = top_frame->pop_operand_stack();
    Value value1 = top_frame->pop_operand_stack();
    assert(value1.type == ValueType::INT);
    assert(value2.type == ValueType::INT);
    if (value1.data.int_value >= value2.data.int_value) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::if_icmpgt()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value2 = top_frame->pop_operand_stack();
    Value value1 = top_frame->pop_operand_stack();
    assert(value1.type == ValueType::INT);
    assert(value2.type == ValueType::INT);
    if (value1.data.int_value > value2.data.int_value) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::if_icmple()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value2 = top_frame->pop_operand_stack();
    Value value1 = top_frame->pop_operand_stack();
    assert(value1.type == ValueType::INT);
    assert(value2.type == ValueType::INT);
    if (value1.data.int_value <= value2.data.int_value) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::if_acmpeq()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value2 = top_frame->pop_operand_stack();
    Value value1 = top_frame->pop_operand_stack();
    assert(value1.type == ValueType::REFERENCE);
    assert(value2.type == ValueType::REFERENCE);
    if (value1.data.object == value2.data.object) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::if_acmpne()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value value2 = top_frame->pop_operand_stack();
    Value value1 = top_frame->pop_operand_stack();
    assert(value1.type == ValueType::REFERENCE);
    assert(value2.type == ValueType::REFERENCE);
    if (value1.data.object != value2.data.object) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        top_frame->pc += branchOffset;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::func_goto()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    int16_t branchOffset = (byte1 << 8) | byte2;
    top_frame->pc += branchOffset;
}

void Operations::jsr()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    int16_t branchOffset = (byte1 << 8) | byte2;
    Value returnAddr = {
        .print_type = ValueType::RETURN_ADDR,
        .type = ValueType::RETURN_ADDR,
        .data = { .return_address = top_frame->pc + 3 }
    };
    top_frame->push_operand_stack(returnAddr);
    top_frame->pc += branchOffset;
}

void Operations::ret()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    uint16_t index = (uint16_t)byte1;
    if (is_wide) {
        u1 byte2 = code[2];
        index = (byte1 << 8) | byte2;
    }
    assert(((int16_t)(top_frame->get_local_variables_vector_size()) > index));
    Value value = top_frame->get_local_variable_value(index);
    assert(value.type == ValueType::RETURN_ADDR);
    top_frame->set_local_variable(value, index);
    top_frame->pc = value.data.return_address;
    is_wide = false;
}

void Operations::tableswitch()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 padding = 4 - (top_frame->pc + 1) % 4;
    padding = (padding == 4) ? 0 : padding;
    u1 defaultbyte1 = code[padding + 1];
    u1 defaultbyte2 = code[padding + 2];
    u1 defaultbyte3 = code[padding + 3];
    u1 defaultbyte4 = code[padding + 4];
    int32_t defaultBytes = (defaultbyte1 << 24) | (defaultbyte2 << 16) | (defaultbyte3 << 8) | defaultbyte4;
    u1 lowbyte1 = code[padding + 5];
    u1 lowbyte2 = code[padding + 6];
    u1 lowbyte3 = code[padding + 7];
    u1 lowbyte4 = code[padding + 8];
    uint32_t lowbytes = (lowbyte1 << 24) | (lowbyte2 << 16) | (lowbyte3 << 8) | lowbyte4;
    u1 highbyte1 = code[padding + 9];
    u1 highbyte2 = code[padding + 10];
    u1 highbyte3 = code[padding + 11];
    u1 highbyte4 = code[padding + 12];
    uint32_t highbytes = (highbyte1 << 24) | (highbyte2 << 16) | (highbyte3 << 8) | highbyte4;
    Value keyValue = top_frame->pop_operand_stack();
    assert(keyValue.type == ValueType::INT);
    int32_t key = keyValue.data.int_value;
    uint32_t i;
    uint32_t baseIndex = padding + 13;
    int32_t offsets = highbytes - lowbytes + 1;
    bool matched = false;
    for (i = 0; i < (unsigned)offsets; i++) {
        if ((unsigned)key == (unsigned)lowbytes) {
            int32_t offset = (code[baseIndex] << 24) | (code[baseIndex + 1] << 16) | (code[baseIndex + 2] << 8) | code[baseIndex + 3];
            top_frame->pc += offset;
            matched = true;
            break;
        }
        lowbytes++;
        baseIndex += 4;
    }
    if (!matched) {
        top_frame->pc += defaultBytes;
    }
}

void Operations::lookupswitch()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 padding = 4 - (top_frame->pc + 1) % 4;
    padding = (padding == 4) ? 0 : padding;
    u1 defaultbyte1 = code[padding + 1];
    u1 defaultbyte2 = code[padding + 2];
    u1 defaultbyte3 = code[padding + 3];
    u1 defaultbyte4 = code[padding + 4];
    int32_t defaultBytes = (defaultbyte1 << 24) | (defaultbyte2 << 16) | (defaultbyte3 << 8) | defaultbyte4;
    u1 npairs1 = code[padding + 5];
    u1 npairs2 = code[padding + 6];
    u1 npairs3 = code[padding + 7];
    u1 npairs4 = code[padding + 8];
    uint32_t npairs = (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;
    Value keyValue = top_frame->pop_operand_stack();
    assert(keyValue.type == ValueType::INT);
    int32_t key = keyValue.data.int_value;
    uint32_t i;
    uint32_t baseIndex = padding + 9;
    bool matched = false;
    for (i = 0; i < npairs; i++) {
        int32_t match = (code[baseIndex] << 24) | (code[baseIndex + 1] << 16) | (code[baseIndex + 2] << 8) | code[baseIndex + 3];
        if (key == match) {
            int32_t offset = (code[baseIndex + 4] << 24) | (code[baseIndex + 5] << 16) | (code[baseIndex + 6] << 8) | code[baseIndex + 7];
            top_frame->pc += offset;
            matched = true;
            break;
        }
        baseIndex += 8;
    }
    if (!matched) {
        top_frame->pc += defaultBytes;
    }
}

void Operations::ireturn()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value returnValue = top_frame->pop_operand_stack();
    assert(returnValue.type == ValueType::INT);
    stack_frame.pop_frame();
    Frame* newTopFrame = stack_frame.get_top_frame();
    newTopFrame->push_operand_stack(returnValue);
}

void Operations::lreturn()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value returnValue = top_frame->pop_operand_stack();
    assert(returnValue.type == ValueType::LONG);
    assert(top_frame->pop_operand_stack().type == ValueType::PADDING);
    stack_frame.pop_frame();
    Frame* newTopFrame = stack_frame.get_top_frame();
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    newTopFrame->push_operand_stack(padding);
    newTopFrame->push_operand_stack(returnValue);
}

void Operations::freturn()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value returnValue = top_frame->pop_operand_stack();
    assert(returnValue.type == ValueType::FLOAT);
    stack_frame.pop_frame();
    Frame* newTopFrame = stack_frame.get_top_frame();
    newTopFrame->push_operand_stack(returnValue);
}

void Operations::dreturn()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value returnValue = top_frame->pop_operand_stack();
    assert(returnValue.type == ValueType::DOUBLE);
    assert(top_frame->pop_operand_stack().type == ValueType::PADDING);
    stack_frame.pop_frame();
    Frame* newTopFrame = stack_frame.get_top_frame();
    Value padding = {
        .print_type = ValueType::PADDING,
        .type = ValueType::PADDING
    };
    newTopFrame->push_operand_stack(padding);
    newTopFrame->push_operand_stack(returnValue);
}

void Operations::areturn()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value returnValue = top_frame->pop_operand_stack();
    assert(returnValue.type == ValueType::REFERENCE);
    stack_frame.pop_frame();
    Frame* newTopFrame = stack_frame.get_top_frame();
    newTopFrame->push_operand_stack(returnValue);
}

void Operations::func_return()
{
    Stack& stack_frame = Stack::get_instance();
    stack_frame.pop_frame();
}

void Operations::getstatic()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t fieldIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo fieldCP = constant_pool[fieldIndex - 1];
    assert(fieldCP.tag == ConstFieldRef);
    ConstFieldRefInfo fieldRef = fieldCP.info.field_ref_info;
    string className = get_formatted_constant(constant_pool, fieldRef.class_index);
    ConstantPoolInfo nameAndTypeCP = constant_pool[fieldRef.name_and_type_index - 1];
    assert(nameAndTypeCP.tag == ConstNameType);
    ConstNameTypeInfo fieldNameAndType = nameAndTypeCP.info.name_type_info;
    string fieldName = get_formatted_constant(constant_pool, fieldNameAndType.name_index);
    string fieldDescriptor = get_formatted_constant(constant_pool, fieldNameAndType.descriptor_index);

    if (className == "java/lang/System" && fieldDescriptor == "Ljava/io/PrintStream;") {
        top_frame->pc += 3;
        return;
    }

    MethodArea& methodArea = MethodArea::get_instance();
    StaticClass* class_runtime = methodArea.load_class(className);
    while (class_runtime != NULL) {
        if (class_runtime->check_field(fieldName) == false) {
            if (class_runtime->get_class_file()->super_class == 0) {
                class_runtime = NULL;
            } else {
                string superClassName = get_formatted_constant(class_runtime->get_class_file()->constant_pool,
                    class_runtime->get_class_file()->super_class);
                class_runtime = methodArea.load_class(superClassName);
            }
        } else {
            break;
        }
    }
    if (class_runtime == NULL) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    if (stack_frame.get_top_frame() != top_frame)
        return;
    Value staticValue = class_runtime->get_value(fieldName);
    switch (staticValue.type) {
    case ValueType::BOOLEAN:
        staticValue.type = ValueType::INT;
        staticValue.print_type = ValueType::BOOLEAN;
        break;
    case ValueType::BYTE:
        staticValue.type = ValueType::INT;
        staticValue.print_type = ValueType::BYTE;
        break;
    case ValueType::SHORT:
        staticValue.type = ValueType::INT;
        staticValue.print_type = ValueType::SHORT;
        break;
    case ValueType::INT:
        staticValue.type = ValueType::INT;
        staticValue.print_type = ValueType::INT;
        break;
    default:
        break;
    }
    if (staticValue.type == ValueType::DOUBLE || staticValue.type == ValueType::LONG) {
        Value paddingValue = {
            .print_type = ValueType::PADDING,
            .type = ValueType::PADDING
        };
        top_frame->push_operand_stack(paddingValue);
    }
    top_frame->push_operand_stack(staticValue);
    top_frame->pc += 3;
}

void Operations::putstatic()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t fieldIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo fieldCP = constant_pool[fieldIndex - 1];
    assert(fieldCP.tag == ConstFieldRef);
    ConstFieldRefInfo fieldRef = fieldCP.info.field_ref_info;
    string className = get_formatted_constant(constant_pool, fieldRef.class_index);
    ConstantPoolInfo nameAndTypeCP = constant_pool[fieldRef.name_and_type_index - 1];
    assert(nameAndTypeCP.tag == ConstNameType);
    ConstNameTypeInfo fieldNameAndType = nameAndTypeCP.info.name_type_info;
    string fieldName = get_formatted_constant(constant_pool, fieldNameAndType.name_index);
    string fieldDescriptor = get_formatted_constant(constant_pool, fieldNameAndType.descriptor_index);
    MethodArea& methodArea = MethodArea::get_instance();
    StaticClass* class_runtime = methodArea.load_class(className);
    while (class_runtime != NULL) {
        if (class_runtime->check_field(fieldName) == false) {
            if (class_runtime->get_class_file()->super_class == 0) {
                class_runtime = NULL;
            } else {
                string superClassName = get_formatted_constant(class_runtime->get_class_file()->constant_pool,
                    class_runtime->get_class_file()->super_class);
                class_runtime = methodArea.load_class(superClassName);
            }
        } else {
            break;
        }
    }
    if (class_runtime == NULL) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    if (stack_frame.get_top_frame() != top_frame)
        return;
    Value topValue = top_frame->pop_operand_stack();
    if (topValue.type == ValueType::DOUBLE || topValue.type == ValueType::LONG) {
        top_frame->pop_operand_stack();
    } else {
        switch (fieldDescriptor[0]) {
        case 'B':
            topValue.type = ValueType::BYTE;
            topValue.print_type = ValueType::BYTE;
            break;
        case 'C':
            topValue.type = ValueType::CHAR;
            topValue.type = ValueType::CHAR;
            break;
        case 'S':
            topValue.type = ValueType::SHORT;
            topValue.type = ValueType::SHORT;
            break;
        case 'Z':
            topValue.type = ValueType::BOOLEAN;
            topValue.type = ValueType::BOOLEAN;
            break;
        }
    }
    class_runtime->insert_value(topValue, fieldName);
    top_frame->pc += 3;
}

void Operations::getfield()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t fieldIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo fieldCP = constant_pool[fieldIndex - 1];
    assert(fieldCP.tag == ConstFieldRef);
    ConstFieldRefInfo fieldRef = fieldCP.info.field_ref_info;
    string className = get_formatted_constant(constant_pool, fieldRef.class_index);
    ConstantPoolInfo nameAndTypeCP = constant_pool[fieldRef.name_and_type_index - 1];
    assert(nameAndTypeCP.tag == ConstNameType);
    ConstNameTypeInfo fieldNameAndType = nameAndTypeCP.info.name_type_info;
    string fieldName = get_formatted_constant(constant_pool, fieldNameAndType.name_index);
    string fieldDescriptor = get_formatted_constant(constant_pool, fieldNameAndType.descriptor_index);
    Value objectValue = top_frame->pop_operand_stack();
    assert(objectValue.type == ValueType::REFERENCE);
    Object* object = objectValue.data.object;
    assert(object->object_type() == ObjectType::CLASS_INSTANCE);
    InstanceClass* classInstance = (InstanceClass*)object;
    if (!classInstance->check_field(fieldName)) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }
    Value fieldValue = classInstance->get_value(fieldName);
    switch (fieldValue.type) {
    case ValueType::BOOLEAN:
        fieldValue.type = ValueType::INT;
        fieldValue.print_type = ValueType::BOOLEAN;
        break;
    case ValueType::BYTE:
        fieldValue.type = ValueType::INT;
        fieldValue.print_type = ValueType::BYTE;
        break;
    case ValueType::SHORT:
        fieldValue.type = ValueType::INT;
        fieldValue.print_type = ValueType::SHORT;
        break;
    case ValueType::INT:
        fieldValue.type = ValueType::INT;
        fieldValue.print_type = ValueType::INT;
        break;
    default:
        break;
    }
    if (fieldValue.type == ValueType::DOUBLE || fieldValue.type == ValueType::LONG) {
        Value paddingValue = {
            .print_type = ValueType::PADDING,
            .type = ValueType::PADDING
        };
        top_frame->push_operand_stack(paddingValue);
    }
    top_frame->push_operand_stack(fieldValue);
    top_frame->pc += 3;
}

void Operations::putfield()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t fieldIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo fieldCP = constant_pool[fieldIndex - 1];
    assert(fieldCP.tag == ConstFieldRef);
    ConstFieldRefInfo fieldRef = fieldCP.info.field_ref_info;
    string className = get_formatted_constant(constant_pool, fieldRef.class_index);
    ConstantPoolInfo nameAndTypeCP = constant_pool[fieldRef.name_and_type_index - 1];
    assert(nameAndTypeCP.tag == ConstNameType);
    ConstNameTypeInfo fieldNameAndType = nameAndTypeCP.info.name_type_info;
    string fieldName = get_formatted_constant(constant_pool, fieldNameAndType.name_index);
    string fieldDescriptor = get_formatted_constant(constant_pool, fieldNameAndType.descriptor_index);
    Value valueToBeInserted = top_frame->pop_operand_stack();
    if (valueToBeInserted.type == ValueType::DOUBLE || valueToBeInserted.type == ValueType::LONG) {
        top_frame->pop_operand_stack();
    } else {
        switch (fieldDescriptor[0]) {
        case 'B':
            valueToBeInserted.type = ValueType::BYTE;
            valueToBeInserted.print_type = ValueType::BYTE;
            break;
        case 'C':
            valueToBeInserted.type = ValueType::CHAR;
            valueToBeInserted.print_type = ValueType::CHAR;
            break;
        case 'S':
            valueToBeInserted.type = ValueType::SHORT;
            valueToBeInserted.print_type = ValueType::SHORT;
            break;
        case 'Z':
            valueToBeInserted.type = ValueType::BOOLEAN;
            valueToBeInserted.print_type = ValueType::BOOLEAN;
            break;
        }
    }
    Value objectValue = top_frame->pop_operand_stack();
    assert(objectValue.type == ValueType::REFERENCE);
    Object* object = objectValue.data.object;
    assert(object->object_type() == ObjectType::CLASS_INSTANCE);
    InstanceClass* classInstance = (InstanceClass*)object;
    classInstance->insert_value(valueToBeInserted, fieldName);
    top_frame->pc += 3;
}

void Operations::invokevirtual()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    stack<Value> operandStackBackup = top_frame->copy_operand_stack();
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t methodIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo methodCP = constant_pool[methodIndex - 1];
    assert(methodCP.tag == ConstMethodRef);
    ConstMethodRefInfo methodInfo = methodCP.info.method_ref_info;
    string className = get_formatted_constant(constant_pool, methodInfo.class_index);
    ConstantPoolInfo nameAndTypeCP = constant_pool[methodInfo.name_and_type_index - 1];
    assert(nameAndTypeCP.tag == ConstNameType);
    ConstNameTypeInfo methodNameAndType = nameAndTypeCP.info.name_type_info;
    string method_name = get_formatted_constant(constant_pool, methodNameAndType.name_index);
    string methodDescriptor = get_formatted_constant(constant_pool, methodNameAndType.descriptor_index);
    if (className.find("java/") != string::npos) {

        if (className == "java/io/PrintStream" && (method_name == "print" || method_name == "println")) {
            if (methodDescriptor != "()V") {
                Value printValue = top_frame->pop_operand_stack();
                if (printValue.type == ValueType::INT) {
                    switch (printValue.print_type) {
                    case ValueType::BOOLEAN:
                        cout << (printValue.data.boolean_value == 0 ? "false" : "true");
                        break;
                    case ValueType::BYTE:
                        cout << (int)printValue.data.byte_value;
                        break;
                    case ValueType::CHAR:
                        cout << printValue.data.char_value;
                        break;
                    case ValueType::SHORT:
                        cout << printValue.data.short_value;
                        break;
                    default:
                        cout << printValue.data.int_value;
                        break;
                    }
                } else {
                    switch (printValue.type) {
                    case ValueType::DOUBLE:
                        top_frame->pop_operand_stack();
                        cout << printValue.data.double_value;
                        break;
                    case ValueType::FLOAT:
                        cout << printValue.data.float_value;
                        break;
                    case ValueType::LONG:
                        top_frame->pop_operand_stack();
                        cout << printValue.data.long_value;
                        break;
                    case ValueType::REFERENCE:
                        assert(printValue.data.object->object_type() == ObjectType::STRING_INSTANCE);
                        cout << ((StrObject*)printValue.data.object)->get_str().c_str();
                        break;
                    case ValueType::BOOLEAN:
                        cout << (printValue.data.boolean_value == 0 ? "false" : "true");
                        break;
                    case ValueType::BYTE:
                        cout << (int)printValue.data.byte_value;
                        break;
                    case ValueType::CHAR:
                        cout << printValue.data.char_value;
                        break;
                    case ValueType::SHORT:
                        cout << printValue.data.short_value;
                        break;
                    default:
                        cerr << "Invalid print type:" << printValue.type << endl;
                        exit(1);
                        break;
                    }
                }
            }
            if (method_name == "println")
                cout << "\n";
        } else if (className == "java/lang/String" && method_name == "equals") {
            Value strValue1 = top_frame->pop_operand_stack();
            Value strValue2 = top_frame->pop_operand_stack();
            assert(strValue1.type == ValueType::REFERENCE);
            assert(strValue2.type == ValueType::REFERENCE);
            assert(strValue1.data.object->object_type() == ObjectType::STRING_INSTANCE);
            assert(strValue2.data.object->object_type() == ObjectType::STRING_INSTANCE);
            StrObject* str1 = (StrObject*)strValue1.data.object;
            StrObject* str2 = (StrObject*)strValue2.data.object;
            Value result = {
                .print_type = ValueType::INT,
                .type = ValueType::INT,
            };
            if (str1->get_str() == str2->get_str()) {
                result.data.int_value = 1;
            } else {
                result.data.int_value = 0;
            }
            top_frame->push_operand_stack(result);
        } else if (className == "java/lang/String" && method_name == "length") {
            Value strValue = top_frame->pop_operand_stack();
            assert(strValue.type == ValueType::REFERENCE);
            assert(strValue.data.object->object_type() == ObjectType::STRING_INSTANCE);
            StrObject* str = (StrObject*)strValue.data.object;
            Value result = {
                .print_type = ValueType::INT,
                .type = ValueType::INT,
                .data = { .int_value = (int32_t)(str->get_str()).size() }
            };
            top_frame->push_operand_stack(result);
        } else {
            cerr << "Call to invalid instance method: " << method_name << endl;
            exit(1);
        }
    } else {
        uint16_t nargs = 0;
        uint16_t i = 1;
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';')
                    ;
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[')
                    ;
                if (methodDescriptor[i] == 'L')
                    while (methodDescriptor[++i] != ';')
                        ;
            } else {
                nargs++;
            }
            i++;
        }
        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = top_frame->pop_operand_stack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value);
            } else {
                args.insert(args.begin(), value);
            }
        }
        Value objectValue = top_frame->pop_operand_stack();
        assert(objectValue.type == ValueType::REFERENCE);
        args.insert(args.begin(), objectValue);
        Object* object = objectValue.data.object;
        assert(object->object_type() == ObjectType::CLASS_INSTANCE);
        InstanceClass* instance = (InstanceClass*)object;
        MethodArea& methodArea = MethodArea::get_instance();
        StaticClass* class_runtime = methodArea.load_class(className);
        Frame* newFrame = new Frame(instance, class_runtime, method_name, methodDescriptor, args);

        if (stack_frame.get_top_frame() != top_frame) {
            top_frame->load_operand_stack(operandStackBackup);
            delete newFrame;
            return;
        }
        stack_frame.push_frame(newFrame);
    }
    top_frame->pc += 3;
}


void Operations::invokespecial()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    stack<Value> operandStackBackup = top_frame->copy_operand_stack();
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t methodIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo methodCP = constant_pool[methodIndex - 1];
    assert(methodCP.tag == ConstMethodRef);
    ConstMethodRefInfo methodInfo = methodCP.info.method_ref_info;
    string className = get_formatted_constant(constant_pool, methodInfo.class_index);
    ConstantPoolInfo nameAndTypeCP = constant_pool[methodInfo.name_and_type_index - 1];
    assert(nameAndTypeCP.tag == ConstNameType);
    ConstNameTypeInfo methodNameAndType = nameAndTypeCP.info.name_type_info;
    string method_name = get_formatted_constant(constant_pool, methodNameAndType.name_index);
    string methodDescriptor = get_formatted_constant(constant_pool, methodNameAndType.descriptor_index);

    if ((className == "java/lang/Object" || className == "java/lang/String") && method_name == "<init>") {
        if (className == "java/lang/String") {
            top_frame->pop_operand_stack();
        }
        top_frame->pc += 3;
        return;
    }

    if (className.find("java/") != string::npos) {
        cerr << "Call to invalid special method: " << method_name << endl;
        exit(1);
    } else {
        uint16_t nargs = 0;
        uint16_t i = 1;
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';')
                    ;
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[')
                    ;
                if (methodDescriptor[i] == 'L')
                    while (methodDescriptor[++i] != ';')
                        ;
            } else {
                nargs++;
            }
            i++;
        }
        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = top_frame->pop_operand_stack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value);
            } else {
                args.insert(args.begin(), value);
            }
        }
        Value objectValue = top_frame->pop_operand_stack();
        assert(objectValue.type == ValueType::REFERENCE);
        args.insert(args.begin(), objectValue);
        Object* object = objectValue.data.object;
        assert(object->object_type() == ObjectType::CLASS_INSTANCE);
        InstanceClass* instance = (InstanceClass*)object;
        MethodArea& methodArea = MethodArea::get_instance();
        StaticClass* class_runtime = methodArea.load_class(className);
        Frame* newFrame = new Frame(instance, class_runtime, method_name, methodDescriptor, args);

        if (stack_frame.get_top_frame() != top_frame) {
            top_frame->load_operand_stack(operandStackBackup);
            delete newFrame;
            return;
        }
        stack_frame.push_frame(newFrame);
    }
    top_frame->pc += 3;
}

void Operations::invokestatic()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    stack<Value> operandStackBackup = top_frame->copy_operand_stack();
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t methodIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo methodCP = constant_pool[methodIndex - 1];
    assert(methodCP.tag == ConstMethodRef);
    ConstMethodRefInfo methodInfo = methodCP.info.method_ref_info;
    string className = get_formatted_constant(constant_pool, methodInfo.class_index);
    ConstantPoolInfo nameAndTypeCP = constant_pool[methodInfo.name_and_type_index - 1];
    assert(nameAndTypeCP.tag == ConstNameType);
    ConstNameTypeInfo methodNameAndType = nameAndTypeCP.info.name_type_info;
    string method_name = get_formatted_constant(constant_pool, methodNameAndType.name_index);
    string methodDescriptor = get_formatted_constant(constant_pool, methodNameAndType.descriptor_index);
    if (className == "java/lang/Object" && method_name == "registerNatives") {
        top_frame->pc += 3;
        return;
    }
    if (className.find("java/") != string::npos) {
        cerr << "Call to invalid static method: " << method_name << endl;
        exit(1);
    } else {
        uint16_t nargs = 0;
        uint16_t i = 1;
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';')
                    ;
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[')
                    ;
                if (methodDescriptor[i] == 'L')
                    while (methodDescriptor[++i] != ';')
                        ;
            } else {
                nargs++;
            }
            i++;
        }
        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = top_frame->pop_operand_stack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value);
            } else {
                args.insert(args.begin(), value);
            }
        }
        MethodArea& methodArea = MethodArea::get_instance();
        StaticClass* class_runtime = methodArea.load_class(className);
        Frame* newFrame = new Frame(class_runtime, method_name, methodDescriptor, args);

        if (stack_frame.get_top_frame() != top_frame) {
            top_frame->load_operand_stack(operandStackBackup);
            delete newFrame;
            return;
        }
        stack_frame.push_frame(newFrame);
    }
    top_frame->pc += 3;
}

void Operations::invokeinterface()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    stack<Value> operandStackBackup = top_frame->copy_operand_stack();
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t methodIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo methodCP = constant_pool[methodIndex - 1];
    assert(methodCP.tag == ConstMethodRef || methodCP.tag == ConstInterfaceMethodRef);
    ConstMethodRefInfo methodInfo = methodCP.info.method_ref_info;
    string className = get_formatted_constant(constant_pool, methodInfo.class_index);
    ConstantPoolInfo nameAndTypeCP = constant_pool[methodInfo.name_and_type_index - 1];
    assert(nameAndTypeCP.tag == ConstNameType);
    ConstNameTypeInfo methodNameAndType = nameAndTypeCP.info.name_type_info;
    string method_name = get_formatted_constant(constant_pool, methodNameAndType.name_index);
    string methodDescriptor = get_formatted_constant(constant_pool, methodNameAndType.descriptor_index);
    if (className.find("java/") != string::npos) {
        cerr << "Call to invalid interface method: " << method_name << endl;
        exit(1);
    } else {
        uint16_t nargs = 0;
        uint16_t i = 1;
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';')
                    ;
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[')
                    ;
                if (methodDescriptor[i] == 'L')
                    while (methodDescriptor[++i] != ';')
                        ;
            } else {
                nargs++;
            }
            i++;
        }
        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = top_frame->pop_operand_stack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value);
            } else {
                args.insert(args.begin(), value);
            }
        }
        Value objectValue = top_frame->pop_operand_stack();
        assert(objectValue.type == ValueType::REFERENCE);
        args.insert(args.begin(), objectValue);
        Object* object = objectValue.data.object;
        assert(object->object_type() == ObjectType::CLASS_INSTANCE);
        InstanceClass* instance = (InstanceClass*)object;
        MethodArea& methodArea = MethodArea::get_instance();
        methodArea.load_class(className);
        Frame* newFrame = new Frame(instance, instance->get_class_runtime(), method_name, methodDescriptor, args);

        if (stack_frame.get_top_frame() != top_frame) {
            top_frame->load_operand_stack(operandStackBackup);
            delete newFrame;
            return;
        }
        stack_frame.push_frame(newFrame);
    }
    top_frame->pc += 5;
}

void Operations::func_new()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t classIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo classCP = constant_pool[classIndex - 1];
    assert(classCP.tag == ConstClass);
    ConstClassInfo classInfo = classCP.info.class_info;
    string className = get_formatted_constant(constant_pool, classInfo.name_index);
    Object* object;
    if (className == "java/lang/String") {
        object = new StrObject();
    } else {
        MethodArea& methodArea = MethodArea::get_instance();
        StaticClass* class_runtime = methodArea.load_class(className);
        object = new InstanceClass(class_runtime);
    }

    Value objectref = {
        .print_type = ValueType::REFERENCE,
        .type = ValueType::REFERENCE,
        .data = { .object = object }
    };
    top_frame->push_operand_stack(objectref);
    top_frame->pc += 3;
}

void Operations::newarray()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value count = top_frame->pop_operand_stack();
    assert(count.type == ValueType::INT);
    if (count.data.int_value < 0) {
        cerr << "NegativeArraySizeException" << endl;
        exit(1);
    }
    Array* array = nullptr;
    Value value;
    value.data.long_value = 0;
    u1* code = top_frame->get_code(top_frame->pc);
    switch (code[1]) {
    case 4:
        array = new Array(ValueType::BOOLEAN);
        value = {
            .print_type = ValueType::BOOLEAN,
            .type = ValueType::BOOLEAN
        };
        for (int i = 0; i < count.data.int_value; i++) {
            array->push_value(value);
        }
        break;
    case 5:
        array = new Array(ValueType::CHAR);
        value = {
            .print_type = ValueType::CHAR,
            .type = ValueType::CHAR
        };
        for (int i = 0; i < count.data.int_value; i++) {
            array->push_value(value);
        }
        break;
    case 6:
        array = new Array(ValueType::FLOAT);
        value = {
            .print_type = ValueType::FLOAT,
            .type = ValueType::FLOAT
        };
        for (int i = 0; i < count.data.int_value; i++) {
            array->push_value(value);
        }
        break;
    case 7:
        array = new Array(ValueType::DOUBLE);
        value = {
            .print_type = ValueType::DOUBLE,
            .type = ValueType::DOUBLE
        };
        for (int i = 0; i < count.data.int_value; i++) {
            array->push_value(value);
        }
        break;
    case 8:
        array = new Array(ValueType::BYTE);
        value = {
            .print_type = ValueType::BYTE,
            .type = ValueType::BYTE
        };
        for (int i = 0; i < count.data.int_value; i++) {
            array->push_value(value);
        }
        break;
    case 9:
        array = new Array(ValueType::SHORT);
        value = {
            .print_type = ValueType::SHORT,
            .type = ValueType::SHORT
        };
        for (int i = 0; i < count.data.int_value; i++) {
            array->push_value(value);
        }
        break;
    case 10:
        array = new Array(ValueType::INT);
        value = {
            .print_type = ValueType::INT,
            .type = ValueType::INT
        };
        for (int i = 0; i < count.data.int_value; i++) {
            array->push_value(value);
        }
        break;
    case 11:
        array = new Array(ValueType::LONG);
        value = {
            .print_type = ValueType::LONG,
            .type = ValueType::LONG
        };
        for (int i = 0; i < count.data.int_value; i++) {
            array->push_value(value);
        }
        break;
    }
    Value arrayref = {
        .print_type = ValueType::REFERENCE,
        .type = ValueType::REFERENCE,
        .data = { .object = array }
    };
    top_frame->push_operand_stack(arrayref);
    top_frame->pc += 2;
}

void Operations::anewarray()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value count = top_frame->pop_operand_stack();
    assert(count.type == ValueType::INT);
    if (count.data.int_value < 0) {
        cerr << "NegativeArraySizeException" << endl;
        exit(1);
    }
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    uint16_t classIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo classCP = constant_pool[classIndex - 1];
    assert(classCP.tag == ConstClass);
    ConstClassInfo classInfo = classCP.info.class_info;
    string className = get_formatted_constant(constant_pool, classInfo.name_index);
    if (className != "java/lang/String") {
        int i = 0;
        while (className[i] == '[')
            i++;
        if (className[i] == 'L') {
            MethodArea& methodArea = MethodArea::get_instance();
            methodArea.load_class(className.substr(i + 1, className.size() - i - 2));
        }
    }

    Value objectref = {
        .print_type = ValueType::REFERENCE,
        .type = ValueType::REFERENCE,
        .data = { .object = new Array(ValueType::REFERENCE) }
    };

    Value nullValue = {
        .print_type = ValueType::REFERENCE,
        .type = ValueType::REFERENCE,
        .data = { .object = NULL }
    };
    for (int i = 0; i < count.data.int_value; i++) {
        ((Array*)objectref.data.object)->push_value(nullValue);
    }
    top_frame->push_operand_stack(objectref);
    top_frame->pc += 3;
}

void Operations::arraylength()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value arrayref = top_frame->pop_operand_stack();
    assert(arrayref.type == ValueType::REFERENCE);
    if (arrayref.data.object == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    Value length = {
        .print_type = ValueType::INT,
        .type = ValueType::INT,
        .data = { .int_value = (int)((Array*)arrayref.data.object)->get_size() }
    };
    top_frame->push_operand_stack(length);
    top_frame->pc++;
}

void Operations::athrow()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    top_frame->pc++;
}

void Operations::checkcast()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    MethodArea& methodArea = MethodArea::get_instance();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    u2 cpIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    ConstantPoolInfo cpElement = constant_pool[cpIndex - 1];
    assert(cpElement.tag == ConstClass);
    string className = get_formatted_constant(constant_pool, cpIndex);
    Value objectrefValue = top_frame->pop_operand_stack();
    assert(objectrefValue.type == ValueType::REFERENCE);
    Value resultValue = {
        .print_type = ValueType::INT,
        .type = ValueType::INT
    };
    if (objectrefValue.data.object == NULL) {
        cerr << "ClassCastException" << endl;
        exit(1);
    } else {
        Object* obj = objectrefValue.data.object;
        if (obj->object_type() == ObjectType::CLASS_INSTANCE) {
            InstanceClass* classInstance = (InstanceClass*)obj;
            StaticClass* class_runtime = classInstance->get_class_runtime();
            bool found = false;
            while (!found) {
                ClassFile* class_file = class_runtime->get_class_file();
                string currClassName = get_formatted_constant(class_file->constant_pool, class_file->this_class);
                if (currClassName == className) {
                    found = true;
                } else {
                    if (class_file->super_class == 0) {
                        break;
                    } else {
                        string superClassName = get_formatted_constant(class_file->constant_pool, class_file->this_class);
                        class_runtime = methodArea.load_class(superClassName);
                    }
                }
            }
            resultValue.data.int_value = found ? 1 : 0;
        } else if (obj->object_type() == ObjectType::STRING_INSTANCE) {
            resultValue.data.int_value = (className == "java/lang/String" || className == "java/lang/Object") ? 1 : 0;
        } else {
            if (className == "java/lang/Object") {
                resultValue.data.int_value = 1;
            } else {
                resultValue.data.int_value = 0;
            }
        }
    }
    top_frame->push_operand_stack(resultValue);
    top_frame->pc += 3;
}

void Operations::instanceof()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    MethodArea& methodArea = MethodArea::get_instance();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    u2 cpIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    ConstantPoolInfo cpElement = constant_pool[cpIndex - 1];
    assert(cpElement.tag == ConstClass);
    string className = get_formatted_constant(constant_pool, cpIndex);
    Value objectrefValue = top_frame->pop_operand_stack();
    assert(objectrefValue.type == ValueType::REFERENCE);
    Value resultValue = {
        .print_type = ValueType::INT,
        .type = ValueType::INT
    };
    if (objectrefValue.data.object == NULL) {
        resultValue.data.int_value = 0;
    } else {
        Object* obj = objectrefValue.data.object;
        if (obj->object_type() == ObjectType::CLASS_INSTANCE) {
            InstanceClass* classInstance = (InstanceClass*)obj;
            StaticClass* class_runtime = classInstance->get_class_runtime();
            bool found = false;
            while (!found) {
                ClassFile* class_file = class_runtime->get_class_file();
                string currClassName = get_formatted_constant(class_file->constant_pool, class_file->this_class);
                if (currClassName == className) {
                    found = true;
                } else {
                    if (class_file->super_class == 0) {
                        break;
                    } else {
                        string superClassName = get_formatted_constant(class_file->constant_pool, class_file->this_class);
                        class_runtime = methodArea.load_class(superClassName);
                    }
                }
            }
            resultValue.data.int_value = found ? 1 : 0;
        } else if (obj->object_type() == ObjectType::STRING_INSTANCE) {
            resultValue.data.int_value = (className == "java/lang/String" || className == "java/lang/Object") ? 1 : 0;
        } else {
            if (className == "java/lang/Object") {
                resultValue.data.int_value = 1;
            } else {
                resultValue.data.int_value = 0;
            }
        }
    }
    top_frame->push_operand_stack(resultValue);
    top_frame->pc += 3;
}

void Operations::monitorenter()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    top_frame->pc++;
}

void Operations::monitorexit()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    top_frame->pc++;
}

void Operations::wide()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    is_wide = true;
    top_frame->pc++;
}

void Operations::multianewarray()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    ConstantPoolInfo* constant_pool = *(top_frame->get_constant_pool());
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    u1 dimensions = code[3];
    assert(dimensions >= 1);
    uint16_t classIndex = (byte1 << 8) | byte2;
    ConstantPoolInfo classCP = constant_pool[classIndex - 1];
    assert(classCP.tag == ConstClass);
    ConstClassInfo classInfo = classCP.info.class_info;
    string className = get_formatted_constant(constant_pool, classInfo.name_index);

    ValueType value_type;
    int i = 0;
    while (className[i] == '[')
        i++;
    string multiArrayType = className.substr(i + 1, className.size() - i - 2);
    switch (className[i]) {
    case 'L':
        if (multiArrayType != "java/lang/String") {
            MethodArea& methodArea = MethodArea::get_instance();
            methodArea.load_class(multiArrayType);
        }
        value_type = ValueType::REFERENCE;
        break;
    case 'B':
        value_type = ValueType::BYTE;
        break;
    case 'C':
        value_type = ValueType::CHAR;
        break;
    case 'D':
        value_type = ValueType::DOUBLE;
        break;
    case 'F':
        value_type = ValueType::FLOAT;
        break;
    case 'I':
        value_type = ValueType::INT;
        break;
    case 'J':
        value_type = ValueType::LONG;
        break;
    case 'S':
        value_type = ValueType::SHORT;
        break;
    case 'Z':
        value_type = ValueType::BOOLEAN;
        break;
    default:
        cerr << "Invalid descriptor in multianewarray" << endl;
        exit(1);
    }
    stack<int> count;
    for (int i = 0; i < dimensions; i++) {
        Value dimLength = top_frame->pop_operand_stack();
        assert(dimLength.type == ValueType::INT);
        count.push(dimLength.data.int_value);
    }
    Array* array = new Array((dimensions > 1) ? ValueType::REFERENCE : value_type);
    populateMultiarray(array, value_type, count);
    Value arrayValue = {
        .print_type = ValueType::REFERENCE,
        .type = ValueType::REFERENCE,
        .data = { .object = array }
    };
    top_frame->push_operand_stack(arrayValue);
    top_frame->pc += 4;
}

void Operations::ifnull()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value referenceValue = top_frame->pop_operand_stack();
    assert(referenceValue.type == ValueType::REFERENCE);
    if (referenceValue.data.object == NULL) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branch = (byte1 << 8) | byte2;
        top_frame->pc += branch;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::ifnonnull()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    Value referenceValue = top_frame->pop_operand_stack();
    assert(referenceValue.type == ValueType::REFERENCE);
    if (referenceValue.data.object != NULL) {
        u1* code = top_frame->get_code(top_frame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branch = (byte1 << 8) | byte2;
        top_frame->pc += branch;
    } else {
        top_frame->pc += 3;
    }
}

void Operations::goto_w()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    u1 byte3 = code[3];
    u1 byte4 = code[4];
    int32_t branchOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
    top_frame->pc += branchOffset;
}

void Operations::jsr_w()
{
    Stack& stack_frame = Stack::get_instance();
    Frame* top_frame = stack_frame.get_top_frame();
    u1* code = top_frame->get_code(top_frame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    u1 byte3 = code[3];
    u1 byte4 = code[4];
    int32_t branchOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
    Value returnAddr = { 
        .print_type = ValueType::RETURN_ADDR, 
        .type = ValueType::RETURN_ADDR, 
        .data = { .return_address = top_frame->pc + 5 }};
    top_frame->push_operand_stack(returnAddr);
    top_frame->pc += branchOffset;
    assert((int32_t)top_frame->pc < (int32_t)top_frame->get_code_size());
}

void Operations::initInstructions()
{
    generic_functions_arr[0x00] = &Operations::nop;
    generic_functions_arr[0x01] = &Operations::aconst_null;
    generic_functions_arr[0x02] = &Operations::iconst_m1;
    generic_functions_arr[0x03] = &Operations::iconst_0;
    generic_functions_arr[0x04] = &Operations::iconst_1;
    generic_functions_arr[0x05] = &Operations::iconst_2;
    generic_functions_arr[0x06] = &Operations::iconst_3;
    generic_functions_arr[0x07] = &Operations::iconst_4;
    generic_functions_arr[0x08] = &Operations::iconst_5;
    generic_functions_arr[0x09] = &Operations::lconst_0;
    generic_functions_arr[0x0a] = &Operations::lconst_1;
    generic_functions_arr[0x0b] = &Operations::fconst_0;
    generic_functions_arr[0x0c] = &Operations::fconst_1;
    generic_functions_arr[0x0d] = &Operations::fconst_2;
    generic_functions_arr[0x0e] = &Operations::dconst_0;
    generic_functions_arr[0x0f] = &Operations::dconst_1;
    generic_functions_arr[0x10] = &Operations::bipush;
    generic_functions_arr[0x11] = &Operations::sipush;
    generic_functions_arr[0x12] = &Operations::ldc;
    generic_functions_arr[0x13] = &Operations::ldc_w;
    generic_functions_arr[0x14] = &Operations::ldc2_w;
    generic_functions_arr[0x15] = &Operations::iload;
    generic_functions_arr[0x16] = &Operations::lload;
    generic_functions_arr[0x17] = &Operations::fload;
    generic_functions_arr[0x18] = &Operations::dload;
    generic_functions_arr[0x19] = &Operations::aload;
    generic_functions_arr[0x1a] = &Operations::iload_0;
    generic_functions_arr[0x1b] = &Operations::iload_1;
    generic_functions_arr[0x1c] = &Operations::iload_2;
    generic_functions_arr[0x1d] = &Operations::iload_3;
    generic_functions_arr[0x1e] = &Operations::lload_0;
    generic_functions_arr[0x1f] = &Operations::lload_1;
    generic_functions_arr[0x20] = &Operations::lload_2;
    generic_functions_arr[0x21] = &Operations::lload_3;
    generic_functions_arr[0x22] = &Operations::fload_0;
    generic_functions_arr[0x23] = &Operations::fload_1;
    generic_functions_arr[0x24] = &Operations::fload_2;
    generic_functions_arr[0x25] = &Operations::fload_3;
    generic_functions_arr[0x26] = &Operations::dload_0;
    generic_functions_arr[0x27] = &Operations::dload_1;
    generic_functions_arr[0x28] = &Operations::dload_2;
    generic_functions_arr[0x29] = &Operations::dload_3;
    generic_functions_arr[0x2a] = &Operations::aload_0;
    generic_functions_arr[0x2b] = &Operations::aload_1;
    generic_functions_arr[0x2c] = &Operations::aload_2;
    generic_functions_arr[0x2d] = &Operations::aload_3;
    generic_functions_arr[0x2e] = &Operations::iaload;
    generic_functions_arr[0x2f] = &Operations::laload;
    generic_functions_arr[0x30] = &Operations::faload;
    generic_functions_arr[0x31] = &Operations::daload;
    generic_functions_arr[0x32] = &Operations::aaload;
    generic_functions_arr[0x33] = &Operations::baload;
    generic_functions_arr[0x34] = &Operations::caload;
    generic_functions_arr[0x35] = &Operations::saload;
    generic_functions_arr[0x36] = &Operations::istore;
    generic_functions_arr[0x37] = &Operations::lstore;
    generic_functions_arr[0x38] = &Operations::fstore;
    generic_functions_arr[0x39] = &Operations::dstore;
    generic_functions_arr[0x3a] = &Operations::astore;
    generic_functions_arr[0x3b] = &Operations::istore_0;
    generic_functions_arr[0x3c] = &Operations::istore_1;
    generic_functions_arr[0x3d] = &Operations::istore_2;
    generic_functions_arr[0x3e] = &Operations::istore_3;
    generic_functions_arr[0x3f] = &Operations::lstore_0;
    generic_functions_arr[0x40] = &Operations::lstore_1;
    generic_functions_arr[0x41] = &Operations::lstore_2;
    generic_functions_arr[0x42] = &Operations::lstore_3;
    generic_functions_arr[0x43] = &Operations::fstore_0;
    generic_functions_arr[0x44] = &Operations::fstore_1;
    generic_functions_arr[0x45] = &Operations::fstore_2;
    generic_functions_arr[0x46] = &Operations::fstore_3;
    generic_functions_arr[0x47] = &Operations::dstore_0;
    generic_functions_arr[0x48] = &Operations::dstore_1;
    generic_functions_arr[0x49] = &Operations::dstore_2;
    generic_functions_arr[0x4a] = &Operations::dstore_3;
    generic_functions_arr[0x4b] = &Operations::astore_0;
    generic_functions_arr[0x4c] = &Operations::astore_1;
    generic_functions_arr[0x4d] = &Operations::astore_2;
    generic_functions_arr[0x4e] = &Operations::astore_3;
    generic_functions_arr[0x4f] = &Operations::iastore;
    generic_functions_arr[0x50] = &Operations::lastore;
    generic_functions_arr[0x51] = &Operations::fastore;
    generic_functions_arr[0x52] = &Operations::dastore;
    generic_functions_arr[0x53] = &Operations::aastore;
    generic_functions_arr[0x54] = &Operations::bastore;
    generic_functions_arr[0x55] = &Operations::castore;
    generic_functions_arr[0x56] = &Operations::sastore;
    generic_functions_arr[0x57] = &Operations::pop;
    generic_functions_arr[0x58] = &Operations::pop2;
    generic_functions_arr[0x59] = &Operations::dup;
    generic_functions_arr[0x5a] = &Operations::dup2_x1;
    generic_functions_arr[0x5b] = &Operations::dup2_x2;
    generic_functions_arr[0x5c] = &Operations::dup2;
    generic_functions_arr[0x5d] = &Operations::dup2_x1;
    generic_functions_arr[0x5e] = &Operations::dup2_x2;
    generic_functions_arr[0x5f] = &Operations::swap;
    generic_functions_arr[0x60] = &Operations::iadd;
    generic_functions_arr[0x61] = &Operations::ladd;
    generic_functions_arr[0x62] = &Operations::fadd;
    generic_functions_arr[0x63] = &Operations::dadd;
    generic_functions_arr[0x64] = &Operations::isub;
    generic_functions_arr[0x65] = &Operations::lsub;
    generic_functions_arr[0x66] = &Operations::fsub;
    generic_functions_arr[0x67] = &Operations::dsub;
    generic_functions_arr[0x68] = &Operations::imul;
    generic_functions_arr[0x69] = &Operations::lmul;
    generic_functions_arr[0x6a] = &Operations::fmul;
    generic_functions_arr[0x6b] = &Operations::dmul;
    generic_functions_arr[0x6c] = &Operations::idiv;
    generic_functions_arr[0x6d] = &Operations::ldiv;
    generic_functions_arr[0x6e] = &Operations::fdiv;
    generic_functions_arr[0x6f] = &Operations::ddiv;
    generic_functions_arr[0x70] = &Operations::irem;
    generic_functions_arr[0x71] = &Operations::lrem;
    generic_functions_arr[0x72] = &Operations::frem;
    generic_functions_arr[0x73] = &Operations::drem;
    generic_functions_arr[0x74] = &Operations::ineg;
    generic_functions_arr[0x75] = &Operations::lneg;
    generic_functions_arr[0x76] = &Operations::fneg;
    generic_functions_arr[0x77] = &Operations::dneg;
    generic_functions_arr[0x78] = &Operations::ishl;
    generic_functions_arr[0x79] = &Operations::lshl;
    generic_functions_arr[0x7a] = &Operations::ishr;
    generic_functions_arr[0x7b] = &Operations::lshr;
    generic_functions_arr[0x7c] = &Operations::iushr;
    generic_functions_arr[0x7d] = &Operations::lushr;
    generic_functions_arr[0x7e] = &Operations::iand;
    generic_functions_arr[0x7f] = &Operations::land;
    generic_functions_arr[0x80] = &Operations::ior;
    generic_functions_arr[0x81] = &Operations::lor;
    generic_functions_arr[0x82] = &Operations::ixor;
    generic_functions_arr[0x83] = &Operations::lxor;
    generic_functions_arr[0x84] = &Operations::iinc;
    generic_functions_arr[0x85] = &Operations::i2l;
    generic_functions_arr[0x86] = &Operations::i2f;
    generic_functions_arr[0x87] = &Operations::i2d;
    generic_functions_arr[0x88] = &Operations::l2i;
    generic_functions_arr[0x89] = &Operations::l2f;
    generic_functions_arr[0x8a] = &Operations::l2d;
    generic_functions_arr[0x8b] = &Operations::f2i;
    generic_functions_arr[0x8c] = &Operations::f2l;
    generic_functions_arr[0x8d] = &Operations::f2d;
    generic_functions_arr[0x8e] = &Operations::d2i;
    generic_functions_arr[0x8f] = &Operations::d2l;
    generic_functions_arr[0x90] = &Operations::d2f;
    generic_functions_arr[0x91] = &Operations::i2b;
    generic_functions_arr[0x92] = &Operations::i2c;
    generic_functions_arr[0x93] = &Operations::i2s;
    generic_functions_arr[0x94] = &Operations::lcmp;
    generic_functions_arr[0x95] = &Operations::fcmpl;
    generic_functions_arr[0x96] = &Operations::fcmpg;
    generic_functions_arr[0x97] = &Operations::dcmpl;
    generic_functions_arr[0x98] = &Operations::dcmpg;
    generic_functions_arr[0x99] = &Operations::ifeq;
    generic_functions_arr[0x9a] = &Operations::ifne;
    generic_functions_arr[0x9b] = &Operations::iflt;
    generic_functions_arr[0x9c] = &Operations::ifge;
    generic_functions_arr[0x9d] = &Operations::ifgt;
    generic_functions_arr[0x9e] = &Operations::ifle;
    generic_functions_arr[0x9f] = &Operations::if_icmpeq;
    generic_functions_arr[0xa0] = &Operations::if_icmpne;
    generic_functions_arr[0xa1] = &Operations::if_icmplt;
    generic_functions_arr[0xa2] = &Operations::if_icmpge;
    generic_functions_arr[0xa3] = &Operations::if_icmpgt;
    generic_functions_arr[0xa4] = &Operations::if_icmple;
    generic_functions_arr[0xa5] = &Operations::if_acmpeq;
    generic_functions_arr[0xa6] = &Operations::if_acmpne;
    generic_functions_arr[0xa7] = &Operations::func_goto;
    generic_functions_arr[0xa8] = &Operations::jsr;
    generic_functions_arr[0xa9] = &Operations::ret;
    generic_functions_arr[0xaa] = &Operations::tableswitch;
    generic_functions_arr[0xab] = &Operations::lookupswitch;
    generic_functions_arr[0xac] = &Operations::ireturn;
    generic_functions_arr[0xad] = &Operations::lreturn;
    generic_functions_arr[0xae] = &Operations::freturn;
    generic_functions_arr[0xaf] = &Operations::dreturn;
    generic_functions_arr[0xb0] = &Operations::areturn;
    generic_functions_arr[0xb1] = &Operations::func_return;
    generic_functions_arr[0xb2] = &Operations::getstatic;
    generic_functions_arr[0xb3] = &Operations::putstatic;
    generic_functions_arr[0xb4] = &Operations::getfield;
    generic_functions_arr[0xb5] = &Operations::putfield;
    generic_functions_arr[0xb6] = &Operations::invokevirtual;
    generic_functions_arr[0xb7] = &Operations::invokespecial;
    generic_functions_arr[0xb8] = &Operations::invokestatic;
    generic_functions_arr[0xb9] = &Operations::invokeinterface;
    generic_functions_arr[0xbb] = &Operations::func_new;
    generic_functions_arr[0xbc] = &Operations::newarray;
    generic_functions_arr[0xbd] = &Operations::anewarray;
    generic_functions_arr[0xbe] = &Operations::arraylength;
    generic_functions_arr[0xbf] = &Operations::athrow;
    generic_functions_arr[0xc0] = &Operations::checkcast;
    generic_functions_arr[0xc1] = &Operations::instanceof;
    generic_functions_arr[0xc2] = &Operations::monitorenter;
    generic_functions_arr[0xc3] = &Operations::monitorexit;
    generic_functions_arr[0xc4] = &Operations::wide;
    generic_functions_arr[0xc5] = &Operations::multianewarray;
    generic_functions_arr[0xc6] = &Operations::ifnull;
    generic_functions_arr[0xc7] = &Operations::ifnonnull;
    generic_functions_arr[0xc8] = &Operations::goto_w;
    generic_functions_arr[0xc9] = &Operations::jsr_w;
}
