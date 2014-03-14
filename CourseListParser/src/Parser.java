import java.io.IOException;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.StringTokenizer;

import FormatIO.FileOut;


public class Parser {


	public	static void main(String[] args) throws IOException{
		Map<String, CourseInfo> map = new HashMap<String, CourseInfo>();

		FileInputStream fin = new FileInputStream("/Users/Crippled.Josh/Coding/Dissertation/Resources/SchoolofComputingScienceCourses.txt");
		BufferedInputStream bis = new BufferedInputStream(fin);
		BufferedReader br = new BufferedReader(new InputStreamReader(bis));

		StringBuilder totalString =  new StringBuilder();
		String in = br.readLine();
		int i = 0;
		while (in != null){
			totalString.append(in);
			totalString.append("\n");
			in = br.readLine();
		}


		StringTokenizer stCourses = new StringTokenizer(totalString.toString(),"~");

		while (stCourses.hasMoreTokens()){
			CourseInfo courseInfo = new CourseInfo();
			String Data = stCourses.nextToken();
			//System.out.println(Data);
			StringTokenizer stDataLine = new StringTokenizer(Data, "\n");

			while (stDataLine.hasMoreTokens()){
				
				String element = stDataLine.nextToken();
				//System.out.println(element);
				if(element.contains("COMPSCI")){
					int index = element.indexOf("COMPSCI");
					courseInfo.setName(element.substring(0,index));
					courseInfo.setCourseCode(element.substring(index));
				}
				else if(element.contains("(SIT)")){
					break;
				}
				else if(element.contains("Credits:")){
					courseInfo.setCredit(Integer.parseInt(element.substring(9)));
				}
				else if(element.contains("Level:")){
					//System.out.println(element);
					courseInfo.setLevel(Integer.parseInt(element.substring(13, 14)));
				}
				else if(element.contains("Typically Offered:")){
					if(element.contains("Runs Throughout")){
						courseInfo.setSemester("1 & 2");
					}else{

						courseInfo.setSemester(element.substring(19));
					}
				}
				else if(element.contains("Short Description")){
					element = stDataLine.nextToken();
					StringBuilder sb = new StringBuilder();
					while(!element.contains("Requirements of Entry")){

						sb.append(element);
						element = stDataLine.nextToken();
						//courseInfo.setLevel(Integer.parseInt(element.substring(13, 14)));
					}
					courseInfo.setDescription(sb.toString());
				}
				if(element.contains("Requirements of Entry")){
					element = stDataLine.nextToken();
					StringBuilder sb = new StringBuilder();
					while(!element.contains("Excluded Courses")){

						sb.append(element);
						element = stDataLine.nextToken();
						//courseInfo.setLevel(Integer.parseInt(element.substring(13, 14)));
					}
					courseInfo.setEntryR(sb.toString());

				}
				if(element.contains("Assessment")){
					element = stDataLine.nextToken();
					StringBuilder sb = new StringBuilder();
					while(!element.contains("Main Assessment In:")){

						sb.append(element);
						element = stDataLine.nextToken();
						//courseInfo.setLevel(Integer.parseInt(element.substring(13, 14)));
					}
					courseInfo.setAsses(sb.toString());
				}
				if(element.contains("Main Assessment In:")){
					courseInfo.setMainAsses(element.substring(20));
				}
				
			}
			map.put(courseInfo.getCourseCode(),courseInfo);
			
		}
		br.close();
		FileOut fout = new FileOut("CourseInfoText.csv");
		System.out.println(map.size());
		map.remove(null);
		fout.println("Level~Semester~Credit~CourseId~Name~Description~EntryRequirements~Assessment~MainAssessment");
		for(String key: map.keySet()){
			
			CourseInfo val = map.get(key);
			fout.println(val.toString());
		}
	}
}
