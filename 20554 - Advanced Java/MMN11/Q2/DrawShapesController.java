import java.util.Random;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class DrawShapesController {

    @FXML
    private Canvas canvas;

    @FXML
    void DrawButtonPress(ActionEvent event) {
    	draw();

    }
    void draw(){
    	Random rnd=new Random();
    	GraphicsContext gc= canvas.getGraphicsContext2D();
    	gc.clearRect(0, 0, canvas.getWidth(),canvas.getHeight());
    	int numShape =10;
		double width=canvas.getWidth();
		double height=canvas.getHeight();
    	double green, blue,red;
    	for(int i=0;i<numShape;i++)
    	{
    		int num=rnd.nextInt(3);// number polygon
    		int x=rnd.nextInt((int)width);//coordination for begin point of the shape
    		int y=rnd.nextInt((int)height);
    		double polyW= rnd.nextInt((int)width/4);//the width of the polygon will be set as less than a 1/4 from the area of the canvas 
    		double polyH= rnd.nextInt((int)height/4);
    		
    		//random color
			red=Math.random();
    		green=Math.random();
    		blue=Math.random();
    		gc.setFill(new Color(red,green,blue,1));//set the filling for this shape
    		switch(num)
    		{
    		case 0://draw stroke
    			//check for the rectangle that contains the line the width and height is 
        		//less then a quarter from the entire canvas
    			int x2=0,y2=0;
    			do{
    				x2=rnd.nextInt((int)width);
    				y2=rnd.nextInt((int)height);
    			}while(!(Math.abs(x2-x)<=width/4 && Math.abs(y2-y)<=height/4));
    			gc.strokeLine(x, y, x2, y2);
    			break;
    		case 1://draw rectangle
    			gc.fillRect(x, y, polyW,polyH);
    			break;
    		case 2://draw oval
    			gc.fillOval(x, y, polyW,polyH);
    			break;
    		}
    	}
    }

}
