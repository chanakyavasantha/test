#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int len(vector<vector<int>>& graph, int v){
        int n=v;
        if(n==0||n==1)//if there are only one or zero nodes the answer should be 0->corner test case
            return 0;
        int endMask=(1<<n)-1;//so for v-nodes the mask will be 1...1(v times)
        // when all the bits are 1 it means we have visited all the nodes
        queue<pair<int ,int>> nq;//queue of pairs->a pair of of node-reference and mask
        set<pair<int ,int>> s;//priority queue of pairs->a pair of node-reference and mask
        for(int i=0;i<n;i++){
            //initializing queues with node references and masks.
            nq.push({i, 1 << i});
            s.insert({i, 1 << i});
            //s and nq will have masks as
            //for 4 nodes->0,1,2,3
            //0001
            //0010
            //0100
            //1000
        }
        int level = 0;
        while(!nq.empty()){//O(2^V)
            int sz=nq.size();//we should iterate through the queue
            while(sz--){
                pair<int,int> ele=nq.front();
                cout<<"***"<<endl;
                cout<<"ref:"<<ele.first<<endl;
                cout<<"Check Mask:"<<ele.second<<endl;
                nq.pop();
                for(auto &x:graph[ele.first]){//O(v) time
                    //graph[ele.first] is the first cell in the adjacency list 1->2->3
                    //1,2,3 are nodes connected to node-0
                    int mask=ele.second|(1<<x);
                    cout<<"mask :"<<mask<<endl;
                    //bit-wise or with respective bitmasks
                    if(mask==endMask){
                        return level+1;
                    }
                    //if we are unable to find that mask in the set s
                    if(s.find({x, mask}) == s.end()){//O(log(v*2^v)
                        //if mask is not found in s we will push the new mask.
                        nq.push({x, mask});
                        pair<int,int> w = nq.back();
                        cout<<"nq: first: "<<w.first<<endl;
                        cout<<"nq: second "<<w.second<<endl;
                        s.insert({x, mask});
                        cout<<"Set: "<<endl;
                        for(auto it: s){
                            cout<<it.first<<" ";
                            cout<<it.second<<endl;
                        }
                    }
                }
            }
            level++;
        }
        return -1;
    }
};

int main() {
    cout << "Enter how many vertices are there in the graph" << endl;
    int v;//number of vertices
    cin >> v;
    vector<vector<int>> w;//taking input of adjacency list
    int count = 0;
    vector<int> q;//each vector in w
    string s;
    cout<<"Enter Adjacency list of the graph"<<endl;
    while (true) {
        char p;
        cin >> p;
        s.push_back(p);
        count++;
        if (p != '[' && p != ']' && p != ','){
            q.push_back((int)p-48);
        }
        if (p == ']') {
            w.push_back(q);
            q.clear();
        }
        if(s[count-1] == ']' && s[count-2] == ']' )
            break;
    }
    Solution obj;
    cout << obj.len(w, v) << endl;
}