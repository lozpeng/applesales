#ifndef CALCULATOR_CLASS 
#define CALCULATOR_CLASS 
 
//*********************queue class****************************//
const int MaxQueueSize = 1000; 
 
template <class T>
class Queue 
{ 
private: 
	int front, rear, count; 
	T qlist[MaxQueueSize]; // array implementation 
 
public: 
	Queue (void);       // initialize integer data members 
	void Insert(const T& item); 
	T Delete(void); 
	void Clear(void); 
	T GetFront(void) const; 
	int GetLength(void) const; 
	bool IsEmpty(void) const; 
	bool IsFull(void) const; 
}; 
                                   
// initialize queue front, rear, count 
template <class T>
Queue<T>::Queue (void) : front(0), rear(0), count(0) 
{} 
 
// insert item into the queue  
template <class T>
void Queue<T>::Insert (const T& item) 
{ 
    // terminate if queue is full 
    if (count == MaxQueueSize) { 
		//cerr << "Queue overflow!" << endl;
        exit(1); 
    } 
    // increment count, assign item to qlist and update rear 
    count++; 
    qlist[rear] = item; 
    rear = (rear+1) % MaxQueueSize; 
} 
 
// delete element from front of queue and return its value 
template <class T>
T Queue<T>::Delete(void) 
{ 
	 
    // if qlist is empty, terminate the program 
    if (count == 0) 
    { 
        /*//cerr << "Deleting from an empty queue!" << endl; */
        exit(1); 
    } 
 
    // record value at the front of the queue 
    T temp = qlist[front]; 
     
    // decrement count, advance front and return former front 
    count--; 
    front = (front+1) % MaxQueueSize; 
    return temp; 
} 
 
// return value of the first entry  
template <class T>
T Queue<T>::GetFront(void) const 
{ 
    return qlist[front]; 
} 
 
// return number of queue elements 
template <class T> 
inline int Queue<T>::GetLength(void) const 
{ 
    return count; 
} 
 
// test for an empty queue 
template <class T>
inline bool Queue<T>::IsEmpty(void) const 
{ 
    // return the logical value count == 0 
    return count == 0; 
} 
 
// test for a full queue 
template <class T> 
inline bool Queue<T>::IsFull(void) const 
{ 
    // return the logical value count == MaxQSize 
    return count == MaxQSize; 
} 
 
// clear the queue by resetting count, front and rear to 0 
template <class T>
void Queue<T>::Clear(void) 
{ 
    count = 0; 
    front = 0;  
    rear = 0;  
} 
//************************************************************//

//********************stack class ****************************//
const int MaxStackSize = 1000; 
 
template <class T>
class Stack 
{ 
private: 
	// private data members. stack array, and top 
	T stacklist[MaxStackSize]; // array implementation 
	int top; 
	 
public: 
	// constructor; initialize the top 
	Stack (void); 
 
	// stack modification operations 
	void Push (const T& item); 
	T Pop (void); 
	void Clear(void); 
 
	// stack access 
	T Peek (void) const; 
 
	// stack test methods 
	int IsEmpty(void) const; 
	int IsFull(void) const; 
}; 
 
// initialize stack top. 
template <class T> 
Stack<T>::Stack (void) : top(-1) 
{} 
 
// push item on the the stack 
template <class T>
void Stack<T>::Push (const T& item) 
{ 
    // if stacklist is full, terminate the program 
    if (top == MaxStackSize - 1) { 
		/*//cerr << "Stack overflow!" << endl; */
		exit(1); 
    } 
 
    // increment top and copy item to stacklist 
    top++; 
    stacklist[top] = item; 
} 
 
// pop the stack and return the top element 
template <class T>
T Stack<T>::Pop (void) 
{ 
 
    // if stack is empty, terminate the program 
    if (top == -1) { 
		/*//cerr << "Attempt to pop an empty stack!" << endl;*/ 
		exit(1); 
    } 
 
    // record the top element 
    T temp = stacklist[top]; 
 
    // decrement top and return former top element 
    top--; 
    return temp; 
} 
 
// return the value at the top of the stack 
template <class T>
T Stack<T>::Peek (void) const 
{ 
    // if the stack is empty, terminate the program 
    if (top == -1) { 
		////cerr << "Attempt to peek at an empty stack!" << endl; 
		exit(1); 
    } 
    return stacklist[top]; 
} 
 
 
// test for an empty stack 
template <class T> 
inline int Stack<T>::IsEmpty(void) const 
{ 
    // return the logical value top == -1 
   return top == -1; 
} 
 
// test for a full stack 
template <class T>
inline int Stack<T>::IsFull(void) const 
{ 
   // test the position of top 
   return top == MaxStackSize - 1; 
} 
 
// clear all items from the stack 
template <class T> 
inline void Stack<T>::Clear(void) 
{ 
    top = -1; 
} 
//************************************************************//

 #include <math.h> 

const int  MaxLength_of_Expression = 500; // 表达式的最大长度 
const int  MaxLength_of_VariableName = 30; // 变量名的最大长度 
const int  MaxNumber_of_Variable = 15; // 变量的最大个数,需小于 19 
 
