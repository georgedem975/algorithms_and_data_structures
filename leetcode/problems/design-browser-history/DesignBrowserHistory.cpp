#include <vector>

class BrowserHistory
{
public:
    BrowserHistory(string homepage)
    {
        list.push_back(homepage);
        positionInList = 0;
        maxPosition = 1;
    }
    
    void visit(string url)
    {
        if (list.size() > positionInList + 1)
        {
            list[++positionInList] = url;
            maxPosition = positionInList + 1;
            return;
        }
        list.push_back(url);
        positionInList++;
        maxPosition = positionInList + 1;
    }
    
    string back(int steps)
    {
        if (maxPosition <= steps)
        {
            positionInList = 0;
        }
        else
        {
            if (positionInList - steps < 0)
                positionInList = 0;
            else
                positionInList -= steps;
        }
        return list[positionInList];
    }
    
    string forward(int steps)
    {
        if (steps + positionInList >= maxPosition)
        {
            positionInList = maxPosition - 1;
        }
        else
        {
            positionInList += steps;
        }
        
        return list[positionInList];
    }
    
    private:
        int maxPosition;
        int positionInList;
        std::vector<std::string> list;
};