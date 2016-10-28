// Build-switch, code is added automatically based on the target OS

#if defined(__linux__)
    #include "Serial/Serial-unix.cpp"
    #include "Serial/Serial_List-linux.cpp"
#elif defined(__APPLE__)
    #include "Serial/Serial-unix.cpp"
    #include "Serial/Serial_List-mac.cpp"
#elif defined(_WIN32)
    #include "Serial/Serial-win.cpp"
    #include "Serial/Serial_List-win.cpp"
#endif
