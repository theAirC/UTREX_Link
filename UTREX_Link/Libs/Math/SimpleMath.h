#pragma once

#define rounddiv(x,y)    ( ( ( ( (x) << 1 ) / (y) ) + 1 ) >> 1 )
#define upperdiv(x,y)      ( ( ( (x) -  1 ) / (y) ) + 1 )
#define roundmod(x,y)    ( x - (rounddiv(x,y) * y) )
#define uppermod(x,y)    ( x - (upperdiv(x,y) * y) )
//#define uppermod(x,y)      ( ( ( (x) -  1 ) % (y) ) + 1 - (y) )

#define limit(x, m, M)    if ((x) < (m)) x = m; else if ((x) > (M)) x = M
#define limitMin(x, m)    if ((x) < (m)) x = m
#define limitMax(x, M)    if ((x) > (M)) x = M

#define isOdd(x)    ((x) & 1)
#define isEven(x)   !((x) & 1)
