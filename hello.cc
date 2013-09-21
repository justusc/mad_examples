/*
 *
 *  Copyright (C) 2013  Virginia Tech
 *  See the file license.txt for copying permission.
 *
 *  Justus Calvin
 *  Department of Chemistry, Virginia Tech
 *
 *  hello.cc
 *  Sep 20, 2013
 *
 */

#include <iostream>
#include <world/world.h>

int main(int argc, char** argv) {
    madness::World& world = madness::initialize(argc,argv);

    std::cout << "Hello from " << world.rank() << std::endl;

    madness::finalize();
    return 0;
}
