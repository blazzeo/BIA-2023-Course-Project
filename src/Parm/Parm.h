#pragma once
#define PARM_IN "-in:"
#define PARM_OUT  "-out:"
#define PARM_LOG  "-log:"
#define PARM_MAX_SIZE 300
#define PARM_OUT_DEFAULT_EXT ".out"
#define PARM_IN_DEFAULT_EXT  ".in"
#define PARM_LOG_DEFAULT_EXT ".log"

namespace Parm {
  struct PARM {
    char in[PARM_MAX_SIZE];
    char out[PARM_MAX_SIZE];
    char log[PARM_MAX_SIZE];
  };

  PARM getparm(int argc, char* argv[]);
};
