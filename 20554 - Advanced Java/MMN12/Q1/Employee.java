// Employee abstract superclass.

public abstract class Employee {
    private final String firstName;
    private final String lastName;
    private final String socialSecurityNumber;
    private BirthDate date;

    // constructor
    public Employee(String firstName, String lastName, 
       String socialSecurityNumber,BirthDate date) {
       this.firstName = firstName;
       this.lastName = lastName;
       this.socialSecurityNumber = socialSecurityNumber;
       this.date=new BirthDate(date);
    } 
    public BirthDate getDate() {
		return date;
	}

	public void setDate(BirthDate date) {
		this.date = new BirthDate(date);
	}

    // return first name
    public String getFirstName() {return firstName;}

    // return last name
    public String getLastName() {return lastName;}

    // return social security number
    public String getSocialSecurityNumber() {return socialSecurityNumber;}

    // return String representation of Employee object
    @Override
    public String toString() {
    	String bDay=""+date.getDay()+"/"+date.getMonth()+"/"+date.getYear();
       return String.format("%s %s%nbirth date: %s\nsocial security number: %s", 
          getFirstName(), getLastName(),bDay, getSocialSecurityNumber());
    }
 
    // abstract method must be overridden by concrete subclasses
    public abstract double earnings(); // no implementation here
} 

