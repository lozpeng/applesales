#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <locale>  
#include <stdlib.h> 
#include <string.h>  
#include  <stdio.h>  
#include "calculator.h"

#ifdef IN
#undef IN
#endif
   
void Calculator::Clear(void)   
{ // 初始化计算器    
    PO.Clear();   
    Result = 0;   
    ErrorID = ERR_NO_ERROR;   
    VarCount = 0;   
    Expression[0] = '\0';   
   
    for(int i = 0; i < MaxNumber_of_Variable; i++) {   
        VarName[i][0] = '\0';   
        Vars[i] = 0.0;   
    }   
}   
   
const char* Calculator::GetErrorMessage(int errid) const   
{   
    static const char *errmsg[] = {"no errors",   
        "expression too long",   
        "missing operand",   
        "missing operator",   
        "missing left parenthesis",   
        "missing right paraenthesis",   
        "devide by zero",   
        "unknown operator",   
        "invalid operator",   
        "unknown error",   
        "too many variables",   
        "variable's name too long",   
        "UNKNOWN ERROR ID!!!"};   
   
    if(errid >= 0 && errid < 12)   
        return errmsg[errid];   
    else   
        return errmsg[12];   
}   
   
void Calculator::Assign(double *pExtVars)   
{ // 将pExtVars所指向数组的值赋给Vars[]    
    double *pd = Vars;    
    while(pd < Vars + VarCount)   
        *pd++ = *pExtVars++;   
}   
   
const char* Calculator::GetVariableName(int i)   
{   
	if ( i > 0 && i < VarCount )
		return VarName[i];
	else
		return 0;
}   

void Calculator::Trim( char *buf )
{
	char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789()+-*/^.";
	strupr( buf );
	
	int i = 0;
	int j = 0;
	char ch;
	while ( ch = buf[i++] )
	{
		if ( strchr( charset, ch) )
			Expression[j++] = ch;
	}

	Expression[j] = '\0';
}

bool Calculator::IsOperandChar( int i ) const
{
	char ch;
	char ch0;
	char ch1;

	int l = strlen( Expression );
	ch = Expression[i];
	ch0 = Expression[i == 0 ? 0 : i - 1];
	ch1 = Expression[i == l - 1 ? i : i -1];

	if ( isdigit(ch) || ch == '.')
		return true;

	if ( ch == '-' || ch == '+')
	{
		if ( strchr( "+-*/(", ch0) && ( isdigit( ch1 ) || ch1 == '.') )
			return true;
	}

	return false;
}

bool Calculator::IsOperatorChar( int i ) const
{
	char ch = Expression[i];
	if ( strchr("+-*/^", ch) != NULL )
		return true;

	if( isalpha( ch ) )
		return true;

	return false;
}

void Calculator::GetOperand( int &i, char *buf ) const
{
	int t = 0;
	while( IsOperandChar( i ) )
		buf[t++] = Expression[i++];

	buf[t] = '\0';
}

bool Calculator::GetOperator( int &i, char *buf ) const
{
	int t = 0;
	char ch;
	ch = Expression[i];

	if ( strchr("+-*/^", ch) != 0 )
	{
		buf[t++] = ch;
		i++;
		buf[t] = '\0';
		return true;
	} 

	while ( isalnum( Expression[i]) )
	{
		buf[t++] = Expression[i++];
		if ( t >= MaxNumber_of_Variable )
		{
			Error( ERR_VARIABLE_NAME_TOO_LONG, __LINE__ );
			return false;
		}
	}

	buf[t] = '\0';
	return true;
}
   
