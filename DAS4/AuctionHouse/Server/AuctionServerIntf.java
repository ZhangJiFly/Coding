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
import java.util.concurrent.CopyOnWriteArrayList;

import Client.AuctionClientIntf;

public interface AuctionServerIntf extends Remote {
   
	public int registerItem(AuctionClientIntf clientRef, String name, int minVal, Date end) throws java.rmi.RemoteException;
	public CopyOnWriteArrayList<AuctionItem> list() throws java.rmi.RemoteException;
	public boolean bid(AuctionClientIntf clientRef, int itemId, double bid) throws java.rmi.RemoteException;
	public int newClientNum(AuctionClientIntf client) throws java.rmi.RemoteException;
	public boolean login(int id, AuctionClientIntf client) throws java.rmi.RemoteException;
}

