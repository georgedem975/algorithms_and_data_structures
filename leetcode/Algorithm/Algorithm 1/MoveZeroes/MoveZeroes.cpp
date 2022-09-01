class Solution 
{
public:
    void moveZeroes(vector<int>& nums) 
    {
        int i = 0, j = 0;
        int pos = 0;
        
        for (; i < nums.size(); i++)
        {
            if (nums[i] == 0)
            {
                pos++;
                continue;
            }
            
            nums[j] = nums[i];
            j++;
        }
        
        pos = nums.size() - pos;
        
        for (; pos < nums.size(); pos++)
        {
            nums[pos] = 0;
        }
    }
};