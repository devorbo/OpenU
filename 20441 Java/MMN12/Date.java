/**
 * This class represents a Date object
 * 
 * @auther Devora Borowski
 * @version 7/12/2019
 */
public class Date
{ 
    private int _day;
    private int _month;
    private int _year;

    private final int MONTH_IN_YEAR=12;
    private final int DAYS_IN_MONTH_JAN=31;
    private final int DAYS_IN_MONTH_APR=30;
    private final int DAYS_IN_MONTH_FEB=28;
    private final int DAYS_IN_MONTH_FEB_LEAP=29;
    private final int DAYS_IN_WEEK=7;
    private final int MAX_YEAR=9999;
    private final int MIN_YEAR=1000;
    private final int MIN_VALUE=1;
    private final int DEFAULT_YEAR=2000;
    private final int LEAP_YEAR=4;
    private final int CENTURY=100;
    private final int LEAP_UNLESS=400;
    private final int REMAINDER=0;
    private final int TENS=10;
    private final int ADD_DAY=1;
    //months of the year
    private final int JAN=1;
    private final int FEB=2;
    private final int MAR=3;
    private final int APR=4;
    private final int MAY=5;
    private final int JUN=6;
    private final int JUL=7;
    private final int AUG=8;
    private final int SEP=9;
    private final int OCT=10;
    private final int NOV=11;
    private final int DEC=12;

    /**
     * creates a new Date object if the date is valid, otherwise creates the date 1/1/2000
     * 
     * @param day - the day in the month (1-31)
     * @param month - the month in the year (1-12)
     * @param year - the year (4 digits)
     */
    public Date(int day,int month, int year)
    {
        if(validDate(day,month,year))
        {
            _day=day;
            _month=month;
            _year=year;
        }
        //if one of the parameters of the date is invalid will build a defalt date 
        else
        {
            _day=MIN_VALUE;
            _month=JAN;
            _year=DEFAULT_YEAR;
        }
    }

    /**
     * copy constructor
     * 
     * @param other - the date to be copied
     */
    public Date (Date other) 
    {
        _day=other._day;
        _month=other._month;
        _year=other._year;
    }

    /**
     * gets the day
     * 
     * @return the day
     */
    public int getDay()
    {
        return this._day;
    }

    /**
     * sets the day (only if date remains valid)
     * 
     * @param dayToSet - the day value to be set
     */
    public void setDay(int dayToSet)
    {
        if(validDate(dayToSet,_month,_year))
        {
            _day=dayToSet;
        }
    }

    /**
     * gets the month
     * 
     * @return the month
     */
    public int getMonth()
    {
        return this._month;
    }

    /**
     * sets the month (only if date remains valid)
     * 
     * @param monthToSet - the month value to be set
     */
    public void setMonth(int monthToSet)
    {
        if(validDate(_day,monthToSet,_year))
        {
            _month=monthToSet;
        }
    }

    /**
     * gets the year
     * 
     * @return the year
     */
    public int getYear()
    {
        return this._year;
    }

    /**
     * sets the year (only if date remains valid)
     * 
     * @param yearToSet - the year value to be set
     */
    public void setYear(int yearToSet)
    {
        if(validDate(_day,_month,yearToSet))
        {
            _year=yearToSet;
        }
    }

    /**
     * check if 2 dates are the same
     * 
     * @param other - the date to compare this date to
     * 
     * @return true if the dates are the same
     */
    public boolean equals(Date other)
    {
        return (_day==other._day && _month==other._month && _year==other._year);
    }

    /**
     * check if this date is before other date
     * 
     * @param other - date to compare this date to
     * 
     * @return true if this date is before other date
     */
    public boolean before(Date other)
    {
        if(_year<other._year)
            return true;
        else if(_year==other._year)
        {
            if(_month<other._month)
                return true;
            else if(_month==other._month)
                if(_day<other._day)
                    return true;
        }
        return false;
    }

