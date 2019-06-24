//user_crc8.cpp
/*
*版权
*
* 文件名称:user_crc8.cpp
* 文件标识:配置管理计划书
* 摘要:crc8校验值的计算对比
*
* 当前版本:V1.0
* 作者:刘家辉
* 完成日期:
* 修改者:
* 修改日期:
*
* 取代版本:
* 原作者:刘家辉
* 完成日期:
*/


#include "user_Binary_conversion.h"	//引用头文件


/*异常输出时，显示帮助*/
void help(char * strnum)
{
	Serial.print("参数无效，格式为:\n%s [num]\n");
	Serial.println(strnum);
	Serial.println("输入二进制格式为0Bccc\n");
	Serial.println("输入八进制格式为0ccc\n");
	Serial.println("输入十六进制格式为0xccc\n");
	Serial.println("输入十进制格式为ccc\n");
}

/*
 * name : strToInt()
 * [IN]
 * flag ：10 十进制
 *        2 二进制
 *        8 八进制
 *        16 十六进制
 * strn ：要转化的字符串
 * [OUT]
 * num  ：存储转化后的值
 * ret  ：0 成功
 *       -1 失败
 *
 * descr: 将strn的内容转化成10进制数赋给num 
 */
int strToInt(char *strn, unsigned long *num, int flag)
{
    int len = strlen(strn);
    *num = 0;
    switch(flag){
        case 2:
        case 8:
        case 10:
            while(len > 0){
                if(*strn >= '0' && *strn < '0' + flag){
                    *num = *num * flag + *strn - '0';
                    strn++;
                    len--;
                }
                else{
                    return -1;
                }
            }
            break;

        case 16:
            while(len > 0){
                if(*strn >= '0' && *strn <= '9'){
                    *num = *num * flag + *strn - '0';
                    strn++;
                    len--;
                }
                else if (*strn == 'a' || *strn == 'A'){
                    *num = *num * flag + 10;
                    strn++;
                    len--;
                }
                else if (*strn == 'b' || *strn == 'B'){
                    *num = *num * flag + 11;
                    strn++;
                    len--;
                }
                else if (*strn == 'c' || *strn == 'C'){
                    *num = *num * flag + 12;
                    strn++;
                    len--;
                }
                else if (*strn == 'd' || *strn == 'D'){
                    *num = *num * flag + 13;
                    strn++;
                    len--;
                }
                else if (*strn == 'e' || *strn == 'E'){
                    *num = *num * flag + 14;
                    strn++;
                    len--;
                }
                else if (*strn == 'f' || *strn == 'F'){
                    *num = *num * flag + 15;
                    strn++;
                    len--;
                }
                else{
                    return -1;
                }
            }
            break;

        default:
            return -1;
    }
    return 0;

}

#if FIRST
/*将十进制转换成2进制输出*/
void Ten2B(unsigned long num,int l)
{
    l++;
    if(num>1){
        Ten2B(num/2,l);
    }
    if (l%4 == 0){
        printf(" ");
    }
    if (l%8 == 0){
        printf(" ");
    }
    printf("%lu",num%2);
    
}

#else
/*每偏移offset个数在str中添加一个空格，并将新生成的字符串赋给out*/
void strFormat(char *str, char *out, int offset)
{
    int len = strlen(str);
    int i ,j;
    i = j = 0;
    while(i < len %offset){
        out[i] = str[j];
        i++;
        j++;
    }
    if (i != 0){
        out[i] = ' ';
        i++;
    }
    while(j < len){
        int k = 0;
        while(k < offset){
            out[i+k] = str[j+k];
            k++;
        }
        j+=k;
        i+=k;
        out[i] = ' ';
        i++;
    }
}

/*
 * NAME: intToB
 * 
 * num[in]: 用于转化成2进制的整数
 *
 * str[out]:  用于存储转化后的2进制字符串
 * 
 * desc：将整数转化成二进制字符串
 *
 *
 * */
void intToB(unsigned long num, char *str)
{
    int len = 0;
    while(num > 0){
        str[len] = '0' + num%2;
        num /= 2;
        len++;
    }
    int j = 0;
    while(j < len/2){
        char tmp = str[j];
        str[j] = str[len - 1 - j];
        str[len - 1 - j] = tmp;
        j++;
    }
}

/*
 * name: displayNum
 *
 * num[in] : 整数
 *
 * flag[in] : 输出显示类型：
 *            10 十进制
 *            16 十六进制
 *            8  八进制
 *            2  二进制
 *
 * desc: 将整数按照flag输出显示
 *
 * */
void displyNum(unsigned long num, int flag)
{
    char str[64];
    char out[100];
    bzero(str,sizeof(str));
    bzero(out,sizeof(out));
    if(flag == 10){
        sprintf(str, "%lu", num);
        strFormat(str,out,3);
        Serial.println("  十进制：");
    }
    else if (flag == 8){
        sprintf(str, "%lo", num);
        strFormat(str,out,3);
		Serial.println("  八进制：");
    }
    else if (flag == 16){
        sprintf(str, "%lx", num);
        strFormat(str,out,2);
		Serial.println("十六进制：");
    }
    else if (flag == 2){
        intToB(num,str);
        strFormat(str,out,4);
		Serial.println("  二进制：");
    }
	Serial.println(out);
}

#endif
int main(int argc, char **argv)
{
    
    if(argc != 2){
        help(argv[0]);
        return 0;
    }
    int res = 0;
    unsigned long num = 0;
    char *p = argv[1];
    int len = strlen(p);
    //将字符转转换成十进制数
    if(len == 1){
        if (p[0] <= '0' || p[0] > '9'){
            res = -1;
        }
        else{//十进制
            num = p[0] - '0';
        }
    }
    else if (len  == 2){
        if (p[0] == '0'){
            if(p[1] > '0' && p[1] < '8'){//八进制
                num = p[1] - '0';
            }
            else{//
                res = -1;
            }
        }
        else{
            res = -1;
        }

    }
    else {
        if (p[0] > '0' && p[0] <= '9'){//十进制
            res = strToInt(p, &num, 10);
        }
        if (p[0] == '0'){
            if(p[1] > '0' && p[1] < '8'){//八进制
                res = strToInt(p+1, &num, 8);
            }
            else if(p[1] == 'B' || p[1] == 'b' ){//二进制
                res = strToInt(p+2, &num, 2);
            }
            else if(p[1] == 'x' || p[1] == 'X' ){//十六进制
                res = strToInt(p+2, &num, 16);
            }
        }
    }
    if (res == -1){
        help(argv[0]);
        return 0;
    }
    #if FIRST
    printf("十六进制：%lx\n",num);
    printf("  十进制：%lu\n",num);
    printf("  八进制：%lo\n",num);
    printf("  二进制：");
    Ten2B(num,0);
    printf("\n");
    #else
    displyNum(num, 16);
    displyNum(num, 10);
    displyNum(num, 8);
    displyNum(num, 2);
    #endif
    return 0;
}