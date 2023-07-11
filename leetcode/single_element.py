# https://leetcode.com/problems/single-element-in-a-sorted-array/solutions/627921/java-c-python3-easy-explanation-o-logn-o-1/

class Solution:
    def singleNonDuplicate(self, nums: List[int]) -> int:
        left, right = 0, len(nums)-1
        while left < right:
            mid = int((left + right)/2)
            if (mid % 2 == 1 and nums[mid - 1] == nums[mid]) or (mid%2 == 0 and nums[mid] == nums[mid + 1]):
                left = mid + 1
            else:
                right = mid
        return nums[left]
        
        
"""
Time: -  O(logN)
space:-  O(1)

Java:-
class Solution {
    public int singleNonDuplicate(int[] nums) {
        int left = 0, right = nums.length-1;
        while(left < right){
            int mid = (left + right)/2;
            if( (mid % 2 == 0 && nums[mid] == nums[mid +1]) || (mid %2 == 1 && nums[mid] == nums[mid - 1]) )
                left = mid + 1;
            else
                right = mid;
        }
        return nums[left];
    }   
}

"""