
public class CellStatus {

	private boolean current;
	private boolean next;
	public CellStatus(){
		current=false;
		next=false;
	}
	public CellStatus(boolean current){
		this.current=current;
		this.next=false;
	}
}
