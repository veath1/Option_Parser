#pragma once

#include <iostream>
#include <string>
#include <vector>



class InputParser {
public:
	InputParser(std::string str) {
		std::string tmp;
		for (size_t i = 0; i < str.length(); i++) {

			char c = str[i];
			if (c == ' ') {
				
				this->tokens.push_back(tmp);
				tmp.clear();
			}
			else if (c == '\"') {
				i++;
				while (str[i] != '\"') { 

					tmp += str[i]; 
					i++; 
				}
				this->tokens.push_back(tmp);
				tmp.clear();
			}
			else {
				tmp += c;
			}
		}
		
	}
	/// @author iain
	const std::string& getCmdOption(const std::string& option) const {
		std::vector<std::string>::const_iterator itr;
		itr = std::find(this->tokens.begin(), this->tokens.end(), option);
		if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
			return *itr;
		}
		static const std::string empty_string("");
		return empty_string;
	}
	/// @author iain
	bool cmdOptionExists(const std::string& option) const {
		return std::find(this->tokens.begin(), this->tokens.end(), option)
			!= this->tokens.end();
	}
private:
	std::vector <std::string> tokens;
};

class CmdArgsParser
{
public:
	CmdArgsParser(int argc, wchar_t* argv[])
	{
		for (int i = 1; i < argc; ++i)
		{
			this->cmdTokens.push_back(std::wstring(argv[i]));
		}

	}

	const std::wstring& GetOptionValue(const std::wstring& cmdOption) const
	{
		std::vector<std::wstring>::const_iterator cmdIt;
		cmdIt = std::find(this->cmdTokens.begin(), this->cmdTokens.end(), cmdOption);
		if (cmdIt != this->cmdTokens.end() && ++cmdIt != this->cmdTokens.end())
		{
			return *cmdIt;
		}
		static const std::wstring empty(L"");
		return empty;
	}

	bool WasOptionRequested(const std::wstring& cmdOption) const
	{
		return
			std::find(this->cmdTokens.begin(), this->cmdTokens.end(), cmdOption) != this->cmdTokens.end();
	}

private:
	std::vector <std::wstring> cmdTokens;
};
