package Server;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

import Client.IntSink;

@SuppressWarnings("serial")
class IntSinkServant extends UnicastRemoteObject implements IntSink {

    public IntSinkServant() throws RemoteException {
    }

    public void ignore(int localParam) throws RemoteException {
    }
}