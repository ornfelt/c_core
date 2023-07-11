#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// https://leetcode.com/problems/median-of-two-sorted-arrays/solutions/2471/very-concise-o-log-min-m-n-iterative-solution-with-detailed-explanation/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int N1 = nums1.size();
        int N2 = nums2.size();
        if (N1 < N2) return findMedianSortedArrays(nums2, nums1);	// Make sure A2 is the shorter one.
        
        int lo = 0, hi = N2 * 2;
        while (lo <= hi) {
            int mid2 = (lo + hi) / 2;   // Try Cut 2 
            int mid1 = N1 + N2 - mid2;  // Calculate Cut 1 accordingly
            
            double L1 = (mid1 == 0) ? INT_MIN : nums1[(mid1-1)/2];	// Get L1, R1, L2, R2 respectively
            double L2 = (mid2 == 0) ? INT_MIN : nums2[(mid2-1)/2];
            double R1 = (mid1 == N1 * 2) ? INT_MAX : nums1[(mid1)/2];
            double R2 = (mid2 == N2 * 2) ? INT_MAX : nums2[(mid2)/2];
            
            if (L1 > R2) lo = mid2 + 1;		// A1's lower half is too big; need to move C1 left (C2 right)
            else if (L2 > R1) hi = mid2 - 1;	// A2's lower half too big; need to move C2 left.
            else return (max(L1,L2) + min(R1, R2)) / 2;	// Otherwise, that's the right cut.
        }
        return -1;
    }
};

int main()
{
	// https://www.geeksforgeeks.org/initialize-a-vector-in-cpp-different-ways/
	vector<int> firstVect{1, 2, 3};
	vector<int> secVect{4, 5, 6};
    // Create a vector of size n with all values as 10.
    vector<int> tenVect(2, 10);
    vector<int> twentyVect(3, 20);

	Solution s;
	double res = s.findMedianSortedArrays(firstVect, secVect);
	cout << "Res: " << res << endl;

	res = s.findMedianSortedArrays(tenVect, twentyVect);
	cout << "Res: " << res << endl;

	// Input: nums1 = [1,3], nums2 = [2]
	// Output: 2.00000
	firstVect = vector<int>{1, 3};
	secVect = vector<int>{2};
	res = s.findMedianSortedArrays(firstVect, secVect);
	cout << "Res: " << res << endl;

	// Input: nums1 = [1,2], nums2 = [3,4]
	// Output: 2.50000
	firstVect = vector<int>{1, 2};
	secVect = vector<int>{3, 4};
	res = s.findMedianSortedArrays(firstVect, secVect);
	cout << "Res: " << res << endl;

	return 0;
}
