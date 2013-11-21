package Server;

import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.concurrent.ConcurrentSkipListSet;

import Client.AuctionClientIntf;

public class AuctionItem implements AuctionItemIntf{
	private String name;
	private Integer minVal;
	private Date end;
	private long id;
	private double bid;
	private static long idCount = 1;
	private ConcurrentSkipListSet<Bid> bids;
	
	public AuctionItem(String name, Integer minVal, Date end) {
		this.name = name;
		this.minVal = minVal;
		this.end = end;
		this.bids = new ConcurrentSkipListSet<Bid>();
		synchronized(AuctionItem.class){
			this.id = idCount;
			idCount++;
		}
	}
	
	public String getName(){
		return this.name;
	}
	
	public Integer getMinVal() {
		return this.minVal;
	}

	public Date getEnd() {
		return this.end;
	}

	public long getId() {
		return this.id;
	}

	public synchronized double getBid() {
		return this.bid;
	}
	
	public synchronized ConcurrentSkipListSet<Bid> getBids(){
		return this.bids;
	}

	public synchronized boolean bid(AuctionClientIntf client, double value, String thread){
		Bid bid = new Bid(client, value, thread);
		System.out.println(bid.getValue());
//		Bid temp;
//		Iterator<Bid> it = bids.iterator();
//		while (it.hasNext()){
//			temp = it.next();
//		}
		boolean temp = bids.add(bid);
		
		return temp;
	}
	
	public String toString(){
		Format formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String dateString = formatter.format(this.end);
		return "Name: " + this.name + " id: " + this.id + " End date: " + dateString +"\n"; 
	}

}
