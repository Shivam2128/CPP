//{ Driver Code Starts
import java.util.*;
import java.lang.*;
import java.io.*;
class GFG
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine().trim());
        while(T-->0)
        {
            String[] s = br.readLine().trim().split(" ");
            int V = Integer.parseInt(s[0]);
            int E = Integer.parseInt(s[1]);
            ArrayList<ArrayList<Integer>>adj = new ArrayList<>();
            for(int i = 0; i < V; i++)
                adj.add(i, new ArrayList<Integer>());
            for(int i = 0; i < E; i++){
                String[] S = br.readLine().trim().split(" ");
                int u = Integer.parseInt(S[0]);
                int v = Integer.parseInt(S[1]);
                adj.get(u).add(v);
                adj.get(v).add(u);
            }
            Solution obj = new Solution();
            int ans = obj.detectCycle(V, adj);
            System.out.println(ans);
        }
    }
}
// } Driver Code Ends

class Solution{
    private int[] parent;
    private int[] depth;
    public int findparent(int vertex){
        if(vertex == parent[vertex]){
            return vertex;
        }
        return parent[vertex] = findparent(parent[vertex]);
    }
    public int detectCycle(int n, ArrayList<ArrayList<Integer>> adj){
        parent = new int[n];
        depth = new int[n];
        Map<Integer, Map<Integer, Integer>> mp = new HashMap<>();
        Arrays.fill(depth, 1);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
        for(int a = 0; a < n; a++){
            for(int b : adj.get(a)){
                if(mp.containsKey(a) && mp.get(a).containsKey(b)){
                    continue;
                }
                if(mp.containsKey(b) && mp.get(b).containsKey(a)){
                    continue;
                }                
                if(!mp.containsKey(a)){
                    mp.put(a, new HashMap<>());
                }
                mp.get(a).put(b, 1);
                int a_parent = findparent(a);
                int b_parent = findparent(b);
                if(a_parent != b_parent){
                    if(depth[a_parent] > depth[b_parent]){
                        parent[b_parent] = a_parent;
                        depth[a_parent] += depth[b_parent];
                    }else if(depth[a_parent] < depth[b_parent]){
                        parent[a_parent] = b_parent;
                        depth[b_parent] += depth[a_parent];
                    }else{
                        parent[a_parent] = b_parent;
                        depth[b_parent] += depth[a_parent];
                    }
                }else{
                    return 1;
                }
            }
        }
        return 0;
    }

}
