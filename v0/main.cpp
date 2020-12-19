#include<iostream>
#include<string>
#include<math.h>
#include<iomanip>
#include<fstream>
#pragma warning(disable:4996)
using namespace std;


class DataBase;            //��ͺ�������ǰ����
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
		Course(){CourseStudentNumber=0;}     //Ĭ�Ϲ��캯��ʹѡ��ѧ������Ϊ0
		~Course();
		Course(string x,long long y,int z,long long m,int a=0,int b=0,int c=0,int d=0,int e=0);
		void SchoolSet(string x,long long y,int z,long long m);
		friend class DataBase;
		friend class Single;
	protected:
		int MidtermPercent,FinalPercent,HomeworkPercent,ExperimentPercent,ProjectPercent;     //�γ̳ɼ�ռ���ǿγ̵�����
		long long CourseId;
		string Name;
		long long TeacherId;       //��ʦ�ı����Ϊ�γ���ĳ�Ա�����ڲ��ҺͶ�λ
		int Credit;
		long long *CourseStudentId;       //ѡ�ε�ѧ��ѧ���Զ�̬������ʽ��Ϊ�γ���ĳ�Ա�����ڲ��ҺͶ�λ
		int CourseStudentNumber;       //ѡ��ѧ��������
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

void Course::SchoolSet(string x,long long y,int z,long long m)      //����ѧУ�������ÿγ���Ϣ
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
	else delete[]CourseStudentId;     //ѧ��������Ϊ0��ɾ������ѡ��ѧ��ѧ�ŵĶ�̬����
}




class Teacher:virtual public Course
{
	public:
		Teacher(){TeacherCourseNumber=0;}     //Ĭ�Ϲ��캯��ʹ��ʦ�����ڿγ�����Ϊ0
		~Teacher();
		Teacher(string a,long long b,string c);
		friend class DataBase;
	protected:
		string Name;
		long long Id;
		string Password;
		Course *TeacherCourse;         //��ʦ�����ڿγ��ö�̬�����ʾ
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
	else delete[]TeacherCourse;     //��ʦ���ڿγ�������Ϊ0��ɾ�����ڴ�����ڿγ̵Ķ�̬����
}




class Student:virtual public Grade
{
	public:
		Student(string a,long long b,string c);
		Student(){StudentCourseNumber=0;}     //Ĭ�Ϲ��캯��ʹѧ��ѡ������Ϊ0
		~Student();
		friend class DataBase;
	protected:
		string Name;
		long long Id;
		string Password;
		double GPA;
		int StudentCredit;
		long long *StudentCourseId;     //ѧ����ѡ�γ̵Ŀγ�����Զ�̬������ʽ��ʾ
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
	else delete[]StudentCourseId;     //ѡ��������Ϊ0��ɾ�����ڴ�����ѡ�γ̿γ���ŵĶ�̬����
}




