
#include "active_object.h"
#include <chrono>
#include <functional>
#include <iostream>

using namespace std;
using namespace std::chrono;

// We do it like this instead of more standard constructor (Java-like) because
// it is more efficient: we are skipping the default constructor call that would
// happen before the actual initialization
ActiveObject::ActiveObject() : t(&ActiveObject::run, this), quit(false) {}

void ActiveObject::run() {
  while (!quit.load()) {
    cout << "Hello world" << endl;
    this_thread::sleep_for(milliseconds(500));
  }
}

ActiveObject::~ActiveObject() {
  if (quit.load())
    return; // For derived classes
  quit.store(true);
  t.join();
}
