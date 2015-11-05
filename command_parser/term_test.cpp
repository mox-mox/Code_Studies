#include <sstream>
#include <iostream>
#include <vector>

void hello(std::vector < std::string > arg)
{
	arg=arg;
	std::cout<<"Hello mox!"<<std::endl;
}

void goodbye(std::vector < std::string > arg)
{
	arg=arg;
	std::cout<<"Goodbye mox!"<<std::endl;
}


class Command_parser
{
		struct Command
		{
			const std::string name;
			const std::string description;
			void (*command)(std::vector < std::string >); const
			uint8_t operator()(std::vector < std::string > arg) const
			{
				command(arg);
				return 1;
			}
		};

		friend bool operator == (std::string const& lhs, Command_parser::Command const& rhs);
		uint8_t print_help()
		{
			std::cout<<"Possible command line arguments are:"<<std::endl;
			for (auto &command : command_list)
			{
				std::cout<<command.name<<": "<<command.description<<std::endl;
			}
			return 1;
		}


		std::vector < Command > command_list =
		{
			{ "help", "Print this help message.", nullptr },
			{ "foo", "Write foo to the console.", [](std::vector < std::string > arg){std::cout<<"foobarasdfasdf"<<std::endl;} },
		};





	public:
		bool operator()(std::string command_line_input)
		{
			// Turn the command line input into a vector of strings
			std::vector < std::string > commandline_tokens;
			{
				std::string fragment;
				std::istringstream full_cmd(command_line_input);
				while (std::getline(full_cmd, fragment, ' '))
				{
					commandline_tokens.push_back(fragment);
				}
			}
			uint8_t test = 0;
			for (auto &command : command_list)
			{
				test |= (commandline_tokens[0] == command && ((command.command && command(commandline_tokens)) || print_help() ));
			}
			if(!test)
			{
				std::cout<<"Command not recognised!"<<std::endl;
				print_help();
			}
			return true;
		}

		void add_command(const Command& command)
		{
			command_list.push_back(command);
		}

		Command_parser() {};
		Command_parser(std::initializer_list < Command > sizes)
		{
			for (auto i = sizes.begin(); i != sizes.end(); ++i)
			{
				Command cmd = *i;
				add_command(*i);
			}
		}
};

bool operator == (std::string const& lhs, Command_parser::Command const& rhs)
{
	return lhs == rhs.name;
}




Command_parser cmd_parse =
{
	{ "hello", "do the harlem shake", hello },
	{ "goodbye", "wuuuf", goodbye },
	{ "good", "wuuuf", goodbye },
};

int main()
{
	std::cout<<"Hello world!"<<std::endl;

	std::cout<<"cmd> "<<std::flush;
	std::string command;
	std::cin>>command;


	cmd_parse(command);

	return 0;
}
