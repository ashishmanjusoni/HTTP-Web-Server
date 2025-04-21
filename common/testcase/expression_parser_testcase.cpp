#include<iostream>
#include<expression_parser>
#include<map>
using namespace std;
using namespace wss;

int main()
{
map<string,string> map;
string parsedExpression;
FILE *file;
char buffer[1026];
int size;
ExpressionParser expressionParser;
map.insert(pair<string,string>("Machine","Thinking"));
map.insert(pair<string,string>("Intelligence","machines"));
map.insert(pair<string,string>("from","Ujjain"));
map.insert(pair<string,string>("predictions","always true"));
map.insert(pair<string,string>("kive","online"));
map.insert(pair<string,string>("types","programming"));
file=fopen("abc.data","rb");
fseek(file,0,SEEK_END);
size=ftell(file);
fseek(file,0,SEEK_SET);
while(1)
{
if(size<1024)
{
fread(buffer,size,1,file);
buffer[size]='\0';
parsedExpression=expressionParser.parse(buffer,&map,true);
cout<<parsedExpression;
break;
}
else
{
fread(buffer,1024,1,file);
buffer[1024]='\0';
parsedExpression=expressionParser.parse(buffer,&map,false);
cout<<parsedExpression;
}
size-=1024;
}
fclose(file);
return 0;
}
