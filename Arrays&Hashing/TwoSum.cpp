class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        vector<int> result;
        
        for(int i = 0; i < nums.size(); i++){
            int temp = target - nums[i];
            if(m.find(temp) == m.end()){
                m[nums[i]] = i;
            }
            else{
                result.push_back(m[temp]);
                result.push_back(i);
                break;
            }
        }
        //sort(result.begin(), result.end());
        return result;
        
    }
};