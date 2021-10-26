#include <memory>
#include <iostream>
#include <string>

class Sensor {

public:
	Sensor(int _id, const std::string &_name) : id(_id), name(_name) {
		// ... Any code you need in the constructor goes here ...
		total_sensors++;
	}
	
	virtual ~Sensor() { // destructor
		// Do something in the destructor...
		total_sensors--;
	}
	
	const std::string &get_name() {
		return this->name;	// or this->id
	}
	
	void set_name(const std::string &name) { // const anche qua perchè non modifico name (non obbligatorio ma meglio)
		this->name = name;
	}
	
	int get_id() const; // importante const quando non si modifica nulla

	static int get_nr_sensors() {
		return total_sensors;
	}
	
//	virtual void update() = 0;
	
	virtual const char * get_class_name() const {
		return "Sensor";
	}

protected:
	std::string name;

private:
	int id;
	static int total_sensors;
};

int Sensor::total_sensors = 0;

int Sensor::get_id() const { // importante const quando non si modifica nulla
	return id;	// or this->id
}
void test_function_2(std::shared_ptr<Sensor> sensor) {
	// DO something with sensor
}

void test_function() {
	// "SMART POINTERS" introduced in c++11
	std::shared_ptr<Sensor> s = std::make_shared<Sensor>(123, "test");	// Dynamically allocated
	test_function_2(s);
	s->get_id();
}	// Destroyed here --> when its lifetime ends! Resolves many problems, ex:
/**
Sensor *s1 = new Sensor(..);
delete s1;
some_func(s1); --> will crash if uses s1
*/
// instead, if done like test_function, the object gets deleted in the right place

int main() {

	Sensor *test = new Sensor(123, "test");
	
	// ...
	
	delete test;

	test_function();

	return 0;
}
