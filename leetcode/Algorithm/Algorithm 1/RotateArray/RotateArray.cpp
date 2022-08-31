class Solution 
{
    public:
        void rotate(vector<int>& nums, int k) 
        {
            vector<int> temp;

            if (nums.size() < k)
            {
                while (k > nums.size())
                {
                    k -= nums.size();
                }
            }

            int pos = nums.size() - k;

            for (int i = pos; i < nums.size(); i++)
            {
                temp.push_back(nums[i]);
            }

            for (int i = 0; i < pos; i++)
            {
                temp.push_back(nums[i]);
            }

            for (int i = 0; i < nums.size(); i++)
            {
                nums[i] = temp[i];
            }
        }
};