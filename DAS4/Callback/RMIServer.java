import java.rmi.*;
import java.rmi.server.*;
import java.net.*;

public class RMIServer extends UnicastRemoteObject implements RMIServerIntf {

   /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private RMIClientIntf rmicif;


	public RMIServer() throws RemoteException {
		super();
	}

   
	public void registerObject(RMIClientIntf client, String n, int t) throws RemoteException {
		rmicif = client;
		try {
			Thread.sleep(t);
		} catch(InterruptedException e) {}
   			System.out.format("Calling client %s\n", n);
   		try {
   			rmicif.callBack("server says hi to: " + n);
   		} catch(RemoteException e) {
         e.printStackTrace();
   		}
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
			System.out.println("RMIServer is not ready");

			RMIServer rmiServer = new RMIServer();
			//RMIServerIntf RSI = (RMIServerIntf) UnicastRemoteObject.exportObject(rmiServer, 0);
			System.out.println("RMIServer is likely under prepared");
			Naming.rebind("//"+host+":"+port+"/RMIServer", rmiServer);

			System.out.println("RMIServer is ready");

		} catch(RemoteException e) {
			System.out.println("Exception in RMIServerImp.main " + e);
		} catch(MalformedURLException ue) {
			System.out.println("MalformedURLException in RMIServerImp.main " + ue);
		}
	}
}

