package Client;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.Serializable;
import java.rmi.*;
import java.rmi.server.*;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.NoSuchElementException;
import java.util.Scanner;

import Server.AuctionServerIntf;

public class AuctionClient extends UnicastRemoteObject implements AuctionClientIntf, Runnable, Serializable {

	private static final long serialVersionUID = -3846450470333966271L;
	private int clientId;
	private int file;
	private int test;
	AuctionServerIntf rmiServer;
	
	public AuctionClient() throws RemoteException {
		super();
	}


	public AuctionClient(int i, int test, AuctionServerIntf rmiServer) throws RemoteException {
		super();
		this.file = i;
		this.test = test;
		this.rmiServer = rmiServer;
	}


	public void callBack(String string) throws RemoteException {
		System.out.println(string);      
	}
	
	public int getClientId(){
		return this.clientId;
	}

	public void run() {
		try {
			FileInputStream fos = new FileInputStream("./tests/test" + this.file);
			Scanner sc;
			if (test == 0){
				sc = new Scanner(System.in);
			}
			else{
				sc = new Scanner(fos);
			}
			
			String inst = "";
			while(!(inst = sc.next().toLowerCase().trim()).equals("end")){
				String name;
				int minVal;
				Date end;
				int clientId;
				int itemId;
				double bid;
				if (inst.equals("add")){
					System.out.println("Please input the name, minimum value and number of minutes until end.");
					name = "item";
					minVal = 0;
					long minutes = 1;
					try{
						name = sc.next();
						minVal = sc.nextInt();
						minutes = sc.nextLong();
					}
					catch(NoSuchElementException e){
						System.out.println("No such element exception on add element scan:" + e);
					}
					
					System.out.println("name: " + name + ", minVal: " + minVal + ", minutes: " + minutes + ".");
					long milli = minutes*60*1000;
					Date date = new Date();
					end = new Date(date.getTime() + milli);
					itemId = rmiServer.registerItem(name, minVal, end);
					Format formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
					String dateString = formatter.format(date);
				    System.out.println("Auction item name: " + name + " with itemId: " + itemId + " added at time: " + dateString + ".");
				    dateString = formatter.format(end);
				    System.out.println("Auction item name: " + name + " with itemId: " + itemId + " ends at time: " + dateString + ".");
				}
				else if (inst.equals("register")){
					this.clientId = rmiServer.newClientNum(this);
				}
				else if(inst.equals("login")){
					System.out.println("Please input the clientId that you would like to login as.");
					clientId = sc.nextInt();
					boolean result = rmiServer.login(clientId, this);
					if (result){
						System.out.println("Successfully logged in as client " + clientId + ".");
					}else{
						System.out.println("No active bids associated with client id " + clientId + ".");
					}
					
				}
				else if (inst.equals("bid")){
					System.out.println("Please input the id and then bid.");
					itemId = sc.nextInt();
					bid = sc.nextDouble();
					rmiServer.bid(this, itemId, bid);
				}
				else if(inst.equals("list")){
					System.out.println(rmiServer.list());
				}
				else if(inst.equals("help")){
					System.out.println("To register as a new user type 'register'.");
					System.out.println("To put an item up for auction type 'add'.");
					System.out.println("To bid on an item type 'bid'.");
					System.out.println("To login as a user to recieve updates on that users current bid items type 'login'.");
					System.out.println("To recieve a list of all items currenly on the server type 'list'.");
				}
				else{
					System.out.println("Command not recognised type 'help' for a list of available commands. ");
				}

			}
		} catch (RemoteException e) {
			System.out.println("Exception in AuctionClient.testServer " + e);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static void main(String args[]) throws Exception {
		String host = "localhost";
		int port = 1099;
		int test = 0;
		int threads = 1;
		
		if (args.length>0) {
			host = args[0];
			if (args.length >= 2)
				port = Integer.parseInt(args[1]);
			if (args.length >=3){
				test = Integer.parseInt(args[2]);
			}
			if ((test != 1) && (args.length >= 4)){
				threads = Integer.parseInt(args[3]);
			}
			
		}
		try{
			AuctionServerIntf rmiServer = (AuctionServerIntf) Naming.lookup("rmi://"+host+":"+port+"/AuctionServer");
			long time = System.currentTimeMillis();
			System.out.println("Start Time: "+ time);
			Thread workers[] = new Thread[threads];
			for (int i = 0;i<workers.length;i++) {
				workers[i] = new Thread(new AuctionClient(i, test, rmiServer));
				workers[i].start();
			}
			for (Thread k : workers){
				try {
					k.join();
				}
				catch(Exception e){
				}
			}
			System.out.println("End Time: " + System.currentTimeMillis());
			System.out.println("Delay Time: " + (System.currentTimeMillis() - time));
			System.out.println("host: " + host + " test: " + test + " threads: " + threads);
		}
		catch (java.rmi.NotBoundException e) {
			System.out.println("AuctionClient unable to bind to server " + e);
		} catch (java.net.MalformedURLException e) {
			System.out.println("Malformed URL for server " + e);
		} 
		
		
	}
}