bool Calculator::GetUnary(element &EL, char ch, int rank) const   
{ // 处理单字符非字母操作符    
    if(rank == 1) { // 需要双目操作符    
        EL.isp = 1; EL.icp = 1;   
        switch (ch) {   
            case '+': EL.type = OPTR_ADD; break;   
            case '-': EL.type = OPTR_SUBTRACT; break;   
            case '*': EL.type = OPTR_MULTIPLY; EL.isp = EL.icp = 2; break;   
            case '/': EL.type = OPTR_DIVIDE; EL.isp = EL.icp = 2; break;   
            case '^': EL.type = OPTR_POWER; EL.isp = 3; EL.icp = 4; break;   
            default : Error(ERR_UNKNOWN_OPERATOR, __LINE__); return false;   
        }   
        return true;   
    }   
       
    if(rank == 0) { // 需要单目操作符    
        EL.isp = 4; EL.icp = 5;   
        switch (ch) {   
            case '+': EL.type = OPTR_POSITIVE; break;   
            case '-': EL.type = OPTR_MINUS; break;   
            default : Error(ERR_UNKNOWN_OPERATOR, __LINE__); return false;   
        }   
        return true;   
    }   
       
    return false; //Error!    
}   
   
bool Calculator::GetVariable(element &EL, const char *buf, int &rank)   
{   
    int j;   
       
    for(j = 0; j < VarCount; j++) {//是否为已知变量    
        if(strcmp(VarName[j], buf) == 0) { //若是变量,则EL为操作数    
            EL.type = 1 + j;   
            EL.isp = 0; EL.icp = 0;   
            rank++; // 操作数的等级为1,累计等级rank自加1    
            if (rank > 1) {   
                Error(ERR_MISS_OPERATOR, __LINE__);   
                return false;   
            }   
            return true;   
        }   
    }   
       
    if (VarCount < MaxNumber_of_Variable) {   
        strcpy(VarName[VarCount], buf); //添加新变量    
        EL.type = 1 + j;   
        EL.isp = 0; EL.icp = 0;   
        VarCount++;   
        rank++;   
        if (rank > 1) {   
            Error(ERR_MISS_OPERATOR, __LINE__);   
            return false;   
        }   
        return true;   
    } else {   
        Error(ERR_TOO_MANY_VARIABLES, __LINE__);   
        return false;   
    }   
}   
   
bool Calculator::GetElement(element &EL, const char *buf, int &rank)   
{ // 得到buf所指的字符串对应的表达式元素的属性    
    static char *fname[]={"SIN", "COS", "TAN", "SQR", "LOG10",    
            "LOG", "COT", "ABS", "INT", "ARCSIN", "ARCCOS", "ARCTAN",   
            "SINH", "COSH", "TANH", "EXP", "SQRT", 0}; //支持的数学函数的名称    
    int l, j;   
    char ch;   
   
    l = strlen(buf);   
    ch = buf[0];   
    if(l == 1 && !isalpha(ch))  //非字母的单字节操作符    
        return GetUnary(EL, ch, rank);   
   
     //处理字母字符串    
    for(j = 0; fname[j] != 0; j++) {//是否为已有的数学函数    
        if(strcmp(fname[j], buf) == 0) {   
            EL.type = 51 + j;   
            EL.isp = 4; EL.icp = 5;   
            return true;   
        }   
    }   
           
    if(GetVariable(EL, buf, rank)) {   
        return true;   
    }   
   
    return false;   
}   
   
bool Calculator::Construe_Numeric(element &EL, int &i, int &rank) const   
{   
    char buf[MaxLength_of_Expression];   
    GetOperand(i, buf);   
    EL.type = 0;   
    EL.value = atof (buf);   
       
    rank++;   
    if (rank > 1) {   
        Error(ERR_MISS_OPERATOR, __LINE__);   
        return false;   
    }   
    return true;   
}   
   
bool Calculator::Construe_Operator(element &EL, int &i, int &rank)   
{   
    char buf[MaxLength_of_VariableName];   
   
    if(!GetOperator(i, buf)) // 取得整个操作符的名称    
        return false; //发生错误    
   
    if(!GetElement(EL, buf, rank)) // 取得相应的属性    
        return false ; //发生错误    
   
    if(EL.type < 40 && EL.type > 20) // 若是双目操作符,rank自减1    
        rank--;   
           
    if (rank < 0) {   
        Error(ERR_MISS_OPERAND, __LINE__);   
        return false;   
    }   
    return true;   
}   
   
