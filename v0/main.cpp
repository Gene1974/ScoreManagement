#include<iostream>
#include<string>
#include<math.h>
#include<iomanip>
#include<fstream>
#pragma warning(disable:4996)
using namespace std;


class DataBase;            //类和函数的提前声明
string SetPassword();






class Grade
{
	public:
		Grade(){}
		Grade(int a,int b, int c, int d, int e);
		friend class Single;
		friend class DataBase;
	protected:
		int Midterm,Final,Homework,Experiment,Project;
};

Grade::Grade(int a,int b, int c, int d, int e)
{
	Midterm=a;
	Final=b;
	Homework=c;
	Experiment=d;
	Project=e;
}



class Course:virtual public Grade
{
	public:
		Course(){CourseStudentNumber=0;}     //默认构造函数使选课学生数量为0
		~Course();
		Course(string x,long long y,int z,long long m,int a=0,int b=0,int c=0,int d=0,int e=0);
		void SchoolSet(string x,long long y,int z,long long m);
		friend class DataBase;
		friend class Single;
	protected:
		int MidtermPercent,FinalPercent,HomeworkPercent,ExperimentPercent,ProjectPercent;     //课程成绩占比是课程的特性
		long long CourseId;
		string Name;
		long long TeacherId;       //教师的编号作为课程类的成员，便于查找和定位
		int Credit;
		long long *CourseStudentId;       //选课的学生学号以动态数组形式作为课程类的成员，便于查找和定位
		int CourseStudentNumber;       //选课学生的数量
};

Course::Course(string x,long long y,int z,long long m,int a,int b,int c,int d,int e)
{
	Name=x;
	CourseId=y;
	Credit=z;
	TeacherId=m;
	MidtermPercent=a;
	FinalPercent=b;
	HomeworkPercent=c;
	ExperimentPercent=d;
	ProjectPercent=e;
	CourseStudentNumber=0;
}

void Course::SchoolSet(string x,long long y,int z,long long m)      //用于学校重新设置课程信息
{
	Name=x;
	CourseId=y;
	Credit=z;
	TeacherId=m;
	CourseStudentNumber=0;
}

Course::~Course()
{
	if(CourseStudentNumber==0);
	else delete[]CourseStudentId;     //学生数量不为0则删除储存选课学生学号的动态数组
}




class Teacher:virtual public Course
{
	public:
		Teacher(){TeacherCourseNumber=0;}     //默认构造函数使教师所教授课程数量为0
		~Teacher();
		Teacher(string a,long long b,string c);
		friend class DataBase;
	protected:
		string Name;
		long long Id;
		string Password;
		Course *TeacherCourse;         //教师所教授课程用动态数组表示
		int TeacherCourseNumber;
};

Teacher::Teacher(string a,long long b,string c)
{
	Name=a;
	Id=b;
	Password=c;
	TeacherCourseNumber=0;
}

Teacher::~Teacher()
{
	if(TeacherCourseNumber==0);
	else delete[]TeacherCourse;     //教师教授课程数量不为0则删除用于储存教授课程的动态数组
}




class Student:virtual public Grade
{
	public:
		Student(string a,long long b,string c);
		Student(){StudentCourseNumber=0;}     //默认构造函数使学生选课数量为0
		~Student();
		friend class DataBase;
	protected:
		string Name;
		long long Id;
		string Password;
		double GPA;
		int StudentCredit;
		long long *StudentCourseId;     //学生所选课程的课程序号以动态数组形式表示
		int StudentCourseNumber;
};

Student::Student(string a,long long b,string c)
{
	Name=a;
	Id=b;
	Password=c;
	StudentCourseNumber=0;
	StudentCredit = 0;
}

Student::~Student()
{
	if(StudentCourseNumber==0);
	else delete[]StudentCourseId;     //选课数量不为0则删除用于储存所选课程课程序号的动态数组
}




class Single:virtual public Course,virtual public Student
{
	public:
		Single(){}
		Single(long long a,long long b,long long c,int d,int e,int f,int g,int h);
		void SingleFindCourse();
		void GetGeneral();         //利用各部分成绩和所占比例计算总评成绩
		void CalcuPoint();         //计算绩点和对应的等级
		friend class DataBase;
	protected:
		long long StudentId;
		long long TeacherId;
		long long SingleCourseId;
		Course SingleCourse;
		Grade SingleGrade;
		int General;
		double Point;
		char* Level;
};

Single::Single(long long a,long long b,long long c,int d,int e,int f,int g,int h)
{
	StudentId=a;
	TeacherId=b;
	SingleCourseId=c;
	SingleGrade=Grade(d,e,f,g,h);
	this->SingleFindCourse();
}

void Single::SingleFindCourse()
{
	ifstream op;
	string n;
	long long m,p;
	int q;
	int a1,a2,a3,a4,a5;
	op.open("Course.txt",ios_base::in);     //由于课程类还未建立，必须扫文件
	while(!op.eof())
	{
		op>>m;
		if(op.fail()) break;		
		op>>n;
		op>>q;
		op>>p;
		op>>a1;op>>a2;op>>a3;op>>a4;op>>a5;
		if(m==SingleCourseId)
		{
			SingleCourse=Course(n,m,q,p,a1,a2,a3,a4,a5);
			GetGeneral();
			CalcuPoint();
			break;
		}
	}
}

void Single::GetGeneral()     //加权计算总评成绩
{
	General=(SingleGrade.Midterm*SingleCourse.MidtermPercent+SingleGrade.Final*SingleCourse.FinalPercent+SingleGrade.Homework*SingleCourse.HomeworkPercent+SingleGrade.Experiment*SingleCourse.ExperimentPercent+SingleGrade.Project*SingleCourse.ProjectPercent)/100;
}

void Single::CalcuPoint()         //直接应用清华现有的等级制进行绩点和等级的换算
{
	if(General<60)
	{
		Point=0.0;
		Level="F";
	}
	if(General>=60&&Final<=62)
	{
		Point=1.0;
		Level="D";
	}
	if(General>=63&&Final<=66)
	{
		Point=1.3;
		Level="D+";
	}
	if(General>=67&&Final<=69)
	{
		Point=1.7;
		Level="C-";
	}
	if(General>=70&&Final<=72)
	{
		Point=2.0;
		Level="C";
	}
	if(General>=73&&Final<=76)
	{
		Point=2.3;
		Level="C+";
	}
	if(General>=77&&Final<=79)
	{
		Point=2.7;
		Level="B-";
	}
	if(General>=80&&Final<=84)
	{
		Point=3.0;
		Level="B";
	}
	if(General>=85&&Final<=89)
	{
		Point=3.3;
		Level="B+";
	}
	if(General>=90&&Final<=94)
	{
		Point=3.7;
		Level="A-";
	}
	if(General>=95&&Final<=100)
	{
		Point=4.0;
		Level="A";
	}
}


