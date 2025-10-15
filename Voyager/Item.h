#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>

using namespace std;

class Item {
private:
	string name; // name of the item
	int count; // how many of the item exists
	const int ITEM_LIMIT = 99; // the max ammount of items you can have
public:
	Item(string n) {
		name = n;
	}
	Item(string n, int c) {
		name = n;
		count = c;
	}
	Item() : name(""), count(0) {}

	Item(const Item& other) : name(other.name), count(other.count) {}

	// Copy Assignment Operator
	Item& operator=(const Item& other) {
		if (this != &other) {  // Self-assignment check
			name = other.name;
			count = other.count;
		}
		return *this;
	}

	string getName() { // get the name of the item 
		return name;
	}
	int getCount() { // get the count of the item
		return count;
	}
	
	void setName(string n) { // sets the name of the item
		name = n;
	}
	void setCount(int c) { // sets the count of the item
		count = c;
		if (count < 0) count = 0;
		else if (count > ITEM_LIMIT) count = ITEM_LIMIT;
	}
	void incrementCount() { // increments the count of the item
		count++;
		if (count > ITEM_LIMIT) {
			count = ITEM_LIMIT;
			cout << "ERROR: Cannot add \"" + name + "\" to your invintory, item limit reached" << endl;
		}
	}
	void decrementCount() { // decrements the count of the item
		count++;
		if (count < 0) {
			count = 0;
			cout << "ERROR: Cannot remove \"" + name + "\" from your invintory, can\'t have less than 0 of an item" << endl;
		}
	}

	// add a generic return type method here
	template <typename T>
	T itemFunction();
};

#endif // !ITEM_H
