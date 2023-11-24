#include "Parm.h"
#include "../Error/Error.h"
#include <cwchar>
#include <wchar.h>
#include "cstring"
#include <iostream>

static void file_name(wchar_t* dst, const wchar_t* src, const wchar_t* ext) {
    if (wcslen(src) + wcslen(ext) >= PARM_MAX_SIZE) throw ERROR_THROW(104);
    wcscpy(dst, src);
    wcsncat(dst,ext, wcslen(ext));
}

namespace Parm {
PARM getparm(int argc, wchar_t* argv[]) {
    bool parm_in = false;
    bool parm_out = false;
    bool parm_log = false;

    PARM parm;

    for(int i=0;i<argc;++i) {
        if (wcslen(argv[i]) >= PARM_MAX_SIZE) throw ERROR_THROW(104);

        if (std::wcsstr(argv[i], PARM_IN) == argv[i]
            && wcslen(PARM_IN) < wcslen(argv[i])) {
            parm_in = true;
            parm.in[0] = L'\0';
            std::wcscat(parm.in,  argv[i] + std::wcslen(PARM_IN));
        }
        else if (std::wcsstr(argv[i], PARM_OUT) == argv[i]
            && wcslen(PARM_OUT) < wcslen(argv[i])) {
            parm_out = true;
            parm.out[0] = L'\0';
            std::wcscat(parm.out,  argv[i] + std::wcslen(PARM_OUT));
        }
        else if (std::wcsstr(argv[i], PARM_LOG) == argv[i]
            && wcslen(PARM_LOG) < wcslen(argv[i])) {
            parm_log = true;
            parm.log[0] = L'\0';
            std::wcscat(parm.log,  argv[i] + std::wcslen(PARM_LOG));
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