class DataBase:virtual public Single,virtual public Teacher     //所有信息都储存在DataBase类成员中
{
	public:
		DataBase()     //默认构造函数是所有信息数量都为0
		{
			StudentNumber=0;
			CourseNumber=0;
			TeacherNumber=0;
			DataNumber=0;
		}
		~DataBase();
		bool AddStudent();         //用于学生注册
		bool AddTeacher();         //用于教师注册
		void SchoolZhuce();        //用于学校注册，由于在本系统内系统只允许注册一次，故没有返回值
		bool StudentDenglu();      //用于学生的登录及后续操作
		bool TeacherDenglu();      //用于教师的登录及后续操作
		bool SchoolDenglu();       //用于学校的登录及后续操作
		void SetSystem();
		bool Begin();
		void CloseSystem();
		void SetStudent();         //用于在系统开始运行时将储存在文件内的学生信息导入到类内
		void SetTeacher();         //用于在系统开始运行时将储存在文件内的教师信息导入到类内
		void SetCourse();          //用于在系统开始运行时将储存在文件内的课程信息导入到类内
		void SetSingle();          //用于在系统开始运行时将储存在文件内的成绩信息导入到类内
		void ResetStudent();       //用于在系统结束运行时将储存在类内的学生信息导入到文件内
		void ResetTeacher();       //用于在系统结束运行时将储存在类内的教师信息导入到文件内
		void ResetCourse();        //用于在系统结束运行时将储存在类内的课程信息导入到文件内
		void ResetSingle();        //用于在系统结束运行时将储存在类内的成绩信息导入到文件内
	private:
		Single *Dat;        //成绩信息以成员数组表示
		int DataNumber;        //成绩数量
		Student *Stu;        //学生信息以成员数组表示
		int StudentNumber;        //学生数量
		Course *Cou;        //课程信息以成员数组表示
		int CourseNumber;        //课程数量
		Teacher *Tea;        //教师信息以成员数组表示
		int TeacherNumber;        //教师数量
		string SchoolPassword;        //学校的登录密码唯一存在，直接储存为DataBase类的成员
};

DataBase::~DataBase()
{
	if(StudentNumber==0);
	else delete[]Stu;     //学生数量不为0则删除储存学生信息的动态数组
	if(CourseNumber==0);
	else delete[]Cou;     //课程数量不为0则删除储存课程信息的动态数组
	if(TeacherNumber==0);
	else delete[]Tea;     //教师数量不为0则删除储存教师信息的动态数组
	if(DataNumber==0);
	else delete[]Dat;     //成绩数量不为0则删除储存成绩信息的动态数组
}




int main()
{
	DataBase Tsinghua;
	Tsinghua.SetSystem();        //将储存在文件里的内容读取出来
	cout<<"欢迎登录成绩管理系统！"<<endl;
	while(Tsinghua.Begin());        //操作部分
	Tsinghua.CloseSystem();        //将操作完成后的内容重新写入文件
}



void DataBase::SetSystem()
{
	ifstream op;
	op.open("Single.txt",ios_base::in);      //新建成绩信息
	if(op==0)     //文件不存在
	{
		op.close();     //关闭文件
		DataNumber=0;     //成绩数量置为0
	}
	else
	{
		op.close();     //关闭文件
		SetSingle();     //读文件
	}
	

	op.open("Student.txt",ios_base::in);      //新建学生信息
	if(op==0)     //文件不存在
	{
		op.close();     //关闭文件
		StudentNumber=0;     //学生数量置为0
	}
	else
	{
		op.close();     //关闭文件
		SetStudent();     //读文件
	}

	op.open("Course.txt",ios_base::in);      //新建课程信息
	if(op==0)     //文件不存在
	{
		op.close();     //关闭文件
		CourseNumber=0;     //课程数量置为0
	}
	else
	{
		op.close();     //关闭文件
		SetCourse();     //读文件
	}

	op.open("Teacher.txt",ios_base::in);      //新建教师信息
	if(op==0)     //文件不存在
	{
		op.close();     //关闭文件
		TeacherNumber=0;     //教师数量置为0
	}
	else
	{
		op.close();     //关闭文件
		SetTeacher();     //读文件
	}
}

void DataBase::SetStudent()
{
	ifstream op;
	op.open("Student.txt",ios_base::in);
	StudentNumber=0;
	while(!op.eof())
	{
		string n,q;
		long long m;
		op>>n;
		if(op.fail()) break;		
		op>>m;
		op>>q;
		StudentNumber++;     //计学生数量
	}
	op.clear();
	op.sync();
	op.seekg(ios_base::beg);
	Stu=new Student[StudentNumber];
	for(int j=0;j<StudentNumber;j++)     //建立学生信息
	{
		string n,q;
		long long m;
		op>>n;
		if(op.fail()) break;		
		op>>m;
		op>>q;
		Stu[j].Name=n;
		Stu[j].Id=m;
		Stu[j].Password=q;
		Stu[j].StudentCourseNumber=0;
		Stu[j].StudentCredit=0;
		double AddGrades=0;
		for(int i=0;i<DataNumber;i++)     //所有成绩信息
		{
			if(m==Dat[i].StudentId)
			{
				Stu[j].StudentCourseNumber++;     //计学生选课数量
			}
		}
		Stu[j].StudentCourseId=new long long[Stu[j].StudentCourseNumber];     //新建学生选课信息
		static int i = 0;     //静态计数器
		for(int k=0;k<Stu[j].StudentCourseNumber;k++)
		{
			Stu[j].StudentCourseId[k]=Dat[i].SingleCourse.CourseId;
			AddGrades+=Dat[i].Point*Dat[i].SingleCourse.Credit;
			Stu[j].StudentCredit+=Dat[i].SingleCourse.Credit;
			i++;
		}
		if(Stu[j].StudentCredit!=0)
		{
			Stu[j].GPA=AddGrades/Stu[j].StudentCredit;
		}
		else
		{
			Stu[j].GPA=0;
		}
	}
	op.close();
}

void DataBase::SetCourse()
{
	ifstream op;
	op.open("Course.txt",ios_base::in);
	CourseNumber=0;
	while(!op.eof())
	{
		string n;
		long long m,p;
		int q;
		int a1,a2,a3,a4,a5;
		Course b;
		op>>m;
		if(op.fail()) break;		
		op>>n;
		op>>q;
		op>>p;
		op>>a1;op>>a2;op>>a3;op>>a4;op>>a5;
		CourseNumber++;     //计课程数量
	}
	op.clear();
	op.sync();	
	op.seekg(ios_base::beg);
	Cou=new Course[CourseNumber];     //新建课程信息
	for(int j=0;j<CourseNumber;j++)
	{
		string n;
		long long m,p;
		int q;
		int a1,a2,a3,a4,a5;
		op>>m;
		if(op.fail()) break;		
		op>>n;
		op>>q;
		op>>p;
		op>>a1;op>>a2;op>>a3;op>>a4;op>>a5;
		Cou[j]=Course(n,m,q,p,a1,a2,a3,a4,a5);
		Cou[j].CourseStudentNumber=0;
		for(int i=0;i<DataNumber;i++)
		{
			if(m==Dat[i].SingleCourse.CourseId)
			{
				Cou[j].CourseStudentNumber++;     //计选课学生数量
			}
		}
		Cou[j].CourseStudentId=new long long[Cou[j].CourseStudentNumber];     //新建选课学生信息
		int k=0;
		{
			for(int i=0;i<DataNumber;i++)
			{
				if(m==Dat[i].SingleCourse.CourseId)
				{
					Cou[j].CourseStudentId[k++]=Dat[i].StudentId;
					if(k==Cou[j].CourseStudentNumber) break;
				}
			}
		}
	}
	op.clear();
	op.sync();	
	op.close();
}

