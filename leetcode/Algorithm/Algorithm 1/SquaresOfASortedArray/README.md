### Squares of a Sorted Array

Given an integer array ```nums``` sorted in __non-decreasing__ order, return ___an array of the squares of each number sorted in non-decreasing order___.

 

__Example 1:__

```
Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].
```

__Example 2:__

```
Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
``` 

__Constraints:__

+ ```1 <= nums.length <= 10^4```
+ ```-10^4 <= nums[i] <= 10^4```
+ ```nums``` is sorted in __non-decreasing__ order.
 

__Follow up:__ Squaring each element and sorting the new array is very trivial, could you find an ```O(n)``` solution using a different approach?