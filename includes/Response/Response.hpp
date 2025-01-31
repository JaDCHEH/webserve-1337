#ifndef Response_HPP
#define Response_HPP

#include "../Config/Config.hpp"

class Response
{
private:
	string		_initial_line;
	string		_headers;
	string		_body;
	string		_query_str;
	Server		_server;
	Location	_location;
	mapstring	_code_map;
	mapstring	_extention_map;
public:
	string	get_content_type(string extention);
	string	get_extention(string content_type);
	string	&get_initial_line();
	string	&get_headers();
	int		handle_cgi(Request &, string, string);
	string	error_page_builder(string code);
	void	fill_initial_line(const string version, const string error_code);
	void	fill_header(const string header, const string value);
	void	reset_values();
	void	_codes();
	void	_extentions();
	void	init();
	int		get_file(Request &request, const string &file);
	int		simple_Response(Request &Request, string code);
	int		redirection(Request &request, int flag);
	int		auto_index(Request &request, string &path);
	int		Get_method(Request &Request);
	int 	Delete_method(Request &Request);
	int		Post_method_cgi(Request &Request);
	int		Post_method(Request &Request);
	int		Create_Response(Request &Request, string code);
};

#endif