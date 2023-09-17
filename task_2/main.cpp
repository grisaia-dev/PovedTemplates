#include <iostream>
#include "lib/observ.hpp"



int main(void) {
    Observed listener;
    WarningObserver warn;
    ErrorObserver err("log.txt");
    FatalErrorObserver ferr("log1.txt");

    listener.AddObserver(&warn);
    listener.warning("I enter in console!");
    listener.RemoveObserver(&warn);

    listener.AddObserver(&err);
    listener.error("I enter in file!");
    listener.RemoveObserver(&err);

    listener.AddObserver(&ferr);
    listener.fatalError("I enter in file and console!");

    listener.RemoveObserver(&ferr);
    return EXIT_SUCCESS;
}