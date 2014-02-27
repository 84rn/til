
#include "URLFetcher.h"
#include <algorithm>
#include <iostream>


CURLFetcher::CURLFetcher(void) : data(NULL), error_code(0) {

}

CURLFetcher::CURLFetcher(std::string str) : data(NULL), error_code(0), url(str) {

}

CURLFetcher::CURLFetcher(std::string new_url, std::string server_port, std::string user_password, long auth_type) :
									data(NULL), error_code(0), url(new_url), proxy_auth_type(auth_type), 
									proxy_user_password(user_password), proxy_server_port(server_port) {
	
}


CURLFetcher::~CURLFetcher(void) {

	if (data)
		delete[] data;

	data = NULL;
}

void CURLFetcher::set_url(std::string new_s) {
	url = new_s;
}

int CURLFetcher::fetch() {

	if (!url.length()) {
		error_msg = "No URL present";
		error_code = -1;
		return error_code;
	}

	CURL* handle = curl_easy_init();
	char buf[1000];
	string_data = "";

//	curl_easy_setopt(handle, CURLOPT_VERBOSE, 1);

	curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(handle, CURLOPT_URL, get_url().c_str());

	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, CURLFetcher::write_f);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, this);

	if (proxy_server_port.length())
		curl_easy_setopt(handle, CURLOPT_PROXY, proxy_server_port.c_str());

	if (proxy_user_password.length()) {
		curl_easy_setopt(handle, CURLOPT_HEADER, 1);
		curl_easy_setopt(handle, CURLOPT_PROXYAUTH, proxy_auth_type);
		curl_easy_setopt(handle, CURLOPT_PROXYUSERPWD, proxy_user_password);
	}

	curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, buf);

	CURLcode ret = curl_easy_perform(handle);	

	curl_easy_cleanup(handle);

	error_msg = std::string(buf);
	error_code = ret;

	return error_code;
}

std::ostream& operator<<(std::ostream& stream, CURLFetcher& fetcher) {
	if (fetcher.data)
		return (stream << fetcher.data);
	else
		return stream;
}


std::string& operator<<(std::string& str, CURLFetcher& fetcher) {

	if (!fetcher.string_data.empty()) {
		str = str + fetcher.string_data;
		return str;
	}
	else 
		return str;
}

size_t CURLFetcher::write_f(char* ptr, size_t size, size_t nmemb, CURLFetcher* ob) {	

	if (ob->data)
		delete[] ob->data;

	ob->data = new char[size * nmemb + 1];
	char* ret = std::copy(ptr, &ptr[size * nmemb], ob->data);
	*ret = 0;

	ob->string_data += std::string(ob->data);

	return ret - ob->data;
}