
import javafx.application.Application;
import javafx.fxml.*;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class DrawShapes extends Application{

	@Override
	public void start(Stage stage) throws Exception {
		Parent root=FXMLLoader.load(getClass().getResource("DrawShapes.fxml"));
		Scene scene= new Scene(root);
		stage.setTitle("Draw Shapes");
		stage.setScene(scene);
		stage.show();
	}
	public static void main(String[] args)
	{
		launch(args);
	}
 
}