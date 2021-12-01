/**
 * This class represents a Matrix object
 *
 * @author Devora Borowski
 * @version 25/12/2019
 */
public class Matrix
{
    private int[][] _array;

    private final int BLACK=255;

    /**
     * Create a new Matrix object
     * Set all the elements to 0
     * 
     * @param size1 the length of the rows
     * @param size2 the length of the columns
     */
    public Matrix(int size1,int size2)
    {
        _array=new int[size1][size2];
        for(int i=0;i<_array.length;i++)//rows
        {
            for(int j=0;j<_array[0].length;j++)//columns
            {
                _array[i][j]=0;
            }
        }
    }

    /**
     * Create a new Matrix object
     * 
     * @param array create a new matrix with tha data of array
     */   
    public Matrix(int[][] array)
    {
        _array=new int[array.length][array[0].length];
        _array=copyArray(array);
    }

    /**
     * Returns the negative image of the image, that is, every point in the image,
     * element in an array that is black becomes white, each element that is white becomes black, 
     * and so all grayscale becomes the number that completes them to 255.
     * 
     * @return a matrix that represents the negative image
     */
    public Matrix makeNegative()
    {
        //build a new array and do not work on the array property
        int[][] array=new int[_array.length][_array[0].length];
        for(int i=0;i<array.length;i++)
        {
            for(int j=0;j<array[0].length;j++)
            {
                //Set this current element to be the complementary number to 255 of the array element that is being tested
                array[i][j]=BLACK-_array[i][j];
            }
        }
        //return a matrix with the array that represents the negative image
        Matrix negative=new Matrix(array);
        return negative;
    }

    /**
     * Rotates the image 90 degrees clockwise
     * 
     * @return a Matrix object after the rotating
     */
    public Matrix rotateClockwise() 
    {
        //the length of the rows will be the length of the current matrix coulmn
        int[][] array=new int[_array[0].length][_array.length];
        for(int i=0;i<array.length;i++)
        {
            for(int j=0;j<array[0].length;j++)
            {
                array[i][j]=_array[array[0].length-1-j][i];
            }
        }
        Matrix rotate=new Matrix(array);
        return rotate;
    }

    /**
     * Rotates the image 90 degrees counterclockwise
     * 
     * @return a Matrix object after the rotating
     */
    public Matrix rotateCounterClockwise()
    {
        //need to leave the array with out changes so saving it in a new variable
        int[][] save=copyArray(_array);
        Matrix rotate=null;
        for(int i=0;i<3;i++)
        {
            //using the rotateClockwise method to rotate 270 degree clockwise that equals to 90 degrees counterclockwise
            rotate=rotateClockwise();
            //the rotateClockwise metod work on the property that why you need to update tha property to the ratate array
            _array=rotate._array;
        }
        //updating this property to be as the original array
        _array=save;
        return rotate;
    }

    /**
     * Returns the image received from the image slice. 
     * The smoothing action, is done by making each element in the current image
     * the value of its average value with its neighbors in the current image.
     * 
     * @return a new matrix representing the image slice of the matrix on which the operation is being triggered
     */
    public Matrix imageFilterAverage()
    {
        int[][] array=new int[_array.length][_array[0].length];
        for(int i=0;i<array.length;i++)
        {
            for(int j=0;j<array[0].length;j++)
            {
                //the value of the element equals to the average value with its neighbors
                array[i][j]=avrageOfElement(i,j);
            }
        }
        Matrix avg=new Matrix(array);
        return avg;      
    }

    /**
     * Returns a String that represents this Matrix 
     * 
     * @return String that represents this Matrix
     */
    public String toString()
    {
        String print="";
        for(int i=0;i<_array.length;i++)
        {
            for(int j=0;j<_array[0].length;j++)
            {
                print+=_array[i][j];
                if(j!=_array[0].length-1)
                {
                    print+="\t";
                }
            }
            //after each row will go down a line
            print+="\n";
        }
        return print;
    }

    private int avrageOfElement(int row,int col)
    {
        int sum=0,count=0;
        //go through the 8 neighbors and also over the element that was sent
        for(int i=row-1;i<=row+1;i++)
        {
            for(int j=col-1;j<=col+1;j++)
            {
                boolean valid=isValid(i,j);
                //only if the row and column is valid add to sum
                if(valid)
                {
                    sum+=_array[i][j];
                    count++;
                }
            }
        }
        //check the average of all the valid neighbors of the elements
        int avrage=sum/count;
        return avrage;
    }

    //check if a certain row and column is valid in a matrix
    private boolean isValid(int row , int col)
    {
        return (((row>-1)&&(row<_array.length)) &&
            ((col>-1)&&(col<_array[0].length)));
    }

    /**
     * copy a array by building a new array with the same length and coping each element to the right element
     * 
     * @return the copy of the array
     */
    private int[][] copyArray(int[][] array1)
    {
        int[][] array2=new int[array1.length][array1[0].length];
        for(int i=0;i<array1.length;i++)
        {
            for(int j=0;j<array1[0].length;j++)
            {
                array2[i][j]=array1[i][j];
            }
        }
        return array2;
    }
}
