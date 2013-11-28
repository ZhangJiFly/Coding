package Server;

import java.io.Serializable;
import java.rmi.RemoteException;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;
import java.util.concurrent.ConcurrentSkipListSet;

import Client.AuctionClientIntf;

public class AuctionItem implements Comparable<AuctionItem>, Serializable{

	private static final long serialVersionUID = -2747410476299566452L;
	private String name;
	private double minVal;
	private Date end;
	private int id;
	private Bid bid;
	private static int idCount = 0;
	private ConcurrentSkipListSet<Bid> bids;
	
	
	@Override
	public int compareTo(AuctionItem item) {
		return this.end.compareTo(item.getEnd());
	}
	
	public AuctionItem(String name, double minVal, Date end) {
		this.name = name;
		this.minVal = minVal;
		this.end = end;
		this.bids = new ConcurrentSkipListSet<Bid>();
		synchronized(AuctionItem.class){
			this.id = ++idCount;
		}
	}
	
	public boolean active(){
		Calendar cal=Calendar.getInstance(); // get today

	    return cal.getTime().compareTo(this.end) < 0;
	}
	
	public static void setIdCount(int id){
		idCount = id;
	}
	public String getName(){
		return this.name;
	}
	
	public double getMinVal() {
		return this.minVal;
	}

	public Date getEnd() {
		return this.end;
	}

	public int getId() {
		return this.id;
	}

	public synchronized Bid getBid() {
		return this.bid;
	}
	
	public synchronized ConcurrentSkipListSet<Bid> getBids(){
		return this.bids;
	}

	public synchronized boolean bid(AuctionClientIntf client, double value) throws RemoteException{
		Bid temp;
		int clientId = client.getClientId();
		Iterator<Bid> it = bids.iterator();
		while (it.hasNext()){
			temp = it.next();
			if (temp.getClient().getClientId() == clientId){
				temp.setBid(value);
				return true;
			}
		}
		Bid newBid = new Bid(client, value);
		if (bids.isEmpty() || value>bid.getValue()){
			this.bid = newBid;
		}
		return bids.add(bid);
	}
	
	public String toString(){
		Format formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String dateString = formatter.format(this.end);
		return "Name: " + this.name + " id: " + this.id + " End date: " + dateString + " Minimum required value: " + this.minVal + "\n"; 
	}

}