void Calculator::Construe(Queue<element> &IN)   
{ // 把输入的表达式整理为中缀表达式    
    element EL;   
   
    char ch;   
    int rank = 0; //表达式等级    
    int i = 0;   
       
    EL.icp = 0; EL.isp = 0; EL.value = 0;   
   
    IN.Clear();   
   
    while((ch = Expression[i]) != '\0') { //扫描表达式    
        if(IsOperandChar(i)) { //处理数字    
            if(!Construe_Numeric(EL, i, rank))   
                return;   
            IN.Insert(EL);   
            continue;   
            }   
           
        if(ch == '(') {   
            EL.type = 20; EL.icp = 6; EL.isp = -1;   
            i++;   
            IN.Insert(EL);   
            continue;   
            }   
           
        if(ch == ')') {   
            EL.type = 40; EL.icp = 0; EL.isp = 0;   
            i++;   
            IN.Insert(EL);   
            continue;   
            }   
           
        if(IsOperatorChar(i)) { //处理操作符    
            if (!Construe_Operator(EL, i, rank))   
                return;   
            IN.Insert(EL);   
            continue;   
        }   
    } // end of while()    
   
    if(rank != 1)    
        Error(ERR_MISS_OPERAND, __LINE__);   
    return;   
}   
   
void Calculator::Conversion(Queue<element> &IN)   
{ //转换中缀表达式为后缀式    
   
    element EL;   
    int type;   
    Stack<element> STE; // Stack to elements    
   
    PO.Clear();   
       
    while(!IN.IsEmpty()) { //依次取出中缀表达式的元素EL    
        EL = IN.Delete();   
        type = EL.type;   
           
        if(type < 20) { // 若是操作数    
            PO.Insert(EL);   
            continue;   
        }   
           
        if(STE.IsEmpty()) { // 栈空时,操作符直接压栈    
            STE.Push(EL);   
            continue;   
        }   
           
        if(type == OPTR_RIGHT_PARENTHESIS) 
		{ // 若为右括号    
            while(!STE.IsEmpty()  
                && STE.Peek().type != OPTR_LEFT_PARENTHESIS)
			{ // 取出左括号之前的操作符    
                EL = STE.Pop();   
                PO.Insert(EL);   
            }   
            if(STE.IsEmpty()) {    
                Error(ERR_MISS_LEFT_PARENTHESIS, __LINE__);   
                return;   
            }   
            STE.Pop(); // 弹出左括号    
            continue;   
        }   
           
        if(STE.Peek().isp < EL.icp) // 栈外优先级高,则直接把EL压栈    
            STE.Push(EL);   
        else { // 否则弹出栈内的优先级比EL.icp高的元素    
            while(!STE.IsEmpty() && STE.Peek().isp >= EL.icp) {   
                PO.Insert(STE.Pop());   
            }   
            STE.Push(EL);   
        }   
    }   
   
    while(!STE.IsEmpty()) { // 栈内剩余的操作符送入中缀表达式PO    
        EL = STE.Pop();   
        if(EL.type == OPTR_LEFT_PARENTHESIS) {   
            Error(ERR_MISS_RIGHT_PARAENTHESIS, __LINE__);   
            return;   
        }   
        PO.Insert(EL);   
    }   
}   
   
bool Calculator::Input(char *exp)   
{   
    Queue<element> IN;   
       
    Clear();   
   
    if (strlen(exp) > MaxLength_of_Expression) {   
        Error(ERR_EXPRESSION_TOO_LONG, __LINE__);   
        return false;   
    }   
   
    Trim(exp); // 去除表达式的非法字符    
       
    Construe(IN); // 整理为中缀表达式    
       
    if(GetErrorID() != ERR_NO_ERROR)   
        return false;   
       
    Conversion(IN); // 转换为后缀表达式    
    return GetErrorID() == 0;   
}   
   
double Calculator::Calculate(element EL, double x, double y) const   
{ // 双目运算符的具体运算    
    int type = EL.type;   
       
    if (type > 20 && type < 40) //处理双目运算    
        switch(type)  { // '+' , '-' , '*' , '/' , '^'    
        case OPTR_ADD : return ( x + y );    
        case OPTR_SUBTRACT : return ( x - y );    
        case OPTR_MULTIPLY : return ( x * y );    
        case OPTR_DIVIDE :    
            if (y == 0.0)    
                Error(ERR_DEVIDE_BY_ZERO, __LINE__);   
            else   
                return ( x / y );   
            break;   
        case OPTR_POWER : return (pow( x, y));   
        default : Error(ERR_INVALID_OPERATOR, __LINE__); return 0.0;   
        }   
    else {   
        Error(ERR_INVALID_OPERATOR, __LINE__);    
        return 0.0;   
    }   
    return 0.0;   
}   
   
