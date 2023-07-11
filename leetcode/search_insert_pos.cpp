#include <iostream>

// https://leetcode.com/problems/search-insert-position/solutions/15101/c-o-logn-binary-search-that-handles-duplicate/

// Given a sorted array of distinct integers and a target value, return the index if the target is found.
// If not, return the index where it would be if it were inserted in order.

// You must write an algorithm with O(log n) runtime complexity.

// Input: nums = [1,3,5,6], target = 5
// Output: 2

// If there are duplicate elements equal to target, my code will always return the one with smallest index.
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int low = 0, high = nums.size()-1;

        // Invariant: the desired index is between [low, high+1]
        while (low <= high) {
            int mid = low + (high-low)/2;

            if (nums[mid] < target)
                low = mid+1;
            else
                high = mid-1;
        }

        // (1) At this point, low > high. That is, low >= high+1
        // (2) From the invariant, we know that the index is between [low, high+1], so low <= high+1. Follwing from (1), now we know low == high+1.
        // (3) Following from (2), the index is between [low, high+1] = [low, low], which means that low is the desired index
        //     Therefore, we return low as the answer. You can also return high+1 as the result, since low == high+1
        return low;
    }
	
	// OR:
	int searchInsertV2(vector<int>& nums, int target) {
        return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    }
};

int main()
{
	return 0;
}

/**
Java version:

https://leetcode.com/problems/search-insert-position/solutions/249092/come-on-forget-the-binary-search-pattern-template-try-understand-it/

class Solution {
	public int searchInsert(int[] nums, int target) {
		if(nums == null || nums.length == 0) return 0;
		
		int n = nums.length;
		int l = 0;
		int r = n - 1;
		while(l < r){
			int m = l + (r - l)/2;
			
			if(nums[m] == target) return m;
			else if(nums[m] > target) r = m; // right could be the result
			else l = m + 1; // m + 1 could be the result
		}
		
		// 1 element left at the end
		// post-processing
		return nums[l] < target ? l + 1: l;
	}
}

TC(Time Complexity): O(logn)
SC(Space Complexity): O(1)

*/