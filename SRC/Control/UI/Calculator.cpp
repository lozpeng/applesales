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
{ // ��ʼ��������    
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
{ // ��pExtVars��ָ�������ֵ����Vars[]    
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
{ // �����ַ�����ĸ������    
    if(rank == 1) { // ��Ҫ˫Ŀ������    
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
       
    if(rank == 0) { // ��Ҫ��Ŀ������    
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
       
    for(j = 0; j < VarCount; j++) {//�Ƿ�Ϊ��֪����    
        if(strcmp(VarName[j], buf) == 0) { //���Ǳ���,��ELΪ������    
            EL.type = 1 + j;   
            EL.isp = 0; EL.icp = 0;   
            rank++; // �������ĵȼ�Ϊ1,�ۼƵȼ�rank�Լ�1    
            if (rank > 1) {   
                Error(ERR_MISS_OPERATOR, __LINE__);   
                return false;   
            }   
            return true;   
        }   
    }   
       
    if (VarCount < MaxNumber_of_Variable) {   
        strcpy(VarName[VarCount], buf); //����±���    
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
{ // �õ�buf��ָ���ַ�����Ӧ�ı��ʽԪ�ص�����    
    static char *fname[]={"SIN", "COS", "TAN", "SQR", "LOG10",    
            "LOG", "COT", "ABS", "INT", "ARCSIN", "ARCCOS", "ARCTAN",   
            "SINH", "COSH", "TANH", "EXP", "SQRT", 0}; //֧�ֵ���ѧ����������    
    int l, j;   
    char ch;   
   
    l = strlen(buf);   
    ch = buf[0];   
    if(l == 1 && !isalpha(ch))  //����ĸ�ĵ��ֽڲ�����    
        return GetUnary(EL, ch, rank);   
   
     //������ĸ�ַ���    
    for(j = 0; fname[j] != 0; j++) {//�Ƿ�Ϊ���е���ѧ����    
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
   
    if(!GetOperator(i, buf)) // ȡ������������������    
        return false; //��������    
   
    if(!GetElement(EL, buf, rank)) // ȡ����Ӧ������    
        return false ; //��������    
   
    if(EL.type < 40 && EL.type > 20) // ����˫Ŀ������,rank�Լ�1    
        rank--;   
           
    if (rank < 0) {   
        Error(ERR_MISS_OPERAND, __LINE__);   
        return false;   
    }   
    return true;   
}   
   
void Calculator::Construe(Queue<element> &IN)   
{ // ������ı��ʽ����Ϊ��׺���ʽ    
    element EL;   
   
    char ch;   
    int rank = 0; //���ʽ�ȼ�    
    int i = 0;   
       
    EL.icp = 0; EL.isp = 0; EL.value = 0;   
   
    IN.Clear();   
   
    while((ch = Expression[i]) != '\0') { //ɨ����ʽ    
        if(IsOperandChar(i)) { //��������    
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
           
        if(IsOperatorChar(i)) { //���������    
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
{ //ת����׺���ʽΪ��׺ʽ    
   
    element EL;   
    int type;   
    Stack<element> STE; // Stack to elements    
   
    PO.Clear();   
       
    while(!IN.IsEmpty()) { //����ȡ����׺���ʽ��Ԫ��EL    
        EL = IN.Delete();   
        type = EL.type;   
           
        if(type < 20) { // ���ǲ�����    
            PO.Insert(EL);   
            continue;   
        }   
           
        if(STE.IsEmpty()) { // ջ��ʱ,������ֱ��ѹջ    
            STE.Push(EL);   
            continue;   
        }   
           
        if(type == OPTR_RIGHT_PARENTHESIS) 
		{ // ��Ϊ������    
            while(!STE.IsEmpty()  
                && STE.Peek().type != OPTR_LEFT_PARENTHESIS)
			{ // ȡ��������֮ǰ�Ĳ�����    
                EL = STE.Pop();   
                PO.Insert(EL);   
            }   
            if(STE.IsEmpty()) {    
                Error(ERR_MISS_LEFT_PARENTHESIS, __LINE__);   
                return;   
            }   
            STE.Pop(); // ����������    
            continue;   
        }   
           
        if(STE.Peek().isp < EL.icp) // ջ�����ȼ���,��ֱ�Ӱ�ELѹջ    
            STE.Push(EL);   
        else { // ���򵯳�ջ�ڵ����ȼ���EL.icp�ߵ�Ԫ��    
            while(!STE.IsEmpty() && STE.Peek().isp >= EL.icp) {   
                PO.Insert(STE.Pop());   
            }   
            STE.Push(EL);   
        }   
    }   
   
    while(!STE.IsEmpty()) { // ջ��ʣ��Ĳ�����������׺���ʽPO    
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
   
    Trim(exp); // ȥ�����ʽ�ķǷ��ַ�    
       
    Construe(IN); // ����Ϊ��׺���ʽ    
       
    if(GetErrorID() != ERR_NO_ERROR)   
        return false;   
       
    Conversion(IN); // ת��Ϊ��׺���ʽ    
    return GetErrorID() == 0;   
}   
   
double Calculator::Calculate(element EL, double x, double y) const   
{ // ˫Ŀ������ľ�������    
    int type = EL.type;   
       
    if (type > 20 && type < 40) //����˫Ŀ����    
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
{// ��Ŀ������ľ�������    
    static double (*fun[])(double)={sin, cos, tan, sqrt,    
        log10, log, cot, fabs, floor, asin, acos, atan, sinh,   
        cosh, tanh, exp, sqrt}; //*fname[]��Ӧ��C������,����cotΪ�Լ�д��    
    int type = EL.type;   
   
    if (type > 40) { //����Ŀ����    
        switch(type)  {   
        case OPTR_MINUS: return -x;   
        case OPTR_POSITIVE: return  x;   
        }   
        if(type>50) //��������    
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
{ // ��׺���ʽ��ֵ    
    int i, l, type;   
    double x, y, r;   
    element EL;   
    Stack<double> ST; //Stack to operands    
    Queue<element> postfix(PO); // ��PO���Ƶ�postfix    
   
    ST.Clear();   
    l = postfix.GetLength();   
   
    for (i = 0; i < l; i++) { //�沨�����ʽ��ֵ    
        EL = postfix.Delete();   
        type = EL.type;   
           
        if (type < 20) { // ������ֱ��ѹջ    
            if (type == 0) // ѹ������    
              ST.Push(EL.value);   
            else // ѹ�����    
              ST.Push(Vars[type-1]);   
            continue;   
        }   
   
        if (type > 40) { // ��Ŀ������    
            x = ST.Pop();   
            r = Calculate(EL, x);   
            ST.Push(r);   
            continue;   
        }   
   
        if (type > 20 && type < 40) { // ˫Ŀ������    
            y = ST.Pop(); x = ST.Pop();   
            r = Calculate(EL, x, y);   
            ST.Push(r);   
            continue;   
        }   
    }   
   
    if(!ST.IsEmpty()) { // ȡ�������    
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
{ // ���Լ������Ĺ���    
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