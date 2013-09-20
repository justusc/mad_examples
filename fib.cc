/*
 *  This file is a part of mad_examples.
 *  Copyright (C) 2013  Virginia Tech
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
  madness::initialize(argc,argv);
  madness::World world(MPI::COMM_WORLD);

  // Serial calculation
  const double serial_start = madness::wall_time();
  long fib1 = serial_fib(nth);
  std::cout << nth << "-th Fibonacci is " << fib1 << "\n";
  const double serial_time = madness::wall_time() - serial_start;

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
