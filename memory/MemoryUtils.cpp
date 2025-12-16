#include "MemoryUtils.h"
#include <iostream>
#include <iomanip>


#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

#else
#include <sys/resource.h>
#include <unistd.h>
#endif

void printMemoryUsageWrapper() {
    std::cout << std::fixed << std::setprecision(2);

#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS memCounter;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter))) {
        size_t bytes = memCounter.WorkingSetSize;
        double kb = bytes / 1024.0;
        double mb = bytes / (1024.0 * 1024.0);
        std::cout << "[Память (Win)] " << kb << " KB (" << mb << " MB)\n";
    }
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        long kb = usage.ru_maxrss; 
        double mb = kb / 1024.0;
        std::cout << "[Память (Linux)] " << kb << " KB (" << mb << " MB)\n";
    }
#endif
}