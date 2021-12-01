
/**
 * binary tree search class
 * insert and search methods
 */
public class BinarySearchTree
{
    /* Class containing left
    and right child of current node
     * and key value*/
    class Node
    {
        int key;
        Node left, right;

        public Node(int item)
        {
            key = item;
            left = right = null;
        }
    }

    // Root of BST
    Node root;

    BinarySearchTree()
    {
        root = null;
    }

    // This method mainly calls insertRec()
    void insert(int key, int[] set)
    {
        root = insertRec(root, key, set);
    }

    /* A recursive function to
    insert a new key in BST */
    private Node insertRec(Node root, int key, int[] set)
    {

        /* If the tree is empty,
        return a new node */
        if (root == null)
        {
            set[1]++;
            root = new Node(key);
            return root;
        }

        /* Otherwise, recur down the tree */
        if (key < root.key)
        {
            set[0]++;
            root.left = insertRec(root.left, key, set);
        }
        else if (key > root.key)
        {
            set[0]++;
            root.right = insertRec(root.right, key, set);
        }

        /* return the (unchanged) node pointer */
        return root;
    }

    // This method mainly calls InorderRec()
    void inorder()
    {
        inorderRec(root);
    }

    // A utility function to
    // do inorder traversal of BST
    private void inorderRec(Node root)
    {
        if (root != null) {
            inorderRec(root.left);
            System.out.println(root.key);
            inorderRec(root.right);
        }
    }

    public boolean search(int key, int[] set)
    {
        return search(root,key,set);
    }
    // function to search a given key in BST
    private boolean search(Node root, int key, int[] set)
    {
        // Base Cases: root is null or key is present at root
        if (root == null) {
            return false;
        } 
        if (key == root.key) 
        {
            set[0]++;
            return true;
        } 
        /* Otherwise, recur down the tree */
        else if (key < root.key)
        {
            set[0]++;
            return search(root.left, key, set);
        }
        else 
        {
            set[0]++;
            return search(root.right, key, set);
        }
    }
}