class Single:virtual public Course,virtual public Student
{
	public:
		Single(){}
		Single(long long a,long long b,long long c,int d,int e,int f,int g,int h);
		void SingleFindCourse();
		void GetGeneral();         //���ø����ֳɼ�����ռ�������������ɼ�
		void CalcuPoint();         //���㼨��Ͷ�Ӧ�ĵȼ�
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
	op.open("Course.txt",ios_base::in);     //���ڿγ��໹δ����������ɨ�ļ�
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

void Single::GetGeneral()     //��Ȩ���������ɼ�
{
	General=(SingleGrade.Midterm*SingleCourse.MidtermPercent+SingleGrade.Final*SingleCourse.FinalPercent+SingleGrade.Homework*SingleCourse.HomeworkPercent+SingleGrade.Experiment*SingleCourse.ExperimentPercent+SingleGrade.Project*SingleCourse.ProjectPercent)/100;
}

void Single::CalcuPoint()         //ֱ��Ӧ���廪���еĵȼ��ƽ��м���͵ȼ��Ļ���
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


class DataBase:virtual public Single,virtual public Teacher     //������Ϣ��������DataBase���Ա��
{
	public:
		DataBase()     //Ĭ�Ϲ��캯����������Ϣ������Ϊ0
		{
			StudentNumber=0;
			CourseNumber=0;
			TeacherNumber=0;
			DataNumber=0;
		}
		~DataBase();
		bool AddStudent();         //����ѧ��ע��
		bool AddTeacher();         //���ڽ�ʦע��
		void SchoolZhuce();        //����ѧУע�ᣬ�����ڱ�ϵͳ��ϵͳֻ����ע��һ�Σ���û�з���ֵ
		bool StudentDenglu();      //����ѧ���ĵ�¼����������
		bool TeacherDenglu();      //���ڽ�ʦ�ĵ�¼����������
		bool SchoolDenglu();       //����ѧУ�ĵ�¼����������
		void SetSystem();
		bool Begin();
		void CloseSystem();
		void SetStudent();         //������ϵͳ��ʼ����ʱ���������ļ��ڵ�ѧ����Ϣ���뵽����
		void SetTeacher();         //������ϵͳ��ʼ����ʱ���������ļ��ڵĽ�ʦ��Ϣ���뵽����
		void SetCourse();          //������ϵͳ��ʼ����ʱ���������ļ��ڵĿγ���Ϣ���뵽����
		void SetSingle();          //������ϵͳ��ʼ����ʱ���������ļ��ڵĳɼ���Ϣ���뵽����
		void ResetStudent();       //������ϵͳ��������ʱ�����������ڵ�ѧ����Ϣ���뵽�ļ���
		void ResetTeacher();       //������ϵͳ��������ʱ�����������ڵĽ�ʦ��Ϣ���뵽�ļ���
		void ResetCourse();        //������ϵͳ��������ʱ�����������ڵĿγ���Ϣ���뵽�ļ���
		void ResetSingle();        //������ϵͳ��������ʱ�����������ڵĳɼ���Ϣ���뵽�ļ���
	private:
		Single *Dat;        //�ɼ���Ϣ�Գ�Ա�����ʾ
		int DataNumber;        //�ɼ�����
		Student *Stu;        //ѧ����Ϣ�Գ�Ա�����ʾ
		int StudentNumber;        //ѧ������
		Course *Cou;        //�γ���Ϣ�Գ�Ա�����ʾ
		int CourseNumber;        //�γ�����
		Teacher *Tea;        //��ʦ��Ϣ�Գ�Ա�����ʾ
		int TeacherNumber;        //��ʦ����
		string SchoolPassword;        //ѧУ�ĵ�¼����Ψһ���ڣ�ֱ�Ӵ���ΪDataBase��ĳ�Ա
};

DataBase::~DataBase()
{
	if(StudentNumber==0);
	else delete[]Stu;     //ѧ��������Ϊ0��ɾ������ѧ����Ϣ�Ķ�̬����
	if(CourseNumber==0);
	else delete[]Cou;     //�γ�������Ϊ0��ɾ������γ���Ϣ�Ķ�̬����
	if(TeacherNumber==0);
	else delete[]Tea;     //��ʦ������Ϊ0��ɾ�������ʦ��Ϣ�Ķ�̬����
	if(DataNumber==0);
	else delete[]Dat;     //�ɼ�������Ϊ0��ɾ������ɼ���Ϣ�Ķ�̬����
}




int main()
{
	DataBase Tsinghua;
	Tsinghua.SetSystem();        //���������ļ�������ݶ�ȡ����
	cout<<"��ӭ��¼�ɼ�����ϵͳ��"<<endl;
	while(Tsinghua.Begin());        //��������
	Tsinghua.CloseSystem();        //��������ɺ����������д���ļ�
}



void DataBase::SetSystem()
{
	ifstream op;
	op.open("Single.txt",ios_base::in);      //�½��ɼ���Ϣ
	if(op==0)     //�ļ�������
	{
		op.close();     //�ر��ļ�
		DataNumber=0;     //�ɼ�������Ϊ0
	}
	else
	{
		op.close();     //�ر��ļ�
		SetSingle();     //���ļ�
	}
	

	op.open("Student.txt",ios_base::in);      //�½�ѧ����Ϣ
	if(op==0)     //�ļ�������
	{
		op.close();     //�ر��ļ�
		StudentNumber=0;     //ѧ��������Ϊ0
	}
	else
	{
		op.close();     //�ر��ļ�
		SetStudent();     //���ļ�
	}

	op.open("Course.txt",ios_base::in);      //�½��γ���Ϣ
	if(op==0)     //�ļ�������
	{
		op.close();     //�ر��ļ�
		CourseNumber=0;     //�γ�������Ϊ0
	}
	else
	{
		op.close();     //�ر��ļ�
		SetCourse();     //���ļ�
	}

	op.open("Teacher.txt",ios_base::in);      //�½���ʦ��Ϣ
	if(op==0)     //�ļ�������
	{
		op.close();     //�ر��ļ�
		TeacherNumber=0;     //��ʦ������Ϊ0
	}
	else
	{
		op.close();     //�ر��ļ�
		SetTeacher();     //���ļ�
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
		StudentNumber++;     //��ѧ������
	}
	op.clear();
	op.sync();
	op.seekg(ios_base::beg);
	Stu=new Student[StudentNumber];
	for(int j=0;j<StudentNumber;j++)     //����ѧ����Ϣ
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
		for(int i=0;i<DataNumber;i++)     //���гɼ���Ϣ
		{
			if(m==Dat[i].StudentId)
			{
				Stu[j].StudentCourseNumber++;     //��ѧ��ѡ������
			}
		}
		Stu[j].StudentCourseId=new long long[Stu[j].StudentCourseNumber];     //�½�ѧ��ѡ����Ϣ
		static int i = 0;     //��̬������
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
		CourseNumber++;     //�ƿγ�����
	}
	op.clear();
	op.sync();	
	op.seekg(ios_base::beg);
	Cou=new Course[CourseNumber];     //�½��γ���Ϣ
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
				Cou[j].CourseStudentNumber++;     //��ѡ��ѧ������
			}
		}
		Cou[j].CourseStudentId=new long long[Cou[j].CourseStudentNumber];     //�½�ѡ��ѧ����Ϣ
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
		TeacherNumber++;     //�ƽ�ʦ����
	}
	op.clear();
	op.sync();	
	op.seekg(ios_base::beg);
	Tea=new Teacher[TeacherNumber];     //�½���ʦ��Ϣ
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
				Tea[j].TeacherCourseNumber++;     //�ƽ�ʦ��������
			}
		}
		Tea[j].TeacherCourse=new Course[Tea[j].TeacherCourseNumber];     //�½���ʦ������Ϣ
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
		DataNumber++;     //�Ƴɼ�����
	}
	op.clear();
	op.sync();	
	op.seekg(ios_base::beg);
	Dat=new Single[DataNumber];     //�½��ɼ���Ϣ
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
	ResetStudent();     //��ѧ����Ϣ����д���ļ�
	ResetTeacher();     //����ʦ��Ϣ����д���ļ�
	ResetCourse();     //���γ���Ϣ����д���ļ�
	ResetSingle();     //���ɼ���Ϣ����д���ļ�
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
	cout<<"��ѡ����Ҫ���еĲ�����"<<endl;
	cout<<"1.ѧ��ע�� 2.��ʦע�� 3.����ע��"<<endl;
	cout<<"4.ѧ����¼ 5.��ʦ��¼ 6.�����¼"<<endl;
	cout<<"7.�˳�ϵͳ"<<endl;
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
		while(flag1==1)     //����ע��
		{
			flag1=AddStudent();
		}
		break;
	case 2:
		flag2=AddTeacher();     //����ע��
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
		cout<<"������1-7���в�����"<<endl;
		break;
	}
	return 1;
}


