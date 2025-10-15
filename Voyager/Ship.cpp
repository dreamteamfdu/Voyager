#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Ship {
private:
	float health; // Health value
	const float DEFAULT_HEALTH = 100; // Default Health value
	int fuel; // Fuel value
	const float DEFAULT_FUEL = 100; // Default Fuel value
	float oxygen; // O2 value
	const float DEFAULT_OXYGEN = 100; // Default O2 value
	// Add Ship Storage

public:
	Ship() // default constructor
	{
		health = DEFAULT_HEALTH;
		fuel = DEFAULT_FUEL;
		oxygen = DEFAULT_OXYGEN;
	}

	Ship(float my_health, float my_fuel, float my_oxygen) // not default constructor
	{
		health = my_health;
		fuel = my_fuel;
		oxygen = my_oxygen;
	}
	
	float getHealth() // returns health
	{
		return health;
	}
	float getFuel() // returns fuel
	{
		if (fuel <= DEFAULT_FUEL * 0.5) {
			cout << "WARNING: Fuel Level 50%";
		}
		else if (fuel <= DEFAULT_FUEL * 0.25) {
			cout << "WARNING: Fuel Level 25%";
		}
		else if (fuel <= DEFAULT_FUEL * 0.10) {
			cout << "WARNING: Fuel Level 10%";
		}
		else if (fuel <= DEFAULT_FUEL * 0.05) {
			cout << "WARNING: Fuel Level 5%";
		}
		else if (fuel <= DEFAULT_FUEL * 0.01) {
			cout << "WARNING: Fuel Level 1%";
		}
		else if (fuel <= 0) {
			cout << "WARNING: Fuel Level 0%";
		}
		else cout << "Status: Fuel level at " + to_string(fuel) + "%" << endl;
		return fuel;
	}
	float getOxygen() // returns O2
	{
		return oxygen;
	}
	
	void setHealth(float x) // sets health
	{
		health = x;
		if (health > DEFAULT_HEALTH) {
			health = DEFAULT_HEALTH;
		}
	}
	void setFuel(float x) // sets fuel
	{
		fuel = x;
		if (fuel > DEFAULT_FUEL) {
			fuel = DEFAULT_FUEL;
		}
	}
	void setOxygen(float x) // sets O2
	{
		oxygen = x;
		if (oxygen > DEFAULT_OXYGEN) {
			oxygen = DEFAULT_OXYGEN;
		}
	}
};