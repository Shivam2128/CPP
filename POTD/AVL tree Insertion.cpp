//{ Driver Code Starts
//

#include <bits/stdc++.h>
#define MAXN 2000
using namespace std;

struct Node
{
    int data, height;
    Node *left, *right;
    
    Node(int x)
    {
        data=x;
        left=right=NULL;
        height=1;
    }
};

bool isBST(Node *n, int lower, int upper)
{
	if(!n) return 1;
	if( n->data <= lower || n->data >= upper ) return 0;
	return isBST(n->left, lower, n->data) && isBST(n->right, n->data, upper) ;
}

pair<int,bool> isBalanced(Node* n)
{
	if(!n) return pair<int,bool> (0,1);

	pair<int,bool> l = isBalanced(n->left);
	pair<int,bool> r = isBalanced(n->right);

	if( abs(l.first - r.first) > 1 ) return pair<int,bool> (0,0);

	return pair<int,bool> ( 1 + max(l.first , r.first) , l.second && r.second );
}

bool isBalancedBST(Node* root)
{
	if( !isBST(root, INT_MIN, INT_MAX) )
		cout<< "BST voilated, inorder traversal : ";

	else if ( ! isBalanced(root).second )
		cout<< "Unbalanced BST, inorder traversal : ";

	else return 1;
	return 0;
}

void printInorder(Node* n)
{
	if(!n) return;
	printInorder(n->left);
	cout<< n->data << " ";
	printInorder(n->right);
}


// } Driver Code Ends
/* The structure of the Node is
struct Node
{
    int data;
    Node *left;
    Node *right;
    int height;
};
*/

class Solution{
  public:
    /*You are required to complete this method */
    int height(Node* N){
        if(!N){
            return 0;
        }
        return N -> height;
    }
    int getbalance(Node* N){
        if(!N){
            return 0;
        }
        return height(N -> left) - height(N -> right);
    }
    Node *rightrotation(Node* a){
        Node *b = a -> left;
        Node *c = b -> right;
        b -> right = a;
        a -> left = c;
        a -> height = max(height(a -> left), height(a -> right)) + 1;
        b -> height = max(height(b -> left), height(b -> right)) + 1;
        return b;
    }
    Node *leftrotation(Node* a){
        Node *b = a -> right;
        Node *c = b -> left;
        b -> left = a;
        a -> right = c;
        a -> height = max(height(a -> left), height(a -> right)) + 1;
        b -> height = max(height(b -> left), height(b -> right)) + 1;
        return b;
    }
    Node* insertToAVL(Node* node, int data){
        if(!node){
            return new Node(data);
        }
        if(data < node -> data){
            node -> left = insertToAVL(node -> left, data);
        }else if(data > node -> data){
            node -> right = insertToAVL(node -> right, data);
        }else{
            return node;
        }
        node -> height = max(height(node -> left), height(node -> right)) + 1;
        int balance = getbalance(node);
        if(balance > 1 and data < node -> left -> data){
            return rightrotation(node);
        }
        if(balance < -1 and data > node -> right -> data){
            return leftrotation(node);
        }
        if(balance > 1 and data > node -> left -> data){
            node -> left = leftrotation(node -> left);
            return rightrotation(node);
        }
        if(balance < -1 and data < node -> right -> data){
            node -> right = rightrotation(node -> right);
            return leftrotation(node);
        }
        return node;
    }
};

//{ Driver Code Starts.

int main()
{
	int ip[MAXN];
    
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        
        for(int i=0; i<n; i++)
            cin>> ip[i];
        
        Node* root = NULL;
        Solution obj;
        for(int i=0; i<n; i++)
        {
            root = obj.insertToAVL( root, ip[i] );
            
            if ( ! isBalancedBST(root) )
                break;
        }
        
        printInorder(root);
        cout<< endl;
    }
    return 0;
}
// } Driver Code Ends
