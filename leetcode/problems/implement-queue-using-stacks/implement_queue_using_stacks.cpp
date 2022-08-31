#include <iostream>
#include <stack>

class MyQueue 
{
    public:
        MyQueue() 
        {
            
        }
    
        void push(int x) 
        {
            pushStack.push(x);
        }
    
        int pop() 
        {
            if (popStack.empty())
            {
                this->rearrangement();
            }
            int elem = popStack.top();
            popStack.pop();
            return elem;
        }
    
        int peek() 
        {
            if (popStack.empty())
            {
                this->rearrangement();
            }
            int elem = popStack.top();
            return elem;
        }
    
        bool empty() 
        {
            return (popStack.empty() && pushStack.empty());
        }
    
    private:
        void rearrangement()
        {
            while(!pushStack.empty())
                {
                    popStack.push(pushStack.top());
                    pushStack.pop();
                }
        }
    
        std::stack<int> pushStack;
        std::stack<int> popStack;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */