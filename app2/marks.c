#include<stdio.h>
struct marks
{
int rollnumber;
int hindi;
int physics;
int chemistry;
int maths;
int english;
};
int main()
{
FILE *file;
struct marks m1,m2,m3,m4,m5;
m1.rollnumber=100;
m1.hindi=100;
m1.physics=80;
m1.chemistry=84;
m1.maths=97;
m1.english=75;

m2.rollnumber=101;
m2.hindi=90;
m2.physics=70;
m2.chemistry=64;
m2.maths=88;
m2.english=80;

m3.rollnumber=102;
m3.hindi=50;
m3.physics=65;
m3.chemistry=63;
m3.maths=65;
m3.english=45;

m4.rollnumber=103;
m4.hindi=100;
m4.physics=100;
m4.chemistry=100;
m4.maths=100;
m4.english=90;

m5.rollnumber=104;
m5.hindi=50;
m5.physics=40;
m5.chemistry=54;
m5.maths=43;
m5.english=38;

file=fopen("marks.data","ab");
fwrite(&m1,sizeof(m1),1,file);
fwrite(&m2,sizeof(m2),1,file);
fwrite(&m3,sizeof(m3),1,file);
fwrite(&m4,sizeof(m4),1,file);
fwrite(&m5,sizeof(m5),1,file);
fclose(file);
return 0;
}
