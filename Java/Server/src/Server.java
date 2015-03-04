import java.net.*;
import java.io.*;
public class Server { 
	public static void main (String [] args )
			throws IOException {
		ServerSocket SS = new ServerSocket(55556);
		Socket socket = SS.accept();
		//System.out.println("Accepted connection : " + socket);
		File f = new File ("E://server.txt");
		byte [] bytearray = new byte [(int)f.length()];
		FileInputStream fInStr = new FileInputStream(f);
		BufferedInputStream bInStr = new BufferedInputStream(fInStr);
		bInStr.read(bytearray,0,bytearray.length);
		OutputStream os = socket.getOutputStream();
		System.out.println("Sending Files...");
		os.write(bytearray,0,bytearray.length);
		os.flush(); 
		socket.close();
		System.out.println("File transfer complete");
		}
	}

