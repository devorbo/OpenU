/**
 *  This class represents a Stock object
 *  The object take track of food items in this stock
 *
 * @author Devora Borowski
 * @version 24/12/2019
 */
public class Stock
{
    FoodItem[] _stock;
    int _noOfItem=0;

    private final int ARRAY_MAX_LENGTH=100;

    /**
     * Creates a new Stock object
     */
    public Stock()
    {
        _stock=new FoodItem[ARRAY_MAX_LENGTH];
    }

    /**
     * Gets the number of items
     * 
     * @return the number of item
     */
    public int getNumOfItems()
    {
        return _noOfItem;
    }

    /**
     * Will add a food item object to the stock
     * 
     * @param newItem the food item to add into the stock
     * 
     * @return true if the item was added successfully and false if not
     */
    public boolean addItem(FoodItem newItem)
    {
        //If the product is already in stock, will add to that item the quantity that was inserted for this item
        for(int i=0;i<_stock.length && _stock[i]!=null;i++)
        {
            //When the name and code are the same, the product will appear at most once in a string
            if(newItem.equals(_stock[i]))//((newItem.getCatalogueNumber()==_stock[i].getCatalogueNumber()))
            {
                _stock[i].setQuantity(_stock[i].getQuantity()+newItem.getQuantity());
                return true;
            }
        }
        //if the stock array is full can not add the item
        int lastIndex=lastItemIndex();
        if(lastIndex==_stock.length)
            return false;  

        // will add the item in the right place and add to the _noOfItem property +1 here, since from here on it will be added successfully
        _noOfItem++;

        //when the stock array is empty the item is added straight without testing
        if(lastIndex==0)
        {
            _stock[0]=new FoodItem(newItem);
            return true;
        }

        // find where the new item should be - based on the catalogue number
        for(int i=lastIndex-1; i>=0;i--)
        {
            //if the current catalogue number of the food item is higher or equal from the new item that was inserted
            //wiil move the food item one place forward
            if(_stock[i].getCatalogueNumber()>=newItem.getCatalogueNumber())
                _stock[i+1]=new FoodItem(_stock[i]);
            //if the catalogue number is lower will insert the new food item in the array after this item
            else if(_stock[i].getCatalogueNumber()<newItem.getCatalogueNumber())
            {
                _stock[i+1]=new FoodItem(newItem);
                return true;
            }
        }
        //if the new item needs to be the first in the list according to the catalogue number
        //will move each element one forward and will add the item to the first place
        _stock[0]=new FoodItem(newItem);
        return true;
    }

    /**
     * A product will enter the order list if the quantity it has in stock is small than amount
     * 
     * @param amount The minimum quantity that the product must have
     * 
     * @return a list of items that need to be ordered
     */
    public String order(int amount)
    {
        String missing="";
        int productQuantity=0;
        boolean firstInARow=true,sameItem=false,firstToOrder=true;
        //look through all array data
        for(int i=0;i<_stock.length && _stock[i]!=null;i++)
        {
            //when the item is the first item from multiple similar products  
            //will set the quantity
            if(firstInARow)
            {
                productQuantity=_stock[i].getQuantity();
                firstInARow=false;
            }
            //if the next element in tha array is null cannot compare it
            if(_stock[i+1]!=null)
            {
                //If the current item and the next item are similar, it will add the quantity to the product
                if((_stock[i].getName().equals(_stock[i+1].getName()))&&(_stock[i].getCatalogueNumber()==_stock[i+1].getCatalogueNumber()))
                {
                    productQuantity+=_stock[i+1].getQuantity();
                    sameItem=true;
                }
                //if not wiil set that they are not similar
                //and that will reset the product quantity
                else
                {
                    sameItem=false;
                    firstInARow=true;
                }
            }
            //when the item is not like the following one or either this is the last element in the array that is filled 
            if(!sameItem || i==_stock.length-1)
            {
                if(productQuantity<amount)
                {
                    if(!firstToOrder)
                        missing+=", ";
                    else
                        firstToOrder=false;
                    missing+=_stock[i].getName();
                }
            }
        }
        return missing;
    }

    /**
     * Each product in which the temperature is within the temperature range - will sum up the quantity of product
     *
     *@param temp This is a temperature in a particular refrigerator
     *
     *@return how many items can be store in that temperature
     */
    public int howMany(int temp)
    {
        int sum=0;
        for(int i=0;i<_stock.length && _stock[i]!=null;i++)
        {
            //if the temperature that was inserted is in the temperature range of this product
            if(temp>=_stock[i].getMinTemperature() && temp<=_stock[i].getMaxTemperature())
            {
                sum+=_stock[i].getQuantity();
            }
        }
        return sum;
    }

