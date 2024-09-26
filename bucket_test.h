#include "assert.h"
#include "bucket.h"

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