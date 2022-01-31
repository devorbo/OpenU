
public class BirthDate {

	private int day;
	private int month;
	private int year;
	
	private final int MONTH_IN_YEAR=12;
    private final int DAYS_IN_MONTH_JAN=31;
    private final int DAYS_IN_MONTH_APR=30;
    private final int DAYS_IN_MONTH_FEB=28;
    
    private final int MAX_YEAR=2022;
    private final int MIN_YEAR=1900;
    private final int MIN_VALUE=1;
    private final int DEFAULT_YEAR=2000;

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
	
	public BirthDate(int day,int month,int year){
		validYear(year);
		validMonth(month);
		validDay(day,month,year);
		this.year=year;
		this.month=month;
		this.day=day;
	}
	//empty constructor/default constructor
	public BirthDate(){
		this.year=DEFAULT_YEAR;
		this.month=MIN_VALUE;
		this.day=MIN_VALUE;
	}
	public BirthDate(BirthDate date){
		this.year=date.year;
		this.month=date.month;
		this.day=date.day;
	}
	//getter and setters
	public int getYear() {
		return year;
	}
	public void setYear(int year) {
		validYear(year);
		this.year=year;
	}
	public int getMonth() {
		return month;
	}
	public void setMonth(int month) {
		validMonth(month);
		this.month=month;
	}
	public int getDay() {
		return day;
	}
	public void setDay(int day) {
		validDay(day,this.month,this.year);
		this.day=day;
	}
	//check if the year is valid
	private void validYear(int year){
		if(year<MIN_YEAR || year>MAX_YEAR)//assume that it is a valid birth year
			throw new IllegalArgumentException("Year value should be between "+MIN_YEAR+" to "+MAX_YEAR);
	}
	//check if the month is valid
	private void validMonth(int month){
		if(month<MIN_VALUE || month>MONTH_IN_YEAR )
	         throw new IllegalArgumentException("Month value should be between "+MIN_VALUE+" to "+MONTH_IN_YEAR);
	}
	//check if the day at the specific month and year is a correct date
	private void validDay(int day,int month, int year){
		int dayInMonth=MIN_VALUE;//this variable need to be initialized
		//setting the days in the current month
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
                dayInMonth=DAYS_IN_MONTH_FEB+1;
            else                    
                dayInMonth=DAYS_IN_MONTH_FEB;
            break;
        }
        if(day>dayInMonth || day<MIN_VALUE)// the value that was enter is a invalid day
        	throw new IllegalArgumentException("Invalid date");
	}
	
	//get a year and check if that year is a leap year
    private boolean isLeapYear(int year)
    {
        if(year%4==0)
        {
            if(year%100==0 && year%400!=0)
                return false;
            else if(year%400==0)
                return true;
        }
        return false;
    }
    
}
