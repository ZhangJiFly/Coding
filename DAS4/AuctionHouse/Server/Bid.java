package Server;
import java.io.Serializable;
import java.rmi.RemoteException;

import Client.AuctionClientIntf;

public class Bid implements Comparable<Bid>, Serializable {

	private static final long serialVersionUID = 6964725828617394615L;
	private double value;
	private AuctionClientIntf client;
	private int clientId;
	
	public Bid(AuctionClientIntf client, double value) throws RemoteException{
		this.value = value;
		this.client = client;
		this.clientId = client.getClientId();
	}
	
	public AuctionClientIntf getClient(){
		return this.client;
	}
	
	public int getClientId(){
		return this.clientId;
	}
	
	public double getValue(){
		return this.value;
	}

	public void setBid(double bid){
		this.value = bid;
	}
	
	public void setClient(AuctionClientIntf client){
		this.client = client;
	}
	
	public boolean equalTo(Bid bid) throws RemoteException{
		return client.getClientId() == bid.getClient().getClientId();
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
	
	public String toString(){
		return "Client Id" + this.clientId + " Value: " + this.value;
	}

}
