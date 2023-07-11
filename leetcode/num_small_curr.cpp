#include <iostream>
#include <vector>

// https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/solutions/693600/c-99-o-n/

// Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it.
// That is,
// for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].

/**
	Input: nums = [8,1,2,2,3]
	Output: [4,0,1,1,3]
	Explanation: 
	For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3). 
	For nums[1]=1 does not exist any smaller number than it.
	For nums[2]=2 there exist one smaller number than it (1). 
	For nums[3]=2 there exist one smaller number than it (1). 
	For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).
*/

// Solution below is in O(n)

using namespace std;

class Solution {
public:
	vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int> answer;
        int i, j;
        int count[101] = {0, 0, 0};
		int len = nums.size();
		// Added all the numbers of nums array to their respective index position
		// ex. if nums[i]=80, you increment value of count array by 1 at index (80-1)
        for(i = 0; i < len; i++) {
            count[nums[i]]++;
        }
		
		// Incrementing and reassigning values based on previous counts element
		// ex. if there are 4 small values than 9th element. You want to add count to the 10th, 
		// and continue adding till the 100th element because constrait is 0 <= nums[i] <= 100
        for(i = 1; i < 101; i++) {
            count[i] += count[i - 1];
        }
		
		// Simply pushing back the value computed above
        for(i = 0; i < len; i++) {
            if(nums[i] == 0)
                answer.push_back(0);
            else
                answer.push_back(count[nums[i] - 1]);
                
        }
        return answer;
    }
	
	// "A lil more simplified and optimised c++ solution"
	vector<int> smallerNumbersThanCurrentV2(vector<int>& nums) {
        int n = nums.size();
        int bucket[102] = {0};
        for(auto i:nums){
            bucket[i+1]++;
        }
        for(int i=1;i<102;i++){
            bucket[i] += bucket[i-1];
        }
        for(int i=0;i<n;i++){
            nums[i] = bucket[nums[i]];
        }
        return nums;
    }
};


int main()
{
	return 0;
}
