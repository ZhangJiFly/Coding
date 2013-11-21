package Client;
import java.rmi.*;
import java.rmi.server.*;
import java.util.Date;
import java.util.Scanner;

import Server.AuctionServerIntf;

public class AuctionClient extends UnicastRemoteObject implements AuctionClientIntf, Runnable {

	/**
	 * 
	 */
	private static final long serialVersionUID = -3846450470333966271L;
	private String host = "localhost";
	private int port = 1099;

	public AuctionClient() throws RemoteException {
		super();
	}


	public AuctionClient(String h, int p) throws RemoteException {
		super();
		host = h;
		port = p;
	}


	public void callBack(String string) throws RemoteException {
		System.out.println(string);      
	}

	public void run() {
		try {
			// RMIServerIntf rmiServer = (RMIServerIntf)Naming.lookup("rmi://localhost:1099/RMIServer");
			Scanner sc = new Scanner(System.in);
			AuctionServerIntf rmiServer = (AuctionServerIntf) Naming.lookup("rmi://"+host+":"+port+"/AuctionServer");
			String inst;
			while(!(inst = sc.nextLine().trim()).equalsIgnoreCase("end")){
				String name;
				int minVal;
				Date end;
				long id;
				double bid;
				String thread = System.getProperty("pid");
				if (inst.toLowerCase().equals("add")){
					System.out.println("Please input the name, minimum value and number of minutes until end.");
					name = sc.next();
					minVal = sc.nextInt();
					long minutes = sc.nextLong();
					System.out.println("name: " + name + ", minVal: " + minVal + ", minutes: " + minutes);
					long milli = minutes*60*1000;
					Date date = new Date();
					end = new Date(date.getTime() + milli);
					rmiServer.registerObject(this, name, minVal, end, thread);  
				}
				else if (inst.toLowerCase().equals("bid")){
					id = sc.nextInt();
					bid = sc.nextDouble();
					rmiServer.bid(this, id, bid, thread);
				}
				else if(inst.toLowerCase().equals("list")){
					System.out.println(rmiServer.list(this));
				}

			}
		} catch (RemoteException e) {
			System.out.println("Exception in AuctionClient.testServer " + e);
		} catch (java.rmi.NotBoundException e) {
			System.out.println("AuctionClient unable to bind to server " + e);
		} catch (java.net.MalformedURLException e) {
			System.out.println("Malformed URL for server " + e);
		}
	}



	public static void main(String args[]) throws Exception {
		String host = "localhost";
		int port = 1099;

		if (args.length>0) {
			host = args[0];
			if (args.length == 2)
				port = Integer.parseInt(args[1]);
		}

		for (int i=0; i<1; i++) {
			// Thread t = new Thread(new RMIClient());

			Thread t = new Thread(new AuctionClient(host,port));
			t.start();
		}
	}
}

