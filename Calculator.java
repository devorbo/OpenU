
import javafx.application.Application;
import javafx.fxml.*;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;



public class Calculator extends Application{


	@Override
	public void start(Stage stage) throws Exception {
		Parent root=FXMLLoader.load(getClass().getResource("Calculator.fxml"));
		Scene scene= new Scene(root);
		stage.setTitle("Calculator");
		stage.setScene(scene);
		stage.show();
		
	}
	public static void main(String[] args)
	{
		launch(args);
	}

}