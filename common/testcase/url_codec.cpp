#include<iostream>
#include<url_encoder>
#include<url_decoder>
using namespace std;
using namespace wss;

int main()
{
const char *e,*f;
e=URLDecoder::decode("rollnumber%3D10001%26name%3DAshish+soni%26city%3DNagda%26gender%3Dm%26caste%3DHindu");
//e=URLFormatter::decode("");
cout<<e<<endl;
f=URLEncoder::encode(e);
cout<<f<<endl;
free((char*)e);
free((char*)f);
return 0;
}
