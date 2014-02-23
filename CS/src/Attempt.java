
public class Attempt {
	private int key;
	private StringBuilder sb;
	private int score;
	
	
	public int getScore() {
		return score;
	}
	public void setScore(int score) {
		this.score = score;
	}
	
	public int getKey() {
		return key;
	}
	public void setKey(int key) {
		this.key = key;
	}
	public StringBuilder getSb() {
		return sb;
	}
	public void setSb(StringBuilder sb) {
		this.sb = sb;
	}
	public Attempt(int key, StringBuilder sb) {
		this.key = key;
		this.sb = sb;
		this.score = 0;
	}
	
	
}
