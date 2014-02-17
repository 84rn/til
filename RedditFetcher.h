#pragma once
#include "URLFetcher.h"
class CRedditFetcher : public CURLFetcher {

public:
	CRedditFetcher(void);
	CRedditFetcher(std::string url);
	CRedditFetcher(std::string url, std::string serverport, std::string userpassword, long auth_type);
	~CRedditFetcher(void);

	void set_url(std::string);
	std::string get_url() const;

private:
	std::string after;
};