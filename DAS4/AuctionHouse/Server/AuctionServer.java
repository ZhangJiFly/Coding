package Server;
import java.rmi.*;
import java.rmi.server.*;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.io.UTFDataFormatException;
import java.net.*;
import java.util.concurrent.CopyOnWriteArrayList;

import Client.AuctionClientIntf;

public class AuctionServer extends UnicastRemoteObject implements AuctionServerIntf, Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private AuctionClientIntf rmicif;
	private CopyOnWriteArrayList<AuctionItem> list;
	private int clientNum = 0;
    transient private MyTimer timer;

	public AuctionServer() throws RemoteException, IOException, ClassNotFoundException {
		super();
		list = new CopyOnWriteArrayList<AuctionItem>();
		this.timer = new MyTimer(this);
	}
	
	public void setClientNum(int clientNum){
		this.clientNum = clientNum;
	}
	
	public CopyOnWriteArrayList<AuctionItem> getList(){
		return list;
	}

	public synchronized int newClientNum(AuctionClientIntf client) throws RemoteException{
		rmicif = client;
		clientNum++;
		rmicif.callBack("Assigned client number for login use is " + clientNum + ".");
		return clientNum;
	}
	
	public int getClientNum(){
		return clientNum;
	}

	public boolean login(int clientId, AuctionClientIntf client){
		rmicif = client;
		Iterator<AuctionItem> it = list.iterator();
		Iterator<Bid> bit;
		Bid bid;
		boolean successFlag = false;;
		while(it.hasNext()){
			AuctionItem item = it.next();
			bit = item.getBids().iterator();
			System.out.println("Item: " + item.toString());
			while (bit.hasNext()){
				bid = bit.next();
				System.out.println("Bid: " + bid.toString());
				if(bid.getClientId() == clientId){
					bid.setClient(client);
					successFlag = true;
				}
			}
		}
		return successFlag;
	}
	
	public synchronized int registerItem(AuctionClientIntf client, String name, int minVal, Date end) {
		rmicif = client;
		int itemId;
		AuctionItem item = new AuctionItem(name, minVal, end);
		itemId = item.getId();
		list.add(item);
		this.timer.addTask(itemId, end);
		writeObject();
		return itemId;
	}

	public void writeObject(){
		FileOutputStream fos = null;
	    ObjectOutputStream oos = null;
		try {
			fos = new FileOutputStream("state");
			oos = new ObjectOutputStream(fos);
			oos.writeObject(this);
			oos.close();
			fos.close();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
	}
	
	public String list(){
		return list.toString();
	}

	public boolean bid(AuctionClientIntf client, int itemId, double bid) throws RemoteException {
		rmicif = client;
		Iterator<AuctionItem> it = list.iterator();
		while(it.hasNext()){
			AuctionItem item = (AuctionItem) it.next();
			if ((item.getId() == itemId)){
				if(!item.active()){
					Format formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
					String dateString = formatter.format(item.getEnd());
					rmicif.callBack("Sorry but the auction for this item expired at " + dateString);
					return false;
				}
				else if(item.getMinVal() > bid){
					rmicif.callBack("The bid did not meet the minimum value requirements of the item please place a bid of at least " + item.getMinVal());
					return false;
				}else{
					rmicif.callBack("Your bid of " + bid + " has been successful");
					writeObject();
					return item.bid(client, bid);	
				}

			}
		}
		rmicif.callBack("None of the current items being auctioned match the id given");
		return false;
	}
	
	private int findMaxId(){
		int itemId = 0;
		Iterator<AuctionItem> it = list.iterator();
		while(it.hasNext()){
			AuctionItem item = it.next();
			if (item.getId() > itemId){
				itemId = item.getId();
			}
		}
		return itemId;
	}
	
	private int maxCliId(){
		int clientId = 0;
		Iterator<AuctionItem> it = list.iterator();
		Iterator<Bid> bit;
		while(it.hasNext()){
			AuctionItem item = it.next();
			bit = item.getBids().iterator();
			while(bit.hasNext()){
				int temp = bit.next().getClientId();
				if(temp>clientId){
					clientId = temp;
				}
			}
		}
		return clientId;
	}

	public void init(){
		this.timer = new MyTimer(this);
		Iterator<AuctionItem> it = list.iterator();
		while(it.hasNext()){
			AuctionItem item = it.next();
			timer.addTask(item.getId(), item.getEnd());	
		}
		AuctionItem.setIdCount(findMaxId());
		this.setClientNum(this.maxCliId());
	}
	
	public static void main(String args[]) throws IOException, ClassNotFoundException {
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
			FileInputStream fis = new FileInputStream("state");
			ObjectInputStream ois = new ObjectInputStream(fis);
			AuctionServer aucServer = (AuctionServer) ois.readObject();
			aucServer.init();
			ois.close();
			fis.close();
			Naming.rebind("//"+host+":"+port+"/AuctionServer", aucServer);

			System.out.println("AuctionServer is ready");

		} catch(FileNotFoundException e){
			AuctionServer aucServer = new AuctionServer();
			Naming.rebind("//"+host+":"+port+"/AuctionServer", aucServer);
			System.out.println("AuctionServer is ready");
		} catch(UTFDataFormatException e){
			AuctionServer aucServer = new AuctionServer();
			Naming.rebind("//"+host+":"+port+"/AuctionServer", aucServer);
			System.out.println("AuctionServer is ready");
		}catch(RemoteException e) {
			System.out.println("Exception in AuctionServerImp.main " + e);
		} catch(MalformedURLException ue) {
			System.out.println("MalformedURLException in AuctionServerImp.main " + ue);
		} 
	}


}

