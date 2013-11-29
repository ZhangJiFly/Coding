import java.util.ArrayList;


public class BoundedBufferImp implements BoundedBuffer {
	private ArrayList<Object> myArray;
	
	BoundedBufferImp(int size){
		this.myArray = new ArrayList<Object>(size);
	}
	
	@Override
	public synchronized void insert(Object o) {
		this.myArray.add(o);
		// TODO Auto-generated method stub
		
	}
	@Override
	public synchronized Object remove() {
		return this.myArray.remove(myArray.size()-1);
	}

}
