import java.net.*;
import java.io.*;
public class client {
	public static void main (String [] args )
			throws IOException {
		int maxSize=1024;
		int readBytes;
		int curr = 0;
		Socket socket = new Socket("127.0.0.1",55556);
		byte [] buffArray = new byte [maxSize];
		InputStream is = socket.getInputStream();
		FileOutputStream f = new FileOutputStream("E://client.txt");
		BufferedOutputStream oStr = new BufferedOutputStream(f);
		readBytes = is.read(buffArray,0,buffArray.length);
		curr = readBytes;
		do {
			readBytes = is.read(buffArray, curr, (buffArray.length-curr));
			if(readBytes >= 0)
				curr += readBytes;
			}
		while(readBytes > -1);
		oStr.write(buffArray, 0 , curr);
		oStr.flush();
		oStr.close();
		socket.close();
		} 
	}

