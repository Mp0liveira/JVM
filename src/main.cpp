#include "ArgParser.hpp"
#include "ClassFileReader.hpp"
#include "ClassFileViewer.hpp"
#include "StaticClass.hpp"
#include "MethodArea.hpp"
#include "Operations.hpp"
#include "ClassFileUtils.hpp"
#include <stdio.h>
#include <iomanip>

int main(int argc, char* argv[])
{
    cout << std::fixed;
    ClassFileReader& instance = ClassFileReader::get_instance();
    const Parameters params = parse_args(argc, argv);
    if (!validate_parameters(&params))
        return -1;
    FILE* fptr = fopen(params.class_file_path, "rb");
    if (fptr == NULL) {
        cerr << "Could not find file at \"" << params.class_file_path << "\"";
    }
    if (params.execute) {
        // Carregamento da classe de entrada.
        MethodArea &methodArea = MethodArea::get_instance();
        
        // Define a pasta onde estao os .class
        string path = string(params.class_file_path);
        size_t pos = path.find_last_of("/");
        if (pos != string::npos) methodArea.class_path = path.substr(0, pos+1);
        
        StaticClass *classRuntime = methodArea.load_class(params.class_file_path);

        // Verificação se o nome da classe de entrada é igual ao nome do arquivo.
        string className = get_formatted_constant(classRuntime->get_class_file()->constant_pool, classRuntime->get_class_file()->this_class);

        string fileName(params.class_file_path);

        int TamStr = fileName.length(), i;
        for (i = 0; i < TamStr; i++) {                            // Converte cada caracter de Str
            fileName[i] = toupper(fileName[i]);  // para maiusculas
        }

        TamStr = className.length();
        for (i = 0; i < TamStr; i++) {                            // Converte cada caracter de Str
            className[i] = toupper(className[i]);  // para maiusculas
        }
        if (!ClassFileUtils::verify_classfile_name(fileName, className)) {
            cerr << "File name different from class name" << endl;
            exit(1);
        }

        Operations &operations = Operations::get_instance();
        bool existeMain = operations.verifyMethod(classRuntime, "main", "([Ljava/lang/String;)V");

        if (!existeMain) {
         cerr << "The file does not have a main method" << "." << endl;
         exit(2);
        }

        operations.executeMethods(classRuntime);
    } else {
        FILE* outptr = fopen(params.output_file_path, "w+");
        if (outptr == NULL) {
            cerr << "Could not write to output file at \"" << params.output_file_path << "\"";
            return -1;
        }
        ClassFile* cf = instance.read_class_file(fptr);
        write_class_file(cf, outptr);
        fclose(outptr);
    }
    fclose(fptr);
    return 0;
}
