package il.co.ilrd.iot;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import com.sun.net.httpserver.HttpServer;

public class HTTPIOTServer {

	public static void main(String[] args) {
		try {
			HttpServer server = HttpServer.create(new InetSocketAddress("localhost", 55554), 0);
			ExecutorService tpexec = Executors.newFixedThreadPool(10);
			server.createContext("/test", new HTTPServerHandler());
			server.setExecutor(tpexec);
			server.start();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}

}
