import java.util.ArrayList;


public class Binarisation {
	ArrayList<ArrayList<Integer>> array;
	ArrayList<ArrayList<Integer>> intensity;
	int L;
	
	public Binarisation(ArrayList<ArrayList<Integer>> array, ArrayList<ArrayList<Integer>> intensity, int L){
		this.array = array;
		this.intensity = intensity;
		this.L = L;
	}
	
	public Integer[] createHistogram(){
		Integer[] histogram = new Integer[L];
		for (int i = 0;i<L;i++){
			histogram[i] = 0;
		}
		for (int i=0;i<intensity.size();i++){
			for (int j=0;j<intensity.get(i).size();j++){
				histogram[intensity.get(i).get(j)] += 1;
			}
		}
		return histogram;
	}
	
	public ArrayList<Integer[]> getGroups(Integer[] histogram, int k){
		Integer[] lowArray = new Integer[k];
		Integer[] highArray = new Integer[L-k];
		System.arraycopy(histogram, 1, lowArray, 0, k);
		System.arraycopy(histogram, 1, highArray, k, L);
		ArrayList<Integer[]> groups = new ArrayList<Integer[]>();
		groups.add(lowArray);
		groups.add(highArray);
		return groups;
	}
	
	public int mean(Integer[] list){
		int sum = 0;
		for(int j = 0;j<list.length;j++){
			sum += list[j];
		}
		return sum/list.length;
	}
	
	public ArrayList<Integer> calcVariance(ArrayList<Integer[]> groups){
		ArrayList<Integer> var = new ArrayList<Integer>();
		
		for(int i = 0;i<2;i++){
			int mean = mean(groups.get(i));
			int diffSum = 0;
			for(int j = 0;j<groups.get(i).length;j++){
				diffSum += (int) Math.pow(groups.get(i)[j] - mean, 2);
			}
			var.add(diffSum/groups.get(i).length);
			
		}
		return var;
	}
	
	public void popList(){
		for (int k = 0;k<L;k++){
			
			array.add(calcVariance(getGroups(createHistogram(), k)));
			
		}
	}
	
	public ArrayList<Integer> findMinDiff(){
		int minDiff = 100000;
		int t1;
		int t2;
		for(int i = 0; i<array.size();i++){
			if (Math.abs(array.get(0).get(j)array.get(0)) < minDiff){
				
			}
		}
	}

}
