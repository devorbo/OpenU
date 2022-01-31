import java.util.Random;

public class WordList {
	private String[] list={"apple","color","computer","school","sky","window","kitchen"};
	public WordList(){
		
	}
	public String chooseWord()
	{
		Random rnd=new Random();
		int num=list.length;
		int choosed=rnd.nextInt(num);// raffle a number, that will be the index in the array of the word
		return list[choosed];// word chosen for the specific game
	}
}
