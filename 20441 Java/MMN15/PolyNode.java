/**
 *  This class represents a PolyNode object
 * @author Devora Borowski
 * @version 4/2/2020
 */
public class PolyNode
{
    private int _power;
    private double _coefficient;
    private PolyNode _next;

    /**
     * Build a new PolyNode object
     * If the parameter power is illegal, will set that parameters to be a default response
     * will set next to be null
     * 
     * @param power The power of the PolyNode
     * @param coefficient The coefficient of the PolyNode 
     */
    public PolyNode(int power, double coefficient) 
    {
        if(power<0)
        {
            _power=0;
            _coefficient=0;
        }
        else
        {
            _power=power;
            _coefficient=coefficient;
        }
        _next=null;
    }

    /**
     * Build a new PolyNode object with a next pointer
     * If the parameter power is illegal, will set that parameters to be a default response
     * 
     * @param power The power of the PolyNode
     * @param coefficient The coefficient of the PolyNode 
     * @param next The next pointer that the PolyNode will point to
     */
    public PolyNode(int power, double coefficient,PolyNode next)
    {
        if(power<0)
        {
            _power=0;
            _coefficient=0;
        }
        else
        {
            _power=power;
            _coefficient=coefficient;
        }
        _next=next;
    }

    /**
     * A copy constructor
     * 
     * @param p The PolyNode to be copied
     */
    public PolyNode(PolyNode p)
    {
        _power=p._power;
        _coefficient=p._coefficient;
        _next=p._next;
    }

    /**
     * Returns the power
     * 
     * @return The power
     */
    public int getPower()
    {
        return _power;
    }

    /**
     * Returns the coefficient
     * 
     * @return The coefficient
     */
    public double getCoefficient()
    {
        return _coefficient;
    }

    /**
     * Returns the next
     * 
     * @return The next
     */
    public PolyNode getNext()
    {
        return _next;
    }

    /**
     * Sets the power
     */
    public void setPower(int power)
    {
        if(power>=0)
            _power=power;
    }

    /**
     * Sets the coefficient
     */
    public void setCoefficient(double coefficient)
    {
        _coefficient=coefficient;
    }

    /**
     * Sets the next
     */
    public void setNext(PolyNode next)
    {
        _next=next;
    }

    /**
     * Returns a String that represents this PolyNode
     * 
     * @return String that represents this PolyNode
     */
    public String toString()
    {
        if(_coefficient==0)//the polynode does not contain a number that count
            return "";
        if(_power==0)//the power is 
            return ""+_coefficient;
        String s="";
        if(_coefficient==-1)
            s+="-";
        if(_coefficient!=1 && _coefficient!=-1)
            s+=_coefficient;
        s+="x";
        if(_power!=1)
            s+="^"+_power;
        return s;
    }
}
