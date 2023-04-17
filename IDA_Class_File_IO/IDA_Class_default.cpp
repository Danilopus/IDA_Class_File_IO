#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <algorithm>

#include <fstream>


//#include <array>

// Service functions prototypes ------------------------------------
int Get_Int_SA();				// String-analysis вариант фильтра INTEGER
int Get_Int_Positive();			// String-Analysis вариант проверки ввода INTEGER_POSITIVE		
int Get_Int_PG();				// peek&get вариант проверки ввода INTEGER	
double Get_Dbl_SA();		// String-analysis вариант фильтра DOUBLE.
double Get_Dbl_Positive();	// String-analysis вариант фильтра DOUBLE_POSITIVE
double Get_Dbl_PG();		// peek&get вариант проверки ввода DOUBLE	
int Get_Random(int Range_min, int Range_max);
double Get_Random(double Range_min, double Range_max);
template <typename ANY> void Fill_Array_with_Random(ANY arr[], int Size, ANY Range_min, ANY Range_max);
template <typename ANY> void Array_Console_Out(ANY arr[], int Size);

// Classwork 17.04.2023 ----------------------------------------------------	

//#include <fstream> - для работы с файловой системой компьютера через С++

//Классы библиотеки:
	// ofstream (ввод в файл)
	// ifstream (чтение из файла)
	// fstream (ввод + чтение из файла)


//Task 1. Работа с ofstream для записи в файл
void Task_1()
{
	std::string File_Path = "file.txt"; // относительный путь, лежит там где проект (или исполняемый файл)

	//std::ofstream out_file_stream(File_Path); объект класса ofstream, позволяет открывать файлы для добавления данных
	std::ofstream out_file_stream;
	out_file_stream.open(File_Path, std::ios::app); //Если файла нет - то он будет создан. Когда файл открыт - друни программы не могут с ним работать


	if (out_file_stream.is_open()) //проерка на открытие
	{
		std::cout << "Файл открыт для записи\n";
		std::cout << "Ввеите строку\n";
		std::string str;
		std::getline(std::cin, str);
		//system("chcp 1251");
		out_file_stream << str << '\n'; // добавление текста в файл
		//system("chcp 866");
		std::cout << "Запись добавлена в файл\n";

	}
	else std::cout << "Ошибка открытия файла\n";

	out_file_stream.close(); //закрываем файл после работы и очистка объекта ofstream
	 
	// Возможные причины ошибки открытия файла:
		//1 файл открыт другим приложением
		//2 некорректный путь к файлу
		//3 нет доступа

}

//Task 2. ifstream
void Task_2()
{
	std::string File_Path = "file.txt"; // относительный путь, лежит там где проект (или исполняемый файл)

	std::ifstream in_file_stream;
	in_file_stream.open(File_Path);

	// ios::in - режим по умолчанию, единственный рабочий

	if (in_file_stream.is_open())
	{
		std::cout << "файл открыт для считывания\n";
		
		
		std::cout <<"\n" << File_Path << ":\n\n";
		
		

		//1 way: посимвольное считывание
		/*
		char sybmbol;
		std::string file_content;
		while (in_file_stream.get(sybmbol))			
		{
			file_content += sybmbol;
			//std::cout << sybmbol;			
		}
		std::cout << file_content;
		*/
		
		//2: пословное считывание // EOF считывание
		/*
		std::string str_tmp;
		std::string file_content_2;
		while (!in_file_stream.eof())
		{
			str_tmp = "";
			in_file_stream >> str_tmp;
			file_content_2 += str_tmp + "\n";
			//file_content_2 += str_tmp + " ";

		}
		std::cout << file_content_2;
		*/


		//3: Построчное считывание
		std::string str_tmp_3;
		std::string file_content_3;
		while (std::getline(in_file_stream, str_tmp_3))
			file_content_3 += str_tmp_3+ '\n';
		std::cout << file_content_3;



	}
	else std::cout << "Error opening file for reading";

	//Ошибки при открытии на чтение
		//1 открыт другим приложением или объектом
		//2 неправильный синтаксис пути
		//3 нет доступа
		//4 файла не существует




	in_file_stream.close();
}

// MAIN ------- MAIN ------- MAIN ------- MAIN ------- MAIN --------
int main()
{
	setlocale(LC_ALL,"Rus");
	//Task_1();
	Task_2();



	
	std::cout << "\n\n";
	system("pause");
	//_getch();
	return 0;
}

