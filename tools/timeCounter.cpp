#include <profileapi.h>
#include "timeCounter.h"

long long int timeCounter::read_QPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}