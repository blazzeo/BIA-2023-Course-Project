#include "Parm.h"
#include "../Error/Error.h"
#include <cstring>
#include "cstring"

static void file_name(char* dst, const char* src, const char* ext) {
    if (strlen(src) + strlen(ext) >= PARM_MAX_SIZE) throw ERROR_THROW(104);
    strcpy(dst, src);
    strncat(dst,ext, strlen(ext));
}

namespace Parm {
PARM getparm(int argc, char* argv[]) {
    bool parm_in = false;
    bool parm_out = false;
    bool parm_log = false;

    PARM parm;

    for(int i=0;i<argc;++i) {
        if (strlen(argv[i]) >= PARM_MAX_SIZE) throw ERROR_THROW(104);

        if (std::strstr(argv[i], PARM_IN) == argv[i]
            && strlen(PARM_IN) < strlen(argv[i])) {
            parm_in = true;
            parm.in[0] = L'\0';
            strcat(parm.in,  argv[i] + strlen(PARM_IN));
        }
        else if (std::strstr(argv[i], PARM_OUT) == argv[i]
            && strlen(PARM_OUT) < strlen(argv[i])) {
            parm_out = true;
            parm.out[0] = L'\0';
            std::strcat(parm.out,  argv[i] + std::strlen(PARM_OUT));
        }
        else if (std::strstr(argv[i], PARM_LOG) == argv[i]
            && strlen(PARM_LOG) < strlen(argv[i])) {
            parm_log = true;
            parm.log[0] = L'\0';
            std::strcat(parm.log,  argv[i] + std::strlen(PARM_LOG));
        }
    }
    if (!parm_in) throw ERROR_THROW(100);

    if (!parm_out)
        file_name(parm.out, parm.in, PARM_OUT_DEFAULT_EXT);

    if (!parm_log)
        file_name(parm.log, parm.in, PARM_LOG_DEFAULT_EXT); 

    return parm;
}
};
