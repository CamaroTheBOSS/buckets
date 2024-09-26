#include "bucket.h"
#include <algorithm>

Bucket::Bucket(int capacity): _capacity(capacity) {}

int Bucket::getWaterAmount() const {
	return _waterAmount;
}

int Bucket::getCapacity() const {
	return _capacity;
}

bool Bucket::hasWater() const {
	return _waterAmount > 0;
}

std::string Bucket::toString() const {
	return "bucket " + std::to_string(_capacity) + "l";
}

void Bucket::makeFilled() {
	_waterAmount = _capacity;
}

int Bucket::makeEmpty() {
	int remainingWater = _waterAmount;
	_waterAmount = 0;
	return remainingWater;
}

bool Bucket::operator>(const Bucket& other) const {
	return _capacity > other._capacity;
}

Bucket& Bucket::operator=(const Bucket& other) {
	_capacity = other._capacity;
	_waterAmount = other._waterAmount;
	return *this;
}

int Bucket::transferToBucket(Bucket& other) {
	int transferAmount = std::min(other.getCapacity() - other.getWaterAmount(), _waterAmount);
	other._waterAmount += transferAmount;
	_waterAmount -= transferAmount;
	return transferAmount;
}