bool DataBase::AddStudent()
{
	cout<<"��ӭ����ѧ��ע�ᣡ"<<endl;
	cout<<"����������ѧ�Ų����س�����������0���أ�";
	long long b;
	cin>>b;
	cin.clear();
	cin.sync();
	if(b==0) return 0;     //����0����
	for(int i=0;i<StudentNumber;i++)
	{
		if(Stu[i].Id==b)
		{
			cout<<"��ѧ���ѱ�ע�ᣡ����1����ע�ᣬ����0���������棺"<<endl;
			bool flag;
			cin>>flag;
			if(flag==0) return 0;     //����0����
			else if(flag==1) return 1;
			else
			{
				cout<<"�����������ڽ����������棡"<<endl;
				return 0;
			}
			break;
		}
	}
	cout<<"�������������������س�������";
	string c,d;
	cin>>c;
	cin.clear();
	cin.sync();
	d=SetPassword();
	StudentNumber++;
	Student *m=new Student[StudentNumber];     //���Ӷ�̬����ĳ���
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
	double AddGrades=0;     //���³ɼ���Ϣ
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
	cout<<"��ϲ��ע��ɹ���"<<endl;
	return 0;
}

bool DataBase::AddTeacher()
{
	cout<<"��ӭ������ʦע�ᣡ"<<endl;
	cout<<"���������Ľ�ְ���Ų����س�����������0���أ�";
	long long b;
	cin>>b;
	cin.clear();
	cin.sync();
	if(b==0) return 0;     //����0����
	for(int i=0;i<TeacherNumber;i++)
	{
		if(Tea[i].Id==b)
		{
			cout<<"��ѧ���ѱ�ע�ᣡ��1����ע�ᣬ��0���������棺"<<endl;
			bool flag;
			cin>>flag;
			if(flag==0) return 0;     //����0����
			else if(flag==1) return 1;     //����1���ز�����ע��
			else
			{
				cout<<"�����������ڽ����������棡"<<endl;
				return 0;
			}
			break;
		}
	}
	cout<<"�������������������س�������";
	string c,d;
	cin>>c;
	cin.clear();
	cin.sync();
	d=SetPassword();
	TeacherNumber++;
	Teacher *m=new Teacher[TeacherNumber];     //������ʦ����
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
	cout<<"��ϲ��ע��ɹ���"<<endl;
	return 0;
}

