/**
 * The Triangle class calculate the area and the perimeter of a given triangle
 * 
 * @author Devora Borowski
 * @version 10/11/2019
 */
import java.util.Scanner; 
public class Triangle 
{ 
    /**
     * Gets the lengths of the tringle's sides
     * checks the legality of the input
     * in case of illegal input will print a message
     * otherwise will calculate the area and the perimeter of the triangle
     */
    public static void main (String [] args) 
    { 
        Scanner scan = new Scanner (System.in); 
        System.out.println ("This program calculates the area "  
            + "and the perimeter of a given triangle. ");  
        System.out.println ("Please enter the three lengths" 
            + " of the triangle's sides"); 
        int a = scan.nextInt(); 
        int b = scan.nextInt(); 
        int c = scan.nextInt(); 
        double area;
        int perimeter = a + b + c;
        double s = perimeter /2.0;//half perimeter, use it for calculat the area
        area = Math.sqrt(s*(s-a)*(s-b)*(s-c));//Heron formula for triangular area testing
        if(a>0 && b>0 && c>0)//triangle length side must be a positive number
        {
            if(a+b>c && a+c>b && b+c>a)//two sides of the triangle need to be bigger than the third
            {
                System.out.println("The triangle area is "+area);
                System.out.println("The perimeter of the triangle is "+perimeter);
            }
            else
            {
                System.out.println("Input data "+a+" "+b+" "+c);
                System.out.println("The sum of two sides of a triangle needs to be greater than the third.");
            }
        }
        else
        {
            System.out.println("Input data "+a+" "+b+" "+c);
            System.out.println("Triangle lengths should be positive numbers");
        }

    } // end of method main 
} //end of class Triangle 