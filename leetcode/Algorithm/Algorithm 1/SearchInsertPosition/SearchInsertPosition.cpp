class Solution 
{
    public:
        int searchInsert(vector<int>& nums, int target) 
        {
            if (nums[nums.size() - 1] < target)
            {
                nums.push_back(target);
                return nums.size() - 1;
            }
            if (nums[0] > target)
            {
                nums.insert(nums.begin(), target);
                return 0;
            }
            
            int left = 0, right = nums.size() - 1;
            int mid = (right + left) / 2;
            
            while (left != right - 1)
            {
                if (nums[mid] > target)
                {
                    right = mid;
                }
                if (nums[mid] < target)
                {
                    left = mid;
                }
                if (nums[mid] == target)
                {
                    return mid;
                }
                mid = (right + left) / 2;
            }
            
            if (nums[left] == target)
            {
                return left;
            }
            if (nums[right] == target)
            {
                return right;
            }
            
            if (nums[left] < target && nums[right] > target)
            {
                nums.insert(nums.begin() + left, target);
                return left + 1;
            }
            
            if (nums[left] > target)
            {
                nums.insert(nums.begin() + left - 1, target);
                return left;
            }
            
            nums.insert(nums.begin() + right, target);
            return right + 1;
            
        }
};