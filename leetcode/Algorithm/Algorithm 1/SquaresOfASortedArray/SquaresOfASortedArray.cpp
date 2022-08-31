class Solution 
{
    public:
        std::vector<int> sortedSquares(std::vector<int>& nums) 
        {
            if (nums[nums.size() - 1] <= 0)
            {
                std::vector<int> temp;
                for (int i = nums.size() - 1; i >= 0; i--)
                {
                    temp.push_back(nums[i] * nums[i]);
                }
                return temp;
            }
            if (nums[0] >= 0)
            {
                std::vector<int> temp;
                for (int i = 0; i < nums.size(); i++)
                {
                    temp.push_back(nums[i] * nums[i]);
                }
                return temp;
            }

            int pos = 0;
            while (!(nums[pos] < 0 && nums[pos + 1] >= 0))
            {
                pos++;
            }

            int right = pos + 1, left = pos;
            std::vector<int> temp;
            
            if (nums.size() <= 4)
            {
                for (int i = 0; i < nums.size(); i++)
                {
                    temp.push_back(nums[i] * nums[i]);
                }
                
                std::sort(temp.begin(), temp.end());
                return temp;
            }
            

            while (left > 0 && right < nums.size() - 1)
            {
                if (nums[left] * -1 < nums[right])
                {
                    temp.push_back(nums[left] * nums[left]);
                    left--;
                }
                if (nums[left] * -1 >= nums[right])
                {
                    temp.push_back(nums[right] * nums[right]);
                    right++;
                }
            }

            while (left >= 0)
            {
                temp.push_back(nums[left] * nums[left]);
                left--;
            }

            while(right <= nums.size() - 1)
            {
                temp.push_back(nums[right] * nums[right]);
                right++;
            }
            
            std::sort(temp.begin(), temp.end());

            return temp;
        }
};