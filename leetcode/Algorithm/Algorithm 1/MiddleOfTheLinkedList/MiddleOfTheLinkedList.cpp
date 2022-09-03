class Solution 
{
public:
    ListNode* middleNode(ListNode* head)
    {
        std::vector<ListNode*> temp;

        ListNode* temper = head;

        while (temper != nullptr)
        {
            temp.push_back(temper);
            temper = temper->next;
        }

        return temp[temp.size() / 2];
    }
};