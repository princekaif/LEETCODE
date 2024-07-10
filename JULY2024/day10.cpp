class Solution {
public:
    int minOperations(vector<string>& logs) {
        int x =0;
        for (int i =0; i<logs.size();i++){
            if(logs[i]=="../"){
                if(x==0){
                x=0;
                }
                else{
                x--;
                }
            }else if(logs[i]=="./"){
                continue;
            }
            else{
            x++;
            }
        }
        return x;
    }
};