void DataBase::SetTeacher()
{
	ifstream op;
	op.open("Teacher.txt",ios_base::in);
	TeacherNumber=0;
	while(!op.eof())
	{
		string n,q;
		long long m;
		Teacher b;
		op>>n;
		if(op.fail()) break;		
		op>>m;
		op>>q;
		TeacherNumber++;     //计教师数量
	}
	op.clear();
	op.sync();	
	op.seekg(ios_base::beg);
	Tea=new Teacher[TeacherNumber];     //新建教师信息
	for(int j=0;j<TeacherNumber;j++)
	{
		string n,q;
		long long m;
		op>>n;
		if(op.fail()) break;		
		op>>m;
		op>>q;
		Tea[j]=Teacher(n,m,q);
		Tea[j].TeacherCourseNumber=0;
		for(int i=0;i<DataNumber;i++)
		{
			if(m==Dat[i].SingleCourse.TeacherId)
			{
				Tea[j].TeacherCourseNumber++;     //计教师代课数量
			}
		}
		Tea[j].TeacherCourse=new Course[Tea[j].TeacherCourseNumber];     //新建教师代课信息
		for(int k=0;k<Tea[j].TeacherCourseNumber;k++)
		{
			for(int i=0;i<DataNumber;i++)
			{
				if(m==Dat[i].SingleCourse.CourseId)
				{
					Tea[j].TeacherCourse[k]=Dat[i].SingleCourse;
				}
			}
		}		
	}
	op.clear();
	op.sync();	
	op.close();
}

void DataBase::SetSingle()
{
	ifstream op;
	op.open("Single.txt",ios_base::in);
	DataNumber=0;
	while(!op.eof())
	{
		long long m,n,p;
		op>>m;
		if(op.fail()) break;		
		op>>n;op>>p;
		int a[5];
		for(int i=0;i<5;i++) op>>a[i];
		DataNumber++;     //计成绩数量
	}
	op.clear();
	op.sync();	
	op.seekg(ios_base::beg);
	Dat=new Single[DataNumber];     //新建成绩信息
	for(int j=0;j<DataNumber;j++)
	{
		long long m,n,p;
		op>>m;
		op>>n;op>>p;
		int a[5];
		for(int i=0;i<5;i++) op>>a[i];
		Dat[j]=Single(m,n,p,a[0],a[1],a[2],a[3],a[4]);
	}
	op.clear();
	op.sync();	
	op.close();
}

void DataBase::CloseSystem()
{
	ResetStudent();     //将学生信息重新写入文件
	ResetTeacher();     //将教师信息重新写入文件
	ResetCourse();     //将课程信息重新写入文件
	ResetSingle();     //将成绩信息重新写入文件
}

void DataBase::ResetStudent()
{
	if(StudentNumber==0);
	else 
	{
		ofstream op;
		op.open("Student.txt",ios_base::out);
		op<<Stu[0].Name<<'\n'<<Stu[0].Id<<'\n'<<Stu[0].Password;
		if(StudentNumber==1);
		else
		{
			for(int i=1;i<StudentNumber;i++)
			{
				op<<'\n'<<Stu[i].Name<<'\n'<<Stu[i].Id<<'\n'<<Stu[i].Password;
			}
		}
		op.close();
	}
}

void DataBase::ResetTeacher()
{
	if(TeacherNumber==0);
	else 
	{
		ofstream op;
		op.open("Teacher.txt",ios_base::out);
		op<<Tea[0].Name<<'\n'<<Tea[0].Id<<'\n'<<Tea[0].Password;
		if(TeacherNumber==1);
		else
		{
			for(int i=1;i<TeacherNumber;i++)
			{
				op<<'\n'<<Tea[i].Name<<'\n'<<Tea[i].Id<<'\n'<<Tea[i].Password;
			}
		}
		op.close();
	}
}

void DataBase::ResetCourse()
{
	if(CourseNumber==0);
	else 
	{
		ofstream op;
		op.open("Course.txt",ios_base::out);
		op<<Cou[0].CourseId<<'\n'<<Cou[0].Name<<'\n'<<Cou[0].Credit<<'\n'<<Cou[0].TeacherId<<'\n'<<Cou[0].MidtermPercent<<'\n'<<Cou[0].FinalPercent
			<<'\n'<<Cou[0].HomeworkPercent<<'\n'<<Cou[0].ExperimentPercent<<'\n'<<Cou[0].ProjectPercent;
		if(CourseNumber==1);
		else
		{
			for(int i=1;i<CourseNumber;i++)
			{
				op<<'\n'<<Cou[i].CourseId<<'\n'<<Cou[i].Name<<'\n'<<Cou[i].Credit<<'\n'<<Cou[i].TeacherId<<'\n'<<Cou[i].MidtermPercent<<'\n'<<Cou[i].FinalPercent
					<<'\n'<<Cou[i].HomeworkPercent<<'\n'<<Cou[i].ExperimentPercent<<'\n'<<Cou[i].ProjectPercent;
			}
		}
		op.close();
	}
}

void DataBase::ResetSingle()
{
	if(DataNumber==0);
	else 
	{
		ofstream op;
		op.open("Single.txt",ios_base::out);
		op<<Dat[0].StudentId<<'\n'<<Dat[0].TeacherId<<'\n'<<Dat[0].SingleCourse.CourseId<<'\n'<<Dat[0].SingleGrade.Midterm<<'\n'<<Dat[0].SingleGrade.Final<<'\n'
			<<Dat[0].SingleGrade.Homework<<'\n'<<Dat[0].SingleGrade.Experiment<<'\n'<<Dat[0].SingleGrade.Project;
		if(DataNumber==1);
		else
		{
			for(int i=1;i<DataNumber;i++)
			{
				op<<'\n'<<Dat[i].StudentId<<'\n'<<Dat[i].TeacherId<<'\n'<<Dat[i].SingleCourse.CourseId<<'\n'<<Dat[i].SingleGrade.Midterm<<'\n'<<Dat[i].SingleGrade.Final<<'\n'
					<<Dat[i].SingleGrade.Homework<<'\n'<<Dat[i].SingleGrade.Experiment<<'\n'<<Dat[i].SingleGrade.Project;
			}
		}
		op.close();
	}
}



