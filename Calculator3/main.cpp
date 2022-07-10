#include<iostream>
#include<string>
#include "Parser.h"
#include "Scanner.h"
#include "Calc.h"
#include "Exception.h"
int main()
{
	EStatus status = STATUS_OK;
	Calc calc;
	do
	{
		std::cout << ">";
		std::string buf;
		std::getline(std::cin, buf);
		std::cout << buf << std::endl;
		Scanner scanner(buf);
		if (scanner.IsEmpty())
		{
			Parser parser(scanner, calc);
			try {
				status = parser.Parse();
				if (status == STATUS_OK) {

					std::cout << parser.Calculate() << std::endl;
				}
			}
			catch (SyntaxError& se)
			{
				std::cout << se.what() << std::endl;
				//std::cout << se.StackTrace << std::endl;
			}
			catch (Exception & e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (...)
			{
				std::cout << "Internal error" << std::endl;
			}
		}
		else
		{
			std::cout << "expression is empty" << std::endl;
		}
	}while(status!= STATUS_QUIT);
	return 0;
}