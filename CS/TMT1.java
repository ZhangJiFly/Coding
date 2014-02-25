import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.StringTokenizer;


public class TMT1 {
	final static int N = 0x00ff;
	final static int L = 0x00ff;
	
	
	public static Table createTable(int plainTxt){
		long startTime = System.nanoTime();
		List<Integer> subSet = new ArrayList<Integer>();
		Random generator = new Random(startTime);
		for (int i=0;i<N;i++ ){
			int random = generator.nextInt(0xffff) ;
			subSet.add(random);
		}
		System.out.println(subSet.size());
		Table table = new Table();
		for (int i=0;i<subSet.size();i++){
			int x0 = subSet.get(i);
			int x2 = x0;
			int x1 = Coder.encrypt(x2, plainTxt);
			for (int j = 0;j<N-1;j++){
				x2 = Coder.encrypt(x1, plainTxt);
				x1 = Coder.encrypt(x2, plainTxt);
			}
			table.add(x1,x0);
		}
		table.saveTable();
		return table;
	}
	
	public	static void main(String[] args) throws IOException{
		BufferedInputStream bisR = new BufferedInputStream(System.in);
		BufferedReader brR = new BufferedReader(new InputStreamReader(bisR));
		
		System.out.println("Type in the filename of the plain text file: ");
		String plainText = brR.readLine();

		
		FileInputStream fin = new FileInputStream(plainText);
		BufferedInputStream bisT = new BufferedInputStream(fin);
		BufferedReader brT = new BufferedReader(new InputStreamReader(bisT));
		
		int plainTxt = Hex16.convert(brT.readLine());
		createTable(plainTxt);
		
		
		
		
	}

}
