
public class CourseInfo {
	private int level;
	private String semester;
	private int credit;
	private String courseCode;
	private String name;
	private String description;
	private String entryR;
	private String asses;
	private String mainAsses;

	public CourseInfo(int level, String semester, String description, String entryR, String coR, String asses, String mainAsses) {
		this.level = level;
		this.semester = semester;
		this.description = description;
		this.entryR = entryR;
		this.asses = asses;
		this.mainAsses = mainAsses;
	}

	public CourseInfo(){
	}
	public String getCourseCode() {
		return courseCode;
	}

	public void setCourseCode(String courseCode) {
		this.courseCode = courseCode;
	}
	
	public int getCredit() {
		return credit;
	}

	public void setCredit(int credit) {
		this.credit = credit;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
	public int getLevel() {
		return level;
	}
	public void setLevel(int level) {
		this.level = level;
	}
	public String getSemester() {
		return semester;
	}
	public void setSemester(String semester) {
		this.semester = semester;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
	public String getEntryR() {
		return entryR;
	}
	public void setEntryR(String entryR) {
		this.entryR = entryR;
	}
	public String getAsses() {
		return asses;
	}
	public void setAsses(String asses) {
		this.asses = asses;
	}
	public String getMainAsses() {
		return mainAsses;
	}
	public void setMainAsses(String mainAsses) {
		this.mainAsses = mainAsses;
	}
	
	
	public String toString(){
		return level+"~"+semester+"~"+credit+"~"+courseCode+"~"+name+"~"+description+"~"+entryR+"~"+asses+"~"+mainAsses;
	}
	
}