void DataBase::SchoolZhuce()
{
	ifstream op1;
	op1.open("School.txt",ios_base::in);
	if(op1==0)     //�ļ������ڣ�˵��ѧУû��ע��
	{
		SchoolPassword=SetPassword();
		ofstream op2;
		op2.open("School.txt",ios_base::out);
		op2<<SchoolPassword;
		op2.close();
		cout<<"��ϲ����ע��ɹ���"<<endl;
	}
	else     //�ļ����ڣ�˵��ѧУ��ע��
	{
		cout<<"ѧУ�˺��Ѿ����ڣ�"<<endl;
	}
}

string SetPassword()
{
	cout<<"�������������룬���س�������";
	string c;
	cin>>c;
	cin.clear();
	cin.sync();
	cout<<"���ٴ������������룬���س�������";
	string d;
	cin>>d;
	cin.clear();
	cin.sync();
	if(c==d) return c;     //������������һ���򷵻�
	else
	{
		cout<<"������������벻һ�£����������룡"<<endl;
		string m=SetPassword();     //�����������벻һ������������
		return m;
	}
}



bool DataBase::StudentDenglu()
{
	cout<<"����������ѧ�Ų����س�����������0���أ�";
	long long a;
	bool flag=0;
	cin>>a;
	cin.clear();
	cin.sync();
	if(a==0) return 0;     //����0����
	else
	{
		for(int i=0;i<StudentNumber;i++)
		{
			if(a==Stu[i].Id)
			{
				flag=1;
				cout<<"���������룺"<<endl;
				string c;
				cin>>c;			
				if(c==Stu[i].Password)
				{
					cout<<"��¼�ɹ�����ӭ����"<<Stu[i].Name<<"ͬѧ��"<<endl;
					while(1)
					{
						cout<<"��ѡ����Ҫ���еĲ��������س�ȷ�ϣ�"<<endl;
						cout<<"1.�鿴�γ��б� 2.�鿴�ɼ��б� 3.�鿴GPA����ѧ�� 4.�˳�ϵͳ"<<endl;
						int StudentDoChoice;
						cin>>StudentDoChoice;
						cin.clear();
						cin.sync();
						switch(StudentDoChoice)
						{
						case 1:
							cout<<setiosflags(ios_base::left)<<setw(20)<<"�γ�����"<<setw(15)<<"�γ����"<<"ѧ��"<<endl;
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
							cout<<setiosflags(ios_base::left)<<setw(10)<<"�γ����"<<setw(9)<<"�����ɼ�"<<setw(5)<<"����"<<setw(5)<<"�ȼ�"
								<<setw(9)<<"���гɼ�"<<setw(10)<<"��ĩ�ɼ�"<<setw(10)<<"��ҵ�ɼ�"<<setw(10)<<"ʵ��ɼ�"<<"����ҵ�ɼ�"<<endl;
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
							cout<<"������ѧ����"<<Stu[i].StudentCredit<<"����GPAΪ"<<Stu[i].GPA<<endl;
							break;
						case 4:
							return 0;
							break;
						default:
							cout<<"������1-4֮������ֽ��в�����"<<endl;
						}
					}
					return 1;
				}
				else
				{
					cout<<"������������µ�¼��"<<endl;
					return 0;
				}
			}
		}
		if(flag==0)
		{
			cout<<"���û������ڣ�����ע�ᣡ"<<endl;
		}
	}
	return 0;
}

