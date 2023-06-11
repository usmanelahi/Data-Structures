template<class T>
class Stack {
	T* ptr;
	int cap;
	int top;
public:
	Stack()
	{
		ptr = 0;
		cap = 0;
		top = -1;
	}
	void push(T n)
	{
		if (top == -1)
		{
			ptr = new T[1];
			ptr[++top] = n;
			cap = 1;
		}
		else if (top == cap - 1)
		{
			cap *= 2;
			T* temp = new T[cap];
			for (int i = 0; i <= top; i++)
				temp[i] = ptr[i];
			delete[] ptr;
			ptr = temp;
			ptr[++top] = n;
		}
		else
		{
			ptr[++top] = n;
		}
	}
	void pop()
	{
		if (top != -1)
		{
			if (top != cap / 2)
			{
				top--;
			}
			else
			{
				cap /= 2;
				T* temp = new T[cap];
				for (int i = 0; i < cap; i++)
				{
					temp[i] = ptr[i];
				}
				top--;
				delete[] ptr;
				ptr = temp;
			}
		}
	}
	const T& peek()
	{
		return ptr[top];
	}

	inline bool isEmpty()
	{
		return top == -1;
	}


	void display()
	{
		if (top != -1)
			for (int i = 0; i <= top; i++)
			{
				cout << ptr[i] << " ";
			}
		cout << endl;
	}
};