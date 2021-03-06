#pragma once
/*
inline json11::Json LoadJson(const std::string& filename) {
	std::ifstream ifs(filename);
	if (!ifs) { return nullptr; }

	std::string strJson(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
			);

	//解析
	std::string err;
	json11::Json jsonObj = json11::Json::parse(strJson, err);
	if (err.size() > 0) { return nullptr; }

	return jsonObj;
}
*/
// 安全にRelease関数を実行する
template<class T>
void KdSafeRelease(T*& p) {
	if (p) {
		p->Release();
		p = nullptr;
	}
}



