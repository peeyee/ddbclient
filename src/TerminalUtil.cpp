#include <cstdlib>
#include <iostream>
#include <sys/ioctl.h>  
#include <unistd.h>       
#include "TerminalUtil.h"



int getTermWidth() {
    if (g_display_width > 0) {
        return g_display_width;
    }

    const char* env_cols = std::getenv("COLUMNS");
    if (env_cols) {
        int w = std::atoi(env_cols);
        if (w > 0) return w;
    }

    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        if (ws.ws_col > 0) {
            return ws.ws_col; // ws.ws_col 就是列数（宽度）
        }
    }

    return 80;
}
