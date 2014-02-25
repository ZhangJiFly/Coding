import FormatIO.EofX;
import FormatIO.FileIn;
import FormatIO.FileOut;


public class KnownPlainTextAttack {
	public void findKey() throws EofX{
		
		FileIn	fin  = new FileIn("KnownPLainText.txt");
		
		int plaintext = Hex16.convert(fin.readWord());
		int cipherblock1 = Hex16.convert("0x9d00");

		for (Integer key1 = 0; key1 < 0xffff; key1++){
			if (plaintext == Coder.decrypt(key1, cipherblock1)){
				System.out.println(Integer.toHexString(key1));
				break;
			}

		}
	}
}
