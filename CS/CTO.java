import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

public class CTO {


	private static List<String> wholeWords(String s){
		StringTokenizer st = new StringTokenizer(s);
		List<String> list = new ArrayList<String>();
		while (st.hasMoreTokens()){
			String string = st.nextToken();
			int index = s.lastIndexOf(string)+string.length();
			if(index<s.length() && s.charAt(index) == ' '){
				list.add(string.toLowerCase());
			}
		}	
		return list;
	}


	@SuppressWarnings("resource")
	public	static void main(String[] args) throws IOException{
		long startTime = System.nanoTime();

		BufferedInputStream bisR = new BufferedInputStream(System.in);
		BufferedReader brR = new BufferedReader(new InputStreamReader(bisR));
		
		System.out.println("Type in the location of the cipher text to decrypt: ");
		String cipherText = brR.readLine();
		System.out.println("Type in the location of the letter frequency file: ");
		String LetterText = brR.readLine();
		System.out.println("Type in the location of the bigram frequency file: ");
		String bigramText = brR.readLine();
		System.out.println("Type in the location of the wordList file: ");
		String wordsList = brR.readLine();
		
		FileInputStream fin = new FileInputStream(cipherText);
		BufferedInputStream bis = new BufferedInputStream(fin);
		BufferedReader br = new BufferedReader(new InputStreamReader(bis));

		FileInputStream fin2 = new FileInputStream(LetterText);
		BufferedInputStream lts = new BufferedInputStream(fin2);
		BufferedReader letr = new BufferedReader(new InputStreamReader(lts));
		Map<Character, Integer> letters = new HashMap<Character, Integer>();

		FileInputStream fin3 = new FileInputStream(bigramText);
		BufferedInputStream big = new BufferedInputStream(fin3);
		BufferedReader bigr = new BufferedReader(new InputStreamReader(big));
		Map<String, Integer> bigrams = new HashMap<String, Integer>();

		FileInputStream fin4 = new FileInputStream(wordsList);
		BufferedInputStream wos = new BufferedInputStream(fin4);
		BufferedReader wor = new BufferedReader(new InputStreamReader(wos));
		List<String> words = new ArrayList<String>();

		String in = br.readLine();
		String let = letr.readLine();
		String bigs = bigr.readLine();
		String word = wor.readLine();

		StringBuilder CipherString =  new StringBuilder();
		ArrayList<KeyAndString> attempts = new ArrayList<KeyAndString>();

		while (in != null){
			CipherString.append(in);
			CipherString.append(" ");
			in = br.readLine();
		}

		while (let != null){
			StringTokenizer stl = new StringTokenizer(let, ",");
			String letter = stl.nextToken();
			int score = Integer.parseInt(stl.nextToken());
			letters.put(letter.charAt(0), score);
			let = letr.readLine();
		}

		while (bigs != null){
			StringTokenizer bgr = new StringTokenizer(bigs, ",");
			String bigram = bgr.nextToken();
			int score = Integer.parseInt(bgr.nextToken());
			bigrams.put(bigram, score);
			bigs = bigr.readLine();
		}

		while (word != null){
			words.add(word);
			word = wor.readLine();
		}

		for (int key = 0; key < 0xffff; key++){
			StringTokenizer st = new StringTokenizer(CipherString.toString());
			StringBuilder sb = null;
			sb =  new StringBuilder();
			int temp;
			while (st.hasMoreTokens()){
				temp = Coder.decrypt(key, Hex16.convert(st.nextToken()));
				int	i = temp;
				int	c0 = i / 256;
				int	c1 = i % 256;
				sb.append((char)c0);
				if (c1 != 0){
					sb.append((char)c1);	
				}
			}
			KeyAndString a = new KeyAndString(key, sb.toString());
			attempts.add(a);
		}

		int maxCount = 0;
		KeyAndString best = null;
		for(int i = 0; i < attempts.size(); i++){
			KeyAndString a = attempts.get(i);
			String sb = a.getSb();
			List<String> list = wholeWords(sb);
			Iterator<String> it = list.iterator();
			int score = 0;
			while (it.hasNext()){
				String s = it.next();
				if (!words.contains(s)){
					score -= 1000;	
				}else{
					score += 1000;
				}
			}

			for(int j = 0; j < sb.length(); j++){
				Character current = sb.charAt(j);
				if(j<sb.length()-1){
					Character next = sb.charAt(j + 1);
					String bigram = current.toString().concat(next.toString()).toLowerCase();

					if (bigrams.containsKey(bigram)){

						score += bigrams.get(bigram);
					}
				}

				if (letters.containsKey(current)){
					score += letters.get(current);
				}
			}
			if(score>maxCount){
				maxCount = score;
				best = a;
			}
		}
		System.out.println(best.getSb().toString());
		System.out.println(Integer.toHexString(best.getKey()));
		long endTime = System.nanoTime();

		long duration = endTime - startTime;
		System.out.println(duration);
	}

}