    /**
     * Deletes from stock all food products whose expiry date is before the date that is inserted
     * 
     * @param d the date that will check the expiry date
     */
    public void removeAfterDate(Date d)
    {
        int i=0;
        while(i<_stock.length && _stock[i]!=null)
        {
            if(d.after(_stock[i].getExpiryDate()))
            {
                //remove this item from the array
                removeElement(i);
            }
            else
            {
                //will continue checking the array
                i++;
            }
        }
        //_noOfItem--;
    }

    /**
     * Looks for the most expensive product in stock
     * 
     * @return the most expensive item
     */
    public FoodItem mostExpensive()
    {
        FoodItem max;
        //if the array is empty will return a pointer to a null FoodItem
        if(_stock[0]!=null)
            max=new FoodItem(_stock[0]);
        else 
            return null;
        for(int i=1;i<_stock.length && _stock[i]!=null;i++)
        {
            if(_stock[i].getPrice()>max.getPrice())
            {
                max=new FoodItem(_stock[i]);
            }
        }
        return max;
    }

    /**
     * Returns how many items are in stock
     * 
     * @return quantity of items
     */
    public int howManyPieces()
    {
        int sum=0;
        for(int i =0;i<_stock.length && _stock[i]!=null;i++)
        {
            //will sum up the quantity
            sum+=_stock[i].getQuantity();
        }
        return sum;
    }

    /**
     * Update the stock after a sale
     * 
     * @param itemsList list of strings that represent the products that were sold
     */
    public void updateStock(String[] itemsList) 
    {
        int k=0;
        boolean found=false;
        //go through the items list and subtract the insert items from the stock
        while(k<itemsList.length)
        {
            //go through the array to find the element that match
            for(int i=0;!found && i<_stock.length && _stock[i]!=null;i++)
            {
                if(_stock[i].getName().equals(itemsList[k]))
                {
                    _stock[i].setQuantity(_stock[i].getQuantity()-1);
                    //if after the update the quantity is 0 will remove this element from the array 
                    if(_stock[i].getQuantity()==0)
                        removeElement(i);
                    found=true;
                    k++;
                }
            }
            //if this item that was insert is not in the Stock object will continue on and will not miss up the program
            if(!found)
                k++;
            found=false;
        }
    }

    /**
     * Returns the temperature at which should be the refrigerator that contains all the products
     * If there is such a range, the method returns the minimum temperature in the range. 
     * If it is not possible to find a temperature that suits all products in the refrigerator, the max integar value will be returned.
     * 
     * @return the temperatureof of the refrigerator that contains all the products
     */
    public int getTempOfStock()
    {
        if(_stock[0]==null)
        {
            return Integer.MAX_VALUE;
        }
        //will set the range as the temperature of the first item
        int minRange=_stock[0].getMinTemperature();
        int maxRange=_stock[0].getMaxTemperature();

        for(int i=1;i<_stock.length && _stock[i]!=null;i++)
        {
            if(_stock[i].getMinTemperature()>minRange)
            {
                minRange=_stock[i].getMinTemperature();
            }
            if(_stock[i].getMaxTemperature()<maxRange)
            {
                maxRange=_stock[i].getMaxTemperature();
            }
        }

        if(minRange<=maxRange)
        //will return tha minimum value in the range
            return minRange;
        //if there is not a temperature range that contains all the products the max integar value will be returned
        return Integer.MAX_VALUE;
    }

    /**
     * returns a String that represents this Stock 
     * 
     * @return String that represents this Stock
     */
    public String toString()
    {
        String s="";
        for(int i =0;i<_stock.length && _stock[i]!=null;i++)
        {
            s+=_stock[i].toString()+"\n";
        }
        return s;
    }

    //return the index of the last element at the array that is with data
    private int lastItemIndex()
    {
        for(int j=0;j<_stock.length;j++)
        {
            if( _stock[j]==null)
                return j;
        }
        //if the array is full will return tha length of the array
        return _stock.length;
    }

    //remove an element in a certain index
    private void removeElement(int index)
    {
        for(int i=index;i<_stock.length-1 && _stock[i]!=null;i++)
        { 
            if(_stock[i+1]!=null)
            //for each element will build a new FoodItem that have the data of the next element
                _stock[i]=new FoodItem(_stock[i+1]);
            else
            //the last element will point to null
                _stock[i]=null;
        }
        _noOfItem--;
    }

}
