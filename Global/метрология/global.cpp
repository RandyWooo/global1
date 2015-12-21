//metric: Global variables;
//programming language: Ruby;
#include <windows.h>
#include <stdio.h>
#include <string.h>
#define N 100

int main()
{
	struct globalVariables 
	{
	   char element[10];
	};

	char string_from_a_file[170];
	char string_for_parameters[170];
	char braсket[2] = "(";
	char dollarSymbol[2] = "$";
	char emptyString[2] = " ";
	char procedure[4] = "def";
	char *pointer_in_a_string;
	//char comment[2] = "#";
	int counter_parameters_for_the_cycle = 0;
	int number_of_string_in_the_code = 0;
	int number_of_parameters = 0;
	int distance_between_parameters = 0;
	int stringNumber = 0;
	int stringLength = 0;
	int position_of_the_file_pointer = 0;
	int practicalManipulation = 0;
	int number_of_procedure = 0;
	float result;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	struct globalVariables parameters[N];

	FILE *Ruby;
	Ruby = fopen("Ruby.txt","rt");
	while(!feof(Ruby))
	{
		fgets(string_from_a_file, 30, Ruby);
		number_of_string_in_the_code++;
	}
	fclose(Ruby);
	
	Ruby = fopen("Ruby.txt","rt");

//Кол-во обращений к глобальным переменным 
	while(!feof(Ruby))
	{
		fgets(string_from_a_file, 30, Ruby);
		stringLength = strlen(string_from_a_file);
		
		for(int i = 0; i < stringLength; i++)
		{
			if((string_from_a_file[i] == '#'))
			{
				 memmove(string_from_a_file, string_from_a_file + 30, 30);
			}
		}	

		for(int i = 0; i < stringLength; i++)
		{
			if((string_from_a_file[i] == '=') && (string_from_a_file[i+1] == 'b') && (string_from_a_file[i+2] == 'e') && (string_from_a_file[i+3] == 'g') && (string_from_a_file[i+4] == 'i') && (string_from_a_file[i+5] == 'n'))
			{
				 while((string_from_a_file[i] != '=') && (string_from_a_file[i+1] != 'e') && (string_from_a_file[i+2] != 'n') && (string_from_a_file[i+3] != 'd'))
					 memmove(string_from_a_file, string_from_a_file + 30, 30);
			}
		}

		for(int i = 0; i < stringLength; i++)
		{
			if((string_from_a_file[i] == '$') && (string_from_a_file[i+1] != ' '))
			{
				practicalManipulation++;
			}
		}

		pointer_in_a_string = strstr(string_from_a_file, procedure);
		if(pointer_in_a_string != NULL)
		{
			pointer_in_a_string = strstr(string_from_a_file, braсket);
			if(pointer_in_a_string != NULL)
			{
				for(int p = pointer_in_a_string-string_from_a_file+2; p < stringLength; p++)
				{
					if(string_from_a_file[p] == ',')
					{
						practicalManipulation--;
					}
				}
				number_of_procedure++;
				practicalManipulation--;
				
			}
		}
	}
	fclose(Ruby);

	for(int count = 0; count < number_of_string_in_the_code; count++)
	{
		Ruby = fopen("Ruby.txt", "rt");
		for(int povtor = 0; povtor <= stringNumber; povtor++)
		{
			fgets(string_for_parameters, 30, Ruby);
			stringLength = stringLength + strlen(string_for_parameters) + 1;
		}
		fclose(Ruby);

		stringLength = stringLength - strlen(string_for_parameters);
		
		pointer_in_a_string = strstr(string_for_parameters, procedure);
		if(pointer_in_a_string != NULL)
		{
			pointer_in_a_string = strstr(string_for_parameters, braсket);
			if(pointer_in_a_string != NULL)
			{
				for(int x = 0; x < 2; x++)
				{
					Ruby = fopen("Ruby.txt", "rt");
					
					if(stringNumber > 0)
					{
						if(x > 0)
						{						
							position_of_the_file_pointer = position_of_the_file_pointer + distance_between_parameters + 2; 
						}
						else
						{
							position_of_the_file_pointer = stringLength + pointer_in_a_string-string_for_parameters+1;
						}
					}
					else
					{
						if(x > 0)
						{
							position_of_the_file_pointer = position_of_the_file_pointer + distance_between_parameters + 2; 
						}
						else
						{
							position_of_the_file_pointer = pointer_in_a_string-string_for_parameters+2;
						}
					}
					 
					fseek(Ruby, position_of_the_file_pointer, SEEK_SET);
					fscanf(Ruby, "%s", string_for_parameters);
					strcpy(parameters[counter_parameters_for_the_cycle].element, string_for_parameters);
					counter_parameters_for_the_cycle++;
					distance_between_parameters = strlen(string_for_parameters) + 2;
				    fclose(Ruby);
				}
				position_of_the_file_pointer = 0;
				distance_between_parameters = 0;
			}
		}
		stringNumber++;
		stringLength = 0;
	}
	//printf("\n");

	number_of_parameters = counter_parameters_for_the_cycle;
	for(int x = 0; x < counter_parameters_for_the_cycle; x++)
	{
		for(int y = x + 1; y < counter_parameters_for_the_cycle; y++)
		{
			if(strcmp(parameters[x].element, parameters[y].element) == 0)
			{
				strcpy(parameters[y].element, emptyString);
				if(strcmp(parameters[x].element, emptyString) != 0)
				{
					number_of_parameters--;
				}
			}
		}
	}

	printf("Количество параметров: %d\n", number_of_parameters);
	result = (double)practicalManipulation/(number_of_procedure * number_of_parameters);
	printf("Количество подпрограмм: %d", number_of_procedure);
	printf("\nКоличество практических обращений к глобальным переменным: %d\n", practicalManipulation);	
	printf("Ответ: %.1f", result);
    getchar();
    return 0;
}