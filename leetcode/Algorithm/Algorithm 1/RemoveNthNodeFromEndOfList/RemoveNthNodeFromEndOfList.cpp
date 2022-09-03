class Solution 
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        std::vector<ListNode*> temp;
        
        while (head != nullptr)
        {
            temp.push_back(head);
            head = head->next;
        }
        
        if (temp.size() - n == 0)
        {
            return temp[0]->next;
        }
        
        temp[temp.size() - n - 1]->next = temp[temp.size() - n - 1]->next->next;
        
        return temp[0];
    }
};