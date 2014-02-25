import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class TMT2 {
	final static int N = 0x00ff;
	final static int L = 0x00ff;
	public static int tableHasKey(int cipher, Table table, int plainTxt, int org){

		
		int x2 = table.getTab().get(cipher);
		int x1 = Coder.encrypt(x2, plainTxt);
		for (int j = 0;j<N;j++){
			x2 = Coder.encrypt(x1, plainTxt);
			if(x2==org){
				return x1;
			}
			x1 = Coder.encrypt(x2, plainTxt);
			if(x1==org){
				return x2;
			}
		}
		return -1;
	}
	
	@SuppressWarnings("resource")
	public	static void main(String[] args) throws IOException{
		long startTime = System.nanoTime();
		
		BufferedInputStream bisR = new BufferedInputStream(System.in);
		BufferedReader brR = new BufferedReader(new InputStreamReader(bisR));
		
		System.out.println("Type in the location of the plain text to decrypt: ");
		String plainText = brR.readLine();
		System.out.println("Type in the location of the cipher file: ");
		String cipherText = brR.readLine();
		System.out.println("Type in the location of the table file (hint, TMT1 saves it to 'table.txt': ");
		String tabletxt = brR.readLine();

		
		FileInputStream fin = new FileInputStream(plainText);
		BufferedInputStream bisT = new BufferedInputStream(fin);
		BufferedReader brT = new BufferedReader(new InputStreamReader(bisT));
		
		int plainTxt = Hex16.convert(brT.readLine());
		FileInputStream fin2 = new FileInputStream(cipherText);
		BufferedInputStream bisC = new BufferedInputStream(fin2);
		BufferedReader brC = new BufferedReader(new InputStreamReader(bisC));
		StringBuilder sbCipher =  new StringBuilder();
		
		FileInputStream fin3 = new FileInputStream(tabletxt);
		BufferedInputStream bisTab = new BufferedInputStream(fin3);
		BufferedReader brTab = new BufferedReader(new InputStreamReader(bisTab));
		
		String in = brC.readLine();
		String tableVal = brTab.readLine();
		Table table = new Table();
		
		int cipher = Hex16.convert(in);
		while(in !=null){
			sbCipher.append(in);
			sbCipher.append(" ");
			in = brC.readLine();
		}
		
		while(tableVal != null){
			StringTokenizer tableTokenizer = new StringTokenizer(tableVal);
			table.add(Integer.parseInt(tableTokenizer.nextToken()), Integer.parseInt(tableTokenizer.nextToken()));
			tableVal = brTab.readLine();
		}
		
		int key = -1;
		if (table.getTab().containsKey(cipher)){
			key = tableHasKey(cipher, table, plainTxt, cipher);
		} else{
			int x2 = cipher;
			int x1 = Coder.encrypt(x2, plainTxt);
			for (int j = 0;j<0x00ff;j++){		
				x2 = Coder.encrypt(x1, plainTxt);
				if(table.getTab().containsKey(x2)){
					key = tableHasKey(x2, table, plainTxt, cipher);
					if(key == -1)break;
				}
				x1 = Coder.encrypt(x2, plainTxt);
				if(table.getTab().containsKey(x1)){
					key = tableHasKey(x1, table, plainTxt, cipher);
					if(key == -1)break;
				}
			}
			
		}
		StringTokenizer st = new StringTokenizer(sbCipher.toString());
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
		if(key!=-1){
			System.out.println("Message: " + sb.toString());
			
			System.out.println("Key: " + key);
			
		}else{
			System.out.println("Key not found in system try again!");
		}

		long endTime = System.nanoTime();

		long duration = endTime - startTime;
		System.out.println("Duration of operation: " + duration);
	}

}
