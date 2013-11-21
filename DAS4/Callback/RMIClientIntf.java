

import java.rmi.*;

public interface RMIClientIntf extends Remote {
   public void callBack(String s) throws java.rmi.RemoteException;
}

