
#include "BuffRemoval.h"
#include "Buff.h"

#include <iostream>

BuffRemoval::BuffRemoval(Buff* buff, const float timestamp, const int iteration) {
    this->buff = buff;
    this->priority = timestamp;
    this->iteration = iteration;
    this->name = "BuffRemoval";
}

void BuffRemoval::act(void) {
    //std::cout << this->priority << ": BuffRemoval\n";
    buff->remove_buff(iteration);
}
