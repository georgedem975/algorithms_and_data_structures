class Solution
{
public:
    int search(std::vector<int>& nums, int target)
    {

        if (nums.size() == 0)
        {
            return -1;
        }
        if (nums.size() == 1)
        {
            if (nums[0] == target)
            {
                return 0;
            }
            return -1;
        }

        int leftPosition = 0, rightPosition = nums.size() - 1;
        int mid = (rightPosition + leftPosition) / 2;

        while(leftPosition != rightPosition - 1)
        {
            if (nums[mid] > target)
            {
                rightPosition = mid;
            }
            else if (nums[mid] < target)
            {
                leftPosition = mid;
            }
            else
            {
                return mid;
            }

            mid = (rightPosition + leftPosition) / 2;
        }
        if (nums[rightPosition] == target)
        {
            return rightPosition;
        }
        if (nums[leftPosition] == target)
        {
            return leftPosition;
        }
        return -1;
    }
};