#include "MethodArea.hpp"
#include "ClassFileReader.hpp"
#include "ClassFileViewer.hpp"
#include "Operations.hpp"
#include "Stack.hpp"

MethodArea::MethodArea() {

}

MethodArea::~MethodArea() {

}

StaticClass* MethodArea::load_class(const string &className) {
  // se a classe já tiver sido carregada, retorna-la
  if (classes.count(className) > 0) {
    return get_class(className);
  }

  string classNameStr(className);
  string classLocation(class_path);
  string classFormat(".class");

  if (classNameStr.size() < classFormat.size()
     || classNameStr.compare(classNameStr.size() - classFormat.size(), classFormat.size(), classFormat) != 0) {
    classNameStr = classLocation + classNameStr + classFormat; // concatena com ".class"
  }

  FILE *fp = fopen(classNameStr.c_str(), "rb");
  if (fp == NULL) {
    cerr << "No support for this class: " << className << endl;
    exit(1);
  }

  ClassFileReader &classLoader = ClassFileReader::get_instance();
  ClassFile *classFile = classLoader.read_class_file(fp);
  StaticClass *classRuntime = new StaticClass(classFile);
  insert_class(classRuntime);
  fclose(fp);

  // adicionando <clinit> da classe (se existir) na stack frame.
  Operations &operations = Operations::get_instance();
  bool existsClinit = operations.verifyMethod(classRuntime, "<clinit>", "()V");
  if (existsClinit) {
    Stack &stackFrame = Stack::get_instance();
    Frame *newFrame = new Frame(classRuntime, "<clinit>", "()V");
    stackFrame.push_frame(newFrame);
  }

  return classRuntime;
}

StaticClass* MethodArea::get_class(const string &className) {
  map<string, StaticClass*>::iterator it = classes.find(className);

  if (it == classes.end()) {
    return nullptr;
  }

  return it->second;
}

bool MethodArea::insert_class(StaticClass *classRuntime) {
  ClassFile *classFile = classRuntime->get_class_file();

  const char *key = get_formatted_constant(classFile->constant_pool, classFile->this_class);

  if (classes.count(key) > 0) {
    return false;
  }

  classes[key] = classRuntime;
  return true;
}
