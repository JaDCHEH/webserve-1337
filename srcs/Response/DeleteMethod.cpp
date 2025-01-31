#include "../../includes/Response/Response.hpp"

int clear_dir(const string& dir_name) 
{
	DIR* dir = opendir(dir_name.c_str());
	int result;
	if (dir == NULL)
	{
		std::cout << "Could not open directory " << dir_name << std::endl;
		return 403;
	}
	dirent* entry;
	while ((entry = readdir(dir)) != NULL) {
		string file_name = entry->d_name;

		if (file_name != "." && file_name != "..")
		{
		   string full_path = dir_name + "/" + file_name;

			if (entry->d_type == DT_DIR) 
			{
				result = clear_dir(full_path);
				if (result != 204)
					return result;
				result = rmdir(full_path.c_str());
				if (result)
				{
					if(result == EACCES)
						return 500;
					return 403;
				}
			} 
			else
			{
				result = unlink(full_path.c_str());
				if (result)
				{
					if(result == EACCES)
						return 500;
					return 403;
				}
			}
		}
	}
	closedir(dir);
	return 204;
}

int	Response::Delete_method(Request &Request)
{
	string fullpath = Request.fullpath;
	DIR *dir = opendir(fullpath.c_str());
	int result ;
	if (dir)
	{
		closedir(dir);
		if (fullpath.back() != '/')
		{
			Request.path += '/';
			return simple_Response(Request, "409");
		}
		clear_dir(fullpath);
		result = clear_dir(fullpath);
		if (result != 204)
			return simple_Response(Request, std::to_string(result));
		result = rmdir(fullpath.c_str());
		if (result)
		{
			if (result == EACCES)
				return simple_Response(Request, "500");
			return simple_Response(Request, "403");
		}
		else
			return simple_Response(Request , "204");
	}
	result = unlink(fullpath.c_str());
	if (result)
	{
		if(result == EACCES)
			return simple_Response(Request, "500");
		return simple_Response(Request, "403");
	}
	return simple_Response(Request , "204");
}