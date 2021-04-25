#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
string str;//输入的整个字符串，包含空格、TAB、换行
string stri;//当前的字符串，一个标识符、一个关键字
int now=0;//str中每个字符的下标

struct node
{
	int id;//属性，关键字1，标识符2，数字5，分隔符3，运算符4
	string val;//字符串
	node(int _id,string _val)
	{
		id=_id;val=_val;
	}
};
vector<node*> ans;//

char keyword[13][15]=
{
	"CONST",
	"VAR",
	"PROCEDURE",
	"BEGIN",
	"END",
	"ODD",
	"IF",
	"THEN",
	"CALL",
	"WHILE",
	"DO",
	"READ",
	"WRITE"
};

void print()
{
	for(int i=0;i<ans.size();i++)
	{
		if(ans[i]->id==2)//标识符
		{
			cout<<"IDENTIFIER "<<ans[i]->val<<endl;
		}
		else if(ans[i]->id==5)//数字
		{
			int num=0;
			for(int j=0;j<ans[i]->val.size();j++)
				num=num*10+ans[i]->val[j]-'0';
			cout<<"NUMBER "<<num<<endl;
		}
		else cout<<ans[i]->val<<endl;
	}
}
int main()
{
	char ch;
	while((ch=getchar())!=EOF)//在输入缓冲区顺序读入一个字符(包括空格、回车和Tab)  
		str+=ch;
	//cout<<"sssssss"<<str<<endl;

	now=0;
	stri.clear();
	while(now<str.size())
	{
		//遍历整个字符串
		if(str[now]==' '||str[now]=='\n'||str[now]=='\t')
		{
			//空格 换行 TAB跳过
			now++;
			//continue;
		}
		else if((str[now]>='a'&&str[now]<='z')||str[now]>='A'&&str[now]<='Z')
		{
			if(str[now]>='a'&&str[now]<='z')str[now]-=32;//小写变大写
			stri+=str[now];
			now++;

			while(now<str.size()&&
				(str[now]>='a'&&str[now]<='z')||
				(str[now]>='A'&&str[now]<='Z')||
				str[now]>='0'&&str[now]<='9')
			{
				//是字母或数字
				if(str[now]>='a'&&str[now]<='z')str[now]-=32;
				stri+=str[now];
				now++;
			}

			int flag=0;//判断是否是关键字
			const char *cstr=stri.data();
			for(int i=0;i<13;i++)
			{
				if(strcmp(keyword[i],cstr)==0)
				{
					//关键字
					flag=1;
					node *t=new node(1,stri);
					ans.push_back(t);//加入结果数组
					//cout<<"<<<<<<<<<"<<stri<<endl;
					stri.clear();
					break;
				}
			}

			if(flag==0)//不是关键字，即标识符
			{
				if(stri.size()>10)
				{
					cout<<"Lexical Error"<<endl;
					exit(0);
				}
				//合法标识符
				node *t=new node(2,stri);
				ans.push_back(t);
				//cout<<"<<<<<<<<<"<<stri<<endl;
				stri.clear();
			}

		}
		else if(str[now]>='0'&&str[now]<='9')
		{
			//数字
			stri+=str[now];
			now++;
			while(now<str.size()&&str[now]>='0'&&str[now]<='9')
			{
				stri+=str[now];
				now++;
			}
			if(now<str.size()&&
				((str[now]<='z'&&str[now]>='a')||(str[now]>='A'&&str[now]<='Z')))
			{
				//数字之后有字母，出错
				cout<<"Lexical Error"<<endl;
				exit(0);
			}
			if(stri.size()>10)
			{
				//数字长度>10，出错
				//cout<<"Lexical Error"<<endl;
				exit(0);
			}


			node *t=new node(5,stri);
			ans.push_back(t);
			//cout<<"<<<<<<<<<"<<stri<<endl;
			stri.clear();
		}
		else if(str[now]==','||str[now]==';'||str[now]=='.'||str[now]=='('||str[now]==')')
		{
			//分隔符
			stri+=str[now];
			now++;

			node *t=new node(3,stri);
			ans.push_back(t);
			//cout<<"<<<<<<<<<"<<stri<<endl;
			stri.clear();
		}
		else if(str[now]=='*'||str[now]=='='||
			str[now]=='-'||str[now]=='+'||
			str[now]=='/'||str[now]=='#')
		{
			//单个运算符直接输出
			stri+=str[now];
			now++;

			node *t=new node(4,stri);
			ans.push_back(t);
			//cout<<"<<<<<<<<<"<<stri<<endl;
			stri.clear();
		}
		else if(str[now]=='<'||str[now]=='>')
		{
			//可能是双运算符，看下一个字符是否为=
			stri+=str[now];
			now++;
			if(str[now]=='=')
			{
				stri+=str[now];
				now++;
			}
			node *t=new node(4,stri);
			ans.push_back(t);
			//cout<<"<<<<<<<<<"<<stri<<endl;
			stri.clear();
		}
		else if(str[now]==':'&&str[now+1]=='=')
		{
			//双运算符
			stri+=str[now];
			now++;
			stri+=str[now];
			now++;
			node *t=new node(4,stri);
			ans.push_back(t);
			//cout<<"<<<<<<<<<"<<stri<<endl;
			stri.clear();
		}
		else
		{
			//错误
			cout<<"Lexical Error"<<endl;
			exit(0);
		}

	}
	print();
	return 0;
}