
/**
 * Lookup table based on a HashMap
 * @author ron
 *
 */

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import FormatIO.FileOut;

public class Table 
{	
	private	Map<Integer,Integer>	tab;
	
	public Map<Integer, Integer> getTab() {
		return tab;
	}

	public void setTab(Map<Integer, Integer> tab) {
		this.tab = tab;
	}

	public	Table()
	{
		tab = new HashMap<Integer,Integer>();
	}
	
	public	void	add(int key, int data)
	{
		tab.put(new Integer(key), new Integer(data));
	}

	public	int	find(int key)	// return data or -1
	{
		Integer	keyobj = new Integer(key);
		if (tab.containsKey(keyobj))
		{
			Integer	io = (Integer) tab.get(keyobj);
			return io.intValue();
		}
		else
			return -1;
	}
	
	public void saveTable(){
		FileOut fout = new FileOut("table.txt");
		Set<Integer> keys = tab.keySet();
		Iterator<Integer> it = keys.iterator();
		while (it.hasNext()){
			Integer key = it.next();
			Integer data = tab.get(key);
			fout.println(key + " " + data);
		}
	
		
	}
}
