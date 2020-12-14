/*-------------------------------------。
程序名字：离散结构逻辑表达式计算机[增强版] 
程序作者：CTGU_LLZ
完成时间：2020/12/4-2020/12/4

函数说明：
	1.binaryAdder 模拟n位数的0-1循环
	2.getAns0 格式化好的情况下进行求值[全是基础模拟]
	3.getAns 去除括号[少量注释讲解] 
	4.format 讲等价式或者蕴含式展开[注释讲解] 
	5.printTable 打印表格
	调用逻辑： 展开 -> 去括号 -> 求值 -> 打印 
变量说明： 略，英文字面意思 
代码补充：本代码可以用很多方式优化，例如查找变量可以直接用map去找，存新的变量可以用set直接插入等等 
--------------------------------------*/
#include <math.h>
#include <stdio.h> /*	标准输入输出头文件 */
#include <string.h>/*	字符串数组的函数定义的头文件	*/
#define N 500
void binaryAdder(int b[N], int f) /*二进制赋值加一器*/
{
    //原理就是二进制相当于写几层for循环
    if (b[f] == 0) //如果本位是0则加一
        b[f] = 1;
    else //否则相当于1+1进位递归判断后面是否进位
    {
        b[f] = 0;
        binaryAdder(b, f + 1);
    }
}
//原理类似计算机 
int getAns0(char expression[N], char variable[N], int loop[N], int h0) //不带括号版本计算值
{
    int i, h = 0, j = 0, j1 = 0, j2 = 0, j3 = 0, i1, i2, p1 = -1, p2 = -1, s;
    char dt[N];
    s = strlen(expression);
    if (s == 1)
        if (expression[0] == -2)
            return 0;
        else
            return 1; /*1	就是 expression[0] 的值*/
    else
    {
        for (i = 0; i < s - j; i++) /*	先处理非 */
        {
            if (expression[i] == '!')
            {
                for (i1 = 0; i1 < h0; i1++)
                    if (expression[i + 1] == variable[i1])
                        p1 = loop[i1];
                if (expression[i + 1] == -2)
                    p1 = 0;
                if (p1 == -1)
                    p1 = expression[i + 1];
                dt[j + 2] = !p1;
                expression[i] = j + 2;
                j++;
                p1 = 0;
                for (i1 = i + 1; i1 < s - j; i1++)
                    expression[i1] = expression[i1 + 1];
            }
        }
        p1 = -1;
        j1 = j;
        for (i = 0; i < s - j1 - 2 * j2; i++) /*	处理与 */
            if (expression[i] == '&')
            {
                for (i1 = 0; i1 < h0; i1++)
                {
                    if (expression[i - 1] == variable[i1])
                        p1 = loop[i1];
                    if (expression[i + 1] == variable[i1])
                        p2 = loop[i1];
                }
                for (i2 = 2; i2 < j + 2; i2++)
                {
                    if (expression[i - 1] == i2)
                        p1 = dt[i2];
                    if (expression[i + 1] == i2)
                        p2 = dt[i2];
                }
                if (expression[i - 1] == -2)
                    p1 = 0;
                if (expression[i + 1] == -2)
                    p2 = 0;
                if (p1 == -1)
                    p1 = (int)(expression[i - 1]);
                if (p2 == -1)
                    p2 = (int)(expression[i + 1]);
                dt[j + 2] = p1 && p2;
                expression[i - 1] = j + 2;
                j++;
                j2++;
                p1 = -1;
                p2 = -1;
                for (i1 = i; i1 < s - j1 - 2 * j2; i1++)
                    expression[i1] = expression[i1 + 2];
                i = i - 1;
            }
        for (i = 0; i < s - j1 - 2 * j2 - 2 * j3; i++) /*	处理或 */
            if (expression[i] == '|')
            {
                for (i1 = 0; i1 < h0; i1++)
                {
                    if (expression[i - 1] == variable[i1])
                        p1 = loop[i1];
                    if (expression[i + 1] == variable[i1])
                        p2 = loop[i1];
                }
                for (i2 = 2; i2 < j + 2; i2++)
                {
                    if (expression[i - 1] == i2)
                        p1 = dt[i2];
                    if (expression[i + 1] == i2)
                        p2 = dt[i2];
                }
                if (expression[i - 1] == -2)
                    p1 = 0;
                if (expression[i + 1] == -2)
                    p2 = 0;
                if (p1 == -1)
                    p1 = expression[i - 1];
                if (p2 == -1)
                    p2 = expression[i + 1];
                dt[j + 2] = p1 || p2;
                expression[i - 1] = j + 2;
                j++;
                j3++;
                p1 = -1;
                p2 = -1;
                for (i1 = i; i1 < s - j1 - 2 * j2 - 2 * j3; i1++)
                    expression[i1] = expression[i1 + 2];
                i--;
            }
        return dt[j + 1];
    }
}
int getAns(char expression[N], char variable[N], int loop[N], int h0) //去括号
{
    int i, j, k, slen, bracketsNum = 0, bracketsIndex[N], flag; /*bracketsIdex 用来保存括号位置 */
    char charStore[N], brackets[N];                             /*charStore	用来保存括号内的字符	brackets 用来保存括号 */
    slen = strlen(expression);
    for (i = 0; i < slen; i++)
    {
        if (expression[i] == '(' || expression[i] == ')')
        {
            bracketsIndex[bracketsNum] = i;
            brackets[bracketsNum] = expression[i];
            bracketsNum++;
        }
    }
    if (bracketsNum == 0)
        return getAns0(expression, variable, loop, h0);
    else
    {
        for (i = 0; i < bracketsNum; i++) //找到第一个右括号
            if (brackets[i] == ')')
                break;
        for (j = bracketsIndex[i - 1] + 1, k = 0; j < bracketsIndex[i]; j++, k++) //储存这层括号内表达式
            charStore[k] = expression[j];
        charStore[k] = '\0';

        flag = getAns0(charStore, variable, loop, h0);
        if (flag == 1)
            expression[bracketsIndex[i - 1]] = 1;
        else
            expression[bracketsIndex[i - 1]] = -2;
        for (j = bracketsIndex[i - 1] + 1; j < slen + bracketsIndex[i - 1] - bracketsIndex[i]; j++) //去括号
            expression[j] = expression[j + bracketsIndex[i] - bracketsIndex[i - 1]];
        expression[j] = '\0';
        return getAns(expression, variable, loop, h0);
    }
}

