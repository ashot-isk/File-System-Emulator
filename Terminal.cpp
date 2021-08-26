#include <iostream>
#include <vector>
#include <string>

/*
*	ls    // show the contents of the folder
*	mkdir // mkdir fld - create a new folder named fld
*	cd    // cd fld - access a folder named  
*	touch // touch fln - create a blank file named fln
*	rm    // rm fln - delete the file named fln
*	rmdir // rmdir fld - delete a folder named fld
*	cd..  // cd .. - exit to parent directory
*	pwd   // pwd - indicates which folder the user is in relative to the root
*	exit  // Sign Out
*/

bool Validation(std::string command);
std::vector<std::string> tokenization(std::string command);
void ls_Command();
void cd_dot_Command();
void pwd_Command();
void exit_Command();
void mkdir_Command(std::vector<std::string> tmp);
void touch_Command(std::vector<std::string> tmp);
void rm_Command(std::vector<std::string> &tmp);
void cd_Command(std::vector<std::string> tmp);
void rmdir_Command(std::vector<std::string> tmp);

struct iteam
{
	iteam()
	{
		this->is_dir = true;
	}

	iteam(std::string Name, bool is_dir)
	{
		this->is_dir = is_dir;
		this->Name = Name;
	}

	std::string Name;
	bool is_dir;
	std::vector<iteam *> file;
} Root;

static int count{};
static std::vector<iteam *> activeSpaces;

int main()
{
	activeSpaces.push_back(new iteam());
	activeSpaces[count] = &Root;
	std::string command;
	std::cout << "ashot@ashot-HP-ProBook-4530s:~$ ";
	getline(std::cin, command);
	while (command != "exit")
	{
		if (!Validation(command))
		{
			std::cout << command << ": command not found" << std::endl;
		}
		std::cout << "ashot@ashot-HP-ProBook-4530s:~$ ";
		getline(std::cin, command);
	}
}

/**** checks the entered command correctly ****/
bool Validation(std::string command)
{
	std::vector<std::string> tmp;
	tmp = tokenization(command);
	if (tmp.empty())
	{
		return false;
	}
	if (tmp[0] == "ls")
	{
		ls_Command();
	}
	else if (tmp[0] == "cd..")
	{
		cd_dot_Command();
	}
	else if (tmp[0] == "pwd")
	{
		pwd_Command();
	}
	else if (tmp[0] == "touch")
	{
		if (tmp.size() != 2)
		{
			return false;
		}
		touch_Command(tmp);
	}
	else if (tmp[0] == "mkdir")
	{
		if (tmp.size() != 2)
		{
			return false;
		}
		mkdir_Command(tmp);
	}
	else if (tmp[0] == "rm")
	{
		if (tmp.size() != 2)
		{
			return false;
		}
		rm_Command(tmp);
	}
	else if (tmp[0] == "cd")
	{
		if (tmp.size() != 2)
		{
			return false;
		}
		cd_Command(tmp);
	}
	else if (tmp[0] == "rmdir")
	{
		if (tmp.size() != 2)
		{
			return false;
		}
		rmdir_Command(tmp);
	}
	else if (tmp[0] == "exit")
	{
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

/**** divaider for string ****/
std::vector<std::string> tokenization(std::string command)
{
	std::vector<std::string> tmp;
	std::string words{};
	for (int i = 0; i < command.size(); ++i)
	{
		if ((command[i] != ' ') && (command[i] != '\0'))
		{
			words += command[i];
		}
		else
		{
			tmp.push_back(words);
			words.clear();
		}

		if (i == command.size() - 1)
		{
			tmp.push_back(words);
		}
	}

	return tmp;
}

/**** create a new folder named fld ****/
void mkdir_Command(std::vector<std::string> tmp)
{
	activeSpaces[count]->file.push_back(new iteam(tmp[1], true));
}

/**** show the contents of the folder ****/
void ls_Command()
{

	for (int i = 0; i < activeSpaces[count]->file.size(); ++i)
	{
		std::cout << activeSpaces[count]->file[i]->Name << "   ";
	}
	std::cout << std::endl;
}

/**** exit to parent directory ****/
void cd_dot_Command()
{
	if (count != 0)
	{
		count--;
	}
}

/**** indicates which folder the user is in relative to the root ****/
void pwd_Command()
{
	
	for(int i = 0; i <= count ; ++i)
	{
		std::cout<<activeSpaces[i]->Name<<"/";
	}
	std::cout<<std::endl;
}

/**** create a blank file ****/
void touch_Command(std::vector<std::string> tmp)
{
	for (int i = 0; i < activeSpaces[count]->file.size(); ++i)
	{
		if (activeSpaces[count]->file[i]->Name == tmp[1])
		{
			std::cout << tmp[1] << ": already exists" << std::endl;
			return;
		}
	}
	activeSpaces[count]->file.push_back(new iteam(tmp[1], false));
}

/**** delete the file ****/
void rm_Command(std::vector<std::string> &tmp)
{

	for (int i = 0; i < activeSpaces[count]->file.size(); ++i)
	{
		if (activeSpaces[count]->file[i]->Name == tmp[1])
		{
			if (activeSpaces[count]->file[i]->is_dir)
			{
				std::cout << "rm: cannot remove '" << tmp[1] << "': Is a directory" << std::endl;
				return;
			}
			else
			{
				auto it = activeSpaces[count]->file.begin();
				activeSpaces[count]->file.erase(it + i);
				return;
			}
		}
	}
}

/****access a folder named****/
void cd_Command(std::vector<std::string> tmp)
{
	for (int i = 0; i < activeSpaces[count]->file.size(); ++i)
	{
		if (tmp[1] == activeSpaces[count]->file[i]->Name)
		{
			if (!activeSpaces[count]->file[i]->is_dir)
			{
				std::cout << "bash: cd: " << tmp[1] << ": Not a directory" << std::endl;
			}
			else
			{
				activeSpaces.push_back(activeSpaces[count]->file[i]);
				++count;
			}
		}
	}
}

/**** delete a folder named ****/
void rmdir_Command(std::vector<std::string> tmp)
{
	for (int i = 0; i < activeSpaces[count]->file.size(); ++i)
	{
		if (activeSpaces[count]->file[i]->Name == tmp[1])
		{
			if (!activeSpaces[count]->file[i]->is_dir)
			{
				std::cout << "rmdir: failed to remove '" << tmp[i] << "': Not a directory" << std::endl;
				return;
			}
			else
			{
				auto it = activeSpaces[count]->file.begin();
				activeSpaces[count]->file.erase(it + i);
				return;
			}
		}
	}
}