bool DataBase::TeacherDenglu()
{
	cout<<"���������Ľ�ְ���Ų����س�����������0���أ�";
	long long a;
	bool flag=0;
	bool CourseExist=0;
	bool StudentExist=0;
	cin>>a;
	cin.clear();
	cin.sync();
	if(a==0) return 0;     //����0����
	else
	{
		for(int i=0;i<TeacherNumber;i++)
		{
			if(a==Tea[i].Id)
			{			
				flag=1;
				cout<<"���������룺"<<endl;
				string c;
				cin>>c;			
				if(c==Tea[i].Password)
				{
					cout<<"��¼�ɹ�����ӭ����"<<Tea[i].Name<<"��ʦ��"<<endl;
					while(1)
					{
						cout<<"��ѡ����Ҫ���еĲ��������س�ȷ�ϣ�"<<endl;
						cout<<"1.�鿴�γ��б� 2.�鿴�γ̳ɼ��б� 3.�鿴ѡ��ѧ���б�"<<endl;
						cout<<"4.�鿴�ɼ�ռ�� 5.���óɼ�ռ��     6.�޸ĳɼ�ռ��"<<endl;
						cout<<"7.¼��ɼ�     8.�޸ĳɼ�         9.�˳�ϵͳ"<<endl;
						int TeacherDoChoice;
						cin>>TeacherDoChoice;
						cin.clear();
						cin.sync();
						switch(TeacherDoChoice)
						{
						case 1:
							cout<<setiosflags(ios_base::left)<<setw(20)<<"�γ�����"<<setw(15)<<"�γ����"<<"ѧ��"<<endl;
							for(int k=0;k<CourseNumber;k++)
							{
								if(Tea[i].Id==Cou[k].TeacherId)
								{
									cout<<setiosflags(ios_base::left)<<setw(20)<<Cou[k].Name<<setw(15)<<Cou[k].CourseId<<Cou[k].Credit<<endl;
								}
							}
							break;
						case 2:
							cout<<"������γ���Ų��Իس�ȷ�ϣ�����0���أ�";
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
										cout<<setiosflags(ios_base::left)<<setw(20)<<"ѧ��ѧ��"<<setw(15)<<"ѧ������"<<"�����ɼ�"<<endl;
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
							cout<<"������γ���Ų��Իس�ȷ�ϣ�����0���أ�";
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
										cout<<setiosflags(ios_base::left)<<setw(20)<<"ѧ��ѧ��"<<setw(15)<<"ѧ������"<<endl;
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
							cout<<"������γ���Ų��Իس�ȷ�ϣ�����0���أ�";
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
										cout<<setw(14)<<"���п���(%)"<<setw(14)<<"��ĩ����(%)"<<setw(10)<<"��ҵ(%)"<<setw(10)<<"ʵ��(%)"<<"����ҵ(%)"<<endl;
										cout<<setw(10)<<Cou[k].MidtermPercent<<setw(10)<<Cou[k].FinalPercent<<setw(10)<<Cou[k].HomeworkPercent<<setw(10)<<Cou[k].ExperimentPercent<<Cou[k].ProjectPercent<<endl;
									}
								}
							}
							break;
						case 5:
							cout<<"������γ���Ų��Իس�ȷ�ϣ�����0���أ�";
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
										cout<<"�������µ����п��Գɼ�ռ��(%),������100���ڵ��������Իس�������";
										cin>>a[0];
										cout<<"�������µ���ĩ���Գɼ�ռ��(%),������100���ڵ��������Իس�������";
										cin>>a[1];
										cout<<"�������µ���ҵ�ɼ�ռ��(%),������100���ڵ��������Իس�������";
										cin>>a[2];
										cout<<"�������µ�ʵ��ɼ�ռ��(%),������100���ڵ��������Իس�������";
										cin>>a[3];
										cout<<"�������µĴ���ҵ�ɼ�ռ��(%),������100���ڵ��������Իس�������";
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
											cout<<"�����ʽ������ܺͲ���100%��"<<endl;
										}	
										break;
									}
								}
							}
							break;
						case 6:
							cout<<"������γ���Ų��Իس�ȷ�ϣ�����0���أ�";
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
										cout<<"ԭ�ȵĳɼ�ռ��Ϊ��"<<endl;
										cout<<"���п���"<<Cou[k].MidtermPercent<<"%,��ĩ����"<<Cou[k].FinalPercent<<"%,��ҵ"<<Cou[k].HomeworkPercent<<"%,ʵ��"<<Cou[k].ExperimentPercent<<"%,����ҵ"<<Cou[k].ProjectPercent<<"%"<<endl;
										int a[5];
										cout<<"�������µ����п��Գɼ�ռ��(%),������100���ڵ��������Իس�������";
										cin>>a[0];
										cout<<"�������µ���ĩ���Գɼ�ռ��(%),������100���ڵ��������Իس�������";
										cin>>a[1];
										cout<<"�������µ���ҵ�ɼ�ռ��(%),������100���ڵ��������Իس�������";
										cin>>a[2];
										cout<<"�������µ�ʵ��ɼ�ռ��(%),������100���ڵ��������Իس�������";
										cin>>a[3];
										cout<<"�������µĴ���ҵ�ɼ�ռ��(%),������100���ڵ��������Իس�������";
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
											cout<<"�����ʽ������ܺͲ���100%��"<<endl;
										}	
										break;
									}
								}
							}
							break;
						case 7:
							cout<<"������γ���Ų��Իس�ȷ�ϣ�����0���أ�";
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
												cout<<"������ѧ����ѧ�ţ�";
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
																cout<<"��ѧ���ĳɼ��Ѿ���¼�룡"<<endl;
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
															cout<<"�밴˳�������ѧ�������гɼ�����ĩ�ɼ�����ҵ�ɼ���ʵ��ɼ�������ҵ�ɼ���"<<endl;
															cout<<"��ע�⣬���гɼ���Ϊ�ٷ��Ƴɼ����������������Կո�ָ�������Իس�������"<<endl;
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
												cout<<"�Ƿ�������룿"<<endl;
												cout<<"1.����¼��ÿγ�����ѧ���ɼ� 2.����"<<endl;
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
											cout<<"����¼��γ̳ɼ�ռ�ȣ�"<<endl;
											break;
										}
										break;
									}
								}
								if(CourseExist==0)
								{
									cout<<"�ÿγ̲����ڣ�"<<endl;
								}
							}
							break;
						case 8:
							cout<<"������γ���Ų��Իس�ȷ�ϣ�����0���أ�";
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
												cout<<"������ѧ����ѧ�ţ�";
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
																cout<<"��ͬѧԭ�ȵĳɼ�Ϊ��"<<endl;
																cout<<"���п���"<<Dat[n].SingleGrade.Midterm<<"��ĩ����"<<Dat[n].SingleGrade.Final<<"��ҵ"<<Dat[n].SingleGrade.Homework<<"ʵ��"<<Dat[n].SingleGrade.Experiment<<"����ҵ"<<Dat[n].SingleGrade.Project<<endl;
																cout<<"�����гɼ���Ϊ0�����п��ܸ�ͬѧ���ſγ̳ɼ�δ�ϴ���"<<endl;
																cout<<"�������޸ĳɼ��������·�������ͬ���ݡ�"<<endl;
																cout<<"�밴˳�������ѧ���µ����гɼ�����ĩ�ɼ�����ҵ�ɼ���ʵ��ɼ�������ҵ�ɼ���"<<endl;
																cout<<"��ע�⣬���гɼ���Ϊ�ٷ��Ƴɼ����������������Կո�ָ�������Իس�������"<<endl;
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
													cout<<"��ͬѧ���ſγ̻�δ¼��ɼ���"<<endl;
												}
												cout<<"�Ƿ�������룿"<<endl;
												cout<<"1.�����޸ĸÿγ�����ѧ���ɼ� 2.����"<<endl;
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
											cout<<"����¼��γ̳ɼ�ռ�ȣ�"<<endl;
											break;
										}
										break;
									}
								}
								if(CourseExist==0)
								{
									cout<<"�ÿγ̲����ڣ�"<<endl;
								}
							}
							break;
						case 9:
							return 0;
							break;
						default:
							cout<<"������1-9֮������ֽ��в�����"<<endl;
						}
					}
					return 1;
				}
				else
				{
					cout<<"�����������,�����µ�¼����"<<endl;
					return 0;
				}
			}
		}
		if(flag==0)
		{
			cout<<"���û������ڣ�����ע�ᣡ"<<endl;
		}
	}
	return 0;
}

