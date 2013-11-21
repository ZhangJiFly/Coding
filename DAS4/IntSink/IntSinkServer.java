import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

class IntSinkServer {
    public static void main(String args[]) {
        String regHost = "localhost";
        Integer regPort = new Integer(1099);
        if (args.length > 0) {
            regHost = args[0];
            if (args.length > 1) regPort = Integer.decode(args[1]);
        }
        try {
            IntSinkServant iss = new IntSinkServant();
            System.out.print("1111111111111\n");
            //IntSink is = (IntSink) UnicastRemoteObject.exportObject(iss, 0);
            Registry reg = LocateRegistry.getRegistry(regHost, regPort.intValue());
            System.out.print("222222222222\n");
            reg.rebind("IntSink", iss);
            System.out.print("3333333333333\n");
        } catch (Exception e) {
            System.out.format("intSink: export error: %s\n", e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
}