bool DataBase::Begin()
{
	cout<<"请选择您要进行的操作："<<endl;
	cout<<"1.学生注册 2.教师注册 3.教务注册"<<endl;
	cout<<"4.学生登录 5.教师登录 6.教务登录"<<endl;
	cout<<"7.退出系统"<<endl;
	int BeginChoice;
	cin>>BeginChoice;
	cin.clear();
	cin.sync();
	bool flag1=0;
	bool flag2=0;
	switch(BeginChoice)
	{
	case 1:
		flag1=AddStudent();
		while(flag1==1)     //继续注册
		{
			flag1=AddStudent();
		}
		break;
	case 2:
		flag2=AddTeacher();     //继续注册
		while(flag2==1)
		{
			flag2=AddTeacher();
		}
		break;
	case 3:
		SchoolZhuce();
		break;
	case 4:
		StudentDenglu();
		break;
	case 5:
		TeacherDenglu();
		break;
	case 6:
		SchoolDenglu();
		break;
	case 7:
		return 0;
	default:
		cout<<"请输入1-7进行操作！"<<endl;
		break;
	}
	return 1;
}


bool DataBase::AddStudent()
{
	cout<<"欢迎来到学生注册！"<<endl;
	cout<<"请输入您的学号并按回车结束，输入0返回：";
	long long b;
	cin>>b;
	cin.clear();
	cin.sync();
	if(b==0) return 0;     //输入0返回
	for(int i=0;i<StudentNumber;i++)
	{
		if(Stu[i].Id==b)
		{
			cout<<"此学号已被注册！输入1继续注册，输入0返回主界面："<<endl;
			bool flag;
			cin>>flag;
			if(flag==0) return 0;     //输入0返回
			else if(flag==1) return 1;
			else
			{
				cout<<"输入有误！现在将返回主界面！"<<endl;
				return 0;
			}
			break;
		}
	}
	cout<<"请输入您的姓名，按回车结束：";
	string c,d;
	cin>>c;
	cin.clear();
	cin.sync();
	d=SetPassword();
	StudentNumber++;
	Student *m=new Student[StudentNumber];     //增加动态数组的长度
	for(int i=0;i<(StudentNumber-1);i++)
	{
		m[i]=Stu[i];
	}
	if(StudentNumber==1);
	else delete []Stu;
	Stu=new Student[StudentNumber];
	for(int i=0;i<(StudentNumber-1);i++)
	{
		Stu[i]=m[i];
	}
	delete []m;
	Stu[StudentNumber-1]=Student(c,b,d);
	Stu[StudentNumber-1].GPA=0;
	Stu[StudentNumber-1].StudentCredit=0;
	Stu[StudentNumber-1].StudentCourseNumber=0;
	for(int i=0;i<DataNumber;i++)
	{
		if(Stu[StudentNumber-1].Id==Dat[i].StudentId)
		{
			Stu[StudentNumber-1].StudentCourseNumber++;
		}
	}
	Stu[StudentNumber-1].StudentCourseId=new long long[Stu[StudentNumber-1].StudentCourseNumber];
	double AddGrades=0;     //更新成绩信息
	for(int k=0;k<Stu[StudentNumber-1].StudentCourseNumber;k++)
	{
		for(int i=0;i<DataNumber;i++)
		{
			if(Stu[StudentNumber-1].Id==Dat[i].StudentId)
			{
				Stu[StudentNumber-1].StudentCourseId[k]=Dat[i].SingleCourse.CourseId;
				AddGrades+=Dat[i].Point*Dat[i].Credit;
				Stu[StudentNumber-1].StudentCredit+=Dat[i].Credit;
			}
		}
	}
	Stu[StudentNumber-1].GPA=AddGrades/StudentCredit;
	cout<<"恭喜，注册成功！"<<endl;
	return 0;
}

bool DataBase::AddTeacher()
{
	cout<<"欢迎来到教师注册！"<<endl;
	cout<<"请输入您的教职工号并按回车结束，输入0返回：";
	long long b;
	cin>>b;
	cin.clear();
	cin.sync();
	if(b==0) return 0;     //输入0返回
	for(int i=0;i<TeacherNumber;i++)
	{
		if(Tea[i].Id==b)
		{
			cout<<"此学号已被注册！按1继续注册，按0返回主界面："<<endl;
			bool flag;
			cin>>flag;
			if(flag==0) return 0;     //输入0返回
			else if(flag==1) return 1;     //输入1返回并继续注册
			else
			{
				cout<<"输入有误！现在将返回主界面！"<<endl;
				return 0;
			}
			break;
		}
	}
	cout<<"请输入您的姓名，按回车结束：";
	string c,d;
	cin>>c;
	cin.clear();
	cin.sync();
	d=SetPassword();
	TeacherNumber++;
	Teacher *m=new Teacher[TeacherNumber];     //增加老师数量
	for(int i=0;i<(TeacherNumber-1);i++)
	{
		m[i]=Tea[i];
	}
	if(TeacherNumber==1);
	else delete []Tea;
	Tea=new Teacher[TeacherNumber];
	for(int i=0;i<(TeacherNumber-1);i++)
	{
		Tea[i]=m[i];
	}
	Tea[TeacherNumber-1]=Teacher(c,b,d);
	delete []m;
	Tea[TeacherNumber-1].TeacherCourseNumber=0;
	for(int i=0;i<DataNumber;i++)
	{
		if(Tea[TeacherNumber-1].Id==Dat[i].TeacherId)
		{
			Tea[TeacherNumber-1].TeacherCourseNumber++;
		}
	}
	Tea[TeacherNumber-1].TeacherCourse=new Course[Tea[TeacherNumber-1].TeacherCourseNumber];
	for(int k=0;k<TeacherCourseNumber;k++)
	{
		for(int i=0;i<CourseNumber;i++)
		{
			if(Tea[TeacherNumber-1].Id==Cou[i].TeacherId)
			{
				Tea[TeacherNumber-1].TeacherCourse[k]=Dat[i].SingleCourse;
			}
		}
	}
	cout<<"恭喜，注册成功！"<<endl;
	return 0;
}

void DataBase::SchoolZhuce()
{
	ifstream op1;
	op1.open("School.txt",ios_base::in);
	if(op1==0)     //文件不存在，说明学校没有注册
	{
		SchoolPassword=SetPassword();
		ofstream op2;
		op2.open("School.txt",ios_base::out);
		op2<<SchoolPassword;
		op2.close();
		cout<<"恭喜您！注册成功！"<<endl;
	}
	else     //文件存在，说明学校已注册
	{
		cout<<"学校账号已经存在！"<<endl;
	}
}

string SetPassword()
{
	cout<<"请设置您的密码，按回车结束：";
	string c;
	cin>>c;
	cin.clear();
	cin.sync();
	cout<<"请再次输入您的密码，按回车结束：";
	string d;
	cin>>d;
	cin.clear();
	cin.sync();
	if(c==d) return c;     //两次密码输入一致则返回
	else
	{
		cout<<"两次输入的密码不一致，请重新输入！"<<endl;
		string m=SetPassword();     //两次密码输入不一致则重新输入
		return m;
	}
}