void format(char expression[N]) //格式化蕴含式和等价式展开，方便求值 
{             
    while (1) //从左往右的优先级
    {
        int flag = 1;                                    //有没有 -> 或者 <->
        char left[N], midLeft[N], midRight[N], right[N]; //左边部分右边部分和 -> 符号分开的两个部分
        int slen = strlen(expression);
        for (int i = 0; i < slen; i++)
        {
            if (expression[i] == '-' && expression[i + 1] == '>')
            { //处理蕴含式 q&(p->r)|y 后面用这个举例
                //蕴含式优先级最低，要考虑有无括号情况
                flag = 0;
                int li = i - 1, bracketsNum = 0;
                //往左边扫
                //匹配到左括号+1，右括号-1
                while (li >= 0) //有单独的左括号表示q|（q->r）蕴含式优先级杯括号提高了单独处理
                {
                    if (expression[li] == ')')
                        bracketsNum--;
                    else if (expression[li] == '(')
                        bracketsNum++;
                    if (bracketsNum > 0)
                        break;
                    li--;
                }
                if (bracketsNum > 0) //有多余左括号
                {
                    int j = 0, tempi = li + 1;
                    for (tempi; tempi < i; tempi++)
                    { //把p存起来
                        midLeft[j++] = expression[tempi];
                    }
                    midLeft[j] = '\0';
                    for (tempi = 0; tempi <= li; tempi++)
                    { //把q存起来
                        left[tempi] = expression[tempi];
                    }
                    left[tempi] = '\0';
                }
                else
                {
                    int tempi;
                    left[0] = '\0';
                    for (tempi = 0; tempi < i; tempi++)
                    { //把q存起来
                        midLeft[tempi] = expression[tempi];
                    }
                    midLeft[tempi] = '\0';
                }
                li = i + 2, bracketsNum = 0;
                //往右边扫
                //匹配到左括号+1，右括号-1
                while (li < slen && expression[li] != '-' && expression[li] != '<') //和上面原理相反
                {
                    if (expression[li] == ')')
                        bracketsNum--;
                    else if (expression[li] == '(')
                        bracketsNum++;
                    if (bracketsNum < 0)
                        break;
                    li++;
                }
                if (bracketsNum < 0 || expression[li] == '-' || expression[li] == '<') //有多余又括号
                {
                    int j = 0, tempi;
                    for (tempi = i + 2; tempi < li; tempi++)
                    { //把p存起来
                        midRight[j++] = expression[tempi];
                    }
                    midRight[j] = '\0';
                    j = 0;
                    for (tempi = li; tempi < slen; tempi++)
                    { //把q存起来
                        right[j++] = expression[tempi];
                    }
                    right[j] = '\0';
                }
                else
                {
                    int tempi;
                    right[0] = '\0';
                    int j = 0;
                    for (tempi = i + 2; tempi < slen; tempi++)
                    { //把q存起来
                        midRight[j++] = expression[tempi];
                    }
                    midRight[j] = '\0';
                }
                //开始拼接新的expression
                //r&q->p|a  --> (!(r&q)v())
                expression[0] = '\0';
                strcat(expression, left);
                strcat(expression, "(!");
                if (strlen(midLeft) > 1)
                    strcat(expression, "(");
                strcat(expression, midLeft);
                if (strlen(midLeft) > 1)
                    strcat(expression, ")");
                strcat(expression, "|");
                if (strlen(midRight) > 1)
                    strcat(expression, "(");
                strcat(expression, midRight);
                if (strlen(midRight) > 1)
                    strcat(expression, ")");
                strcat(expression, ")");
                strcat(expression, right);
                break;
            }
            else if (i + 2 < slen && expression[i] == '<' && expression[i + 1] == '-' && expression[i + 2] == '>')
            { //处理等价式
                flag = 0;
                int li = i - 1, bracketsNum = 0;
                //和上面同理，只是长度变成了3个 <->
                while (li >= 0)
                {
                    if (expression[li] == ')')
                        bracketsNum--;
                    else if (expression[li] == '(')
                        bracketsNum++;
                    if (bracketsNum > 0)
                        break;
                    li--;
                }
                if (bracketsNum > 0) //有多余左括号
                {
                    int j = 0, tempi = li + 1;
                    for (tempi; tempi < i; tempi++)
                    { //把p存起来
                        midLeft[j++] = expression[tempi];
                    }
                    midLeft[j] = '\0';
                    for (tempi = 0; tempi <= li; tempi++)
                    { //把q存起来
                        left[tempi] = expression[tempi];
                    }
                    left[tempi] = '\0';
                }
                else
                {
                    int tempi;
                    left[0] = '\0';
                    for (tempi = 0; tempi < i; tempi++)
                    { //把q存起来
                        midLeft[tempi] = expression[tempi];
                    }
                    midLeft[tempi] = '\0';
                }
                li = i + 2, bracketsNum = 0;
                //往右边扫
                //匹配到左括号+1，右括号-1
                while (li < slen && expression[li] != '-' && expression[li] != '<') //和上面原理相反
                {
                    if (expression[li] == ')')
                        bracketsNum--;
                    else if (expression[li] == '(')
                        bracketsNum++;
                    if (bracketsNum < 0)
                        break;
                    li++;
                }
                if (bracketsNum < 0 || expression[li] == '-' || expression[li] == '<') //有多余又括号
                {
                    int j = 0, tempi;
                    for (tempi = i + 3; tempi < li; tempi++)
                    { //把p存起来
                        midRight[j++] = expression[tempi];
                    }
                    midRight[j] = '\0';
                    j = 0;
                    for (tempi = li; tempi < slen; tempi++)
                    { //把q存起来
                        right[j++] = expression[tempi];
                    }
                    right[j] = '\0';
                }
                else
                {
                    int tempi;
                    right[0] = '\0';
                    int j = 0;
                    for (tempi = i + 3; tempi < slen; tempi++)
                    { //把q存起来
                        midRight[j++] = expression[tempi];
                    }
                    midRight[j] = '\0';
                }
                expression[0] = '\0';
                strcat(expression, left);
                strcat(expression, "((!");
                if (strlen(midLeft) > 1)
                    strcat(expression, "(");
                strcat(expression, midLeft);
                if (strlen(midLeft) > 1)
                    strcat(expression, ")");
                strcat(expression, "|");
                if (strlen(midRight) > 1)
                    strcat(expression, "(");
                strcat(expression, midRight);
                if (strlen(midRight) > 1)
                    strcat(expression, ")");
                strcat(expression, ")&");
                strcat(expression, "(!");
                if (strlen(midRight) > 1)
                    strcat(expression, "(");
                strcat(expression, midRight);
                if (strlen(midRight) > 1)
                    strcat(expression, ")");
                strcat(expression, "|");
                if (strlen(midLeft) > 1)
                    strcat(expression, "(");
                strcat(expression, midLeft);
                if (strlen(midLeft) > 1)
                    strcat(expression, ")");
                strcat(expression, "))");
                strcat(expression, right);
                break;
            }
        }
        //printf("%s\n", expression);
        if (flag)
            break; //没有蕴含式或者等价式退出
    }
}

