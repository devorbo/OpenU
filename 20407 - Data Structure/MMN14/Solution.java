import java.util.*;
/**
 * MMN 14 - implement the question from MMN 11 Q2a in different ways using various algorithm and strategies 
 *
 * @author Devora Borowski
 * @id 345811723
 * @version 4.6.2021
 */
public class Solution
{
    private static final int END=100;

    public static void main(String[] args)
    {
        Scanner scan=new Scanner(System.in);
        System.out.println("Enter number of element in the array - N");
        int n=scan.nextInt();
        if(n<1)
        {
            System.out.println("Error");
            return;
        }
        int[] arr=new int[n];
        Random rnd=new Random();
        for(int i=0;i<arr.length;i++)
        {
            arr[i]=rnd.nextInt(END)+1;/* insert random numbers to the array */
        }
        
        numElementOriginal(arr,n);
        numElementInsertionSort(arr,n);
        numElementMergeSort(arr,n);
        numElementCountingSort(arr,n);
        numElementHashTable(arr,n);
        numElementBinaryTreeSearch(arr,n);
        numElementRedBlackTree(arr,n);

    }

    /***
     *  method to print out the review for the specific algorithm - num comparsion and num placement
     */
    public static void printAlgoReview(int n,String nameAlgo, int[]set)
    {
        System.out.println("For N="+n+" the "+ nameAlgo+ " algurithm made "+ set[0] + " comparsion and "+ set[1] + " placement");
    }
    
    /***
     * Q7 - Red Black Tree
     * return how many uniqe valuse there is in the array by using a red black tree
     * check if the element exist in the binary tree, if not
     * insert the elements to the tree
     * @set - count comparsion and placements
     * @return number of uniqe values
     */
    public static int numElementRedBlackTree(int[]arr,int n)
    {
        int[] set=new int[2];
        int count=0;
        RedBlackTree tree=new RedBlackTree();
        for(int i=0;i<arr.length;i++)
        {
            if(tree.search(arr[i],set)==null)// search the value if exist in the tree
            {
                tree.insert(arr[i],set); // if not, insert to the tree
                count++;
            }
        }
        printAlgoReview(n,"red black tree search",set);
        return count;
    }

    /***
     * Q6 - Binary tree search
     * return how many uniqe valuse there is in the array by using a binary tree
     * check if the element exist in the binary tree, if not
     * insert the elements to the tree
     * @set - count comparsion and placements
     * @return number of uniqe values
     */
    public static int numElementBinaryTreeSearch(int[]arr,int n)
    {
        int[] set=new int[2];
        int count=0;
        BinarySearchTree tree=new BinarySearchTree();
        for(int i=0;i<arr.length;i++)
        {
            if(!tree.search(arr[i],set))// search the value if exist in the tree
            {
                tree.insert(arr[i],set); // if not, insert to the tree
                count++;
            }
        }
        printAlgoReview(n,"binary tree search",set);
        return count;
    }

    /***
     * Q5 - Hash table
     * checks uniqe valuse in the array by using a hashtable
     */
    public static void numElementHashTable(int[] arr,int n)
    {
        int[] set=new int[2];
        removeDuplicatesHashTable(arr,set);
        printAlgoReview(n,"hashtable",set);
    }

    /***
     * insert the array elements to the hashtable if the value doesn't exist yet
     * @set - count comparsion and placements
     * @return number of uniqe values
     */
    private static int removeDuplicatesHashTable(int[] arr,int[] set)
    {
        Hashtable table=new Hashtable();
        int count=0;
        for(int i=0;i<arr.length;i++)
        {
            if(table.containsValue(arr[i])==false)
            {
                count++;
                table.put(count,arr[i]);
                set[1]++;
            }
            set[0]++;
        }
        return count;
    }

    /***
     * Q4 - Counting sort
     * checks uniqe valuse in the array by using the algorithm of counting sort
     */
    public static void numElementCountingSort(int[] arr,int n)
    {
        int[] set=new int[2];
        countingSortVersionCount(set,arr,END);
        printAlgoReview(n,"counting sort",set);
    }

    /***
     * counting apperance for each number in the range 0..k
     */
    private static int countingSortVersionCount(int[] set, int[] a, int k)
    {
        int count=0;
        //placing for the array elements
        int[] c=new int[k+1];
        for(int j=0;j<a.length;j++)
        {
            c[a[j]]++;//placement
            set[1]++;
        }
        //c[i] now contains the number of elements equal to i
        for(int i=0;i<c.length;i++)
        {
            if(c[i]!=0)
                count++;
        }
        return count;
    }
    /***
     * Q3 - Merge sort
     * checks uniqe valuse in the array by using the algorithm of merge sort
     */
    public static void numElementMergeSort(int[] arr, int n)
    {
        int[] set =new int[2];
        mergeSort(set,arr,0,arr.length-1);
        numElementAfterSort(set,arr);
        printAlgoReview(n,"merge sort",set);
    }


