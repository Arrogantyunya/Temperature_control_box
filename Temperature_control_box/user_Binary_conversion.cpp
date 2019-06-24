//user_crc8.cpp
/*
*��Ȩ
*
* �ļ�����:user_crc8.cpp
* �ļ���ʶ:���ù���ƻ���
* ժҪ:crc8У��ֵ�ļ���Ա�
*
* ��ǰ�汾:V1.0
* ����:���һ�
* �������:
* �޸���:
* �޸�����:
*
* ȡ���汾:
* ԭ����:���һ�
* �������:
*/


#include "user_Binary_conversion.h"	//����ͷ�ļ�


/*�쳣���ʱ����ʾ����*/
void help(char * strnum)
{
	Serial.print("������Ч����ʽΪ:\n%s [num]\n");
	Serial.println(strnum);
	Serial.println("��������Ƹ�ʽΪ0Bccc\n");
	Serial.println("����˽��Ƹ�ʽΪ0ccc\n");
	Serial.println("����ʮ�����Ƹ�ʽΪ0xccc\n");
	Serial.println("����ʮ���Ƹ�ʽΪccc\n");
}

/*
 * name : strToInt()
 * [IN]
 * flag ��10 ʮ����
 *        2 ������
 *        8 �˽���
 *        16 ʮ������
 * strn ��Ҫת�����ַ���
 * [OUT]
 * num  ���洢ת�����ֵ
 * ret  ��0 �ɹ�
 *       -1 ʧ��
 *
 * descr: ��strn������ת����10����������num 
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
/*��ʮ����ת����2�������*/
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
/*ÿƫ��offset������str�����һ���ո񣬲��������ɵ��ַ�������out*/
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
 * num[in]: ����ת����2���Ƶ�����
 *
 * str[out]:  ���ڴ洢ת�����2�����ַ���
 * 
 * desc��������ת���ɶ������ַ���
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
 * num[in] : ����
 *
 * flag[in] : �����ʾ���ͣ�
 *            10 ʮ����
 *            16 ʮ������
 *            8  �˽���
 *            2  ������
 *
 * desc: ����������flag�����ʾ
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
        Serial.println("  ʮ���ƣ�");
    }
    else if (flag == 8){
        sprintf(str, "%lo", num);
        strFormat(str,out,3);
		Serial.println("  �˽��ƣ�");
    }
    else if (flag == 16){
        sprintf(str, "%lx", num);
        strFormat(str,out,2);
		Serial.println("ʮ�����ƣ�");
    }
    else if (flag == 2){
        intToB(num,str);
        strFormat(str,out,4);
		Serial.println("  �����ƣ�");
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
    //���ַ�תת����ʮ������
    if(len == 1){
        if (p[0] <= '0' || p[0] > '9'){
            res = -1;
        }
        else{//ʮ����
            num = p[0] - '0';
        }
    }
    else if (len  == 2){
        if (p[0] == '0'){
            if(p[1] > '0' && p[1] < '8'){//�˽���
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
        if (p[0] > '0' && p[0] <= '9'){//ʮ����
            res = strToInt(p, &num, 10);
        }
        if (p[0] == '0'){
            if(p[1] > '0' && p[1] < '8'){//�˽���
                res = strToInt(p+1, &num, 8);
            }
            else if(p[1] == 'B' || p[1] == 'b' ){//������
                res = strToInt(p+2, &num, 2);
            }
            else if(p[1] == 'x' || p[1] == 'X' ){//ʮ������
                res = strToInt(p+2, &num, 16);
            }
        }
    }
    if (res == -1){
        help(argv[0]);
        return 0;
    }
    #if FIRST
    printf("ʮ�����ƣ�%lx\n",num);
    printf("  ʮ���ƣ�%lu\n",num);
    printf("  �˽��ƣ�%lo\n",num);
    printf("  �����ƣ�");
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