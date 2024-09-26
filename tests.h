#pragma once
#include <iostream>
#include <random>
#include "assert.h"
#include "bucket.h"
#include "operator.h"

void print(const std::vector<std::string>& instructions) {
	for (int i = 0; i < instructions.size(); i++) {
		std::cout << std::to_string(i + 1) + ". " << instructions[i] << "\n";
	}
}

void sameBucketTransferTest() {
	Bucket firstBucket{ 3 };
	Bucket secondBucket{ 3 };
	firstBucket.makeFilled();
	assert(firstBucket.getWaterAmount() == 3);
	assert(firstBucket.transferToBucket(secondBucket) == 3);
	assert(firstBucket.getWaterAmount() == 0);
	assert(secondBucket.getWaterAmount() == 3);
	assert(secondBucket.makeEmpty() == 3);
	assert(secondBucket.getWaterAmount() == 0);
}

void biggerBucketTransferTest() {
	Bucket firstBucket{ 3 };
	Bucket secondBucket{ 4 };
	firstBucket.makeFilled();
	assert(firstBucket.getWaterAmount() == 3);
	assert(firstBucket.transferToBucket(secondBucket) == 3);
	assert(firstBucket.getWaterAmount() == 0);
	assert(secondBucket.getWaterAmount() == 3);
	assert(secondBucket.makeEmpty() == 3);
	assert(secondBucket.getWaterAmount() == 0);
}

void smallerBucketTransferTest() {
	Bucket firstBucket{ 4 };
	Bucket secondBucket{ 3 };
	firstBucket.makeFilled();
	assert(firstBucket.getWaterAmount() == 4);
	assert(firstBucket.transferToBucket(secondBucket) == 3);
	assert(firstBucket.getWaterAmount() == 1);
	assert(secondBucket.getWaterAmount() == 3);
	assert(secondBucket.makeEmpty() == 3);
	assert(secondBucket.getWaterAmount() == 0);
}

void bucketTests() {
	sameBucketTransferTest();
	biggerBucketTransferTest();
	smallerBucketTransferTest();
}

void taskTest(const std::vector<Bucket>& buckets, const int targetLiter) {
	std::string taskHeader = "BUCKET SIZES: [";
	for (const auto& bucket : buckets) {
		taskHeader += std::to_string(bucket.getCapacity()) + ",";
	}
	taskHeader += "], TARGET LITERS TO FILL: " + std::to_string(targetLiter);
	Operator op{buckets};
	std::cout << taskHeader << "\n";
	print(op.getInstructions(targetLiter));
	std::cout << "\n\n";

}

void mainTaskTest() {
	for (int i = 1; i <= 19; i++) {
		std::vector<Bucket> buckets{Bucket(3), Bucket(6), Bucket(10)};
		taskTest(buckets, i);
	}
}

void randomTaskTest() {
	std::random_device device;
	std::mt19937 mt(device());
	std::uniform_int_distribution<int> getVectorSize(3, 18);
	std::uniform_int_distribution<int> getCapacity(1, 100);
	std::uniform_int_distribution<int> getTargetLiters(100, 200);
	std::vector<Bucket> buckets{};
	for (int i = 0; i < getVectorSize(mt); i++) {
		buckets.emplace_back(Bucket{ getCapacity(mt)});
	}
	taskTest(buckets, getTargetLiters(mt));
}
