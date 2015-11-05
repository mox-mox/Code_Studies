#include "terminal.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>


uint8_t Command_parser::Command::operator()(std::vector < std::string > arg) const
{
	command(arg);
	return 1;				// The return value is used to set the flag that says that a matching command was found
}




void Command_parser::update_max_cmd_length()
{
	for (auto &command : command_list)
	{
		if(command.name.length() > max_cmd_length) max_cmd_length = command.name.length();
	}
}
void Command_parser::update_max_arg_length()
{
	for (auto &command : command_list)
	{
		if(command.args.length() > max_arg_length) max_arg_length = command.args.length();
	}
}




uint8_t Command_parser::print_help()
{
	std::cout<<"Possible command line arguments are:"<<std::endl;
	for (auto &command : command_list)
	{
		std::string name(command.name);
		name.resize(max_cmd_length, ' ');
		std::string args(command.args);
		args.resize(max_arg_length, ' ');
		std::cout<<name<<" : "<<args<<" : "<<command.description<<std::endl;
	}
	return 1;
}



bool Command_parser::operator()(std::string command_line_input)
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
	uint8_t test = (commandline_tokens[0] == "help" && print_help());
	for (auto &command : command_list)
	{
		test |= (commandline_tokens[0] == command && command.command && command(commandline_tokens));
	}
	if(!test)
	{
		std::cout<<"Command not recognised!"<<std::endl;
		print_help();
	}
	return true;
}

void Command_parser::add_command(const Command& command)
{
	command_list.push_back(command);
	if(command.name.length() > max_cmd_length) max_cmd_length = command.name.length();
	if(command.args.length() > max_arg_length) max_arg_length = command.args.length();
}

Command_parser::Command_parser() {};
Command_parser::Command_parser(std::initializer_list < Command > Commands) : command_list(Commands)
{
	update_max_cmd_length();
	update_max_arg_length();
}

bool operator == (std::string const& lhs, Command_parser::Command const& rhs)
{
	return lhs == rhs.name;
}


void hello(std::vector < std::string > arg)
{
	int iterations = arg.size() >= 2 ? std::stoi(arg[1]) : 1;
	for(int i=0; i < iterations; i++)
		std::cout<<"Hello mox!"<<std::endl;
}

void goodbye(std::vector < std::string > arg)
{
	arg=arg;
	std::cout<<"Goodbye mox!"<<std::endl;
}


Command_parser cmd_parse =
{
	{ "hello", "Number of iterations", "do the harlem shake", hello },
	{ "goodbye", "none", "wuuuf", goodbye },
	{ "good", "none", "wuuuf", goodbye },
	{ "foo", "none", "Write foo to the console.", [] (std::vector < std::string > arg){ std::cout<<"foobarasdfasdf"<<std::endl;
	  }
	},
	{ "+", "none", "Increase volume.", [] (std::vector < std::string > arg){ std::cout<<"foobarasdfasdf"<<std::endl;
	  }
	},
};

int main()
{
	std::cout<<"Hello world!"<<std::endl;

	std::cout<<"cmd> "<<std::flush;
	std::string command;
	//std::cin>>command;
	std::getline(std::cin, command);


	cmd_parse(command);

	return 0;
}
