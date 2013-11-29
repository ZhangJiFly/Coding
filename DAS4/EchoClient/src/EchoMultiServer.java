import java.io.IOException; 
import java.net.ServerSocket; 
 
public class EchoMultiServer { 
	 public static void main(String[] args) throws IOException { 
		 ServerSocket serverSocket = null; 
		 
		 try { 
			 serverSocket = new ServerSocket(8765); 
		 }
		 catch (IOException e) { 
			 System.err.println("Could not listen on port: 8765."); 
			 System.exit(-1); 
		 } 
		 while (!Thread.currentThread().isInterrupted()) { 
			 EchoMultiServerTask t = new EchoMultiServerTask(serverSocket.accept()); 
		 new Thread(t).start(); 
		 } 
		 serverSocket.close(); 
	}
} 
