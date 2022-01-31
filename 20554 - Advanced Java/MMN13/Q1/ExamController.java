import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;

import javax.swing.JOptionPane;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.ToggleGroup;

public class ExamController {

    @FXML
    private Button newQuiz;

    @FXML
    private Label question;

    @FXML
    private RadioButton answer1;

    @FXML
    private ToggleGroup Questions;

    @FXML
    private RadioButton answer2;

    @FXML
    private RadioButton answer3;

    @FXML
    private RadioButton answer4;
    
    @FXML
    private Button continueBtn;
    
    private RadioButton[] quList;
    private String correct;//correct answer for current question
    private int countCorrect=0;
    private int countQuestion=0;
    private Scanner input;

    @FXML
    void initialize() {
        assert newQuiz != null : "fx:id=\"newQuiz\" was not injected: check your FXML file 'Exam.fxml'.";
        assert question != null : "fx:id=\"question\" was not injected: check your FXML file 'Exam.fxml'.";
        assert answer1 != null : "fx:id=\"answer1\" was not injected: check your FXML file 'Exam.fxml'.";
        assert Questions != null : "fx:id=\"Questions\" was not injected: check your FXML file 'Exam.fxml'.";
        assert answer2 != null : "fx:id=\"answer2\" was not injected: check your FXML file 'Exam.fxml'.";
        assert answer3 != null : "fx:id=\"answer3\" was not injected: check your FXML file 'Exam.fxml'.";
        assert answer4 != null : "fx:id=\"answer4\" was not injected: check your FXML file 'Exam.fxml'.";

        radioButtonList();
        beginQuiz();
    }
    //save the radio buttons as a list
    void radioButtonList(){
    	quList=new RadioButton[4];
		quList[0]=answer1;
		quList[1]=answer2;
		quList[2]=answer3;
		quList[3]=answer4;
    }
    void beginQuiz(){
    	countCorrect=0;
    	countQuestion=0;
    	try {
			input = new Scanner(new File("exam.txt"));
			setQuestion();			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
    }
    void setQuestion() {
    	if (!input.hasNext()){
    		endQuiz();
    	}
    	question.setText(input.nextLine());
		//deal with the answers for the question
		String[] lines=new String[4];
		int j;
		for(j=0;j<lines.length&&input.hasNext();j++){
			lines[j]=input.nextLine();//save answers
		}
		if(j<lines.length-1){//exit loop because finish reading file
			endQuiz();
			return;
		}
		correct=lines[0];//the correct answer
		Random rnd=new Random();
		//shuffle the answers
		for(int i=0;i<5;i++){
			int index1=rnd.nextInt(lines.length);
			int index2=rnd.nextInt(lines.length);
			String temp=lines[index1];
			lines[index1]=lines[index2];
			lines[index2]=temp;
		}		
		//write to the app the answers option 
		for(int i=0;i<quList.length;i++){
			quList[i].setText(lines[i]);
		}
		for(int i=0;i<quList.length;i++){
    		quList[i].setDisable(false);//enable the radio buttons
    		quList[i].setSelected(false);
    		
    	}	
		continueBtn.setVisible(false);
   	}
    
    @FXML
    void answerChecked(ActionEvent event) {
    	countQuestion++;
    	String message="";
    	RadioButton selectedRadioButton=(RadioButton)Questions.getSelectedToggle();
    	String selectedValue=selectedRadioButton.getText();
    	if(selectedValue.equals(correct)){//compare choice to the correct  
    		message+="Correct answer !!";
        	JOptionPane.showMessageDialog(null, message, "Respond", JOptionPane.INFORMATION_MESSAGE);

    		countCorrect++;
    	}
    	else{
    		message+="Uncorrect :(";
        	JOptionPane.showMessageDialog(null, message, "Respond", JOptionPane.ERROR_MESSAGE);

    	}
    	
    	for(int i=0;i<quList.length;i++){
    		quList[i].setDisable(true);//disable the ability to answer again
    	}
    	continueBtn.setVisible(true);
    }

    @FXML
    void newQuizPress(ActionEvent event) {
    	beginQuiz();
    	
    }
    @FXML
    void continuePress(ActionEvent event) {
    	setQuestion();
    }
    void endQuiz(){
    	//input.close();
    	for(int i=0;i<quList.length;i++){
    		quList[i].setText("answer");
    	}
    	String message="";
    	message="Your grade is ";
    	double grade=((double)countCorrect/countQuestion)*100;
    	
    	String value=String.format("%.2f", grade);
    	message+=value+"%";
    	if(grade==100)
    		message+="\nPerfect score!";
    	message+="\nWould you like to play again?";
    	int choice=JOptionPane.showConfirmDialog(null, message, "End Quiz", JOptionPane.YES_NO_OPTION);
    	if(choice==0)//yes
    		beginQuiz();
    	else{	
    		javafx.application.Platform.exit();
    	}
    }
    
    
   
   


}
