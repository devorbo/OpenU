import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;

public class CalculatorController {

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private TextField typeText;
    
    private double calc1=0;
    private double num=0;
    private char operator;
    private char opt2;
    private boolean firstCalc=true;


    @FXML
    void backspcePress(ActionEvent event) {
    	String text=typeText.getText();
    	if(text.equals(""))
    		return;
    	text=text.substring(0, text.length()-1);//backspace->removing the last character
    	typeText.setText(text);
    }

    @FXML
    void clearPress(ActionEvent event) {
    	reset();
    }
    
    @FXML
    void dotPress(ActionEvent event) {
		String text=typeText.getText();
		if(!isOperator(text.charAt(0))){//it is illegal to have a dot after operator
			for(int i=0;i<text.length();i++){
				if(text.charAt(i)=='.')//contain a dot already
					return;
    		}
    		typeText.setText(typeText.getText()+".");//add the dot	
		}
    }

    @FXML
    void numPress(ActionEvent event) {
    	if(opt2=='=')//last operator
    		reset();// reset for a new calculation
    	if(checkOperator()){//was operator before, then calculate the numbers until now
    		calculateTwoNumbers();
    	}
    	typeText.setText(typeText.getText()+((Button)event.getSource()).getText());
    }

    @FXML
    void operatorPress(ActionEvent event) {
    	operator=opt2;//current operator
    	if(!checkOperator()&& typeText.getText().length()>0){//wasn't a operator before
    		num=Double.parseDouble(typeText.getText());//save the number that was entered before
    	}
    	char temp=((Button)event.getSource()).getText().charAt(0);
    	if(temp=='='){
    		if(firstCalc)//entered just one number
     		{
     			typeText.setText(""+num);//print the number
     			return;
     		}
        	calculateTwoNumbers();
        	typeText.setText(""+calc1);//print the calculation
    	}
    	 else
    	 {
    		 typeText.setText(((Button)event.getSource()).getText());
    	     System.out.println(typeText.getText());
    	 }
    	 opt2=temp;//save next operator for next calculation
    }

    @FXML
    void plusminusPress(ActionEvent event) {
    	String text=typeText.getText();
    	if(text.length()>0)
    	{
    		if(text.charAt(0)=='-'){
        		text=text.substring(1, text.length());//remove minus sign
        		typeText.setText(text);
        	}
        	else{
        		String minus="-";
        		text=minus.concat(text);//add minus sign to number
        		typeText.setText(text);
        	}
    	}
    }

    
    // check if was operator entered one step before
    boolean checkOperator(){
    	if(typeText.getText().length()==1){
    		if(isOperator(typeText.getText().charAt(0)) ){
    			//operator=typeText.getText().charAt(0);
        		typeText.setText("");
        		return true;
        	}
    	}
    	return false;
    }
    
    boolean isOperator(char symbol){
    	if(symbol=='/' || symbol=='*' || symbol=='-' || symbol=='+' || symbol=='=' )
    		return true;
    	return false;
    }
    void calculateTwoNumbers(){
    	if(firstCalc){//only entered one number
    		calc1=num;
    		firstCalc=false;
    	}
    	else{//calculate, current number with last calculation
    		switch(operator){
    		case '/':
    			if(num!=0){
    				calc1=calc1/num;
    			}
    			else
    				throw new IllegalArgumentException("Cannot divide by zero");
    			break;
    		case '*':
    			calc1*=num;
    			break;
    		case '+':
    			calc1+=num;
    			break;
    		case '-':
    			calc1-=num;
    			break;
    		}
    	}
    }
    
    void reset(){
    	typeText.setText("");
    	calc1=0;
    	num=0;
    	operator=' ';
    	opt2=' ';
    	firstCalc=true;
    }

    
}
