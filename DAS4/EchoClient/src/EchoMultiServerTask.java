import java.net.Socket; 
import java.io.PrintWriter; 
import java.io.BufferedReader; 
import java.io.InputStreamReader; 
import java.io.IOException; 
 
public class EchoMultiServerTask implements Runnable { 
 private Socket socket = null; 
 
	 public EchoMultiServerTask(Socket socket) { 
		 this.socket = socket; 
	 } 
	 
	 public void run() { 
	 
		 try { 
			 PrintWriter out = new PrintWriter(socket.getOutputStream(), true); 
			 BufferedReader in = new BufferedReader( 
			 new InputStreamReader( 
			 socket.getInputStream()));
			 String inputLine; 
			 
			 while ((inputLine = in.readLine()) != null) { 
				 out.println(inputLine); 
			 } 
			 out.close(); 
			 in.close(); 
			 socket.close(); 
			 
		 } 
		 catch (IOException e) { 
			 e.printStackTrace(); 
		 } 
	} 
} 