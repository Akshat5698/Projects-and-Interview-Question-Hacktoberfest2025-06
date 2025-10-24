class Solution {
public:
    int distSq(int x1, int y1, int x2, int y2) {
        int dx = x1 - x2;
        int dy = y1 - y2;
        return dx * dx + dy * dy; 
    }
    int orientation(int x1,int y1,int x2,int y2,int x3,int y3){
        int s2 = (x2 - x1);
        int s1 = (y2 - y1);

        int s4 = (x3 - x2);
        int s3 = (y3 - y2);

        return (s2 * s3) - (s1 * s4);
    }
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {

        vector<vector<int>> ans;
        vector<vector<bool>> visited(101,vector<bool>(101,false));
        int start_x = trees[0][0];
        int start_y = trees[0][1];
        for(int i = 1; i<trees.size(); i++){
            if((trees[i][0] < start_x) || (trees[i][0] == start_x && trees[i][1] > start_y)){
                start_x = trees[i][0];
                start_y = trees[i][1];
            }
        }
        int cur_x = start_x;
        int cur_y = start_y;
        ans.push_back({cur_x,cur_y});

        visited[cur_x][cur_y] = true;
        while(true){
            cout<<cur_x<<" "<<cur_y<<endl;

            int nextP_x = trees[0][0];
            int nextP_y = trees[0][1];

            vector<vector<int>> collinear;

            for(int i = 1; i<trees.size(); i++){
                
                if(trees[i][0] == cur_x && trees[i][1] == cur_y) continue;

                
                int o = orientation(cur_x,cur_y,nextP_x,nextP_y,trees[i][0],trees[i][1]);

                if(o > 0){
                    nextP_x = trees[i][0];
                    nextP_y = trees[i][1];

                    collinear.clear();
                }
                else if(o == 0){
                    
                    int dst1 = distSq(cur_x,cur_y,nextP_x,nextP_y);
                    int dst2 = distSq(cur_x,cur_y,trees[i][0],trees[i][1]);
                    if(dst1 <= dst2){ 

                        if(nextP_x != cur_x || nextP_y != cur_y) {
                            collinear.push_back({nextP_x, nextP_y});
                        }
                        nextP_x = trees[i][0];
                        nextP_y = trees[i][1];
                    }
                    else if(dst1 > dst2){
                        collinear.push_back({trees[i][0], trees[i][1]});
                    }
                }
            }

            cur_x = nextP_x;
            cur_y = nextP_y;
            
            for(int i = 0; i<collinear.size(); i++){
                
                if(visited[collinear[i][0]][collinear[i][1]] == false) ans.push_back({collinear[i][0],collinear[i][1]});
                
                visited[collinear[i][0]][collinear[i][1]] = true;

            } 

            if(cur_x == start_x && cur_y == start_y) {
                break;
            }
    
            ans.push_back({nextP_x,nextP_y});
            
            visited[nextP_x][nextP_y] = true;
        }

        return ans;
    }
};
