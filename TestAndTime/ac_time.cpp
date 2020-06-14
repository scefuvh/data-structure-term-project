#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <dirent.h>//linux
// #include "include/dirent.h"//win
#include <regex>
#include <fstream>
#include <string>
#include <sys/time.h>
#include<sstream>
using namespace std;
/*
代码在mac上测试通过
author：bear
*/

/* 读文件，根据操作系统决定是否去除'\r' */
string readfile(string filepath){
    stringstream str1;
    ifstream op;
    char x;
    op.open(filepath);
    string line;
	while(getline(op, line))
	{
        int ls=line.size();
        if(line[ls-1]=='\r')
            line=line.substr(0,line.size()-1);//去除'\r'
		str1<<line<<endl;
	}
    op.close();
    return str1.str();
}

bool eq(string myout, string out_f)
{
    bool r = false;
    string str1 = "", str2 = "";
    str1=readfile( myout);
    str2=readfile( out_f);
    if (str1 == str2)
        r = true;
    else
    {
        // cout << str1 << "|||||" << str2 << endl;
        r=false;
    }
    return r;
}


//把代码的main函数添加进去
int dot1(ifstream &cin, ofstream &cout){
    //从磁盘读写
    ;

}

int dot1_noio(istringstream &cin, ostringstream &cout){
    //内存中读写
    ;
}




int main()
{
    bool io_time=false;//是否计算读取数据的时间
    string dirname = "/Users/brobear/Downloads/数据结构本科/TASK1-IN &OUT/";//输入输出所在文件夹
    DIR *dp;
    struct dirent *dirp;
    dp = opendir(dirname.c_str());
    if (dp == NULL)
        cout << "Can't open " << dirname << endl;

    regex reg_obj(".*\.in", regex::icase);
    double alltime = 0;
    while ((dirp = readdir(dp)) != NULL)
        if (dirp->d_type == 8 && regex_match(dirp->d_name, reg_obj))
        {
            bool r = false;
            string in_f = dirname + string(dirp->d_name);
            cout << dirp->d_name;
            string out_f = in_f.substr(0, in_f.size() - 2) + "out";
            timeval starttime, endtime;
            double timeuse = 0;
            if(io_time){
                ifstream infile;
                infile.open(in_f);
                ofstream outfile;
                string myout = "myout";
                outfile.open(myout); //我的输出（缓存文件）
                try
                {
                    gettimeofday(&starttime, 0);
                    //do some process here
                    dot1(infile, outfile);//算上读写硬盘时间
                    gettimeofday(&endtime, 0);
                    timeuse = 1000000 * (endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec; //us
                }
                catch (...)//todo 把错误细分输出
                {
                    cout << "run error" << endl;
                    infile.close();
                    outfile.close();
                    continue;
                }
                infile.close();
                outfile.close();
                //判断对错
                r = eq(myout, out_f);
            }
            else{
                // 如果读写不计时（将io限制在内存）的话，可以用ostringstream，istringstream 进行修改 
                //读数据
                string in_str=readfile( in_f);
                istringstream  infile(in_str);
                ostringstream  outfile;
                try
                {
                    gettimeofday(&starttime, 0);
                    //do some process here
                    dot1_noio(infile, outfile);//算上读写硬盘时间
                    gettimeofday(&endtime, 0);
                    timeuse = 1000000 * (endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec; //us
                }
                catch (...)//todo 把错误细分输出
                {
                    cout << "run error" << endl;
                    continue;
                }
                string out_str=readfile(out_f);
                string my_str=outfile.str();
                if (my_str==out_str){//判断对错
                    r=true;
                }

            }
            alltime += timeuse;

            if (r)
            {
                cout << " √ " << timeuse/1000 << "ms" << endl;
            }
            else
            {
                cout << " x " << endl;
            }
            
        }
    cout << "alltime: " << alltime / 1000000 << "s" << endl;
    closedir(dp);
    return 0;
}