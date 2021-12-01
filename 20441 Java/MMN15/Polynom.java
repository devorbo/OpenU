/**
 *  This class represents a Polynom object
 *  Define Polynom as a list of PolyNode objects
 *
 * @author Devora Borowski
 * @version 4/2/2020
 */
public class Polynom
{
    private PolyNode _head;
    /**
     * Build a new Polynom object
     */
    public Polynom()
    {
        _head=null;
    }

    /**
     * Build a new Polynom object 
     * 
     * @param p Set head to point to p
     */
    public Polynom(PolyNode p)
    {
        _head=p;
    }

    /**
     * Get the pointer tho head
     * 
     * @return The pointer to head
     */
    public PolyNode getHead()
    {
        return _head;
    }

    /**
     * Set the pointer to head
     */
    public void setHead(PolyNode p) 
    {
        _head=p;
    }

    /**
     * Gets a object from the PolyNode class, and add it to the Polynom. (In the right place, the polynom must be sorted.)
     * Time Complications O(n) a loop that goes through the list that head is pointing to
     * Place complications O(1)
     * 
     * @param p The PolyNode to add
     * 
     * @return The Polynom after the changes
     */
    public Polynom addNode(PolyNode p)
    {
        //if the list is empty, set the first pointer to point to the node that was given
        if(_head==null)
        {
            _head=p;
            return this;
        }
        // if p points to null it will not enter the condition and will return the current polynomial without modifications
        if(p!=null)
        {
            //add the node before the list
            if(p.getPower()>_head.getPower())
            {
                p.setNext(_head);
                _head=p;
                return this;
            }
            //add the coefficient to the first node
            if(p.getPower()==_head.getPower())
            {
                _head.setCoefficient(_head.getCoefficient()+p.getCoefficient());
                return this;
            }
            PolyNode temp=_head;//a temporary pointer to go through the list
            while(temp.getNext()!=null)
            {
                if(p.getPower()<temp.getNext().getPower())
                {
                    temp=temp.getNext();
                }
                else 
                {
                    //p need to be add after temp before the next node
                    if(p.getPower()>temp.getNext().getPower())
                    {
                        p.setNext(temp.getNext());
                        temp.setNext(p);
                        return this;
                    }
                    //add to the coefficient
                    else if(p.getPower()==temp.getNext().getPower())
                    {
                        temp=temp.getNext();
                        temp.setCoefficient(temp.getCoefficient()+p.getCoefficient());
                        return this;
                    }
                }
            }
            //if got to the last node, then p will be set to be after temp
            temp.setNext(p);
        }
        //if q pointed to null, or p was added to the last node,
        return this;
    }

    /**
     * Gets a number and multiply the Polynom in this scalar
     * 
     * Time Complications O(n) a loop that goes through the list that head is pointing to
     * Place complications O(1)
     * 
     * @param num The scalar value
     * 
     * @return The Polynom after the changes
     */
    public Polynom multByScalar(int num)
    {
        //a temporary pointer to the list
        PolyNode temp=_head;
        //go through the all list
        while(temp!=null)
        {
            //for each element, multiply the coefficient by the scalar (by num)
            temp.setCoefficient(temp.getCoefficient() * num);
            //temp will point to the next element of the list
            temp=temp.getNext();
        }
        return this;
    }

