#include "operator.h"
#include <assert.h>
#include <exception>
#include <algorithm>
#include <queue>

Operator::Operator(std::vector<Bucket> initBuckets) {

	std::sort(initBuckets.begin(), initBuckets.end(), std::greater<Bucket>());
	buckets = std::move(initBuckets);
}


Operator::BasicStepsMap Operator::getBasicStepsMap(Bucket& targetBucket) {
	// Step where map is fulfilled with possible delta liters
	std::queue<int> queue;
	BasicStepsMap stepsMap;
	for (auto& bucket : buckets) {
		if (bucket.getCapacity() == 0) {
			continue;
		}
		queue.push(bucket.getCapacity());
		std::vector<StepWithArgs> steps{};
		steps.emplace_back(StepWithArgs{ Step::makeFilled, &bucket, nullptr });
		auto [it, newOne] = stepsMap.try_emplace(bucket.getCapacity(), steps);
		if (!newOne && it->second.size() > steps.size()) {
			it->second = steps;
		}
	}
	while (!queue.empty()) {
		int parentCap = queue.front();
		queue.pop();
		for (auto& diffBucket : buckets) {
			int childCap = parentCap - diffBucket.getCapacity();
			if (stepsMap.find(childCap) != stepsMap.end() || childCap <= 0) {
				continue;
			}
			auto parentIt = stepsMap.find(parentCap);
			if (parentIt == stepsMap.end()) {
				continue;
			}
			std::vector<StepWithArgs> steps = parentIt->second;
			steps.emplace_back(StepWithArgs{ Step::makeEmpty, &diffBucket, nullptr });
			steps.emplace_back(StepWithArgs{ Step::transferFromTo, steps[steps.size() - 2].first, &diffBucket });
			auto [it, newOne] = stepsMap.try_emplace(childCap, steps);
			if (!newOne && it->second.size() > steps.size()) {
				it->second = steps;
			}
			queue.push(childCap);
		}
	}
	return stepsMap;
}


Operator::Instructions Operator::getInstructions(const int targetLiters) {
	Bucket targetBucket{ INT_MAX };
	Instructions instructions;
	BasicStepsMap stepsMap = getBasicStepsMap(targetBucket);
	int neededWater = targetLiters - targetBucket.getWaterAmount();
	if (stepsMap.empty()) {
		auto fulfillmedLog = std::to_string(targetBucket.getWaterAmount()) + "\\" + std::to_string(targetLiters);
		instructions.emplace_back("SOLUTION DOES NOT EXISTS! FILLED only " + fulfillmedLog);
		return instructions;
	}
	// Pushing instructions
	while (neededWater > 0) {
		for (auto stepsIt = stepsMap.rbegin(); stepsIt != stepsMap.rend(); stepsIt++) {
			if (stepsIt->first > neededWater) {
				continue;
			}
			for (const auto& step : stepsIt->second) {
				auto instruction = makeStep(step);
				if (!instruction.empty()) {
					instruction += "\n" + getBucketStatesStr(targetBucket);
					instructions.emplace_back(instruction);
				}
			}
			auto lastBucket = stepsIt->second[stepsIt->second.size() - 1].first;
			auto instruction = transferFromTo(*lastBucket, targetBucket);
			instruction += "\n" + getBucketStatesStr(targetBucket);
			instructions.emplace_back(instruction);
			neededWater = targetLiters - targetBucket.getWaterAmount();
		}
		if (neededWater > 0 && neededWater < stepsMap.begin()->first) {
			auto fulfillmedLog = std::to_string(targetBucket.getWaterAmount()) + "\\" + std::to_string(targetLiters);
			instructions.emplace_back("SOLUTION DOES NOT EXISTS! FILLED only " + fulfillmedLog);
			break;
		}
	}
	return instructions;
}

std::string Operator::makeStep(const StepWithArgs& stepArgs) {
	if (stepArgs.stepType == Step::makeFilled) {
		return makeFilled(*stepArgs.first);
	} else if (stepArgs.stepType == Step::makeEmpty) {
		return makeEmpty(*stepArgs.first);
	} else if (stepArgs.stepType == Step::transferFromTo) {
		return transferFromTo(*stepArgs.first, *stepArgs.second);
	}
	return "Empty step";
}

std::string Operator::makeFilled(Bucket& bucket) {
	bucket.makeFilled();
	return "Fill " + bucket.toString();
}
std::string Operator::makeEmpty(Bucket& bucket) {
	bool hadWater = bucket.makeEmpty();
	return hadWater ? "Make empty " + bucket.toString() : "";
}
std::string Operator::transferFromTo(Bucket& first, Bucket& second) {
	int transfered = first.transferToBucket(second);
	return "Transfer all water from " + first.toString() + " to " + second.toString();
}

std::string Operator::getBucketStatesStr(Bucket& targetBucket) const {
	std::string state = "     bucket states: ";
	for (const auto& bucket : buckets) {
		state += std::to_string(bucket.getWaterAmount()) + "\\" + std::to_string(bucket.getCapacity()) + "  ";
	}
	state += "TARGET BUCKET: " + std::to_string(targetBucket.getWaterAmount()) + "\\" + std::to_string(targetBucket.getCapacity());
	return state;
}
