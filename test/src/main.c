//
// Created by Frityet on 2022-02-01.
//

#include "satellite.h"

int main()
{
    struct satellite s = create_satellite(8123);
    free_satellite(s);
}
