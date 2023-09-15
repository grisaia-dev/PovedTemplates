#include <iostream>
#include "lib/logger.hpp"

void print(LogCommand& log) {
    log.print("Halo!");
}

int main(void) {
    LogInConsole logT;
    LogInFile logF("log.txt");

    print(logT);
    print(logF);
    return EXIT_SUCCESS;
}