    /**
     * Gets a Polynom and adds it to the current Polynom
     * 
     * Time Complications O(n) a loop that goes through the proparty head for the polynom other that was given
     * Place complications O(n) for each node of the list that was given, that is power does not exist in the current node, will build a new polynode 
     * 
     * @param other The Polynom to add 
     * 
     * @return The sum Polynom 
     */
    public Polynom addPol(Polynom other)
    {
        if(other==null || other.getHead()==null)//the polynom that was givan dos not point to any list
            return this;
        PolyNode p=other.getHead();//set the pointer to the list that was given to be p. 
        if(_head==null)
        {
            //will copy only the first node of other, will continue on to the loop and their will copy the rest     
            _head=new PolyNode(p.getPower(),p.getCoefficient());
            p=p.getNext();
        }
        else
        {
            //check if need to add the node at the beginning of the list, before the first node
            if(p.getPower()>_head.getPower())
            {
                _head=new PolyNode(p.getPower(),p.getCoefficient(),_head);
                p=p.getNext();
            }
            //check if need to add to the coefficient of the first node 
            else if(p.getPower()==_head.getPower())
            {
                _head.setCoefficient(_head.getCoefficient()+p.getCoefficient());//add to the coefficient
                p=p.getNext();
            }
        }
        PolyNode temp=_head;//will work on a temporary pointer
        //while still searching through the other list
        while(p!=null)
        {
            //if at the other list there are a few nodes that are not set, that their power are lower than the current lowest power, 
            //will add all what lift to the end of the current list 
            if(temp.getNext()==null)
            {
                temp.setNext(new PolyNode(p.getPower(),p.getCoefficient()));
                p=p.getNext();
                temp=temp.getNext();
            }
            else
            {
                //if the power of p is lower than the power of the next node after temp, so then we don't need to place it here, and will move the pointer temp
                if(p.getPower()<temp.getNext().getPower())
                {
                    temp=temp.getNext();
                }
                //will place the copy of p between temp and the next element, that is the right order
                else if(p.getPower()>temp.getNext().getPower())
                {
                    temp.setNext(new PolyNode(p.getPower(),p.getCoefficient(),temp.getNext()));
                    p=p.getNext();
                    temp=temp.getNext();
                }

                //add to the coefficent, then move p to the next element
                else if(p.getPower()==temp.getNext().getPower())
                {
                    temp=temp.getNext();//move temp to point to the node that is working on, to add to the coefficient
                    temp.setCoefficient(temp.getCoefficient()+p.getCoefficient());//add to the coefficient
                    p=p.getNext();
                }
            }
        }
        //after going through the entire list of other, and added all the polynode will return the up-to-date current list
        return this;
    }

    /**
     * Gets a Polynom and multiply it on the current Polynom
     * 
     * @param other The Polynom to multiply
     * 
     * @return The multiply Polynom
     */
    public Polynom multPol(Polynom other)
    {
        //will not do changes on the current Polynom
        if(other==null || other.getHead()==null)
            return this;

        PolyNode p=other.getHead();//p will point the to head of other
        PolyNode temp=_head;//temp is pointing to the head of the current list
        PolyNode q=null;//the list that will be build from the multiplication (for each node of the current list), will point to the last node in the list
        PolyNode first=null;//will point to the first node in the new list
        Polynom save=new Polynom();//the polynom that will add the new list, sorted 
        //for each node in temp will multiply that element by all the other list
        while(temp!=null)
        {
            //p points to the head of other. will build a new node that q will point onto the last node of the list, first will save the first node.
            //then for each node in p, will set the next of q as a new node then q will point to there. 
            //basically, first will point to a list that has the data of the current node of temp, multiply in each node of p.   
            q=new PolyNode(temp.getPower()+p.getPower(),temp.getCoefficient()*p.getCoefficient(),null);
            first=q;
            p=p.getNext();
            while(p!=null)
            {
                q.setNext(new PolyNode(temp.getPower()+p.getPower(),temp.getCoefficient()*p.getCoefficient(),null));
                q=q.getNext();
                p=p.getNext();
            }
            //will build a new polynom that the head proparty will point to first
            //then will add it to the save polynom, it will be add sorted
            Polynom o=new Polynom(first);
            save.addPol(o);
            //will not save the node that q was pointing to with direct access 
            q=null;
            temp=temp.getNext();
            p=other.getHead();
        }
        //will set the current head to point to the list that we save, that is the multiplication polynom 
        _head=save.getHead();
        return this;
    }

    /**
     * Calculate the polynom differential and return that polynom
     * 
     * @return The differential polynom
     */
    public Polynom differential()
    {
        PolyNode p=_head,first=null,temp=null;
        if(p!=null && p.getPower()>0)
        {
            //will build the first node for the differential
            temp=new PolyNode(p.getPower()-1,p.getCoefficient()*p.getPower(),null);
            //first will point to the first node of the differential polynom
            first=temp;
            p=p.getNext();
            //ignore power of 0 , because the polynom is sorted by power from high to low, if will get to a node with power 0 will stop looping
            //or either will stop when p is pointing to null, (that's mean that the lowest power was greater than 0)
            while(p!=null && p.getPower()>0)
            {
                temp.setNext(new PolyNode(p.getPower()-1,p.getCoefficient()*p.getPower(),null));
                temp=temp.getNext();
                p=p.getNext();
            }
        }
        _head=first;
        return this;
    }

    /**
     * Returns a String that represents this Polynom 
     * 
     * @return String that represents this Polynom
     */
    public String toString()
    {
        String s="";
        PolyNode p=_head;
        while(p!=null)
        {
            if(p.getCoefficient()!=0)
            {
                if(p.getCoefficient()>0 && s!="")//a positive number
                {
                    s+="+";
                }
                s+=p.toString();
            }
            p=p.getNext();
        }
        return s;
    }
}
