#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <sstream>
#include <iostream>
#include <string>
#include <vector>



class Command_parser
{
	struct Command
	{
		const std::string name;
		const std::string args;
		const std::string description;
		void (*command)(std::vector < std::string >);
		uint8_t operator()(std::vector < std::string > arg) const;
	};
	uint8_t max_cmd_length=0;
	uint8_t max_arg_length=0;
	void update_max_cmd_length();
	void update_max_arg_length();
	uint8_t print_help();

	std::vector < Command > command_list;
	friend bool operator == (std::string const& lhs, Command_parser::Command const& rhs);

	public:
		Command_parser();
		Command_parser(std::initializer_list < Command > Commands);

		void add_command(const Command& command);
		bool operator()(std::string command_line_input);


};



#endif /* TERMINAL_HPP */