bool DataBase::SchoolDenglu()
{
	cout<<"���������룺"<<endl;
	string a,b;
	cin>>a;	
	ifstream op;
	op.open("School.txt",ios_base::in);
	op>>b;
	if(a==b)
	{
		cout<<"��¼�ɹ�����ӭ����"<<endl;
		while(1)
		{
			cout<<"��ѡ����Ҫ���еĲ��������س�ȷ�ϣ�"<<endl;
			cout<<"1.�鿴�γ��б�     2.�鿴ѧ���б�     3.�鿴��ʦ�б�"<<endl;
			cout<<"4.�鿴�γ̳ɼ��б� 5.�鿴ѡ��ѧ���б� 6.�鿴�γ̳ɼ�ռ��"<<endl;
			cout<<"7.��ӿγ�         8.�޸Ŀγ���Ϣ     9.�˳�ϵͳ"<<endl;
			int SchoolDoChoice;
			cin>>SchoolDoChoice;
			cin.clear();
			cin.sync();
			bool CourseExist=0;
			bool StudentExist=0;
			switch(SchoolDoChoice)
			{
			case 1:
				cout<<setiosflags(ios_base::left)<<setw(20)<<"�γ�����"<<setw(15)<<"�γ����"<<"ѧ��"<<endl;
				for(int k=0;k<CourseNumber;k++)
				{
					cout<<setiosflags(ios_base::left)<<setw(20)<<Cou[k].Name<<setw(15)<<Cou[k].CourseId<<Cou[k].Credit<<endl;
				}
				break;
			case 2:
				cout<<setiosflags(ios_base::left)<<setw(20)<<"ѧ������"<<setw(15)<<"ѧ��"<<"��ѧ��"<<endl;
				for(int k=0;k<StudentNumber;k++)
				{
					cout<<setiosflags(ios_base::left)<<setw(20)<<Stu[k].Name<<setw(15)<<Stu[k].Id<<Stu[k].StudentCredit<<endl;
				}
				break;
			case 3:
				cout<<setiosflags(ios_base::left)<<setw(20)<<"��ʦ����"<<setw(15)<<"��ְ����"<<endl;
				for(int k=0;k<TeacherNumber;k++)
				{
					cout<<setiosflags(ios_base::left)<<setw(20)<<Tea[k].Name<<setw(15)<<Tea[k].Id<<endl;
				}
				break;
			case 4:
				cout<<"������γ���Ų��Իس�ȷ�ϣ�����0���أ�";
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
							CourseExist=1;     //�γ̴���
							cout<<setiosflags(ios_base::left)<<setw(20)<<"ѧ��ѧ��"<<setw(15)<<"ѧ������"<<"�����ɼ�"<<endl;
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
					if(CourseExist==0)     //�γ̲�������ʾ������Ϣ
					{
						cout<<"�ÿγ̲����ڣ�"<<endl;
					}
				}
				break;
			case 5:
				cout<<"������γ���Ų��Իس�ȷ�ϣ�����0���أ�";
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
							CourseExist=1;     //�γ̴���
							cout<<setiosflags(ios_base::left)<<setw(20)<<"ѧ��ѧ��"<<"ѧ������"<<endl;
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
					if(CourseExist==0)     //�γ̲�������ʾ������Ϣ
					{
						cout<<"�ÿγ̲����ڣ�"<<endl;
					}
				}
				break;
			case 6:
				cout<<"������γ���Ų��Իس�ȷ�ϣ�����0���أ�";
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
							CourseExist=1;     //�γ̴���
							cout<<setiosflags(ios_base::left)<<setw(14)<<"���п���(%)"<<setw(14)<<"��ĩ����(%)"<<setw(10)<<"��ҵ(%)"<<setw(10)<<"ʵ��(%)"<<"����ҵ(%)"<<endl;
							cout<<setiosflags(ios_base::left)<<setw(14)<<Cou[k].MidtermPercent<<setw(14)<<Cou[k].FinalPercent<<setw(10)<<Cou[k].HomeworkPercent<<setw(10)<<Cou[k].ExperimentPercent<<Cou[k].ProjectPercent<<endl;
						}
					}
					if(CourseExist==0)
					{
						cout<<"�ÿγ̲����ڣ�"<<endl;     //�γ̲�������ʾ������Ϣ
					}
				}
				break;
			case 7:
				cout<<"��������Ҫ��ӵ��¿γ̵Ŀγ���Ų��Իس�����������0���أ�"<<endl;
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
							cout<<"�ÿγ��Ѿ����ڣ�"<<endl;
							flag5=0;
							break;
						}
					}
					if(flag5==1)
					{
						int Cre;
						long long TI;
						string Na;
						cout<<"������γ����Ʋ��Իس�������"<<endl;
						cin>>Na;
						cin.clear();
						cin.sync();
						cout<<"������γ�ѧ�ֲ��Իس�������"<<endl;
						cin>>Cre;
						cin.clear();
						cin.sync();
						cout<<"�����������ʦ�Ľ�ְ���Ų��Իس�������"<<endl;
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
				cout<<"��������Ҫ�޸ĵĿγ̵Ŀγ���Ų��Իس�����������0���أ�"<<endl;
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
							cout<<"�ÿγ�ԭ�ȵ���ϢΪ��"<<endl;
							cout<<setiosflags(ios_base::left)<<setw(20)<<"�γ���"<<setw(15)<<"�γ����"<<setw(10)<<"ѧ��"<<"��ʦ���"<<endl;
							cout<<setiosflags(ios_base::left)<<setw(20)<<Cou[i].Name<<setw(15)<<Cou[i].CourseId<<setw(10)<<Cou[i].Credit<<setw(10)<<Cou[i].TeacherId<<endl;
							cout<<setw(14)<<"���п���(%)"<<setw(14)<<"��ĩ����(%)"<<setw(10)<<"��ҵ(%)"<<setw(10)<<"ʵ��(%)"<<"����ҵ(%)"<<endl;
							cout<<setw(14)<<Cou[i].MidtermPercent<<setw(14)<<Cou[i].FinalPercent<<setw(10)<<Cou[i].HomeworkPercent<<setw(10)<<Cou[i].ExperimentPercent<<Cou[i].ProjectPercent<<endl;
							cout<<"��ע�⣬������Ȩ�޸ĸÿγ̵ĸ���ɼ�ռ�ȡ�"<<endl;
							cout<<"�������޸�������Ϣ�������·�������ͬ���ݡ�"<<endl;
							cout<<"�밴˳������ÿγ��µĿγ������γ���š�ѧ�֡���ʦ��š�"<<endl;
							int Cre2;
							long long CI2,TI2;
							string Na2;
							cout<<"������γ����Ʋ��Իس�������";
							cin>>Na2;
							cin.clear();
							cin.sync();
							cout<<"������γ���Ų��Իس�������";
							cin>>CI2;
							cin.clear();
							cin.sync();
							cout<<"������γ�ѧ�ֲ��Իس�������";
							cin>>Cre2;
							cin.clear();
							cin.sync();
							cout<<"�����������ʦ�Ľ�ְ���Ų��Իس�������";
							cin>>TI2;
							cin.clear();
							cin.sync();
							for(int j=0;j<TeacherNumber;j++)     //ɾ��ԭ�ȵ���Ϣ
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
							for(int j=0;j<TeacherNumber;j++)     //�½���Ϣ
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
						cout<<"�ÿγ̲����ڣ�"<<endl;
					}
				}
				break;
			case 9:
				return 0;
				break;
			default:
				cout<<"������1-9������ֽ��в�����"<<endl;
			}
		}
	}
	else
	{
		cout<<"������������µ�¼��"<<endl;
		return 0;
	}
	return 1;
}