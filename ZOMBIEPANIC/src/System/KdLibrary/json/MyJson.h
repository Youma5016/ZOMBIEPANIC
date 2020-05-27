#pragma once


class MyJson {

private:
	MyJson() {};
	~MyJson() {};

	std::map<std::string, std::shared_ptr<json11::Json>>jsons;

	std::string Directly = "Resource/JsonData/";

public:


	inline 	std::shared_ptr <json11::Json> LoadJson(const std::string& filename) {
		
		//ÉäÉXÉgì‡åüçı
		if (jsons.find(filename) != jsons.end()) {
			return jsons[filename];
		}

		auto mfilename = Directly+ filename;

		std::ifstream ifs(mfilename);
		if (!ifs) { return nullptr; }

		std::string strJson(
			(std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>())
		);

		//âêÕ
		std::string err;

		auto Json = std::make_shared<json11::Json>();
		//Json->parse(strJson, err);
		(*Json)=json11::Json::parse(strJson, err);
		if (err.size() > 0) { return nullptr; }


		
		jsons[filename] = Json;
		ifs.close();
		return Json;
	}
	inline  void SaveJson(const std::shared_ptr < json11::Json>Json, std::string filename) {
		std::string stJson = (*Json).dump(true);
		
		std::ofstream outFile(Directly + filename);
		outFile << stJson;
		outFile.close();
	}


	bool checkValue(const std::shared_ptr < json11::Json>Json, const std::string& Tag, const std::string & Value);
	 bool checkValue(const std::shared_ptr < json11::Json>Json, const std::string& Tag, const int & Value);
	 bool checkValue(const std::shared_ptr < json11::Json>Json, const std::string& Tag, const double & Value);
	 bool checkValue(const std::shared_ptr < json11::Json>Json, const std::string& Tag, const bool & Value);
	
	


	void AddKeyValue( std::shared_ptr<json11::Json>Json, const std::string& Tag, const std::string Value);
	void AddKeyValue( std::shared_ptr<json11::Json> Json, const std::string& Tag, const int Value);
	void AddKeyValue( std::shared_ptr<json11::Json> Json, const std::string& Tag, const double Value);
	void AddKeyValue( std::shared_ptr<json11::Json> Json, const std::string& Tag, const bool Value);
	void AddKeyValue( std::shared_ptr<json11::Json> Json, const std::string& Tag, const json11::Json& Value);
	





	
	
	json11::Json& NomalJson(const std::shared_ptr < json11::Json>Json) {
		return (*Json);
	}

	static MyJson& GetInstance()
	{
		static MyJson instance;
		return instance;

	}
};
#define JSONS MyJson::GetInstance()

