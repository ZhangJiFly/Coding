package Server;
import Client.AuctionClientIntf;

public class Bid implements Comparable<Bid> {
	private double value;
	private AuctionClientIntf client;
	private String thread;
	
	public Bid(AuctionClientIntf client, double value, String thread){
		this.value = value;
		this.client = client;
		this.thread = thread;
	}
	
	public AuctionClientIntf getClient(){
		return this.client;
	}
	
	public double getValue(){
		return this.value;
	}
	
	public String getThread(){
		return this.thread;
	}

	@Override
	public int compareTo(Bid bid) {
		if (this.value > bid.getValue()){
			return 1;
		}else if(this.value == bid.getValue()){
			return 0;
		}
		else{
			return -1;
		}
	}

}
