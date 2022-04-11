#include <iostream>
#include <cassert> // для assert()
#include <vector>
#include <set>


class Array
{
private:
	int k_length;
	int* k_date;

	void swap(int& a, int& b)
	{
		int x = a;
		a = b;
		b = x;
	}
	void k_sort(int first, int last)
	{
		int f = first;
		int l = last;

		int x = k_date[(first + last) / 2];

		do
		{
			while (k_date[f] < x) f++;
			while (k_date[l] > x) l++;

			if (f <= l)
			{
				swap(k_date[f], k_date[l]);
				f++;
				l--;
			}
		} while (f <= l);
		
			if (f < last) k_sort(f, last);
			if (first < f) k_sort(first, l);
		
	}


public:
	Array() : k_length(0), k_date(nullptr){}

	Array(int length) : k_length(length)
	{
		assert(length >= 0);

		if (length > 0)
			k_date = new int[length];
		else
			k_date = nullptr;
	}
	void wipeOf()
	{
		delete[] k_date;

		k_date = nullptr;
		k_length = 0;
	}

	int getLength() { return k_length; }

	void resize(int newLength)
	{
		if (newLength == k_length)
			return;
		if (newLength <= 0) { wipeOf(); return; }

		int* date = new int[newLength];

		if (k_length > 0)
		{
			int elementsCopy = (newLength > k_length) ? k_length : newLength;
			for (int index = 0; index < elementsCopy; ++index)
				date[index] = k_date[index];
		}

		delete[] k_date;

		k_date = date;
		k_length = newLength;
	}

	void insertBefore(int value, int index)
	{
		assert(index >= 0 && index <= k_length);

		int* date = new int[k_length + 1];

		for (int after = index; after < k_length; ++after)
			date[after + 1] = k_date[after];

		delete[] k_date;
		k_date = date;
		++k_length;
	}

	void push_back(int value)
	{
		insertBefore(value, k_length);
	}

	void pop_back()
	{
		if (k_length == 0)
			return;

		resize(k_length - 1 == 0);
	}

	void pop_front()
	{
		if (k_length == 0)
			return;

		if (k_length - 1 == 0)
		{
			wipeOf();
			return;
		}

		int* data = new int[k_length - 1];

		for (int index = 1; index < k_length; ++index)
			data[index - 1] = k_date[index];

		delete[] k_date;
		k_date = data;
		--k_length;
	}

	void sort()
	{
		k_sort(0, k_length - 1);
	}

	~Array()
	{
		delete[] k_date;
	}

	friend std::ostream& operator<<(std::ostream&, Array&);

	int& operator[](int index)
	{
		assert(index >= 0 && index < k_length);

		return k_date[index];
	}
};
std::ostream& operator<<(std::ostream& s, Array& f)
{
	int length = f.getLength();

	for (int i = 0; i < length; ++i)
		s << f[i] << (((length == 1) || (length - 1 == i)) ? "" : ", ");

	return s;
}



int main()
{
	//za_1
	setlocale(LC_ALL, "ru");
	Array array;

	array.push_back(2);
	array.push_back(1);
	array.push_back(3);
	array.push_back(4);
	array.push_back(2);

	std::cout << "Исходный массив: " << array << std::endl;

	array.sort();

	std::cout << "Отсортированный массив: " << array << std::endl;

	array.pop_front();
	array.pop_front();

	std::cout << "После удаления двух первых элементов: " << array << std::endl;

	array.pop_back();
	array.pop_back();

	std::cout << "После удаления двух последних элементов: " << array << std::endl;

	//za_2
	std::vector<int> v = { 1, 5, 2, 2, 6, 7, 3, 1, 9, 2, 3, 5, 8, 4 };
	std::set<int> s(v.begin(), v.end());
	std::cout << s.size() << " различных значений из " << v.size() << std::endl;

	return 0;
}




