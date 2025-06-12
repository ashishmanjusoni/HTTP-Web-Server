#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>

int main(int count,char **args)
{
if(count<2) return 0;
int write_as_expr;
int complete_expr;
int i;
char m;
char *e;
char *f,*g;
char buffer[1025];
int symbol;
FILE *tpl_file;
FILE *tpl_cpp_file;
char *tpl_cpp_file_name;
char *function_name;
char *tpl_file_name;
struct stat st_tpl_file;
struct stat st_tpl_cpp_file;
int x,y;
FILE * tpl_header_file;
char **functions;
int is_process_tpl;
functions=(char**)malloc(sizeof(char *)*(count-1));
is_process_tpl=0;
for(x=1,y=0;x<count;x++,y++)
{
buffer[0]='\0';
write_as_expr=0;
complete_expr=1;
symbol=0;
tpl_file_name=args[x];
tpl_file=fopen(tpl_file_name,"r");
if(!tpl_file) return 0;
fseek(tpl_file,0,SEEK_END);
if(ftell(tpl_file)<=0) return 0;
fseek(tpl_file,0,SEEK_SET);
tpl_cpp_file_name=(char*)malloc(sizeof(char)*(strlen(tpl_file_name)+5));
if(!tpl_cpp_file_name)
{
fclose(tpl_file);
continue;
}
strcpy(tpl_cpp_file_name,tpl_file_name);
strcat(tpl_cpp_file_name,".cpp");
// compare modification time
tpl_cpp_file=fopen(tpl_cpp_file_name,"r");
if(tpl_cpp_file)
{
fclose(tpl_cpp_file);
stat(tpl_file_name,&st_tpl_file);
stat(tpl_cpp_file_name,&st_tpl_cpp_file);
if(st_tpl_file.st_mtime<st_tpl_cpp_file.st_mtime) continue;
}
is_process_tpl=1;
tpl_cpp_file=fopen(tpl_cpp_file_name,"w");
if(!tpl_cpp_file) 
{
fclose(tpl_file);
free(tpl_cpp_file_name);
continue;
}
fputs("#include<http_request>\n",tpl_cpp_file);
fputs("#include<http_response>\n",tpl_cpp_file);
fputs("void ",tpl_cpp_file);
function_name=(char*)malloc(sizeof(char)*((strlen(tpl_cpp_file_name)+1)));
if(!function_name)
{
free(tpl_cpp_file_name);
fclose(tpl_file);
fclose(tpl_cpp_file);
remove(tpl_cpp_file_name);
continue;
}
f=tpl_cpp_file_name;
g=function_name;
while(*f)
{
if(*f=='.') *g='_';
else *g=*f;
f++;
g++;
}
*g='\0';
fputs(function_name,tpl_cpp_file);
functions[y]=function_name;
fputs("(wss::Request &request,wss::Response &response)\n{\n",tpl_cpp_file);
fputs("response.write(\"HTTP/1.1 200 OK\\n\");\n",tpl_cpp_file);
fputs("response.write(\"Content-Type: text/html\");\n",tpl_cpp_file);
fputs("response.write(\"\\n\\n\");\n",tpl_cpp_file);
while(1)
{
for(i=0;i<1024;i++)
{
m=fgetc(tpl_file);
if(feof(tpl_file)) break;
buffer[i]=m;
}
if(i==0) break;
buffer[i]='\0';
for(e=buffer;*e;e++)
{
if(*e=='$' || *e=='{')
{
symbol=(symbol)|(int)(*e);
if(symbol==127) write_as_expr=1;
continue;
}
if(write_as_expr)
{
if(complete_expr) fputs("response.write(request.getParameter(\"",tpl_cpp_file);
while(*e && *e!='}') 
{
fputc(*e,tpl_cpp_file);
e++;
}
if(!*e) 
{
complete_expr=0;
break;
}
fputs("\"));\n",tpl_cpp_file);
write_as_expr=0;
symbol=0;
if(!complete_expr) complete_expr=1;
}
else
{
fputs("response.write(\"",tpl_cpp_file);
while(*e && *e!='$' && *e!='\n')
{
if(*e=='"') fputs("'",tpl_cpp_file);
else fputc(*e,tpl_cpp_file);
e++;
}
fputs("\");\n",tpl_cpp_file);
if(*e=='$') e--;
if(!*e) break;
}
}
}
fputs("}\n",tpl_cpp_file);
fclose(tpl_file);
fclose(tpl_cpp_file);
free(tpl_cpp_file_name);
}
if(is_process_tpl)
{
tpl_header_file=fopen("tpl.h","w");
fputs("#ifndef __$__TPL__2025_\n",tpl_header_file);
fputs("#define __$__TPL__2025_\n",tpl_header_file);
fputs("#include<http_request>\n",tpl_header_file);
fputs("#include<http_response>\n",tpl_header_file);
fputs("#include<http_linux_tcp_server>\n",tpl_header_file);
fputs("using namespace wss;\n",tpl_header_file);
for(x=0;x<count-1;x++)
{
fputs("void ",tpl_header_file);
fputs(functions[x],tpl_header_file);
fputs("(wss::Request &request,wss::Response &response);\n",tpl_cpp_file);
}
fputs("void register_template_files(LinuxTCPServer *webServer){\n",tpl_header_file);
for(x=0;x<count-1;x++) 
{
fputs("webServer->onRequest(",tpl_header_file);
fputs("\"/",tpl_header_file);
fputs(args[x+1],tpl_header_file);
fputs("\",",tpl_header_file);
fputs(functions[x],tpl_header_file);
fputs(");\n",tpl_header_file);
free(functions[x]);
}
fputs("}\n",tpl_header_file);
fputs("#endif",tpl_header_file);
fclose(tpl_header_file);
}
return 0;
}