double Calculator::Calculate(element EL, double x) const   
{// 单目运算符的具体运算    
    static double (*fun[])(double)={sin, cos, tan, sqrt,    
        log10, log, cot, fabs, floor, asin, acos, atan, sinh,   
        cosh, tanh, exp, sqrt}; //*fname[]对应的C函数名,其中cot为自己写的    
    int type = EL.type;   
   
    if (type > 40) { //处理单目运算    
        switch(type)  {   
        case OPTR_MINUS: return -x;   
        case OPTR_POSITIVE: return  x;   
        }   
        if(type>50) //函数运算    
            return ((*fun[type-51])(x));   
        else {   
            Error(ERR_INVALID_OPERATOR, __LINE__); return 0.0;   
        }   
    }   
    else {   
        Error(ERR_INVALID_OPERATOR, __LINE__); return 0.0;   
    }   
    return 0.0;   
}   
   
   
bool Calculator::Compute(void)   
{ // 后缀表达式求值    
    int i, l, type;   
    double x, y, r;   
    element EL;   
    Stack<double> ST; //Stack to operands    
    Queue<element> postfix(PO); // 将PO复制到postfix    
   
    ST.Clear();   
    l = postfix.GetLength();   
   
    for (i = 0; i < l; i++) { //逆波兰表达式求值    
        EL = postfix.Delete();   
        type = EL.type;   
           
        if (type < 20) { // 操作数直接压栈    
            if (type == 0) // 压入数字    
              ST.Push(EL.value);   
            else // 压入变量    
              ST.Push(Vars[type-1]);   
            continue;   
        }   
   
        if (type > 40) { // 单目操作符    
            x = ST.Pop();   
            r = Calculate(EL, x);   
            ST.Push(r);   
            continue;   
        }   
   
        if (type > 20 && type < 40) { // 双目操作符    
            y = ST.Pop(); x = ST.Pop();   
            r = Calculate(EL, x, y);   
            ST.Push(r);   
            continue;   
        }   
    }   
   
    if(!ST.IsEmpty()) { // 取出最后结果    
        Result = ST.Pop();   
        if (ST.IsEmpty())   
            return true;   
        else {   
            Error(ERR_MISS_OPERATOR, __LINE__);   
            return false;   
        }   
    }   
    else     
        Error(ERR_UNKNOWN_ERROR, __LINE__);   
    return false;   
}   
   
   
void Calculator::Test(void)   
{ // 测试计算器的功能    
/*    int i, nv;   
    int errid;   
    char buf[1000];   
    const char *name;   
    const char *pch;   
    double varsfrom[MaxNumber_of_Variable], var;   
       
    cout << "Input a expression: "<<ENDL; { } return ; ? (nv if nv="GetNumberOfVariables();" <<endl; GetErrorLineNo() ?<< Line ?\nNear << pch="GetErrorMessage(errid);" : ?ERROR endl cout errid="GetErrorID();" if(!Input(buf)) stdin); sizeof(buf), fgets(buf, sizeof(buf)); cin.getline(buf,> 0) {   
        cout << "\nThere seems to be " << nv <<    
            " Variable(s) in your expression, please input them :" << endl;   
        for(i = 0; i < nv; i++) {   
            name = GetVariableName(i);   
            cout << "No." << i + 1 << "  " << name << " = ";   
            cin >> var;   
            varsfrom[i] = var;   
        }   
        Assign(varsfrom);   
    }   
       
    if(!Compute()) {   
        errid = GetErrorID();   
           
        cout << endl << "ERROR : " << GetErrorMessage(errid) << "\nNear Line "<< GetErrorLineNo() << endl;   
        return ;   
    }   
   
    cout << "Answer: " << GetResult() << endl; */  
} 