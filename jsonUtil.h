#pragma once

#include <stdio.h>
#include <boost/filesystem.hpp>
#define RAPIDJSON_HAS_STDSTRING	1
#define RAPIDJSON_HAS_CXX11_RVALUE_REFS	1
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"


typedef rapidjson::PrettyWriter<rapidjson::StringBuffer>	JsonWriterBase;
typedef rapidjson::Document	JsonReaderBase;
typedef rapidjson::Value	JsonValue;


struct JsonWriter : public JsonWriterBase
{
	rapidjson::StringBuffer strBuf;

	JsonWriter();

	void Save(std::string _fPath);
};


struct JsonReader : public JsonReaderBase
{
	bool Load(std::string _fPath);
};


inline JsonWriter::JsonWriter()
 : JsonWriterBase(strBuf)
{
	SetIndent('\t', 1);
	StartObject();
}


inline void JsonWriter::Save(std::string _fPath)
{
	_fPath += ".json";

	EndObject();

	::FILE *pFile = ::fopen(_fPath.c_str(), "wb");
	::fwrite(strBuf.GetString(), sizeof(decltype(strBuf)::Ch), strBuf.GetLength(), pFile);
	::fclose(pFile);
}


inline bool JsonReader::Load(std::string _fPath)
{
	_fPath += ".json";

	namespace fs = boost::filesystem;
	if (!fs::is_regular_file(_fPath))
		return false;

	::FILE *pFile = ::fopen(_fPath.c_str(), "rb");
	::fseek(pFile, 0, SEEK_END);
	long fSize = ::ftell(pFile);
	::rewind(pFile);

	std::vector<char> content;
	content.resize(sizeof(char) * fSize + 1);
	size_t result = ::fread(content.data(), sizeof(char), fSize, pFile);
	assert(result == fSize);
	::fclose(pFile);
	content.back() = '\0';

	if (Parse(content.data()).HasParseError()) {
#ifdef _DEBUG
#ifdef _WIN
		pFile = ::fopen("r:/err.json", "wb");
#elif defined(_APPLE)
		pFile = ::fopen("/Volumes/RamDisk/err.json", "wb");
#endif
		::fwrite(content.data(), sizeof(char), content.size(), pFile);
		::fclose(pFile);
		assert(false);
#endif
		return false;
	}

	return true;
}