bool DataBase::StudentDenglu()
{
	cout<<"请输入您的学号并按回车结束，输入0返回：";
	long long a;
	bool flag=0;
	cin>>a;
	cin.clear();
	cin.sync();
	if(a==0) return 0;     //输入0返回
	else
	{
		for(int i=0;i<StudentNumber;i++)
		{
			if(a==Stu[i].Id)
			{
				flag=1;
				cout<<"请输入密码："<<endl;
				string c;
				cin>>c;			
				if(c==Stu[i].Password)
				{
					cout<<"登录成功！欢迎您，"<<Stu[i].Name<<"同学。"<<endl;
					while(1)
					{
						cout<<"请选择您要进行的操作，按回车确认！"<<endl;
						cout<<"1.查看课程列表 2.查看成绩列表 3.查看GPA和总学分 4.退出系统"<<endl;
						int StudentDoChoice;
						cin>>StudentDoChoice;
						cin.clear();
						cin.sync();
						switch(StudentDoChoice)
						{
						case 1:
							cout<<setiosflags(ios_base::left)<<setw(20)<<"课程名称"<<setw(15)<<"课程序号"<<"学分"<<endl;
							for(int j=0;j<Stu[i].StudentCourseNumber;j++)
							{
								for(int k=0;k<CourseNumber;k++)
								{
									if(Stu[i].StudentCourseId[j]==Cou[k].CourseId)
										cout<<setiosflags(ios_base::left)<<setw(20)<<Cou[k].Name<<setw(15)<<Cou[k].CourseId<<Cou[k].Credit<<endl;
								}
							}
							break;
						case 2:
							cout<<setiosflags(ios_base::left)<<setw(10)<<"课程序号"<<setw(9)<<"总评成绩"<<setw(5)<<"绩点"<<setw(5)<<"等级"
								<<setw(9)<<"期中成绩"<<setw(10)<<"期末成绩"<<setw(10)<<"作业成绩"<<setw(10)<<"实验成绩"<<"大作业成绩"<<endl;
							for(int j=0;j<Stu[i].StudentCourseNumber;j++)
							{
								for(int k=0;k<DataNumber;k++)
								{
									if(Stu[i].Id==Dat[k].StudentId&&Stu[i].StudentCourseId[j]==Dat[k].SingleCourseId)
									{
										cout<<setiosflags(ios_base::left)<<setw(10)<<Stu[i].StudentCourseId[j]<<setw(10)<<Dat[k].General<<
											setw(6)<<Dat[k].Point<<setw(6)<<Dat[k].Level<<setw(10)<<Dat[k].SingleGrade.Midterm<<setw(10)<<Dat[k].SingleGrade.Final<<
											setw(10)<<Dat[k].SingleGrade.Homework<<setw(10)<<Dat[k].SingleGrade.Experiment<<Dat[k].SingleGrade.Project<<endl;
									}
								}
							}
							break;
						case 3:
							cout<<"您的总学分是"<<Stu[i].StudentCredit<<"您的GPA为"<<Stu[i].GPA<<endl;
							break;
						case 4:
							return 0;
							break;
						default:
							cout<<"请输入1-4之间的数字进行操作！"<<endl;
						}
					}
					return 1;
				}
				else
				{
					cout<<"密码错误！请重新登录！"<<endl;
					return 0;
				}
			}
		}
		if(flag==0)
		{
			cout<<"该用户不存在！请先注册！"<<endl;
		}
	}
	return 0;
}

