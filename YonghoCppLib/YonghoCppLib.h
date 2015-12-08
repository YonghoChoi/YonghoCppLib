#include <memory>
#include <string>

class YonghoCppLib
{
public:
	YonghoCppLib(){}
	~YonghoCppLib(){}

/// Date Time
	time_t GetNowToTime_t();
	std::shared_ptr<char> GetNowToStr();
	tm GetNowToTmStruct();
	std::shared_ptr<char> ConvertFromTmToString(tm& gmtm);

/// Enum To String
	std::shared_ptr<char> GetEnumToString();
	std::shared_ptr<char> GetEnumToStringByVariable();

/// Json
	std::string WriteJson();
	void ReadJson(std::string jsonStr);

/// Local Ip
	std::string GetLocalIp();
};