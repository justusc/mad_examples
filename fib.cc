/*
 *
 *  Copyright (C) 2013  Virginia Tech
 *  See the file license.txt for copying permission.
 *
 *  Justus Calvin
 *  Department of Chemistry, Virginia Tech
 *
 *  fib.cc
 *  Sep 20, 2013
 *
 */

#include <iostream>
#include <world/world.h>

long serial_fib(long n) {
  if( n<2 )
    return n;
  else
    return serial_fib(n - 1) + serial_fib(n - 2);
}

long sum(long left, long right) {
  return left + right;
}

madness::Future<long> task_fib(madness::World* world,
    long n, const long cutoff) {
  if(n < cutoff ) {
    return madness::Future<long>(serial_fib(n));
  } else {
    madness::Future<long> x =
        world->taskq.add(& task_fib, world, n - 1,
            cutoff, madness::TaskAttributes::hipri());
    madness::Future<long> y = task_fib(world, n - 2, cutoff);

    return world->taskq.add(& sum, x, y,
        madness::TaskAttributes::hipri());
  }
}

long nth = 46;

int main(int argc, char** argv) {
  
  madness::World& world = madness::initialize(argc,argv);

  // Serial calculation
  const double serial_start = madness::wall_time();
  long fib1 = serial_fib(nth);
  const double serial_time = madness::wall_time() - serial_start;
  std::cout << nth << "-th Fibonacci is " << fib1 << "\n";

  std::cout << "Serial time = " << serial_time << "\n";

  // Parallel calculation
  const double parallel_start = madness::wall_time();
  madness::Future<long> fib2 = task_fib(& world, nth, 30);
  fib2.get();
  const double parallel_time = madness::wall_time() - parallel_start;

  std::cout << "Parallel time = " << parallel_time
      << "\nSpeedup = " << serial_time / parallel_time << "\n";

  madness::finalize();
  return 0;
}
