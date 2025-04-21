#include<map>
#include<string.h>
#include<iostream>
#include<expression_parser>
using namespace std;
using namespace wss;

ExpressionParser::ExpressionParser()
{
this->symbol=0;
this->expression="";
}
string ExpressionParser::parse(const char* buffer,map<string,string> *parameters,bool clear=false)
{
if(strlen(buffer)<=0 || !parameters || parameters->empty()) return string ("");
string content;
const char *e;
for(e=buffer;*e;e++)
{
if(*e=='$' || *e=='{')
{
if(this->symbol==127)
{
content.append(this->expression);
this->expression.clear();
this->symbol=0;
}
this->symbol=(this->symbol) | (int)(*e);
}
else if(*e=='}')
{
if(this->symbol==127)
{
if(!this->expression.empty())
{
map<string,string>::iterator itr=parameters->find(expression);
if(itr==parameters->end()) content.append("${").append(expression).append("}");
else content.append(itr->second);
expression.clear();
}
}
else
{
content.push_back((char)this->symbol);
content.push_back(*e);
}
this->symbol=0;
}
else if(this->symbol==127) this->expression.push_back(*e);
else
{
if(this->symbol==36 || this->symbol==123)
{
content.push_back((char)(this->symbol));
this->expression.clear();
this->symbol=0;
}
else content.push_back(*e);
}
}
if(clear)
{
if(this->symbol==127) content.append("${");
if(this->symbol==36 || this->symbol==123) content.push_back((char)this->symbol);
if(!this->expression.empty()) content.append(this->expression);
this->expression.clear();
}
return content;
}

