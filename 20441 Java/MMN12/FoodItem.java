/**
 * This class represents a FoodItem object
 * 
 * @auther Devora Borowski
 * @version 7/12/2019
 */
public class FoodItem
{
    private String _name;
    private long _catalogueNumber; 
    private int _quantity;
    private Date _productionDate;
    private Date _expiryDate;
    private int _minTemperature;
    private int _maxTemperature;
    private int _price;

    private final String DEFAULT_NAME="item";
    private final long MIN_CATALOGUE_NUMBER=1000;
    private final long MAX_CATALOGUE_NUMBER=9999;
    private final int MIN_QUANTITY=0;
    private final int MIN_PRICE=1;

    /**
     * creates a new FoodItem object
     * If one of the parameters is illegal, will set that parameter to be a valid parameter or a default response
     * 
     * @param name - name of food item
     * @param catalogueNumber - catalogue number of food item
     * @param quantity - quantity of food item
     * @param productionDate - production date
     * @param expiryDate - expiry date
     * @param minTemperature - minimum storage temperature
     * @param maxTemperature - maximum storage temperature
     * @param price - unit price
     */
    public FoodItem(String name,long catalogueNumber,int quantity,Date productionDate,Date expiryDate,int minTemperature,int maxTemperature,int price)
    {
        if(validName(name))
            _name=name;
        else
            _name=DEFAULT_NAME;

        if(validCatalogueNumber(catalogueNumber))
            _catalogueNumber=catalogueNumber;            
        else
            _catalogueNumber=MAX_CATALOGUE_NUMBER;

        if(validQuantity(quantity))
            _quantity=quantity;
        else
            _quantity=MIN_QUANTITY;

        _productionDate=new Date(productionDate);
        if(validProOrExDate(productionDate,expiryDate))
            _expiryDate=new Date(expiryDate);   
        else
            _expiryDate=productionDate.tomorrow();

        if(validTemperature(minTemperature,maxTemperature))
        {
            _minTemperature=minTemperature;
            _maxTemperature=maxTemperature;
        }
        else
        {
            _minTemperature=maxTemperature;
            _maxTemperature=minTemperature;
        }

        if(validPrice(price))
            _price=price;
        else
            _price=MIN_PRICE;    
    }

    /**
     * copy contructor
     * 
     * @param other - the food item to be copied
     */
    public FoodItem(FoodItem other)
    {
        _name=other._name;
        _catalogueNumber=other._catalogueNumber;
        _quantity=other._quantity;
        _productionDate=new Date(other._productionDate);
        _expiryDate=new Date(other._expiryDate);
        _minTemperature=other._minTemperature;
        _maxTemperature=other._maxTemperature;
        _price=other._price;
    }

    /**
     * gets the name
     * 
     * @return the name
     */
    public String getName()
    {
        return _name;
    }

    /**
     * gets the catalogue number
     * 
     * @return the catalogue number
     */
    public long getCatalogueNumber()
    {
        return _catalogueNumber;
    }

    /**
     * gets the quanity
     * 
     * @return the quantity
     */
    public int getQuantity()
    {
        return _quantity;
    }

    /**
     * set the quantity (only if not negative)
     * 
     * @param n - the quantity value to be set
     */
    public void setQuantity (int n)
    {
        if(validQuantity(n))
            _quantity=n;
    }

    /**
     * gets the production date
     * 
     * @return the production date
     */
    public Date getProductionDate()
    {
        return new Date(_productionDate);
    }

    /**
     * set the production date (only if not after expiry date)
     * 
     * @param d - production date value to be set
     */
    public void setProductionDate (Date d) 
    {
        if (validProOrExDate(d,_expiryDate))
            _productionDate=new Date(d);
    }

    /**
     * gets the expiry date
     * 
     * @return the expiry date
     */
    public Date getExpiryDate()
    {
        return new Date(_expiryDate);
    }

    /**
     * set the expiry date (only if not befor production date)
     * 
     * @param d - expiry date value to be set
     */
    public void setExpiryDate (Date d) 
    {
        if (validProOrExDate(_productionDate,d))
            _expiryDate=new Date(d);
    }

