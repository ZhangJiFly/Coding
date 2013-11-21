package Server;
import java.rmi.*;
import java.rmi.server.*;
import java.util.Date;
import java.util.Iterator;
import java.net.*;
import java.util.concurrent.CopyOnWriteArrayList;

import Client.AuctionClientIntf;

public class AuctionServer extends UnicastRemoteObject implements AuctionServerIntf {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private AuctionClientIntf rmicif;
	private CopyOnWriteArrayList<AuctionItem> list;


	public AuctionServer() throws RemoteException {
		super();
		list = new CopyOnWriteArrayList<AuctionItem>();
	}

	public synchronized long registerObject(AuctionClientIntf client, String name, int minVal, Date end, String thread) throws RemoteException {
		rmicif = client;
		System.out.println("thread: " + thread);
		long id;
		MyTimer timer = new MyTimer(this.list);
		AuctionItem item = new AuctionItem(name, minVal, end);
		id = item.getId();
		list.add(item);
		timer.addTask(id, end);
		return id;
	}

	public String list(AuctionClientIntf client) throws java.rmi.RemoteException{
		rmicif = client;
		return list.toString();
	}

	public boolean bid(AuctionClientIntf client, long id, double bid, String thread) throws RemoteException {
		rmicif = client;
		Iterator<AuctionItem> it = list.iterator();
		while(it.hasNext()){
			AuctionItem item = (AuctionItem) it.next();
			if (item.getId() == id){
				rmicif.callBack("Your bid has been successful");
				return item.bid(client, bid, thread);	
			}
		}
		rmicif.callBack("None of our records matched the id given");
		return false;
	}
	

	public static void main(String args[]) {
		String host = "localhost";
		int port = 1099;

		if (args.length > 0) {
			host = args[0];
			if (args.length == 2)
				port = Integer.parseInt(args[1]);
		}

		if (System.getSecurityManager() == null) {
			System.setSecurityManager(new RMISecurityManager());
		}

		try {

			AuctionServer aucServer = new AuctionServer();
			Naming.rebind("//"+host+":"+port+"/AuctionServer", aucServer);
			System.out.println("AuctionServer is ready");

		} catch(RemoteException e) {
			System.out.println("Exception in AuctionServerImp.main " + e);
		} catch(MalformedURLException ue) {
			System.out.println("MalformedURLException in AuctionServerImp.main " + ue);
		}
	}

	
}

