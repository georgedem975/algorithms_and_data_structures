class Solution 
{
public:
    string reverseWords(string s) 
    {
        string answer;
        vector<char> temp;
        for (auto k : s)
        {
            if (k == ' ')
            {
                for (int i = temp.size() - 1; i >= 0; i--)
                {
                    answer.push_back(temp[i]);
                }
                answer.push_back(' ');
                temp.clear();
            }
            else
            {
                temp.push_back(k);
            }
        } 
        
        if (!(temp.empty()))
        {
            for (int i = temp.size() - 1; i >= 0; i--)
            {
                answer.push_back(temp[i]);
            }
        }
        
        return answer;
    }
};