    /***
     * Merge sort
     * sent to sort array 
     * @p - begginning index 
     * @r - end index to sort
     */
    public static void mergeSort(int[]set, int[] arr,int p,int r)
    {
        if(p<r)
        {
            int q=(p+r)/2;
            mergeSort(set,arr,p,q);
            mergeSort(set,arr,q+1,r);
            merge(set,arr,p,q,r);
        }
    }

    /***
     * sort array by merging the subarrays
     */
    private static void merge(int[] set, int[] arr,int p,int q,int r)
    {
        int n1=q-p+1;
        int n2=r-q;
        //temporary subarrays
        int[] left=new int[n1];
        int[] right=new int[n2];
        int i=0,j=0;
        // Copying elements into the subarrays 
        for(i=0;i<left.length;i++)
        {
            left[i]=arr[p+i];
            set[1]++;
        }
        for(i=0;i<right.length;i++)
        {
            right[i]=arr[q+i+1];
            set[1]++;
        }

        i=0;
        j=0;
        // Copying from leftArray and rightArray back into array
        for(int k=p;k<r+1;k++)
        {
            // If there are still uncopied elements in R and L, copy minimum of the two
            if(i<left.length && j<right.length)
            {

                if(left[i]<=right[j])
                {
                    arr[k]=left[i];
                    set[1]++;
                    i++;
                }
                else
                {
                    arr[k]=right[j];
                    set[1]++;
                    j++;
                }
                set[0]++;
            }
            else if(i<left.length)
            {
                // If all elements have been copied from rightArray, copy rest of left array
                arr[k]=left[i];
                set[1]++;
                i++;
            }
            else if(j<right.length)
            {
                // If all elements have been copied from leftArray, copy rest of right array
                arr[k]=right[j];
                set[1]++;
                j++;
            }
        }
    }
    /***
     * function that counts how many differents values in a sorted array
     */
    public static int numElementAfterSort(int[] set,int[] arr)
    {
        int count=1;
        for(int i=1;i<arr.length;i++)
        {
            if(arr[i]!=arr[i-1])// the first appearance for this value, count it
            {
                count++;
            }
            set[0]++;
        }
        return count;
    }
    
    /***
     * Q2 - Insertion sort
     * checks uniqe valuse in the array by using the algorithm of insertion sort
     */
    public static void numElementInsertionSort(int[] arr,int n)
    {
        int[] set=new int[2];//save the values of comparing and placing
        insertionSort(set,arr);
        numElementAfterSort(set,arr);
        printAlgoReview(n,"inseration sort",set);
    }

    /***
     * sort array by using the algorithm insertion sort
     * for each subarray - arr[0...i-1] will insert the arr[i] in the right position
     */
    private static void insertionSort(int[]set, int[] arr)
    {     
        int compare=0, place=0;
        for (int i = 1; i < arr.length; i++) 
        { 
            int key = arr[i]; 
            int j = i - 1;
            while (j >= 0 && arr[j] > key) // Compare key with each element on the left of it until an element smaller than it is found.
            {
                arr[j + 1] = arr[j];
                place++;
                j = j - 1;
            }
            compare++;
            arr[j + 1] = key; // place key 
            place++;
        }
        set[0]=compare;
        set[1]=place;
    }

    /***
     * Q1 - Original algorithm
     * checks uniqe valuse in the array by using the original algorithm 
     */
    public static int numElementOriginal(int[] arr,int n)
    {
        int size=1;
        int[] set=new int[2];
        int compare=0,place=0;
        for(int i=1;i<arr.length;i++)
        {
            boolean U=true;
            for(int j=0;j<size;j++)
            {
                if(arr[j]==arr[i])/* the element appears another time in the array */
                {
                    U=false;
                    j=size;/* will stop the loop */
                }
                set[0]++;
            }
            if(U==true)/* the element apears only once in the sub array */
            {
                size++;/* count this element */
                arr[size-1]=arr[i];/* put this element in the sub array in a order that contains only one appearance  for each element */
                set[1]++;
            }
        }
        printAlgoReview(n,"original",set);
        return size;
    }


}
