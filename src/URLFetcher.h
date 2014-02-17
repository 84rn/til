#pragma once
#include <string>
#include "curl/curl.h"

class CURLFetcher {

public:
	CURLFetcher();
	CURLFetcher(std::string url);
	CURLFetcher(std::string url, std::string serverport, std::string userpassword, long auth_type);
	virtual ~CURLFetcher(void);

	void set_url(std::string);
	virtual std::string get_url() const;
	virtual int fetch();
	std::string get_error_msg() const;
	int get_error_code() const;

	friend std::ostream& operator<<(std::ostream& stream, CURLFetcher& fetcher);
	friend std::string& operator<<(std::string& string, CURLFetcher& fetcher);	

private:
	static size_t write_f(char *ptr, size_t size, size_t nmemb, CURLFetcher* ob);
	
protected:
	char* data;
	std::string url;
	std::string proxy_user_password;
	std::string proxy_server_port;
	long proxy_auth_type;
	std::string string_data;

	std::string error_msg;
	int error_code;
};