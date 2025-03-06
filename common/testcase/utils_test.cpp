#include<utils>
#include<iostream>
using namespace std;

int main()
{
char left[100];
char right[100];
strcpy(left,"text/htmls");
strcpy(right,"text/htmls");
cout<<wss::extensionEquals((const char *)left,(const char *)right)<<endl;
strcpy(left,"text/html");
strcpy(right,"text/css");
cout<<wss::extensionEquals((const char *)left,(const char *)right)<<endl;
cout<<wss::extensionEquals(NULL,right)<<endl;
cout<<wss::extensionEquals(left,NULL)<<endl;
cout<<wss::extensionEquals(NULL,NULL)<<endl;
return 0;
}

