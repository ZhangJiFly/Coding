package Server;

import java.io.Serializable;
import java.rmi.RemoteException;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ConcurrentSkipListSet;

import Client.AuctionClientIntf;

public class MyTimer implements Serializable{

	private static final long serialVersionUID = 5878998380080868273L;
	private Timer timer;
	AuctionServer server;

	public MyTimer(AuctionServer server) {
		timer = new Timer();
		this.server = server;
	}

	public void addTask(int itemId, Date end){
		BidTask bTask = new BidTask();
		bTask.init(itemId);
		timer.schedule(bTask, end);
	}

	/**
	 * task that is scheduled by the timer
	 */
	class BidTask extends TimerTask implements Serializable {

		private static final long serialVersionUID = -5518507500202475897L;
		private int itemId;
		
		public void init(int itemId){
			this.itemId = itemId;
		}
		public void run() {
			ConcurrentSkipListSet<AuctionItem> auctions = server.getList();
			Iterator<AuctionItem> it = auctions.iterator();
			Iterator<Bid> bit;
			AuctionItem item;
			ConcurrentSkipListSet<Bid> bidList;
			Bid bid;
			AuctionClientIntf client;
			DeleteItemTask dTask = new DeleteItemTask();
			dTask.init(this.itemId);
			long delay = 2 * 60000;
			timer.schedule(dTask, delay);
			while (it.hasNext()){
				item = it.next();
				if (item.getId() == this.itemId){
					bidList = item.getBids();
					bit = bidList.iterator();
					while (bit.hasNext()){
						bid = bit.next();
						client = bid.getClient();
						try {
							if (bid.equals(item.getBid())){
								client.callBack("Congratulations you were successful in your bid to get item " + itemId);
							}
							else{
								client.callBack("The bid you placed on item " + itemId + " was unsuccessful as you were outbid by client with id: " + item.getBid().getClientId() + " with a bid of " + item.getBid().getValue() + ".");
							}
						} catch (RemoteException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}

				}
			}
		}
	}
	class DeleteItemTask extends TimerTask implements Serializable {

		private static final long serialVersionUID = -5715355655708131046L;
		private long id;
		public void init(long id){
			this.id = id;
		}
		public void run() {
			ConcurrentSkipListSet<AuctionItem> auctions = server.getList();
			Iterator<AuctionItem> it = auctions.iterator();
			AuctionItem item;
			while (it.hasNext()){
				item = it.next();
				if (item.getId() == this.id){
					Format formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
					String dateString = formatter.format(new Date());
					auctions.remove(item);
				    System.out.println("Auction item deleted at time: " + dateString);
					server.writeObject();
				}
			}
		}

	}
}
