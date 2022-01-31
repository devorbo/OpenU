import java.util.ArrayList;


public class Word {
	private String rndword="";
	private char[] guessWord;
	private ArrayList<Character> abcList;
	private int numAbc=26;
	public Word(){
		WordList wL=new WordList();
		rndword=wL.chooseWord();// the chosen word
	    guessWord=new char[rndword.length()];// array of char for the guessing game
		for(int i=0; i<guessWord.length;i++ )
		{
			guessWord[i]='_';// initialize the chosen word with lines
		}
		//list that will contain the alphabet letters
		abcList=new ArrayList<Character>();
		for(int i=0;i<numAbc;i++)
		{
			abcList.add((char)('a'+i));
		}
	}
	public char[] getGuessWord(){
		return guessWord;
	}
	public ArrayList<Character> getAbcList(){
		return abcList;
	}
	public String getRndWord(){
		return rndword;
	}
	public int getNumAbc(){
		return numAbc;
	}
	public int lenghtWord(){
		return guessWord.length;
	}
	
	public boolean letterExistInWord(char letter){	
		boolean found=false;
		for(int i=0;i<guessWord.length;i++)
		{
			if(rndword.charAt(i)==letter)
			{
				found=true;//letter exist in the word
				guessWord[i]=letter;//replace the line with the letter
			}
		}
		removeFromAbcList(letter);	
		return found;
	}
	public void removeFromAbcList(char letter){
		abcList.remove((Character)letter);
	}
}
