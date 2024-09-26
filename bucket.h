#pragma once
#include <string>

class Bucket {
public:
	Bucket(int capacity);
	int getWaterAmount() const;
	int getCapacity() const;
	bool hasWater() const;
	std::string toString() const;

	void makeFilled();
	int makeEmpty();
	int transferToBucket(Bucket& other);
	
	bool operator>(const Bucket& other) const;
	Bucket& operator=(const Bucket& other);
	

private:
	int _capacity;
	int _waterAmount = 0;
};