    /**
     * check if this date is after other date
     * 
     * @param other - date to compare this date to
     * 
     * @return true if this date is after other date
     */
    public boolean after(Date other)
    {
        return other.before(this);
    }

    /**
     * calculates the difference in days between two dates
     * 
     * @param other - the date to calculate the difference between
     * 
     * @return the number of days between the dates
     */
    public int difference(Date other)
    {
        int d1 =calculateDate(other._day,other._month,other._year);
        int d2 =calculateDate(_day,_month,_year);
        return Math.abs(d2-d1);
    }

    /**
     * calculate the date of tomorrow
     * 
     * @return the date of tomorrow
     */
    public Date tomorrow()
    {
        int day=_day+ADD_DAY;
        int month=_month;
        int year=_year;
        if(!validDate(day,month,year))
        {
            day=MIN_VALUE;
            month++;
            if(!validDate(day,month,year))
            {
                month=MIN_VALUE;
                year++;
                if(!validDate(day,month,year))
                    year=DEFAULT_YEAR;
            }
        }
        return new Date(day,month,year);
    }

    /**
     * calculate the day of the week that this date occurs on 0-Saturday 1-Sunday 2-Monday etc.
     * 
     * @return the day of the week that this date occurs on
     */
    public int dayInWeek()
    {
        int month=_month;
        int year=_year;
        if (month < MAR) 
        {             
            year--;             
            month = month + MONTH_IN_YEAR;         
        }
        int y=year%CENTURY;
        int c=year/CENTURY;  
        int dayInWeek=(_day+(26*(month+1))/10+y+y/4+c/4-2*c);        
        return Math.floorMod(dayInWeek,DAYS_IN_WEEK);
    }

    /**
     * returns a String that represents this date
     * 
     * @override toString in class java.lang.Object
     * 
     * @return String that represents this date in the following format: day/month/year for example: 02/03/1998
     */
    public String toString()
    {
        String s="";
        if(_day<TENS)
            s+="0";
        s+=_day+"/";
        if(_month<TENS)
            s+="0";
        s+=_month+"/";
        s+=_year;
        return s;
    }
    
     // computes the day number since the beginning of the Christian counting of years
    private int calculateDate( int day, int month, int year)
    {
        if (month < 3) 
        {
            year--;             
            month = month + 12; 
        }
        return 365 * year + year/4 - year/100 + year/400 + ((month+1) * 306)/10 + (day - 62); 
    }
    
    //get a date and check if is a valid date
    private boolean validDate(int day,int month,int year)
    {
        int dayInMonth=MIN_VALUE;//this variable need to be initialized
        if (year>=MIN_YEAR && year<=MAX_YEAR)//if year is valid
            if(month<=MONTH_IN_YEAR && month>=MIN_VALUE)
            {
                //for each month, setting the days in the month
                switch(month)
                {
                    case JAN:
                    case MAR:
                    case MAY:
                    case JUL:
                    case AUG:
                    case OCT:
                    case DEC:dayInMonth=DAYS_IN_MONTH_JAN;break;

                    case APR:
                    case JUN:
                    case SEP:
                    case NOV:dayInMonth=DAYS_IN_MONTH_APR;break;

                    case FEB:
                    if(isLeapYear(year))
                        dayInMonth=DAYS_IN_MONTH_FEB_LEAP;
                    else                    
                        dayInMonth=DAYS_IN_MONTH_FEB;
                    break;
                }
                if(day<=dayInMonth && day>=MIN_VALUE)
                    return true;
            }
        return false; 
    }
    
    //get a year and check if that year is a leap year
    private boolean isLeapYear(int year)
    {
        if(year%LEAP_YEAR==REMAINDER)
        {
            if(year%CENTURY==REMAINDER && year%LEAP_UNLESS!=REMAINDER)
                return false;
            if(year%CENTURY!=REMAINDER||year%LEAP_UNLESS==REMAINDER)
                return true;
        }
        return false;
    }
}
