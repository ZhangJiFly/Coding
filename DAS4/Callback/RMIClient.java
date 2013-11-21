import java.rmi.*;
import java.rmi.server.*;
import java.net.*;
import java.util.Random;

public class RMIClient extends UnicastRemoteObject implements RMIClientIntf, Runnable {

   private String host = "localhost";
   private int port = 1099;
   
   public RMIClient() throws RemoteException {
      super();
   }

   
   public RMIClient(String h, int p) throws RemoteException {
      super();
      host = h;
      port = p;
   }

  
  public void callBack(String s) throws RemoteException {
      System.out.println(s);      
   }

  public void run() {
  	try {
  	// RMIServerIntf rmiServer = (RMIServerIntf)Naming.lookup("rmi://localhost:1099/RMIServer");

	RMIServerIntf rmiServer = (RMIServerIntf) Naming.lookup("rmi://"+host+":"+port+"/RMIServer");
  	Random rg = new Random();
  	int timer = rg.nextInt(5000);
  	String name = Thread.currentThread().getName();
  	System.out.format("%s - Requesting callback from server in %d seconds\n",name, timer/1000);
  	rmiServer.registerObject(this, name, timer);  	
  	} catch (RemoteException e) {
         System.out.println("Exception in RMIClient.testServer " + e);
      } catch (java.rmi.NotBoundException e) {
         System.out.println("RMIClient unable to bind to server " + e);
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
			
			for (int i=0; i<5; i++) {
				// Thread t = new Thread(new RMIClient());

				Thread t = new Thread(new RMIClient(host,port));
      	t.start();
      }
   }
}

