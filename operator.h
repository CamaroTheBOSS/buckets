#pragma once
#include <vector>
#include <string>
#include <map>

#include "bucket.h"

class Operator {
public:
	enum class Step { makeFilled, makeEmpty, transferFromTo };
	struct StepWithArgs {
		Step stepType;
		Bucket* first;
		Bucket* second;
	};

	using Instructions = std::vector<std::string>;
	using BasicStepsMap = std::map<int, std::vector<StepWithArgs>>;

	Operator(std::vector<Bucket> initBuckets);
	Instructions getInstructions(const int liters);
private:
	std::string makeStep(const StepWithArgs& stepArgs);
	std::string makeFilled(Bucket& bucket);
	std::string makeEmpty(Bucket& bucket);
	std::string transferFromTo(Bucket& first, Bucket& second);
	std::string getBucketStatesStr(Bucket& targetBucket) const;

	BasicStepsMap getBasicStepsMap(Bucket& targetBucket);

	std::vector<Bucket> buckets{Bucket{ 3 }, Bucket{ 6 }, Bucket{ 10 }};
};