bool DataBase::TeacherDenglu()
{
	cout<<"请输入您的教职工号并按回车结束，输入0返回：";
	long long a;
	bool flag=0;
	bool CourseExist=0;
	bool StudentExist=0;
	cin>>a;
	cin.clear();
	cin.sync();
	if(a==0) return 0;     //输入0返回
	else
	{
		for(int i=0;i<TeacherNumber;i++)
		{
			if(a==Tea[i].Id)
			{			
				flag=1;
				cout<<"请输入密码："<<endl;
				string c;
				cin>>c;			
				if(c==Tea[i].Password)
				{
					cout<<"登录成功！欢迎您，"<<Tea[i].Name<<"老师。"<<endl;
					while(1)
					{
						cout<<"请选择您要进行的操作，按回车确认！"<<endl;
						cout<<"1.查看课程列表 2.查看课程成绩列表 3.查看选课学生列表"<<endl;
						cout<<"4.查看成绩占比 5.设置成绩占比     6.修改成绩占比"<<endl;
						cout<<"7.录入成绩     8.修改成绩         9.退出系统"<<endl;
						int TeacherDoChoice;
						cin>>TeacherDoChoice;
						cin.clear();
						cin.sync();
						switch(TeacherDoChoice)
						{
						case 1:
							cout<<setiosflags(ios_base::left)<<setw(20)<<"课程名称"<<setw(15)<<"课程序号"<<"学分"<<endl;
							for(int k=0;k<CourseNumber;k++)
							{
								if(Tea[i].Id==Cou[k].TeacherId)
								{
									cout<<setiosflags(ios_base::left)<<setw(20)<<Cou[k].Name<<setw(15)<<Cou[k].CourseId<<Cou[k].Credit<<endl;
								}
							}
							break;
						case 2:
							cout<<"请输入课程序号并以回车确认，输入0返回：";
							long long d;
							cin>>d;
							cin.clear();
							cin.sync();
							if(d==0) break;
							else
							{
								for(int k=0;k<CourseNumber;k++)
								{
									if(Cou[k].CourseId==d)
									{
										cout<<setiosflags(ios_base::left)<<setw(20)<<"学生学号"<<setw(15)<<"学生姓名"<<"总评成绩"<<endl;
										for(int j=0;j<DataNumber;j++)
										{
											if(Tea[i].Id==Dat[j].TeacherId&&d==Dat[j].SingleCourse.CourseId)
											{
												cout<<setiosflags(ios_base::left)<<setw(20)<<Dat[j].StudentId;
												for(int m=0;m<StudentNumber;m++)
												{
													if (Stu[m].Id == Dat[j].StudentId)
													{
														Dat[j].GetGeneral();
														cout << setw(15) << Stu[m].Name << Dat[j].General << endl;
														break;
													}
												}
											}
										}
										break;
									}
								}
							}
							break;
						case 3:
							cout<<"请输入课程序号并以回车确认，输入0返回：";
							long long f;
							cin>>f;
							cin.clear();
							cin.sync();
							if(f==0) break;
							else
							{
								for(int k=0;k<CourseNumber;k++)
								{
									if(Cou[k].CourseId==f)
									{
										cout<<setiosflags(ios_base::left)<<setw(20)<<"学生学号"<<setw(15)<<"学生姓名"<<endl;
										for(int j=0;j<DataNumber;j++)
										{	
											if(Tea[i].Id==Dat[j].TeacherId&&f==Dat[j].SingleCourse.CourseId)
											{
												cout<<setiosflags(ios_base::left)<<setw(20)<<Dat[j].StudentId;
												for(int m=0;m<StudentNumber;m++)
												{
													if(Stu[m].Id==Dat[j].StudentId)
													{
														cout<<setw(15)<<Stu[m].Name<<endl;
														break;
													}
												}
											}
										}
										break;
									}
								}
							}
							break;
						case 4:
							cout<<"请输入课程序号并以回车确认，输入0返回：";
							long long g;
							cin>>g;
							cin.clear();
							cin.sync();
							if(g==0) break;
							else
							{
								for(int k=0;k<CourseNumber;k++)
								{
									if(Cou[k].CourseId==g)
									{
										cout<<setw(14)<<"期中考试(%)"<<setw(14)<<"期末考试(%)"<<setw(10)<<"作业(%)"<<setw(10)<<"实验(%)"<<"大作业(%)"<<endl;
										cout<<setw(10)<<Cou[k].MidtermPercent<<setw(10)<<Cou[k].FinalPercent<<setw(10)<<Cou[k].HomeworkPercent<<setw(10)<<Cou[k].ExperimentPercent<<Cou[k].ProjectPercent<<endl;
									}
								}
							}
							break;
						case 5:
							cout<<"请输入课程序号并以回车确认，输入0返回：";
							long long h;
							cin>>h;
							cin.clear();
							cin.sync();
							if(h==0) break;
							else
							{
								for(int k=0;k<CourseNumber;k++)
								{
									if(Cou[k].CourseId==h)
									{
										int a[5];
										cout<<"请输入新的期中考试成绩占比(%),请输入100以内的整数并以回车结束：";
										cin>>a[0];
										cout<<"请输入新的期末考试成绩占比(%),请输入100以内的整数并以回车结束：";
										cin>>a[1];
										cout<<"请输入新的作业成绩占比(%),请输入100以内的整数并以回车结束：";
										cin>>a[2];
										cout<<"请输入新的实验成绩占比(%),请输入100以内的整数并以回车结束：";
										cin>>a[3];
										cout<<"请输入新的大作业成绩占比(%),请输入100以内的整数并以回车结束：";
										cin>>a[4];
										cin.clear();
										cin.sync();
										if(a[0]+a[1]+a[2]+a[3]+a[4]==100)
										{
											Cou[k].MidtermPercent=a[0];
											Cou[k].FinalPercent=a[1];
											Cou[k].HomeworkPercent=a[2];
											Cou[k].ExperimentPercent=a[3];
											Cou[k].ProjectPercent=a[4];
										}
										else
										{
											cout<<"输入格式错误或总和不是100%！"<<endl;
										}	
										break;
									}
								}
							}
							break;
						case 6:
							cout<<"请输入课程序号并以回车确认，输入0返回：";
							long long o;
							cin>>o;
							cin.clear();
							cin.sync();
							if(o==0) break;
							else
							{
								for(int k=0;k<CourseNumber;k++)
								{
									if(Cou[k].CourseId==o)
									{
										cout<<"原先的成绩占比为："<<endl;
										cout<<"期中考试"<<Cou[k].MidtermPercent<<"%,期末考试"<<Cou[k].FinalPercent<<"%,作业"<<Cou[k].HomeworkPercent<<"%,实验"<<Cou[k].ExperimentPercent<<"%,大作业"<<Cou[k].ProjectPercent<<"%"<<endl;
										int a[5];
										cout<<"请输入新的期中考试成绩占比(%),请输入100以内的整数并以回车结束：";
										cin>>a[0];
										cout<<"请输入新的期末考试成绩占比(%),请输入100以内的整数并以回车结束：";
										cin>>a[1];
										cout<<"请输入新的作业成绩占比(%),请输入100以内的整数并以回车结束：";
										cin>>a[2];
										cout<<"请输入新的实验成绩占比(%),请输入100以内的整数并以回车结束：";
										cin>>a[3];
										cout<<"请输入新的大作业成绩占比(%),请输入100以内的整数并以回车结束：";
										cin>>a[4];
										cin.clear();
										cin.sync();
										if(a[0]+a[1]+a[2]+a[3]+a[4]==100)
										{
											Cou[k].MidtermPercent=a[0];
											Cou[k].FinalPercent=a[1];
											Cou[k].HomeworkPercent=a[2];
											Cou[k].ExperimentPercent=a[3];
											Cou[k].ProjectPercent=a[4];
										}
										else
										{
											cout<<"输入格式错误或总和不是100%！"<<endl;
										}	
										break;
									}
								}
							}
							break;
						case 7:
							cout<<"请输入课程序号并以回车确认，输入0返回：";
							long long t;
							cin>>t;
							cin.clear();
							cin.sync();
							CourseExist=0;
							if(t==0) break;
							else
							{
								for(int k=0;k<CourseNumber;k++)
								{
									if(Cou[k].CourseId==t)
									{
										CourseExist=1;
										if(Cou[k].MidtermPercent+Cou[k].FinalPercent+Cou[k].HomeworkPercent+Cou[k].ExperimentPercent+Cou[k].ProjectPercent==100)
										{
											while(1)
											{
												cout<<"请输入学生的学号：";
												long long e;
												bool Exist=0;
												cin>>e;
												for(int j=0;j<StudentNumber;j++)
												{
													if(Stu[j].Id==e)
													{
														for(int n=0;n<DataNumber;n++)
														{
															if(Dat[n].SingleCourse.CourseId==Cou[k].CourseId&&Dat[n].StudentId==e)
															{
																Exist=1;
																cout<<"该学生的成绩已经被录入！"<<endl;
																break;
															}
														}
														if(Exist==0)
														{
															DataNumber=DataNumber+1;
															Single *NewSetSingle=new Single[DataNumber];
															for(int n=0;n<(DataNumber-1);n++)
															{
																NewSetSingle[n]=Dat[n];
															}
															delete []Dat;
															Dat=new Single[DataNumber];
															for(int n=0;n<(DataNumber-1);n++)
															{
																Dat[n]=NewSetSingle[n];
															}
															delete []NewSetSingle;	
															int a1,a2,a3,a4,a5;
															cout<<"请按顺序输入该学生的期中成绩、期末成绩、作业成绩、实验成绩、大作业成绩。"<<endl;
															cout<<"请注意，所有成绩均为百分制成绩！相邻两个数字以空格分隔，最后以回车结束。"<<endl;
															cin>>a1;
															cin>>a2;
															cin>>a3;
															cin>>a4;
															cin>>a5;
															cin.clear();
															cin.sync();
															Dat[DataNumber-1]=Single(e,a,t,a1,a2,a3,a4,a5);
														}
													}
												}
												cout<<"是否继续输入？"<<endl;
												cout<<"1.继续录入该课程其他学生成绩 2.返回"<<endl;
												int flag;
												cin>>flag;
												cin.clear();
												cin.sync();
												if(flag==1);
												else if(flag==2) break;
											}
										}
										else
										{
											cout<<"请先录入课程成绩占比！"<<endl;
											break;
										}
										break;
									}
								}
								if(CourseExist==0)
								{
									cout<<"该课程不存在！"<<endl;
								}
							}
							break;
						case 8:
							cout<<"请输入课程序号并以回车确认，输入0返回：";
							long long u;
							cin>>u;
							cin.clear();
							cin.sync();
							CourseExist=0;
							StudentExist=0;
							if(u==0) break;
							else
							{
								for(int k=0;k<CourseNumber;k++)
								{
									if(Cou[k].CourseId==u)
									{
										CourseExist=1;
										if(Cou[k].MidtermPercent+Cou[k].FinalPercent+Cou[k].HomeworkPercent+Cou[k].ExperimentPercent+Cou[k].ProjectPercent==100)
										{
											while(1)
											{
												cout<<"请输入学生的学号：";
												long long v;
												cin>>v;
												for(int j=0;j<Cou[k].CourseStudentNumber;j++)
												{
													if(Cou[k].CourseStudentId[j]==v)
													{
														StudentExist=1;
														for(int n=0;n<DataNumber;n++)
														{
															if(Dat[n].SingleCourse.CourseId==Cou[k].CourseId&&Dat[n].StudentId==v)
															{
																cout<<"该同学原先的成绩为："<<endl;
																cout<<"期中考试"<<Dat[n].SingleGrade.Midterm<<"期末考试"<<Dat[n].SingleGrade.Final<<"作业"<<Dat[n].SingleGrade.Homework<<"实验"<<Dat[n].SingleGrade.Experiment<<"大作业"<<Dat[n].SingleGrade.Project<<endl;
																cout<<"若所有成绩均为0，则有可能该同学该门课程成绩未上传。"<<endl;
																cout<<"若无需修改成绩，请在下方输入相同数据。"<<endl;
																cout<<"请按顺序输入该学生新的期中成绩、期末成绩、作业成绩、实验成绩、大作业成绩。"<<endl;
																cout<<"请注意，所有成绩均为百分制成绩！相邻两个数字以空格分隔，最后以回车结束。"<<endl;
																cin>>Dat[n].SingleGrade.Midterm;
																cin>>Dat[n].SingleGrade.Final;
																cin>>Dat[n].SingleGrade.Homework;
																cin>>Dat[n].SingleGrade.Experiment;
																cin>>Dat[n].SingleGrade.Project;
																cin.clear();
																cin.sync();
															}
														}
													}
												}
												if(StudentExist==0)
												{
													cout<<"该同学此门课程还未录入成绩！"<<endl;
												}
												cout<<"是否继续输入？"<<endl;
												cout<<"1.继续修改该课程其他学生成绩 2.返回"<<endl;
												int flag;
												cin>>flag;
												cin.clear();
												cin.sync();
												if(flag==1);
												else if(flag==2) break;
											}
										}
										else
										{
											cout<<"请先录入课程成绩占比！"<<endl;
											break;
										}
										break;
									}
								}
								if(CourseExist==0)
								{
									cout<<"该课程不存在！"<<endl;
								}
							}
							break;
						case 9:
							return 0;
							break;
						default:
							cout<<"请输入1-9之间的数字进行操作！"<<endl;
						}
					}
					return 1;
				}
				else
				{
					cout<<"密码输入错误,请重新登录！！"<<endl;
					return 0;
				}
			}
		}
		if(flag==0)
		{
			cout<<"该用户不存在！请先注册！"<<endl;
		}
	}
	return 0;
}

