#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool isEqual(unordered_map<int, int> &mp, unordered_map<int, int> &curMp)
{

    return mp.size() == curMp.size();
}
int countCompleteSubarrays(vector<int> &nums)
{
    int flag = 0, curIndex, numsLength = nums.size(), cnt = 0, headIndex = 0;
    unordered_map<int, int> mp, curMp;
    for (int num : nums)
    {
        if (mp.find(num) == mp.end())
        {
            flag++;
        }
        mp[num]++;
    }
    for (int i = 0; i < flag; i++)
    {
        curMp[nums[i]]++;
    }
    curIndex = flag;
    while (curIndex <= nums.size())
    {
        if (isEqual(mp, curMp))
        {
            cnt += numsLength - curIndex + 1;
            curMp[nums[headIndex]]--;
            headIndex++;
            if (curMp[nums[headIndex - 1]] == 0)
            {
                curMp.erase(nums[headIndex - 1]);
            }
            continue;
        }
        if (curIndex == numsLength)
        {
            break;
        }
        curMp[nums[curIndex]]++;
        curIndex++;
    }
    return cnt;
}
long long countInterestingSubarrays(vector<int> &nums, int modulo, int k)
{
    long long res = 0;
    vector<int> prefixSum = {0}; // 初始化前缀和数组，避免在空数组上调用 back()
    vector<int> cnt(min((int)nums.size() + 1, modulo), 0);
    for (int num : nums)
    {
        prefixSum.push_back(prefixSum.back() + (num % modulo == k ? 1 : 0));
    }
    for (int s : prefixSum)
    {
        if (s > k)
        {
            res += cnt[(s - k) % modulo];
        }
        cnt[s % modulo]++;
    }
    return res;
}
void testCountCompleteSubarrays()
{
    vector<int> nums = {3, 1, 9, 6};
    cout << countCompleteSubarrays(nums) << endl;
}
void testCountInterestingSubarrays()
{
    vector<int> nums = {3, 1, 9, 6};
    cout << countInterestingSubarrays(nums, 3, 0) << endl;
}
int main()
{
    testCountInterestingSubarrays();
    return 0;
}