/**
 * The Congruent class checks if two triangle overlap
 * 
 * @author Devora Borowski
 * @version 10/11/2019
 */
import java.util.Scanner; 
public class Congruent  
{ 
    /**
     *Gets vertices of two triangles
     *check if the triangles overlap or not
     */
    public static void main (String [] args) 
    { 
        Scanner scan = new Scanner (System.in); 
        System.out.println ("This program checks if two triangle overlap or not.");  
        System.out.println ("Please enter three pairs of real numbers");
        double x11 = scan.nextDouble(); 
        double y11 = scan.nextDouble();
        double x12 = scan.nextDouble();
        double y12 = scan.nextDouble();
        double x13 = scan.nextDouble();
        double y13 = scan.nextDouble();

        System.out.println ("Please enter another three pairs of numbers");
        double x21 = scan.nextDouble(); 
        double y21 = scan.nextDouble();
        double x22 = scan.nextDouble();
        double y22 = scan.nextDouble();
        double x23 = scan.nextDouble();
        double y23 = scan.nextDouble();

        //Calculate distance using distance formula
        double a1,b1,c1;
        a1=Math.sqrt(Math.pow((x11-x12),2)+Math.pow((y11-y12),2));
        b1=Math.sqrt(Math.pow((x12-x13),2)+Math.pow((y12-y13),2));
        c1=Math.sqrt(Math.pow((x11-x13),2)+Math.pow((y11-y13),2));

        double a2,b2,c2;
        a2=Math.sqrt(Math.pow((x21-x22),2)+Math.pow((y21-y22),2));
        b2=Math.sqrt(Math.pow((x22-x23),2)+Math.pow((y22-y23),2));
        c2=Math.sqrt(Math.pow((x21-x23),2)+Math.pow((y21-y23),2));

        System.out.print("The first triangle is ");
        System.out.print("("+x11+","+y11+")" );
        System.out.print("("+x12+","+y12+")" );
        System.out.println("("+x13+","+y13+")." );
        System.out.println("Its lengths are "+a1+", "+b1+", "+c1+".");

        System.out.print("The second  triangle is ");
        System.out.print("("+x21+","+y21+")" );
        System.out.print("("+x22+","+y22+")" );
        System.out.println("("+x23+","+y23+")." );
        System.out.println("Its lengths are "+a2+", "+b2+", "+c2+".");
        
        //Conditions to check whether the triangles are congruent
        boolean overlap=false;
        if(a1==a2)
        {
            if(b1==b2)
            {
                if(c1==c2)
                {
                    overlap=true;
                }
            }
            else if(b1==c2)
            {
                if(c1==b2)
                {
                    overlap=true;
                }
            }
        }
        else if(a1==b2)
        {
            if(b1==a2)
            {
                if(c1==c2)
                {
                    overlap=true;
                }
            }
            else if(b1==c2)
            {
                if(c1==a2)
                {
                    overlap=true;
                }
            }
        }
        else if(a1==c2)
        {
            if(b1==a2)
            {
                if(c1==b2)
                {
                    overlap=true;
                }
            }
            else if(b1==b2)
            {
                if(c1==a2)
                {
                    overlap=true;
                }
            }
        }
        //this part is not working exactly, so I changed it to what I wrote above
        /*
        if(a1!=a2)
        {
            if(b1!=b2)
            {
                if(c1!=c2)
                {
                    overlap=false;
                }
            }
            else if(b1!=c2)
            {
                if(c1!=b2)
                {
                    overlap=false;
                }
            }
        }
        else if(a1!=b2)
        {
            if(b1!=a2)
            {
                if(c1!=c2)
                {
                    overlap=false;
                }
            }
            else if(b1!=c2)
            {
                if(c1!=a2)
                {
                    overlap=false;
                }
            }
        }
        else if(a1!=c2)
        {
            if(b1!=a2)
            {
                if(c1!=b2)
                {
                    overlap=false;
                }
            }
            else if(b1!=b2)
            {
                if(c1!=a2)
                {
                    overlap=false;
                }
            }
        }
        */
        if(overlap)
            System.out.println("The triangles are congruent.");
        else
            System.out.println("The triangles are not congruent.");

    } // end of method main 
} //end of class Congruent