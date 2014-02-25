import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;


public class TMT {
	final static int N = 1000;
	
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
	
	public static Table createTable(List<Integer> subSet, int plainTxt){
		Table table = new Table();
		for (int i=0;i<subSet.size();i++){
			int x0 = subSet.get(i);
			int x2 = x0;
			int x1 = Coder.encrypt(x2, plainTxt);
			for (int j = 0;j<N/10;j++){
				x2 = Coder.encrypt(x1, plainTxt);
				x1 = Coder.encrypt(x2, plainTxt);
			}
			table.add(x1,x0);
		}
		table.saveTable();
		return table;
	}
	
	public	static void main(String[] args) throws IOException{
		final int L = 0x0f0f;
		long startTime = System.nanoTime();
		FileInputStream fin = new FileInputStream("/Users/Crippled.Josh/Coding/CS/TMTPlain.txt");
		BufferedInputStream bisT = new BufferedInputStream(fin);
		BufferedReader brT = new BufferedReader(new InputStreamReader(bisT));
		
		FileInputStream fin2 = new FileInputStream("/Users/Crippled.Josh/Coding/CS/TMTCipher.txt");
		BufferedInputStream bisC = new BufferedInputStream(fin2);
		BufferedReader brC = new BufferedReader(new InputStreamReader(bisC));
		StringBuilder sbCipher =  new StringBuilder();
		
		FileInputStream fin3 = new FileInputStream("/Users/Crippled.Josh/Coding/CS/table.txt");
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
		
		
		int plainTxt = Hex16.convert(brT.readLine());
		List<Integer> passwords = new ArrayList<Integer>();
		List<Integer> subSet = new ArrayList<Integer>();
		for (int i=0;i<0xffff;i++){
			passwords.add(i);
		}
		
		int added = 0xffff/L;
		for (int i=1;i<0xffff;i += added ){
			subSet.add(i);
		}
		
		while(tableVal != null){
			StringTokenizer tableTokenizer = new StringTokenizer(tableVal);
			table.add(Integer.parseInt(tableTokenizer.nextToken()), Integer.parseInt(tableTokenizer.nextToken()));
			tableVal = brTab.readLine();
		}
		
		//Table table = createTable(subSet, plainTxt);
		
		int key = -1;
		if (table.getTab().containsKey(cipher)){
			key = tableHasKey(cipher, table, plainTxt, cipher);
		} else{
			int x2 = cipher;
			int x1 = Coder.encrypt(x2, plainTxt);
			for (int j = 0;j<100;j++){		
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
		
		System.out.print(sb.toString());
		
		System.out.println(key);
		long endTime = System.nanoTime();

		long duration = endTime - startTime;
		System.out.println(duration);
	}

}
