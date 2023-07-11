# Approach 1: Recursive
# This is a classic tree problem that is best-suited for a recursive approach.
# https://leetcode.com/problems/invert-binary-tree/solutions/127840/invert-binary-tree/

# Since each node in the tree is visited only once, the time complexity is O(n)
# where n is the number of nodes in the tree.
# We cannot do better than that, since at the very least we have to visit each node to invert it.

# Because of recursion, O(h) function calls will be placed on the stack in the worst case,
# where h is the height of the tree. The space complexity is O(n).
class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None
        
        right = self.invertTree(root.right)
        left = self.invertTree(root.left)
        root.left = right
        root.right = left
        return root
        
# Iterative solution
# Also O(n) time and space complexity...
class IterativeSolution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None
        
        queue = collections.deque([root])
        while queue:
            current = queue.popleft()
            current.left, current.right = current.right, current.left
            
            if current.left:
                queue.append(current.left)
            
            if current.right:
                queue.append(current.right)
        
        return root
     