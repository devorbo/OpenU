import java.util.Calendar;

public class Program {

	public static void main(String[] args) {
		int numEmp=5;
		Employee[] emp=new Employee[numEmp];
		emp[0]=new CommissionEmployee("Reuven","Coen","111111111",new BirthDate(20,5,1980),50000,0.2);
		emp[1]=new BasePlusCommissionEmployee("Noah", "Levi", "222222222", new BirthDate(6,10,1988), 45000, 0.25, 7000);
		emp[2]=new SalariedEmployee("Yehudit", "Man", "333333333", new BirthDate(12,7,1995), 12000);
		emp[3]=new HourlyEmployee("Ron", "Shevet", "444444444", new BirthDate(3,4,1987), 110, 85);
		emp[4]=new PieceWorker("Leah", "Sliver", "5555555555", new BirthDate(11,11,2001), 820, 24);

		//go through the employees and print their profile
		for(int i=0;i<emp.length;i++)
		{
			Calendar cal=Calendar.getInstance();
			System.out.println(emp[i].toString());
			int addSalary=0;
			if(emp[i].getDate().getMonth()== cal.get(Calendar.MONTH)+1)//if birthday month is current month
			{
				addSalary+=200;//add bonus
				System.out.println("You received a bonus for your birthday month:)");
			}
			System.out.println(String.format("%s $%,.2f","earned:",(emp[i].earnings()+addSalary)));
			System.out.println();
		}
	}

}
