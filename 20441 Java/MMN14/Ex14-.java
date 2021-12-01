public class Ex14
{

    /**
     * Creates a new Ex14 object
     */
    public Ex14()
    {

    }

    /**
     * Returns the number of substrings that begin and end with this symbol, 
     * and contain only once that specific symbol. 
     * If in any case, either the symbol dos not exist in the string, 
     * or there is no substring that is according to the requirement will return 0.
     * 
     * Time Complications
     * O(n)
     * Place complexity
     * O(1)
     * 
     * @param s the string to search on
     * @param c the symbol that will be checked 
     * 
     * @return the number of substring from the string that begin and end with this symbol, 
     * and contain only once that specific symbol
     */
    public static int subStrC(String s, char c)
    {
        //string that is shorter than 3 can't contain the correct substring according to the requirements
        if(s.length()<=2)
            return 0;
        int countsub=0
        //build a new string only with the specific symbol
        for(int i=0;i<s.length();i++)
        {
            //add the symbols that are equal to the one that was gotten from the user, into the new string
            if(s.charAt(i)==c)
            {

                countsub++;
            }
        }
        if(sub.length()<=2)//substring that is only with two symbols or less, 
        //that mean that can begin with a c and maybe end with a c, but between them dos not contain another c
            return 0;
        //for the new string that is buildt only from the specific symbol, will add to count the possibilities that could be.
        //will count how many substrings there is that begin and end with the symbol, and contain only once that specific symbol
        int count=countsub-2;
        return count;
    }

    /**
     * Returns the number of substrings that begin and end with this symbol, 
     * and contain up to k times that specific symbol.
     * If in any case, either the symbol dos not exist in the string, 
     * or there is no substring that is according to the requirement will return 0.
     * 
     * Time Complications
     * O(n)
     * Place complexity
     * O(1)
     * 
     * @param s the string to search on
     * @param c the symbol that will be checked 
     * @param k the max times that a substring can contain the symbol c
     * 
     * @return the number of substring from the string that begin and end with this symbol, 
     * and contain up to k times that specific symbol.

     */
    public static int subStrMaxC(String s, char c, int k)
    {
        int countsub=0;
        //build a new string only with the specific symbol
        for(int i=0;i<s.length();i++)
        {
            if(s.charAt(i)==c)
            {
                countsub++;
            }
        }

        int count=0;
        for(int i=0;i<sub.length();i++)
        {
            //the distance from the specific index until the end, 
            //when it is a higher value than the value that the user insert
            //will add that value, 
            //k - substring that contains the symbol maximum k times
            if(countsub-i-1>=k+1)
                count+=k+1;
            else
                count+=countsub-i-1;
        }
        return count;
    }

    /**
     * Replaces any value in the array that is not zero, to be the the distance to the closes element that is zero 
     * 
     * Time Complications
     * O(n)
     * Place complexity
     * O(1)
     * 
     * @param a the array to edit, the distance to each element
     */
    public static void zeroDistance (int [] a)
    {
        //go through the array, from the secound position and until the secound to the last 
        //switch the elements that are value are not 0, 
        //but not those who next to a element that is value 0, either from the left or from the right.
        //the element that need to work on,make the element value to be as the one next to them from the left +1
        for(int i=1;i<a.length-1;i++)
        {
            if(a[i]!=0)
            {         
                if((a[i-1]!=0 && a[i+1]!=0))
                {
                    a[i]=a[i-1]+1;
                }
            }

        }
        //if the last element dos not equal to 0, and the element from the left dosn't equal 
        //so then make tha element value to be one more than the element from the left 
        if(a[a.length-1]!=0)
        {
            if(a[a.length-2]!=0)//the element to the left
            {
                a[a.length-1]=a[a.length-2]+1;
            }
        }
        //until here, the array is sort as distance from 0 ,distance from the left accep the 0 and 1 that are in place

        int index=a.length-1;//find the index of the closes 0, the 0 that is the closes to the beginning of the array
        //we need to use later, if the first element in th array, is not 0

        //we sort the array from right to left, each value that is greater than the element from the right,
        //will set that element to be one more than the value from the right
        for(int i=a.length-2;i>0;i--)
        {
            if(a[i]!=1 && a[i]!=0)
            {
                if(a[i]>a[i+1])
                {
                    a[i]=a[i+1]+1;
                }             
            }  
            else if(a[i]==0)
                index=i;
        }

        //when the first element is not 0, will go through the part from the first element until the closes 0, 
        //and will set the value to be a higher number by one from the element from the right
        if(a[0]!=0)
        {
            if(index>=2)//if it is equal or lower that 2, so those values are 0 and 1
                for(int i=index-2;i>=0;i--)
                {
                    a[i]=a[i+1]+1;
                }
        }

    }

    /**
     * Define that a string had a transformation from a string if each symbol of the second string appears in the same order at least once.
     * If a symbol in the first string appears several times then it will exist in the second string at least the same amount of times, not less
     * 
     * @param s the string being checked
     * @param t the string to check if had a transformation
     * 
     * @return true if the string t have being transformed and false if not
     */
    public static boolean isTrans(String s, String t) 
    {
        if(t.length()< s.length())//each symbol of s needs to appear at least the same amount of times in t, 
        //if t length is shorter than s than definitely she is not transformation because she is missing a symbol      
            return false;
        if(t.equals(s))
            return true;
       
        //if the first string length is 0, and the method didn't stop until here, that means that t contains a few more symbols that do not appear at s 
        if(s.length()!=0)
        {
            int numS=duplicated(s,s.charAt(0));//check how many time the first symbol appears in a row
            s=s.substring(numS-1);//than s will have the last char between them and the continuation of the string
            if(s.charAt(0)==t.charAt(0))
            {
                int numT=duplicated(t,t.charAt(0));//check how many time the first symbol appears in a row
                if(numT<numS)//the symbol has to appear at least the same amount of times as s
                    return false;
                return isTrans(s.substring(1),t.substring(numT));//the s we will return from the secound position,
                //because we want to go over to the next character , the t we want to begin next round with the next character
            }
        }
        return false;
    }

    /**
     * Returns how many time the character appears at the string in a row, from the first position
     */
    private static int duplicated(String s,char c)
    {
        if(s.length()==0)
            return 0;
        if(s.charAt(0)==c)
            return duplicated(s.substring(1),c)+1;
        return 0;
    }

    /**
     * Returns the number of possible valid paths in the array.
     * 
     * Define a valid path in the array as a series of elements in the array, 
     * with the first element - row 0 and column 0.
     * And progressing the array according to the unity and tens digit of the number in the element, 
     * until the last element in the last row and last column.
     * 
     * Note that it is impossible to move beyond the boundaries of the array
     * 
     * @param mat the array that searching on for valid paths
     * 
     * @return the number of possible valid paths in the array
     */
    public static int countPaths (int [][] mat)  
    {
        //begin searching the array from row index 0 and column index 0
        return countPaths(mat,0,0);
    }

    /**
     * Returns the number of possible valid paths in the array.
     * 
     * @param mat the array that searching on for valid paths
     * @param i the row index of the element
     * @param j the column index of the element 
     * 
     * @return the number of possible valid paths in the array
     */
    private static int countPaths (int [][] mat,int i,int j)  
    {
        //base case
        //when the method comes to the last element (last row last column) that's mean that the path is valid and will return 1 to add to the count 
        if(i==mat.length-1 && j==mat[0].length-1)
            return 1;
        //if the index is greater then the length of the array (either rows or columns ) it is an invalid path
        else if(i>=mat.length)
            return 0;
        else if(j>=mat[0].length)
            return 0;

        int value1=mat[i][j]/10;//tens digit
        int value2=mat[i][j]%10;//unity digit
        //in a situation that need to continue on but can not because the element value is zero  
        if(value1==0 && value2==0)
        {
            //can not continue on - infinite
            return 0;
        }
        //if the tens digit and the unity digit are the same, send it as one route
        if(value1==value2)
        {
            //add to both indexes the value and send to the method
            return countPaths(mat,i+value1,j+value1);
        }
        //add to the first index the tens digit and to the second index the unity digit, then send to the method, also,
        //add to the first index the unity digit and to the second index the tens digit, then send both indexes with the array to the method
        //return the sum routes between the two numbers that the methods returned
        return countPaths(mat,i+value1,j+value2) + countPaths(mat,i+value2,j+value1);
    }

}