void printTable() /*	功能 BC*/
{
    int i1, i2, loop[N], bracketsNum = 0, ans, variableNum = 0;
    char expression[N], oldexpression[N], variable[N], expressionTemp[N];
    printf("【请输入一个合法的命题公式】\n");
    printf("|基本析取：q|p            |\n");
    printf("|基本合取: q&p            |\n");
    printf("|可包含蕴含式 : q->r      |\n");
    printf("|可包含等价式 : q<->r     |\n");
    printf("|可包含否和括号: p|(!q|r) |\n");
    printf("|\n|\n|:");
    scanf("%s", expression);
    strcpy(oldexpression, expression);
    format(expression); //将主析取范式转换为标准式
    strcpy(expressionTemp, expression);
    for (i1 = 0; i1 < strlen(expression); i1++)
    {
        if (expression[i1] == ')' || expression[i1] == '(')
            bracketsNum++;
        if (expression[i1] >= 'a' && expression[i1] <= 'z' || expression[i1] >= 'A' && expression[i1] <= 'Z')
        {
            for (i2 = 0; i2 < variableNum; i2++) /*	判断并储存变量 */
                if (variable[i2] == expression[i1])
                    break;
            if (i2 == variableNum) //自然退出循环说明变量之前还没有过就存下
            {
                variable[variableNum] = expression[i1];
                variableNum++;
            }
        }
    }
    printf("总变量个数为：	%d\n", variableNum);
    variableNum;
    printf("输出真值表如下： \n");
    //打印表头的信息
    for (i1 = 0; i1 < variableNum; i1++)
        printf(" %c ", variable[i1]);
    printf("[%s] ==> ", oldexpression);
    printf("[%s] ", expression);
    printf("\n");
    for (i1 = 0; i1 < variableNum; i1++) /*	先将所有的变量赋值为零	*/
        loop[i1] = 0;
    //打印表格主体的信息
    for (i1 = 0; i1 < (int)pow(2, variableNum); i1++) //打印2^n次方行情况
    {
        if (i1 != 0)              //0的时候不需要加一
            binaryAdder(loop, 0); //n位二进制递归加法器：000 -> 100 -> 010 -> 110类似
        ans = getAns(expression, variable, loop, variableNum);
        strcpy(expression, expressionTemp);  //恢复被修改的数组
        for (i2 = 0; i2 < variableNum; i2++) //将每行的变量真值打印出来
            printf(" %d ", loop[i2]);
        for (int formati = 0; formati < strlen(oldexpression) + 5; formati++)
            printf("-");
        printf("> ");
        for (int formati = 0; formati < strlen(oldexpression); formati++)
            printf(" ");
        printf("%d\n", ans);
    }
    getchar(); 
    getchar();
}

int main()
{
    do
    {
        printTable();
    } while (1);
}

