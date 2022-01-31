import java.util.Random;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;

public class LifeGameController {

	private boolean[][] table;
	private boolean[][] next;
	private int countG=0;
	private int numCells=10;
	
    @FXML
    private Button clickBtn;

    @FXML
    private Canvas canvas;

    public LifeGameController(){
    	table=new boolean[numCells][numCells];//matrix that contain the status of the cells table 
    	next=new boolean[numCells][numCells];//next generation status 
    	initializeNext();
    }
    @FXML
    void pressAction(ActionEvent event) {
    	GraphicsContext gc= canvas.getGraphicsContext2D();
    	gc.clearRect(0, 0, canvas.getWidth(),canvas.getHeight());// clear canvas 
    	   	
    	if(countG==0)//first click
    		drawRandomly();//will fill random cells 
    	else
    		draw();//fill by using the current values in table
    	
    	//checking table for next generation 
    	for(int i=0;i<numCells;i++){
    		for(int j=0;j<numCells;j++){
    			int numNeighbor=neighborAlive(i,j);
    			if(table[i][j]==false){//current not alive
    				if(numNeighbor==3){//birth
    					next[i][j]=true;
    				}
    				else{
    					next[i][j]=false;//stay dead
    				}
    			}
    			else{//current alive
    				if(numNeighbor==0 || numNeighbor==1){//death from loneliness
    					next[i][j]=false;
    				}
    				else if(numNeighbor>=4){//death from over population
    					next[i][j]=false;
    				}
    				else{//existence
    					next[i][j]=true;
    				}
    			}
    		}
    	}
    	copyGeneration();
    	
    	countG++;//num generation
    }
    void draw()
    {
    	GraphicsContext gc= canvas.getGraphicsContext2D();
    	gc.clearRect(0, 0, canvas.getWidth(),canvas.getHeight());
    	
    	double height=canvas.getHeight()/numCells;//height of each cell when drawing
    	double x=0,y=0;//first column, first row
    	for(int i=0;i<numCells;i++){
    		for(int j=0;j<numCells;j++){
    			gc.strokeRect(x,y,height,height);//cell outlines
    			if(table[i][j]==true){
        			gc.fillRect(x,y,height,height);//fill the current cell
    			}
    			x+=height;//next column 
    		}
    		x=0;//first column
    		y+=height;//next row
    	}
    	
    	
    }
    public void drawRandomly(){
    	// fill randomly
    	GraphicsContext gc= canvas.getGraphicsContext2D();
    	gc.clearRect(0, 0, canvas.getWidth(),canvas.getHeight());
    	
    	double height=canvas.getHeight()/numCells;
    	double x=0,y=0;//first column, first row
    	Random rnd=new Random();
    	for(int i=0;i<numCells;i++){
    		for(int j=0;j<numCells;j++){
    			gc.strokeRect(x,y,height,height);//cell outlines
    			int fill=rnd.nextInt(2);
    			if(fill==1){
    				table[i][j]=true;//filled
        			gc.fillRect(x,y,height,height);//fill the current cell
    			}
    			else{
    				table[i][j]=false;//unfilled
    			}
    			x+=height;//next column 
    		}
    		x=0;//first column
    		y+=height;//next row
    	}
    }
    
    public void initializeNext(){
    	for(int i=0;i<next.length;i++){
    		for(int j=0;j<next.length;j++){
    			next[i][j]=false;
    		}
    	}
    }

    public int neighborAlive(int i, int j){
    	int count=0;
    	//go through all neighbors(including himself)
    	for(int k=i-1;k<=i+1;k++){
    		for(int l=j-1;l<=j+1;l++){
    			if(k>0 && k<table.length && l>0 && l<table.length)//valid indexes
    				if(table[k][l]==true)
    					count++;	
    		}
    	}
    	if(table[i][j]==true)//alive
    		count--;// was counted as a neighbor, decrement it
    	return count;
    }

    public void copyGeneration(){
    	for(int i=0;i<table.length;i++){
    		for(int j=0;j<table.length;j++){
    			table[i][j]=next[i][j];
    		}
    	}
    	initializeNext();
    }
}