bool DataBase::SchoolDenglu()
{
	cout<<"请输入密码："<<endl;
	string a,b;
	cin>>a;	
	ifstream op;
	op.open("School.txt",ios_base::in);
	op>>b;
	if(a==b)
	{
		cout<<"登录成功！欢迎您。"<<endl;
		while(1)
		{
			cout<<"请选择您要进行的操作，按回车确认！"<<endl;
			cout<<"1.查看课程列表     2.查看学生列表     3.查看教师列表"<<endl;
			cout<<"4.查看课程成绩列表 5.查看选课学生列表 6.查看课程成绩占比"<<endl;
			cout<<"7.添加课程         8.修改课程信息     9.退出系统"<<endl;
			int SchoolDoChoice;
			cin>>SchoolDoChoice;
			cin.clear();
			cin.sync();
			bool CourseExist=0;
			bool StudentExist=0;
			switch(SchoolDoChoice)
			{
			case 1:
				cout<<setiosflags(ios_base::left)<<setw(20)<<"课程名称"<<setw(15)<<"课程序号"<<"学分"<<endl;
				for(int k=0;k<CourseNumber;k++)
				{
					cout<<setiosflags(ios_base::left)<<setw(20)<<Cou[k].Name<<setw(15)<<Cou[k].CourseId<<Cou[k].Credit<<endl;
				}
				break;
			case 2:
				cout<<setiosflags(ios_base::left)<<setw(20)<<"学生姓名"<<setw(15)<<"学号"<<"总学分"<<endl;
				for(int k=0;k<StudentNumber;k++)
				{
					cout<<setiosflags(ios_base::left)<<setw(20)<<Stu[k].Name<<setw(15)<<Stu[k].Id<<Stu[k].StudentCredit<<endl;
				}
				break;
			case 3:
				cout<<setiosflags(ios_base::left)<<setw(20)<<"教师姓名"<<setw(15)<<"教职工号"<<endl;
				for(int k=0;k<TeacherNumber;k++)
				{
					cout<<setiosflags(ios_base::left)<<setw(20)<<Tea[k].Name<<setw(15)<<Tea[k].Id<<endl;
				}
				break;
			case 4:
				cout<<"请输入课程序号并以回车确认，输入0返回：";
				long long d;
				cin>>d;
				cin.clear();
				cin.sync();
				CourseExist=0;
				if(d==0) break;
				else
				{
					for(int k=0;k<CourseNumber;k++)
					{
						if(Cou[k].CourseId==d)
						{
							CourseExist=1;     //课程存在
							cout<<setiosflags(ios_base::left)<<setw(20)<<"学生学号"<<setw(15)<<"学生姓名"<<"总评成绩"<<endl;
							for(int j=0;j<DataNumber;j++)
							{
								if(d==Dat[j].SingleCourse.CourseId)
								{
									cout<<setiosflags(ios_base::left)<<setw(20)<<Dat[j].StudentId;
									for(int m=0;m<StudentNumber;m++)
									{
										if(Stu[m].Id==Dat[j].StudentId)
										{
											cout<<setw(15)<<Stu[m].Name<<Dat[j].General<<endl;
											break;
										}
									}
								}
							}
							break;
						}
					}
					if(CourseExist==0)     //课程不存在提示错误信息
					{
						cout<<"该课程不存在！"<<endl;
					}
				}
				break;
			case 5:
				cout<<"请输入课程序号并以回车确认，输入0返回：";
				long long d3;
				cin>>d3;
				cin.clear();
				cin.sync();
				CourseExist=0;
				if(d3==0) break;
				else
				{
					for(int k=0;k<CourseNumber;k++)
					{
						if(Cou[k].CourseId==d3)
						{
							CourseExist=1;     //课程存在
							cout<<setiosflags(ios_base::left)<<setw(20)<<"学生学号"<<"学生姓名"<<endl;
							for(int j=0;j<DataNumber;j++)
							{
								if(d==Dat[j].SingleCourse.CourseId)
								{
									cout<<setiosflags(ios_base::left)<<setw(20)<<Dat[j].StudentId;
									for(int m=0;m<StudentNumber;m++)
									{
										if(Stu[m].Id==Dat[j].StudentId)
										{
											cout<<Stu[m].Name<<endl;
											break;
										}
									}
								}
							}
							break;
						}
					}
					if(CourseExist==0)     //课程不存在提示错误信息
					{
						cout<<"该课程不存在！"<<endl;
					}
				}
				break;
			case 6:
				cout<<"请输入课程序号并以回车确认，输入0返回：";
				long long d4;
				cin>>d4;
				cin.clear();
				cin.sync();
				CourseExist=0;
				if(d4==0) break;
				else
				{
					for(int k=0;k<CourseNumber;k++)
					{
						if(Cou[k].CourseId==d4)
						{
							CourseExist=1;     //课程存在
							cout<<setiosflags(ios_base::left)<<setw(14)<<"期中考试(%)"<<setw(14)<<"期末考试(%)"<<setw(10)<<"作业(%)"<<setw(10)<<"实验(%)"<<"大作业(%)"<<endl;
							cout<<setiosflags(ios_base::left)<<setw(14)<<Cou[k].MidtermPercent<<setw(14)<<Cou[k].FinalPercent<<setw(10)<<Cou[k].HomeworkPercent<<setw(10)<<Cou[k].ExperimentPercent<<Cou[k].ProjectPercent<<endl;
						}
					}
					if(CourseExist==0)
					{
						cout<<"该课程不存在！"<<endl;     //课程不存在提示错误信息
					}
				}
				break;
			case 7:
				cout<<"请输入您要添加的新课程的课程序号并以回车结束，输入0返回："<<endl;
				long long c;
				cin>>c;
				cin.clear();
				cin.sync();
				int flag5;
				flag5=1;
				if(c==0) break;
				else
				{
					for(int i=0;i<CourseNumber;i++)
					{
						if(Cou[i].CourseId==c)
						{
							cout<<"该课程已经存在！"<<endl;
							flag5=0;
							break;
						}
					}
					if(flag5==1)
					{
						int Cre;
						long long TI;
						string Na;
						cout<<"请输入课程名称并以回车结束："<<endl;
						cin>>Na;
						cin.clear();
						cin.sync();
						cout<<"请输入课程学分并以回车结束："<<endl;
						cin>>Cre;
						cin.clear();
						cin.sync();
						cout<<"请输入代课老师的教职工号并以回车结束："<<endl;
						cin>>TI;
						cin.clear();
						cin.sync();
						Course *m=new Course[CourseNumber];
						for(int j=0;j<CourseNumber;j++)
						{
							m[j]=Cou[j];
						}
						delete []Cou;
						Cou=new Course[CourseNumber+1];
						for(int j=0;j<CourseNumber;j++)
						{
							Cou[j]=m[j];
						}
						delete []m;
						Cou[CourseNumber]=Course(Na,c,Cre,TI);
						for(int j=0;j<TeacherNumber;j++)
						{
							if(Tea[j].TeacherId==TI)
							{
								Tea[j].TeacherCourse[TeacherCourseNumber]=Cou[CourseNumber];
								Tea[j].TeacherCourseNumber++;
							}
						}
						CourseNumber++;
					}
				}
				break;
			case 8:
				cout<<"请输入您要修改的课程的课程序号并以回车结束，输入0返回："<<endl;
				long long c5;
				cin>>c5;
				cin.clear();
				cin.sync();
				CourseExist=0;
				if(c5==0) break;
				else
				{
					for(int i=0;i<CourseNumber;i++)
					{
						if(Cou[i].CourseId==c5)
						{
							CourseExist=1;     //
							cout<<"该课程原先的信息为："<<endl;
							cout<<setiosflags(ios_base::left)<<setw(20)<<"课程名"<<setw(15)<<"课程序号"<<setw(10)<<"学分"<<"教师序号"<<endl;
							cout<<setiosflags(ios_base::left)<<setw(20)<<Cou[i].Name<<setw(15)<<Cou[i].CourseId<<setw(10)<<Cou[i].Credit<<setw(10)<<Cou[i].TeacherId<<endl;
							cout<<setw(14)<<"期中考试(%)"<<setw(14)<<"期末考试(%)"<<setw(10)<<"作业(%)"<<setw(10)<<"实验(%)"<<"大作业(%)"<<endl;
							cout<<setw(14)<<Cou[i].MidtermPercent<<setw(14)<<Cou[i].FinalPercent<<setw(10)<<Cou[i].HomeworkPercent<<setw(10)<<Cou[i].ExperimentPercent<<Cou[i].ProjectPercent<<endl;
							cout<<"请注意，教务无权修改该课程的各项成绩占比。"<<endl;
							cout<<"若无需修改以上信息，请在下方输入相同数据。"<<endl;
							cout<<"请按顺序输入该课程新的课程名、课程序号、学分、教师序号。"<<endl;
							int Cre2;
							long long CI2,TI2;
							string Na2;
							cout<<"请输入课程名称并以回车结束：";
							cin>>Na2;
							cin.clear();
							cin.sync();
							cout<<"请输入课程序号并以回车结束：";
							cin>>CI2;
							cin.clear();
							cin.sync();
							cout<<"请输入课程学分并以回车结束：";
							cin>>Cre2;
							cin.clear();
							cin.sync();
							cout<<"请输入代课老师的教职工号并以回车结束：";
							cin>>TI2;
							cin.clear();
							cin.sync();
							for(int j=0;j<TeacherNumber;j++)     //删除原先的信息
							{
								if(Tea[j].TeacherId==Cou[i].TeacherId)
								{
									for(int k=0;k<Tea[j].TeacherCourseNumber;k++)
									{
										if(Tea[j].TeacherCourse[k].CourseId==Cou[i].CourseId)
										{
											for(int m=k;m<(Tea[j].TeacherCourseNumber-1);m++)
											{
												Tea[j].TeacherCourse[m]=Tea[j].TeacherCourse[m+1];
											}
											break;
										}
									}
									Tea[j].TeacherCourseNumber--;
								}
							}
							Cou[i].SchoolSet(Na2,CI2,Cre2,TI2);
							for(int j=0;j<TeacherNumber;j++)     //新建信息
							{
								if(Tea[j].TeacherId==TI2)
								{
									Course *q=new Course[Tea[j].TeacherCourseNumber];
									for(int k=0;k<Tea[j].TeacherCourseNumber;k++)
									{
										q[k]=Tea[j].TeacherCourse[k];
									}
									delete []Stu[j].StudentCourseId;
									Tea[j].TeacherCourse=new Course[Tea[j].TeacherCourseNumber+1];
									for(int k=0;k<Tea[j].TeacherCourseNumber;k++)
									{
										Tea[j].TeacherCourse[i]=q[i];
									}
									delete []q;
									Tea[j].TeacherCourse[TeacherCourseNumber]=Cou[i];
									Tea[j].TeacherCourseNumber++;
								}
							}
							break;
						}
					}
					if(CourseExist==0)
					{						
						cout<<"该课程不存在！"<<endl;
					}
				}
				break;
			case 9:
				return 0;
				break;
			default:
				cout<<"请输入1-9间的数字进行操作！"<<endl;
			}
		}
	}
	else
	{
		cout<<"密码错误！请重新登录！"<<endl;
		return 0;
	}
	return 1;
}