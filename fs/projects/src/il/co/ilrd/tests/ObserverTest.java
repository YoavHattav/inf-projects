package il.co.ilrd.tests;

import il.co.ilrd.design_patterns.Dispatcher;
import il.co.ilrd.design_patterns.Dispatcher.*;

import static org.junit.jupiter.api.Assertions.*;

import java.util.LinkedList;

import org.junit.jupiter.api.Test;

class ObserverTest {

	@Test
	void youTube() {
		
		class Subscriber {
			String name;
			Callback<String> cb = new Callback<String>(this::notificationRecived, this::deathNotice);

			public Subscriber(String name) {
				super();
				this.name = name;
			}
			void notificationRecived(String vid_name) {
				System.out.println(name +"! there is a new vid named: " + vid_name);
			}
			void deathNotice() {
				System.out.println("channel not available anymore");
			}
		}
		class Youtube {
			
			Callback<String> cb = new Callback<String>(this::congrads, this::deathNotice);

			void congrads(String vid_name) {
				System.out.println("congradulations for the new vid:" + vid_name +"!");
			}
			void deathNotice() {
				System.out.println("channel removed successfully");
			}
		}
		
		Subscriber sub = new Subscriber("yoav");
		Youtube youtube = new Youtube();
		
		Dispatcher<String> league_channel = new Dispatcher<String>();
		
		league_channel.register(sub.cb);
		league_channel.register(youtube.cb);
		
		league_channel.updateAll("eggStaticMax with a new vlad god gameplay");
		league_channel.stopAll();
		
		sub.cb.stopService();
		league_channel.updateAll("only once");
	
		league_channel.unregister(youtube.cb);
		league_channel.updateAll("wont see this");


	}
}
