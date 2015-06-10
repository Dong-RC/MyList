#include<iostream>
using namespace std;

template<class T>
class MyList{
private:
	T *a;
	int size;
	int top;
	void double_space()
	{
		T *tmp = new T[2 * size];
		for (int i = 0; i <= top; ++i) tmp[i] = a[i];
		delete []a;
		a = new T[2 * size];
		for (int i = 0; i <= top; ++i) a[i] = tmp[i];
		size *= 2;
	}
public:
	MyList()
	{
		size = 100;
		a = new T[size];
		top = -1;
	}
	
	MyList(int num, const T &item)
	{
		size = 2 * num;
		a = new T[size];
		top = -1;
		for (int i = 0; i < num; ++i) 
		{
			a[i] = item;
			++top;
		}
	}
		
	MyList(const MyList &l)
	{
		size = l.size;
		a = new T[size];
		top = -1;
		for (int i = 0; i < l.top; ++i)
		{
			a[i] = l.a[i];
			++top;
		}
	}
	
    MyList(T* arr, int len)
    {
    	size = 2 * len;
    	a = new int[size];
    	top = -1;
    	for (int i = 0; i < len; ++i)
		{
			a[i] = arr[i];
			++top;
		}
	}

	void push(const T &item)
	{
		if (top + 1 == size) this->double_space();
		a[top + 1] = item;
		++top;
	}
	
	T pop()
	{ 
		try
		{
			if (top == -1) throw long("!"); 
			T del_ele;
			del_ele = a[top];
			top--;
			return del_ele;
		}
		catch (long)
		{
			cout << endl;
			cout << "The list is empty" << endl;
		}
	}

	void insert(int index, const T &item)
	{
		try
		{
			if (top + 1 == size) this->double_space();
			if (index < 0) index = top + index + 1;
			if (index < 0 || index > top) throw int(1);
			for (int i = top; i >= index; --i) a[i + 1] = a[i];
			a[index] = item;
			++top;
		}
		catch (int)
		{
			cout << endl;
			cout << "The index is wrong" << endl;
		}
	}
	
	void clean()
	{
		top = -1;
	}
	
	int get_size()
	{
		return top + 1;
	}
	
	void erase(int start, int end)
	{
		try
		{
			T *tmp = new T[size];
			if (start < 0) start = top + 1 + start;
			if (end < 0) end = top + 1 + end;
			if (start > end || end > top || start < 0) throw int(1);
			for (int i = end + 1; i <= top; ++i) tmp[i - end - 1] = a[i]; 
			for (int i = 0; i < top - end; ++i) a[i + start] = tmp[i];
			top -= end - start + 1;
		}
		catch (int)
		{
			cout << endl;
			cout << "The index is wrong" << endl;
			throw int(1);
		}
	}
	
	T get_item(int index)
	{
		try
		{
			if (index < 0) index = top + index + 1;
			if (index < 0 || index > top) throw int(1);
			return a[index];
		}
		catch (int)
		{
			cout << endl;
			cout << "The index is wrong" << endl;
			throw int(1);
		}
	}
	
	MyList get_item(int start, int end)
	{
		try
		{
			MyList b;
			b.size = size;
			b.a = new T[size];
			if (start < 0) start = top + 1 + start;
			if (end < 0) end = top + 1 + end;
			if (end > top || start < 0) throw long("!");
			if (start > end)
			{
				b.top = -1;
				return b;
			}
			b.top = end - start; 
			for (int i = start; i <= end; ++i) b.a[i - start] = a[i];
			return b;
		}
		catch (long)
		{
			cout << endl;
			cout << "The index is wrong" << endl;
		}
	}
	
	int count(const T &item)
	{
		int n = 0;
		for (int i = 0; i <= top; ++i)
			if (a[i] == item)
				++n;
		return n;
	}
	
	void remove(const T &item)
	{
		for (int i = 0; i <= top; ++i)
			if (a[i] == item)
			{
				for (int j = i; j < top; ++j) a[j] = a[j + 1];
				--top;
				break;
			}
	}


	friend MyList operator + (const MyList &l1, const MyList &l2)
	{
		MyList sum;
		sum.size = 2 * (l1.top + l2.top + 1);
		sum.top = l1.top + l2.top + 1;
		sum.a = new T[sum.size];
		for (int i = 0; i <= l1.top; ++i) sum.a[i] = l1.a[i];
		for (int i = 0; i <= l2.top; ++i) sum.a[i + l1.top + 1] = l2.a[i];
		return sum;
	}
		
    friend MyList operator + (const MyList &l1, const T &item)
    {
    	MyList sum;
    	sum.size = 2 * (l1.top + 1);
    	sum.top = l1.top + 1;
    	sum.a = new T[sum.size];
    	for (int i = 0; i <= l1.top; ++i) sum.a[i] = l1.a[i];
    	sum.a[l1.top + 1] = item;
    	return sum;
	}
	
	MyList &operator = (const MyList &l)
	{
		if (this == &l) return *this;
		delete [] a;

		size = l.size;
		top = l.top;
		a = new T[size];
		for (int i = 0; i <= l.top; ++i) a[i] = l.a[i];
		return *this;
	}
	
	MyList &operator += (const T &item)
	{
    	a[top + 1] = item;
		++top; 
    	return *this;
	}
	
	MyList &operator += (const MyList &l)
	{
		for (int i = 0; i <= l.top; ++i) a[top + i + 1] = l.a[i];
		top += l.top + 1;
		return *this;
	}
	
	T &operator [](int index)
	{
		try
		{
			if (index < 0) index = top + 1 + index;
			if (index < 0 || index > top) throw int(1);
			return a[index];
		}
		catch (int)
		{
			cout << endl;
			cout << "The index is wrong" << endl;
		}
	}
	
	friend ostream & operator<<(ostream &os, const MyList &obj)
    {
    	if (obj.top >= 0)
    	{
    		os << "[";
			for (int i = 0; i < obj.top; ++i) os << obj.a[i] << ", ";
			os << obj.a[obj.top] << "]";
	    	return os;
		}
    	else os << "[]";
	}

    void quicksort(int *a, int low, int high)
	{
		int mid;
		if (low >= high) return;
		else
	    {        
	        int mid = low, j = high, x = a[low];  
	        while (mid < j)  
	        {  
	            while(mid < j && a[j]>= x)
	                j--;   
	            if(mid < j)  
	                a[mid++] = a[j];  
	            while(mid < j && a[mid]< x)
	                mid++;   
	            if(mid < j)  
	                a[j--] = a[mid];  
	        }  
	        a[mid] = x;  
	
			quicksort(a, low, mid - 1);
			quicksort(a, mid + 1, high);
		}
	}
    
	void reverse()
	{
		T *tmp = new T[size];
		for (int i = 0; i <= top; ++i) tmp[i] = a[top - i];
		for (int i = 0; i <= top; ++i) a[i] = tmp[i];
	}
	
	void sort(bool less=true)
    {
    	quicksort(a, 0, top);
    	if (less != true)
    	{
    		T *tmp = new T[size];
			for (int i = 0; i <= top; ++i) tmp[i] = a[top - i];
			for (int i = 0; i <= top; ++i) a[i] = tmp[i];
		}
	}
	
	~MyList(){delete [] a;}
};


int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);

	a[3] = 15;
	a.sort();
	a.reverse();
	a += 12;
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3);
	b = a.get_item(3, -1);
	a += b;
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean();
	cout<<b.get_size()<<endl;
	a.erase(2, 5);
	b = a + a;
	b.insert(3, 116);
	b.remove(4);
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}
