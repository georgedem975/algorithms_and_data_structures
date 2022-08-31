class Solution
{
    public:
        int firstBadVersion(int n)
        {
            if (n == 1)
            {
                return 1;
            }
            
            long long leftPosition = 1, rightPosition = n;
            long long mid;
            if (n == INT_MAX)
            {
                mid = n / 2;
            }
            else
            {
                mid = (n + 1) / 2;
            }

            while (leftPosition != rightPosition - 1)
            {
                if (isBadVersion(mid))
                {
                    rightPosition = mid;
                }
                else
                {
                    leftPosition = mid;
                }
                mid = (long long)(rightPosition + leftPosition) / 2;
            }

            if (isBadVersion(rightPosition) && isBadVersion(leftPosition))
            {
                return leftPosition;
            }
            else if (isBadVersion(rightPosition) && !isBadVersion(leftPosition))
            {
                return rightPosition;
            }
            return leftPosition;
        }
};