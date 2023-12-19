#include "Log.h"
#include <cstdarg>
#include <cwchar>
#include <cstdlib>
#include "../Error/Error.h"
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>

namespace Log
{
LOG getlog(char* logfile) {
    char* filename = logfile; 
    LOG log;
    strcpy(log.logfile, logfile);
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

void WriteLog(LOG log) {
  std::time_t time = std::time(nullptr);
  char timeString[128];
  std::strftime(timeString, std::size(timeString),
                "%d.%m.%y %T", std::localtime(&time));
  *log.stream << "----\tProtocol\t-----\t" << timeString << "\t----\n";
}

void WriteParm(LOG log, Parm::PARM parm) {
  *log.stream << "----\tParametrs\t-----\n";
    *log.stream << "-in: " << parm.in << '\n'
    << "-out: " << parm.out << '\n'
    << "-log: " << parm.log << '\n';
}

void WriteIn(LOG log, In::IN in) {
  WriteLine(log, (char*)"----\tInitial data\t----\n","");
  *log.stream << "Total Lines: " << in.lines << std::endl;
  *log.stream << "Total symbols: " << in.size << std::endl;
  *log.stream << "Total ignored: " << in.ignor << std::endl;
}

void WriteError(LOG log, Error::ERROR e) {
  if (log.stream && log.stream->is_open()) {
    *log.stream << "Error " << e.id << ": " << e.message <<
      ", line " << e.position.line <<
      ", position " << e.position.col << std::endl << std::endl;
  } else {
    std::cout << "Error " << e.id << ": " << e.message <<
      ", line " << e.position.line <<
      ", position " << e.position.col << std::endl << std::endl;
  }
}

void Close(LOG log) {
  log.stream->close();
    delete log.stream;
}
};
