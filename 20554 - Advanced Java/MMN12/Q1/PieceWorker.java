
public class PieceWorker extends Employee {

	private int numItems;
	private double payItem;
	
	public PieceWorker(String firstName, String lastName,
		      String socialSecurityNumber,BirthDate date, int numItems, double payItem){
		super(firstName, lastName, socialSecurityNumber,date);
		
		if (numItems < 0) { // validate num items
	         throw new IllegalArgumentException("Number of items should be a positive number");
	      }
		if (payItem < 0) { // validate payment per items
	         throw new IllegalArgumentException("Payment per each item should be a positive number");
	      }
		this.numItems=numItems;
		this.payItem=payItem;
	}
	public int getNumItems(){return numItems;}
	public void setNumItems(int numItems){
		if (numItems < 0) { // validate num items
	         throw new IllegalArgumentException("Number of items should be a positive number");
	      }
		this.numItems=numItems;
	}
	public double getPayItem(){return payItem;}
	public void setPayItem(double payItem){
		if (payItem < 0) { // validate payment per items
	         throw new IllegalArgumentException("Payment per each item should be a positive number");
	      }
		this.payItem=payItem;
	}
	
	@Override                                                           
	public double earnings(){
		return numItems * payItem;
	}
	// return String representation of PieceWorker object              
	   @Override                                                             
	   public String toString(){
		   return String.format("piece worker: %s%n%s: %d; %s: $%,.2f", 
			         super.toString(), "number of items", getNumItems(),                     
			         "payment per item", getPayItem());
	   }
	
}
