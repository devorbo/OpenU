import javax.swing.JOptionPane;

public class Game {

	public static void main(String[] args)
	{
		Word w1=new Word();
		int count=0;
		while(!String.valueOf(w1.getGuessWord()).toLowerCase().equals(w1.getRndWord()))//didn't guess yet the entire chosen word
		{
			String message="Guessing Game\n";
			for(int i=0;i<w1.lenghtWord();i++)// print the word, with the letters that were guessed until now
			{
				message+=w1.getGuessWord()[i]+" ";
			}
			message+="\n"+w1.getAbcList().toString();
			message+="\nGuess a letter";
			
			String guess=JOptionPane.showInputDialog(null,message,"Guessing Game",JOptionPane.DEFAULT_OPTION);
			if(guess.length()>1)
			{
				JOptionPane.showMessageDialog(null, "Input is to long", "Error", JOptionPane.ERROR_MESSAGE);
			}
			else if(guess.length()==0)
			{
				JOptionPane.showMessageDialog(null, "No input was entered", "Error", JOptionPane.ERROR_MESSAGE);
			}
			else// input is exactly one character
			{
				char letter=guess.toLowerCase().charAt(0);
				if(letter>='a'&& letter <='z')// the char is a letter
				{
					if(w1.getAbcList().contains(letter))
					{
						if(!w1.letterExistInWord(letter))//check if the letter is in the chosen word
							count++;// count letters that are not in the word 
					}
					else//the letter was in used
					{
						JOptionPane.showMessageDialog(null, "You have used this letter earlier", "Error", JOptionPane.ERROR_MESSAGE);
					}
				}
				else
				{
					JOptionPane.showMessageDialog(null, "Incorrect input", "Error", JOptionPane.ERROR_MESSAGE);
				}
			}
			
		}
		JOptionPane.showMessageDialog(null, "Game Over\nIncorrect guesses: "+count, "Game Over", JOptionPane.CLOSED_OPTION);

	}
}
