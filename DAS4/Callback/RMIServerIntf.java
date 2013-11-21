/**
 * RMI Server Interface
 * @author DP
 * @version %I,%G
 */

/* RMIServerIntf */

/* This interface defines the methods which are callable
 * in the remote object.  Obviously the remote object
 * must implement this interface.  Note how all the methods
 * can raise java.rmi.RemoteException
 */

import java.rmi.*;

public interface RMIServerIntf extends Remote {
   
	public void registerObject(RMIClientIntf clientRef, String name, int t) throws java.rmi.RemoteException;
}

