#include "RedditFetcher.h"
#include "json/json.h"


CRedditFetcher::CRedditFetcher(void) : CURLFetcher() {
	
}

CRedditFetcher::CRedditFetcher(std::string str) : CURLFetcher(str) {
	
}

CRedditFetcher::CRedditFetcher(std::string new_url, std::string server_port, std::string user_password, long auth_type) :
				CURLFetcher(new_url, server_port, user_password, auth_type) {

}

CRedditFetcher::~CRedditFetcher(void) {

}

int CRedditFetcher::fetch() {

	int ret = ::CURLFetcher::fetch();

	Json::Value temp_root;
	Json::Reader reader;

	if (reader.parse(string_data, temp_root, false))

	if (temp_root["data"]["after"].isString())
		after = temp_root["data"]["after"].asString();

	return ret;
}

std::string CRedditFetcher::get_url() const {

	std::string ret;

	if (after.length())
		ret = url + "?count=25&after=" + after;
	else
		ret = url;

	return ret;
}