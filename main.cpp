#include "bucket.h"
#include "tests.h"

/*
LICENSE: MIT
TESTED ON WINDOWS MVSC (required C++17 or newer)
README:
--- Filling bath with capacity from range <1, 19> with buckets with capacities [10, 6, 3] ---
0. Program will print instructions in order to get specific target liters, by filling/emptying/transfering buckets,
   It will print states of the buckets and TARGET BUCKET which has capacity=INT_MAX=2147483647
1. I've followed OOP rules to make code expandable and reusable, 
   so we have Bucket class and Operator class which is operating buckets
2. I've prepared simple unit tests in bucketTests() function
3. Algorithm is optimal for given constrains: buckets [10, 6, 3] liters <1, 19>
4. It can be tested via mainTaskTest()
5. I had fun with this, so I tried to implement algorithm for any 
   number of buckets with any capacities (in some range obviously)
7. It can be tested via randomTaskTest()
8. To solve this problem for any conditions required to build a tree, which will contain information 
   about all delta liters, which can be achieved by just filling/transfering/emptying given buckets, 
   together with sequences of steps which leads to specific delta liter
9. Example of the tree for our buckets [10, 6, 3] case
							|-----------------ROOT-------------------|
					  |-----10-----|	    |--6--|		             3
				 |--7(-3)--|     4(-6)    3(-3)  0(-6)             0(-3)
               4(-3)     1(-6)   1(-3)    0(-3)
			   1(-3)
10. So possible delta liters to create are [10, 7, 6, 4, 3, 1]
11. For example steps to reproduce delta liter 1 -> fill 10 -> transfer to 6 -> trasnfer to 3
12. And such tree is built with std::map datastructure where key is delta liter and value are steps to get
    specific delta liter. Map is canonical what means that keys are not repeated (prefered are these with 
    less steps -> higher in the tree)
13. Map was choosen, because after fulfilling it with delta liters, whole algorithm is just taking sequence
    of steps with highest possible delta liter smaller than neededWater (it's just iterating from end to begin of the map)
12. It's not perfect, might be hard to expand, but it's good prototype or just proof of concept
*/


int main() {
	bucketTests();
	mainTaskTest();
	randomTaskTest();
}