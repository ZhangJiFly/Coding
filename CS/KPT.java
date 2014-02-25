import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class KPT {


	@SuppressWarnings("resource")
	public	static void main(String[] args) throws IOException{

		long startTime = System.nanoTime();
		
		BufferedInputStream bisR = new BufferedInputStream(System.in);
		BufferedReader brR = new BufferedReader(new InputStreamReader(bisR));
		
		System.out.println("Type in the location of the plain text file: ");
		String plainText = brR.readLine();
		System.out.println("Type in the location of the cipher text to decrypt: ");
		String cipherText = brR.readLine();


		
		FileInputStream finT = new FileInputStream(plainText);
		BufferedInputStream bisT = new BufferedInputStream(finT);
		BufferedReader brT = new BufferedReader(new InputStreamReader(bisT));

		FileInputStream finC = new FileInputStream(cipherText);
		BufferedInputStream bisC = new BufferedInputStream(finC);
		BufferedReader brC = new BufferedReader(new InputStreamReader(bisC));
		
		
		int plaintext = Hex16.convert(brT.readLine());
		String cipherBlock = brC.readLine();
		
		StringBuilder CipherString =  new StringBuilder();
		
		while (cipherBlock != null){
			CipherString.append(cipherBlock);
			CipherString.append(" ");
			cipherBlock = brC.readLine();
		}
		int key = 0;
		StringTokenizer st = new StringTokenizer(CipherString.toString());
		int Block = Hex16.convert(st.nextToken());		
		for (Integer key1 = 0; key1 < 0xffff; key1++){
			if (plaintext == Coder.decrypt(key1, Block)){
				key = key1;
				break;
			}

		}
		
		StringBuilder sb = null;
		sb =  new StringBuilder();
		int temp;
		while (st.hasMoreTokens()){
			temp = Coder.decrypt(key, Block);
			int	i = temp;
			int	c0 = i / 256;
			int	c1 = i % 256;
			sb.append((char)c0);
			if (c1 != 0){
				sb.append((char)c1);	
			}
			Block = Hex16.convert(st.nextToken());

		}
		
		System.out.println(sb);
		System.out.println(Integer.toHexString(key));
		long endTime = System.nanoTime();

		long duration = endTime - startTime;
		System.out.println(duration);
	}
}