// Service functions -----------------------------------------
int Get_Int_SA() {
	std::string a;
	std::cin.sync(); 
	std::cin.clear(); 
	getline(std::cin, a);
	if (a != "")
	{

		if ((a.find_first_not_of("-0123456789") == -1))
		{
			for (int i = 1; i < a.size(); i++) // определяем есть ли минусы кроме первого символа
			{
				if (a[i] == '-') 
				{
					std::cout << "Input Error: Minus misstanding. [INTEGER] expected.\n";
					return Get_Int_SA();
				}
			}
			try
			{
				return stoi(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Input Error: Data type overflow. [INTEGER] expected.\n";
				return Get_Int_SA();
			}


		}
		else
		{
			std::cout << "Input Error: Incorrect symbol. [INTEGER] expected.\n";
			return Get_Int_SA();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input. [INTEGER] expected.\n";
		return Get_Int_SA();
	}
}
int Get_Int_Positive()
{
	std::string a;
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "") 
	{

		if ((a.find_first_not_of("0123456789") == -1))
		{
			try{
				return stoi(a);
			}
			catch (std::out_of_range){
				std::cout << "Input Error: overflow. Positive [INTEGER] expected.\n";
			}
		}
		else
		{
			std::cout << "Input Error: Positive [INTEGER] expected.\n";
			return Get_Int_Positive();
		}		
	}
	else
		std::cout << "Input Error: NULL input. Positive [INTEGER] expected.\n";
	return Get_Int_Positive();
}
int Get_Int_PG()
{
	int a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! [INTEGER] expected. Repeat please...\n";
	}
	return a;
}
double Get_Dbl_SA(){
	std::string a;
	std::cin.sync();
	getline(std::cin, a);
	if (a == "") { std::cout << "\nInput Error : NULL input\n"; return Get_Dbl_SA(); }
	if ((a.find_first_not_of("-.0123456789") == -1))
	{
		for (int i = 1; i < a.size(); i++) // Проверяем отсутсвие лишних минусов
		{
			if (a[i] == '-')
			{
				std::cout << "\nInput Error: Minus misstanding. [DOUBLE] expected.\n";
				return Get_Dbl_SA();
			}

		}
		bool Dot_Flag = 0;
		for (int i = 0; i < a.size(); i++) // проверяем отсутсвие лишних точек
		{
			if (a[i] == '.')
			{
				if (Dot_Flag == 1)
				{
					std::cout << "\nInput Error: Dot misstandig. [DOUBLE] expected.\n";
					return Get_Dbl_SA();
				}
				Dot_Flag = 1;
			}

		}		 	
				try{
					return stod(a);
				}
				catch (std::out_of_range) {
					std::cout << "Input Error: overflow. [DOUBLE] expected.\n";
					return Get_Dbl_SA();					
				}						
	}
	else {		
		std::cout << "Incorrect symbols: [DOUBLE] expected.\nUse dot instead of coma. Example 50.64\n";
		return Get_Dbl_SA();
	}
}
double Get_Dbl_Positive(){
	std::string a, dot = ".";
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "")
	{
		if ((a.find_first_not_of(".0123456789") == -1))
		{
			bool One_Dot_already = false;
			for (int i = 0; i < a.size(); i++)
			{				
				if (a[i] == dot[0] && One_Dot_already == true) //проверяем количество разделителей
				{
					std::cout << "Input Error: Dot misstandig. Positive [DOUBLE] expected.\n";
					return Get_Dbl_Positive();
				}
				if (a[i] == dot[0])	One_Dot_already = true;
			}
			try
			{				
				return stod(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Input Error: Data type overflow. Positive [DOUBLE] expected.\n";
				return Get_Dbl_Positive();
			}
		}
		else
		{
			//std::cout << "Incorrect symbols: positive REAL expected.\nUse coma instead of dot. Example 50,64\n"; // да точно говорю вот даже сообщение такое было, а теперь наоборот wtf*2?!
			std::cout << "Incorrect symbols: Positive [DOUBLE] expected.\nUse dot instead of coma. Example 50.64\n";
			return Get_Dbl_Positive();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input. Positive [DOUBLE] expected.\n";
		return Get_Dbl_Positive();
	}
	return Get_Dbl_Positive();
}
double Get_Dbl_PG()
{
	double a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! [DOUBLE] expected. Repeat please...\n";
	}
	return a;
}
int Get_Random(int Range_min=-999, int Range_max=999)
{
	if (Range_min > Range_max) 
	{ 
		std::cout << "\nError: Range_min > Range_max. New range: [Range_max..Range_min]\n";
		std::swap(Range_min, Range_max);
	}
	//return (Range_min + rand() % (Range_max - Range_min + 1));
	double K_random = double((rand() % RAND_MAX)) / RAND_MAX;
	int random = Range_min + ((Range_max - Range_min) * K_random);
	//return Range_min + (Range_max - Range_min) * (rand() % RAND_MAX) / RAND_MAX;
	return random;
}
double Get_Random(double Range_min=-9999.0, double Range_max=9999.0)
{
	if (Range_min > Range_max)
	{
		std::cout << "\nError: Range_min > Range_max. New range: [Range_max..Range_min]\n";
		std::swap(Range_min, Range_max);
	}
	return 	Range_min + (Range_max - Range_min) * double(rand() % RAND_MAX) / RAND_MAX;	
}
template <typename ANY> void Array_Console_Out(ANY arr[], int Size)
{
	std::cout << "\n[";
	for (int i = 0; i < Size; i++)
		std::cout << arr[i] << ", ";
	std::cout << "\b\b]\n";
}
template <typename ANY> void Fill_Array_with_Random(ANY arr[], int Size, ANY Range_min, ANY Range_max)
{
	for (int i = 0; i < Size; i++)
	{
		arr[i] = Get_Random(Range_min, Range_max);		
	}
}