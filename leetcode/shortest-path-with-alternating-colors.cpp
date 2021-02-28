class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        
        vector< pair<int, int> > graph[101];
        vector<int> answer;
        
        for(int i=0; i<n; i++) {
            answer.push_back(INT_MAX);
        }
        
        // red = 0
        for(int i=0; i<red_edges.size(); i++) {
            graph[red_edges[i][0]].push_back(make_pair(red_edges[i][1], 0));
        }
        
        // blue = 1
        for(int i=0; i<blue_edges.size(); i++) {
            graph[blue_edges[i][0]].push_back(make_pair(blue_edges[i][1], 1));
        }
        
        // first node in bfs is 0
        queue< pair< pair<int, int>, int> > q;
        q.push(make_pair(make_pair(0,-1), 0));
        answer[0] = 0;
        
        bool red_vis[101] = {0};
        bool blue_vis[101] = {0};
        
        while(!q.empty()) {
            pair< pair<int, int>, int> Nnode = q.front();
            pair<int, int> node = Nnode.first;
            int dis = Nnode.second;
            
            red_vis[0] = blue_vis[0] = true;
            q.pop();
            
            for(int i=0; i<graph[node.first].size(); i++) {
                pair<int,int> to_node = graph[node.first][i];
                
                int to = to_node.first;
                int to_color = to_node.second;
                                
                if(node.second == -1) {
                    q.push(make_pair(to_node, dis+1));
                    answer[to] = min(answer[to], dis + 1);
                                        
                    if(to_color == 1) blue_vis[to] = true;
                    else if(to_color == 0) red_vis[to] = true;
                } else if(node.second == 0 && to_color == 1 && !blue_vis[to]) {
                    q.push(make_pair(to_node, dis+1));
                    answer[to] = min(answer[to], dis + 1);
                    blue_vis[to] = true;
                } else if(node.second == 1 && to_color == 0 && !red_vis[to]) {
                    q.push(make_pair(to_node, dis+1));
                    answer[to] = min(answer[to], dis + 1);
                    red_vis[to] = true;
                }
            }
        }
        
        for(int i=0; i<n; i++) {
            if(answer[i] == INT_MAX) {
                answer[i] = -1;
            }
        }
        
        return answer;
    }
};