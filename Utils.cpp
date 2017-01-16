#include "stdafx.h"
#include "Utils.h"

#include <string>
#include <locale>
#include <codecvt>

Utils::Utils()
{
}


Utils::~Utils()
{
}
int Utils::Mat2CImage(cv::Mat& mat, CImage& cImage)
{
	if (!mat.data || mat.empty())
	{
		return -1;
	}

	if (cImage == NULL || cImage.IsNull())
	{
		cImage.Create(mat.cols, mat.rows, 24);
	}
	uchar * src = mat.data;
	uchar * dst = (uchar *)cImage.GetBits();
	for (int y = 0; y < mat.rows; y++)
	{
		memcpy(dst, src, mat.cols * mat.channels());
		src += mat.step;
		dst += cImage.GetPitch();
	}
	return 0;

}
std::string Utils::CString2String(const CString cstr)
{
	std::wstring ws(cstr);
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
	return myconv.to_bytes(ws);
}
CString Utils::String2CString(const std::string str)
{

	CString s(str.c_str());
	return s;
}
bool Utils::playSound(LPCWSTR file)
{
	return PlaySound(file, NULL, SND_FILENAME | SND_ASYNC);
}

bool Utils::serilizeFeature(DETECTRESULT * feature, std::string file)
{
	std::ofstream out(file, std::ios::binary);
	out.write((char*)feature, sizeof(DETECTRESULT));
	out.close();
	return true;
}
DETECTRESULT Utils::loadFeature(std::string file)
{
	DETECTRESULT fet;
	std::ifstream in(file, std::ios::binary);
	in.read((char *)&fet, sizeof(DETECTRESULT));
	in.close();
	return fet;
}
std::string Utils::getCurrentDatetime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%dXX%X", &tstruct);
	std::string s(buf);
	return s;
}
std::string Utils::getDate(std::string dateTime)
{
	return dateTime.substr(0, dateTime.find("XX"));
}
std::string Utils::getTime(std::string dateTime)
{
	return dateTime.substr(dateTime.find("XX") + 2, dateTime.length());
}
std::string Utils::formatDateTime(std::string dateTime)
{
	std::string s = dateTime;
	std::replace(s.begin(), s.end(), '-', '_');
	std::replace(s.begin(), s.end(), ':', '_');

	return s;
}