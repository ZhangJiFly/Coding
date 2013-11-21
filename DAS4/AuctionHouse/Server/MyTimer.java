package Server;

import java.rmi.RemoteException;
import java.util.Date;
import java.util.Iterator;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Calendar;
import java.util.concurrent.ConcurrentSkipListSet;
import java.util.concurrent.CopyOnWriteArrayList;

import Client.AuctionClientIntf;

public class MyTimer {

	private Timer timer;
	CopyOnWriteArrayList<AuctionItem> auctions;
	/**
	 * constructor
	 *
	 * - starts a timer that fires at the next 5 minute boundary and
	 *   every 5 minutes after that
	 */

	public MyTimer(CopyOnWriteArrayList<AuctionItem> list) {
		timer = new Timer();
		auctions = list;
	}

	public void addTask(long id, Date end){
		BidTask bTask = new BidTask();
		bTask.init(id);
		timer.schedule(bTask, end);
	}

	/**
	 * task that is scheduled by the timer
	 */
	class BidTask extends TimerTask {
		private long id;
		public void init(long id){
			this.id = id;
		}
		public void run() {
			Iterator<AuctionItem> it = auctions.iterator();
			Iterator<Bid> bit;
			AuctionItem item;
			ConcurrentSkipListSet<Bid> bidList;
			Bid bid;
			AuctionClientIntf client;
			while (it.hasNext()){
				item = it.next();
				if (item.getId() == this.id){
					bidList = item.getBids();
					bit = bidList.iterator();
					while (bit.hasNext()){
						bid = bit.next();
						client = bid.getClient();
						try {
							client.callBack("You did a bid... well done but its over now");
						} catch (RemoteException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
					
				}
			}
		}
	}
}
