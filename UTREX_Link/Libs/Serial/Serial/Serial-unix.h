#pragma once

namespace Serial {

    typedef enum {
        Databits_5 = 5,
        Databits_6 = 6,
        Databits_7 = 7,
        Databits_8 = 8,
        Databits_9 = 9,
    } Databits_t;

    typedef enum {
        Parity_None,
        Parity_Odd,
        Parity_Even,
        Parity_Mark,
        Parity_Space,
    } Parity_t;

    typedef enum {
        Stopbits_1 = 1,
        Stopbits_2 = 2,
    } Stopbits_t;

}
