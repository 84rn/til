#pragma once
#include "URLFetcher.h"
class CRedditFetcher : public CURLFetcher {

public:
	CRedditFetcher(void);
	CRedditFetcher(std::string url);
	CRedditFetcher(std::string url, std::string serverport, std::string userpassword, long auth_type);
	~CRedditFetcher(void);
	
	std::string get_url() const;
	int fetch();

private:
	std::string after;
};