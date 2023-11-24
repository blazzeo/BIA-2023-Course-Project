#include "Log.h"
#include <cstdarg>
#include <cwchar>
#include <cstdlib>
#include "../Error/Error.h"
#include "../WCHAR/WCHAR.h"
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>

namespace Log
{
LOG getlog(wchar_t* w_logfile) {
    char* filename = getCH(w_logfile); 
    LOG log;
    wcscpy(log.logfile, w_logfile);
    //log.logfile = {*logfile};
    log.stream = new std::ofstream(filename);
    if (!log.stream->is_open()) {
        throw ERROR_THROW(112);
    }
    return log;
}

void WriteLine(LOG log, char* c, ...) {
    va_list argv;
    va_start(argv, c);

    size_t size = 0;
    char* pargv = c;
    while (strcmp(pargv,"")) {
        size += strlen(pargv);
        pargv = va_arg(argv, char*);
    }
    va_end(argv);

    char* string = new char[size+1];
    string[0] = '\0';
    va_start(argv, c);
    pargv = c;
    while (strcmp(pargv,"")) {
        strcat(string, pargv);
        pargv = va_arg(argv, char*);
    }
    *log.stream << string;
    log.stream->flush();
    va_end(argv);
    delete []string;
}

void WriteLine(LOG log, wchar_t* c, ...) {
    va_list argv;
    va_start(argv, c);

    size_t size = 0;
    wchar_t* pargv = c;
    while (pargv) {
        size += wcslen(pargv);
        pargv = va_arg(argv, wchar_t*);
    }
    va_end(argv);

    wchar_t* string = new wchar_t[size+1];
    va_start(argv, c);
    pargv = c;
    while (pargv) {
        wcscat(string, pargv);
        pargv = va_arg(argv, wchar_t*);
    }
    *log.stream << getCH(string);
    std::wcout << "result: " << string << " " << wcslen(string) << std::endl;
    log.stream->flush();
    delete []string;
    va_end(argv);
}

void WriteLog(LOG log) {
  std::time_t time = std::time(nullptr);
  char timeString[128];
  std::strftime(timeString, std::size(timeString),
                "%d.%m.%y %T", std::localtime(&time));
  *log.stream << "----\tПротокол\t-----\t" << timeString << "\t----\n";
}

void WriteParm(LOG log, Parm::PARM parm) {
  *log.stream << "----\tПараметры\t-----\n";
    *log.stream << "-in: " << getCH(parm.in) << '\n'
    << "-out: " << getCH(parm.out) << '\n'
    << "-log: " << getCH(parm.log) << '\n';
}

void WriteIn(LOG log, In::IN in) {
  WriteLine(log, (char*)"----\tИсходные данные\t----\n","");
  *log.stream << "всего строк: " << in.lines << std::endl;
  *log.stream << "всего символов: " << in.size << std::endl;
  *log.stream << "всего пропущено: " << in.ignor << std::endl;
}

void WriteError(LOG log, Error::ERROR e) {
  if (log.stream && log.stream->is_open()) {
    *log.stream << "Ошибка " << e.id << ": " << e.message <<
      ", строка " << e.inext.line <<
      ", позиция " << e.inext.col << std::endl << std::endl;
  } else {
    std::cout << "Ошибка " << e.id << ": " << e.message <<
      ", строка " << e.inext.line <<
      ", позиция " << e.inext.col << std::endl << std::endl;
  }
}

void Close(LOG log) {
  log.stream->close();
    delete log.stream;
}
};
