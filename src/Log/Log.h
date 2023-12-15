#pragma once
#include "../In/In.h"
#include "../Parm/Parm.h"
#include "../Error/Error.h"
#include <fstream>

namespace Log 
{
  struct LOG {
    char logfile[PARM_MAX_SIZE];
    std::ofstream* stream;
  };

  static const LOG INITLOG { "", NULL };
  LOG getlog(char logfile[]);
  void WriteLine(LOG log, char* c, ...);
  void WriteLine(LOG log, char*  c, ...);
  void WriteLog(LOG log);
  void WriteParm(LOG log, Parm::PARM parm);
  void WriteIn(LOG log, In::IN in);
  void WriteError(LOG log, Error::ERROR error);
  void Close(LOG log);
};