enum ERR_TYPE{ 
    ERR_NO_ERROR = 0, 
    ERR_EXPRESSION_TOO_LONG = 1, // 表达式太长 
    ERR_MISS_OPERAND = 2, // 缺少操作数 
    ERR_MISS_OPERATOR = 3, // 缺少操作符 
    ERR_MISS_LEFT_PARENTHESIS = 4, // 缺左括号 
    ERR_MISS_RIGHT_PARAENTHESIS = 5, // 缺右括号 
    ERR_DEVIDE_BY_ZERO = 6, // 除数为零 
    ERR_UNKNOWN_OPERATOR = 7, // 未知的操作符 
    ERR_INVALID_OPERATOR = 8, // 非法操作符 
    ERR_UNKNOWN_ERROR = 9, // 未知的错误 
    ERR_TOO_MANY_VARIABLES = 10, // 变量个数太多 
    ERR_VARIABLE_NAME_TOO_LONG = 11 // 变量名太长 
}; 
 
enum OPTR_TYPE{ 
    OPTR_MINUS = 41, // 负号 
    OPTR_POSITIVE = 42, // 正号 
 
    OPTR_ADD = 21, // 加法 
    OPTR_SUBTRACT = 22, // 减法 
    OPTR_MULTIPLY = 23, // 乘法 
    OPTR_DIVIDE = 24, // 除法 
    OPTR_POWER = 25, // 乘方 
 
    OPTR_LEFT_PARENTHESIS = 20, // 左括号 
    OPTR_RIGHT_PARENTHESIS = 40 // 右括号 
}; 
 
inline double cot(double n) 
{ // 反正切 
	return 1.0 / tan(n); 
} 
/* 
int _matherr (struct _exception *a)  
{ //数学运算的异常处理，不同的编译器要求不一 
	a->retval = 100000.0; 
	return 1; 
} 
*/ 
class Calculator 
{ 
private: 
 
	struct element { 
		int type; // 元素类别,是操作数还是操作符由此定 
		int icp; // 栈外优先级 
		int isp; // 栈内优先级 
		double value; // 如果是普通操作数(非变量),此为值 
    }; 
 
	Queue<element> PO; // 后缀表达式, 存储在队列中 
 
	double Result; // 表达式的运算结果 
	double Vars[MaxNumber_of_Variable]; // 表达式中各个变量的值存放于此 
	char VarName[MaxNumber_of_Variable][MaxLength_of_VariableName]; // 各个变量的名字 
	char Expression[MaxLength_of_Expression]; // 输入的表达式 
	mutable int ErrorID; // 最近发生的错误的号码 
	mutable int ErrorLineNo; // 最近发生的错误的行号 
	int  VarCount; // 变量的个数 
 
	void Error(int err, int lineno) const {	ErrorID = err; ErrorLineNo = lineno; } // 处理错误 
 
	// 以下为将输入的表达式转换为中缀表达式的元素序列所用的函数 
	void Trim(char *); // 整理输入的表达式,除去非法字符 
	bool IsOperandChar(int) const; // 当前字符是否属于一个操作数 
	bool IsOperatorChar(int) const; // 当前字符是否属于一个操作符 
	void GetOperand(int &, char *) const; // 取得一个操作数(纯数字) 
	bool GetOperator(int &, char *) const; // 取得一个操作符(字母序列或“+-*/^”等)，成功返回true 
    bool GetUnary(element &, char , int) const;  // 单字符非字母操作符对应的属性，成功返回true 
    bool GetVariable(element &, const char *, int &); // 表达式中出现的变量的属性，成功返回true 
	bool GetElement(element &, const char *, int &); // 取得字符串buf对应的元素属性，成功返回true 
	bool Construe_Numeric(element &, int &, int &) const; //  
	bool Construe_Operator(element &, int &, int &); 
    void Construe(Queue<element> &); // 将输入表达式整理为元素序列(即中缀表达式) 
	 
	// 将中缀表达式转换为后缀表达式 
	void Conversion(Queue<element> &);  
 
	double Calculate(element EL, double x, double y) const; // 双目操作符的运算 
	double Calculate(element EL, double x) const; // 单目操作符的运算 
 
public: //以下为接口 
 
	Calculator(void) { Clear(); } 
	void Clear(void); // 初始化计算器 
	const char* GetErrorMessage(int errid) const; // 得到错误信息 
	int  GetErrorID(void) const { return ErrorID; } // 返回错误的号码 
	int  GetErrorLineNo(void) const { return ErrorLineNo; } // 返回发生错误的行号 
 
	bool Input(char *); // 向计算器输入一个表达式,成功则返回true 
    int  GetNumberOfVariables(void) { return VarCount; } // 返回表达式中的变量个数 
    const char* Calculator::GetVariableName(int i); // 得到表达式第i个变量的名称 
	void Assign(double *); // 给变量赋值 
	bool Compute(void); // 执行计算,成功则返回true 
	double GetResult(void) { return Result; }// 返回计算结果 
	void Test(void); // 演示基本的功能 
}; 
 
 
#endif  // CALCULATOR_CLASS