     /**
     * gets the minimum temperature
     * 
     * @return the minimum temperature
     */
    public int getMinTemperature()
    { 
        return _minTemperature;
    }
    
     /**
     * gets the maximum temperature
     * 
     * @return the maximum temperature
     */
    public int getMaxTemperature()
    {
        return _maxTemperature;
    }

    /**
     * gets the unit price
     * 
     * @return the unit price
     */
    public int getPrice()
    { 
        return _price;
    }

    /**
     * set the price (only if positive)
     * 
     * @param n - price value to be set
     */
    public void setPrice (int n)
    {
        if(validPrice(n))
            _price=n;
    }

    /** 
     * check if 2 food items are the same (excluding the quantity values)
     * 
     * @param other - the food item to compare this food item to
     * 
     * @return true if the food items are the same
     */
    public boolean equals(FoodItem other) 
    {
        return ((_name.equals(other._name)) && (_catalogueNumber==other._catalogueNumber) && (_productionDate.equals(other._productionDate)) 
            && (_expiryDate.equals(other._expiryDate)) && (_minTemperature==other._minTemperature) && (_maxTemperature==other._maxTemperature)
            && (_price==other._price));
    }

    /**
     * check if this food item is older than other food item
     * 
     * @param other - food item to compare this food item to
     * 
     * @return true if this food item is older than other date
     */
    public boolean olderFoodItem(FoodItem other)
    {
        return _productionDate.before(other._productionDate);
    }

    /**
     * returns the number of units of products that can be purchased for a given amount
     * if there is not enough in stock will return the quantity that is available
     * 
     * @param amount - amount to purchase
     * 
     * @return the number of units can be purchased
     */
    public int howManyItems(int amount)
    {
        if(amount<=MIN_QUANTITY)
            return MIN_QUANTITY;
        if(amount>_quantity*_price)
            return _quantity;
        return amount/_price;    
    }

    /**
     * check if this food item is cheaper than other food item
     * 
     * @param other - food item to compare this food item to
     * 
     * @return true if this food item is cheaper than other date
     */
    public boolean isCheaper(FoodItem other)
    {
        return (_price<other._price);
    }

    /**
     * check if this food item is fresh on the date that was insert
     * 
     * @param d - date to check
     * 
     * @return true if this food item is fresh on the date d
     */
    public boolean isFresh(Date d)
    {
        return ((d.after(_productionDate)|| d.equals(_productionDate)) && ((d.before(_expiryDate))||(d.equals(_expiryDate))));//including these dates
    }

    /**
     * returns a String that represents this food item
     * 
     * @return String that represents this food item in the following format:
     * FoodItem: milk CatalogueNumber: 1234 ProductionDate: 14/12/2019 ExpiryDate: 21/12/2019 Quantity: 3
     */
    public String toString()
    {
        return "FoodItem: "+ _name+"\tCatalogueNumber: "+ _catalogueNumber+"\tProductionDate: "+_productionDate+
        "\tExpiryDate: "+_expiryDate+"\tQuantity: "+_quantity;
    }
    
    //checks if an item name has a value 
    private boolean validName(String name)
    {
        return (!name.equals(""));
    }
    
    //checks if the item catalogue number is valid, that means a 4 digit number
    private boolean validCatalogueNumber(long catalogueNumber)
    {
        return (catalogueNumber<=MAX_CATALOGUE_NUMBER && catalogueNumber>=MIN_CATALOGUE_NUMBER);
    }

    //checks if the quantity is not a negative number
    private boolean validQuantity(int quantity)
    {
        return (quantity>=MIN_QUANTITY);
    }

    //checks if the expiry date is not before the production date
    private boolean validProOrExDate(Date productionDate,Date expiryDate)
    {
        return !(expiryDate.before(productionDate));
    }

    //checks that the min temperature is not higher than the max temperature
    private boolean validTemperature(int minTemperature,int maxTemperature)
    {
        return (minTemperature<=maxTemperature);
    }

    //checks that a price is a positive number
    private boolean validPrice(int price)
    {
        return (price>=MIN_PRICE);
    }

}
