
#include "serial.cpp"

#if defined(__linux__)
    #include "impl/list_ports/list_ports_linux.cpp"
    #include "impl/unix.cpp"
#elif defined(__APPLE__)
    #include "impl/list_ports/list_ports_osx.cpp"
    #include "impl/unix.cpp"
#elif defined(_WIN32)
    #include "impl/list_ports/list_ports_win.cpp"
    #include "impl/win.cpp"
#else
    #error Serial| Unsupported platform
#endif
