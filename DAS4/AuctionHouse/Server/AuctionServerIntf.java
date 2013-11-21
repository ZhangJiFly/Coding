package Server;
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
import java.util.Date;

import Client.AuctionClientIntf;

public interface AuctionServerIntf extends Remote {
   
	public long registerObject(AuctionClientIntf clientRef, String name, int minVal, Date end, String thread) throws java.rmi.RemoteException;
	public String list(AuctionClientIntf clientRef) throws java.rmi.RemoteException;
	public boolean bid(AuctionClientIntf clientRef, long id, double bid, String thread) throws java.rmi.RemoteException;
}

