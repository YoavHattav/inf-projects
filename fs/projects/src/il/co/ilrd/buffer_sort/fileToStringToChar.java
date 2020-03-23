package il.co.ilrd.buffer_sort;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Stream;

public class fileToStringToChar {
	
	String file_path = new String();
	
	public fileToStringToChar(String file_path) {
		this.file_path = file_path;
	}
	static char[] scramble(String string) {
		
		String[] scram = string.split("");
        List<String> letters = Arrays.asList(scram);
        Collections.shuffle(letters);
        StringBuilder sb = new StringBuilder(string.length());
        for (String c : letters) {
            sb.append(c);
        }
        return sb.toString().toCharArray();
		
	}
	public char[] generateShuffledCharArray() {
		
		StringBuilder contentBuilder = new StringBuilder();
		 
        try (Stream<String> stream = Files.lines( Paths.get(file_path), StandardCharsets.UTF_8)) 
        {
            stream.forEach(s -> contentBuilder.append(s).append("\n"));
        }
        catch (IOException e) 
        {
            e.printStackTrace();
        }
        
        return scramble(contentBuilder.toString());
	}
 }
