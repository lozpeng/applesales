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

const int  MaxLength_of_Expression = 500; // ���ʽ����󳤶� 
const int  MaxLength_of_VariableName = 30; // ����������󳤶� 
const int  MaxNumber_of_Variable = 15; // ������������,��С�� 19 
 
enum ERR_TYPE{ 
    ERR_NO_ERROR = 0, 
    ERR_EXPRESSION_TOO_LONG = 1, // ���ʽ̫�� 
    ERR_MISS_OPERAND = 2, // ȱ�ٲ����� 
    ERR_MISS_OPERATOR = 3, // ȱ�ٲ����� 
    ERR_MISS_LEFT_PARENTHESIS = 4, // ȱ������ 
    ERR_MISS_RIGHT_PARAENTHESIS = 5, // ȱ������ 
    ERR_DEVIDE_BY_ZERO = 6, // ����Ϊ�� 
    ERR_UNKNOWN_OPERATOR = 7, // δ֪�Ĳ����� 
    ERR_INVALID_OPERATOR = 8, // �Ƿ������� 
    ERR_UNKNOWN_ERROR = 9, // δ֪�Ĵ��� 
    ERR_TOO_MANY_VARIABLES = 10, // ��������̫�� 
    ERR_VARIABLE_NAME_TOO_LONG = 11 // ������̫�� 
}; 
 
enum OPTR_TYPE{ 
    OPTR_MINUS = 41, // ���� 
    OPTR_POSITIVE = 42, // ���� 
 
    OPTR_ADD = 21, // �ӷ� 
    OPTR_SUBTRACT = 22, // ���� 
    OPTR_MULTIPLY = 23, // �˷� 
    OPTR_DIVIDE = 24, // ���� 
    OPTR_POWER = 25, // �˷� 
 
    OPTR_LEFT_PARENTHESIS = 20, // ������ 
    OPTR_RIGHT_PARENTHESIS = 40 // ������ 
}; 
 
inline double cot(double n) 
{ // ������ 
	return 1.0 / tan(n); 
} 
/* 
int _matherr (struct _exception *a)  
{ //��ѧ������쳣������ͬ�ı�����Ҫ��һ 
	a->retval = 100000.0; 
	return 1; 
} 
*/ 
class Calculator 
{ 
private: 
 
	struct element { 
		int type; // Ԫ�����,�ǲ��������ǲ������ɴ˶� 
		int icp; // ջ�����ȼ� 
		int isp; // ջ�����ȼ� 
		double value; // �������ͨ������(�Ǳ���),��Ϊֵ 
    }; 
 
	Queue<element> PO; // ��׺���ʽ, �洢�ڶ����� 
 
	double Result; // ���ʽ�������� 
	double Vars[MaxNumber_of_Variable]; // ���ʽ�и���������ֵ����ڴ� 
	char VarName[MaxNumber_of_Variable][MaxLength_of_VariableName]; // �������������� 
	char Expression[MaxLength_of_Expression]; // ����ı��ʽ 
	mutable int ErrorID; // ��������Ĵ���ĺ��� 
	mutable int ErrorLineNo; // ��������Ĵ�����к� 
	int  VarCount; // �����ĸ��� 
 
	void Error(int err, int lineno) const {	ErrorID = err; ErrorLineNo = lineno; } // ������� 
 
	// ����Ϊ������ı��ʽת��Ϊ��׺���ʽ��Ԫ���������õĺ��� 
	void Trim(char *); // ��������ı��ʽ,��ȥ�Ƿ��ַ� 
	bool IsOperandChar(int) const; // ��ǰ�ַ��Ƿ�����һ�������� 
	bool IsOperatorChar(int) const; // ��ǰ�ַ��Ƿ�����һ�������� 
	void GetOperand(int &, char *) const; // ȡ��һ��������(������) 
	bool GetOperator(int &, char *) const; // ȡ��һ��������(��ĸ���л�+-*/^����)���ɹ�����true 
    bool GetUnary(element &, char , int) const;  // ���ַ�����ĸ��������Ӧ�����ԣ��ɹ�����true 
    bool GetVariable(element &, const char *, int &); // ���ʽ�г��ֵı��������ԣ��ɹ�����true 
	bool GetElement(element &, const char *, int &); // ȡ���ַ���buf��Ӧ��Ԫ�����ԣ��ɹ�����true 
	bool Construe_Numeric(element &, int &, int &) const; //  
	bool Construe_Operator(element &, int &, int &); 
    void Construe(Queue<element> &); // ��������ʽ����ΪԪ������(����׺���ʽ) 
	 
	// ����׺���ʽת��Ϊ��׺���ʽ 
	void Conversion(Queue<element> &);  
 
	double Calculate(element EL, double x, double y) const; // ˫Ŀ������������ 
	double Calculate(element EL, double x) const; // ��Ŀ������������ 
 
public: //����Ϊ�ӿ� 
 
	Calculator(void) { Clear(); } 
	void Clear(void); // ��ʼ�������� 
	const char* GetErrorMessage(int errid) const; // �õ�������Ϣ 
	int  GetErrorID(void) const { return ErrorID; } // ���ش���ĺ��� 
	int  GetErrorLineNo(void) const { return ErrorLineNo; } // ���ط���������к� 
 
	bool Input(char *); // �����������һ�����ʽ,�ɹ��򷵻�true 
    int  GetNumberOfVariables(void) { return VarCount; } // ���ر��ʽ�еı������� 
    const char* Calculator::GetVariableName(int i); // �õ����ʽ��i������������ 
	void Assign(double *); // ��������ֵ 
	bool Compute(void); // ִ�м���,�ɹ��򷵻�true 
	double GetResult(void) { return Result; }// ���ؼ����� 
	void Test(void); // ��ʾ�����Ĺ��� 
}; 
 
 
#endif  // CALCULATOR_CLASS
